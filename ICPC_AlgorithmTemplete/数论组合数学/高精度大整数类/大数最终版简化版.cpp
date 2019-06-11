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
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;
#define bint BigInteger
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
        register int i,j,m,N=p2[ni],n=N>>1;
        cd *p,*q;
        for(i=0,j=0;i<N;++i){
            if(i<j)swap(x[i],x[j]);
            for(m=n;(j^=m)<m;m>>=1);
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
    BigInteger(ll s,int up){//指定开辟空间
        init(s,up);
    }
    ~BigInteger(){
        delete []nu;
    }
    void init(char*s){//s可以有符号,1代表正数，-1代表负数
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
    void __moveNumber(int n){//新建nu数组,把umber后面的部分拷贝过来，也就是让umber
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
    int absCompare(BigInteger *b,int st=0){//st代表b的st位开始比较
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
    BigInteger* absAdd(BigInteger *b){//st表示舍去多少个个位
        BigInteger *c=new BigInteger(max(size,b->size)+1);
        BigInteger *a=this;
        if(size < b->size)
            swap(a,b);
        ll i,j,k,next=0;
        for(i=0;i<b->size;i++){
            k=a->nu[i]+b->nu[i]+next;
            next=k/HEX;
            c->nu_push(k%HEX);
        }
        for(;i<a->size;i++){
            k=a->nu[i]+next;
            next=k/HEX;
            c->nu_push(k%HEX);
        }
        if(next)
            c->nu_push(next);
        return c;
    }
    void __push(BigInteger *c,ll k,ll &cnt,ll &next){
        k<0?(k+=HEX,next=1):next=0;//借位
        if(k){
            int i=c->size;
            for(;cnt;cnt--)
                c->nu[i++]=0;
            c->nu[i++]=k;
            c->size=i;
        }else{
            cnt++;
        }
    }
    BigInteger* absSub(BigInteger *b){//绝对值相减
        BigInteger *c=new BigInteger(max(size,b->size));
        ll i,j,k,next=0,cnt=0;
        c->sg=absCompare(b);
        if(c->sg!=0){
            BigInteger *a=this;
            if(c->sg==1)
                swap(a,b);
            for(i=0;i<a->size;i++){
                k=b->nu[i]-a->nu[i]-next;
                __push(c,k,cnt,next);
            }
            for(;i<b->size;i++){
                k=b->nu[i]-next;
                __push(c,k,cnt,next);
            }
        }else{
            c->nu_push(0);
        }
        return c;
    }
    void selfAbsAdd(ll b){
        b=abs(b);
        nu[0]+=b;
        ll i,next=0;
        for(i=0;i<size;i++){
            nu[i]+=next;
            next=nu[i]/HEX;
            nu[i]%=HEX;
        }
        if(next)
            nu_push(next);
    }
    void selfAbsSub(ll b,int com){//com代表大小.1代表自己大于b,则正常减法。否则就说明
        b=abs(b);
        if(com==1){
            nu[0]-=b;
            ll i,next=0;
            for(i=0;i<size;i++){
                nu[i]-=next;
                next=0;
                if(nu[i]<0){
                    nu[i]+=HEX;
                    next=1;
                }
            }
            for(;!nu[size-1];size--);
        }else{
            nu[0]=b-nu[0];
        }
    }
    BigInteger* add(BigInteger *b){
        BigInteger *c;
        ll i,j,k,next=0;
        if(sg*b->sg==1){
            c=absAdd(b);
            c->sg=sg;
        }else if(sg*b->sg==-1){
            c=absSub(b);
            if(sg==-1)
                c->sg=-c->sg;
        }else{
            return sg?clone():b->clone();
        }
        return c;
    }
    void selfAdd(ll b){//自加，b小于HEX
        if(b==0)
            return;
        int sgb,i,j,s,k;
        sgb=b>0?1:-1;
        b=abs(b);
        if(sg==0){
            sg=sgb;
            nu[0]=b;
        }else if(sgb==sg){
            selfAbsAdd(b);
        }else{
            s=sg;
            sg=1;
            k=compare(b);
            if(k==0){
                to0();
            }else{
                selfAbsSub(b,k);
                sg=(k==1?s:sgb);
            }
        }
    }
    void selfSub(ll b){//自减，b小于HEX
        if(b==0)
            return;
        int sgb,i,j,s,k;
        sgb=b>0?1:-1;
        b=abs(b);
        if(sg==0){
            sg=-sgb;
            nu[0]=b;
        }else if(sgb==sg){
            s=sg;
            sg=1;
            k=compare(b);
            if(k==0){
                nu[0]=sg=0;
                size=1;
            }else{
                selfAbsSub(b,k);
                sg=k==1?s:-sgb;
            }
        }else{
            selfAbsAdd(b);
        }
    }
    BigInteger* sub(BigInteger *b){
        BigInteger *c;
        ll i,j,k,next=0;
        if(sg*b->sg==1){
            c=absSub(b);
            if(sg==-1)
                c->sg=-c->sg;
        }else if(sg*b->sg==-1){
            c=absAdd(b);
            c->sg=sg;
        }else if(sg==0){
            c=b->clone();
            c->sg=-c->sg;
        }else{
            c=clone();
        }
        return c;
    }

    BigInteger* mul(BigInteger *b){
        BigInteger *c=new BigInteger(size+b->size);
        c->sg=sg*b->sg;
        ll i,j,h,k,next=0;
        for(i=0;i<size;i++){
            for(j=0;j<b->size;j++){
                h=j+i;
                k=nu[i]*b->nu[j]+next;
                if(h<c->size){
                    k+=c->nu[h];
                    c->nu[h]=k%HEX;
                }else{
                    c->nu_push(k%HEX);
                }
                next=k/HEX;
            }
            for(;next;c->nu_push(next%HEX),next/=HEX);
        }
        return c;
    }
    void mul(ll b,BigInteger* c){//b小于HEX,C是结果
        int sgb=0,i,j;
        if(b!=0)
            sgb=b>0?1:-1;
        c->sg=sg*sgb;
        c->size=size;
        ll next=0;
        for(i=0;i<size;i++){
            c->nu[i]=next+nu[i]*b;
            next=c->nu[i]/HEX;
            c->nu[i]%=HEX;
        }
        if(next)
            c->nu_push(next);
    }

    BigInteger* div(cint b,int st=0){//b<HEX,st表示从a的哪个位置算起
        if(b==0)
            return NULL;
        if(is0())
            return clone();
        int i,j,k,next=0,clen=size-st;
        BigInteger *c=new BigInteger(clen+1);
        c->sg=abs(b)/b*sg;
        for(i=size-1,j=clen-1;j>=0;i--,j--){
            ll k=next*HEX+nu[i];
            c->nu[j]=k/b;
            next=k%b;
        }
        while(clen>1&&!c->nu[clen-1])
            clen--;
        if(clen==1&&c->nu[0]==0)
            c->sg=0;
        c->size=clen;
        return c;
    }
    ll mod(ll b){//b小于HEX
        if(b<2){
            return 0;
        }else if(b==2){
            return nu[0]%2;
        }
        ll m=0,i;
        for(i=size-1;i>=0;i--)
            m=(nu[i]+m*HEX)%b;
        return sg*m;
    }
    BigInteger* fmod(BigInteger *b,BigInteger *d){//b是被除数，d是除法结果
        if(!b||b->is0()||b->compare(1)==0){
            return new BigInteger("0");
        }else if(b->compare(2)==0){
            return new BigInteger((ll)(nu[0]%2));
        }
        BigInteger *c,*ans;
        c=d->fmul(b);
        ans=absSub(c);
        ans->sg=!ans->is0();
        delete c;
        return ans;
    }
    BigInteger* fmul(BigInteger *b,cint st=0){//FFT实现,从b的第st位算起
        if(is0()||b->is0())
            return new BigInteger("0");
        rg ll i,len,N,next=0,s,ni;
        ni=max(FFT::changeN(size*2),FFT::changeN((b->size-st)*2));//为什么是乘2，这样把FFT数组取长了，大数就能多压几位
        N=FFT::p2[ni];
        FFT::getwn(N);
        cd *x1=new cd[N];
        cd *x2=new cd[N];
        for(i=0;i<size;i++)
             x1[i].r=nu[i];
        for(i=st;i<b->size;i++)
             x2[i-st].r=b->nu[i];
        FFT::fft(x1,ni,1);
        FFT::fft(x2,ni,1);
        for(i=0;i<N;i++)
            x1[i]=x1[i]*x2[i];
        FFT::fft(x1,ni,-1);
        len=size+b->size-st;
        BigInteger *c=new BigInteger(len);
        for(i=0;i<len;++i){
            s=x1[i].r+0.5+next;//舍去精度的范围大一点没事0.5很保险
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

    BigInteger* fdiv(BigInteger* b,cint st=0){//牛顿迭代求除法,st是表示a从哪里算起
        if(b->size==1)
            return div(b->nu[0]*b->sg,st);
        BigInteger*x=new BigInteger(2);
        int fp=b->absCompare(this,st);
        if(fp>=0){
            x->nu[0]=x->sg=fp;
            return x;
        }
        BigInteger *ans,*c,*d;
        rg int i,j,k,len=2,sz=size-st;
        x->size=2;
        int *bn=b->nu+b->size-2;
        k=digitCnt(bn[1]);
        double s=1.0/(bn[1]*p10[BIT-k]+bn[0]/p10[k]);
        while(s<1)s*=10;
        for(i=0;s<HEX;s*=10){
            i*=10;
            i+=(int)(s)%10;
        }
        x->nu[1]=i/p10[k-1];
        x->nu[0]=i%p10[k-1]*p10[BIT-k+1];
        k=FFT::changeN(sz-b->size);
        for(j=0;j<=k;j++,len<<=1){
            c=b->fmul(x);
            d=new BigInteger(x->size+b->size);
            d->size=x->size+b->size;
            for(i=0;c->nu[i]==0;i++)d->nu[i]=0;
            d->nu[i]=HEX-c->nu[i];
            for(i++;i<d->size;i++)
                d->nu[i]=HEX- c->nu[i] -1 ;
            d->nu[i-1]=(d->nu[i-1]+2)%HEX;
            eq(x,x->fmul(d));
            delete c;
            delete d;
            if(x->size>len)
                x->__moveNumber(x->size-len);
        }
        k=x->size - sz+b->size-1;
        if(k>0)
            x->__moveNumber(k);
        ans=x->fmul(this,st);
        delete x;
        if(ans->size > sz){
            ans->__moveNumber(sz);
            ans->sg=sg*b->sg;
            ans->selfAdd(ans->sg);
            x=b->fmul(ans);
            if(absCompare(x,st)==-1)
                ans->selfAdd(-1);
            delete x;
        }else{
            ans->size=1;
            ans->nu[0]=0;
            ans->sg=0;
        }
        return ans;
    }
    BigInteger* sqrtn(){//开n次根号,用牛顿迭代实现
        rg int i,k,n,next,len,len2,fp=sg,clen=(size+1)/2;
        if(is0())
            return clone();
        BigInteger *c=new BigInteger(1),*t,*s;
        c->size=c->sg=sg=1;
        if(size&1){
            c->nu[0]=(int)sqrt((double)nu[size-1]);
        }else{
            c->nu[0]=(int)sqrt((double)nu[size-1]*HEX+nu[size-2]);
        }
        for(len=1;len<=clen;len=len2){
            len2=len<<1;
            k=size-len2-c->size;
            t=fdiv(c,k<0?0:k);
            s=new BigInteger(t->size+1);
            n=t->size-c->size;
            for(i=next=0;i<n;i++)
                s->nu_push(t->nu[i]);
            for(;i<t->size;i++){
                k=t->nu[i]+c->nu[i-n]+next;
                s->nu_push(k%HEX);
                next=k/HEX;
            }
            if(next)
                s->nu_push(next);
            delete t;
            eq(c,s->div(2));
            delete s;
        }
        if(c->size>clen)
            c->__moveNumber(c->size-clen);
        c->sg=fp;
        return c;
    }
    BigInteger* pow(ll b){//低精度次方
        BigInteger*c=new BigInteger("1");
        BigInteger *a=clone();
        while(b){
            if(b&1)
                eq(c,c->fmul(a));
            b>>=1;
            eq(a,a->fmul(a));
        }
        delete a;
        return c;
    }
    inline void write(cint x){
        for(rg int i=BIT-1;i>=0;i--)
            putchar(x/p10[i]%10+'0');
    }
    void print(){//打印格式长度等于BIT
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
    bool issqrt(){
        if(is0())
            return 1;
        bint *a=sqrtn();
        bint *m=a->fmul(a);
        int ans=0;
        if(compare(m)==0){
            ans=1;
        }
        delete a;
        delete m;
        return ans;
    }
};
char str[110];
int main(int argc,char *argv[]){
    scanf("%s",str);
    bint *a=new bint(str);
    scanf("%s",str);
    bint *b=new bint(str);
    a->add(b)->println();
return 0;
}


