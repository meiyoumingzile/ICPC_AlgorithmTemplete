#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=10010;
const int mod=1e9+7;

struct Edge{
    int b,e;
    void sett(int b,int e){
        this->b=b;
        this->e=e;
    }
};
vector<Edge>adList[MAX];//邻接表 
int color[MAX];//代表某一点颜色，0未染色，1黑色，-1白色,color[0]是1或者-1都可以
int V,E;
void clear(){
	memset(color,0,sizeof(color));
	for(int i=0;i<MAX;i++){
		adList[i].clear();
	}
}
bool isBipartite(int now,int father){
    int i,next;
    color[now]=-color[father];
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        if(next!=father&&next!=now){
            if(color[next]==0){
                if(isBipartite(next,now)==0)
                    return 0;
            }else if(color[next]==color[now]){
                return 0;
            }
        }
    }
    return 1;
}
bool judge(){
    if(V<2)//二分图必须有2个以上点
        return false;
    memset(color,0,sizeof(color));
    color[0]=1;
    bool v=1;
    for(int i=1;i<=V;i++){//图可能分成多个联通分量，都要判断，对于每一块，用dfs
        if(color[i]==0){
            v*=isBipartite(i,0);//有一块不符合条件就不是二分图
        }
    }
    return v;
}
int main(){
	int i,j,k,T,b,e;
	Edge edge;
    cin>>T;
    while(T--){
        scanf("%d%d",&V,&E);
        for(i=1;i<=V;i++){
            adList[i].clear();
        }
        for(i=0;i<E;i++){
            scanf("%d%d",&b,&e);
            edge.sett(b,e);
            adList[b].push_back(edge);
            edge.sett(e,b);
            adList[e].push_back(edge);
        }
        string str=judge()?"Correct":"Wrong";
        printf("%s\n",str.c_str());
    }
return 0;
}


