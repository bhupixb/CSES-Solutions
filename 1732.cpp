// Don't Look
#include <bits/stdc++.h> 
#include "bits/stdc++.h" 
 
using namespace std;
 
#define int long long
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
 
#ifndef bhupixb
  #define var(...) 
  #define stl(...) 
#endif
 
vector<int> pi;
 
// Kmp
inline void lps(string &s) {
  int n = s.size();
  pi.resize(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i-1];
    while (j > 0 && s[i] != s[j])
      j = pi[j-1];
    if (s[i] == s[j])
      j++;
    pi[i] = j;
  }
}
 
signed main() {
  fast;
  string s;
  cin >> s;
  lps(s);

  int n = s.size();
  int cur = pi[n-1];  
  
  vector<int> v;
  while (cur > 0) {
    v.push_back(cur);
    cur = pi[cur - 1];
  }
  sort(v.begin(), v.end());
  for (int x: v) {
    cout << x << ' ';
  }
  return 0;
}
