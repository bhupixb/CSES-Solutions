// Don't Look
#include <bits/stdc++.h> 
#include "bits/stdc++.h" 
 
using namespace std;
 
// #define int long long
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
 
#ifndef bhupixb
  #define var(...) 
  #define stl(...) 
#endif
 
const int N = 1e6 + 3;
const int mod = 1e9 + 7;
 
bool dp[5005][5005]; // dp[i][j] stores if substring s[i,j] exists in given n string or not
 
int ways[5005]; // ways[i] is number of ways to form string [1, i] using given n words
 
struct node {
  node *p[26]; 
  bool leaf;
  node() {
    leaf = false;
    memset(p, 0, sizeof(p));
  }
};
 
vector<int> upto;
 
struct trie {
  node *root;
  static char base;
  public:      
  trie(){
    root = new node();
  }
  void insert(const string &s){
    node *x = root;
    int size = s.size();
    for (int i = 0; i < size; i++) {
      if (x->p[s[i] - base] == NULL) {
        x->p[s[i] - base] = new node();
      }
      x = x->p[s[i] - base];      
    }
    x->leaf = true;
  }    
  void find(const string &s, int st, int ed){
    node *x = root;
    int size = s.size();
    for (int i = st; i < ed; ++i){
      if(x->p[s[i] - base] == NULL){
        return;
      }
      x = x->p[s[i] - base];
      if (x != NULL && x->leaf) upto.push_back(i - st);
    }    
  }    
};
char trie::base = 'a';
 
inline void add_self(int &x, int y) {
  x += y;
  if (x >= mod) x -= mod;
}
 
signed main() {
  fast;
  string s, tmp;
  cin >> s;
  int n = s.size();

  int t;
  cin >> t;
  trie ins;
  while (t--) {
    cin >> tmp;
    ins.insert(tmp);
  }
  
  for (int i = 0; i < n; ++i) {    
    upto.clear();
    // checks how many substrings starting from i exists in given set of strings
    ins.find(s, i, n); 
    for (int x: upto) {
      dp[i][i+x] = true;
    }      
  }
 
  for (int i = 0; i < n; ++i) {
    if (dp[0][i]) ways[i] = 1;
    for (int j = i - 1; j >= 0; --j) {
      if (dp[j + 1][i]) {        
        add_self(ways[i], ways[j]);
      }
    }
  }
 
  cout << ways[n - 1] << '\n';
 
  return 0;
}
