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
const int MAX=3000010;
const int mod=1e9+7;
inline void scan(int &x){
    rg char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}

ll INV[MAX];
void getInv(ll MAX,ll p){//打表法求很多个逆元,p是素数
    INV[1] = 1;
    for (int i=2;i<MAX;i++) {
        INV[i]=(ll)(p-p/i)*INV[p%i]%p;
    }
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,t,T,n,p;
	scanf("%d%d",&n,&p);
	getInv(n+1,p);
    for(i=1;i<=n;i++){
        printf("%lld\n",INV[i]);
    }
return 0;
}

