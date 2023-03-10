#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-7
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;

struct v2{
    int x,y;
	v2(){}
	v2(const int &x,const int &y){
		sett(x,y);
	}
    void sett(const int &x,const int &y){
        this->x=x;
        this->y=y;
    }
};
bool cmp(const v2 &a,const v2 &b){
    return a.x<b.x;
}
double dp[2001][2001],a[2001],q1i[2001];
int main(int argc,char *argv[]){//dp[i][j]代表长度为1的队列，排在第j个时，正好关门时，且他在队伍的前k位概率
	int i,j,k,t,T,n,m;
	double p1,p2,p3,p4,q1,q2,q3,sum=0;
	cin>>n>>m>>k>>p1>>p2>>p3>>p4;
	if(p1==1||p4==0){
        printf("0.00000\n");
        return 0;
	}
	q1=p2/(1-p1);
	q2=p3/(1-p1);
	q3=p4/(1-p1);
	q1i[0]=1;
	for(i=1;i<=n;i++){
        q1i[i]=q1i[i-1]*q1;
	}
	dp[1][1]=p4/(1-p1-p2);
	for(i=2;i<=n;i++){
        for(j=1;j<=i;j++){
            a[j]=q3*(j<=k)+q2*dp[i-1][j-1];
        }
        dp[i][i]=0;
        for(j=1;j<=i;j++){
            dp[i][i]+=q1i[i-j]*a[j];
        }
        dp[i][i]/=(1-q1i[i]);
        dp[i][1]=q1*dp[i][i]+a[1];
        for(j=2;j<i;j++){
            dp[i][j]=dp[i][j-1]*q1+a[j];
        }
	}
    printf("%.5lf\n",dp[n][m]);
return 0;
}

