#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {// [a,b]
    return rand()%(b-a+1) + a;
}

int main(int argc, char** argv) {
    srand(atoi(argv[1]));
	int l = 10, c = 10;
	int prob = 500;// chance de botar espaco, em 1000
	cout << l << ' ' << c << endl;
	for(int i = 0; i < l; i++) {
		for(int j = 0; j < c; j++)
			cout << (rand(0,999) < prob ? '.' : '#');
		cout << endl;
	}
	int k = 100;
	cout <<  k << endl;
	for(int i = 0; i < k; i++)
		cout << rand(1,min(500,max(l,c))) << ' ' << rand(1,min(500,max(l,c))) << endl;
}
