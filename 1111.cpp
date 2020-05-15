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
 
vector<vector<int>> res;
 
template<typename T>
void manacher(const T &s) {
  int n = s.size();
  res.assign(2, vector<int>(n));
  // let l = res[1][i] - 1, here range(i - l, i + l) is a palindrome
  // let l = res[0][i], here range(i - l, i + l - 1) if valid then is palindrome 
  for (int i = 0, l = 0, r = -1; i < n; i++) {
    int k = (i > r) ? 1 : min(res[1][l + r - i], r - i + 1);
    while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
      k++;
    }
    res[1][i] = k--;
    if (i + k > r) {
      l = i - k;
      r = i + k;
    }
  }
  for (int i = 0, l = 0, r = -1; i < n; i++) {
    int k = (i > r) ? 0 : min(res[0][l + r - i + 1], r - i + 1);
    while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
      k++;
    }
    res[0][i] = k--;
    if (i + k > r) {
      l = i - k - 1;
      r = i + k ;
    }
  }  
}
using pi = pair<int,int>;
 
pi ask(int i, bool f = 0) {
  int l;
  if (f) {
    l = res[1][i] - 1;
    return make_pair(i - l, i + l);
  }
  l = res[0][i];
  return make_pair(i - l, i + l - 1);
}
 
signed main() {
  fast;
  string s;
  cin >> s;
  manacher(s);
  int lenOfLongestPalindrome = 0, id = - 1;  
  int n = s.size();  
  for (int i = 0; i < n; ++i) {
    auto oddLen = ask(i, 1);
    int len = oddLen.second - oddLen.first + 1;
    if (lenOfLongestPalindrome < len) {
      lenOfLongestPalindrome = len;
      id = oddLen.first;
    }
    auto evenLen = ask(i, 0);
    len = evenLen.second - evenLen.first + 1;
    if (lenOfLongestPalindrome < len) {
      lenOfLongestPalindrome = len;
      id = evenLen.first;
    }
  }
  cout << s.substr(id, lenOfLongestPalindrome) << '\n';
 
 
  return 0;
}
