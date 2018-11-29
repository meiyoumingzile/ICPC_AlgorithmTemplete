#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<map>
#include<set>
#include<windows.h>
using namespace std;
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LL long long
#define ll long long
#define ll __int64
#define lld I64d
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;

//得到一个数欧拉函数
ll getEu(ll N){//根据公式
    ll i,j,n=N,ans=N,m=1;
    for(i=2;n!=1;i++){
        if(n%i==0){
            while(n%i==0)
                n/=i;
            ans/=i;
            m*=i-1;
        }
    }
    if(ans==N){
        return N-1;
    }
    return ans*m;
}


struct getEuler{//快一点的o(n)方法，可以顺便素筛，欧拉筛法
    bool *flag;///标记数组
    int *phi;///欧拉函数值；
    int *prime;///素数
    int cnt;
    void getPhi(int MAX){
        cnt = 0;
        int i,j;
        flag=new bool[MAX];
        phi=new int[MAX];
        prime=new int[MAX];
        memset(flag,1,sizeof(bool)*MAX);//1代表是素数
        memset(phi,-1,sizeof(int)*MAX);//1代表是素数
        phi[1] = 1;
        for(i=2;i<MAX;i++){
            if(flag[i]){
                prime[cnt++]=i;
                phi[i]=i-1;//素数的欧拉函数是本身-1
            }
            for(j=0;j<cnt&&i*prime[j]<=MAX;j++){//遍历之前得到的每个素数
                flag[i*prime[j]]= false;///素数的倍数，所以i*p[j]不是素数
                if(i%prime[j]==0){///性质imodp==0, phi(i * p) == p * phi(i)
                    phi[i*prime[j]] =prime[j]*phi[i];
                    break;//有break为了加速，对于质数这已经是最后一个，对于合数，比如4*2算完不用管4*3=12,12留给后面6去计算
                }else{//如果不能除开，
                    phi[i*prime[j]]=(prime[j]-1)*phi[i];///i mod p != 0, 那么 phi(i * p) == phi(i) * (p-1)
                }
            }
            /*for(j=2;j<40;j++){
                printf("%d:%d ",j,phi[j]);
            }
            system("pause");*/
        }
    }
};
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//OJ上有的地方不能加这句话
    ll n;
    getEuler e;
    e.getPhi(MAX);
    printf("%d\n",e.cnt);

    while(~scanf("%lld",&n)){
        printf("%d %lld\n",e.phi[n],getEu(n));
    }
return 0;
}
