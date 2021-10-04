#include<iostream>
using namespace std;
void Hz() {
	int n, x, cnt = 0;
	int list[5000];
	bool flag;

	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> x;
		list[i] = x;
	}

	for (int i = 1; i < n; i++) {
		flag = true;
		for (int j = 0; j < n - i; j++) {
			if (list[j] != list[j + i]) {
				flag = false;

				if (i == n - 1)
					cnt++;
			}
		}
		cnt++;
		
		if (flag) {
			break;
		}
	}
	for (int i = 0; i < cnt; i++) {
		cout << list[i] << " ";
	}
	cout << "\n";
}
int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		Hz();
	}
}
