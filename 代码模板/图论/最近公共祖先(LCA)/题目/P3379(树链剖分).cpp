#include<bits/stdc++.h>
using namespace std;
const int MAX=500010;

list<int>adList[MAX];//储存树,有向图
int V,E;//V个点
int sz[MAX],//子节点数目
p[MAX],//父节点编号
h[MAX],//高度
top[MAX];//所在重链顶端的重节点，如果本身不是重节点就是0
//bool isheavy[MAX];//子节点中重节点编号
int son[MAX];//子节点中，重节点编号
inline void dfsh(int now){
    int k=0,next,maxsz=-1;
    for(list<int>::iterator i=adList[now].begin();i!=adList[now].end();++i){//等价于c++11语法 for(auto i: adList[now]){next=i;
        next=*i;
        if(next!=p[now]){
            p[next]=now;
            h[next]=h[now]+1;
            dfsh(next);
            sz[now]+=sz[next]+1;
            if(maxsz<sz[next]){
                maxsz=sz[next];
                k=next;
            }
        }
    }
    son[now]=k;
}
inline void dfstop(int now){
    int next;
   // if(son[now]>0){//不是根，且是sz最大的
        top[son[now]]=top[now];//不许if判断如果now是叶子结点，son[now]==0
   // }
    for(list<int>::iterator i=adList[now].begin();i!=adList[now].end();++i){//等价于c++11语法 for(auto i: adList[now]){next=i;
        next=*i;
        if(next!=p[now]){
            dfstop(next);

        }
    }
}
inline int getLCA(int a,int b){
    while(1){
        if(top[a]==top[b])
            return h[a]<h[b]?a:b;
        else if(h[top[a]] > h[top[b]])
            a=p[top[a]];
        else
            b=p[top[b]];
    }
}
inline void init(int root){
    int i,k;
    for(i=1;i<=V;i++){//初始化p
        top[i]=i;//初始化top
    }
    dfsh(root);
    dfstop(root);
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,n,m,T,b,e,a,root,Q;
    scanf("%d%d%d",&V,&Q,&root);//V个点Q次查询
    for(i=1;i<V;i++){//V-1条边,保证输入是一棵树，且第一个数是第二个数的父节点
        scanf("%d%d",&b,&e);
        adList[b].push_back(e);
        adList[e].push_back(b);
    }
    init(root);
    for(i=0;i<Q;i++){//Q次查询
        scanf("%d%d",&a,&b);
        printf("%d\n",getLCA(a,b));
    }
return 0;
}

/*
16 999 8
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
