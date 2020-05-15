#include <bits/stdc++.h>
 
using namespace std;
 
#define int long long
 
vector<int> pi;
 
int lps(string &s) {
  int n = (s.size());
  pi.resize(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i-1];
    while (j > 0 && s[i] != s[j])
      j = pi[j-1];
    if (s[i] == s[j])
      j++;
    pi[i] = j;
  }
  return pi[n-1];
}
 
 
signed main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  string a, b;
  cin >> a >> b;
  int n = b.size();
  b += '$';
  b += a;
  lps(b);
  int ans = 0;
  for (int i = n + 1; i < pi.size(); ++i) {
    // cout << pi[i] << ' ';
    ans += pi[i] == n;
  }
  cout << ans << '\n';
  return 0;
}
