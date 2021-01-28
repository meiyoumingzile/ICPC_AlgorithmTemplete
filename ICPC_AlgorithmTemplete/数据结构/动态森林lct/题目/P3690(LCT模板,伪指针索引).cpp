#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
const int INF=2147483647;////2139062143
const int MAX=3000010;

void println(int *arr,int b,int e){//[b,e)
    printf("(%d:%d)",b,arr[b]);
    for(int i=b+1;i<e;i++){
        printf(" (%d:%d)",i,arr[i]);
    }printf("\n");
}
struct LCT{
    int n,p[MAX],son[MAX][2],val[MAX],xorsum[MAX];
    bool lz[MAX];//懒惰标记，用来做splay的区间翻转。
    /*p[i]是i父节点; son[i]是i左右儿子,0代表左边，1代表右边,son[i][0]=0代表空指针，son特指splay的儿子
    val[i]是点i权值，xorsum[i]是i异或和
    */

    LCT(){
       // memset();
    }

    void pushdown(){

    }
    void pushup(){

    }
    int makeroot(int now){//换普通多叉树的根，让新的节点x成为普通多叉树的根
        access(x);
        splay(x);
        reversal(x);
    }
    void access(int now){//把now到该多叉树的根节点的路径，变成splay
        for(int ch=0;now;ch=now,now=p[now]){//ch是now的儿子，ch=0代表初始是空，初始
            splay(now);
            son[now][1]=ch;
            update(now);//儿子变了，需要及时上传信息
        }
    }
    void splay(int now){//把now旋转到他所在的根节点
        stack<int>st;
        int p=now;
        st.push(now);
        while(){//标记要从上往下更新

        }
        for(int fp=getfp(now);fp!=-1;fp=getfp(now)){
            p=p[now];
            rotate(p,fp);
        }
    }
    int query(int x,int y){//查询亦或和
        split(x,y);
        return xorsum[y];
    }

    void linkNode(int x,int next,int fp){
        son[x][fp]=next;
        p[next]=x;
    }
    int getfp(int x){//返回-1表示此点是根,否则返回方向
        if(son[p[x]][0]==x)
            return 0;
        if(son[p[x]][1]==x)
            return 1;
        return -1;
    }
    int rotate(int x,int fp){//单旋转，fp是指，要转x的左边还是右边，1代表转x的右边，把整体向左转。
        int p=p[x],e=son[x][fp];
        int xfp=getfp(x);
        linkNode(x,son[e][fp^1],fp);
        linkNode(e,x,fp^1);
        linkNode(p,e,xfp);
        update(x);
        update(e);
        return e;
    }
    void reversal(int now){//Splay区间翻转操作
        swap(son[x][0],son[x][1]);
        lz[x]^=1;//r为区间翻转懒标记数组
    }
    void update(int x){//更新当前点的值,其自己的亦或和：是左右儿子再亦或val[x]，具体看题目需求
        xorsum[x]=xorsum[son[x][0]]^xorsum[son[x][0]]^val[x];
    }
    void pushdown(int x){//判断并释放懒标记
        if(lz[x]){
            if(son[x][0])reversal(son[x][0]);
            if(son[x][1])reversal(son[x][1]);
            lz[x]=0;
        }
    }
};
LCT lct;
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
	int i,j,k,t,T,n,m,id,x,y;
    scanf("%d%d",&n,&m);
    for(i=0;i<n;i++){
        scanf("%d",&lct.val[i]);
    }
    while(m--){
        scanf("%d%d%d",&id,&x,&y);
        switch(id){
            case 0://返回从 x 到 y 的路径上的点的权值的xor 和。保证 x 到 y 是联通的
                lct.split(x,y);
                printf("%d\n",lct.xorsum[y]);
                break;
            case 1://若边edge(x,y)不存在，则链接它，存在则什么都不做
                lct.link(x,y);
                break;
            case 2://若边edge(x,y)存在，则删除它，不存在则什么都不做
                lct.cut(x,y);
                break;
            case 3://把第x点的权值变成y
                lct.splay(x);
                lct.val[x]=y;//先把x转上去再改，不然会影响Splay信息的正确性
                break;
        }
    }
return 0;
}
