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

struct Node{
    int val,dis,son[2],p;
    int com(const Node &b){
        if(val==b.val)
            return 0;
        return val>b.val?1:-1;
    }
};
struct Mheap{//二项堆不是一个堆，是一群堆，初始有n个离散的节点，它们各自属于一个堆
    const int NO=-INF;//代表已经被删除的点的val
    Node node[MAX];
    void clear(){
        memset(node,0,sizeof(node));
    }
    int __merge(int x,int y){//合并以根x和根y所在节点的堆
        if(x==0||y==0)//有一个是空就不能合并了,返回不是空的
            return x?x:y;
        if(node[x].com(node[y])==1||(node[x].com(node[y])==0&&x>y))
            swap(x,y);
        int &xl=node[x].son[0];
        int &xr=node[x].son[1];
        xr=__merge(xr,y);
        node[xr].p=x;//右的父亲是x
        if(node[xl].dis<node[xr].dis)
            swap(xl,xr);
        node[x].dis=node[xr].dis+1;
        return x;
    }
    int merge(int x,int y){//合并第x个节点与第y个节点所在的堆，x和y编号[1,n],f返回根节点编号，合并不成功返回0
        if(node[x].val!=NO&&node[y].val!=NO&&x!=y){
            x=getRoot(x);
            y=getRoot(y);
            return __merge(x,y);
        }
        return 0;
    }
    int getRoot(int x){//找到编号是x的点的，根节点
        while(node[x].p)
            x=node[x].p;
        return x;
    }
    int pop(int x){//分离节点x所在树的根,返回删除后，谁是根
        x=getRoot(x);
        node[x].val=NO;//表示这个点不存在
        int &xl=node[x].son[0];
        int &xr=node[x].son[1];
        node[xl].p=node[xr].p=0;
        return merge(xl,xr);
    }
};
Mheap que;

int main(int argc,char *argv[]){
	int i,k,n,m,b,e;
	//que.clear();
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
        scanf("%d",&que.node[i].val);//输入n个数，
	}
	for(i=0;i<m;i++){
        scanf("%d",&k);
        if(k==1){
            scanf("%d%d",&b,&e);//合并编号为b和编号为e所在的堆
            que.merge(b,e);
        }else if(k==2){
            scanf("%d",&b);
            if(que.node[b].val!=que.NO){//有没有被删过
                b=que.getRoot(b);
                printf("%d\n",que.node[b].val);
                que.pop(b);
            }else{//要找的被删除了输出-1，
                printf("-1\n");
            }
        }
	}
return 0;
}
