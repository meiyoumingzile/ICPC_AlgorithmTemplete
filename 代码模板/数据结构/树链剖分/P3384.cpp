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
const int MAX=100010;
const int mod=1e9+7;
int P;
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
    int V,E,S,T,size;
    int head[MAX];
    Edge edge[MAX*2];
    Graphic(){}
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
Graphic g;//储存树
ll val[MAX];//点权值

struct Node{
    int r,l;
    ll sum,lz;
    void addlz(ll a){
        lz=(lz+a)%P;
    }
    void addsum(ll a){
        sum=(sum+a*(r-l)%P)%P;
    }
};
struct LineTree{//区间是左闭 左开[)
    Node tree[MAX*4];
    void mergeSon(cint now){
        tree[now].sum=(tree[now*2].sum+tree[now*2+1].sum)%P;
    }
    void buildTree(int now,ll *b,int l,int r){//建树
        tree[now].l=l;
        tree[now].r=r;
        tree[now].lz=0;
        if(r-l==1){
            tree[now].sum=b[l]%P;
            return;
        }
        int mid=(l+r)/2,next=now*2;
        buildTree(next,b,l,mid);
        buildTree(next+1,b,mid,r);
        mergeSon(now);
    }

    void downLz(cint now){
        cint next=now*2;
        if(tree[now].lz!=0){
            tree[next].addlz(tree[now].lz);
            tree[next+1].addlz(tree[now].lz);
            tree[next].addsum(tree[now].lz);
            tree[next+1].addsum(tree[now].lz);
        }
        tree[now].lz=0;
    }
    void add(int now,int l,int r,ll a){
        Node &t=tree[now];
        const int mid=(t.r+t.l)/2,next=now*2;
        if(t.l==l&&t.r==r){
            t.addlz(a);
            t.addsum(a);
        }else{
            downLz(now);//没走到根节点更新
            if(mid>=r){
                add(next,l,r,a);
            }else if(mid<=l){
                add(next+1,l,r,a);
            }else{
                add(next,l,mid,a);
                add(next+1,mid,r,a);
            }
             mergeSon(now);
        }
    }
    ll searchSum(int now,int l,int r){
        Node &t=tree[now];
        const int mid=(t.r+t.l)/2,next=now*2;
        if(t.l==l&&t.r==r){
            return t.sum;
        }else{
            downLz(now);
            if(mid>=r){
                return searchSum(next,l,r);
            }else if(mid<=l){
                return searchSum(next+1,l,r);
            }else{
                return (searchSum(next,l,mid)+searchSum(next+1,mid,r))%P;
            }
        }
    }
};
LineTree tr;

namespace Split{
    int sz[MAX],//子节点数目,包括自身
        p[MAX],//父节点编号
        h[MAX],//高度
        top[MAX],//当前重链最顶端的点
        shv[MAX],//子节点中重节点编号
        id[MAX];//新编号
    ll newVal[MAX];//如果想节省空间可以不要
    int cnt;
    inline void dfs1(cint now,cint f,cint deep){//标记4个属性，sz,p,j,shv,根节点的p是-1，deep是0
        h[now]=deep;
        p[now]=f;//标记每个点的父亲
        sz[now]=1;//标记每个非叶子节点的子树大小
        int maxsz=-1;//记录最大的sz数
        for(int i=g.head[now];i!=-1;i=g.edge[i].k){
            cint e=g.edge[i].e;
            if(e!=f){
                dfs1(e,now,deep+1);
                sz[now]+=sz[e];//加上儿子的大小
                if(sz[e]>maxsz){
                    shv[now]=e;
                    maxsz=sz[e];
                }
            }
        }
    }
    inline void dfs2(cint now,cint tnow){//x当前节点，topf当前链的最顶端的节点，根节点的topf是自己，cnt从0开始
        id[now]=cnt;//标记每个点的新编号
        newVal[cnt++]=val[now];//把每个点的初始值赋到新编号上来
        top[now]=tnow;//这个点所在链的顶端
        if(shv[now]){////如果有儿子
            dfs2(shv[now],tnow);//按先处理重儿子，再处理轻儿子的顺序递归处理
            for(int i=g.head[now];i!=-1;i=g.edge[i].k){
                cint e=g.edge[i].e;
                if(e!=p[now]&&e!=shv[now]){//不是父节点也不是重节点
                    dfs2(e,e);//对于每一个轻儿子都有一条从它自己开始的链
                }
            }
        }
    }
    void split(int root){//遍历两次树
        dfs1(root,-1,0);
        cnt=0;
        dfs2(root,root);
    }
    void add(int x,int y,ll a){//树上x到y最短路,增加a
        while(top[x]!=top[y]){
            int &now=h[top[x]]>h[top[y]]?x:y;
            if(top[now]){
                tr.add(1,id[top[now]],id[now]+1,a);
                now=p[top[now]];
            }else{
                tr.add(1,id[now],id[now]+1,a);
                now=p[now];
            }
        }
        x=id[x];
        y=id[y];
        if(x>y)
            swap(x,y);
        tr.add(1,x,y+1,a);
    }
    ll getSum(int x,int y){//得到树上x到y最短路上点的值
        ll sum=0;
        while(top[x]!=top[y]){
            int &now=h[top[x]]>h[top[y]]?x:y;
            if(top[now]){
                sum=(sum+tr.searchSum(1,id[top[now]],id[now]+1))%P;
                now=p[top[now]];
            }else{
                sum=(sum+tr.searchSum(1,id[now],id[now]+1))%P;;
                now=p[now];
            }
        }
        x=id[x];
        y=id[y];
        if(x>y)
            swap(x,y);
        sum=(sum+tr.searchSum(1,x,y+1))%P;
        return sum;
    }
}
int main(int argc,char *argv[]){
    //freopen("in1.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    rg int i,j,k,t,T,n,m,root,u,v,x,y,z;
    ll sum;
    scanf("%d%d%d%d",&n,&m,&root,&P);
    for(i=1;i<=n;i++){
        scanf("%lld",&val[i]);
    }
    g.clear();
    for(i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        g.push(u,v,0);
        g.push(v,u,0);
    }
    Split::split(root);
    tr.buildTree(1,Split::newVal,0,n);// 用新数组建立线段树
    for(i=0;i<m;i++){
        scanf("%d",&k);
        if(k==1){
            scanf("%d%d%d",&x,&y,&z);
            Split::add(x,y,z);
        }else if(k==2){
            scanf("%d%d",&x,&y);
            printf("%lld\n",Split::getSum(x,y));
        }else if(k==3){
            scanf("%d%d",&x,&z);
            tr.add(1,Split::id[x],Split::id[x]+Split::sz[x],z);
        }else if(k==4){
            scanf("%d",&x);
            sum=tr.searchSum(1,Split::id[x],Split::id[x]+Split::sz[x]);
            printf("%lld\n",sum);
        }
    }
return 0;
}
