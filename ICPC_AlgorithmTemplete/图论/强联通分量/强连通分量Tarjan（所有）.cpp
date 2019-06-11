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
int V,E;//V代表多少个点，E代表多少条边


bool vis[MAX];//标记是不是被找过了
int dfn[MAX],low[MAX];//dfn代表访问顺序编号，low代表儿子节点编号最小的
stack<int>st;
bool inSt[MAX];//是否在栈里面
int newCnt=0;

void tarjan(int now,int &len){//递归代码，dot从任意[1,V]开始都可以，但要注意可能不会被都走到，len代表深度
    int i,j,k,next;
    st.push(now);
    dfn[now]=low[now]=len++;
    inSt[now]=1;
    vis[now]=1;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        if(dfn[next]==0&&vis[next]==0){//把dfn当做dfs的vis数组判断走没走过
            tarjan(next,len);
              //递归的更新low,按照low的定义，它的父节点now,应该是儿子当做最小的，每次dfs出来后更新父节点now
            low[now]=min(low[now],low[next]);
        }else if(inSt[next]==1){
            low[now]=min(low[now],low[next]);
        }else{//排除，inSt[next]==0&&vis[next]==1，那就什么都不做

        }
    }
    if(dfn[now]==low[now]){//没更新过low,说明有强联通分量，以这个点为开始.那些点正好是栈顶的，那么从栈弹出元素直到弹出当前点now
        do{
            k=st.top();
            st.pop();
            inSt[k]=0;//把它更新成不在栈里；
            printf("%d ",k);
        }while(k!=now);
        printf("\n");
        newCnt++;
    }
}

int main(int argc,char *argv[]){
   // freopen("p2002_data1.in","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,b,e,d,len;
    Edge edge;
    cin>>V>>E;
    for(i=0;i<E;i++){
        scanf("%d%d",&b,&edge.e);
        adList[b].push_back(edge);//有向图
    }


    memset(vis,0,sizeof(vis));
    memset(dfn,0,sizeof(dfn));//vis和dfn每次清空
    newCnt=0;
    for(i=1;i<=V;i++){//由于单个点为起点可能不会被全部找到，要循环的去试验
        if(vis[i]==0){
            /*
            *不需要更新dfn和low否则超时，为什么不需要更新，因为dfs里面是会在开始初始化的
            *inSt也不需要更新，因为做完一次 tarjan，由于所有点最终都会被出栈，inSt最坏会变回0
            */
            len=1;
            tarjan(i,len);
        }
    }

return 0;
}
/*
8 10
1 2
1 7
7 8
8 1
2 3
3 4
4 2
3 5
4 5
4 5


*/
