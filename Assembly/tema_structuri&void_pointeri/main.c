#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<inttypes.h>
#include "structs.h"

int add_last(void **arr, int *len, data_structure *data) {
    int ok = 0, i;
    void *f;
    f = *arr;

    for (i = 0; i< *len; i++ ) {
        ok = ok + sizeof(head) + ((head *)f)->len;
        f = f + sizeof(head) + ((head *)f)->len;
    }
    f = *arr;
    f = realloc(f,ok + sizeof(head) + data->header->len);
    
    *arr = f;
    f = f + ok;
    *(head *)f = *data->header;
    f = f + sizeof(head);
    memcpy(f,data->data,data->header->len);
    
    (*len)++;
    free(data->header);
    free(data->data);
    free(data);
    return 0;
}

int add_at(void **arr, int *len, data_structure *data, int index) {

    return 0;
}

void find(void *data_block, int len, int index)  {
    if( index >= 0 && index <= len ) {
        int i;
        for( i = 0; i < index; i++)
            data_block = data_block + sizeof(head) + ((head*)data_block)->len;
        
        if( ((head*)data_block)->type == '1') {
            printf("Tipul 1\n");
            data_block = data_block + sizeof(head);
            printf("%s pentru %s\n",(char*)data_block, (char*)(data_block + strlen((char*)data_block) + 1 + 2*sizeof(int8_t)));
            printf("%"PRId8"\n",*(int8_t *)(data_block + strlen((char *)data_block) + 1));
            printf("%"PRId8"\n",*(int8_t *)(data_block + strlen((char *)data_block) + 1 + sizeof(int8_t)));
            printf("\n");
          }
        else if( ((head*)data_block)->type == '2') {
            printf("Tipul 2\n");
            data_block = data_block + sizeof(head);
            printf("%s pentru %s\n",(char*)data_block, (char*)data_block + strlen((char*)data_block) + 1 + sizeof(int16_t) + sizeof(int32_t));
            printf("%"PRId16"\n",*(int16_t *)(data_block + strlen((char *)data_block) + 1));
            printf("%"PRId32"\n",*(int32_t *)(data_block + strlen((char *)data_block) + 1 + sizeof(int16_t)));
            printf("\n");
           }
        else {
            printf("Tipul 3\n");
            data_block = data_block + sizeof(head);
            printf("%s pentru %s\n",(char*)data_block, (char*)(data_block + strlen((char*)data_block) + 1 + 2*sizeof(int32_t)));
            printf("%"PRId32"\n",*(int32_t *)(data_block + strlen((char *)data_block) + 1));
            printf("%"PRId32"\n",*(int32_t *)(data_block + strlen((char *)data_block) + 1 + sizeof(int32_t)));
            printf("\n");
           }
    }
}

int delete_at(void **arr, int *len, int index) {
    void *cpyarr, *cp, *p; // p- pointer pt arr, cp- pointer pt cpyarr
    int i, ok = 0;
    if( index >= 0 && index <= *len ) { // daca indexul e bun
        p = *arr;
        memcpy(cpyarr, *arr, *len); // cpyarr = *arr, parcurg copia si pun rezultatul final in arr
        cp = cpyarr;
        for (i = 0; i < index; i++ ) { //nr cate biti exista inainte de elem ce trb sters
            ok = ok + sizeof(head) + ((head *)cp)->len;
            cp = cp + sizeof(head) + ((head *)cp)->len;
        }
        
        free(p);
        //newlen = *len - sizeof(head) - ((head *)cp)->len; //noua dimensiune
        p = realloc( p, *len - sizeof(head) - ((head *)cp)->len); // fac alocarea corecta
        
        cp = cpyarr;
        memcpy(p, cp, ok); // pun bitii de dinainte elem ce trb sters
               
        cp = cp + sizeof(head) + ((head *)cp)->len; // sar peste elem ce trb sterse
        
        ok = 0;
        for (i = index + 1; i <= *len; i++ ) { //nr cati biti sunt dupa elem ce trb sterse
            ok = ok + sizeof(head) + ((head *)cp)->len;
            cp = cp + sizeof(head) + ((head *)cp)->len;
        }
        memcpy(p, cp, ok);//copiez restul elementelor
        *len = *len - 1;
    }
    return 0;
}

