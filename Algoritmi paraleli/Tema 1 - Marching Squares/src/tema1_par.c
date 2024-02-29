// Author: Alexe Alexandra Florentina, 333CC, starting from the frame provided by the apd team

#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include "pthread_barrier_mac.h"

#define CONTOUR_CONFIG_COUNT    16
#define FILENAME_MAX_SIZE       50
#define STEP                    8
#define SIGMA                   200
#define RESCALE_X               2048
#define RESCALE_Y               2048

#define CLAMP(v, min, max) if(v < min) { v = min; } else if(v > max) { v = max; }



// Type of structure used for working with threads
typedef struct {
    ppm_image **image;
    ppm_image **scaled_image;
    ppm_image ***contour_map;
    long thread_id;
    int *threads_no;
    int *step_x;
    int *step_y;
    int *rescale;
    pthread_barrier_t *barrier;
} Structure;

// I create a map between the binary configuration and the pixels that need to be set on the output image. 
ppm_image **init_contour_map() {
    ppm_image **map = (ppm_image **)malloc(CONTOUR_CONFIG_COUNT * sizeof(ppm_image *));
    if (!map) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }

    for (int i = 0; i < CONTOUR_CONFIG_COUNT; i++) {
        char filename[FILENAME_MAX_SIZE];
        sprintf(filename, "../checker/contours/%d.ppm", i);
        map[i] = read_ppm(filename);
    }

    return map;
}

// I call `free` method on the utilized resources
void free_resources(ppm_image *image, ppm_image **contour_map) {
    for (int i = 0; i < CONTOUR_CONFIG_COUNT; i++) {
        free(contour_map[i]->data);
        free(contour_map[i]);
    }
    free(contour_map);

    free(image->data);
    free(image); 
}

ppm_image *rescale_image(ppm_image *image, int *rescale) {

    // I rescale only downwards
    if (image->x <= RESCALE_X && image->y <= RESCALE_Y) {
        *rescale = 0;
        return image;
    }

    // Alloc memory for image
    ppm_image *new_image = (ppm_image *)malloc(sizeof(ppm_image));
    if (!new_image) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
    new_image->x = RESCALE_X;
    new_image->y = RESCALE_Y;

    new_image->data = (ppm_pixel*)malloc(new_image->x * new_image->y * sizeof(ppm_pixel));
    if (!new_image) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }

    // I mark the fact that I started the rescaling
    *rescale = 1;
    return new_image;
}

