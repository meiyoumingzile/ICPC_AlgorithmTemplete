#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=10010;
const int mod=1e9+7;

char str[MAX];

#define BIT 10//位数，代表10^bit进制数;
ll p10[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000,100000000000};
const ll HEX=p10[BIT];
struct BigInteger{//不可变类型
    int sign;
    vector<ll>number;
    BigInteger(){
        number.reserve(MAX);//提前预申请空间避免到达vector默认上限
    }
    BigInteger(char*s,int sign){
        number.reserve(MAX);
        init(s,sign);
    }
    BigInteger(ll s){
        init(s);
    }
    void init(char*s,int sign){//s不能有符号,1代表正数
        ll c=0;
        int i,j=0,len;
        len=strlen(s);
        for(i=len-1;i>=0;i--){
            if(j<BIT){
                c+=p10[j++]*(s[i]-'0');
            }else{
                number.push_back(c);
                j=0;
                c=p10[j++]*(s[i]-'0');
            }
        }
        number.push_back(c);
        this->sign=sign;
    }

    void init(ll s){
        sign=0;
        if(s<0){
            sign=-1;
            s=-s;
        }else if(s>0){
            sign=1;
        }
        while(s){
            number.push_back(s%HEX);
            s/=HEX;
        }
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

    int absCompare(BigInteger *b){
        int l1=number.size(),l2=b->number.size();
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
    BigInteger* absAdd(BigInteger *b){
        BigInteger *c=new BigInteger();
        ll i,j,k,next=0;
        if(number.size()>b->number.size()){
            for(i=0;i<b->number.size();i++){
                k=number[i]+b->number[i]+next;
                next=k/HEX;
                c->number.push_back(k%HEX);
            }
            for(;i<number.size();i++){
                k=number[i]+next;
                next=k/HEX;
                c->number.push_back(k%HEX);
            }
            if(next){
                c->number.push_back(next);
            }
        }else{
            for(i=0;i<number.size();i++){
                k=number[i]+b->number[i]+next;
                next=k/HEX;
                c->number.push_back(k%HEX);
            }
            for(;i<b->number.size();i++){
                k=b->number[i]+next;
                next=k/HEX;
                c->number.push_back(k%HEX);
            }
            if(next){
                c->number.push_back(next);
            }
        }
        return c;
    }
    void push(BigInteger *c,ll k,ll &cnt,ll &next){
        k<0?(k+=HEX,next=1):next=0;
        if(k){
            for(;cnt;cnt--){
                c->number.push_back(0);
            }
            c->number.push_back(k);
        }else{
            cnt++;
        }
    }
    BigInteger* absSub(BigInteger *b){
        BigInteger *c=new BigInteger();
        ll i,j,k,next=0,cnt=0;
        c->sign=this->absCompare(b);
        if(c->sign==1){
            for(i=0;i<b->number.size();i++){
                k=number[i]-b->number[i]-next;
                push(c,k,cnt,next);
            }
            for(;i<number.size();i++){
                k=number[i]-next;
                push(c,k,cnt,next);
            }
        }else{
            for(i=0;i<number.size();i++){
                k=b->number[i]-number[i]-next;
                push(c,k,cnt,next);
            }
            for(;i<b->number.size();i++){
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
    BigInteger* mul(BigInteger *b){//FFT的题，以后再说，我把FFT模块写好
        BigInteger *c;
        c->sign=sign*b->sign;

        return c;
    }

    void println(){//打印格式长度等于BIT
        if(sign==0){
            printf("0\n");
            return;
        }
        if(sign==-1)
            printf("-");
        printf("%lld",number[number.size()-1]);
        for(int i=number.size()-2;i>=0;i--){
            printf("%010lld",number[i]);
        }printf("\n");
    }
};


int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k;
    cin>>str;
    BigInteger *a=new BigInteger(str,1);
    cin>>str;
    BigInteger *b=new BigInteger(str,1);
    //a->println();
    //b->println();

    a->sub(b)->println();
return 0;
}
