#include <bits/stdc++.h>
using namespace std;

const int maxN = (int) 1e6 + 7;

vector<int> f(maxN, 1);
vector<int> Next(maxN);
string text, pattern;

void buildF(){
	f[1] = 0;
	for(int i = 1;i < (int)pattern.size() - 1;i++){
		if(f[i] > 0 && pattern[i] == pattern[f[i]]){
			f[i + 1] = f[i] + 1;
		}
	}
	//in ra mang f de check
	for(int i = 1;i < (int)pattern.size();i++){
		cout << f[i] << " ";
	}
	cout << "\n";
}

void buildF_2(){
	f[1] = 0;
	for(int j = 1;j <= (int) pattern.size() - 1;j++){
		int t = f[j];
		while(t > 0 && pattern[j] != pattern[t]){
			t = Next[t];
		}
		f[j + 1] = t + 1;
	}
}

void buildNext(){
	int j = 1; // index of pattern
	int t = 0;
	while(j < (int)pattern.size()){
		t = f[j];
		while(t > 0 && pattern[j] != pattern[t]){
			t = Next[t];
		}
		t++;
		j++;
		if(pattern[j] == pattern[t]) Next[j] = Next[t];
		else Next[j] = t;
	}
	// in ra mang Next de check
	for(int i = 1;i < (int)pattern.size();i++){
		cout << Next[i] << " ";
	}
	cout << "\n";
}

void solve(){
	int ans = 0; // so lan xuat hien cua pattern trong text
	int j = 1; // index of pattern
	int k = 1; // index of text
	while(j < (int)pattern.size() && k < (int)text.size()){
		while(j > 0 && text[k] != pattern[j]){
			j = Next[j];
		}
		k++;j++;
		if(j == (int)pattern.size()){
			//in ra vi tri xuat hien
			cout << k - (int)pattern.size() + 1 << " ";
			// ---------------
			ans++;
			j = Next[j];
		}
	}
	// in ra xem co xuat hien khong
	if(j == (int)pattern.size()){
		cout << "Found!\n";
		return;
	}
	cout << "Not Found!\n";

	// in ra so lan xuat hien
	cout << ans << "\n";
}

void solveFaster(){
	char a = pattern[1];
	pattern[(int)pattern.size()] = '@';
	Next[(int)pattern.size()] = -1;
	int k = 1; text[(int)text.size()] = '|'; text[(int)text.size()] = a;
	int j = 1;
	get_started: j = 1;
	quick_test: while(text[k] != a) k++;
	char_matched: {j++; k++;}
	loop: if(j > 0);
		if(text[k] == pattern[j]){
			goto char_matched;
		}
		j = Next[j];
		if(j == 1){
			goto quick_test;
		}
		if(j == 0){
			k++;
			goto get_started;
		}
		if(j > 0) goto loop;
		string s = "";
		for(int i = k - (int)pattern.size() + 1;i <= k - 1;i++){
			s += text[i];
		}
		cout << "s = " << s << "\n";
		if(" " + s == pattern){
			cout << "Found!\n";
			return;
		}
	cout << "Not Found!\n";
}


int main(){
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	cin >> text >> pattern;
	text = " " + text;
	pattern = " " + pattern;
	buildF();
	buildNext();
	solve();
	solveFaster();
	return 0;
}