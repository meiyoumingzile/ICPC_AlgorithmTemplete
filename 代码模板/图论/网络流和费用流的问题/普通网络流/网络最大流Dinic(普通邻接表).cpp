#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;
/*
以洛谷3376为例，数据比较特殊，输入数据不存在相互反向的边，邻接表可以储存反向边编号优化，链式前向星可以用数组相邻元素边存储相反边方式优化，目的是能用o1时间找到相反边而不是迭代寻找。
这里是不加特殊优化的代码
*/
struct Edge{
    int b,e,v;
    Edge(){}
    Edge(int b,int e,int v){
        this->b=b;
        this->e=e;
        this->v=v;
    }
};
struct Dot{//bfs用
    int d,len;
    Dot(){}
    Dot(int d,int len){
        this->d=d;
        this->len=len;
    }
};
int V,E,S,T;//点数边数，起点终点
vector<Edge>adList[MAX];//邻接表
Edge load[MAX];//储存路径，b代表起点，e代表这条边在邻接表中编号
int layer[MAX];
bool Dinic_bfs(){//分层,只需要找到T点即可停止，找不到T返回false，D是为了更好的储存层数，否则要开两个队列，找不到T返回false
    int i,minv=INF,b,e;
    queue<Dot>que;
    Dot now(S,0),next;
    memset(layer,-1,sizeof(layer));
    layer[S]=0;
    que.push(now);
    while(!que.empty()){
        now=que.front();
        que.pop();
        if(now.d==T)
            return 1;
        for(i=0;i<adList[now.d].size();i++){
            e=adList[now.d][i].e;
            if(layer[e]==-1&&adList[now.d][i].v>0){
                next.d=e;
                layer[e]=next.len=now.len+1;
                que.push(next);
            }
        }
    }
    return 0;
}
int Dinic_dfs(int now){//dfs寻找路径，load储存的是路径，load[i].b是起点，e代表这条边在邻接表中编号。
    int i,j,k,e,pb,pe,val,minv,sumv=0;
    for(i=0;i<adList[now].size();i++){
        e=adList[now][i].e;
        val=adList[now][i].v;
        if(layer[e]==layer[now]+1){
            load[layer[now]]=Edge(now,i,val);
            if(e==T){//如果下个点是终点
                for(j=0,minv=INF;j<=layer[now];j++){//沿着路径寻找最小值
                     minv=min(minv,adList[load[j].b][load[j].e].v);
                }
                for(j=0;j<=layer[now];j++){//路径上的每条边增广
                    pb=load[j].b;
                    pe=adList[pb][load[j].e].e;
                    adList[pb][load[j].e].v-=minv;
                    for(k=0;k<adList[pe].size()&&adList[pe][k].e!=pb;k++);
                    if(k==adList[pe].size()){
                        Edge edge(pb,pe,minv);
                        adList[pe].push_back(edge);
                    }else{
                        adList[pe][k].v+=minv;
                    }
                }
                sumv+=minv;
            }else{
                sumv+=Dinic_dfs(e);
            }
        }
    }
    return sumv;//返回找到的可行的方案权值总和，没有自然就是0
}
int Dinic(){
    int sumVal=0;
    while(Dinic_bfs()){//多次调用直到不能分层
        sumVal+=Dinic_dfs(S);
    }
    return sumVal;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,b;
    scanf("%d%d%d%d",&V,&E,&S,&T);
    Edge edge;
    for(i=0;i<E;i++){
        scanf("%d%d%d",&edge.b,&edge.e,&edge.v);
        adList[edge.b].push_back(edge);
    }
    printf("%d\n",Dinic());
return 0;
}

