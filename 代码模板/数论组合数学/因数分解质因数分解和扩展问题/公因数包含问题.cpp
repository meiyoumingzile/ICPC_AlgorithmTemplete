#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}
struct F{
    ll a,b,g;//a/b;
    void init(ll a,ll b){
        this->a=a;
        this->b=b;
        this->g=gcd(a,b);
        sim();
    }
    void sim(){
        a/=g;
        b/=g;
    }
};
bool isContain(ll a,ll b){//a的质因数种类，是否被b的质因数种类包含
    ll n=a,g=2;
    for(n=a;g>1;){
        g=gcd(n,b);
        b=g;
        n=n/g;
    }
    if(n==1){
        return 1;
    }
    return 0;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    ll i,j,k,T,n,a,b,g;
    F x,y;
    cin>>T;
    while(T--){
        scanf("%lld%lld%lld",&a,&b,&k);
        x.init(a,b);
        if(a==0||isContain(x.b,k)){
            printf("Finite\n");
        }else{
            printf("Infinite\n");
        }
    }
return 0;
}

