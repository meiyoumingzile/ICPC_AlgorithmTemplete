#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

int tree[MAX],A[MAX];
int N,Q;
int lowbit(int x){
    return x&(-x);
}

void update(int x,int y){
    for(int i=x;i<=N;i+=lowbit(i)){
        tree[i]=max(y,tree[i]);
    }
}

int getMax(int l,int r){//查询[l,r]最值
    int ans=0;
    while(1){
         ans = max(A[r],ans);
         if(r==l) break;
         for(r--; r-lowbit(r)>=l; r -= lowbit(r))
             ans =max(ans,tree[r]);
    }
    return ans;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,a,b;
    cin>>N;
    for(i=1;i<=N;i++){
        scanf("%d",&A[i]);
        update(i,A[i]);
    }
    cin>>Q;
    for(i=0;i<Q;i++){
        scanf("%d%d",&a,&b);
        printf("%d\n",getMax(a+1,b+1));
    }
return 0;
}
