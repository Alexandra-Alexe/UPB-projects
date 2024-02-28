#include <stdio.h>
#include <string.h>


int is_anagram(char *s1, char *s2) {
    char a[50], b[50], aux;
    int i, j;
    strcpy(a, s1);//copiez sirul s1 in a si sirul s2 in b
    strcpy(b, s2);//pt ca aceasta functie le modifica
    
    for(i = 0; i < strlen(a)-1; i++)//ordonez alfabetic literele din primul cuv
        for(j = i+1; j < strlen(a); j++)
            if(a[i] > a[j]) {
                aux = a[i];
                a[i] = a[j];
                a[j] = aux;
            }
    
    for(i = 0; i < strlen(b)-1; i++) //ordonez alfabetic literele din al doilea cuv
        for(j = i+1; j < strlen(b); j++)
            if(b[i] > b[j]) {
                aux = b[i];
                b[i] = b[j];
                b[j] = aux;
            }
    
    if(strcmp(a,b) == 0) //daca cuv modificate sunt egale,sunt anagrame
        return 0;
    else
        return -1;
}

double compute_grade(char *s1, char *s2) {
    int i;
    double n, k = 0;
    n = strlen(s1);
    for(i = 0; i < n; i++)
        if(s1[i] != s2[i])
            k++;//in variabila k, numar pe cate pozitii difera caracterele
    return k/n; //returnez gradul anagramei
}

void interschimbare(char *s1,char *s2) {
    char aux[50];
    strcpy(aux, s1);
    strcpy(s1, s2);
    strcpy(s2, aux);
}

int main() {
    int N, i, j, imax = 0;
    double v[1000], gmax = -2;
    char cuv1[1000][50], cuv2[1000][50];
    scanf("%d",&N);
    for(i = 0; i < N; i++)
        scanf("%s%s",cuv1[i],cuv2[i]);//in cuv1[i] si cuv2[i] se retine primul si al doilea cuvant al perechii i
    
    for(i = 0; i < N-1; i++)//ordonez descrescator toate perechile
        for(j = i+1; j < N; j++)
            if(strcmp(cuv1[i], cuv1[j])<0) { //ordonare in functie de primul cuvant
                interschimbare(cuv1[i], cuv1[j]);
                interschimbare(cuv2[i], cuv2[j]);
            }
    
    for(i = 0; i < N; i++) { //asociez fiecarei perechi gradul sau
        v[i] = is_anagram(cuv1[i], cuv2[i]); //daca cuvintele nu sunt anagrame, gradul va fi -1
        if(v[i] == 0)
            v[i] = compute_grade(cuv1[i], cuv2[i]);//daca cuv sunt anagrame,functia compute_grade recalculeaza gradul
    }
    
    for(j = 0; j < N; j++) {
        for(i = 0; i < N; i++)
            if(v[i] > gmax && v[i] <= 1) {
                gmax = v[i];//retin in gmax gradul maxim
                imax = i;//retin in imax pozitia gradului maxim
            }
        printf("%s %s %lf\n", cuv1[imax], cuv2[imax], v[imax]); //afisez perechea cu gradul maxim
        v[imax] = 3; //modific gradul perechii afisate pt a nu afecta urmatoarele parcurgeri
        gmax = -2;//reinitializez gmax cu o valoare mica pt urmatoarea parcurgere
    }
    
    return 0;
}
