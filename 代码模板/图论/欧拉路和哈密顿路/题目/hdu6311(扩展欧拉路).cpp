#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;

struct Edge{
    int e,val,k,i;
    Edge(){}
    Edge(const int &e,const int &val,const int &k,const int &i){
        this->e=e;
        this->val=val;
        this->k=k;
        this->i=i;
    }
};
struct Graphic{
    int V,E,S,T,size=0;
    int head[MAX];
    Edge edge[MAX*10];
    Graphic(){
        clear();
    }
    void push(const int &b,const int &e,const int &val,const int &i=0){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t,i);
    }
    void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
    void println(){
        int i,j,next;
        for(i=1;i<=V;i++){
            printf("%d:::",i);
            for(j=head[i];j!=-1;j=edge[j].k){
                printf("%d ",edge[j].e);
            }printf("\n");
        }
    }
};
Graphic g;

void println(int *arr,int b,int e){//[b,e)
    printf("(%d:%d)",b,arr[b]);
    for(int i=b+1;i<e;i++){
        printf(" (%d:%d)",i,arr[i]);
    }printf("\n");
}

int du[MAX],dot[MAX*10],vis[MAX*10];
int len;

inline void dfs(int now){//寻找联通块
    vis[now]=1;
    dot[len++]=now;
    for(int i=g.head[now];i!=-1;i=g.edge[i].k){
        if(vis[g.edge[i].e]==0){
            dfs(g.edge[i].e);
        }
    }
}
inline void findLoad(int now){//返回要输出的起点,i代表编号
    int val;
    for(int i=g.head[now];i!=-1;i=g.edge[i].k){
        if(g.edge[i].val<10){
            val=g.edge[i].val;
            g.edge[i].val+=20;
            g.edge[i^1].val+=20;
            findLoad(g.edge[i].e);
            dot[len]=g.edge[i].i;
            vis[len]=-val;
            len++;
        }
    }
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	rg int i,j,k,h,T,b,e,cnt,lastDot;
	while(~scanf("%d%d",&g.V,&g.E)){
        g.clear();
        memset(du,0,sizeof(du));
        memset(vis,0,sizeof(vis));
        for(i=1;i<=g.E;i++){
            scanf("%d%d",&b,&e);
            g.push(b,e,1,i);
            g.push(e,b,-1,i);
            du[b]++;
            du[e]++;
        }
        for(i=1,cnt=0;i<=g.V;i++){
            if(vis[i]==0&&du[i]>0){
                len=0;
                dfs(i);//找到联通块
                for(j=k=0;j<len;j++){
                    if(du[dot[j]]&1){
                        k++;
                        if(k&1){
                            lastDot=dot[j];
                        }else{//够2个连边
                            g.push(dot[j],lastDot,0);
                            g.push(lastDot,dot[j],0);

                        }
                    }
                }
                cnt+=max(1,k/2);
            }
        }
        printf("%d\n",cnt);//输出个数
        for(i=1;i<=g.V;i++){
            if(du[i]==0){//孤立点
                //printf("1 %d\n",i);
            }else{
                len=0;
                findLoad(i);
                for(j=0;vis[j]!=0&&j<len;j++);
                if(j==len&&len>0){//没有添加的边直接循环输出
                    printf("%d",len);
                    for(j=0;j<len;j++){
                        printf(" %d",dot[j]*vis[j]);
                    }printf("\n");
                }else if(len>0){
                    h=j;
                    do{
                        k=j;
                        for(cnt=0,j=(k+1)%len;vis[j]!=0;j=(j+1)%len,cnt++);
                        if(cnt>0){
                            printf("%d",cnt);
                            for(j=(k+1)%len;vis[j]!=0;j=(j+1)%len){
                                printf(" %d",dot[j]*vis[j]);
                            }printf("\n");
                        }
                    }while(h!=j);
                }

            }
        }
	}
return 0;
}
/*
7 6
1 2
1 3
2 3
1 4
2 5
6 7

6 7
1 2
2 3
3 5
5 6
2 4
4 5
2 5

4 4
1 2
2 3
3 4
4 1

8 12
1 2
1 3
2 4
3 4
5 6
5 7
6 8
7 8
1 5
2 6
3 7
4 8
*/
