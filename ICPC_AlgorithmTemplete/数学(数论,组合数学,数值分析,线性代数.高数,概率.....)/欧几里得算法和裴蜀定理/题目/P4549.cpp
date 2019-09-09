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
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;

ll gcd(ll a,ll b){//普通求最大公约数
    return b?gcd(b,a%b):a;
}
ll A[100];
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,t,T,n;
	ll ans;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%lld",&A[i]);
    }
    ans=abs(A[0]);
    if(n>1){
        for(i=1;i<n;i++){
            ans=gcd(ans,abs(A[i]));
        }
    }
    printf("%lld\n",ans);
return 0;
}

