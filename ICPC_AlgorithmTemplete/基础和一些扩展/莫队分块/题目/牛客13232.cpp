#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;
inline void scan(int &x){
    char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}
struct v2{
    int x,y,z,i;
	v2(){}
	v2(const int &x,const int &y){
		sett(x,y);
	}
    void sett(const int &x,const int &y){
        this->x=x;
        this->y=y;
    }
};
bool cmp1(const v2 &a,const v2 &b){
    return a.x<b.x;
}
v2 que[MAX],ans[MAX];
int ind[MAX],A[MAX];
int cnt=0;
void addCnt(int x){
    ind[x]++;
    cnt+=(ind[x]==1);
}
void subCnt(int x){
    ind[x]--;
    cnt-=(ind[x]==0);
}
int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}
void changeIndx(int pre,int now){
    if(pre<now){
        for(int i=pre;i<now;i++){
            subCnt(A[i]);
        }
    }else{
        for(int i=pre-1;i>=now;i--){
            addCnt(A[i]);
        }
    }
}
void changeIndy(int pre,int now){
    if(pre<now){
        for(int i=pre+1;i<=now;i++){
            addCnt(A[i]);
        }
    }else{
        for(int i=pre;i>now;i--){
            subCnt(A[i]);
        }
    }
}
int sq=0;
int main(int argc,char *argv[]){
	int i,j,k,t,T,n,m,l,r,z;
    scan(n);scan(m);
    sq=(int)sqrt(n);
    cnt=0;
    for(i=0;i<n;i++){
        scan(A[i]);
    }
    for(i=0;i<m;i++){
        scan(l);
        scan(r);
        scan(z);
        que[i].x=l-1;
        que[i].y=r-1;
        que[i].z=z;
        que[i].i=i;
    }
    sort(que,que+m,[](const v2 &a,const v2 &b){
         if(a.x/sq==b.x/sq){//左端点属于同一块,此时y按照奇数偶数分块，如果a.x/sq是偶数则递增，否则递减
            return (bool)((a.y<b.y)^(a.x/sq%2==1));
         }
         return a.x<b.x;//左端点不属于同一块，就直接按照前后分
    });
    for(i=0;i<m;i++){
        ans[i].i=que[i].i;
    }

    for(i=que[0].x;i<=que[0].y;i++){
        addCnt(A[i]);
    }
    ans[0].x=cnt;
    for(i=1;i<m;i++){
        changeIndx(que[i-1].x,que[i].x);
        changeIndy(que[i-1].y,que[i].y);

        ans[i].x=cnt;
    }
    sort(ans,ans+m,[](const v2 &a,const v2 &b){
         return a.i<b.i;
    });
    for(i=0;i<m;i++){
        printf("%d\n",ans[i].x);
    }
return 0;
}

