#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=998244353;

struct v2{
    ll x,y;
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
v2 A[2021];
ll coe[2021],temp[2021];//coefficient系数
ll quickmi(ll a,ll b,const ll &mod){//最短写法
    ll ans=1;
    for(a%=mod;b;b>>=1,a=a*a%mod)
        if(b&1)
            ans=ans*a%mod;
    return ans;
}
void lagrange2(v2 *A,ll *coe,int n){//n个数据点，n-1次多项式
    int i,j;
    ll lup=1,ldown,inv[2],a;//ldown是所有A[i].x乘积是作为函数li的分母
    memset(temp,0,sizeof temp);
    memset(coe,0,sizeof coe);
    temp[0]=1;
    for(i=0;i<n;i++){
        for(j=i;j>=0;j--){
            temp[j+1]=(temp[j+1]*A[i].x%mod+temp[j])%mod;
        }
        temp[0]=temp[0]*A[i].x%mod;
    }

    //printf("~~%lld\n",lup);
    for(i=0;i<n;i++){
        ldown=1;
        for(j=0;j<n;j++){//多项式除法和计算ldown
            if(i!=j)
                ldown=ldown*(A[i].x-A[j].x+mod)%mod;
        }
        ldown=quickmi(ldown,mod-2,mod)*A[i].y%mod;
        a=quickmi(A[i].x,mod-2,mod)%mod;
        inv[1]=(2-a*A[i].x%mod+mod)%mod*a%mod;
        inv[0]=(0-a+mod)%mod*a%mod;
        //temp[n-j]=0;
        for(j=0;j<n;j++){//多项式除法和计算ldown
            coe[j]=(temp[j]*inv[0]%mod+inv[1]*temp[j+1]%mod)%mod;
        }
        for(j=0;j<n;j++){//多项式除法和计算ldown
            printf("%lld ",coe[j]);
        }printf("\n");
        //ans=(ans+lup*ldown%mod*inv%mod*A[i].y%mod)%mod;//直接计算
    }
}
ll lagrange1(v2 *A,ll *coe,int n,int x0=0){//n个数据点，n-1次多项式
    int i,j;
    ll lup=1,ans=0,ldown,inv;//ldown是所有A[i].x乘积是作为函数li的分母
    memset(temp,0,sizeof temp);
    temp[0]=1;
    for(i=0;i<n;i++){
        //lup=lup*(x0-A[i].x+mod)%mod;
        for(j=0;j<=i;j++){

        }
    }
    //printf("~~%lld\n",lup);
    memset(coe,0,sizeof coe);
    memset(temp,0,sizeof temp);
    for(i=0;i<n;i++){

        inv=quickmi((x0-A[i].x+mod)%mod,mod-2,mod);
        ldown=1;
        for(j=0;j<n;j++){
            if(i!=j)
                ldown=ldown*(A[i].x-A[j].x+mod)%mod;
        }
        ldown=quickmi(ldown,mod-2,mod);
        //ans=(ans+lup*ldown%mod*inv%mod*A[i].y%mod)%mod;//直接计算
        //ans=(ans+lup*ldown%mod*inv%mod*A[i].y%mod)%mod;//直接计算
    }
    return ans;
}
ll calc(int n,int x0=0){
    ll ans=0,a=1;
    for(int i=0;i<=n;i++){
        ans=(ans+coe[i]*a%mod)%mod;
        a=a*x0%mod;
    }
    return ans;
}
int main(int argc,char *argv[]){//先求多项式系数表示法的系数，再求解。直接带入更简单。
	int i,j,k,t,T,n,m;
    scanf("%d%d",&n,&k);
    for(i=0;i<n;i++){
        scanf("%lld%lld",&A[i].x,&A[i].y);
    }
    lagrange2(A,coe,n);
    printf("%lld\n",calc(n,k));
    //printf("%lld\n",lagrange2(A,n,k));
return 0;
}
/*
3 100
1 4
2 9
3 16

166374059 526851186 864220806 23877758
998244352 1
249561088 499122177
554580196 332748118
*/
