/*
邻接表,
有向树，
数组实现，
*/
#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=10010;
const int mod=1e9+7;

vector<int>adList[MAX];//储存树,有向图
int V,E;//V个点
int h[MAX];//高度
int p[MAX][15];//p[u][i]节点u的向上走2^i步是哪个节点
int pLen[MAX];

int dfs_seq[500001];
int dfs_seq_i=0;
void dfsh(int now,int pre){
    int i,j,k,next;
    dfs_seq[now]=dfs_seq_i++;
    for(auto next : adList[now]){
        if(pre!=next){
            h[next]=h[now]+1;
            for(j=0;;j++){//更新倍增数组
                k=p[next][j];
                if(pLen[k]>j){
                    p[next][pLen[next]++]=p[k][j];
                }else{
                    break;
                }
            }
            dfsh(next,now);
        }
    }
}
void toSameh(int &c,int minh){
    int i,k;
    for(i=0;i<pLen[c]&&h[p[c][i]]>=minh;i++);//把它们深度相同
    i--;
    c=p[c][i];
    if(h[c]>minh){
        toSameh(c,minh);
    }
}
int toSameDot(int a,int b){
    if(a==b)
        return a;
    int i;
    for(i=0;i<pLen[a]&&p[a][i]!=p[b][i];i++);//由于深度相同
    i--;
    if(i==-1){
        return p[a][0];
    }
    return toSameDot(p[a][i],p[b][i]);
}

int getLCA(int a,int b){
    int i,j,k;
    if(h[a]!=h[b]){//第一步把深度较小的点搬到根节点
        int &c=h[a]>h[b]?a:b;//得到它们的引用
        toSameh(c,min(h[a],h[b]));
    }
    return toSameDot(a,b);
}

void init(int V,int root){//bfs初始化
    queue<int>que;
    que.push(root);
    while(!que.empty()){
        int now=que.front();
        que.pop();
        for(auto next : adList[now]){
            if(p[now][0]!=next){
                p[next][pLen[next]++]=now;
                que.push(next);
            }
        }
    }
    h[1]=1;
    dfsh(root,-1);//初始化高度和倍增数组
}

int main(int argc,char *argv[]){
    int i,j,k,n,m,T,b,e,a,root,Q;
    scanf("%d%d",&V,&Q);//V个点Q次查询
    for(i=1;i<V;i++){//V-1条边,保证输入是一棵树，且第一个数是第二个数的父节点
        scanf("%d%d",&b,&e);
        adList[b].push_back(e);
    }
    init(V,1);
    for(i=0;i<Q;i++){//Q次查询
        scanf("%d%d",&a,&b);
        printf("LCA:%d\n",getLCA(a,b));
    }
return 0;
}
/*
12 999
1 2
1 3
1 4
3 5
3 6
6 7
12 1
4 8
8 11
2 9
9 10
*/
