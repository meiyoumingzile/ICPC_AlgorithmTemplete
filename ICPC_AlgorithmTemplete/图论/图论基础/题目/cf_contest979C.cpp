#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=300010;
const int mod=1e9+7;


vector<int>adList[MAX];//储存树
int V,E,y,x;//V个点
int seq[MAX];
bool seqvis[MAX];
bool vis[MAX];
void dfs1(int now,int p,int step){
    int i,next;
    seq[step]=now;
    if(now==y){
        for(i=0;i<=step;i++){
            seqvis[seq[i]]=1;
        }
        return ;
    }
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i];
        if(next!=p){
            dfs1(next,now,step+1);
        }
    }
}

void dfs2(int now,int p,int &cnt){
    int i,next;
    cnt++;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i];
        if(next!=p&&seqvis[next]==0){
            dfs2(next,now,cnt);
        }
    }
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int a,b,i,j,c1=0,c2=0;
    scanf("%d%d%d",&V,&x,&y);
    for(i=0;i<V-1;i++){
        scanf("%d%d",&a,&b);
        adList[a].push_back(b);
        adList[b].push_back(a);
    }
    dfs1(x,0,0);
    dfs2(x,0,c1);
    dfs2(y,0,c2);
    ll ans=(ll)V*(ll)(V-1)-(ll)c1*(ll)c2;
    printf("%lld\n",ans);
return 0;
}

