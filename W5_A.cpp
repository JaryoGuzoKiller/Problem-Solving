#include<iostream>
#include<vector>
using namespace std;

void findCycle() {
	int n;
	cin >> n;
	int* x = new int[n];
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		x[i] = k;
	}

	for (int i = 1; i < n; i++) {
		int* check = new int[i];
		for (int j = 0; j < i; j++) {
			check[j] = x[j];
		}

		for (int j = 0; j < n; j++) {
			if (x[j] != check[j % i]) break;
			if (j == n - 1) {
				for (int k = 0; k < i; k++) {
					cout << check[k] << " ";
				}
				cout << "\n";
				return;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		cout << x[i] << " ";
	}
	cout << "\n";
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;
	while (T--) {
		findCycle();
	}
}