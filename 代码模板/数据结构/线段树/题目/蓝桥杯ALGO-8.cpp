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
    int r,l,s,m;
};

int A[MAX];
struct LineTree{
    Node tree[MAX*4];
    void buildTree(int now,int *a,int l,int r){
        tree[now].l=l;
        tree[now].r=r;
        if(r-l<=1){
            tree[now].m=tree[now].s=a[l];
            return;
        }
        int mid=(l+r)/2,next=now*2;
        buildTree(next,a,l,mid);
        buildTree(next+1,a,mid,r);
        tree[now].m=max(tree[next].m,tree[next+1].m);
        tree[now].s=tree[next].s+tree[next+1].s;
    }

    void update(int now,int ind,int a){
        if(ind==tree[now].l&&tree[now].r-tree[now].l==1){
            tree[now].m=tree[now].s=a;
            return;
        }
        int mid=(tree[now].l+tree[now].r)/2,next=now*2;
        if(mid>ind){
            update(next,ind,a);
        }else{
            update(next+1,ind,a);
        }
        tree[now].m=max(tree[next].m,tree[next+1].m);
        tree[now].s=tree[next].s+tree[next+1].s;
    }

    int searchm(int now,int l,int r){
        if(l==tree[now].l&&tree[now].r==r){
            return tree[now].m;
        }
        int mid=(tree[now].l+tree[now].r)/2,next=now*2;
        if(mid>=r){
            return searchm(next,l,r);
        }else if(mid<=l){
            return searchm(next+1,l,r);
        }else{
            return max(searchm(next,l,mid),searchm(next+1,mid,r));
        }
    }

    int searchs(int now,int l,int r){
        if(l==tree[now].l&&tree[now].r==r){
            return tree[now].s;
        }
        int mid=(tree[now].l+tree[now].r)/2,next=now*2;
        if(mid>=r){
            return searchs(next,l,r);
        }else if(mid<=l){
            return searchs(next+1,l,r);
        }else{
            return searchs(next,l,mid)+searchs(next+1,mid,r);
        }
    }

    void print(int now){
        printf("%d ",tree[now].s);
        if(tree[now].r-tree[now].l==1){
            return ;
        }
        print(now*2);
        print(now*2+1);
    }
};

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,m,n,p,x,y;
    scanf("%d%d",&n,&m);
    for(i=0;i<n;i++){
        scanf("%d",&A[i]);
    }
    LineTree *t=new LineTree();
    t->buildTree(1,A,0,n);
   // t->print(1);
    for(i=0;i<m;i++){
        scanf("%d%d%d",&p,&x,&y);
        if(p==1){
            t->update(1,x-1,y);
        }else if(p==2){
            printf("%d\n",t->searchs(1,x-1,y));
        }else if(p==3){
            printf("%d\n",t->searchm(1,x-1,y));
        }
    }
return 0;
}
