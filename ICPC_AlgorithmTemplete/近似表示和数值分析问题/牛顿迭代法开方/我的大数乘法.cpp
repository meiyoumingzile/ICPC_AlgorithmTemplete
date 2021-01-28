#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
#define ll long long
#define ull unsigned long long
#define infll BigInteger*
const int MAX=100010;

const double PI=acos(-1.0);
#define cd Complex
struct Complex{
    double r=0,i=0;//r+ii
    Complex(){}
    Complex(double r,double i){
        sett(r,i);
    }
    void sett(double r,double i){
        this->r=r;
        this->i=i;
    }
    Complex operator + (const Complex &other){
        Complex(r+other.r,i+other.i);
        return Complex(r+other.r,i+other.i);
    }
    Complex operator - (const Complex &other){
        return Complex(r-other.r,i-other.i);
    }
    Complex operator * (const Complex &other){
        return Complex(r*other.r-i*other.i,i*other.r+r*other.i);
    }
    Complex operator / (const Complex &other){
        double m=other.r*other.r+other.i*other.i;
        return Complex((r*other.r+i*other.i)/m,(i*other.r-r*other.i)/m);
    }
    Complex operator / (const double &other){
        return Complex(r/other,i/other);
    }
};

namespace FFT{//FFT准备较多，避免名称混淆，定义个命名空间，以后避免重名的麻烦
    cd powg[MAX*8];
    const int p2[30]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216};
    inline ll changeN(ll N){//把N变成2的整数次方，并且生成序列,返回p2数组的下标
        ll i;
        for(i=0;p2[i]<N;i++);
        return i;
    }
    inline cd getW(int n,int fp){//得到Wn
        double k=2*PI/n;
        cd ans(cos(k),-sin(k)*fp);
        return ans;
    }
    inline void fft(cd *x,int ni,int fp){//把原本数组变换
        register int i,j,m,k,bit,N=p2[ni],n=N>>1;
        register cd d,inv,G;
        cd *p,*q;
        for(i=0,j=0;i<N;++i){
            if(i<j) swap(x[i],x[j]);
            for(k=n;(j^=k)<k;k>>=1);
        }
        powg[0]=cd(1,0);
        bit=1;
        for(m=1;m<N;m=n){
            n=m<<1;
            G=getW(n,fp);
            for(i=1;i<m;i++)//提前预处理加速
                powg[i]=powg[i-1]*G;
            for(i=0;i<N;i+=n){
                p=x+i;
                q=x+i+m;//得到前一半和后一半地址
                for(j=0;j<m;++j){
                    d=q[j]*powg[j];
                    q[j]=p[j]-d;
                    p[j]=p[j]+d;
                }
            }
            ++bit;
        }
        if(fp==-1)
            for(i=0;i<N;i++)
                x[i]=x[i]/(double)N;
    }
    //x长度必须是2的整数倍,ni是2的多少次幂，N=p2[ni]表示x数组要FFT的长度, fp是-1表示逆变换， xlen是x有效长度不够补0，up新数组长度
    inline cd *fft(const cd *x,int ni,int fp,int xlen,int up){
        cd *F=new cd[up];
        memcpy(F,x,sizeof(cd)*xlen);
        fft(F,ni,fp);
        return F;
    }
    void conv(cd *a,cd *b,int ni){//求卷积,ni表示是2的多少次方
        fft(a,ni,1);
        fft(b,ni,1);
        for(int i=0;i<ni;++i) a[i] = a[i]*b[i];
        fft(a,ni,-1);
    }
};


#define BIT 2//压位
ll p10[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000,100000000000};
const ll HEX=p10[BIT];
struct BigInteger{
    short int sign=1;
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
    int absCompare(BigInteger *b,int st=0){//st代表b*HEA^st次方
        int l1=size-st,l2=b->size;
        if(l1==l2){
            for(int i=l2-1;i>=0;i--)
                if(number[i+st]!=b->number[i])
                    return number[i+st]>b->number[i]?1:-1;
            for(int i=st-1;i>=0;i--)
                if(number[i]>0)
                    return 1;
            return 0;
        }
        return l1>l2?1:-1;
    }
    int compare(BigInteger *b,int st=0){
        if(sign==b->sign)
            return sign<0?-absCompare(b,st):absCompare(b,st);
        return sign>b->sign?1:-1;
    }
    int compare(ll b,int st=0){
        BigInteger *now=new BigInteger(b);
        int res=compare(now,st);
        delete now;
        return res;
    }

    BigInteger* __fmul(cd *x2,int lb,int bsign=1){//无符号乘以b的fft后数组
        register ll i,ni,len,N,next=0,up;
        len=size+lb-1;
        ni=FFT::changeN(len);
        N=FFT::p2[ni];
        up=N+10;
        cd *x1=new cd[up];
        for(i=0;i<size;i++)
             x1[i].r=number[i];
        FFT::fft(x1,ni,1);
        for(i=0;i<N;i++)
            x1[i]=x1[i]*x2[i];
        FFT::fft(x1,ni,-1);
        BigInteger *c=new BigInteger((int)up);
        for(i=0;i<len;++i){
            c->number[i]=(int)(x1[i].r+0.1)+next;
            next=c->number[i]/HEX;
            c->number[i]=c->number[i]%HEX;
        }
        if(next)
            c->number[len++]=next;
        for(;!c->number[len-1];len--);
        delete []x1;
        delete []x2;
        c->size=len;
        c->sign=sign*bsign;
        return c;
    }
    BigInteger* fmul(BigInteger *b){//FFT实现
        register ll i,ni,len,N,next=0,up;
        len=size+b->size-1;
        ni=FFT::changeN(len);
        N=FFT::p2[ni];
        up=N+10;
        cd *x2=new cd[up];
        for(i=0;i<b->size;i++)
             x2[i].r=b->number[i];
        FFT::fft(x2,ni,1);
        return __fmul(x2,b->size,b->sign);
    }
    void selfMul(ll b,BigInteger* c){//b小于HEX,C是结果
        int signb=0,i,j;
        if(b!=0)
            signb=b>0?1:-1;
        c->sign=sign*signb;
        c->size=size;
        ll next=0;
        for(i=0;i<size;i++){
            c->number[i]=next+number[i]*b;
            next=c->number[i]/HEX;
            c->number[i]%=HEX;
        }
        if(next)
            c->number_push(next);
    }
    void println(){//打印格式长度等于BIT
        if(sign==0){
            printf("0\n");
            return;
        }
        if(sign==-1)
            printf("-");
        printf("%lld",number[size-1]);
        for(int i=size-2;i>=0;i--){
            printf("%02lld",number[i]);
        }printf("\n");
    }
};


char str[101000];
int main(int argc,char *argv[]){
    //freopen("数据//in1.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("数据//myout.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    ll n,i;
    //c->pow(new BigInteger(22))->println();
    gets(str);
    BigInteger *a=new BigInteger(str);
    gets(str);
    BigInteger *b=new BigInteger(str);
    a->fmul(b)->println();
return 0;
}
