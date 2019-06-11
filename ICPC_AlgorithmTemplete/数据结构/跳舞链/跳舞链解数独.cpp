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
    Node node[DN*DN],col[DN],row[DN],root;
    int ans[DN],sz[DN],cnt,n,m,ansLen;
    bool mapp[DN][DN];
    void init(int n,int m){
        this->n=n;
        this->m=m;
        memset(mapp,0,sizeof(mapp));
        root.sett(n,m);cnt=0;
        root.link(root,0);root.link(root,2);
        for(int i=1;i<m;i++){
            col[i].sett(n,i);
            col[i].link(col[i],0);//上下是自己
            sz[i]=0;//上下节点个数是0
            col[i].link(col[i-1],2);
        }
        col[0].link(col[0],0);//上下是自己
        col[0].sett(n,0);
        root.link(col[m-1],2);//root左是col[m-1]
        root.link(col[0],3);//root右是col[0]
        for(int i=1;i<n;i++){
            row[i].sett(i,m);
            row[i].link(row[i],2);//左右是自己
            row[i].link(row[i-1],0);
        }
        row[0].link(row[0],2);//左右是自己
        row[0].sett(0,m);
        root.link(row[n-1],0);//root上是row[n-1]
        root.link(row[0],1);//root下是row[0]
    }
    void fill(){//根据mapp数组填充跳舞链
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(mapp[i][j]==1){
                    addnode(i,j);
                }
            }
        }
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
        if(root.f[2]==(&root)){
            //找到解法
            ansLen=k;
            return 1;
        }
        int c=-1,minsz=INF;
        Node *now,*rc;
        for(now=root.f[2];now!=(&root);now=now->f[2]){
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
            ans[k]=now->i;//填入解法
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
int Sudoku[9][9];
int toid(int i,int j){
    return i*9+j;
}
void addmapp(int i,int j,int k,int a){
    dlx.mapp[toid(i,j)*9+a][toid(i,j)+0*81]=1;
    dlx.mapp[toid(i,j)*9+a][toid(i,a)+1*81]=1;
    dlx.mapp[toid(i,j)*9+a][toid(j,a)+2*81]=1;
    dlx.mapp[toid(i,j)*9+a][toid(k,a)+3*81]=1;
}
int main(int argc,char *argv[]){
    int i,j,T,a,k,h,n,m;
    cin>>T;
	while(T--){
        n=9*9*9;
        m=4*81;
        dlx.init(n,m);
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                scanf("%d",&a);
                Sudoku[i][j]=a;
                k=i/3*3+j/3;
                if(a>0){
                    a--;
                    addmapp(i,j,k,a);
                }else{
                    for(h=0;h<9;h++){
                        addmapp(i,j,k,h);
                    }
                }
            }
        }
        dlx.fill();
        if(!dlx.dance(0)){
            printf("NO\n");
        }else{
            for(k=0;k<dlx.ansLen;k++){
                h=dlx.ans[k]/9;
                a=dlx.ans[k]%9;
                i=h/9;
                j=h%9;
                Sudoku[i][j]=a+1;
            }
        }
        printf("\n");
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                printf("%d%c",Sudoku[i][j],j==8?'\n':' ');
            }
        }
	}
return 0;}
/*
7 0 0 0 0 0 3 0 0
0 2 0 5 7 0 9 0 6
8 0 6 0 0 0 0 4 0
0 7 0 0 0 9 0 0 0
0 0 0 4 0 0 0 6 0
0 0 0 0 0 6 5 3 0
3 0 0 0 6 0 0 2 0
0 0 2 0 0 1 0 0 0
0 0 0 0 3 8 0 9 0
*/
