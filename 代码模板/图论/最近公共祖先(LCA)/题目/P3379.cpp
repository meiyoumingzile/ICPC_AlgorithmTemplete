#include<bits/stdc++.h>
using namespace std;
const int MAX=500010;
list<int>adList[MAX];//储存树,有向图
int V,E;//V个点
int h[MAX];//高度
int p[MAX][25];//p[u][i]节点u的向上走2^i步是哪个节点
int pLen[MAX];
inline  void dfsh(int now,int father){
    int k,j,next;
    for(list<int>::iterator i=adList[now].begin();i!=adList[now].end();++i){//等价于c++11语法 for(auto i: adList[now]){next=i;
        next=*i;
        if(next!=father){
            h[next]=h[now]+1;
            p[next][pLen[next]++]=now;
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
inline  void toSameh(int &c,int minh){
    int i,k;
    for(i=pLen[c]-1;i>=0&&h[p[c][i]]<minh;--i);//把它们深度相同
    c=p[c][i];
    if(h[c]>minh){
        toSameh(c,minh);
    }
}
inline  int toSameDot(int a,int b){
    if(a==b)
        return a;
    int i;
    for(i=0;i<pLen[a]-1&&p[a][i]!=p[b][i];++i);//由于深度相同
    --i;
    if(i==-1){
        return p[a][0];
    }
    return toSameDot(p[a][i],p[b][i]);
}
inline  int getLCA(int a,int b){
    int i,j,k;
    if(h[a]!=h[b]){//s深度调整相同
        int &c=h[a]>h[b]?a:b;//得到它们的引用
        toSameh(c,min(h[a],h[b]));
    }
    return toSameDot(a,b);
}
inline void init(int root){
    dfsh(root,0);//初始化高度和倍增数组,把1当做树根
}
int main(int argc,char *argv[]){
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
12 999 12
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
