#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    FILE *f, *fp;
    char s[31], sp[101];
    int j = 0, n = 3, m = 0, ok1 = 0, ok2 = 0, ok3 = 0, i;
    //ok1 - titlu, ok2 - continut, ok3 - culoare
    const char cc[4] = "<>=";
    char *token;
    struct site {
        char URL[51], titlu[51], *continut, culoare[101];
        int l, nracc, cksum;
    };
    struct site *v;
    v = (struct site*)malloc(n*sizeof(struct site));
    f = fopen("master.txt","r");
    while(fgets(s,101,f)) {
            s[strlen(s)-1] = '\0';
        //deschid fiserul fiecaruit site
        fp = fopen(s,"r");
        if(fp != NULL) {
            //daca este nevoie,maresc memoria lui v
            if(j/3 == 0 && j > 0) {
                n = n+3;
                v = (struct site*)realloc(v,n*sizeof(struct site));
            }
            //citesc datele de pe fiecare prima linie
            fscanf(fp,"%s%d%d%d",v[j].URL,&v[j].l,&v[j].nracc,&v[j].cksum);
            fgets(sp,101,fp);
            //citesc urmatoarele linii
            while(fgets(sp,101,fp)) {
                           sp[strlen(sp)-1] = '\0';
                //extrag fiecare token
                token = strtok(sp,cc);
                if(token == NULL)
                    break;
                //daca ok-ul corespunzator are valoarea 1, tokenul este copiat
                if(ok1 == 1) {
                    strcpy(v[j].titlu,token);
                    ok1 = 0;
                }
                if(ok2 == 1) {
                    if(m != 0) {
                        m = m+strlen(token);
                        v[j].continut = (char*)malloc(m*sizeof(char));
                    }
                    else {
                        m = m+strlen(token);
                        v[j].continut = (char*)realloc(v[j].continut,m*sizeof(char));
                    }
                    strcpy(v[j].continut,token);
                }
                if(ok3 == 1) {
                    strcpy(v[j].culoare,token);
                    ok2 = 1;
                    ok3 = 0;
                }
                //la intalnirea unui cuvant cheie, ok-ul corespunzator devine 1
                if(strcmp(token,"title") == 0)
                    ok1 = 1;
                if(strcmp(token,"p") == 0)
                    ok2 = 1;
                if(strcmp(token,"p style") == 0)
                    ok3 = 1;
                //reiau aceiasi pasi ca mai sus, pt fiecare token
                        token = strtok(NULL,cc);
                while(token != NULL) {
                    if(strcmp(token,"/p") == 0)
                        ok2 = 0;
                    if(ok1 == 1) {
                        strcpy(v[j].titlu,token);
                        ok1 = 0;
                    }
                    if(ok2 == 1) {
                        if(m != 0) {
                            m = m+strlen(token);
                            v[j].continut = (char*)malloc(m*sizeof(char));
                        }
                        else {
                            m = m+strlen(token);
                            v[j].continut = (char*)realloc(v[j].continut,m*sizeof(char));
                        }
                        strcpy(v[j].continut,token);
                    }
                    if(ok3 == 1) {
                        strcpy(v[j].culoare,token);
                        ok2 = 1;
                        ok3 = 0;
                    }
                    if(strcmp(token,"title") == 0)
                        ok1 = 1;
                    if(strcmp(token,"p") == 0)
                        ok2 = 1;
                    if(strcmp(token,"p style") == 0)
                        ok3 = 1;
                              token = strtok(NULL,cc);
                }
            }
            fclose(fp);
        }
        j++;
    }
    for(i = 0; i < j; i++)
        printf("%s %d %s\n",v[i].URL, v[i].nracc, v[i].titlu);
    fclose(f);
    for(j = 0; j < m; j++)
        free(v[j].continut);
    free(v);
    return 0;
}
