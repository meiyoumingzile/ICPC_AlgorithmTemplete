#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
#define cdou const double &
#define cv2 const v2 &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=500010;
const int mod=1e9+7;
/*
�����p3379Ϊ����������������������������ѯm��LCA
*/
inline void scan(int &x){
    rg char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}
struct Edge{
    int e,val,k;
    Edge(){}
    Edge(const int &e,const int &val,const int &k){
        this->e=e;
        this->val=val;
        this->k=k;
    }
};
struct Graphic{
    int V,E,S,T,size=0;
    int head[MAX];
    Edge edge[MAX*2];
    void push(const int &b,const int &e,const int &val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
    }
	void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
};
struct Union{
    int father[MAX];
    int rank[MAX];
    void init(int n){
        for(int i=0;i<n;i++){
            father[i]=i;
            rank[i]=1;
        }
    }
    int GetFather(int son) {
        if(father[son]!=son)
            father[son]=GetFather(father[son]);
        return father[son];
    }
    void merge(int x, int y){//��ͨ�ϲ�����y���x���������ܽ��Ͳ�ѯЧ�ʣ����ǿ��Կ��Ƹ��ڵ����ĸ�
        father[y]=x;
    }
    bool isSameSet(int x, int y) {
        return GetFather(x)==GetFather(y);
    }
};
Union un;
Graphic g,li;
bool lcavis[MAX];
void tarjan(int now,int p){//������now�ǵ�ǰ���ĵ㣬un��һ�����鼯����
    for(int i=g.head[now];i!=-1;i=g.edge[i].k){
        cint e=g.edge[i].e;
        if(e!=p){
            tarjan(e,now);
            un.merge(now,e);//����ͨ���ӽ�next����now
            lcavis[e]=1;
        }
    }
    for(int i=li.head[now];i!=-1;i=li.edge[i].k){
        cint e=li.edge[i].e;
        if(lcavis[e]){
            //printf("(%d,%d)==%d\n",now,e,un.GetFather(e));//�ҵ�һ��lca,���Ҵ��val��
            li.edge[i].val=li.edge[i^1].val=un.GetFather(e);
        }
    }
}
int main(int argc,char *argv[]){
    int i,n,m,b,e,root;
    while(~scanf("%d%d%d",&g.V,&m,&root)){
        g.clear();
        li.clear();
        for(i=0;i<g.V-1;i++){
            scan(b);
            scan(e);
            g.push(b,e,0);
            g.push(e,b,0);
        }
        for(i=0;i<m;i++){
            scan(b);
            scan(e);
            li.push(b,e,0);
            li.push(e,b,0);
        }
        //һ����������tarjan��lca
        un.init(g.V+1);
        memset(lcavis,0,sizeof(lcavis));
        tarjan(root,-1);
        for(i=0;i<m;i++){
            printf("%d\n",li.edge[i*2].val);
        }
    }
return 0;
}
/*
5 5 4
3 1
2 4
5 1
1 4
2 4
3 2
3 5
1 2
4 5
*/
