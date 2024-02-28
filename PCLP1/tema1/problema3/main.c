#include <stdio.h>
#include <string.h>

void dec_to_bin (int n, char *s) {
    int i=0,j;
    char cs[9];//sirul s scris de la dreapta la stanga
    while (n > 0)// memorez resturile impartirii in ordinea naturala (st la dr)
    {
        cs[i] = n%2;
        n = n/2;
        i++;
    }
    i=8-strlen(cs);
    for (j = strlen(cs)-1; j>=0; j--) //adaug resturile memorata in cs, in ordinea corecta
        s[i++]=cs[j];
}

int main()
{
    int i,j,x;
    char s[9][9];
    for (i = 0; i < 8; i++)
    {
        scanf("%d",&x);
        dec_to_bin(x,s[i]);
    }
    for(i=0;i<8;i++) {
        for(j=0;j<8;j++)
            printf("%c ",s[i][j]);
        printf("\n");
    }
    return 0;
}
