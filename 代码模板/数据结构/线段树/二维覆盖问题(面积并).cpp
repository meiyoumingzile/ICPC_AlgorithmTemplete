#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
#define cdou const double &
const int INF=2147483647;////2139062143
const int MAX=4010;
const int mod=1e9+7;
struct segment{
    double xl,xr,y;
    bool fp;
};
segment A[MAX];
double X[MAX],todou[MAX];
unordered_map<double,int>ind;
struct Node{
    int r,l,lz,col;//col代表最少的层数
    double s1,s2;//s1代表覆盖一次以上的区间长度，s2代表覆盖了2次及以上区间的长度
    double sdis(){
        return todou[r]-todou[l];
    }
};
struct LineTree{//区间是左闭 左开[)
    Node tree[MAX*4];
    void buildTree(int now,int l,int r){//建树,初始化col和lz是-1，代表无颜色无标记
        tree[now].l=l;
        tree[now].r=r;
        tree[now].col=0;
        tree[now].s1=tree[now].s2=0;
        if(r-l<=1){
            return;
        }
        int mid=(l+r)/2,next=now*2;
        buildTree(next,l,mid);
        buildTree(next+1,mid,r);
    }
    void updateS(cint now){
        Node &t=tree[now],&tl=tree[now*2],&tr=tree[now*2+1];
        if(t.r-t.l==1){//叶子结点的值要么是0，要么是总距离
            if(t.col==0){
                t.s1=t.s2=0;
            }else if(t.col==1){
                t.s1=t.sdis();
                t.s2=0;
            }else{
                t.s1=t.s2=t.sdis();
            }
        }else{
            if(t.col==0){//本身没被覆盖就是它子节点的值加和
                t.s1=tl.s1+tr.s1;
                t.s2=tl.s2+tr.s2;
            }else if(t.col==1){//被覆盖一次的话，s1是总距离，s2是子节点的s1值之和再被覆盖一次
                t.s1=t.sdis();
                t.s2=tl.s1+tr.s1;
            }else{
                t.s1=t.s2=t.sdis();
            }
        }
    }
    void add(int now,int l,int r,int a){
        Node &t=tree[now];
        cint mid=(t.r+t.l)>>1,next=now<<1;
        if(t.l==l&&t.r==r){
            t.col+=a;
            updateS(now);
        }else{
            if(mid>=r){
                add(next,l,r,a);
            }else if(mid<=l){
                add(next+1,l,r,a);
            }else{
                add(next,l,mid,a);
                add(next+1,mid,r,a);
            }
            updateS(now);
        }
    }
};
LineTree tr;
void scanning(cint n){//扫描线法
    int i,j,k=0;
    ind.clear();
    sort(X,X+2*n);//先离散化X坐标建立索引。
    for(i=0;i<2*n-1;i++){
        ind[X[i]]=k;
        todou[k]=X[i];
        if(X[i]!=X[i+1]){
            k++;
        }
    }
    ind[X[i]]=k;
    todou[k]=X[i];
    k++;
    sort(A,A+2*n,[](const segment &a,const segment &b){
         return a.y<b.y;});//对线段按照高度排序
    tr.buildTree(1,0,k);
    double ans=0;
    tr.add(1,ind[A[0].xl],ind[A[0].xr],1);
    for(i=1;i<2*n;i++){
        ans+=(A[i].y-A[i-1].y)*tr.tree[1].s2;
        if(A[i].fp){//上部的线
            tr.add(1,ind[A[i].xl],ind[A[i].xr],-1);
        }else{//下部的线
            tr.add(1,ind[A[i].xl],ind[A[i].xr],1);
        }
    }
    printf("%.2lf\n",ans);
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,t,T,n;
	double x1,y1,x2,y2;
	scanf("%d",&T);
	while(T--){
        scanf("%d",&n);
        for(i=0;i<n;i++){
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            X[2*i]=x1;
            X[2*i+1]=x2;
            A[2*i].y=y1;//A[2*i]代表矩形下边,xy代表高度;
            A[2*i].xl=x1;
            A[2*i].xr=x2;
            A[2*i].fp=0;
            A[2*i+1].y=y2;//A[2*i+1]代表矩形上边边,y代表高度;
            A[2*i+1].xl=x1;
            A[2*i+1].xr=x2;
            A[2*i+1].fp=1;
        }
        scanning(n);//离散化并且输出结果
	}
return 0;
}

