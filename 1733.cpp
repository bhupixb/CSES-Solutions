#include <bits/stdc++.h>
 
using namespace std;
 
#define int long long
 
const int N = 1e6 + 3;
 
#define MP make_pair
#define F first
#define S second
#define sz(s) ((int)s.size())
 
int rand(int l, int r){
  static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> ludo(l, r); return ludo(rng);
}
 
char s[N];
 
struct Hash {
  vector<pair<int,int>> H, pre;
  static const int mod;
  int add(int x, int y){
    x += y; return (x >= mod ? x - mod : x);
  }
  int sub(int x, int y) {
    x -= y; return (x < 0 ? x + mod : x);    
  }
  int mul(int x, int y) {
    x *= y; 
    x = (x >> 31) + (x & mod);
    x = (x >> 31) + (x & mod);
    return x;
  }
  Hash(const char *s, int N, int b1 = 41, int b2 = 53) :
    H(N + 5), pre(N + 5) {       
    pre[0].F = 1, b1 = rand(37, 1 << 10);
    pre[0].S = 1, b2 = rand(41, 1 << 9);
    int cur1 = 0, cur2 = 0;
    for (int i = 1; i <= N; ++i) {
      pre[i].F = mul(pre[i-1].F, b1);
      pre[i].S = mul(pre[i-1].S, b2);
      cur1 = add(mul(cur1, b1), (s[i] - 'a'));
      cur2 = add(mul(cur2, b2), (s[i] - 'a'));
      H[i].F = cur1, H[i].S = cur2;
    }   
  }
  pair<int,int> get_hash(int l, int r) {
    int rem1 = mul(pre[r-l+1].F, H[l-1].F);
    int rem2 = mul(pre[r-l+1].S, H[l-1].S);
    return MP(sub(H[r].F, rem1), sub(H[r].S, rem2));
  }
};
const int Hash::mod = (1LL << 31) - 1;
 
signed main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  srand(chrono::steady_clock::now().time_since_epoch().count());
  cin >> (s + 1);
  // cout << mod << '\n';
  int n = strlen(s + 1);
  Hash ins(s, n);
  vector<int> answer;
  answer.reserve(n);
  for (int len = 1; len <= n; ++len) {
    bool pos = true;
    auto forLen = ins.get_hash(1, len);
    for (int i = len + len; i <= n && pos; i += len) {
      pos &= (forLen == ins.get_hash(i - len + 1, i));      
    }
    int l = n / len * len;
    if (l != n) {
      int rem = n - l;
      pos &= ins.get_hash(1, rem) == ins.get_hash(l + 1, n);
    }
    if (pos) answer.push_back(len);
  }
  for (int x: answer) cout << x << ' ';
  return 0;
}