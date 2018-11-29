/*

邻接表,
有向树，
vector实现，


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
int h[MAX];//高度
vector<int>p[MAX];//p[u][i]节点u的向上走2^i步是哪个节点
void printp(){
    int i,j;
    for(i=1;i<=V;i++){
        printf("%d:",p[i].size());
        for(j=0;j<p[i].size();j++){
            printf("%d ",p[i][j]);
        }printf("\n");
    }
}
void dfsh(int now){//优化常数，传参尽可能少，不要传深度
    int i,j,k,next;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        h[next]=h[now]+1;
        for(j=0;;j++){//更新倍增数组
            k=p[next][j];
            if(p[k].size()>j){
                p[next].push_back(p[k][j]);
            }else{
                break;
            }
        }
        dfsh(next,deep+1);
    }
}
void toSameh(int &c,int minh){
    int i,k;
    for(i=0;i<p[c].size()&&h[p[c][i]]>=minh;i++);//把它们深度相同
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
    for(i=0;i<p[a].size()&&p[a][i]!=p[b][i];i++);//由于深度相同
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
void init(){
    int i,k,j,root;
    for(i=1;i<=V;i++){//初始化倍增数组
        p[i].reserve(25);
        for(j=0;j<adList[i].size();j++){
            p[adList[i][j].e].push_back(i);//e节点的2^0的步数是b
        }
    }
    for(i=1;i<=V;i++){//寻找根
        if(p[i].size()==0){
            root=i;
            break;
        }
    }
    printf("%d\n",root);
    dfsh(root,0);//初始化高度和倍增数组
    printp();
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
