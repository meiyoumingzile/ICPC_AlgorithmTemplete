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
const int MAX=1010;
const int mod=1e9+7;

struct Node{
    int i,j;//位置
    Node *f[4];//上下左右
    Node(){}
    Node(int r,int c){
        sett(r,c);
    }
    void sett(int r,int c){
        i=r;j=c;
    }
    void link(Node &b,int x){
        f[x]=&b;
        b.f[x^1]=this;
    }
    void link(Node *b,int x){
        f[x]=b;
        b->f[x^1]=this;
    }
};
const int DN=1010;
struct DLX{
    Node node[DN*DN],col[DN],row[DN],head;
    int ans[DN],sz[DN],cnt,n,m;
    void init(int n,int m){
        this->n=n;
        this->m=m;
        head.sett(n,m);cnt=0;
        head.link(head,0);head.link(head,2);
        for(int i=1;i<m;i++){
            col[i].sett(n,i);
            col[i].link(col[i],0);//上下是自己
            sz[i]=0;//上下节点个数是0
            col[i].link(col[i-1],2);
        }
        col[0].link(col[0],0);//上下是自己
        col[0].sett(n,0);
        head.link(col[m-1],2);//head左是col[m-1]
        head.link(col[0],3);//head右是col[0]
        for(int i=1;i<n;i++){
            row[i].sett(i,m);
            row[i].link(row[i],2);//左右是自己
            row[i].link(row[i-1],0);
        }
        row[0].link(row[0],2);//左右是自己
        row[0].sett(0,m);
        head.link(row[n-1],0);//head上是row[n-1]
        head.link(row[0],1);//head下是row[0]
    }
    void addnode(int r,int c){
        Node *p=&node[cnt++];
        p->sett(r,c);
        p->link(row[r].f[2],2);//p左是row[r]的左
        p->link(row[r],3);//p右是row[r]
        p->link(col[c].f[0],0);//p上是col[c]的上
        p->link(col[c],1);//p下是col[c]
        sz[c]++;
    }
    inline void delnode(Node *now,int fp){//fp==0表示删除上下，2表示删除左右
        now->f[fp]->f[fp^1]=now->f[fp^1];
        now->f[fp^1]->f[fp]=now->f[fp];
    }
    inline void renode(Node *now,int fp){//fp==0表示复原上下，2表示复原左右
        now->f[fp^1]->f[fp]=now->f[fp]->f[fp^1]=now;
    }
    inline void cover(int j){//覆盖，也就是消除某一列和这列影响到的行
        if(j==m) return;
        delnode(&col[j],2);
        for(Node *c=col[j].f[1];c!=(&col[j]);c=c->f[1]){
            if(c->j==m)
                continue;
            for(Node *r=c->f[2];r!=c;r=r->f[2]){
                if(r->j==m)
                    continue;
                --sz[r->j];
                delnode(r,0);
            }
            delnode(c,2);
        }
    }
    inline void re(int j){//复原，也就是消除某一列和这列影响到的行
        if(j==m) return;
        for(Node *c=col[j].f[0];c!=(&col[j]);c=c->f[0]){
            if(c->j==m) continue;
            renode(c,2);
            for(Node *r=c->f[3];r!=c;r=r->f[3]){
                if(r->j==m) continue;
                ++sz[r->j];
                renode(r,0);
            }
        }
        renode(&col[j],2);
    }
    bool dance(int k){
        if(head.f[2]==(&head)){
            //找到解法
            for(int i=0;i<k;i++){
                printf("%d ",ans[i]);
            }
            return 1;
        }
        int c=-1,minsz=INF;
        Node *now,*rc;
        for(now=head.f[2];now!=(&head);now=now->f[2]){
            if(minsz>sz[now->j]){
                minsz=sz[now->j];
                c=now->j;
            }
        }
        cover(c);
        for(now=col[c].f[1];now!=(&col[c]);now=now->f[1]){
            now->f[3]->f[2]=now;
            for(rc=now->f[2];rc!=now;rc=rc->f[2])
                cover(rc->j);
            now->f[3]->f[2]=now->f[2];
            ans[k]=now->i+1;
            if(dance(k+1)) return 1;
            now->f[2]->f[3]=now;
            for(rc=now->f[3];rc!=now;rc=rc->f[3]){
                re(rc->j);
            }
            now->f[2]->f[3]=now->f[3];
        }
        re(c);
        return 0;
    }
};
DLX dlx;
int mapp[MAX][MAX];
int main(int argc,char *argv[]){
	int i,j,k,t,T,n,m;
    scanf("%d%d",&n,&m);
    dlx.init(n,m);
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            scanf("%d",&mapp[i][j]);
            if(mapp[i][j]==1){
                dlx.addnode(i,j);
            }
        }
    }
    if(!dlx.dance(0)){
        cout<<"No Solution!"<<endl;
    }
return 0;
}

