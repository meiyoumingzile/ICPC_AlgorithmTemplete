#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;

struct v3{
    int x,y,z;
};
v3 d[MAX];
bool cmp(const v2 &a,const v2 &b){
    if(a.x==b.x&&a.y==b.y){
        return a.z<b.z;
        if(a.x==b.x){
            return a.y<b.y;
        }
    }
    return a.x<b.x;
}

int main(int argc,char *argv[]){
	int i,j,k,t,T,n,m;
    cin>>n>>k;
    for(i=0;i<n;i++){
        scanf("%d%d%d",&d[i].x,&d[i].y,&d[i].z);
    }
    sort(d,d+n,cmp);

return 0;
}

