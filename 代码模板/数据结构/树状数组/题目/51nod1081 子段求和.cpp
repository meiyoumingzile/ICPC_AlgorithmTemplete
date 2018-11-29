#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;

ll tree[MAX];
int N,Q;
int lowbit(int x){
    return x&(-x);
}
void update(int x,ll y){
    for(int i=x;i<=N;i+=lowbit(i)){
        tree[i]+=y;
    }
}
ll getSum(int x){
    ll sum=0;
    for(int i=x;i;i-=lowbit(i)){
        sum+=tree[i];
    }
    return sum;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,len;
    ll a,b,c;
    cin>>N;
    for(i=0;i<N;i++){
        scanf("%lld",&a);
        update(i+1,a);
    }
    cin>>Q;
    for(i=0;i<N;i++){
        scanf("%d%d",&j,&len);
        printf("%lld\n",getSum(j+len-1)-getSum(j-1));
    }
return 0;
}

