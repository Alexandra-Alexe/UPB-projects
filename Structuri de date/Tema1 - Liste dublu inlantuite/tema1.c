#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct node {
    int *timestamp;
    double *value;
    struct node *next;
    struct node *prev;
} node_t;

typedef struct dl_list {
    node_t *head;
    node_t *tail;
    int len;
} list_t;

list_t *init_list() {
    list_t *new_list = malloc(sizeof(list_t));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->len = 0;
    return new_list;
}

node_t *init_node(int *timestamp, double *value) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->timestamp = malloc(sizeof(int));
    new_node->value = malloc(sizeof(double));
    *new_node->timestamp = *timestamp;
    *new_node->value = *value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void print_list(list_t *list) {
    node_t *aux = list->head;
    if (aux == NULL) {
        printf("NULL\n");
        return;
    }
    printf("%d\n", list->len);
    while (aux != list->tail) {
        printf("%d %.2lf\n", *aux->timestamp, round((*aux->value)*100)/100);
        aux = aux->next;
    }
    printf("%d %.2lf\n", *aux->timestamp, round((*aux->value)*100)/100);
}

void free_node(node_t *nod) {
    free(nod->value);
    free(nod->timestamp);
    free(nod);
}

void destroy_list(list_t *list) {
    node_t *aux;
    while (list->len > 0) {
        aux = list->tail;
        list->tail = list->tail->prev;
        free_node(aux);
        --list->len;
    }
    free(list);
}

void remove_node(list_t *list, int position) {
    int i;
    if( position == 0) {
        node_t *nod = list->head;
        list->head = nod->next;
        nod->next->prev = NULL;
        free_node(nod);
        list->len --;
    } else if( position == list->len -1) {
        node_t *nod = list->tail;
        list->tail = nod->prev;
        nod->prev->next = NULL;
        free_node(nod);
        list->len --;
    } else if( position <= (list->len) /2 ) {
        node_t *nod = list->head;
        for( i=0; i<position; i++)
            nod = nod->next;
        nod->next->prev = nod->prev;
        nod->prev->next = nod->next;
        free_node(nod);
        list->len--;
    } else {
        node_t *nod = list->tail;
        for( i=list->len; i>position+1; i-- )
            nod = nod->prev;
        nod->next->prev = nod->prev;
        nod->prev->next = nod->next;
        free_node(nod);
        list->len--;
    }
}

void insert_node(list_t *list, double *value, int *timestamp, int position) {
    int i;
    if( list->len == 0) {
        node_t *new_node = init_node(timestamp,value);
        list->head = new_node;
        list->tail = new_node;
        list->len ++;
    } else if( position == 0) {
        node_t *new_node = init_node(timestamp, value);
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
        list->len ++;
    } else if( position == list->len ) {
        node_t *new_node = init_node(timestamp, value);
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
        list->len++;
    } else if( position <= (list->len)/2-1 ) {
        node_t *new_node = init_node(timestamp, value);
        node_t *first = list->head;
        for( i=0; i<position-1; i++)
            first = first->next;
        new_node->prev = first;
        new_node->next = first->next;
        first->next->prev = new_node;
        first->next = new_node;
        list->len++;
    } else if( position >= (list->len / 2) ) {
        node_t *new_node = init_node(timestamp, value);
        node_t *last = list->tail;
        for( i=list->len; i>position; i--)
            last = last->prev;
        new_node->next = last->next;
        new_node->prev = last;
        last->next->prev = new_node;
        last->next = new_node;
        list->len++;
    }
}

void insert_sorted_asc(list_t *list, double value, int timestamp) {
    node_t *current, *new_node;
    new_node = init_node(&timestamp, &value);
    current = list->head;
    if( list->len == 0) {
        list->head = new_node;
        list->tail = new_node;
        list->len++;
        return;
    }
    while( *new_node->value > *current->value && current->next != NULL)
        current = current->next;
    if( *new_node->value > *current->value ) {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
        list->len++;
    } else if ( current == list->head ) {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
        list->len++;
    } else if ( current == list->tail && *new_node->value > *current->value ) {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
        list->len++;
    }
    else {
        new_node->next = current;
        new_node->prev = current->prev;
        current->prev->next = new_node;
        current->prev = new_node;
        list->len++;
    }
}

void e1(list_t *list) {
    int pos = 2, i;
    double average, deviation, sum1, sum2;
    node_t *nod,*cpynod;
    list_t *cpylist;
    cpylist = init_list();
    
    nod = list->head;
    for ( i=0; i < list->len; i++) {
        insert_node( cpylist, nod->value, nod->timestamp, i);
        nod = nod->next;
    }
    
    cpynod = cpylist->head->next->next;
    nod = list->head->next->next;
    while ( nod->next->next != NULL) {
        sum1 = 0;
        sum2 = 0;
        node_t *aux;
        aux = cpynod->prev->prev;
        for( i=0; i<5; i++) {
            sum1 = sum1 + *aux->value;
            aux = aux->next;
        }
        average = sum1/5;
        
        aux = cpynod->prev->prev;
        for( i=0; i<5; i++) {
            sum2 = sum2 + (*aux->value - average)*(*aux->value - average);
            aux = aux->next;
        }
        deviation = sqrt( sum2 /5 );
        aux = nod->next;
        if( (*nod->value < average - deviation) || (*nod->value > average + deviation)) {
            remove_node(list, pos);
        }
        else
            pos++;
        nod = aux;
        cpynod = cpynod->next;
    }
    destroy_list(cpylist);
}

