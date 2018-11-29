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
const int MAX=100010;

#define bint BigInteger

namespace NTT{
    ll wn[MAX*4],grn[33],grninv[33];
    const int P=998244353;
    const int p2[30]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216};
    inline ll changeN(ll N){//��N���2�������η���������������,����p2������±�
        ll i;
        for(i=0;p2[i]<N;i++);
        return i;
    }
    inline ll quickmi(ll a,ll b,ll P){
        ll ans=1;
        for(a%=P;b;b>>=1,a=a*a%P)
            if(b&1)
                ans=ans*a%P;
        return ans;
    }
    void getgrn(int g=3){//g��Pԭ��
        for(int i=0;i<30&&p2[i]>0;i++){
            ll r=(P-1)/p2[i];
            grn[i]=quickmi(g,r,P);
            grninv[i]=quickmi(grn[i],P-2,P);
        }
    }
    inline void ntt(ll *x,int ni,int fp){//��ԭַ����fft�任Ҫ�����鳤��Ҫ����p2[ni]
        register int i,j,m,N=p2[ni],n=N>>1;
        ll *p,*q,d,G;
        for(i=0,j=0;i<N;++i){
            if(i<j)swap(x[i],x[j]);
            for(m=n;(j^=m)<m;m>>=1);
        }
        wn[0]=1;
        int bit=1;
        for(m=1;m<N;m=n){
            n=m<<1;
            G=fp==1?grn[bit]:grninv[bit];
            for(i=1;i<m;++i)//��ǰԤ�������
                wn[i]=wn[i-1]*G%P;
            for(i=0;i<N;i+=n){
                p=x+i;
                q=x+i+m;//�õ�ǰһ��ͺ�һ���ַ
                for(j=0;j<m;++j){
                    d=q[j]*wn[j]%P;
                    q[j]=(p[j]-d+P)%P;
                    p[j]=(p[j]+d)%P;
                }
            }
            ++bit;
        }
        if(fp==-1){
            ll inv=quickmi(N,P-2,P);
            for(i=0;i<N;++i)
                x[i]=x[i]*inv%P;
        }
    }
}
int digitCnt(ll n){
    int cnt=0;
    for(;n;n/=10,cnt++);
    return cnt;
}
#define BIT 5
const ll p10[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000,100000000000};
const ll HEX=p10[BIT];
struct BigInteger{
    int sg=1;
    int *nu;
    int size=0;
    BigInteger(int up=MAX){
        nu=new int[up];
        size=0;
    }
    BigInteger(char*s){
        init(s);
    }
    BigInteger(ll s,int up){//ָ�����ٿռ�
        init(s,up);
    }
    ~BigInteger(){
        delete []nu;
    }
    void init(char*s){//s�����з���,1����������-1������
        ll c=0;
        int i,j=0,len;
        len=strlen(s);
        nu=new int[len/BIT+2];
        sg=1;
        for(i=len-1;i>=0;i--){
            if(s[i]>47&&s[i]<58){
                if(j<BIT){
                    c+=p10[j++]*(s[i]-'0');
                }else{
                    nu_push(c);
                    j=0;
                    c=p10[j++]*(s[i]-'0');
                }
            }else if(s[i]=='-'){
                sg=-1;
            }
        }
        nu_push(c);
        if(size==1&&nu[0]==0){
            sg=0;
        }
    }
    void init(ll s,int up){
        nu=new int[up];
        sg=0;
        if(s<0){
            sg=-1;
            s=-s;
        }else if(s>0){
            sg=1;
        }
        while(s){
            nu_push(s%HEX);
            s/=HEX;
        }
    }
    static void eq(BigInteger *&a,BigInteger*b){
        if(a)
            delete a;
        a=b;
    }
    ll tolong(){
        int i;
        ll ans=0,p=1;
        for(i=0;i<size;i++){
            ans+=p*nu[i];
            p*=HEX;
        }
        return ans;
    }
    void nu_push(int a){
        nu[size++]=a;
    }
    void __moveNumber(int n){//�½�nu����,��umber����Ĳ��ֿ���������Ҳ������umber
        size-=n;
        int *x=new int[size];
        memcpy(x,nu+n,sizeof(int)*size);
        delete []nu;
        nu=x;
    }
    BigInteger* clone(){
        BigInteger *c=new BigInteger(size);
        memcpy(c->nu,nu,sizeof(int)*size);
        c->sg=sg;
        c->size=size;
        return c;
    }
    bool is0(){
        return !sg&&!nu[0];
    }
    void to0(){
        sg=0;
        size=1;
        nu[0]=0;
    }
    int absCompare(BigInteger *b,int st=0){//st����b��stλ��ʼ�Ƚ�
        int i,j,l1=size,l2=b->size-st;
        if(l1==l2){
            for(i=l1-1;i>=0;i--)
                if(nu[i]!=b->nu[i+st])
                    return nu[i]>b->nu[i+st]?1:-1;
            return 0;
        }
        return l1>l2?1:-1;
    }
    int compare(BigInteger *b,int st=0){
        if(sg==b->sg)
            return sg<0?-absCompare(b,st):absCompare(b,st);
        return sg>b->sg?1:-1;
    }
    int compare(ll b,int st=0){
        BigInteger *now=new BigInteger(b);
        int res=compare(now,st);
        delete now;
        return res;
    }
    BigInteger* fmul(BigInteger *b,cint st=0){//FFTʵ��,��b�ĵ�stλ����
        if(is0()||b->is0())
            return new BigInteger("0");
        rg ll i,len,N,next=0,s,ni;
        ni=max(FFT::changeN(size*2)+b->size-st));//Ϊʲô�ǳ�2��������FFT����ȡ���ˣ��������ܶ�ѹ��λ
        N=FFT::p2[ni];
        ll *x1=new ll[N];
        ll *x2=new ll[N];
        memset(x1,0,sizeof(ll)*N);
        memset(x2,0,sizeof(ll)*N);
        for(i=0;i<size;i++)
             x1[i]=nu[i];
        for(i=st;i<b->size;i++)
             x2[i-st]=b->nu[i];
        FFT::fft(x1,ni,1);
        FFT::fft(x2,ni,1);
        for(i=0;i<N;i++)
            x1[i]=x1[i]*x2[i]%FFT::P;
        FFT::fft(x1,ni,-1);
        len=size+b->size-st;
        BigInteger *c=new BigInteger(len);
        for(i=0;i<len;++i){
            s=x1[i]+next;//��ȥ���ȵķ�Χ��һ��û��0.5�ܱ���
            next=s/HEX;
            c->nu[i]=s%HEX;
        }
        for(;!c->nu[len-1];len--);
        c->size=len;
        c->sg=sg*b->sg;
        delete []x1;
        delete []x2;
        return c;
    }
    inline void write(cint x){
        for(rg int i=BIT-1;i>=0;i--)
            putchar(x/p10[i]%10+'0');
    }
    void print(){//��ӡ��ʽ���ȵ���BIT
        if(is0()){
            putchar('0');
            return;
        }
        rg int i,j,x;
        if(sg==-1)putchar('-');
        printf("%d",nu[size-1]);
        for(i=size-2;i>=0;i--)
            write(nu[i]);
    }
    void println(){
        print();
        putchar('\n');
    }
};
char s1[MAX],s2[MAX];
int main(int argc,char *argv[]){
    register ll i,j,k,n,N,m;
    while(~scanf("%s%s",s1,s2)){
        bint *a=new bint(s1);
        bint *b=new bint(s2);
        bint *c=a->fmul(b);
        c->println();
        delete a;
        delete b;
        delete c;
    }
return 0;
}