void print( void *arr, int len) {
    int i;
    void *copie;
    for (i = 0; i< len; i++ ) {
    copie = arr;
        if( ((head*)copie)->type == '1') {
            printf("Tipul 1\n");
            copie = copie + sizeof(head);
            printf("%s pentru %s\n",(char*)copie, (char*)(copie + strlen((char*)copie) + 1 + 2*sizeof(int8_t)));
            printf("%"PRId8"\n",*(int8_t *)(copie + strlen((char *)copie) + 1));
            printf("%"PRId8"\n",*(int8_t *)(copie + strlen((char *)copie) + 1 + sizeof(int8_t)));
            printf("\n");
          }
        else if( ((head*)copie)->type == '2') {
            printf("Tipul 2\n");
            copie = copie + sizeof(head);
            printf("%s pentru %s\n",(char*)copie, (char*)(copie + strlen((char*)copie) + 1 + sizeof(int16_t) + sizeof(int32_t) ));
            printf("%"PRId16"\n",*(int16_t *)(copie + strlen((char *)copie) + 1));
            printf("%"PRId32"\n",*(int32_t *)(copie + strlen((char *)copie) + 1 + sizeof(int16_t)));
            printf("\n");
           }
        else {
            printf("Tipul 3\n");
            copie = copie + sizeof(head);
            printf("%s pentru %s\n",(char*)copie, (char*)(copie + strlen((char*)copie) + 1 + 2*sizeof(int32_t)));
            printf("%"PRId32"\n",*(int32_t *)(copie + strlen((char *)copie) + 1));
            printf("%"PRId32"\n",*(int32_t *)(copie + strlen((char *)copie) + 1 + sizeof(int32_t)));
            printf("\n");
           }
    arr = arr + ((head*)arr)->len + sizeof(head);
    }
}

