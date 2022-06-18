#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <stack>
#include <cassert>

using namespace std;

int main() {
	// pra ler e escrever mais rapido
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int l,c;
	cin >> l >> c;
	vector<vector<char>> mapa1(l, vector<char>(c)), mapa2(c, vector<char>(l));
	for(int i = 0; i < l; i++)
		for(int j = 0; j < c; j++) {
			cin >> mapa1[i][j];
			mapa2[j][i] = mapa1[i][j];
		}

	int k;
	cin >> k;
	vector<pair<int,int>> mesas(k);
	for(auto&pa:mesas)cin >> pa.first >> pa.second;

	int maxi = -0x7fffffff, maxil = -1, maxic = 1;

	for(auto mesa: mesas) {
		for(int i = 0; i < l; i++) {
			for(int j = 0; j < c; j++) {
				bool da = true;
				for(int r = 0; da && r < mesa.first; r++) {
					for(int s = 0; da && s < mesa.second; s++) {
						if(i+r >= l or s+j >= c or mapa1[i+r][s+j] == '#') {
							da = false;
						}
					}
				}
				if (da and mesa.first*mesa.second > maxi) {
					maxi = mesa.first*mesa.second;
					maxil = mesa.first;
					maxic = mesa.second;
				} else if (da and mesa.first*mesa.second == maxi and mesa.second > maxic) {
					maxil = mesa.first;
					maxic = mesa.second;
				}
			}
		}
	}
	for(auto mesa: mesas) {
		for(int i = 0; i < c; i++) {
			for(int j = 0; j < l; j++) {
				bool da = true;
				for(int r = 0; da && r < mesa.first; r++) {
					for(int s = 0; da && s < mesa.second; s++) {
						if(i+r >= c or s+j >= l or mapa2[i+r][s+j] == '#') {
							da = false;
						}
					}
				}
				if (da and mesa.first*mesa.second > maxi) {
					maxi = mesa.first*mesa.second;
					maxil = mesa.first;
					maxic = mesa.second;
				} else if (da and mesa.first*mesa.second == maxi and mesa.second > maxic) {
					maxil = mesa.first;
					maxic = mesa.second;
				}
			}
		}
	}

	cout << maxil << ' ' << maxic << endl;
	return 0;
}
