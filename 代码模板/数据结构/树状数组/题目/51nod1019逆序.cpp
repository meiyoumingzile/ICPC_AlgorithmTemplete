#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;

struct BIT{
    int n;
    int tree[MAX];
    void init(int n){
        this->n=n;
        memset(tree,0,sizeof(tree));
    }
    int lowbit(int x){
        return x&(-x);
    }
    void add(int x,int y){//单点x下标增加y,x下标从1开始
        for(int i=x;i<=n;i+=lowbit(i))
            tree[i]+=y;
    }
    int getsum(int x){//得到前缀和
        int ans=0;
        if(x>0){
            for(int i=x;i;i-=lowbit(i))//i要大于0
                ans+=tree[i];
        }
        return ans;
    }
    int getsum(int x,int y){//得到区间[x,y]的和，x，y下标从1开始
        if(x>y)
            return 0;
        return getsum(y)-getsum(x-1);
    }
};

struct v2{
    int x,y;

    void sett(int x,int y){
        this->x=x;
        this->y=y;
    }
};
v2 A[MAX];
int rankk[MAX];
bool cmp1(const v2 &a,const v2 &b){
    return a.x < b.x;
}
bool cmp2(const v2 &a,const v2 &b){
    return a.y < b.y;
}
BIT bi;
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,n,cnt;
    cin>>n;
    for(i=0;i<n;i++){
        scanf("%d",&A[i].x);
        A[i].y=i+1;
    }
    sort(A,A+n,cmp1);
    for(i=1,rankk[0]=1;i<n;i++){
        rankk[i]=A[i-1].x==A[i].x?rankk[i-1]:rankk[i-1]+1;
    }
    for(i=0;i<n;i++){
        A[i].x=rankk[i];
    }
    sort(A,A+n,cmp2);

    bi.init(n);
    for(i=0,cnt=0;i<n;i++){
        bi.add(A[i].x,1);
        cnt+=i+1-bi.getsum(A[i].x);
    }
    printf("%d\n",cnt);

return 0;
}
/*
5 6
2 3 4 5 6
1 0 4

*/
