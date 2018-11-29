#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<map>
#include<bitset>
using namespace std;
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LL long long
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;

ll exgcd(ll a,ll b,ll &x,ll &y){  //另一种写法，返回最大公约数
    if(!b){
        x=1;y=0;return a;
    }
    int e=exgcd(b,a%b,x,y);
    int kkz=x;x=y;y=kkz-a/b*y;
    return e;
}

int main(int argc,char *argv[]){//这道题代码好长，是我第一次写的
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//OJ上有的地方不能加这句话
    ll i,j,k,a,b,c,ans,n2,x,y,g,dm;
    while(scanf("%lld%lld%lld%lld",&a,&b,&c,&k),a|b|c|k){//这里用|运算符判断0
        n2=(ll)1<<k;
        if(a==b){
            ans=0;
        }else{
            x=0;y=0;
            g=exgcd(n2,c,x,y);
            if((b-a)%g!=0){
                printf("FOREVER\n",ans);
                continue;
            }
            dm=n2/g;
            /*解释
            首先,y是扩展欧几里得ax+by=gcd;的一个解，那么y*(b-a)/g就应该是ax+by=c这个方程的解
            b/g可以调整x的结果，a/g可以调整y结果
            本题中n2*x+c*y=b-a;
            而本题中，y是想要的，题目中的dm=n2/gcd(a,b),可以调整结果，
            而本题要找和0最近的且是正的，就先%dm一下，变成0左右的，
            +dm是因为如果是负的就加到第一个正的
            但原本就是正的时候就又多了，就要再%dm一下
            所以一下这么写，很好的把很多情况合并，比如b-a大于还是小于0
            */
            ans=((y*(b-a)/g%dm)+dm)%dm;
        }
        printf("%lld\n",ans);
    }
return 0;
}
