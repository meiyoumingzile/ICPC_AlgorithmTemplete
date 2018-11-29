#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=500010;
const int mod=1e9+7;
struct Edge {
    int b,e,val;
    void sett(int b,int e){
        this->b=b;
        this->e=e;
        this->val=0;
    }
};
vector<Edge>adList[MAX];//储存树,有向图
int V,E;//V个点
int sz[MAX],//子节点数目
p[MAX],//父节点编号
h[MAX],//高度
top[MAX];//所在重链顶端的重节点，如果本身不是重节点就是0
bool isheavy[MAX];//子节点中重节点编号

void dfsh(int now){
    int i,next;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        h[next]=h[now]+1;
        dfsh(next);
        sz[now]+=sz[next]+1;
    }
}
void dfstop(int now){
    int i,next,maxSz=0,k=0;
    for(i=0;i<adList[now].size();i++){//标记isheavy数组
        next=adList[now][i].e;
        if(maxSz<sz[next]){
            maxSz=sz[next];
            k=next;
        }
    }
    isheavy[k]=1;
    if(isheavy[now]){
        top[k]=top[now];
    }
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        dfsh(next);
    }
}
inline int getLCA(int a,int b){
    while(1){
        if(top[a]==top[b])
            return h[a]<h[b]?a:b;
        else if(h[top[a]]>h[top[b]])
            a=p[top[a]];
        else
            b=p[top[b]];
    }
}
void init(){
    int i,k,j,root;
    for(i=1;i<=V;i++){//初始化p
        top[i]=i;//初始化top
        for(j=0;j<adList[i].size();j++){
            k=adList[i][j].e;
            p[k]=i;
        }
    }
    for(i=1;i<=V;i++){//寻找根
        if(p[i]==0){
            root=i;
            break;
        }
    }
    //printf("%d\n",root);
    dfsh(root);//初始化高度和倍增数组
    dfstop(root);
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,n,m,T,b,e,a,root,Q;
    Edge edge;
    scanf("%d%d",&V,&Q);//V个点Q次查询
    for(i=1;i<V;i++){//V-1条边,保证输入是一棵树，且第一个数是第二个数的父节点
        scanf("%d%d",&b,&e);
        edge.sett(b,e);
        adList[b].push_back(edge);
    }
    init();
    for(i=0;i<Q;i++){//Q次查询
        scanf("%d%d",&a,&b);
        printf("LCA:%d\n",getLCA(a,b));
    }
return 0;
}

/*
16 999
8 5
8 4
8 1
5 9
4 6
4 10
1 14
1 13
6 15
6 7
10 11
10 16
10 2
16 3
16 12

*/
