#include<bits/stdc++.h>
using namespace std;

const int mn = 5e6 + 7;
const int mm = 1e3 + 4;
const long long inf = 1e17;

using ll = long long;
template<typename T> using i2 = array<T,2>;

ll n, a[mn];
ll suffixMin[mn], prefixMin[mn];
ll suffixSum[mn], prefixSum[mn];
ll increase[mn][2], decrease[mn][2];
ll dp[mn];

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
	for(int i = 1; i <= n; ++i) cin >> a[i];
	prefixMin[0] = inf;
	suffixMin[n+1] = inf;
	for(int i = 1; i <= n; ++i) {
		prefixMin[i] = min(prefixMin[i-1],a[i]);
		prefixSum[i] = prefixSum[i-1] + prefixMin[i];
		suffixMin[n-i+1] = min(suffixMin[n-i+2],a[n-i+1]);
		suffixSum[n-i+1] = suffixSum[n-i+2] + suffixMin[n-i+1];
	}

	deque<int>dq;
	dq.push_back(0);
	for(int i = 1; i <= n; ++i) {
		increase[i][0] = (prefixMin[i] < a[i]? -inf: prefixSum[i]);
		while(!dq.empty() && a[dq.back()] > a[i]) {
			dq.pop_back();
		}
		dp[i] = dp[dq.back()] + (i-dq.back())*a[i];
		dq.push_back(i);
		decrease[i][0] = dp[i];
	}

	dq = deque<int>();
	dq.push_back(n+1);
	memset(dp, 0, sizeof dp);

	for(int i = n; i >= 1; --i) {
		increase[i][1] = (suffixMin[i] < a[i]? -inf: suffixSum[i]);
		while(!dq.empty() && a[dq.back()] > a[i]) {
			dq.pop_back();	
		}
		dp[i] = dp[dq.back()] + (dq.back()-i)*a[i];
		dq.push_back(i);
		decrease[i][1] = dp[i];
	}

	long long ans = 0;
	i2<int>type = {0,0};
	int pos = 0;

	for(int i = 1; i <= n; ++i) {
		if(increase[i][0]+decrease[i][1]-a[i] > ans) {
			ans = increase[i][0]+decrease[i][1]-a[i];
			type = {1,0};
			pos = i;
		}
		if(decrease[i][0]+increase[i][1]-a[i] > ans) {
			ans = decrease[i][0]+increase[i][1]-a[i];
			type = {0,1};
			pos = i;
		}
		if(decrease[i][0]+decrease[i][1]-a[i] > ans) {
			ans = decrease[i][0]+decrease[i][1]-a[i];
			type = {0,0};
			pos = i;
		}
	}

	for(int i = pos-1;i >= 1; --i) {
		if(type[0]) {
			a[i] = prefixMin[i];
		}
		else {
			a[i] = min(a[i],a[i+1]);
		}
	}

	for(int i = pos+1;i <= n; ++i) {
		if(type[1]) {
			a[i] = suffixMin[i];
		}
		else {
			a[i] = min(a[i],a[i-1]);
		}
	}

	cout << ans << '\n';
	for(int i = 1; i <= n; ++i)cout << a[i] <<" \n"[i==n];

	return 0;
}