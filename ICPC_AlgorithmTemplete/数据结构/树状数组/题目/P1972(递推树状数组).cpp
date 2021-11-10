#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;
inline void scan(int &x){
    char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}


struct BIT{
    int n;
    int tree[MAX];
    void init(int n){
        this->n=n;
        memset(tree,0,sizeof(tree));
    }
    int lowbit(int x){
        return x&(-x);
    }
    void add(int x,int y){//单点x下标增加y,x下标从1开始
        for(int i=x;i<=n;i+=lowbit(i))
            tree[i]+=y;
    }
    int getsum(int x){//得到前缀和
        int ans=0;
        if(x>0){
            for(int i=x;i;i-=lowbit(i))//i要大于0
                ans+=tree[i];
        }
        return ans;
    }
    int getsum(int x,int y){//得到区间[x,y]的和，x，y下标从1开始
        if(x>y)
            return 0;
        return getsum(y)-getsum(x-1);
    }
};
BIT bi;

struct v2{
    int x,y,i;
	v2(){}
	v2(const int &x,const int &y){
		sett(x,y);
	}
    void sett(const int &x,const int &y){
        this->x=x;
        this->y=y;
    }
};

v2 que[MAX],ans[MAX];
int ind[MAX],A[MAX];//ind代表上一个A[i]所在的下标

void updateBit(int l,int r){//[l,r)
    for(int i=l;i<r;i++){
        bi.add(i,1);
        if(ind[A[i-1]]>0)
            bi.add(ind[A[i-1]],-1);
        ind[A[i-1]]=i;
    }
}
int main(int argc,char *argv[]){
	int i,j,k,t,T,n,m;
    scan(n);
    bi.init(n);
    for(i=0;i<n;i++){
        scan(A[i]);
    }
    scan(m);
    for(i=0;i<m;i++){
        scan(que[i].x);
        scan(que[i].y);
        que[i].i=i;
    }
    sort(que,que+m,[](const v2 &a,const v2 &b){
         if(a.y==b.y){//
            return a.x<b.x;
         }
         return a.y<b.y;//左端点不属于同一块，就直接按照前后分
    });
    int pre=1;
    for(i=0;i<m;i++){
        updateBit(pre,que[i].y+1);
        ans[i].x=bi.getsum(que[i].y)-bi.getsum(que[i].x-1);
        ans[i].i=que[i].i;
        pre=que[i].y+1;
    }
    sort(ans,ans+m,[](const v2 &a,const v2 &b){
         return a.i<b.i;
    });
    for(i=0;i<m;i++){
        printf("%d\n",ans[i].x);
    }

return 0;
}
/*
6
1 2 3 4 3 5
8
1 2
3 5
2 6
1 1
2 2
3 3
4 4
1 5
*/
