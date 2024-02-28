#include <stdio.h>
#include <stdlib.h>     
#include <unistd.h>     
#include <string.h>     
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h>      
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include <ctype.h>

#define MAX_COMMAND_LEN 100
#define MAX_INPUT_LEN 100

// functie pentru extragerea cartilor din json ul primit ca raspuns al cererii
void extract_books(const char* json) {
    // caut prima paranteza deschisa
    const char* start = strchr(json, '{');
    const char* end = NULL;
    
    while (start != NULL) {
        // caut prima paranteza inchisa
        end = strchr(start, '}');

        // daca nu gasesc paranteza închisa, ies din bucla
        if (end == NULL) {
            break; 
        }

        // afisez continutul dintre paranteze
        for (const char* p = start + 1; p <= end - 1; ++p) {
            printf("%c", *p);
        }

        // adaug un rand nou
        printf("\n");
        
        // caut urmatoarea paranteza deschisa
        start = strchr(end, '{'); 
    }
    // daca nu exista date de afisat
    if (end == NULL) {
        printf("Nu exista carti in biblioteca!\n");
    }
}


int main(int argc, char *argv[])
{
    char command[MAX_COMMAND_LEN] = "";
    char input[MAX_INPUT_LEN] = "";
    char *message;
    char *response;
    int sockfd;
    char *cookie_start;
    char *cookie_end;
    char *session_cookie = NULL;
    char *token_start;
    char *token_end;
    char *jwt_token = NULL;
    int num_words;

    while (1)
    {

        // citesc comanda si elimin caracterul \n
        fgets(command, MAX_COMMAND_LEN, stdin);
        command[strcspn(command, "\n")] = '\0';

        // comanda exit
        if (strcmp(command, "exit") == 0)
        {
            break;
        }

        // comanda register (tip POST)
        if (strcmp(command, "register") == 0)
        {
            // deschid conexiunea
            sockfd = open_connection("34.254.242.81", 8080, AF_INET, SOCK_STREAM, 0);

            // citesc username-ul valid (nu se permit sirul vid si spatii)
            char *username = NULL;
            num_words = 1;
            do {
                printf("username=");
                fgets(input, MAX_INPUT_LEN, stdin);
                input[strcspn(input, "\n")] = '\0';

                num_words = 1;
                for (int i = 0; input[i] != '\0'; i++) {
                    if (input[i] == ' ') {
                        num_words++;
                    }
                }

                if (num_words > 1) {
                    printf("Nu sunt permise spatii!\n");
                } else {
                    username = realloc(username, strlen(input) + 1);
                    strcpy(username, input);
                }
            } while (username == NULL || strlen(username) < 1 || num_words > 1);

            // citesc parola valida (nu se permite sirul vid)
            char *password = NULL;
            num_words = 1;
            do {
                printf("password=");
                fgets(input, MAX_INPUT_LEN, stdin);
                input[strcspn(input, "\n")] = '\0';

                num_words = 1;
                for (int i = 0; input[i] != '\0'; i++) {
                    if (input[i] == ' ') {
                        num_words++;
                    }
                }

                if (num_words > 1) {
                    printf("Nu sunt permise spatii!\n");
                } else {
                    password = realloc(password, strlen(input) + 1);
                    strcpy(password, input);
                }
            } while (password == NULL || strlen(password) < 1 || num_words > 1);

            // construiesc datele
            char data[BUFLEN];
            sprintf(data, "{\n\t\"username\": \"%s\",\n\t\"password\": \"%s\"\n}", username, password);
            char *body_data[] = {data};

            // trimit cererea si primesc raspunsul
            message = compute_post_request("34.254.242.81", "/api/v1/tema/auth/register", "application/json", body_data, 1, NULL, 0, NULL);
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);

            // verific dacă înregistrarea a avut succes sau username-ul e deja folosit
            if (strstr(response, "is taken") != NULL)
            {
                printf("Username-ul este deja folosit de către cineva!\n");
            }
            else
            {
                printf("200 - OK - Utilizator inregistrat cu succes!\n");
            }

            // eliberez memoria si inchid conexiunea
            free(username);
            free(password);
            close_connection(sockfd);
        }

        // comanda login (tip POST)
        if (strcmp(command, "login") == 0 && session_cookie == NULL)
        {
            sockfd = open_connection("34.254.242.81", 8080, AF_INET, SOCK_STREAM, 0);

            // citesc username-ul valid
            char *username = NULL;
            num_words = 1;
            do {
                printf("username=");
                fgets(input, MAX_INPUT_LEN, stdin);
                input[strcspn(input, "\n")] = '\0';

                num_words = 1;
                for (int i = 0; input[i] != '\0'; i++) {
                    if (input[i] == ' ') {
                        num_words++;
                    }
                }

                if (num_words > 1) {
                    printf("Nu sunt permise spatii!\n");
                } else {
                    username = realloc(username, strlen(input) + 1);
                    strcpy(username, input);
                }
            } while (username == NULL || strlen(username) < 1 || num_words > 1);


            // citesc parola valida
            char *password = NULL;
            num_words = 1;
            do {
                printf("password=");
                fgets(input, MAX_INPUT_LEN, stdin);
                input[strcspn(input, "\n")] = '\0';

                num_words = 1;
                for (int i = 0; input[i] != '\0'; i++) {
                    if (input[i] == ' ') {
                        num_words++;
                    }
                }

                if (num_words > 1) {
                    printf("Nu sunt permise spatii!\n");
                } else {
                    password = realloc(password, strlen(input) + 1);
                    strcpy(password, input);
                }
            } while (password == NULL || strlen(password) < 1 || num_words > 1);


            // construiesc datele
            char data[BUFLEN];
            sprintf(data, "{\n\t\"username\": \"%s\",\n\t\"password\": \"%s\"\n}", username, password);
            char *body_data[] = {data};

            // trimit cererea si primesc mesajul
            message = compute_post_request("34.254.242.81", "/api/v1/tema/auth/login", "application/json", body_data, 1, NULL, 0, NULL);
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);

            // verific daca parola este incorecta
            if (strstr(response, "Credentials are not good!") != NULL)
            {
                printf("Parola incorecta!\n");
            }
            // sau daca contul nu a fost inregistrat
            else if (strstr(response, "No account with this username!") != NULL)
            {
                printf("Nu exista un cont pentru acest username!\n");
            }
            // sau cazul de succes
            else
            {
                printf("200 - OK - Bun venit!\n");
                // extrag in session_cookie, cookie-ul primit
                cookie_start = strstr(response, "Set-Cookie:");
                    if (cookie_start != NULL) {
                        cookie_start += strlen("Set-Cookie:");
                        cookie_end = strchr(cookie_start, ';');
                        if (cookie_end != NULL) {
                            size_t cookie_length = cookie_end - cookie_start;
                            session_cookie = realloc(session_cookie, cookie_length + 1);
                            strncpy(session_cookie, cookie_start, cookie_length);
                            session_cookie[cookie_length] = '\0';
                        }
                    }
            }

            free(username);
            free(password);
            close_connection(sockfd);
        } 
        // comanda login in cazul in care cookie-ul e deja existent
        else if(strcmp(command, "login") == 0 && session_cookie != NULL) {
            printf("Esti deja logat!\n");
        }

        // comanda entry_library (tip GET)
        if (strcmp(command, "enter_library") == 0 && jwt_token == NULL)
        {
            sockfd = open_connection("34.254.242.81", 8080, AF_INET, SOCK_STREAM, 0);

            // trimit cererea, ce include cookie-ul si primesc raspunsul
            char *cookies[] = {session_cookie};
            message = compute_get_request("34.254.242.81", "/api/v1/tema/library/access", NULL, cookies, 1, NULL);
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);

            // verific daca cererea a avut succes sau daca userul nu e logat
            if (strstr(response, "You are not logged in!") != NULL)
            {
                printf("Nu esti logat!\n");
            }
            else
            {
                printf("200 - OK - Biblioteca accesata cu succes!\n");
                // extrag token-ul in jwt_token
                token_start = strstr(response, "{\"token\":\"");
                if (token_start != NULL) {
                    token_start += strlen("{\"token\":\"");
                    token_end = strstr(token_start, "\"}");
                    if (token_end != NULL) {
                        size_t token_length = token_end - token_start;
                        jwt_token = realloc(jwt_token, token_length + 1);
                        strncpy(jwt_token, token_start, token_length);
                        jwt_token[token_length] = '\0';
                    }
                }
            }
            close_connection(sockfd);
        }
        // comanda enter_library in cazul in care token-ul e deja existent 
        else if (strcmp(command, "enter_library") == 0 && jwt_token != NULL) {
            printf("Ai deja acces la biblioteca!\n");
        }

        // comanda get_books (tip GET)
        if (strcmp(command, "get_books") == 0)
        {
            sockfd = open_connection("34.254.242.81", 8080, AF_INET, SOCK_STREAM, 0);

            // trimit cererea, incluzand token-ul
            // jwt_token poate fi null daca nu exista acces la biblioteca
            if(jwt_token != NULL) {
                char *headers[] = {jwt_token};
                message = compute_get_request("34.254.242.81", "/api/v1/tema/library/books", NULL, NULL, 1, headers);

            } else {
                char **headers = NULL;
                message = compute_get_request("34.254.242.81", "/api/v1/tema/library/books", NULL, NULL, 1, headers);
            }
            
            // primesc raspunsul
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);

            // verific daca exista acces, caz in care se afiseaza cartile
            if (strstr(response, "Authorization header is missing!") != NULL)
            {
                printf("Nu ai acces la biblioteca!\n");
            } else {
                const char* start = strchr(response, '[');
                if (start != NULL) {
                    // ignor primul caracter după [
                    start++;  
                    extract_books(start);
                }
            }
            close_connection(sockfd);
        }

        // comanda get_book (tip GET)
        if (strcmp(command, "get_book") == 0)
        {
            sockfd = open_connection("34.254.242.81", 8080, AF_INET, SOCK_STREAM, 0);
            int id = -1;

            // citesc id ul numeric
            do {
                printf("id=");
                if (scanf("%d", &id) != 1) {
                    printf("Introduceti un numar intreg.\n");
                    // curat buffer-ul de intrare în caz de introducere greșită
                    scanf("%*[^\n]");
                    scanf("%*c");
                }
            } while (id < 1);

            // curat buffer-ul de intrare pt viitoare citiri
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            
            // creez url-ul, adaugand id-ul
            char url[40];
            sprintf(url,"/api/v1/tema/library/books/%d", id);

            // creez cererea, incluzand url-ul si headerul cu token
            // jwt_token poate fi null daca nu exista acces la biblioteca
            if(jwt_token != NULL) {
                char *headers[] = {jwt_token};
                message = compute_get_request("34.254.242.81", url, NULL, NULL, 1, headers);
            } else {
                char **headers = NULL;
                message = compute_get_request("34.254.242.81", url, NULL, NULL, 1, headers);
            }
            
            // trimit cererea si primesc raspusnul
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);

            // verific daca exista acces la biblioteca
            if (strstr(response, "Authorization header is missing!") != NULL) {
                printf("Nu ai acces la biblioteca!\n");
            } 
            // verific daca exista cartea cu acel id
            else if(strstr(response, "No book was found!") != NULL) {
                printf("Cartea cu id %d nu exista!\n", id);
            } 
            // cazul de succes in care afisez datele acelei carti
            else {
                extract_books(response);
            }
            close_connection(sockfd);
        }

        // comanda add_book (POST)
        if (strcmp(command, "add_book") == 0)
        {
            sockfd = open_connection("34.254.242.81", 8080, AF_INET, SOCK_STREAM, 0);

            // citesc titlul
            char *title = NULL;
            do {
                printf("title=");
                fgets(input, MAX_INPUT_LEN, stdin);
                input[strcspn(input, "\n")] = '\0';
                if (strlen(input) < 1) {
                    printf("Introduceti cel putin un caracter.\n");
                } else {
                    title = realloc(title, strlen(input) + 1);
                    strcpy(title, input);
                }
            } while (title == NULL || strlen(title) < 1);


            // citesc autorul
            char *author = NULL;
            do {
                printf("author=");
                fgets(input, MAX_INPUT_LEN, stdin);
                input[strcspn(input, "\n")] = '\0';
                if (strlen(input) < 1) {
                    printf("Introduceti cel putin un caracter.\n");
                } else {
                    author = realloc(author, strlen(input) + 1);
                    strcpy(author, input);
                }
            } while (author == NULL || strlen(author) < 1);

            // citesc genul
            char *genre = NULL;
            do {
                printf("genre=");
                fgets(input, MAX_INPUT_LEN, stdin);
                input[strcspn(input, "\n")] = '\0';
                if (strlen(input) < 1) {
                    printf("Introduceti cel putin un caracter.\n");
                } else {
                    genre = realloc(genre, strlen(input) + 1);
                    strcpy(genre, input);
                }
            } while (genre == NULL || strlen(genre) < 1);

            // citesc id ul valid, numeric
            int page_count = -1;
            do {
                printf("page_count=");
                if (scanf("%d", &page_count) != 1) {
                    printf("Introduceti un numar intreg.\n");
                    // curat buffer-ul de intrare în caz de introducere greșită
                    scanf("%*[^\n]");
                    scanf("%*c");
                }
            } while (page_count < 1);

            // citesc editorul
            char *publisher = NULL;
            do {
                printf("publisher=");

                 // curat buffer-ul de intrare inainte de a utiliza fgets
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {
                }

                fgets(input, MAX_INPUT_LEN, stdin);
                input[strcspn(input, "\n")] = '\0';
                if (strlen(input) < 1) {
                    printf("Introduceti cel putin un caracter.\n");
                } else {
                    publisher = realloc(publisher, strlen(input) + 1);
                    strcpy(publisher, input);
                }
            } while (publisher == NULL || strlen(publisher) < 1);


            // construiesc datele
            char data[BUFLEN];
            sprintf(data, "{\n\t\"title\": \"%s\",\n\t\"author\": \"%s\",\n\t\"genre\": \"%s\",\n\t\"page_count\": %d,\n\t\"publisher\": \"%s\"\n}", title, author, genre, page_count, publisher);
            char *body_data[] = {data};

            // construiesc cererea (daca am acces la biblioteca)
            if(jwt_token != NULL) {
                char *headers[] = {jwt_token};
                message = compute_post_request("34.254.242.81", "/api/v1/tema/library/books", "application/json", body_data, 1, NULL, 0, headers);
            } else {
                char **headers = NULL;
                message = compute_post_request("34.254.242.81", "/api/v1/tema/library/books", "application/json", body_data, 1, NULL, 0, headers);
            }

            // trimit cererea si primesc raspuns de la server
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);

            // verific dacă înregistrarea a avut succes sau daca nu exista acces la biblioteca
            if (strstr(response, "Authorization header is missing!") != NULL)
            {
                printf("Nu ai acces la biblioteca!\n");
            } else {
                printf("200 - OK - Carte adaugata cu succes!\n");
            }

            // eliberez memoria alocata
            free(title);
            free(author);
            free(genre);
            free(publisher);
            close_connection(sockfd);
        } 

        // comanda delete_book (DELETE)
        if (strcmp(command, "delete_book") == 0)
        {
            sockfd = open_connection("34.254.242.81", 8080, AF_INET, SOCK_STREAM, 0);

            // citesc id ul valid, numeric
            int id = -1;
            do {
                printf("id=");
                if (scanf("%d", &id) != 1) {
                    printf("Introduceti un numar intreg.\n");
                    // curat buffer-ul de intrare in caz de introducere gresita
                    scanf("%*[^\n]");
                    scanf("%*c");
                }
            } while (id < 1);

            // curat buffer-ul de intrare inainte de a utiliza fgets
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
            }

            // creez url-ul incluzand id-ul
            char url[40];
            sprintf(url,"/api/v1/tema/library/books/%d", id);

            // construiesc cererea (daca am acces la biblioteca)
            if(jwt_token != NULL) {
                char *headers[] = {jwt_token};
                message = compute_delete_request("34.254.242.81", url, headers);
            } else {
                char **headers = NULL;
                message = compute_delete_request("34.254.242.81", url, headers);
            }

            // trimit cererea si primesc raspuns
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);

            // verific dacă exista acces la biblioteca
            if(strstr(response, "Authorization header is missing!") != NULL) {
                printf("Nu ai acces la biblioteca!\n");
            } 
            // verific daca exista cartea cu acel id
            else if (strstr(response, "No book was deleted!") != NULL) {
                printf("Nu exista nicio carte cu id-ul %d!\n", id);
            } 
            // cazul de succes
            else {
                printf("200 - OK - Carte stearsa cu succes!\n");
            }
            close_connection(sockfd);
        }

        // comanda logout (tip GET)
        if (strcmp(command, "logout") == 0)
        {
            sockfd = open_connection("34.254.242.81", 8080, AF_INET, SOCK_STREAM, 0);

            // creez cererea, ce include cookie-ul
            if (session_cookie != NULL) {
                char *cookies[] = {session_cookie};
                message = compute_get_request("34.254.242.81", "/api/v1/tema/auth/logout", NULL, cookies, 1, NULL);
            } else {
                char **cookies = NULL;
                message = compute_get_request("34.254.242.81", "/api/v1/tema/auth/logout", NULL, cookies, 1, NULL);
            }

            // trimit cererea si primesc raspuns
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);

            // verific daca cererea a avut succes sau userul nu e logat
            if (strstr(response, "You are not logged in!") != NULL)
            {
                printf("Nu esti logat!\n");
            }
            else
            {
                printf("200 - OK - Tocmai te-ai delogat!\n");
                // setez nule token-ul si cookie-ul
                session_cookie = NULL;
                jwt_token = NULL;
            }
            close_connection(sockfd);
        }
        // printare intre comenzi pentru a vizualiza print urile mai usor
        printf("----------------------------------------------------------------\n");
    }
    return 0;
}