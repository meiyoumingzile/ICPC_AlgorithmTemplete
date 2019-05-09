#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=10010;
const int mod=1e9+7;

namespace NTT{
    const int P=998244353;
    ll powg[MAX];
    const int p2[30]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216};
    const int grn[30]={1,998244352,911660635,372528824,929031873,452798380,922799308,781712469,476477967,166035806,258648936,584193783,63912897,350007156,666702199,968855178,629671588,24514907,996173970,363395222,565042129,733596141};
    const int grninv[30]={1,998244352,86583718,509520358,337190230,87557064,609441965,135236158,304459705,685443576,381598368,335559352,129292727,358024708,814576206,708402881,283043518,3707709,121392023,704923114,950391366,428961804};
    inline ll quickmi(ll a,ll b,ll P){
        ll ans=1;
        for(a%=P;b;b>>=1,a=a*a%P)
            if(b&1)
                ans=ans*a%P;
        return ans;
    }
    inline ll changeN(ll N){//把N变成2的整数次方，并且生成序列,返回p2数组的下标
        ll i;
        for(i=0;p2[i]<N;i++);
        return i;
    }
    inline void ntt(ll *F,int ni,int fp,int xlen){//把原本数组变换
        register int i,j,m,k,bit,N=p2[ni],n=N>>1;
        register ll d,inv,G;
        ll *temp,*p,*q;
        for(i=0,j=0;i<N;++i){
            if(i<j) swap(F[i],F[j]);
            for(k=n;(j^=k)<k;k>>=1);
        }
        powg[0]=1;
        bit=1;
        for(m=1;m<N;m=n){
            n=m<<1;
            G=fp==1?grn[bit]:grninv[bit];
            for(i=1;i<m;++i)//提前预处理加速
                powg[i]=powg[i-1]*G%P;
            for(i=0;i<N;i+=n){
                p=F+i;
                q=F+i+m;//得到前一半和后一半地址
                for(j=0;j<m;++j){
                    d=q[j]*powg[j]%P;
                    q[j]=(p[j]-d+P)%P;
                    p[j]=(p[j]+d)%P;
                }
            }
            ++bit;
        }
        if(fp==-1){
            ll invN=quickmi(N,P-2,P);
            for(i=0;i<N;++i)
                F[i]=F[i]*invN%P;
        }
    }
    //x长度必须是2的整数倍,ni是2的多少次幂，N=p2[ni]表示x数组要FFT的长度, fp是-1表示逆变换， xlen是x有效长度不够补0，up新数组长度
    inline ll *ntt(const ll *x,int ni,int fp,int xlen,int up){
        ll *F=new ll[up];
        memcpy(F,x,sizeof(ll)*xlen);
        memset(F+xlen,0,sizeof(ll)*(p2[ni]-xlen));
        ntt(F,ni,fp,xlen);
        return F;
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
    void __moveNumber(int n){
        size-=n;
        ll *x=new ll[size];
        memcpy(x,number+n,sizeof(ll)*size);
        delete []number;
        number=x;//number是个数组
       // number+=n;
    }
    BigInteger* clone(int up=MAX){
        BigInteger *c=new BigInteger(up);
        memcpy(c->number,number,sizeof(ll)*size);
        c->sign=sign;
        c->size=size;
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
        k<0?(k+=HEX,next=1):next=0;//借位
        if(k){
            int i=c->size;
            for(;cnt;cnt--){
                c->number[i++]=0;
            }
            c->number[i++]=k;
            c->size=i;
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
    BigInteger* nttmul(BigInteger *b){//NTT实现
        BigInteger *c=new BigInteger(1);
        c->sign=sign*b->sign;
        ll i,ni,len,N,next=0,up;
        len=size+b->size-1;
        ni=NTT::changeN(len);
        N=NTT::p2[ni];
        up=N+10;
        ll *F1=NTT::ntt(number,ni,1,size,up);
        ll *F2=NTT::ntt(b->number,ni,1,b->size,up);
        for(i=0;i<N;i++){
            F1[i]*=F2[i];
        }
        NTT::ntt(F1,ni,-1,N);
        ll *x=F1;
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
        delete []F2;
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
        while(c->size>1&&!c->number[c->size-1])
            c->size--;
        if(c->size==1&&c->number[0]==0)
            c->sign=0;
        return c;
    }
    BigInteger *__binDivcal(BigInteger *b,int st,ll &d){//返回小于等于number的b的倍数的数，st是number第几位开始，d是得到的商，采用二分法
        ll i,f,be=1,ed=HEX-1,mid;
        while(be<=ed){
            mid=(be+ed)/2;
            BigInteger *c=new BigInteger();
            b->selfMul(mid,c);
            f=absCompare(c,st);
            if(f==0){
                d=mid;
                return c;
            }else if(f>0){
                be=mid+1;
            }else{
                ed=mid-1;
            }
            delete c;
        }
        d=ed;
        BigInteger *c=new BigInteger();
        b->selfMul(d,c);
        return c;
    }
    BigInteger* div(BigInteger *b){//大数除法，时间是logHEX*lena*lenb
        if(b->sign==0)
            return NULL;
        BigInteger *a=clone();
        if(b->compare(1)==0||b->compare(-1)==0){//是1返回自身复制
            a->sign=b->sign*sign;
            return a;
        }
        BigInteger *c=new BigInteger("0");
        ll ai,i,j,h,k,next,cnt0,d;
        h=size - b->size;
        if(is0()||h<0)
            return c;
        c->sign=b->sign*sign;
        c->size=h+1;
        for(i=h;i>=0;i--){
            if(a->absCompare(b,i)==-1){
                c->number[i]=0;
            }else{
                BigInteger *tem=a->__binDivcal(b,i,d);
                for(j=cnt0=next=0,ai=i;j<tem->size;j++){//减法
                    k=a->number[j+i]-tem->number[j]-next;
                    k<0?(k+=HEX,next=1):next=0;//借位
                    if(k){
                        for(;cnt0;cnt0--)
                            a->number[ai++]=0;
                        a->number[ai++]=k;
                    }else{
                        cnt0++;
                    }
                }
                a->size=ai;
                delete tem;
                c->number[i]=d;
            }
        }
        delete a;
        while(c->size>1&&!c->number[c->size-1])
            c->size--;
        if(c->size==1&&c->number[0]==0)
            c->sign=0;
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
    BigInteger*mod(BigInteger *b){//b小于HEX
        if(!b||b->is0()||b->compare(1)==0){
            return new BigInteger("0");
        }else if(b->compare(2)==0){
            return new BigInteger(number[0]%2);
        }
        ll ai,i,j,h,k,next,cnt0,d;
        h=size - b->size;
        BigInteger *a=clone();
        for(i=h;i>=0;i--){
            if(a->absCompare(b,i)>=0){
                BigInteger *tem=a->__binDivcal(b,i,d);
                for(j=cnt0=next=0,ai=i;j<tem->size;j++){//减法
                    k=a->number[j+i]-tem->number[j]-next;
                    k<0?(k+=HEX,next=1):next=0;//借位
                    if(k){
                        for(;cnt0;cnt0--)
                            a->number[ai++]=0;
                        a->number[ai++]=k;
                    }else{
                        cnt0++;
                    }
                }
                a->size=ai;
                delete tem;
            }
        }
        a->sign=sign*b->sign;
        return a;
    }
    BigInteger* nttdiv(BigInteger* b){//牛顿迭代求除法,恰好整除如34/17=1算作没整除，有这种情况请特判
        BigInteger*c=new BigInteger(1);
        BigInteger*temp,*ans,*d1,*d2;
        int i,j,t,k,next,clen,dightCnt=b->size;
        c->size=1;
        c->number[0]=b->number[b->size-1]+1;
        if(c->number[0]==HEX){
            c->number[0]=1;
            dightCnt++;
        }else{
            c->number[0]=HEX/c->number[0]+1;
        }
        clen=size+1;
        for(t=0;t<18;t++){
            d1=b->nttmul(c);
            d2=new BigInteger(dightCnt+1);
            d2->size=dightCnt+1;
            d2->number[0]=HEX-d1->number[0];
            for(i=1;i<d1->size;i++)
                d2->number[i]=HEX- d1->number[i] -1 ;
            for(;i<d2->size;i++)
                d2->number[i]=HEX-1;
            d2->number[dightCnt]=(d2->number[dightCnt]+2)%HEX;
            temp=c;
            c=c->nttmul(d2);
            delete temp,d1,d2;
            dightCnt<<=1;
            if(dightCnt>clen){
                k=clen-dightCnt+c->size;
                dightCnt=clen;
                if(c->size>k){
                    c->__moveNumber(c->size -k);
                }
            }
        }
        ans=nttmul(c);
        delete c;
        if(ans->size>clen){
            ans->__moveNumber(clen);
            ans->sign=sign*b->sign;
        }else{
            ans->size=1;
            ans->number[0]=0;
            ans->sign=0;
        }
        return ans;
    }
    BigInteger* nttmod(BigInteger *b,BigInteger *d){//b是被除数，d是除法结果
        if(!b||b->is0()||b->compare(1)==0){
            return new BigInteger("0");
        }else if(b->compare(2)==0){
            return new BigInteger(number[0]%2);
        }
        BigInteger *c,*ans;
        c=d->nttmul(b);
        ans=absSub(c);
        ans->sign=1;
        delete c;
        return ans;
    }
    BigInteger* pow(ll b){//低精度次方
        BigInteger*ans=new BigInteger("1");
        BigInteger *t,*a=this;
        if(b&1){
            t=ans;
            ans=ans->nttmul(a);
            delete t;
        }
        b>>=1;
        a=a->nttmul(this);
        while(b){
            if(b&1){
                t=ans;
                ans=ans->nttmul(a);
                delete t;
            }
            b>>=1;
            t=a;
            a=a->nttmul(a);
            delete t;
        }
        delete a;
        return ans;
    }
    BigInteger *pow(BigInteger* b){
        BigInteger*ans=new BigInteger("1");
        BigInteger *t,*a=this;
        if(b->mod(2)){
            t=ans;
            ans=ans->nttmul(a);
            delete t;
        }
        t=b;
        b=b->div(2);
        delete t;
        a=a->nttmul(this);
        while(!b->is0()){
            if(b->mod(2)){
                t=ans;
                ans=ans->nttmul(a);
                delete t;
            }
            t=b;
            b=b->div(2);
            delete t;
            t=a;
            a=a->nttmul(a);
            delete t;
        }
        return ans;
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

BigInteger *pow(ll a,ll n){
    BigInteger *b=new BigInteger(a);
    BigInteger *ans= b->pow(n);
    delete b;
    return ans;
}
void ass(BigInteger *&ans,BigInteger *b,BigInteger *a=NULL){//传入一个指针的引用
    delete ans;
    ans=b;
    if(a!=NULL)
        delete a;
}
BigInteger * mapp[31][31];
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	ll i,j,k,T,N,C,n,m;
	BigInteger *a,*temp;
    for(i=0;i<31;i++){
        for(j=0;j<31;j++){
            mapp[i][j]=NULL;
        }
    }
    while(~scanf("%lld%lld",&N,&C)){
        if(mapp[N][C]!=NULL){
            mapp[N][C]->println();
            continue;
        }else if(C==1){
            printf("1\n");
            continue;
        }
        n=N*N;
        m=N/2;

        //旋转
        BigInteger *ans=pow(C,n);//90 270
        if(N&1){//90
            a=pow(C,1+m*m+m);
        }else{
            a=pow(C,m*m);
        }
        a->selfMul(2,a);
        ass(ans,ans->add(a),a);

        a=pow(C,n/2+n%2);//180
        ass(ans,ans->add(a),a);

        //翻折
        if(N&1){//水平竖直
            a=pow(C,(n+N)/2);
        }else{
            a=pow(C,n/2);
        }
        a->selfMul(2,a);
        ass(ans,ans->add(a),a);

        a=pow(C,N*(N+1)/2);
        a->selfMul(2,a);
        ass(ans,ans->add(a),a);

        ass(ans,ans->div((ll)8));
        mapp[N][C]=ans;
        ans->println();
    }
return 0;
}