void *rescale_grid_march_update(void *arg)
{
    Structure *s = (Structure *) arg; 
    int i, j, r, t;

    // If rescaling started, I have to use bicubic interpolation
    if(*s->rescale) {
        uint8_t sample[3];
        // I calculate the indices for parallelization
        int start_res_x = s->thread_id * (*s->scaled_image)->x / *s->threads_no;
        int end_res_x = (s->thread_id + 1) * (*s->scaled_image)->x / *s->threads_no;

        for (i = start_res_x; i < end_res_x; i++) {
            for (j = 0; j < (*s->scaled_image)->y; j++) {
                float u = (float)i / (float)((*s->scaled_image)->x - 1);
                float v = (float)j / (float)((*s->scaled_image)->y - 1);
                sample_bicubic(*s->image, u, v, sample);

                (*s->scaled_image)->data[i * (*s->scaled_image)->y + j].red = sample[0];
                (*s->scaled_image)->data[i * (*s->scaled_image)->y + j].green = sample[1];
                (*s->scaled_image)->data[i * (*s->scaled_image)->y + j].blue = sample[2];
            }
        }
    }

    // I make sure that the scaling of the image is finished before using it
    pthread_barrier_wait(s->barrier);

    // I calculate the number of squares of fixed size that fit in the image and create the grid
    int p = (*s->scaled_image)->x / *s->step_x;
    int q = (*s->scaled_image)->y / *s->step_y;
    unsigned char grid[p + 1][q + 1];

    // Builds the grid of points with 0 or 1, depending on how the pixel values compare to the SIGMA
    for (i = 0; i < p; i++) {
        for (j = 0; j < q; j++) {
            ppm_pixel curr_pixel = (*s->scaled_image)->data[i * *s->step_x * (*s->scaled_image)->y + j * *s->step_y];

            unsigned char curr_color = (curr_pixel.red + curr_pixel.green + curr_pixel.blue) / 3;

            if (curr_color > SIGMA) {
                grid[i][j] = 0;
            } else {
                grid[i][j] = 1;
            }
        }
    }

    // I use pixels on the last row / column of the input image for points with no neighbors below / to the right
    grid[p][q] = 0;
    for (i = 0; i < p; i++) {
        ppm_pixel curr_pixel = (*s->scaled_image)->data[i * *s->step_x * (*s->scaled_image)->y + (*s->scaled_image)->x - 1];
        unsigned char curr_color = (curr_pixel.red + curr_pixel.green + curr_pixel.blue) / 3;

        if (curr_color > SIGMA) {
            grid[i][q] = 0;
        } else {
            grid[i][q] = 1;
        }
    }
    for (j = 0; j < q; j++) {
        ppm_pixel curr_pixel = (*s->scaled_image)->data[((*s->scaled_image)->x - 1) * (*s->scaled_image)->y + j * *s->step_y];
        unsigned char curr_color = (curr_pixel.red + curr_pixel.green + curr_pixel.blue) / 3;

        if (curr_color > SIGMA) {
            grid[p][j] = 0;
        } else {
            grid[p][j] = 1;
        }
    }

    // I make sure that the calculation of the grid is finished before I use it
    pthread_barrier_wait(s->barrier);

    // I calculate the indices for parallelization and execute march and update function
    int start_p = s->thread_id * p / *s->threads_no;
    int end_p = (s->thread_id + 1) * p / *s->threads_no;
    for (i = start_p; i < end_p; i++) {
        for (j = 0; j < q; j++) {
            unsigned char k = 8 * grid[i][j] + 4 * grid[i][j + 1] + 2 * grid[i + 1][j + 1] + 1 * grid[i + 1][j];

            for (r = 0; r < (*s->contour_map)[k]->x; r++) {
                for (t = 0; t < (*s->contour_map)[k]->y; t++) {
                    int contour_pixel_index = (*s->contour_map)[k]->x * r + t;
                    int image_pixel_index = (i * (*s->step_x) + r) * (*s->scaled_image)->y + j * (*s->step_y) + t;

                    (*s->scaled_image)->data[image_pixel_index].red = (*s->contour_map)[k]->data[contour_pixel_index].red;
                    (*s->scaled_image)->data[image_pixel_index].green = (*s->contour_map)[k]->data[contour_pixel_index].green;
                    (*s->scaled_image)->data[image_pixel_index].blue = (*s->contour_map)[k]->data[contour_pixel_index].blue;
                }
            }
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: ./tema1 <in_file> <out_file> <P>\n");
        return 1;
    }

    ppm_image *image = read_ppm(argv[1]);
    int step_x = STEP;
    int step_y = STEP;
    
    // declarations for threads and threads fields
    int threads_no = atoi(argv[3]);
    pthread_t threads[threads_no];
    int r;
    long id;
    void *status;
    int rescale = 0;
    pthread_barrier_t barrier;
    pthread_barrier_init(&barrier, NULL, threads_no);
    
    // Initialize contour map
    ppm_image **contour_map = init_contour_map();

    // Alloc memory for rescaling the image if necessary
    ppm_image *scaled_image = rescale_image(image, &rescale);

    // Create structure fields and create the threads
    Structure s[threads_no];
    for (long id = 0; id < threads_no; id++) {
        s[id].thread_id = id;
        s[id].threads_no = &threads_no;
        s[id].step_x = &step_x;
        s[id].step_y = &step_y;
        s[id].scaled_image = &scaled_image; 
        s[id].image = &image;
        s[id].rescale = &rescale;

        s[id].contour_map = &contour_map;
        s[id].barrier = &barrier;
        
        // Bicubic interpolation if there was rescaling;
        // Sample the grid, march the square
        r = pthread_create(&threads[id], NULL, rescale_grid_march_update, (void *)&s[id]); 
 
        if (r) {
            printf("Eroare la crearea thread-ului %ld\n", id);
            exit(-1);
        }
    }

    // Join threads after rescale_grid_march_update 
    for (id = 0; id < threads_no; id++) {
        r = pthread_join(threads[id], &status);

        if (r) {
            printf("Eroare la asteptarea thread-ului %ld\n", id);
            exit(-1);
        }
    }

    // Write output, destroy barrier, free resources
    write_ppm(scaled_image, argv[2]);
    pthread_barrier_destroy(&barrier);
    free_resources(scaled_image, contour_map);

    return 0;
}
