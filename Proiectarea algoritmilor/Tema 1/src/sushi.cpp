#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int task1(long n, long m, long x, vector <long>& p,
								vector <vector <long> >& g) {
	long i, lei, aux, sol_aux, j;
	// suma maxima de bani
	long max = x * n;
    vector<long> last_line(max + 1, 0);
	vector<long> current_line(max + 1, 0);
	vector<long> sum_pref(m, 0);

	// se calculeaza sumele preferintelor prietenilor
	for (i = 0; i < m; i++) {
		aux = 0;
		for(j = 0; j < n; j++) {
			aux += g[j][i];
		}
		sum_pref[i] = aux;
	}
    for (i = 0; i < m; i++) {
        for (lei = 1; lei <= max; lei++) {
			// daca pretul platoului curent e prea mare, nu-l cumparam
			if (lei < p[i]) {
				current_line[lei] = last_line[lei];
			}
			/* altfel il cumparam si de restul banilor luam platourile 
			la care ne hotarasem la pasul anterior */
            if (lei - p[i] >= 0) {
                sol_aux = last_line[lei - p[i]] + sum_pref[i];
				/* alegem suma maxima a notelor dintre posibilitatea de
				a nu cumpara un platou curent si posibilitatea de a
				cumpara unul */
                current_line[lei] = std::max(last_line[lei], sol_aux);
            }
        }
		// linia anterioara devine linia curenta
		std::copy(current_line.begin(), current_line.end(),
													last_line.begin());
	}
	return current_line[max];
}

// similiar taskului 1, voi comenta modificarile aduse
int task2(long n, long m, long x, vector <long> &p,
								vector <vector <long> > &g) {
	/* este necesara inca o variabila sol_aux pt ca intervine
	cazul in care cumparam 2 platouri de acelasi tip */
	long i, lei, aux, sol_aux1, sol_aux2, j;
	long max = x * n;
    vector<long> last_line(max + 1, 0);
	vector<long> current_line(max + 1, 0);
	vector<long> sum_pref(m, 0);

	for (i = 0; i < m; i++) {
		aux = 0;
		for(j = 0; j < n; j++) {
			aux += g[j][i];
		}
		sum_pref[i] = aux;
	}
    for (i = 0; i < m; i++) {
        for (lei = 1; lei <= max; lei++) {
			if (lei - p[i] < 0) {
				current_line[lei] = last_line[lei];
			}
            if (lei - p[i] >= 0) {
                sol_aux1 = last_line[lei - p[i]] + sum_pref[i];

				// cazul in care putem cumpara 2 platouri de acelasi tip
				if((lei - p[i])/p[i] >= 1) {
					sol_aux2 = last_line[lei - p[i] * 2] + 2 * sum_pref[i];
				} else {
					sol_aux2 = 0;
				}
				// alegem maximul dintre cele 3 posibilitati de cumparare
                current_line[lei] = std::max(last_line[lei], sol_aux1);
				current_line[lei] = std::max(current_line[lei], sol_aux2);
            }
        }
		std::copy(current_line.begin(), current_line.end(), last_line.begin());
	}
	return current_line[max];
}

// similar taskului 2
int task3(long n, long m, int x, vector <long> &p, vector <vector <long> > &g) {
	long i, j, lei, aux, sol_aux1 = 0, sol_aux2 = 0;
	long max = x * n;
    vector<vector<long>> last_line(max + 1, vector<long>(n + 1, 0));
	vector<vector<long>> current_line(max + 1, vector<long>(n + 1, 0));
	vector<long> sum_pref(m + 1, 0);

	for (i = 0; i < m; i++) {
		aux = 0;
		for(j = 0; j < n; j++) {
			aux += g[j][i];
		}
		sum_pref[i + 1] = aux;
	}

    for (i = 1; i <= m; i++) {
		for (lei = 1; lei <= max; lei++) {
			// la fiecare iteratie se limiteaza nr total de platouri
			for (j = 1; j <= n; j++) {
				if (lei - p[i - 1] < 0) {
					current_line[lei][j] = last_line[lei][j];
				} else {
					if (lei - p[i - 1] >= 0) {
						sol_aux1 = last_line[lei - p[i - 1]][j - 1] + sum_pref[i];
					} else {
						sol_aux1 = 0;
					}
					// pt a cumpara 2 platouri trb ca limita sa mi permita asta (j > 1)
					if (lei - p[i - 1] * 2 >= 0  && j > 1) {
						sol_aux2 = last_line[lei - p[i - 1] * 2][j - 2] + 2 * sum_pref[i];
					} else {
						sol_aux2 = 0;
					}
					current_line[lei][j] = std::max(last_line[lei][j], sol_aux1);
					current_line[lei][j] = std::max(current_line[lei][j], sol_aux2);
				}
			}
		}
		std::copy(current_line.begin(), current_line.end(), last_line.begin());
	}
	return current_line[max][n];
}

int main() {
	freopen("sushi.in", "r", stdin);
	freopen("sushi.out", "w", stdout);

	int task;  // task number

	long n;  // number of friends
	long m;  // number of sushi types
	long x;  // how much each of you is willing to spend

	vector <long> prices;  // prices of each sushi type
	// the grades you and your friends gave to each sushi type
	vector <vector <long> > grades;

	cin >> task;
	cin >> n >> m >> x;

	prices.assign(m, 0);
	grades.assign(n, vector <long> (m, 0));

	// price of each sushi
	for(int i = 0; i < m; ++i) {
		cin >> prices[i];
	}

	// each friends rankings of sushi types
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			cin >> grades[i][j];
		}
	}

	int ans = -1;

	switch(task) {
		case 1:
			ans = task1(n, m, x, prices, grades);
			break;
		case 2:
			ans = task2(n, m, x, prices, grades);
			break;
		case 3:
			ans = task3(n, m, x, prices, grades);
			break;
		default:
			cout << "wrong task number" << endl;
	}

	cout << ans << endl;
	return 0;
}
