#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

// functie pentru creearea cererii GET
char *compute_get_request(char *host, char *url, char *query_params,
                            char **cookies, int cookies_count, char **headers)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    // adaug numele metodei, URL-ul, tipul protocolului si parametrii de cerere
    if (query_params != NULL) {
        sprintf(line, "GET %s?%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "GET %s HTTP/1.1", url);
        }
    compute_message(message, line);

    // adaug host-ul
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    // adaug cookies daca exista
    if (cookies != NULL) {
        for (int i = 0; i < cookies_count; i++) {
            sprintf(line, "Cookie:%s", cookies[i]);
            compute_message(message, line);
        }
    }
    // adaug headers daca exista
    if (headers != NULL) {
        sprintf(line, "Authorization: Bearer %s", headers[0]);
        compute_message(message, line);
    }

    // adaug 2 linii noi la final
    compute_message(message,"\r\n");
    return message;
}

// functie pentru creearea cererii POST
char *compute_post_request(char *host, char *url, char* content_type, char **body_data,
            int body_data_fields_count, char **cookies, int cookies_count, char **headers)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    char *body_data_buffer = calloc(LINELEN, sizeof(char));

    // adaug numele metodei, URL-ul, tipul protocolului si parametrii de cerere
    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);
    
    // adaug host-ul
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    // pregatesc datele
    for(int i=0; i < body_data_fields_count; i++) {
        if (i != 0) {
            strcat(body_data_buffer, "&");
        }
        strcat(body_data_buffer, body_data[i]);
   }

   // adaug antetele necesare
   sprintf(line, "Content-Type: application/json");
   compute_message(message, line);
   sprintf(line, "Content-Length: %lu", strlen(body_data_buffer));
   compute_message(message, line);

    // adaug cookies daca exista
    if (cookies != NULL && cookies_count > 0) {
        for (int i = 0; i < cookies_count; i++) {
            sprintf(line, "Cookie: %s", cookies[i]);
            compute_message(message, line);
        }
    }

    // adaug headers daca exista
    if (headers != NULL) {
        sprintf(line, "Authorization: Bearer %s", headers[0]);
        compute_message(message, line);
    }
    
    // adaug linie noua dupa headere
    compute_message(message, "");

    // adaug payload-ul
    memset(line, 0, LINELEN);
    strcat(message, body_data_buffer);

    free(line);
    return message;
}

// functie pentru crearea cererii DELETE
char *compute_delete_request(char *host, char *url, char **headers)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    // adaug numele metodei, URL-ul, tipul protocolului si parametrii de cerere
    sprintf(line, "DELETE %s HTTP/1.1", url);
    compute_message(message, line);

    // adaug host-ul
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    // adaug headere
    if (headers != NULL) {
        sprintf(line, "Authorization: Bearer %s", headers[0]);
        compute_message(message, line);
    }

    // adaug 2 linii noi la final
    compute_message(message,"\r\n");
    return message;
}


