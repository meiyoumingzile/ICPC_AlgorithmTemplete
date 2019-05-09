#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;

struct Node{
    int r,l,sum,minb,maxa,lz;//维护A的最大值和B的最小值
};

int B[MAX],A[MAX];
struct LineTree{
    Node tree[MAX*4];
    void buildTree(int now,int *b,int l,int r){//维护A的最大值和B的最小值,但A初始全部是0
        tree[now].l=l;
        tree[now].r=r;
        if(r-l<=1){
            tree[now].minb=b[l];
            tree[now].maxa=0;
            return;
        }
        int mid=(l+r)/2,next=now*2;
        buildTree(next,b,l,mid);
        buildTree(next+1,b,mid,r);
        tree[now].maxa=0;
        tree[now].minb=min(tree[next].minb,tree[next+1].minb);
    }

    void downLz(int now){//下放，增加下边节点的maxa值,这个操作在递归的非终止层的前面执行，也保证了不会到叶子节点而越界
        const int next=now<<1;
        tree[next].lz+=tree[now].lz;
        tree[next+1].lz+=tree[now].lz;
        tree[next].maxa+=tree[now].lz;
        tree[next+1].maxa+=tree[now].lz;
        tree[now].lz=0;
    }

    void updateB(int now){
        Node &t=tree[now];
        const int mid=(t.r+t.l)>>1,next=now<<1;
        if(t.maxa<t.minb)
            return;
        if(t.r==t.l+1){
            int k=t.maxa/B[t.l]-t.sum;
            t.minb+=k*B[t.l];
            t.sum+=k;
        }else{
            downLz(now);
            updateB(next);
            updateB(next+1);
            t.maxa=max(tree[next].maxa,tree[next+1].maxa);
            t.minb=min(tree[next].minb,tree[next+1].minb);
            t.sum=tree[next].sum+tree[next+1].sum;
        }
    }
    void updateA(int now,int l,int r,int a){
        Node &t=tree[now];
        const int mid=(t.r+t.l)>>1,next=now<<1;
        if(t.l==l&&t.r==r){
            t.lz+=a;
            t.maxa+=a;
            if(t.maxa>=t.minb){
                //printf("hh");
                updateB(now);
            }
        }else{
            downLz(now);
            if(mid>=r){
                updateA(next,l,r,a);
            }else if(mid<=l){
                updateA(next+1,l,r,a);
            }else{
                updateA(next,l,mid,a);
                updateA(next+1,mid,r,a);
            }
            t.maxa=max(tree[next].maxa,tree[next+1].maxa);
            t.minb=min(tree[next].minb,tree[next+1].minb);
            t.sum=tree[next].sum+tree[next+1].sum;
        }
    }
    int searchSum(int now,int l,int r){
        Node &t=tree[now];
        const int mid=(t.r+t.l)>>1,next=now<<1;
        if(t.l==l&&t.r==r){
            return t.sum;
        }else{
            downLz(now);
            if(mid>=r){
                return searchSum(next,l,r);
            }else if(mid<=l){
                return searchSum(next+1,l,r);
            }else{
                return searchSum(next,l,mid)+searchSum(next+1,mid,r);
            }
        }
    }
    void clear(){
        memset(tree,0,sizeof(tree));
    }
    void print(int now){
        printf("[%d,%d):%d,sum:%d ",tree[now].l,tree[now].r,tree[now].maxa,tree[now].sum);
        if(tree[now].r-tree[now].l==1){
            return ;
        }
        print(now*2);
        print(now*2+1);
    }
    void println(){
        print(1);
        printf("\n");
    }
};

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,m,n,p,x,y,l,r;
    char kind[10];
    LineTree *t=new LineTree();
    while(~scanf("%d%d",&n,&m)){
        t->clear();
        for(i=0;i<n;i++){
            scanf("%d",&B[i]);
        }
        t->buildTree(1,B,0,n);
        for(i=0;i<m;i++){
            scanf("%s%d%d",kind,&l,&r);
            if(strcmp(kind,"add")==0){
                t->updateA(1,l-1,r,1);
            }else{
                printf("%d\n",t->searchSum(1,l-1,r));
            }
            //t->println();
        }
    }
return 0;
}
/*
5 12
1 5 2 4 3
add 1 4
add 3 5
q 3 4
*/
