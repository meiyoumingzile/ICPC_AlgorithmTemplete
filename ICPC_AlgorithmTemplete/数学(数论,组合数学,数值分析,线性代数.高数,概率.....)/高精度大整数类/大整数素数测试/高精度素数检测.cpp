#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
#define ll long long
const int MAX=100010;
#define BIT 1//压位
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
    void __push(BigInteger *c,ll k,ll &cnt,ll &next){
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
    BigInteger* absSub(BigInteger *b){//绝对值相减
        BigInteger *c=new BigInteger();
        ll i,j,k,next=0,cnt=0;
        c->sign=this->absCompare(b);
        if(c->sign==1){
            for(i=0;i<b->size;i++){
                k=number[i]-b->number[i]-next;
                __push(c,k,cnt,next);
            }
            for(;i<size;i++){
                k=number[i]-next;
                __push(c,k,cnt,next);
            }
        }else{
            for(i=0;i<size;i++){
                k=b->number[i]-number[i]-next;
                __push(c,k,cnt,next);
            }
            for(;i<b->size;i++){
                k=b->number[i]-next;
                __push(c,k,cnt,next);
            }
        }
        return c;
    }
    void selfAbsAdd(ll b){
        b=abs(b);
        number[0]+=b;
        ll i,next=0;
        for(i=0;i<size;i++){
            number[i]+=next;
            next=number[i]/HEX;
            number[i]%=HEX;
        }
        if(next)
            number_push(next);
    }
    void selfAbsSub(ll b,int com){//com代表大小
        b=abs(b);
        if(com==1){
            number[0]-=b;
            ll i,next=0;
            for(i=0;i<size;i++){
                number[i]-=next;
                if(number[i]<0){
                    number[i]+=HEX;
                    next=1;
                }
            }
            for(;!number[size-1];size--);
        }else{
            number[0]=b-number[0];
        }
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
    void selfAdd(ll b){//自加，b小于HEX
        if(b==0)
            return;
        int signb,i,j,s,k;
        signb=b>0?1:-1;
        b=abs(b);
        if(sign==0){
            sign=signb;
            number[0]=b;
        }else if(signb==sign){
            selfAbsAdd(b);
        }else{
            s=sign;
            sign=1;
            k=compare(b);
            if(k==0){
                sign=0;
                size=1;
                number[0]=0;
            }else{
                selfAbsSub(b,k);
                sign=k==1?s:signb;
            }
        }
    }
    void selfSub(ll b){//自减，b小于HEX
        if(b==0)
            return;
        int signb,i,j,s,k;
        signb=b>0?1:-1;
        b=abs(b);
        if(sign==0){
            sign=-signb;
            number[0]=b;
        }else if(signb==sign){
            s=sign;
            sign=1;
            k=compare(b);
            if(k==0){
                sign=0;
                size=1;
                number[0]=0;
            }else{
                selfAbsSub(b,k);
                sign=k==1?s:-signb;
            }
        }else{
            selfAbsAdd(b);
        }
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
    BigInteger* mul(BigInteger *b){
        BigInteger *c=new BigInteger();
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
    void mul(ll b,BigInteger* c){//b小于HEX,C是结果
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

    BigInteger* div(ll b){//b<HEX
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
    BigInteger *bin(BigInteger *a,BigInteger *b,int st,ll &d){//a是要比较的数，b是被除数,st是10^st次方，d是位数
        ll i,j,k,be=1,ed=HEX-1,mid;
        while(be<=ed){
            mid=(be+ed)/2;
            BigInteger *c=new BigInteger();
            b->mul(mid,c);
            k=a->absCompare(c,st);
            if(k==0){
                d=mid;
                return c;
            }else if(k>0){
                be=mid+1;
            }else{
                ed=mid-1;
            }
            delete c;
        }
        d=ed;
        BigInteger *c=new BigInteger();
        b->mul(d,c);
        return c;
    }
    BigInteger* div(BigInteger *b){//大数除法，时间是logHEX*lena*lenb
        if(b->sign==0)
            return NULL;
        if(is0())
            return clone();
        BigInteger *c=new BigInteger((ll)0);
        BigInteger *ans=clone();
        c->sign=b->sign*sign;
        ll i,j,h,k,next=0;
        h=size - b->size;
        for(i=absCompare(b,h)<0?h-1:h;i>=0;i--){//首位不能商0因此要判断一下
            BigInteger *tem=bin(ans,b,i,k);
            for(j=ans->size-1-i;j>=0;j--){
                next=
            }
            c->number[i]=k;
        }
        while(c->size>0&&!c->number[c->size-1]){
            if(c->size)
                c->size--;
        }
        delete ans;
        return c;
    }
    ll mod(ll b){//b小于HEX
        if(b<2){
            return 0;
        }else if(b==2){
            return number[0]%2;
        }
        ll m=0,i;
        for(i=size-1;i>=0;i--)
            m=(number[i]+m*HEX)%b;
        return sign*m;
    }
    BigInteger *pow(BigInteger* b,BigInteger* m){
        BigInteger *c=new BigInteger((ll)0);
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

struct PRIME{
    const int MT=5;
    bool vis[MAX];
    int prime[MAX];
    int pCount;
    int init(int n){
        memset(vis,1,sizeof(vis));
        int i,j,primeCount=0;
        for(i=2;i<n;i++){
            if(vis[i]){
                prime[primeCount++]=i;
            }
            for(j=0;i*prime[j]<n;j++){
                vis[i*prime[j]]=false;
                if(i%prime[j]==0){
                    break;
                }
            }
        }
        pCount=primeCount;
        return primeCount;
    }
    ll quickmi(ll a,ll b,ll mod){//最短写法
        ll ans=1;
        for(a%=mod;b;b>>=1,a=a*a%mod){
            if(b&1)
                ans=ans*a%mod;
        }
        return ans;
    }
    int TwiceDetect(ll a, ll b, ll k) {
        int t = 0;
        ll x, y;
        while ((b & 1) == 0) {
            b >>= 1;
            t++;
        }
        y = x = quickmi(a, b, k);
        while (t--) {
            y =x*x%k;
            if (y == 1 && x != 1 && x != k - 1)///注意y!=1的时候是不做判断的,即对应
                return 0;///递归时在某一环节x==p-1的情况,对此x开方则无意义,但是迭代的话不能break,只能ignore并继续.
            x = y;///继续向高次迭代,那么至少最后一次应该是等于1的(Fermat小定理)
        }
        return y;
    }

    int isPrime(ll n) {
        if(n<=1){
            return -1;
        }else if(n&1==0){
            return 0;
        }
        int i;
        ll tmp;
        for (i=0;i<MT;i++){//测试次数
            tmp=prime[i];
            if(n==prime[i]) return 1;
            if(TwiceDetect(tmp, n - 1, n) != 1)
                break;
        }
        return (i == MT);
    }
};
PRIME pr;//一定要声明全局的
char str[10000];
int main(int argc,char *argv[]){
    int n,i;
    scanf("%s",str);
    BigInteger *a=new BigInteger(str);
    BigInteger *c=new BigInteger("22222222222222");
    a->mul(5,c);
    a->println();
    c->println();
   // printf("%lld\n",a->mul(5,a));
return 0;
}
