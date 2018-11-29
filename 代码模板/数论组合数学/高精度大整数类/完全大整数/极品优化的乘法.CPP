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
#define bint BigInteger*
#define rg register
#define cint const int&
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
    cd wn[MAX*4];
    const int p2[30]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216};
    inline ll changeN(ll N){//把N变成2的整数次方，并且生成序列,返回p2数组的下标
        ll i;
        for(i=0;p2[i]<N;i++);
        return i;
    }

    void getwn(int n){
        for(int i=0;i<n;i++)wn[i] = cd(cos(2*PI/n*i),sin(2*PI/n*i));
    }
    inline void fft(cd *x,int ni,int fp){//在原址进行fft变换要求数组长度要大于p2[ni]
        register int i,j,m,k,N=p2[ni],n=N>>1;
        register cd d,inv,G;
        cd *p,*q;
        for(i=0,j=0;i<N;++i){
            if(i<j)swap(x[i],x[j]);
            for(k=n;(j^=k)<k;k>>=1);
        }
        for(m=1;m<N;m=n){
            n=m<<1;
            for(i=0;i<N;i+=n){
                p=x+i;
                q=x+i+m;//得到前一半和后一半地址
                for(j=0;j<m;++j){
                    cd d=wn[N/n*j]*q[j];
                    q[j]=p[j]-d;
                    p[j]=p[j]+d;
                }
            }
        }
        if(fp==-1){
            m=N>>1;
            for(i=1;i<m;i++)
                swap(x[i],x[N-i]);
            for(i=0;i<N;i++)
                x[i]=x[i]/N;
        }
    }
};
int digitCnt(ll n){
    int cnt=0;
    for(;n;n/=10,cnt++);
    return cnt;
}
#define BIT 5//压位2
const ll p10[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000,100000000000};
const ll HEX=p10[BIT];
struct BigInteger{
    int sign=1;
    int *number;
    int size=0;
    BigInteger(int up=MAX){
        number=new int[up];
    }
    BigInteger(char*s){
        init(s);
    }
    BigInteger(ll s){
        init(s);
    }
    ~BigInteger(){
        delete []number;
    }
    void init(char*s){//s可以有符号,1代表正数，-1代表负数
        ll c=0;
        int i,j=0,len;
        len=strlen(s);
        number=new int[len/BIT+2];
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
        //printf("ff");
    }
    void init(ll s,int up=MAX){
        number=new int[up];
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
    ll tolong(){
        int i;
        ll ans=0,p=1;
        for(i=0;i<size;i++){
            ans+=p*number[i];
            p*=HEX;
        }
        return ans;
    }
    void number_push(int a){
        number[size++]=a;
    }
    void __moveNumber(int n){//新建number数组,把umber后面的部分拷贝过来，也就是让umber
        size-=n;
        int *x=new int[size];
        memcpy(x,number+n,sizeof(int)*size);
        delete []number;
        number=x;
    }
    BigInteger* clone(int up=MAX){
        BigInteger *c=new BigInteger(up);
        memcpy(c->number,number,sizeof(int)*size);
        c->sign=sign;
        c->size=size;
        return c;
    }
    bool is0(){
        return !sign;
    }
    void to0(){
        sign=0;
        size=1;
        number[0]=0;
    }

    BigInteger* fmul(BigInteger *b){//FFT实现
        register ll i,j,len,N,next=0,s,ni,n1,n2;
        n1=FFT::changeN(size*2);
        n2=FFT::changeN(b->size*2);
        ni=max(n1,n2);
        N=FFT::p2[ni];
        FFT::getwn(N);
        cd *x1=new cd[N];
        cd *x2=new cd[N];
        for(i=0;i<size;i++)
             x1[i].r=number[i];
        for(i=0;i<b->size;i++)
             x2[i].r=b->number[i];
        FFT::fft(x1,ni,1);
        FFT::fft(x2,ni,1);
        for(i=0;i<N;i++)
            x1[i]=x1[i]*x2[i];
        FFT::fft(x1,ni,-1);
        len=size+b->size;
        BigInteger *c=new BigInteger(len);
        for(i=0;i<len;++i){
            s=(x1[i].r+0.1)+next;
            next=s/(HEX);
            c->number[i]=s%(HEX);
        }
        for(;!c->number[len-1];len--);
        c->size=len;
        c->sign=sign*b->sign;
        delete []x1;
        delete []x2;
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
    inline void write(cint x){
        for(rg int i=BIT-1;i>=0;i--){
            putchar((x/p10[i]%10)+'0');
        }
    }
    void println(){//打印格式长度等于BIT
        if(sign==0){
            puts("0\n");
            return;
        }
        rg int i,j,x;
        if(sign==-1)
            putchar('-');
        printf("%d",number[size-1]);
        for(i=size-2;i>=0;i--){
            write(number[i]);
        }putchar('\n');
    }
};


char str[101000];
int main(int argc,char *argv[]){
    //freopen("数据//in2.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("数据//myout.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    ll n,i;
    //c->pow(new BigInteger(22))->println();
    gets(str);
    BigInteger *a=new BigInteger(str);
   // a->sqrt()->println();
    gets(str);
    BigInteger *b=new BigInteger(str);
    /*a->div(b)->println();
    a->mod(b)->println();
    BigInteger *c=new BigInteger("22222222222222");
    printf("%lld\n",a->mul(5,a));*/

    a->fmul(b)->println();
return 0;
}
/*
99999999999999999999
*/
