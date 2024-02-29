#include <cstdint>
#include <fstream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

void tarjanDFS(int node, vector<vector<int>>& graph, vector<int>& index,
                vector<int>& lowLink, vector<bool>& onStack, stack<int>& s,
                                    vector<vector<int>>& components, int& id) {
    /*  in parcurgere, fiecare nod primeste un id, o valoare de low link si
    se adauga pe stiva, marcandu-se acest lucru in vectorul onStack  */
    static int currentId = 0;
    index[node] = ++currentId;
    lowLink[node] = currentId;
    s.push(node);
    onStack[node] = true;

    for (int neighbor : graph[node]) {
        // pentru fiecare vecin parcurs, se aplica acest dfs
        if (index[neighbor] == 0) {
            tarjanDFS(neighbor, graph, index, lowLink, onStack, s, components,
                                                                            id);
            /*  la intoarcerea din apel, valoarea de low link va fi minimul low 
            linkul curent si low link ul vecinului  */
            lowLink[node] = min(lowLink[node], lowLink[neighbor]);
        } else if (onStack[neighbor]) {
            // cazul in care se gaseste un ciclu si low linkul trb sa fie minim
            lowLink[node] = min(lowLink[node], index[neighbor]);
        }
    }

    /*  conditia pentru a detecta ca toate nodurile puse in stiva la acest moment,
    formeaza o comp tare conexa  este sa ajung la nodul cu indicele care mi-a dat
    acel low link minim  */
    if (index[node] == lowLink[node]) {
        // pun toate nodurile din stiva in acea componenta
        components.push_back(vector<int>());
        while (true) {
            int top = s.top();
            s.pop();
            onStack[top] = false;
            components[id].push_back(top);

            if (top == node) {
                break;
            }
        }
        id++;
    }
}

vector<vector<int>> tarjan(vector<vector<int>>& graph, int n) {
    /*  sunt necesare o stiva, un vector care retine daca un nod a fost sau nu
    pus pe stiva, un vector pt indici si unul pentru valoarea lowLink si un vector
    de vectori, components, in care se grupeaza nodurile pe componente tari conexe  */
    vector<int> index(n, 0);
    vector<int> lowLink(n, 0);
    vector<bool> onStack(n, false);
    stack<int> s;
    vector<vector<int>> components;
    int id = 0, i;

    /*  se ia fiecare nod vechi si daca nu a fost parcurs, se realizeaza o parcurge DFS 
    pentru a-l adauga intr-o componenta tare conexa  */
    for (i = 0; i < n; i++) {
        if (index[i] == 0) {
            tarjanDFS(i, graph, index, lowLink, onStack, s, components, id);
        }
    }

    return components;
}

vector<vector<int>> buildNewGraph(vector<vector<int>>& graph,
                                    vector<vector<int>>& components) {
    int i, neighborComp;
    int n = components.size();
    vector<vector<int>> newGraph(n);

    /*  in map realizez o mapare între un nod initial și componenta tare 
    conexă a lui  */
    unordered_map<int, int> map;
    for (i = 0; i < n; i++) {
        for (int node : components[i]) {
            map[node] = i;
        }
    }

    // parcurg fiecare comp tare conexa
    for (i = 0; i < n; i++) {
        // parcurg fiecare nod al componentei
        for (int node : components[i]) {
            // parcurg fiecare vecin al nodului
            for (int neighbor : graph[node]) {
                /*  extrag componenta vecinului, si daca e diferita de componenta curenta si
                daca acesta muchie noua nu a mai fost adugata, o adaug in graful nou  */
                neighborComp = map[neighbor];
                if (neighborComp != i) {
                    if (find(newGraph[i].begin(), newGraph[i].end(),
                                    neighborComp) == newGraph[i].end()) {
                        newGraph[i].push_back(neighborComp);
                    }
                }
            }
        }
    }
    return newGraph;
}


int main() {
    ifstream fin("ferate.in");
    ofstream fout("ferate.out");

    int n, m, i, src, dest, s;
    fin >> n >> m >> s;

    // retin grafului sub forma unei liste de adiacenta
    vector<vector<int>> graph(n);
    for (i = 0; i < m; i++) {
        fin >> src >> dest;
        graph[src - 1].push_back(dest - 1);
    }

    // aplic algoritmul lui Tarjan pentru a afla comp tari conexe
    vector<vector<int>> components = tarjan(graph, n);

    // construiesc un nou graf, in care consider o comp tare conexa - un nod
    vector<vector<int>> newGraph = buildNewGraph(graph, components);

    // retin in x indexul componentei tari conexe care contine nodul s
    int x = -1;
    for (i = 0; i < components.size(); i++) {
        if (find(components[i].begin(), components[i].end(), s - 1) !=
                                                    components[i].end()) {
            x = i;
            break;
        }
    }

    // retin in vectorul inDegree gradele interne ale nodurilor din graful nou
    vector<int> inDegrees(newGraph.size(), 0);

    /*  retin in rezultat, nr de noduri cu grad intern 0, exceptand
    nodul cu depozitul  */
    int res = 0;
    for (i = 0; i < newGraph.size(); i++) {
        for (int j : newGraph[i]) {
            inDegrees[j]++;
        }
    }

    for (i = 0; i < newGraph.size(); i++) {
        if (inDegrees[i] == 0 && i != x) {
            res++;
        }
    }

    fout << res;
    return 0;
}
