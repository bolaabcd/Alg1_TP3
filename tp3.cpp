#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <stack>
#include <cassert>

using namespace std;

int maxi, maxil, maxih;

void find_best(int w, int h, vector<pair<int,int>> &ps) {
	int lyg = 0, ryg = ps.size()-1;
	while (lyg < ryg) {
		int mid = (lyg + ryg + 1)/2;
		if (ps[mid].second <= h)
			lyg = mid;
		else
			ryg = mid-1;
	}
	// sem mesa de altura h
	if (ryg < 0 || ps[ryg].second != h)
		return;
	int lys = 0, rys = ps.size()-1;
	while (lys != rys) {
		int mid = (lys + rys)/2;
		if (ps[mid].second >= h)
			rys = mid;
		else
			lys = mid + 1;
	}
	assert(ps[lys].second == h);
	while(lys < ryg) {
		int mid = (lys + ryg + 1)/2;
		if (ps[mid].first <= w)
			lys = mid;
		else
			ryg = mid - 1;
	}
	// sem mesa de altura h e largura <= w
	if (ryg < 0 || ps[ryg].first > w)
		return;
	assert(ps[ryg].first <= w);
	assert(ps[ryg].second == h);
	if (ps[ryg].first*h > maxi) {
		maxi = ps[ryg].first*h;
		maxil = ps[ryg].first;
		maxih = h;
	} else if (ps[ryg].first*h == maxi and ps[ryg].second > maxih) {
		maxil = ps[ryg].first;
		maxih = h;
	}
}

pair<int,int> solve(int l,int c, vector<vector<int>> &prefy, vector<pair<int,int>> &ps) {
	maxi = -0x7fffffff, maxil = -1, maxih = 1;
	for (int i = 0; i < l; i++) {
		prefy[i].push_back(0);
		stack<int> st;
		for (int j = 0; j < c+1; j++) {
			if (st.empty() or prefy[i][st.top()] <= prefy[i][j])
				st.push(j);
			while (!st.empty() and prefy[i][st.top()] > prefy[i][j]) {
				int tops = st.top();
				st.pop();
				int stop = -1;
				if(!st.empty())
					stop = st.top();
				find_best(j-1-(stop+1)+1,prefy[i][tops],ps);
			}
			if (st.empty() or prefy[i][st.top()] <= prefy[i][j])
				if (st.empty() or j != st.top())
					st.push(j);
		}
		prefy[i].pop_back();
	}
	return {maxil, maxih};
}

int main() {
	// pra ler e escrever mais rapido
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int l,c;
	cin >> l >> c;
	vector<vector<int>> prefx(c,vector<int>(l,0)), prefy(l,vector<int>(c,0));
	for (int i = 0; i < l; i++)
		for (int j = 0; j < c; j++) {
			char ch;
			cin >> ch;
			prefx[j][i] += ch == '.';
			prefy[i][j] += ch == '.';
			if (i > 0 && prefy[i][j] != 0)
				prefy[i][j] += prefy[i-1][j];
			if (j > 0 && prefx[j][i] != 0)
				prefx[j][i] += prefx[j-1][i];
		}
	int k;
	cin >> k;
	set<pair<int,int>> sy;
	for (int i = 0; i < k; i++) {
		int a, b;
		cin >> a >> b;
		sy.emplace(b,a);
	}
	vector<pair<int,int>> vy;
	for (auto pa: sy)
		vy.emplace_back(pa.second,pa.first);
	auto [a1, b1] = solve(l,c,prefy,vy);
	auto [a2, b2] = solve(c,l,prefx,vy);
	if (a1*b1 > a2*b2)
		cout << a1 << ' ' << b1 << endl;
	else if (a1*b1 < a2*b2)
		cout << a2 << ' ' << b2 << endl;
	else if (b1 > b2)
		cout << a1 << ' ' << b1 << endl;
	else
		cout << a2 << ' ' << b2 << endl;
}
