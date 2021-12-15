#include<iostream>
using namespace std;
int T;
long long X, N, M;
pair <long long,long long> geoSeries(long long x, long long n) {
	pair<long long, long long> temp;
	if (n == 1) {
		temp.first = x % M;
		temp.second = x % M;
		return  temp;
	}
	pair<long long, long long>half = geoSeries(x, n / 2);
	long long exp = half.first;
	long long sum = half.second;
	if (n % 2 == 0) {
		temp.first = (exp * exp) % M;
		temp.second = ((1 + exp) * sum) % M;
		return temp;
	}
	else {
		temp.first = (x * exp * exp) % M;
		temp.second = (x + x * (1 + exp) * sum) % M;
		return temp;
	}
}
int main() {
	cin >> T;
	while (T--) {
		cin >> X >> N >> M;
		pair<long long, long long>answer = geoSeries(X, N);
		cout << answer.second << "\n";
	}
}