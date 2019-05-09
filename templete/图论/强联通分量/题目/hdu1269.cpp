#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;

struct Edge{//边，这里只存了终止点
    int e=0;
};

vector<Edge>adList[MAX];
int N,M,cnt;


bool vis[MAX];//标记是不是被找过了
int dfn[MAX],low[MAX];//dfn代表访问顺序编号，low代表儿子节点编号最小的
stack<int>st;
bool inSt[MAX];//是否在栈里面
void tarjan(int now,int &len){//递归代码，dot从任意[1,V]开始都可以，但要注意可能不会被都走到，len代表深度
    int i,j,k,next;
    st.push(now);
    dfn[now]=low[now]=len++;
    inSt[now]=1;
    vis[now]=1;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        if(inSt[next]==0){//把dfn当做dfs的vis数组判断走没走过
            tarjan(next,len);
        }
           //递归的更新low,按照low的定义，它的父节点now,应该是儿子当做最小的，每次dfs出来后更新父节点now
        low[now]=min(low[now],low[next]);
    }
    if(dfn[now]==low[now]){//没更新过low,说明有强联通分量，以这个点为开始.那些点正好是栈顶的，那么从栈弹出元素直到弹出当前点now
        do{
            k=st.top();
            st.pop();
            inSt[k]=0;//把它更新成不在栈里
        }while(k!=now);
        cnt++;
    }
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,b,e,len;
    Edge edge;
    while(~scanf("%d%d",&N,&M),M>0||N>0){

        for(i=0;i<M;i++){
            scanf("%d%d",&b,&edge.e);
            adList[b].push_back(edge);//有向图
        }


        cnt=0;
        memset(vis,0,sizeof(vis));
        for(i=1;i<=N;i++){//由于单个点为起点可能不会被全部找到，要循环的去试验
            if(vis[i]==0){
                memset(dfn,0,sizeof(dfn));
                memset(low,0,sizeof(low));
                memset(inSt,0,sizeof(inSt));
                len=1;
                tarjan(i,len);//
            }
        }
        printf("%s\n",cnt==1?"Yes":"No");
        for(i=1;i<=N;i++){
            adList[i].clear();
        }
    }

return 0;
}

