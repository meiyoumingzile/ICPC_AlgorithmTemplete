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
const int mod=998244353;

namespace NTT{//FFT准备较多，避免名称混淆，定义个命名空间，以后避免重名的麻烦
    const int P=998244353;
    ll powg[MAX*8];
    int *seq[25];
    int seqSize[25];
    const int p2[30]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216};
    const int grn[30]={1,998244352,911660635,372528824,929031873,452798380,922799308,781712469,476477967,166035806,258648936,584193783,63912897,350007156,666702199,968855178,629671588,24514907,996173970,363395222,565042129,733596141};
    const int grninv[30]={1,998244352,86583718,509520358,337190230,87557064,609441965,135236158,304459705,685443576,381598368,335559352,129292727,358024708,814576206,708402881,283043518,3707709,121392023,704923114,950391366,428961804};
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



ll *getInv(const ll *A,int lenA){//对A数组求逆，lenA代表A长度
    int i,ni,N,n;
    ll *B;
    if(lenA==1){
        B=new ll[2];
        B[0]=NTT::quickmi(A[0],NTT::P-2,NTT::P);
        B[1]=0;
        return B;
    }
    B=getInv(A,(lenA+1)>>1);
    ni=NTT::changeN(lenA);
    n=NTT::p2[ni];
    N=NTT::p2[ni+1];
    NTT::getSeq(ni+1);
    ll *F1=NTT::ntt(A,ni+1,1,lenA,N);//要求的是乘积所以项数应该是两者和，参数传ni+1
    ll *F2=NTT::ntt(B,ni+1,1,lenA,N);
    for(i=0;i<N;i++)
        F1[i]=F1[i]*F2[i]%mod*F2[i]%mod;
    ll *x=NTT::ntt(F1,ni+1,-1,N,N);
    for(i=0;i<n;i++)
        x[i]=(2*B[i]%mod-x[i]+mod)%mod;
    memset(x+lenA,0,sizeof(ll)*(N-lenA));
    delete []B;
    B=x;
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
