#include<bits/stdc++.h>
#define LL long long
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;


ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}

ll exgcd(ll a,ll b,ll &x,ll &y){  //另一种写法，返回最大公约数
    if(!b){
        x=1;y=0;return a;
    }
    int e=exgcd(b,a%b,x,y);
    int kkz=x;x=y;y=kkz-a/b*y;
    return e;
}


int main(int argc,char *argv[]){
    //freopen("debug\\in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("debug\\out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//OJ上有的地方不能加这句话
    ll i,j,t,a,b,c,p,g,x,y;

    while(1){
        scanf("%lld%lld",&a,&p);//求a对p得逆元，由于逆元存在条件是a和p互质，因此求解ax-py=1无解逆元也就不存在
        g=exgcd(a,p,x,y);
        if(1%g!=0){//1%gcd(a,p)！=0无解，根据扩展欧几里得解不定方程的方法
            printf("无解！！\n");
        }else{
            printf("%lld\n",x);
        }
    }
return 0;
}
