#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <fstream>

using namespace std;

int calculate(vector<vector<int>>& graph, vector<int>& inDegree,
                                            vector<int>& dataSet, int n) {
    int switches = 0;
    int i, u, add;
    /*  se foloseste o coada pentru a parcugere toate nodurile
    tinand cont de dependente  */
    queue<int> q;
    /*  se foloseste un vector dp pentru a retine lungimea maximă de la nodul de start la fiecare nod,
    astfel încât fiecare nod are un set diferit de date față de predecesorul său */
    vector<int> dp(n, 0);

    // se pun in coada nodurile cu gradele interne 0
    for (i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        u = q.front();
        q.pop();
        for (int neighbor : graph[u]) {
            // se decrementeaza gradul intern si daca e nul, push
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }

            // daca e nevoie de seturi diferite de date, se considera +1
            if ((dataSet[u] != dataSet[neighbor])) {
                add = 1;
            } else {
                add = 0;
            }
            /*  se ia maximul dintre nr curent si nr de context switch uri prin
            drumul curent  */
            dp[neighbor] = max(dp[neighbor], dp[u] + add);
        }
    }

    for (i = 0; i < n; i++) {
        switches = max(switches, dp[i]);
    }
    return switches;
}

int main() {
    ifstream fin("supercomputer.in");
    ofstream fout("supercomputer.out");
    int n, m, i, src, dest;
    fin >> n >> m;

    // reprezentarea grafului prin liste de adiacenta
    vector<vector<int>> graph(n);
    // vector ce retine gradele interne, initial 0
    vector<int> inDegree(n, 0);
    //  vector ce retine setul de date cerut de fiecare task(nod)
    vector<int> dataSet(n, 0);

    for (i = 0; i < n; i++) {
        fin >> dataSet[i];
    }

    for (i = 0; i < m; i++) {
        fin >> src >> dest;
        graph[src - 1].push_back(dest - 1);
        inDegree[dest - 1]++;
    }

    // se calculeaza numarul minim de switch uri si se afiseaza
    int switches = calculate(graph, inDegree, dataSet, n);
    fout << switches;
    return 0;
}
