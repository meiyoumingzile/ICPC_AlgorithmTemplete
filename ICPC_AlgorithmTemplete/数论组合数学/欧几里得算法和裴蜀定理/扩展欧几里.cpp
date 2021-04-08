#include<bits/stdc++.h>
#define LL long long
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;

ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}

ll exgcd(ll a,ll b,ll &x,ll &y){
    if(!b){
        x=1;y=0;return a;
    }
    ll e=exgcd(b,a%b,x,y);
    ll kkz=x;x=y;y=kkz-a/b*y;
    return e;
}


struct v2{
    ll x,y;

    void sett(ll x,ll y){
        this->x=x;
        this->y=y;
    }
    bool operator == (const v2 &t){
         return (t.x==this->x&&t.y==this->y);
    }
};

v2 ex_gcd(ll a,ll b){//a,b不同时为0，扩展欧几里得,a,b要么同正要么同负才有效；
    v2 ans;
    if(b==0){
        ans.sett(1,0);
    }else{
        v2 next=ex_gcd(b,a%b);
        ans.x=next.y;
        ans.y=next.x-(a/b)*next.y;
    }
    return ans;
}

//利用扩展欧几里得找出1个解后，找左右的其他解
v2 getOther(v2 ans,ll a,ll b,ll t){//公示如下，t是任意整数
    ll gcdab=gcd(a,b);
    ans.x+=b/gcdab*t;
    ans.y-=a/gcdab*t;
    return ans;
}

int main(int argc,char *argv[]){
    //freopen("debug\\in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("debug\\out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//OJ上有的地方不能加这句话
    ll i,j,t,a,b,c,n2;
    printf("%lld\n",exgcd(6543,1611,a,b));
    while(1){
        scanf("%lld%lld",&a,&b);
        v2 ans=ex_gcd(a,b);
        printf("%lldx+%lldy==%lld\n",a,b,gcd(a,b));
        printf("%lld %lld\n",ans.x,ans.y);
        printf("输入一个t\n");
        while(~scanf("%lld",&t)){
            v2 ans1=getOther(ans,a,b,t);
            printf("第%lld个：%lld %lld\n",t,ans1.x,ans1.y);
        }
    }
return 0;
}
