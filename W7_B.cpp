#include<iostream>
#include<queue>
#include<cmath>
using namespace std;
int T, M, N, K, x, y;
struct point {
	int x, y;
	double dist;
	point(int x, int y, double dist) {
		this->x = x;
		this->y = y;
		this->dist = dist;
	}
	bool operator<(const point a)const {
		if (this->dist == a.dist) {
			if (this->x == a.x) {
				return a.y > this->y;
			}
			return a.x > this->x;
		}
		return a.dist > this->dist;
	}
};
int main() {
	cin >> T;
	while (T--) {
		cin >> M >> N >> K;
		priority_queue<point> stores;

		for (int i = 1; i <= M; i++) {
			cin >> x >> y;
			stores.push(point(x, y, sqrt(x * x + y * y)));
			if (stores.size() > K)
				stores.pop();
		}
		for (int i = 1; i<= N; i++) {
			cin >> x >> y;
			stores.push(point(x, y, sqrt(x * x + y * y)));
			stores.pop();
			cout << stores.top().x << " " << stores.top().y << "\n";
		}
	}
}
