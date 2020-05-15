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
 
int N, M;
 
string substring; 
// dp[i][j] -> we have prefix of length i and their longest common suffix matches with first 
// j characters of given substring.
int dp[1004][104]; 
 
const int mod = 1e9 + 7;
 
inline void add_self(int &x, int y) {
  x += y;
  if (x >= mod) x -= mod;
}
 
int go(int id, int match) {
  if (id == N) return match == M;
  if (dp[id][match] != -1) {
    return dp[id][match];
  }
  int answer = 0;
  for (char ch = 'A'; ch <= 'Z'; ++ch) {
    if (match == M) add_self(answer, go(id + 1, M));
    else {
      if (ch == substring[match]) {
        add_self(answer, go(id + 1, match + 1));
      }
      else {
        int j = 0;
        if (match > 0) { // similiar as we do in KMP
          j = pi[match - 1];
          while (j > 0 && ch != substring[j]) {
            j = pi[j-1];
          }
          j += ch == substring[j];
        }
        add_self(answer, go(id + 1, j));
      }
    }
  }
 
  return dp[id][match] = answer;
}
 
signed main() {
  fast;
  memset(dp, -1, sizeof dp);
  cin >> N >> substring;
  M = substring.size();
  if (M > N) return cout << 0 << '\n', 0;
  lps(substring);
  int answer = go(0, 0);
  cout << (answer) % mod << '\n';
 
  return 0;
}
