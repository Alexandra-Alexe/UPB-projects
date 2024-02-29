#include <cstdint>
#include <fstream>
#include <vector>

using namespace std;

int verificare(long *v, long n, long k, long x) {
    long i, feri, suma;
    feri = 1;
    suma = v[0];

    for (i = 1; i < n; i++) {
        // daca o masina are greutatea mai mare ca costul x, nu convine
        if (v[i] > x)
            return 0;
        /* se calculeaza suma greutatilor, iar la fiecare depasire a nr x,
        se incrementeaza feriboturile necesare si se reia suma de la 0 */
        if (suma + v[i] <= x) {
            suma += v[i];
        } else {
            feri ++;
            suma = v[i];
        }
    }
    // daca e necesar un nr mai mare de feriboturi, nu convine
    if (feri > k)
        return 0;
    // altfel succes
    return 1;
}

long CautareBinara(long stg, long dr, long smax, long *v, long n, long k) {
    long mij, smin;
    smin = smax;
    while (stg <= dr) {
        // se alege un cost pt care se face verificarea
        mij = (stg + dr) / 2;
        if (verificare(v, n, k, mij)) {
            // se cauta costul minim deci se micsoreaza intervalul de cautare
            // in caz de succes, se retine aceasta suma minima
            dr = mij - 1;
            smin = mij;
        } else {
            stg = mij + 1;
        }
    }
    return smin;
}

int main() {
    ifstream fin("feribot.in");
    ofstream fout("feribot.out");

    long k, n, i, smax, smin;
    fin >> n >> k;
    long * v = (long*)malloc(n*sizeof(long));
    smax = 0;

    // se citesc si se calculeaza suma tuturor greutatilor
    for (i = 0; i < n; i++) {
        fin >> v[i];
        smax += v[i];
    }
    // se aplica cautarea binara pe intervalul de valori al costurilor
    smin = CautareBinara(1, smax, smax, v, n, k);
    fout << smin << "\n";
    free(v);
    return 0;
}
