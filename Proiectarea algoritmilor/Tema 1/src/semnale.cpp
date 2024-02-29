#include <iostream>
#include <vector>

using namespace std;

const int mod = 1000000007;

long long type1(long long x, long long y) {
	/* construiesc o "matrice" in care valorile reprezintă
	nr de semnale posibile pentru x de 0 și y de 1 */
    long long i, j;
	// initial au toate valorile 0
    vector<long long> last_line(y + 1, 0);
	vector<long long> current_line(y + 1, 0);
	/* initializez manual prima linie si prima coloana
	consider ca exista semnalul din 0 biti 0 si 0 biti 1 */
    last_line[0] = 1;
	// cu 0 biti de 0 si 1 bit de 1 -> 1 semnal
    last_line[1] = 1;
	// cu 1 bit de 0 si 0 biti de 1 -> 1 semnal
    current_line[0] = 1;

	// construiesc "matricea" pe baza relatiei de recurenta gasite (readme)
    for (i = 1; i <= x; i++) {
        for (j = 1; j <= y; j++) {
			current_line[j] = (last_line[j] % 1000000007  +
									last_line[j-1] % 1000000007) % 1000000007;
        }
		// linia curenta devine linia veche, pt continuitatea parcurgerii
		std::copy(current_line.begin(), current_line.end(), last_line.begin());
	}
	return current_line[y];
}

long long type2(long long x, long long y) {
	long long i, j;
    vector<long long> last_line(y + 1, 0);
	vector<long long> current_line(y + 1, 0);
	// consider ca exista semnalul din 0 biti 0 si 0 biti 1
    last_line[0] = 1;
	// cu 0 biti de 0 si 1 bit de 1 -> 1 semnal
    last_line[1] = 1;
	// cu 0 biti de 0 si 2 biti de 1 -> 1 semnal
	last_line[2] = 1;
	// cu 1 bit de 0 si 0 biti de 1 -> 1 semnal
    current_line[0] = 1;

	/* recurenta se bazeaza de regula pe suma a 3 nr precendete pe linie,
	deci pt crearea coloanei 2 se ia cazul separat */
    for (i = 1; i <= x; i++) {
        for (j = 1; j <= y; j++) {
            if (j == 1) {
                current_line[j] = (last_line[j] % 1000000007  +
								last_line[j-1] % 1000000007) % 1000000007;
            } else {
			    current_line[j] = (last_line[j] % 1000000007  +
					last_line[j-1] % 1000000007  + last_line[j-2] % 1000000007) % 1000000007;
            }
        }
		std::copy(current_line.begin(), current_line.end(), last_line.begin());
	}
	return current_line[y];
}

int main() {
    freopen("semnale.in", "r", stdin);
	freopen("semnale.out", "w", stdout);

	long long sig_type, x, y;

	cin >> sig_type >> x >> y;

    switch (sig_type) {
		case 1:
			cout << type1(x, y);;
			break;
		case 2:
			cout << type2(x, y);
			break;
		default:
			cout << "wrong task number" << endl;
	}

    return 0;
}
