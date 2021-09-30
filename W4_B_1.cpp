#include<iostream>
using namespace std;
struct pii {
	int x, y;
};
int CCW(pii a, pii b, pii c) {
	return  (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
void swap(int a, int b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;
	while (T--) {
		int x1, y1, x2, y2;
		int x3, y3, x4, y4;
		cin >> x1 >> y1 >> x2 >> y2;

		pii a, b;
		a.x = x1;
		a.y = y1;
		b.x = x2;
		b.y = y2;

		cin >> x3 >> y3 >> x4 >> y4;

		pii c, d;
		c.x = x3;
		c.y = y3;
		d.x = x4;
		d.y = y4;

		if (CCW(a, b, c) * CCW(a, b, d) > 0) { //교차 가능성이 없음
			cout << "1" << "\n"; //두 선분이 서로 겹치지 않음
			//a---b
			//c---d
		}
		else if (CCW(a, b, c) * CCW(a, b, d) <= 0) { // 두 선분이 교차 가능성이 있음
			if (CCW(c, d, a) * CCW(c, d, b) <= 0) { //실제로 교차 함
				if (CCW(a, b, c) * CCW(a, b, d) == 0 && CCW(c, d, a) * CCW(c, d, b) == 0) {
					//한 줄에 평행하는 경우
					int temp;
					if (a.x > b.x) {
						temp = a.x;
						a.x = b.x;
						b.x = temp;
					}
					if (c.x > d.x) {
						temp = c.x;
						c.x = d.x;
						d.x = temp;
					}
					if (a.y > b.y) {
						temp = a.x;
						a.y = b.y;
						b.y = temp;
					}
					if (c.y > d.y) {
						temp = c.y;
						c.y = d.y;
						d.y = temp;
					}
					//A<B, C<D 인 상태로 만듬

					if ((a.x < c.x && c.x < b.x&&b.x<d.x) || (a.y < c.y && c.y < b.y && b.y < d.y)
						|| (c.x < a.x && a.x <d.x && d.x < b.x) || (c.y < a.y && a.y < d.y && d.y < b.y))
						cout << "3" << "\n";
					//a---c---b---d
					else if ((a.x <= c.x && d.x < b.x) || (a.x < c.x && d.x <= b.x)
						||(a.y < c.y && b.y <= d.y)|| (a.y <= c.y && b.y < d.y)
						|| (c.x <= a.x && b.x < d.x) || (c.x < a.x && b.x <= d.x)
						|| (c.y < a.y && b.y <= d.y) || (c.y <= a.y && b.y < d.y))
					{						
							cout << "4" << "\n";
					}
					else if (a.x == c.x && b.x == d.x) {
						if (a.x != b.x || c.x != d.x)
							cout << "4" << "\n";
						else
							cout << "1" << "\n";
					}
					else if (a.y == c.y && b.y == d.y) {
						if (a.y != b.y || c.y != d.y)
							cout << "4" << "\n";
						else
							cout << "1" << "\n";
					}						
					//a---c---d---b
					else
						cout << "1" << "\n";
					//a---b   c---d
				}
				else
					cout << "2" << "\n";
				//그냥 교차함
			}
			else
				cout << "1" << "\n";
			//교차 하기 전에 안만남

		}

	}

}