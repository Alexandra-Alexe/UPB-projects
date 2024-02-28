#include "functions.h"

int main()
{
	int i, j, u, v, deposit, nr_of_tasks;
	float w;
	char *taskid;
    Graf g;
	// n - nr de noduri, m - nr de arce, d - nr depozite
    scanf("%d%d%d",&g.n,&g.m,&g.d);
    g.matrix = malloc(g.n*sizeof(float*));
    for(i = 0; i < g.n; i++)
        g.matrix[i] = calloc(g.n,sizeof(float)); // toate valorile matricei sunt initial 0
    for(i = 0; i < g.m; i++) 
        {
            scanf("%d%d%f",&u,&v,&w); //se citesc costurile
            g.matrix[u][v] = w;  // pentru fiecare arc, se noteaza in matrice costul acestuia
        }
    for(i = 0; i < g.n; i++)
        g.deposits[i] = 0; //se initializeaza vectorul de depozite cu 0
    
    for(i = 0; i < g.d; i++)
        {
            scanf("%d",&deposit);
            g.deposits[deposit]=1; // se marcheaza cu 1 depozitele existente
        }

    scanf("%d",&nr_of_tasks); // se citeste nr de taskuri
    for(j = 0; j < nr_of_tasks; j++)
    {
        taskid = malloc(4*sizeof(char));
        scanf("%s",taskid);
        if(strcmp(taskid,"e1")==0) // task-ul 1
            {
                int s,k;
                float totaldist=0;
				// s-depozitul in care se incarca marfa, k-nr de magazine aprovizionate
                scanf("%d%d",&s,&k);
                int stores[100];
                for( i = 0; i < k; i++)
                    scanf("%d",&stores[i]); // se citesc nodurile magazinelor ce trb aprovizonate
                for(i = 0; i < k; i++)
                {
                    float d1, d2;//d1 - distanta la dus, d2 - distanta la intors
                    dijkstra(g,s,stores[i],0,&d1);//parametrul 0, indica faptul ca nu se doreste afisarea
                    dijkstra(g,stores[i],s,0,&d2);
                    totaldist+=d1;
                    totaldist+=d2;
                    printf("%d\n",stores[i]);//se afiseaza magazinul
                    printf("%.1f %.1f\n",d1,d2);//se afiseaza cele 2 distante
                    printf("%d",s);//se afiseaza nodul depozitului
                    dijkstra(g,s,stores[i],1,&d1); //paramentrul 1 indica faptul ca se doreste afisarea
                    dijkstra(g,stores[i],s,1,&d2);
                    printf("\n");
                }
                printf("%.1f",totaldist);
                if(j < nr_of_tasks-1)
                    printf("\n");
            }
        if( strcmp(taskid,"e2") == 0 ) // task-ul 2
            plusminus(g);
        free(taskid);
    }
    for(i = 0; i < g.n; i++) //se elibereaza memoria matricei
        free(g.matrix[i]);
    free(g.matrix);
}
