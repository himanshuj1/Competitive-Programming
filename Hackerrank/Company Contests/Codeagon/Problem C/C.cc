#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <queue>
#include <stack>

#define sd(x) scanf("%d",&x)
#define sd2(x,y) scanf("%d%d",&x,&y)
#define sd3(x,y,z) scanf("%d%d%d",&x,&y,&z)

#define fi first
#define se second
#define pb(x) push_back(x)
#define mp(x,y) make_pair(x,y)
#define LET(x, a)  __typeof(a) x(a)
#define foreach(it, v) for(LET(it, v.begin()); it != v.end(); it++)

#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define __ freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);

#define tr(x) cout<<x<<endl;
#define tr2(x,y) cout<<x<<" "<<y<<endl;
#define tr3(x,y,z) cout<<x<<" "<<y<<" "<<z<<endl;
#define tr4(w,x,y,z) cout<<w<<" "<<x<<" "<<y<<" "<<z<<endl;
#define tr5(v,w,x,y,z) cout<<v<<" "<<w<<" "<<x<<" "<<y<<" "<<z<<endl;
#define tr6(u,v,w,x,y,z) cout<<u<<" "<<v<<" "<<w<<" "<<x<<" "<<y<<" "<<z<<endl;

using namespace std;

int n, m, a[100100];
vector<int> pos[100100];

const int LOGN = 17;
int sp[LOGN][1<<LOGN], k[1<<LOGN], o[1<<LOGN];

void sparseTable(){
	
	for(int i = 0; i < n; i++){
		sp[0][i] = a[i];
	}
	
	for(int j = 1; j < LOGN; j++){
		for(int i = 0; (i+(1<<j)-1) < n; i++){
			sp[j][i] = max(sp[j-1][i], sp[j-1][i+(1<<(j-1))]);
		}
	}
	
	for(int i = 2; i <= n; i++){
		k[i] = k[i-1] + ((i&(i-1)) == 0);
		if(k[i] == k[i-1]) o[i] = o[i-1];
		else o[i] = ((o[i-1]+1)<<1)-1;
	}
	
	return;
}

int rmq(int x, int y){
	int l = y-x+1;
	return max(sp[k[l]][x], sp[k[l]][y-o[l]]);
}

int main(){
	sd2(n,m);
	for(int i = 0; i < n; i++){
		sd(a[i]);
		pos[a[i]].pb(i);
	}
	
	sparseTable();
	while(m--){
		int l, r;
		sd2(l,r);
		l--, r--;
		int val = rmq(l,r);
		int l1 = lower_bound(pos[val].begin(), pos[val].end(), l) - pos[val].begin();
		int l2 = upper_bound(pos[val].begin(), pos[val].end(), r) - pos[val].begin() - 1;
		printf("%d\n", l2-l1+1);
	}
	
	
	return 0;
}
