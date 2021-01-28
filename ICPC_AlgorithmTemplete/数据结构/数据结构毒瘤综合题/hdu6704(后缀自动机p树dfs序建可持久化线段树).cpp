#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=200010;
const int mod=1e9+7;
struct v2{
    int x,y;
	v2(){}
	v2(const int &x,const int &y){
		sett(x,y);
	}
    void sett(const int &x,const int &y){
        this->x=x;
        this->y=y;
    }
};

vector<int>adlist[MAX];
int binp[MAX][21],pLen[MAX],treeSize[MAX];//树上节点深度和向上的倍增数组
struct Node{
    int sum,son[2];
};
struct PersistentLineTree{
    int size,rlen;
    int root[MAX];//表示根节点集合，root[0]代表最原始的树
    Node tree[MAX*50];
    void build(int l,int r){
        size=rlen=1;
        root[0]=__build(l,r);
    }
    int __build(int l,int r){
        int now=size++,mid=(l+r)/2;
        tree[now].sum=0;
        if(r-l>1){
            tree[now].son[0]=__build(l,mid);
            tree[now].son[1]=__build(mid, r);
        }
        return now;
    }
    void insert(int tl,int tr,int x){//单点修改,在最新版本基础上x位置加1,x是离散化之后的数值
        int last=root[rlen-1];
        root[rlen++]=__insert(last,tl,tr,x);
    }
    int __insert(int other,int tl,int tr, int x){//单点修改,在other版本的树的基础上的x位置加1,x是离散化之后的数值
        int now=size++;
        Node &t=tree[now];//t去引用tree[now]，以后t就是tree[now]
        t=tree[other];//把历史版本的一个复制给tree[now]
        t.sum++;
        if(tr-tl>1){
            int mid=(tl+tr)/2;
            if(x<mid){//节点编号在左边，往右找
                t.son[0]=__insert(tree[other].son[0],tl,mid,x);
            }else{//节点编号在右边，往右找
                t.son[1]=__insert(tree[other].son[1],mid,tr,x);
            }
        }
        return now;
    }
    int searchKi(int l,int r,int tl,int tr,int k){//查询区间[l,r]的第k小
        return __searchKi(root[l-1],root[r],tl,tr,k);
    }
    int __searchKi(int root1,int root2,int tl,int tr,int k){//查询区间第k小，用法见文档
        if (tr-tl<=1)//是叶子结点
            return tl;
        int tl1=tree[root1].son[0];
        int tl2=tree[root2].son[0];
        int x=tree[tl2].sum - tree[tl1].sum;
        int mid=(tl+tr)/2;
        if(x>=k)
            return __searchKi(tl1,tl2,tl,mid,k);
        else
            return __searchKi(tree[root1].son[1],tree[root2].son[1],mid,tr,k-x);
    }
};
PersistentLineTree tr;

const int CHARCNT=26;
inline int toInt(const char &a){
    return a-'a';
}
struct SAM{
    int root,last,size;
    int p[MAX],nodelen[MAX],son[MAX][CHARCNT],pos[MAX],mainid[MAX];

    //eplen[i]是编号为i的节点endpos集合元素个数,du是只看p指针的每个点入度数
    SAM(){
       clear();
    }
    void clear(){//初始化
        root=last=0;//根节点编号是0
        memset(son[0],-1,sizeof(son[0]));
        memset(pos,0,sizeof(pos));
        p[0]=-1;
        nodelen[0]=0;
        size=1;
    }
    int addNode(int len,bool isMain){//按照编号顺序添加节点
        int sz=size++;
        memset(son[sz],-1,sizeof(son[sz]));
        nodelen[sz]=len;
        return sz;
    }
    int push(const char &a,int si){
        int f=toInt(a),now,node,q,nq;
        node=addNode(nodelen[last]+1,1);
        pos[node]=si;
        mainid[si]=node;
        for(now=last;now!=-1&&son[now][f]==-1;now=p[now]){
            son[now][f]=node;
        }
        if(now!=-1){
            q=son[now][f];
            if(nodelen[now]+1==nodelen[q]){
                p[node]=q;
            }else{
                nq=addNode(nodelen[now]+1,0);
                memcpy(son[nq], son[q], sizeof son[q]);
                p[nq]=p[q];
                p[q]=p[node]=nq;
                while(now!=-1&&son[now][f]==q){
                    son[now][f]= nq;
                    now=p[now];
                }
            }
        }else{
             p[node]=root;
        }
        last=node;
        return nodelen[node]- nodelen[p[node]];
    }
};
SAM sam;
int LRDid[MAX],LRDlen;//后序遍历编号
/*void dfsSAMTree(int now,int n,int h=0){
    treeSize[now]=1;
    for(auto next:adlist[now]){
        for(int j=0;;j++){//更新倍增数组
            int k=binp[next][j];
            if(j<pLen[k]){
                binp[next][pLen[next]++]=binp[k][j];
            }else{
                break;
            }
        }
        dfsSAMTree(next,n,h+1);
        treeSize[now]+=treeSize[next];
    }
    //printf("%d->%d->%d\n",now,LRDlen,sam.pos[now]);
    if(sam.pos[now])
        tr.insert(0,sam.size+1,sam.pos[now]);
    else
        tr.insert(0,sam.size+1,sam.size);
    LRDid[now]=++LRDlen;
}*/

