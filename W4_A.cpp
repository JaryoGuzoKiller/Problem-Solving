#include<iostream>
using namespace std;

void getMax_gcd(int a, int b,int x,int y) {
	int max_gcd = a - b;

	if (max_gcd < 0)
		max_gcd = max_gcd * -1;

	int a1=a, a2=a, b1=b, b2=b;
	int x_count = 0, y_count = 0;

	while (1) {
		a1++;
		b1++;
		x_count++;
		if (a1 % max_gcd == 0 && b1 % max_gcd == 0) {
			break;
		}
	}
	if (a2 == 1 || b2 == 1) {
		cout << max_gcd << " " << x * x_count << "\n";
		return;
	}
	while (1) {	
		a2--;
		b2--;
		y_count++;
		if (a2 == 1 || b2 == 1) {
			y_count = 0;
			cout << max_gcd << " " << x * x_count << "\n";
			return;
		}


		if (a2 % max_gcd == 0 && b2 % max_gcd == 0) {
			break;
		}
		
	}
	cout << max_gcd << " ";
	if (x * x_count <= y * y_count)
		cout << x * x_count << "\n";
	else
		cout << y * y_count << "\n";
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	int A, B, x, y;

	cin >> T;
	while (T--) {
		cin >> A >> B >> x >> y;

		getMax_gcd(A, B,x,y);		
	}
}