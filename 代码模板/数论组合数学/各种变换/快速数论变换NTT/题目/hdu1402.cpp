#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=500010;
const int mod=1e9+7;
char str1[MAX],str2[MAX];
    int P=998244353;
    ll powg[MAX];
    int seq[MAX];
    int p2[30]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152};
    int grn[30]={1,998244352,911660635,372528824,929031873,452798380,922799308,781712469,476477967,166035806,258648936,584193783,63912897,350007156,666702199,968855178,629671588,24514907,996173970,363395222,565042129,733596141};
    int grninv[30]={1,998244352,86583718,509520358,337190230,87557064,609441965,135236158,304459705,685443576,381598368,335559352,129292727,358024708,814576206,708402881,283043518,3707709,121392023,704923114,950391366,428961804};
    void rader(int *x,int N){//必须是2的整数幂
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
    ll quickmi(ll a,ll b,ll P){//×î¶ÌÐ´·¨
        ll ans=1;
        for(a%=P;b;b>>=1,a=a*a%P)
            if(b&1)
                ans=ans*a%P;
        return ans;
    }
    ll changeN(ll N){//把N变成2的整数次方，并且生成序列
        ll i;
        for(i=0;p2[i]<N;i++);
        N=p2[i];
        rader(seq,N);
        return N;
    }
    ll* NTT(const ll *x,int N,int kind){//必须是2的整数倍
        int i,j,n,m,bit,now;
        ll d,inv,b,G,Gn;
        ll *temp,*F;
        F=new ll[N];
        for(i=0;i<N;i++)
            F[i]=x[seq[i]];
        for(n=2,bit=1;n<=N;n*=2,bit++){
            temp=new ll[N];
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


#define BIT 1//不压位,这样可以FFT
ll p10[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000,100000000000};
const ll HEX=p10[BIT];
struct BigInteger{//不可变类型
    int sign;
    ll *number;
    int size=0;
    BigInteger(){
        number=new ll[MAX/BIT];
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
        number=new ll[MAX/BIT];
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
    void init(ll s){
        number=new ll[MAX/BIT];
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

    BigInteger* clone(){
        BigInteger *c=new BigInteger();
        c->number=number;
        c->sign=sign;
        return c;
    }

    int digitCnt(ll n){
        int cnt=0;
        for(;n;n/=10,cnt++);
        return cnt;
    }
    bool is0(){
        return !sign;
    }

    int absCompare(BigInteger *b){
        int l1=size,l2=b->size;
        if(l1==l2){
            for(int i=l1-1;i>=0;i--){
                if(number[i]!=b->number[i]){
                    return number[i]>b->number[i]?1:-1;
                }
            }
            return 0;
        }
        return l1>l2?1:-1;
    }
    int compare(BigInteger *b){
        if(sign==b->sign)
            return sign<0?-absCompare(b):absCompare(b);
        return sign>b->sign?1:-1;
    }
    int compare(ll b){
        BigInteger *now=new BigInteger(b);
        int res=compare(now);
        delete now;
        return res;
    }
    BigInteger* absAdd(BigInteger *b){
        BigInteger *c=new BigInteger();
        ll i,j,k,next=0;
        if(size>b->size){
            for(i=0;i<b->size;i++){
                k=number[i]+b->number[i]+next;
                next=k/HEX;
                c->number_push(k%HEX);
            }
            for(;i<size;i++){
                k=number[i]+next;
                next=k/HEX;
                c->number_push(k%HEX);
            }
            if(next){
                c->number_push(next);
            }
        }else{
            for(i=0;i<size;i++){
                k=number[i]+b->number[i]+next;
                next=k/HEX;
                c->number_push(k%HEX);
            }
            for(;i<b->size;i++){
                k=b->number[i]+next;
                next=k/HEX;
                c->number_push(k%HEX);
            }
            if(next){
                c->number_push(next);
            }
        }
        return c;
    }
    void push(BigInteger *c,ll k,ll &cnt,ll &next){
        k<0?(k+=HEX,next=1):next=0;
        if(k){
            for(;cnt;cnt--){
                c->number_push(0);
            }
            c->number_push(k);
        }else{
            cnt++;
        }
    }
    BigInteger* absSub(BigInteger *b){
        BigInteger *c=new BigInteger();
        ll i,j,k,next=0,cnt=0;
        c->sign=this->absCompare(b);
        if(c->sign==1){
            for(i=0;i<b->size;i++){
                k=number[i]-b->number[i]-next;
                push(c,k,cnt,next);
            }
            for(;i<size;i++){
                k=number[i]-next;
                push(c,k,cnt,next);
            }
        }else{
            for(i=0;i<size;i++){
                k=b->number[i]-number[i]-next;
                push(c,k,cnt,next);
            }
            for(;i<b->size;i++){
                k=b->number[i]-next;
                push(c,k,cnt,next);
            }
        }
        return c;
    }
    BigInteger* add(BigInteger *b){
        BigInteger *c;
        ll i,j,k,next=0;
        if(sign*b->sign==1){
            c=absAdd(b);
            c->sign=sign;
        }else if(sign*b->sign==-1){
            c=absSub(b);
            if(sign==-1)
                c->sign=-c->sign;
        }else{
            return sign?this->clone():b->clone();
        }
        return c;
    }
    BigInteger* sub(BigInteger *b){
        BigInteger *c;
        ll i,j,k,next=0;
        if(sign*b->sign==1){
            c=absSub(b);
            if(sign==-1)
                c->sign=-c->sign;
        }else if(sign*b->sign==-1){
            c=absAdd(b);
            c->sign=sign;
        }else if(sign==0){
            c=b->clone();
            c->sign=-c->sign;
        }else{
            c=clone();
        }
        return c;
    }
    BigInteger* mul(BigInteger *b){//NTT实现
        BigInteger *c=new BigInteger();
        c->sign=sign*b->sign;
        ll i,len,N,next=0;
        len=size+b->size-1;
        N=changeN(len);
        ll *F1=NTT(number,N,1);
        ll *F2=NTT(b->number,N,1);
        ll *F3=new ll[N];
        for(i=0;i<N;i++){
            F3[i]=F1[i]*F2[i]%P;
        }
        ll* x=NTT(F3,N,-1);
        for(i=0;i<len;i++){
            x[i]+=next;
            next=x[i]/HEX;
            x[i]=x[i]%HEX;
        }
        if(next){
            x[len++]=next;
        }
        for(;!x[len-1];len--);
        c->number=x;
        c->size=len;
        delete []F1;
        delete []F2;
        delete []F3;
        return c;
    }
    BigInteger* div(int b){//b<HEX
        if(b==0)
            return NULL;
        BigInteger *c=new BigInteger((ll)0);
        if(is0())
            return clone();
        c->sign=abs(b)/b*sign;
        ll i,j,h,k,next=0;
        while(c->size<size)
            c->number_push(0);
        for(i=size-1;i>=0;i--){
            k=next*HEX+number[i];
            c->number[i]=k/b;
            next=k%b;
        }
        while(c->size>0&&!c->number[c->size-1]){
            if(c->size)
                c->size--;
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
        printf("%lld",number[size-1]);
        for(int i=size-2;i>=0;i--){
            printf("%01lld",number[i]);
        }printf("\n");
    }
};


int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    while(~scanf("%s%s",str1,str2)){
        BigInteger *a=new BigInteger(str1);
        BigInteger *b=new BigInteger(str2);
        a->mul(b)->println();
        delete a;
        delete b;
    }
return 0;
}
