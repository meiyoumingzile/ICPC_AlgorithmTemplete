#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;

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


#define BIT 2//压位
ll p10[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000,100000000000};
const ll HEX=p10[BIT];
struct BigInteger{
    int sign;
    ll *number;
    int size=0;
    BigInteger(int up=MAX){
        number=new ll[up];
    }
    BigInteger(char*s,int up=MAX){
        init(s,up);
    }
    BigInteger(ll s,int up=MAX){
        init(s,up);
    }
    ~BigInteger(){
        delete []number;
    }
    void init(char*s,int up=MAX){//s可以有符号,1代表正数，-1代表负数
        number=new ll[up];
        ll c=0;
        int i,j=0,len;
        len=strlen(s);
        sign=1;
        for(i=len-1;i>=0;i--){
            if(s[i]>47&&s[i]<58){
                if(j<BIT){
                    c+=p10[j++]*(s[i]-'0');
                }else{
                    number_push(c);
                    j=0;
                    c=p10[j++]*(s[i]-'0');
                }
            }else if(s[i]=='-'){
                sign=-1;
            }
        }
        number_push(c);
        if(size==1&&number[0]==0){
            sign=0;
        }
    }
    void init(ll s,int up=MAX){
        number=new ll[up];
        sign=0;
        if(s<0){
            sign=-1;
            s=-s;
        }else if(s>0){
            sign=1;
        }
        while(s){
            number_push(s%HEX);
            s/=HEX;
        }
    }
    void number_push(ll a){
        number[size++]=a;
    }

    BigInteger* nttmul(BigInteger *b){//NTT实现
        BigInteger *c=new BigInteger();
        c->sign=sign*b->sign;
        ll i,ni,len,N,next=0,up;
        len=size+b->size-1;
        ni=NTT::changeN(len);
        N=NTT::p2[ni];
        up=N<<1;
        ll *F1=NTT::ntt(number,ni,1,size,up);
        ll *F2=NTT::ntt(b->number,ni,1,b->size,up);
        ll *F3=new ll[up];
        for(i=0;i<N;i++){
            F3[i]=F1[i]*F2[i]%NTT::P;
        }
        ll* x=NTT::ntt(F3,ni,-1,N,up);
        for(i=0;i<len;i++){
            x[i]+=next;
            next=x[i]/HEX;
            x[i]=x[i]%HEX;
        }
        if(next){
            x[len++]=next;
        }
        for(;!x[len-1];len--);
        memset(x+len,0,sizeof(ll)*(up-len));//末尾清0；
        delete []c->number;
        c->number=x;
        c->size=len;
        delete []F1;
        delete []F2;
        delete []F3;
        return c;
    }
    BigInteger* mul(BigInteger *b){
        BigInteger *c=new BigInteger(size+b->size);
        c->sign=sign*b->sign;
        ll i,j,h,k,next=0;
        for(i=0;i<size;i++){
            for(j=0;j<b->size;j++){
                h=j+i;
                k=number[i]*b->number[j]+next;
                if(h<c->size){
                    k+=c->number[h];
                    c->number[h]=k%HEX;
                }else{
                    c->number_push(k%HEX);
                }
                next=k/HEX;
            }
            for(;next;c->number_push(next%HEX),next/=HEX);
        }
        return c;
    }

    void println(){//打印格式长度等于BIT
        if(sign==0){
            printf("0\n");
            return;
        }
        if(sign==-1)
            printf("-");
        printf("%llu",number[size-1]);
        for(int i=size-2;i>=0;i--){
            printf("%02llu",number[i]);
        }printf("\n");
    }
    char *toChar(ll a){
        char *c=new char[BIT];
        memset(c,'0',sizeof(char)*BIT);
        for(int i=BIT-1;i>=0;i--){
            c[i]=(char)(a%10+'0');
            a/=10;
        }
        return c;
    }
    void myprintln(){//打印格式长度等于BIT
        ll i,j,k;
        printf("%lld",number[size-1]);
        for(i=0,k=number[size-1];k>0;i++,k/=10);
        int len=i;
        for(int i=size-2;i>=0;i--){
            if(len+BIT<1000){
                printf("%02lld",number[i]);
                len+=BIT;
            }else{
                char *c=toChar(number[i]);
                for(j=0;j<BIT;j++){
                    printf("%c",c[j]);
                    if(j+len==999)
                        printf("\n");
                }
                len=len+BIT-1000;
                delete []c;
            }
        }
    }
};

BigInteger *temp;
BigInteger *arr[MAX];
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("数据1059/out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    ll i,j,k,n,N;
    scanf("%lld",&n);
    //n=100000;
    for(i=1;i<=n;i++){
        arr[i]=new BigInteger(i,16);
    }
    for(j=1;j<n;j=k){
        k=j*2;
        for(i=1;i+j<=n;i+=k){
            temp=arr[i];
            if(arr[i]->size<32&&arr[i+j]->size<32){
                arr[i]=arr[i]->mul(arr[i+j]);
            }else{
                arr[i]=arr[i]->nttmul(arr[i+j]);
            }
            delete temp;
            delete arr[i+j];
        }
    }
    arr[1]->myprintln();
return 0;
}
