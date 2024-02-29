#include <cstdint>
#include <fstream>
#include <vector>

using namespace std;

void dfs(int current, int& exp, vector<vector<int>>& graph,
                            vector<bool>& visited, int& result) {
    int i, neighbor;

    /*  daca numarul de expedieri s-a terminat, intorc depozitul la care 
    s-a ajuns  */
    if (exp == 0) {
        result = current;
        return;
    }

    // vizitez nodul curent
    visited[current] = true;

    /*  pt fiecare vecin nevizitat al nodului curent, decrementez nr de
    expedieri si realizez parcurgerea in adancime prin reapelarea functiei dfs*/
    for (i = 0; i < graph[current].size(); i++) {
        neighbor = graph[current][i];
        if (!visited[neighbor]) {
            exp --;
            dfs(neighbor, exp, graph, visited, result);
        }
    }
}

int main() {
    ifstream fin("magazin.in");
    ofstream fout("magazin.out");

    int n, q, x, i, exp, rezultat;

    // citesc datele de intrare si construiesc graful
    fin >> n >> q;
    vector<vector<int>> graph(n);
    vector<vector<int>> perechi(q, vector<int>(2));
    vector<bool> visited(n, false);

    for (i = 2; i <= n; i++) {
        fin >> x;
        graph[x - 1].push_back(i - 1);
    }

    // retin intrebarile in perechi(nod start, nr expedieri)
    for (i = 0; i < q; i++) {
        fin >> x >> exp;
        perechi[i][0] = x - 1;
        perechi[i][1] = exp;
    }

    /*  pt fiecare intrebare, consider toate nodurile nevizitate, aplic dfs
    si afisez rezultatul tinand cont de faptul ca am lucrat cu indici de la 0
    in cadrul grafului  */
    for (i = 0; i < q; i++) {
        vector<bool> visited(n, false);
        int exp = perechi[i][1];
        int result = -1;

        dfs(perechi[i][0], exp, graph, visited, result);
        if (result == -1) {
            fout << result << endl;
        } else {
            fout << result  + 1 << endl;
        }
    }

    return 0;
}
