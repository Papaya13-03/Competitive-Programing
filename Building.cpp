#include<bits/stdc++.h>
using namespace std;

const int mn = 4e6 + 7;
const int mm = 1e3 + 4;
const long long inf = 1e9+7;

using ll = long long;
template<typename T> using i2 = array<T,2>;

int n, a[mn];
int suffixMin[mn], prefixMin[mn];
ll increase[mn][2], decrease[mn][2];
ll prefixSum, suffixSum;

int main() {
	#define name ""
	ios_base :: sync_with_stdio(NULL);
	cin.tie(nullptr);
	cout.tie(nullptr);
	#ifndef ONLINE_JUDGE
	freopen(name".inp","r",stdin);
	freopen(name".out","w",stdout);
	#endif // ONLINE_JUDGE

	cin >> n;
	long long key, seed, mod;
	cin >> key >> seed >> mod;
	for(int i = 1; i <= n; ++i) {
		if(i == 1)a[i] = key%mod + 1;
		else a[i] = 1ll*a[i-1]*seed%mod + 1;
	}

	prefixMin[0] = inf;
	suffixMin[n+1] = inf;
	for(int i = 1; i <= n; ++i) {
		prefixMin[i] = min(prefixMin[i-1],a[i]);
		suffixMin[n-i+1] = min(suffixMin[n-i+2],a[n-i+1]);
	}

	deque<int>dq,dq1;
	dq.push_back(0);
	for(int i = 1; i <= n; ++i) {
		prefixSum = prefixSum + prefixMin[i];
		increase[i][0] = (prefixMin[i] < a[i]? -inf: prefixSum);
		while(!dq.empty() && a[dq.back()] > a[i]) {
			dq.pop_back();
		}
		decrease[i][0] = decrease[dq.back()][0] + 1ll*(i-dq.back())*a[i];
		dq.push_back(i);
	}


	dq1.push_back(n+1);
	for(int i = n; i >= 1; --i) {
		suffixSum = suffixSum + suffixMin[i];
		increase[i][1] = (suffixMin[i] < a[i]? -inf: suffixSum);
		while(!dq1.empty() && a[dq1.back()] > a[i]) {
			dq1.pop_back();	
		}
		decrease[i][1] = decrease[dq1.back()][1] + 1ll*(dq1.back()-i)*a[i];
		dq1.push_back(i);
	}

	long long ans = 0;
	i2<int>type = {0,0};
	int pos = 0;

	for(int i = 1; i <= n; ++i) {
		if(increase[i][0]+decrease[i][1]-a[i] >= ans) {
			ans = increase[i][0]+decrease[i][1]-a[i];
			type = {1,0};
			pos = i;
		}
		if(decrease[i][0]+increase[i][1]-a[i] >= ans) {
			ans = decrease[i][0]+increase[i][1]-a[i];
			type = {0,1};
			pos = i;
		}
		if(decrease[i][0]+decrease[i][1]-a[i] >= ans) {
			ans = decrease[i][0]+decrease[i][1]-a[i];
			type = {0,0};
			pos = i;
		}
	}

	for(int i = pos-1;i >= 1; --i) {
		if(type[0]) a[i] = prefixMin[i];
		else a[i] = min(a[i],a[i+1]);
	}

	for(int i = pos+1;i <= n; ++i) {
		if(type[1]) a[i] = suffixMin[i];
		else a[i] = min(a[i],a[i-1]);
	}

	cout << ans << '\n';
	for(int i = 1; i <= n; ++i)cout << a[i] <<" ";

	cerr<<"Running Time: "<<clock()/double(1000) <<"s\n";
	return 0;
}
