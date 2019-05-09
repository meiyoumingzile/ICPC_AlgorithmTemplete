#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
#define cdou const double &
#define cv2 const v2 &
#define dd double
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;
ll dp[20][10];
ll getAns1(ll m){
    if(m<6)
        return 0;
    ll n,ans=0,p10=1,p=0,j=0,i,t=0;
    for(n=m,i=1;n;n/=10){//找到最好一个6
        if(n%10==6)
            j=i;
        i++;
    }
    for(n=m,i=1;n;n/=10){
        p=n%10;
        if(i>=j){
            if(p>0)
                ans+=dp[i][p-1];
        }else{
            t+=p*p10;
        }
        p10*=10;
        i++;
    }
    if(j>0)
        t++;
   // printf("%lld : %lld %lld\n",m,ans,t);
    return ans+t;
}
ll getAns2(ll n){
    ll i,j,ans=0,p10=1;
    for(i=6;i<=n;i++){
        for(j=i;j;j/=10){
            if(j%10==6){
                ans++;
                break;
            }
        }
    }
    return ans;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	ll i,j,t,T,n,m,ans;
    ll p10=1;
    for(i=1;i<=19;i++){
        dp[i][0]=dp[i-1][9];
        for(j=1;j<=5;j++){
            dp[i][j]=dp[i][j-1]+dp[i][0];
        }
        dp[i][6]=dp[i][5]+p10;
        for(j=7;j<=9;j++){
            dp[i][j]=dp[i][j-1]+dp[i][0];
        }
        p10*=10;
    }
    p10=1;

    cin>>n>>m;
    printf("%lld\n",getAns1(m)-getAns1(n-1));
   // printf("ac:%lld\n",getAns2(m)-getAns2(n-1));
return 0;
}
/*
0 1000000000000000000
*/
