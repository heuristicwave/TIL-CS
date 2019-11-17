#include <iostream>
using namespace std;

class Power {
	int kick;
	int punch;
public:
	Power(int kick = 0, int punch = 0) {
		this->kick = kick; this->punch = punch;
	}
	void show();
	Power operator+ (int op2);
	friend Power operator++(Power& op, int x);
};

void Power::show() {
	cout << "kick=" << kick << ',' << "punch=" << punch << endl;
}

Power Power::operator+ (int op2) {
	Power tmp;
	tmp.kick = kick + op2;
	tmp.punch = kick + op2;
	return tmp;
}

Power operator++(Power& op, int x) {
	Power tmp = op;
	op.kick++;
	op.punch++;
	return tmp;
}

int main() {
	Power a(3, 5), b;
	a.show();			// 3, 5
	b.show();			// 0, 0
	b = a + 2;
	a.show();			// 3, 5
	b.show();			// 5, 5
	b = a++;
	a.show();			// 4, 6
	b.show();			// 3, 5
}