#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
const int MAX=2100000;

ll x1[MAX];
ll x2[MAX];
ll F3[MAX];

namespace NTT{//FFT准备较多，避免名称混淆，定义个命名空间，以后避免重名的麻烦
    const int P=998244353;
    int saveN=-1;
    ll powg[MAX];
    int seq[MAX];
    const int p2[30]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152};
    const int grn[30]={1,998244352,911660635,372528824,929031873,452798380,922799308,781712469,476477967,166035806,258648936,584193783,63912897,350007156,666702199,968855178,629671588,24514907,996173970,363395222,565042129,733596141};
    const int grninv[30]={1,998244352,86583718,509520358,337190230,87557064,609441965,135236158,304459705,685443576,381598368,335559352,129292727,358024708,814576206,708402881,283043518,3707709,121392023,704923114,950391366,428961804};
    inline void rader(int *x,int N){//必须是2的整数幂
        int i,j,k;
        for(i=0;i<N;i++){
            x[i]=i;
        }
        for(j=0,i=0;i<N-1;i++){
            if(i<j){
               swap(x[i],x[j]);
            }
            k=N/2;
            while(j>=k){
                j-=k;
                k/=2;
            }
            j+=k;
        }
    }
    inline ll quickmi(ll a,ll b,ll P){
        ll ans=1;
        for(a%=P;b;b>>=1,a=a*a%P)
            if(b&1)
                ans=ans*a%P;
        return ans;
    }
    inline ll changeN(ll N){//把N变成2的整数次方，并且生成序列
        ll i;
        for(i=0;p2[i]<N;i++);
        N=p2[i];
        if(saveN!=N){//避免重复计算倒序，如果和上次一样就用原来的
            saveN=N;
            rader(seq,N);
        }
        return N;
    }
    //x长度必须是2的整数倍,x数组一定要长度>=N,否则可能出现越界，kind是-1表示逆变换，flen新数组长度,xlen是原本数组长度
    inline ll* ntt(const ll *x,int N,int kind,int flen=MAX,int xlen=MAX){
        int i,j,n,m,bit;
        ll d,inv,b,G,Gn;
        ll *temp,*F;
        F=new ll[flen];
        for(i=0;i<N;i++)
            F[i]=seq[i]<xlen?x[seq[i]]:0;
        for(n=2,bit=1;n<=N;n*=2,bit++){
            temp=new ll[flen];
            m=n/2;
            powg[0]=1;
            G=kind==1?grn[bit]:grninv[bit];
            for(i=1;i<m;i++){//提前预处理加速
                powg[i]=powg[i-1]*G%P;
            }
            for(i=0;i<N;i+=n){
                for(j=0;j<m;j++){
                    b=F[i+j];
                    d=F[i+j+m]*powg[j]%P;
                    temp[i+j]=(b+d)%P;
                    temp[i+j+m]=(b-d+P)%P;//利用公式少做乘法加速
                }
            }
            delete []F;
            F=temp;
        }
        if(kind==-1){
            ll invN=quickmi(N,P-2,P);
            for(i=0;i<N;i++){
                F[i]=F[i]*invN%P;
            }
        }
        return F;
    }
};




void print(ll *x,int len){
    int i;
    printf("%lld",x[0]);
    for(i=1;i<len;i++){
        printf(" %lld",x[i]);
    }printf("\n");
}

int main(int argc,char *argv[]){
    //freopen("data//3.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("data//2out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    ll N,M,i,j,k,nm,len;
    scanf("%lld%lld",&N,&M);
    nm=len=M+N+1;
    for(i=0;i<=N;i++){
        scanf("%lld",&x1[i]);
    }
    for(i=0;i<=M;i++){
        scanf("%lld",&x2[i]);
    }
    nm=NTT::changeN(nm);
    ll *F1=NTT::ntt(x1,nm,1);
    ll *F2=NTT::ntt(x2,nm,1);
    for(i=0;i<nm;i++){
        F1[i]*=F2[i];
    }
    ll *x=NTT::ntt(F1,nm,-1);
    print(x,len);
return 0;
}