int main() {
    void *arr = NULL;
    arr = malloc(sizeof(head));
    int len = 0, count = 0, i = 0, index;
    char c;
    char *command;
    
    while ( 1 ) {
        data_structure *Structure = (data_structure *)malloc(sizeof(data_structure));
        Structure->header = (head *)malloc(sizeof(head));
        i = 0;    //citesc comanda caracter cu caracter
    count = 0;
        command = malloc(1);
        scanf("%c",&c);
        while(c != ' ' && c != '\n') {
            count++;
            command = realloc( command, count);
            command[i++] = c;
            scanf("%c",&c);
        }
        command = realloc(command, ++count);
        command[i] = '\0';
        
        if ( strcmp(command,"insert") == 0 ) { // COMANDA INSERT
            char tip;
            scanf("%c",&tip);
            Structure->header->type = tip;
            
            if ( Structure->header->type == '1') { //TIPUL 1
                int8_t suma1, suma2;
                char *dedicator, *dedicatul;
                dedicator = malloc(1);
                dedicatul = malloc(1);
                void *p;
                
                
                scanf("%c",&c); //citesc DEDICATORUL
                scanf("%c",&c);// ~ un spatiu liber
                count = 0;
                i = 0;
                while(c != ' ' && c != '\n') {
                    count++;
                    dedicator = realloc( dedicator, count);
                    dedicator[i++] = c;
                    scanf("%c",&c);
                }
                dedicator = realloc(dedicator, ++count);
                dedicator[i] = '\0';
                
                scanf("%"PRId8"%"PRId8"", &suma1, &suma2); //citesc NUMERELE
                
                scanf("%c",&c); // citesc DEDICATUL
                scanf("%c",&c);
                count = 0;
                i = 0;
                while(c != ' ' && c != '\n') {
                    count++;
                    dedicatul = realloc( dedicatul, count);
                    dedicatul[i++] = c;
                    scanf("%c",&c);
                }
                dedicatul = realloc(dedicatul, ++count);
                dedicatul[i] = '\0';
                
                //initializari si alocari memmorie pt struct
                Structure->data = malloc( (strlen(dedicator) + 1) * sizeof(char) + sizeof(int8_t) + sizeof(int8_t) + (strlen(dedicatul) + 1)*sizeof(char));
                
                p = Structure->data;
                Structure->header->len = strlen(dedicatul) + 1 + 2*sizeof(int8_t) + strlen(dedicator) + 1;
                
                strcpy((char *)Structure->data, dedicator);
                Structure->data = Structure->data + strlen(dedicator) + 1;
                
                *(int8_t *)Structure->data = suma1;
                Structure->data = Structure->data + sizeof(int8_t);
                
                *(int8_t *)Structure->data = suma2;
                Structure->data = Structure->data + sizeof(int8_t);
               
                strcpy((char *)Structure->data, dedicatul);
                Structure->data = Structure->data + strlen(dedicatul) + 1;
                Structure->data = p;
                
                free(dedicatul);
                free(dedicator);
            }
            else if ( Structure->header->type == '2') { //TIPUL 2
                int16_t suma1;
                int32_t suma2;
                char *dedicator, *dedicatul;
                dedicator = malloc(1);
                dedicatul = malloc(1);
                void *p;
                
                
                scanf("%c",&c); //citesc DEDICATORUL
                scanf("%c",&c);// ~ un spatiu liber
                count = 0;
                i = 0;
                while(c != ' ' && c != '\n') {
                    count++;
                    dedicator = realloc( dedicator, count);
                    dedicator[i++] = c;
                    scanf("%c",&c);
                }
                dedicator = realloc(dedicator, ++count);
                dedicator[i] = '\0';
                
                scanf("%"PRId16"%"PRId32"", &suma1, &suma2); //citesc NUMERELE
                
                scanf("%c",&c); // citesc DEDICATUL
                scanf("%c",&c);
                count = 0;
                i = 0;
                while(c != ' ' && c != '\n') {
                    count++;
                    dedicatul = realloc( dedicatul, count);
                    dedicatul[i++] = c;
                    scanf("%c",&c);
                }
                dedicatul = realloc(dedicatul, ++count);
                dedicatul[i] = '\0';
                
                //initializari si alocari memorie pt struct
                Structure->data = malloc( (strlen(dedicator) + 1) * sizeof(char) + sizeof(int16_t) + sizeof(int32_t) + (strlen(dedicatul) + 1)*sizeof(char));
                
                p = Structure->data;
                Structure->header->len = strlen(dedicatul) + 1 + sizeof(int16_t) + sizeof(int32_t) + strlen(dedicator) + 1;
                
                strcpy((char *)Structure->data, dedicator);
                Structure->data = Structure->data + strlen(dedicator) + 1;
                
                *(int16_t *)Structure->data = suma1;
                Structure->data = Structure->data + sizeof(int16_t);
                
                *(int32_t *)Structure->data = suma2;
                Structure->data = Structure->data + sizeof(int32_t);
               
                strcpy((char *)Structure->data, dedicatul);
                Structure->data = Structure->data + strlen(dedicatul) + 1;
                Structure->data = p;
                
                free(dedicatul);
                free(dedicator);
        }
            else { // TIPUL 3
                int32_t suma1, suma2;
                char *dedicator, *dedicatul;
                dedicator = malloc(1);
                dedicatul = malloc(1);
                void *p;
                
                
                scanf("%c",&c); //citesc DEDICATORUL
                scanf("%c",&c);// ~ un spatiu liber
                count = 0;
                i = 0;
                while(c != ' ' && c != '\n') {
                    count++;
                    dedicator = realloc( dedicator, count);
                    dedicator[i++] = c;
                    scanf("%c",&c);
                }
                dedicator = realloc(dedicator, ++count);
                dedicator[i] = '\0';
                
                scanf("%"PRId32"%"PRId32"", &suma1, &suma2); //citesc NUMERELE
                
                scanf("%c",&c); // citesc DEDICATUL
                scanf("%c",&c);
                count = 0;
                i = 0;
                while(c != ' ' && c != '\n') {
                    count++;
                    dedicatul = realloc( dedicatul, count);
                    dedicatul[i++] = c;
                    scanf("%c",&c);
                }
                dedicatul = realloc(dedicatul, ++count);
                dedicatul[i] = '\0';
                
                //initializari si alocari memmorie pt struct
                Structure->data = malloc( (strlen(dedicator) + 1) * sizeof(char) + 2*sizeof(int32_t) + (strlen(dedicatul) + 1)*sizeof(char));
                
                p = Structure->data;
                Structure->header->len = strlen(dedicatul) + 1 + 2*sizeof(int32_t) + strlen(dedicator) + 1;
                
                strcpy((char *)Structure->data, dedicator);
                Structure->data = Structure->data + strlen(dedicator) + 1;
                
                *(int32_t *)Structure->data = suma1;
                Structure->data = Structure->data + sizeof(int32_t);
                
                *(int32_t *)Structure->data = suma2;
                Structure->data = Structure->data + sizeof(int32_t);
               
                strcpy((char *)Structure->data, dedicatul);
                Structure->data = Structure->data + strlen(dedicatul) + 1;
                Structure->data = p;
                
                free(dedicatul);
                free(dedicator);
            }
            
            if ( add_last( &arr, &len, Structure) )
                printf("Functia add_last nu s-a executat cu succes.\n");
        }
        else if( strcmp(command,"exit") == 0 ) { //COMANDA EXIT
            free(command);
            free(arr);
            return 0;
        }
        else if ( strcmp(command,"print") == 0 ) { //COMANDA PRINT
            print(arr, len);
        }
        else if( strcmp(command,"find") == 0) { //COMANDA FIND
            scanf("%d", &index);
            find( arr, len, index);
        }
        else if( strcmp(command,"delete_at") == 0) { //COMANDA DELETE_AT
            scanf("%d", &index);
            if ( !delete_at( &arr, &len, index) )
                printf("Functia delete_at nu s-a executat cu succes.\n");
        }
        free(command);
    }
    free(arr);
    return 0;
}
