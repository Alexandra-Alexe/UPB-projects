#include "functions.h"

int mindistancenode(Graf g,float dist[],int viz[])
{
    int i;
    int min = 999;
    int minnode;
    for(i = 0; i < g.n; i++)
        if(viz[i] == 0 && dist[i] <= min)//se parcurg nodurile
            {
                min = dist[i];//pt a-l afla pe cel cu drumul cel mai scurt
                minnode = i;
            }
    return minnode;
}

void printPath(int parent[], int source, int destination)
{
    if( parent[destination] == -1 )//daca nodul destination nu areun nod parinte, return
        return;
    printPath(parent, source, parent[destination]); //apel recursiv pt acceasi sursa si nodul parinte al nodului destination
    if(destination != source) 
        printf(" %d",destination); 
}

void dijkstra(Graf g, int source, int destination, int path, float *dist)
{
    int i, j, u;
    float distance[100];
    int viz[100];
    int parent[100];
    for(i = 0; i < g.n; i++)
    {
        distance[i] = 999;//toate distantele au initial o valoarea ft mare
        viz[i] = 0;//nodurile nevizitate sunt marcate cu 0 
        parent[i] = -1;
    }
    distance[source] = 0; //distanta minima se afla pe nodul depozit
    for(i = 0; i < g.n - 1; i++)
    {
        u = mindistancenode(g, distance, viz);// u retine nodul nevizitat cu distanta minima
        viz[u] = 1;
        for(j = 0; j < g.n; j++)
            if(viz[j] == 0 && g.matrix[u][j] != 0)//daca nodul n-a fost vizitat & exista arc catre el
                if(g.matrix[u][j] + distance[u] < distance[j]) //daca lungimea drumul e mai mica ca cea initiala
                    {
                        distance[j] = g.matrix[u][j] + distance[u];//distanta e modificata cu valoarea reala
                        parent[j] = u;//se retin nodurile parcurse pentru afisare
                    }
    }
    *dist = distance[destination]; //distanta finala sursa-destinatie se afla pe pozitia destination din vector
    if(path == 1) // path e un parametru care indica daca se doreste afisarea
        printPath(parent,source,destination);
}

void recursive(Graf g,int node,int *viz,int reverse)
{
    viz[node] = 1;//se marcheaza cu 1 nodul de inceput
    int i;
    for(i = 0; i < g.n; i++)
        if(reverse == 0)//daca reverse e 0, parcurgerea e normala
            {
				//daca nodul nu e vizitat, este arc catre el si nu e depozit
                if(viz[i] == 0 && g.matrix[node][i] != 0 && g.deposits[i] == 0) 
                    recursive(g,i,viz,reverse);// se face apel recursiv pentru acesta 
            }
        else //altfel parcurgerea se face in mod invers
            if(viz[i] == 0 && g.matrix[i][node] != 0 && g.deposits[i] == 0)
                    recursive(g,i,viz,reverse);
}

void plusminus(Graf g)
{
    int nrcomponents = 0;//variabila care retine nr de componente tari conexe
	//vectorii plus si minus vor ajuta la parcurgerea normala si inversa a nodurilor
    int component[100], viz[100], plus[100], minus[100];
    int i,j;
    for(i = 0; i < g.n; i++)
        component[i] = 0;//initial vectorul are toate valorile 0
	for ( i = 0; i < g.n; i++)
		viz[i] = 0;
    for(i = 0; i < g.n; i++)
        if(component[i] == 0 && g.deposits[i] == 0) 
        {
            for(j = 0; j < g.n; j++) //pentru fiecare nod, vectorii de parcurgeri sunt initial nuli
                plus[j] = minus[j] = 0;
            nrcomponents++;
            recursive(g,i,plus,0);
            recursive(g,i,minus,1);
            for(j = 0; j < g.n; j++)
				//daca nodul a fost marcat in ambele parcurgeri si nu e depozit
                if(plus[j] == 1 && minus[j] == 1 && g.deposits[j] == 0) 
                    component[j] = i; // se marcheaza faptul ca nodul j face parte din componenta i
        }
    printf("%d\n",nrcomponents);//se afiseaza numarul de componente tari conexe

	for ( i = 0; i < g.n; i++)
		viz[i] = 0; //vectorul de noduri vizitate pleca din nou de la 0
    for(i = 0; i < g.n; i++) //afisarea componentelor
            if(viz[i] == 0 && g.deposits[i] == 0) 
                {
                    printf("%d",i);
                    viz[i] = 1; //dupa afisare se marcheaza nodul cu 1
                    for(j = 0; j < g.n; j++)
						//toate nodurile ce fac parte din aceeasi componenta
                        if(component[j] == component[i] && viz[j] == 0) 
                            {
                                printf(" %d",j); //se afiseaza
                                viz[j] = 1; //si se marcheaza cu 1
                            }
                    if(nrcomponents > 1)
                        printf("\n");
                    nrcomponents--;
                }
}
