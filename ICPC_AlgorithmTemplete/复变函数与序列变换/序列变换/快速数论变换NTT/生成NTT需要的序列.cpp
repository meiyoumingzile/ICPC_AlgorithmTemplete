#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100000010;
const int mod=1e9+7;
int p2[30]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152};

int pCnt;
bool vis[MAX];
int prime[MAX/10];
int phi[MAX];
void getPrime(int N){
    int i,j,k;
    pCnt=0;
    phi[1]=1;
    for(i=2;i<N;i++){
        if(!vis[i]){
            prime[pCnt++]=i;
            phi[i]=i-1;//如果i是素数，phi[i]=i-1
        }
        for(j=0;i*prime[j]<N;j++){
            k=i*prime[j];
            vis[k]=true;
            if(i%prime[j]==0){
                //i mod p = 0, 那么phi(i * p)=p * phi(i)
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }else{
                 //i mod p ≠0,  那么phi(i * p)=phi(i) * (p-1)，p是素数
                 phi[i*prime[j]]=phi[i]*(prime[j]-1);
            }
        }
    }
}

ll getEu(ll N){//根据公式，求一个数欧拉函数值,且数据较大有必要用筛法先求出素数,如果打表求很多个用下面的筛选方法
    ll i,n=N,ans=N,m=1;
    for(i=0;n!=1&&i<pCnt;i++){
        if(n%prime[i]==0){
            while(n%prime[i]==0)
                n/=prime[i];
            ans/=prime[i];
            m*=prime[i]-1;
        }
    }
    if(n>1){
        ans/=n;
        m*=n-1;
    }
    return ans*m;
}

ll quickmi(ll a,ll b,ll mod){//最短写法
    ll ans=1;
    for(a%=mod;b;b>>=1,a=a*a%mod)
        if(b&1)
            ans=ans*a%mod;
    return ans;
}

ll getmathRoot(ll p){//素数p的原根,p<int,判断到sqrt(p-1)
    ll phin,i,g,nown;
    phin=p-1;
    for(g=2;g<p;g++){
        for(i=0,nown=phin;i<pCnt&&nown>1;i++){
            if(nown%prime[i]==0){
                if(quickmi(g,phin/prime[i],p)==1)
                    goto ti;
                while(nown%prime[i]==0)
                    nown/=prime[i];
            }
        }
        if(nown==1||quickmi(g,phin/nown,p)!=1)
            return g;
        ti:;
    }
    return -1;
}

ll grn[30],grninv[30];
void wf(ll *a,int len,char *str=""){
    printf("%s",str);
    printf("{%lld",a[0]);
    for(int i=1;i<len;i++){
        printf(",%lld",a[i]);
    }printf("};\n");
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,g,p;
    ll r,G,inv;
    getPrime(MAX);
    printf("请输入一个合适的大素数,将生成30个原根的次方取模");
    scanf("%d",&p);
    freopen("原根预处理.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //p=998244353;
    g=getmathRoot(p);
    r=(p-1);
    //printf("%d\n",quickmi(g,r,p)%p);
    for(i=0;i<30&&p2[i]>0;i++){
        r=(p-1)/p2[i];
        grn[i]=G=quickmi(g,r,p);
        grninv[i]=quickmi(G,p-2,p);
    }
    wf(grn,i,"const int grn[30]=");
    wf(grninv,i,"const int grninv[30]=");
    fclose(stdout);
    printf("成功");
    system("pause");
return 0;
}