void e2( list_t *list) {
    int i;
    node_t *nod,*cpynod,*aux;
    list_t *cpylist;
    cpylist = init_list();
    nod = list->head;
    for ( i=0; i < list->len; i++) {
        insert_node( cpylist, nod->value, nod->timestamp, i);
        nod = nod->next;
    }
    remove_node(list,0);
    remove_node(list,0);
    nod = list->head;
    cpynod = cpylist->head->next->next;
    while ( cpynod->next->next != NULL) {
        list_t *new_list;
        new_list = init_list();
        aux = cpynod->prev->prev;
        for( i=0; i<5; i++) {
            insert_sorted_asc( new_list, *aux->value, *aux->timestamp);
            aux = aux->next;
        }
        aux = new_list->head->next->next;
        *nod->value = *aux->value;
        
        nod = nod->next;
        cpynod = cpynod->next;
        destroy_list(new_list);
    }
    remove_node(list,list->len-2);
    remove_node(list,list->len-1);
    destroy_list(cpylist);
}

void e3(list_t *list) {
    int i;
    node_t *nod,*cpynod,*aux;
    list_t *cpylist;
    cpylist = init_list();
    nod = list->head;
    for ( i=0; i < list->len; i++) {
        insert_node( cpylist, nod->value, nod->timestamp, i);
        nod = nod->next;
    }
    remove_node(list,0);
    remove_node(list,0);
    nod = list->head;
    cpynod = cpylist->head->next->next;
    while ( cpynod->next->next != NULL) {
        double sum = 0;
        list_t *new_list;
        new_list = init_list();
        aux = cpynod->prev->prev;
        for( i=0; i<5; i++) {
            insert_sorted_asc( new_list, *aux->value, *aux->timestamp);
            aux = aux->next;
        }
        
        aux = new_list->head;
        for( i=0; i<5; i++) {
            sum = sum + *aux->value;
            aux = aux->next;
        }
        sum = sum / 5;
        *nod->value = sum;
        nod = nod->next;
        cpynod = cpynod->next;
        destroy_list(new_list);
    }
    remove_node(list,list->len-2);
    remove_node(list,list->len-1);
    destroy_list(cpylist);
}

void u(list_t *list) {
    node_t *nod;
    nod = list->head->next;
    while (nod != NULL) {
        if( ( *nod->timestamp -  *nod->prev->timestamp >= 100 ) &&  ( *nod->timestamp -  *nod->prev->timestamp <= 1000) ) {
            *nod->timestamp = (*nod->timestamp + *nod->prev->timestamp)/2;
            *nod->value = (*nod->value + *nod->prev->value)/2;
        }
        nod = nod->next;
    }
}

void c( list_t *list) {
}

void st( list_t *list, int delta) {
    int inf = 0, sup, nr, ok = 0;
    sup = delta;
    list_t *cpylist;
    cpylist = init_list();
    node_t *nod;
    
    nod = list->head;
    while ( nod != NULL) {
        insert_sorted_asc ( cpylist, *nod->value, *nod->timestamp);
        nod = nod->next;
    }
    
    nod = cpylist->head;
   if( *nod->value < 0 ) {
       while ( inf > *nod->value)
           inf = inf - delta;
       sup = inf + delta;
    }
    
    while ( nod != NULL) {
        nr = 0;
        while( (inf <= *nod->value) && (sup >= *nod->value)) {
            nr++;
            if ( nod == cpylist->tail) {
                ok = 1;
                break;
            }
            nod = nod->next;
        }
        if ( nr != 0)
            printf("[%d, %d] %d\n", inf, sup, nr);
        if ( ok == 1)
           break;
        inf = sup;
        sup = sup + delta;
    }
    destroy_list(cpylist);
}

int main (int argc, const char * argv[]) {
    int n,timestamp,i, ok = 0, delta;
    double value;
    scanf("%d",&n);
    list_t *list;
    list = init_list();
    
    for( i=0; i<n; i++)
    {
        scanf("%d%lf",&timestamp,&value);
        if( list->len == 0 )
        {
            node_t *nod = init_node(&timestamp,&value);
            list->head = nod;
            list->tail = nod;
            list->len++;
        }
        else
        {
            node_t *nod = init_node(&timestamp,&value);
            nod->prev = list->tail;
            list->tail->next = nod;
            list->tail = nod;
            nod->next = NULL;
            list->len++;
        }
    }
    
    for( i = 1; i < argc; i++)
        if( strcmp(argv[i],"--e1") == 0)
            e1(list);
        else if ( strcmp(argv[i],"--e2") == 0)
            e2(list);
        else if ( strcmp(argv[i],"--e3") == 0)
            e3(list);
        else if ( strcmp(argv[i],"--u") == 0)
            u(list);
        else if ( strcmp(argv[i], "--c") == 0)
            c(list);
        else {
            delta = atoi( argv[i] +4);
            st(list,delta);
            ok = 1;
        }
    if ( ok == 0)
        print_list(list);
    destroy_list(list);
    return 0;
}
