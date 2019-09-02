#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register
const int inv2=500000004;
const int INF=2147483647;
const int MAX=2000010;
const int mod=1e9+7;

namespace NTT{//FFT准备较多，避免名称混淆，定义个命名空间，以后避免重名的麻烦
    const int P=1e9+7;
    ll powg[MAX];
    int *seq[25];
    int seqSize[25];
    const int p2[30]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216};
    const int grn[30]={1,1000000006,694969654,233939221,850153601,410273365,70568353,896703593,418923782,376965048,80677378,403647879,188324199,231374250,662406845,19945454,427497125,363665645,162861709,486465643,380534669,281016459};
    const int grninv[30]={1,1000000006,525151758,566626863,630744615,840235484,822979621,950696814,68344034,876980455,856898045,962301030,15264921,622960887,827496651,360704903,632508602,104226761,505863558,290141121,350813334,2870323};

    inline void rader(int *x,int N){//必须是2的整数幂
        register int i,j,k;
        for(i=0;i<N;++i)
            x[i]=i;
        for(j=0,i=0;i<N-1;++i){
            if(i<j){
               swap(x[i],x[j]);
            }
            k=N>>1;
            while(j>=k){
                j-=k;
                k>>=1;
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
    inline void getSeq(int i){
        int N=p2[i];
        if(seqSize[i]==0){//防止多次求相同倒序，但是会牺牲一点空间
            seq[i]=new int[N+1];
            seqSize[i]=N;
            rader(seq[i],N);
        }
    }
    inline ll changeN(ll N){//把N变成2的整数次方，并且生成序列,返回p2数组的下标
        ll i;
        for(i=0;p2[i]<N;i++);
        getSeq(i);
        return i;
    }
    //x长度必须是2的整数倍,ni是2的多少次幂，N=p2[ni]表示x数组要FFT的长度, fp是-1表示逆变换， xlen是x有效长度不够补0，up新数组长度
    inline ll* ntt(const ll *x,int ni,int fp,int xlen=MAX,int up=MAX){
        register int i,j,n,m,bit,now,N=p2[ni];
        register ll d,inv,b,G,Gn;
        ll *temp,*F;
        F=new ll[up];
        for(i=0;i<N;++i)
            F[i]=seq[ni][i]<xlen?x[seq[ni][i]]:0;
        for(n=2,bit=1;n<=N;n<<=1,++bit){
            temp=new ll[up];
            m=n>>1;
            powg[0]=1;
            G=fp==1?grn[bit]:grninv[bit];
            for(i=1;i<m;++i){//提前预处理加速
                powg[i]=powg[i-1]*G%P;
            }
            for(i=0;i<N;i+=n){
                for(j=0;j<m;++j){
                    d=F[i+j+m]*powg[j]%P;
                    temp[i+j]=(F[i+j]+d)%P;
                    temp[i+j+m]=(F[i+j]-d+P)%P;//利用公式少做乘法加速
                }
            }
            delete []F;
            F=temp;
        }
        if(fp==-1){
            ll invN=quickmi(N,P-2,P);
            for(i=0;i<N;++i){
                F[i]=F[i]*invN%P;
            }
        }
        return F;
    }
};

ll *nttcalc(ll *a,ll*b,int ni){//a和b代表要计算的序列，ni代表要计算2的多少次方
    int i,n,N;
    n=NTT::p2[ni];
    N=NTT::p2[ni+1];
    NTT::getSeq(ni+1);
    ll *F1=NTT::ntt(a,ni+1,1,n,N);//要求的是乘积所以项数应该是两者和，参数传ni+1
    ll *F2=NTT::ntt(b,ni+1,1,n,N);
    ll *F3=new ll[N];
    for(i=0;i<N;i++){
        F3[i]=F1[i]*F2[i]%mod*F2[i]%mod;
    }

    ll *x=NTT::ntt(F3,ni+1,-1,N,N);
    for(i=0;i<n;i++){
        x[i]=(2*b[i]%mod-x[i]+mod)%mod;
    }
    memset(x+n,0,sizeof(ll)*n);
    delete []F1;
    delete []F2;
    delete []F3;
    return x;
}

ll *getInv(ll *A,int lenA){//对A数组求逆，lenA代表A长度
    int i,j,ni,n,M;
    ll *B,*B1;
    ni=NTT::changeN(lenA);
    M=NTT::p2[ni];
    B=new ll[1];
    B[0]=NTT::quickmi(A[0],NTT::P-2,NTT::P);
    for(i=0;NTT::p2[i]<=M;i++){
        B1=nttcalc(A,B,i);
        delete []B;
        B=B1;
        for(j=0;j<NTT::p2[i];j++){
            printf("%lld ",B[j]);
        }printf("\n");
    }
    return B;
}

ll A[MAX];
inline void read(ll &x){
    ll f=1;//标记正负
    x=0;//归零（这就是潜在bug，有可能传进来时x没有归零）
    char s=getchar();//读入第一个字符
    while(s<'0'||s>'9'){
        if(s=='-')//不能直接把f=-1，有可能输入的不是'-'而是其他乱七八糟的东西
            f=-1;
        s=getchar();//继续读
    }
    while(s>='0'&&s<='9'){
        x=x*10+s-'0';
        s=getchar();
    }
    x*=f;//改变正负
}
inline void print(ll x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)//只要x还是2位数或更多就继续分解
        print(x/10);//这里递归完后栈里面x的每一位是倒过来的（关于递归，我也实在解释不清楚，各位去看看神犇们的递归解释吧）
    putchar(x%10+'0');//输出（要把int型变为char型，加'0'即可）
}
int main(int argc,char *argv[]){
    //freopen("数据多项式求逆//in1.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("数据多项式求逆//out1.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    ll i,j,k,T,n,ni;
    read(n);
    for(i=0;i<n;i++){
        read(A[i]);
    }
    ll *B=getInv(A,n);

    print(B[0]);

    for(i=1;i<n;i++){
        putchar(' ');
        print(B[i]);
    }
return 0;
}
/*
5
1 6 3 4 9
7
21 2 423235 212441277 12 21 777
*/
