#include <iostream>

using namespace std;

int main() {
	
	short int a, b;
	b = 0;
	cin >> a;
	if(9 & 1){
		cout << "x" <<endl;
	}
	
	while (a != 0){
		if(a & 1){
			b ++;
		}
		a >>= 1;
	}
	
	cout << b;
	
	return 0;
}
