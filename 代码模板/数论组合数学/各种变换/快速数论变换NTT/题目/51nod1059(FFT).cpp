#include <iostream>
#include <stdio.h>
#include<string.h>
#include <cmath>
#include <algorithm>
using namespace std;
#define ll long long
#define cd Complex
const int MAX=100010;
const double PI=acos(-1.0);

struct Complex{
    double real=0,imag=0;//real+imagi
    Complex(){}
    Complex(double real,double imag){
        sett(real,imag);
    }
    void sett(double real,double imag){
        this->real=real;
        this->imag=imag;
    }
    Complex operator + (const Complex &other){
        Complex(real+other.real,imag+other.imag);
        return Complex(real+other.real,imag+other.imag);
    }
    Complex operator - (const Complex &other){
        return Complex(real-other.real,imag-other.imag);
    }
    Complex operator * (const Complex &other){
        return Complex(real*other.real-imag*other.imag,imag*other.real+real*other.imag);
    }
    Complex operator / (const Complex &other){
        double m=other.real*other.real+other.imag*other.imag;
        return Complex((real*other.real+imag*other.imag)/m,(imag*other.real-real*other.imag)/m);
    }
    Complex operator / (const double &other){
        return Complex(real/other,imag/other);
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
};



#define BIT 2//压位
ll p10[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000,100000000000};
const ll HEX=p10[BIT];
struct BigInteger{
    int sign;
    int *number;
    int size=0;
    BigInteger(int up=MAX){
        number=new int[up];
    }
    BigInteger(ll s,int up=MAX){
        init(s,up);
    }
    ~BigInteger(){
        delete []number;
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
    void number_push(int a){
        number[size++]=a;
    }

    inline BigInteger* fftmul(BigInteger *b){//FFT实现
        register ll i,ni,len,N,next=0,up;
        len=size+b->size-1;
        ni=FFT::changeN(len);
        N=FFT::p2[ni];
        up=N<<1;
        cd *x1=new cd[up];
        for(i=0;i<size;i++){
             x1[i].real=(double)number[i];
        }
        FFT::fft(x1,ni,1);
        cd *x2=new cd[up];
        for(i=0;i<b->size;i++){
             x2[i].real=(double)b->number[i];
        }
        FFT::fft(x2,ni,1);
        for(i=0;i<N;i++)
            x1[i]=x1[i]*x2[i];
        FFT::fft(x1,ni,-1);
        BigInteger *c=new BigInteger((int)up);
        c->sign=sign*b->sign;
        for(i=0;i<N;++i){
             c->number[i]=(int)(x1[i].real+0.1);
        }
        delete []x1;
        delete []x2;
        for(i=0;i<len;i++){
            c->number[i]+=next;
            next=c->number[i]/HEX;
            c->number[i]=c->number[i]%HEX;
        }
        if(next){
            c->number[len++]=next;
        }
        for(;!c->number[len-1];len--);
        if(N-len>0)
            memset(c->number+len,0,sizeof(int)*(N-len));//末尾清0；

        c->size=len;
        return c;
    }
    inline BigInteger* mul(BigInteger *b){
        if(size>40||b->size>40){
            return fftmul(b);
        }
        BigInteger *c=new BigInteger(size+b->size);
        c->sign=sign*b->sign;
        ll i,j,h,k,next=0;
        BigInteger *a=this;
        if(size>b->size)
            swap(a,b);
        for(i=0;i<a->size;i++){
            for(j=0;j<b->size;j++){
                h=j+i;
                k=a->number[i]*b->number[j]+next;
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
    char *toChar(int a){
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
        printf("%d",number[size-1]);
        for(i=0,k=number[size-1];k>0;i++,k/=10);
        int len=i;
        for(int i=size-2;i>=0;i--){
            if(len+BIT<1000){
                printf("%02d",number[i]);
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
        printf("\n");
    }
};

BigInteger *temp;
BigInteger *arr[MAX];
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("数据1059/out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    register ll i,j,k,n,N,m;
    scanf("%lld",&n);
    for(i=1;i<=n;i++){
        arr[i]=new BigInteger(i,16);
    }
    for(m=n;m>1; m=k){
        k=m>>1;
        if(m%2){
            temp=arr[2];
            arr[2]=arr[2]->mul(arr[1]);
            delete temp;
            for(i=1,j=2;i<=k;++i){
                temp=arr[i];
                arr[i]=arr[j]->mul(arr[j+1]);
                delete temp;
                j+=2;
            }
        }else{
            for(i=j=1;i<=k;++i){
                temp=arr[i];
                arr[i]=arr[j]->mul(arr[j+1]);
                delete temp;
                j+=2;
            }
        }
    }
    arr[1]->myprintln();
return 0;
}
