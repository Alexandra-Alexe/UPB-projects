#include <fstream>
#include <algorithm>
#include <climits>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

int64_t SolveTask1(long* a, long* b, int n) {
    int i;
    int64_t sum = 0;
    // sortez vectorul a crescator si b descrescator
    std::sort(a, a + n);
    std::sort(b, b + n, [](long x, long y) { return x > y; });

    // aleg maximul din pereche de nr
    for (i = 0; i < n; i++) {
        if (a[i] > b[i])
            sum += (int64_t)a[i];
        else
            sum += (int64_t)b[i];
    }
    return sum;
}

int64_t SolveTask2(long* a, long* b, int moves, int n) {
    std::priority_queue<long, std::vector<long>, std::greater<long>> v_max_pq;
    std::priority_queue<long> v_min_pq;
    int64_t sum = 0;
    int i;
    long max_elem, min_elem;
    std::vector<long>::iterator it;

    for (i = 0; i < n; i++) {
        /* maximul din fiecare pereche se adauga in coada de prioritati pt nr maxime,
        similar pentru minim */
        max_elem = std::max(a[i], b[i]);
        min_elem = std::min(a[i], b[i]);
        v_max_pq.push(max_elem);
        v_min_pq.push(min_elem);

        // se calculeaza suma maximelor in forma initiala a listelor
        sum += (uint64_t)max_elem;
    }

    /* se modifica suma, datorita mutarilor inlocuind 
    nr minime din v_max_pq cu nr maxime din v_min_pq */
    for (i = 0; i < moves; i++) {
        if (v_min_pq.top() > v_max_pq.top())
            sum = (uint64_t)(sum - v_max_pq.top() + v_min_pq.top());
        v_min_pq.pop();
        v_max_pq.pop();
    }
    return sum;
}

int main() {
    ifstream fin("nostory.in");
    ofstream fout("nostory.out");

    int task, i;
    int64_t rez;
    long* a;
    long* b;
    fin >> task;

    int n, moves;
    if (task == 1) {
        fin >> n;
        a = (long*)malloc(n * sizeof(long));
        b = (long*)malloc(n * sizeof(long));
        for (i = 0; i < n; i++)
            fin >> a[i];
        for (i = 0; i < n; i++)
            fin >> b[i];
    } else {
        fin >> n >> moves;
        a = (long*)malloc(n * sizeof(long));
        b = (long*)malloc(n * sizeof(long));
        for (i = 0; i < n; i++)
            fin >> a[i];
        for (i = 0; i < n; i++)
            fin >> b[i];
    }

    if (task == 1)
        rez = SolveTask1(a, b, n);
    else
        rez = SolveTask2(a, b, moves, n);

    fout << rez << "\n";
    return 0;
}
