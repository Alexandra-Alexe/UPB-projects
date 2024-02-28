#include <stdio.h>

int nr_perechi(int N, int a[1000][2]) {
    int i, j, nr = 0;
    for(i = 0; i < N-1; i++)//iau perechile de coord 2 cate 2 din matricea a si verific daca suma sau diferenta lor e egala
        for(j = i+1; j < N; j++)//suma(diferenta) lor e egala => nebunii se afla pe aceeasi diagonala secundara (principala)
            if((a[i][0]+a[i][1]) == (a[j][0]+a[j][1]) || (a[i][0]-a[i][1]) == (a[j][0]-a[j][1]) )
                nr++;// numar in variabila nr, perechile de nebuni care se ataca
    printf("%d\n",nr);
    return nr;
}

int verificare(int N,int nr,int M,int a[1000][2]) {
    int i, j, p, b[1000][1000], r, d, s;
    
    if(nr != 1) {//afisez "NU" daca nu exista exact o pereche de nebuni care se ataca
        printf("NU\n");
        return 0;
    }
    
    for(i = 0; i < N-1; i++) //parcurg din nou matricea de coordonate
        for(j = i+1; j < N; j++)
            if((a[i][0]+a[i][1]) == (a[j][0]+a[j][1]) || (a[i][0]+a[i][1]) == (a[j][0]+a[j][1]))
                p = j;//retin in p indicele care-mi indica coordonatele nebunului pe care vreau sa-l mut
    
    for(i = 0; i < M; i++)
        for(j = 0; j < M; j++)
            b[i][j] = 0;//construiesc o matrice-tabla de sah si initializez toate valorile cu 0
    
    for(i = 0; i < N; i++)//pt fiecare pereche de coordonate din matricea a
        if(i != p) {//cu exceptia coordonatelor nebunului pe care vreau sa-l mut
            d = a[i][0]-a[i][1];//calculez suma si diferenta
            s = a[i][0]+a[i][1];
            for(j = 0; j < M; j++)//parcurg tabla de sah element cu element
                for(r = 0; r < M; r++)
                    if(((j-r) == d) || ((j+r) == s))//iar pozitiile care verifica una dintre relatii sunt marcate cu 1
                        b[j][r] = 1;//astfel exclud posibilitatea acelei mutari
        }
    
    for(i = 0; i < M; i++) {
        for(j = 0; j < M; j++)
            printf("%d ",b[i][j]);
        printf("\n");
    }
    
    for(i = 0; i < M; i++)
        for(j = 0; j < M; j++)
            if(b[i][j] == 0) {//daca in final mai exista o casuta libera nemarcata cu 1
                printf("DA\n");//nebunul exclus poate fi mutat
                return 0;
            }
    printf("NU\n");//altfel "NU"
    return 0;
}

int main() {
    int M, N, i, j, nr;
    scanf("%d%d",&M,&N);
    int a[1000][2];
    for(i = 0; i < N; i++)
        for(j = 0; j < 2; j++)
            scanf("%d",&a[i][j]);//citesc coordonatele nebunilor in matricea a
    nr=nr_perechi(N,a);//aflu nr de perechi de nebuni care se ataca reciproc
    verificare(N,nr,M,a);//verific daca se poate face mutarea
}
