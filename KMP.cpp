#include <bits/stdc++.h>
using namespace std;

int main(){
	string a,b;
	cin >> a >> b;
	int len_a = a.length();
	int len_b = b.length();
	int LCS[len_a] = {0};
	for(int i = 1;i < len_b;i++){
		if(b[i] == b[LCS[i-1]]){
			LCS[i] = LCS[i-1] + 1;
		}
		else
			LCS[i] = 0;
	}
	int pointer = 0;
	//bool ok = false;
	int ans = 0;
	for(int i = 0;i < len_a;i++){
		while(pointer > 0 && a[i] != b[pointer]) pointer = LCS[pointer-1];
		if(a[i] == b[pointer]){
			pointer++;
			if(pointer == len_b){
				//ok = true;
				ans++;
				pointer = LCS[pointer-1];
			}
		}
	}
	cout << ans << "\n";
	return 0;
}