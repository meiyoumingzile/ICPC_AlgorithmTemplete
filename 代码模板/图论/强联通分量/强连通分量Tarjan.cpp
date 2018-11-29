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

int dfn[MAX],low[MAX];//dfn代表访问顺序编号，low代表儿子节点编号最小的
stack<int>st;
bool inSt[MAX];//是否在栈里面
void tarjan(int now,int &len){//递归代码，dot从任意[1,V]开始都可以，但要注意可能不会被都走到，len代表深度
    int i,j,k,next;
    st.push(now);
    dfn[now]=low[now]=len++;
    inSt[now]=1;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        if(dfn[next]==0){//把dfn当做dfs的vis数组判断走没走过
            tarjan(next,len);
            low[now]=min(low[now],low[next]);
        }else if(inSt[next]==1){
             //low[now]=min(low[now],dfn[next]),是等价的，因为inSt[next]==1说明在栈里，说明没更新过low==dfn,写哪个都一样
            low[now]=min(low[now],low[next]);
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
    }
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,b,e;
    Edge edge;
    cin>>V>>E;
    for(i=0;i<E;i++){
        scanf("%d%d",&b,&edge.e);
        adList[b].push_back(edge);//有向图
    }
    int len=1;
    tarjan(1,len);//不一定能找到所有的环，因为有可能1不能到达全部点,样例里6是被孤立的
return 0;
}
/*
7 9
1 2
1 7
7 8
8 1
2 3
3 4
4 2
3 5
4 5
*/
