#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e6 + 7;
const int ASIZE = 256;
string pattern, text;
vector<int> d(maxN);
vector<int> dd(maxN);
int n,m;
int ans = 0;
// n: length text
// m: length pattern

void build_d(){
	for(int i = 0;i < ASIZE;i++){
		d[i] = m;
	}
	for(int i = 0;i < m - 1;i++){
		d[pattern[i]] = m - i - 1;
	}
}

void suffixes(vector<int> &suff){
	int f,g;
	suff[m - 1] = m;
	g = m - 1;
	for(int i = m - 2;i >= 0;i--){
		if(i > g && suff[i + m - 1 - f] < i - g){
			suff[i] = suff[i + m - 1 - f];
		}
		else{
			if(i < g){
				g = i;
			}
			f = i;
			while(g >= 0 && pattern[g] == pattern[g + m - 1 - f]){
				--g;
			}
			suff[i] = f - g;
		}
	}
}

void build_dd(){
	vector<int> suff(maxN);
	suffixes(suff);
	for(int i = 0;i < m;i++){
		dd[i] = m;
	}
	int j = 0;
	for(int i = m - 1;i >= 0;i--){
		if(suff[i] == i + 1){
			for(;j < m - 1 - i;j++){
				if(dd[j] == m){
					dd[j] = m - 1 - i;
				}
			}
		}
	}
	for(int i = 0;i <= m - 2;i++){
		dd[m - 1 - suff[i]] = m - 1 - i;
	}
}


void solve(){
	build_d();
	build_dd();
	int j = 0;
	int i;
	while(j <= n - m){
		for(i = m - 1;i >= 0 && pattern[i] == text[i + j];i--);
		if(i < 0){
			//cout << j << " ";
			ans++;
			j += dd[0];
		}
		else{
			j += max(dd[i],d[text[i + j]] - m + 1 + i);
		}
	}
}

int main(){
	cin >> text >> pattern;
	n = (int)text.size();
	m = (int)pattern.size();
	// text = " " + text;
	// pattern = " " + pattern;
	solve();
	cout << ans << "\n";
	return 0;
}