stack<v2>st;
void dfs(int root){
    v2 now,next;
    st.push(v2(root,0));
    for(int i=0;i<sam.size;i++){
        treeSize[i]=1;
    }
    while(!st.empty()){
        now=st.top();
        st.pop();
        if(now.y<adlist[now.x].size()){
            now.y++;
            st.push(now);
        }else{
            if(sam.p[now.x]>=0)
                treeSize[sam.p[now.x]]+=treeSize[now.x];
            if(sam.pos[now.x])
                tr.insert(0,sam.size+1,sam.pos[now.x]);
            else
                tr.insert(0,sam.size+1,sam.size);
            LRDid[now.x]=++LRDlen;
            continue;
        }
        next.x=adlist[now.x][now.y-1];
        next.y=0;

        int v=next.x;
        for(int j=0;;j++){//更新倍增数组
            int k=binp[v][j];
            if(j<pLen[k]){
                binp[v][pLen[v]++]=binp[k][j];
            }else{
                break;
            }
        }
        st.push(next);
    }
}
int findTargetNode(int now,int len){//返回编号,祖先里nodelen第一个大于等于h的节点
    int i;
    while(sam.nodelen[now]>=len){
        for(i=0;i<pLen[now]&&sam.nodelen[binp[now][i]]>=len;i++);
        if(i==0)
            return now;
        now=binp[now][i-1];
    }
    return now;
}

char str[MAX];
void init(int n){
    sam.clear();//清空后缀自动机
    for(int i=0;i<=n;i++){
        adlist[i].clear();//清空邻接表
    }
    for(int i=0;i<n;i++){
        sam.push(str[i],i+1);
    }
    tr.build(0,sam.size+1);
    memset(pLen,0,sizeof(pLen));
    memset(binp,0,sizeof(binp));
    for(int i=1;i<sam.size;i++){//初始化倍增数组，得到邻接表
        binp[i][pLen[i]++]=sam.p[i];
        adlist[sam.p[i]].push_back(i);
    }
    LRDlen=0;
    dfs(sam.root);
   /* for(int i=1;i<sam.size;i++){
        printf("%d->%d :%d %d\n",sam.p[i],i,sam.nodelen[sam.p[i]],sam.nodelen[i]);
    }*/
}
enum index{underflow, overflow};
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,n,j,len,m,T,l,r,k,id,ans;
    cin>>T;
    while(T--){
        scanf("%d%d%s",&n,&m,str);
        init(n);
        for(i=0;i<m;i++){
            scanf("%d%d%d",&l,&r,&k);
            len=r-l+1;
            id=findTargetNode(sam.mainid[r],len);

            //printf("%d %d %d\n",high[id],len+1,sam.p[id]);
             //printf("id:%d\n",id);
            //printf("%d %d\n",treeSize[id],LRDid[id]);
            if(treeSize[id]>=k){
                ans=tr.searchKi(LRDid[id]-treeSize[id]+1,LRDid[id],0,sam.size+1,k);
                printf("%d\n",ans==sam.size?-1:ans-len+1);
            }else{
                printf("-1\n");
            }
        }
    }
return 0;
}
/*
11
7 7
aabbabd
2 2 2
2 3 1

2
12 6
aaabaabaaaab
3 3 4
2 3 2
7 8 3
3 4 2
1 4 2
8 12 1
1 1
a
1 1 1

2
12 6
aaabaabaaaab
3 4 3

13 14 3 6 11 12 2 5 9 10 1 15 4 7 8 0 3 3 4
*/
