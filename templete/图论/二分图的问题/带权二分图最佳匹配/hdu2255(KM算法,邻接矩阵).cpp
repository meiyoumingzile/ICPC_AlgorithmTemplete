#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1010;
const int mod=1e9+7;

//KM算法

struct Graphic{//邻接矩阵储存，因为方便访问边权，而且二分图最大权值匹配的数据一般很小算法复杂度本身就是n^3的
    int V1,V2;
    int adMat[1010][1010];
    void clear(){
        memset(adMat,0,sizeof(adMat));
    }
};
Graphic g;
int lx[MAX],ly[MAX],xtoy[MAX],ytox[MAX],visx[MAX],visy[MAX];//lx,ly是定点标号，xtoy是匈牙利算法中的表示x集每个点映射到y,而ytox表示y集合映射到x,vis[x]表示x集某个点有木有被访问
int minVal;
inline bool KM_dfs(int now){//找到一个最大匹配
    visx[now]=1;//标记x点
    for(rg int i=1;i<=g.V2;i++){
        const int &next=i;
        if(visy[next]==0){
            const int &t=lx[now]+ly[next]-g.adMat[now][next];
            if(t==0){
                visy[next]=1;//标记y点
                if(xtoy[next]==0||KM_dfs(xtoy[next])){
                    xtoy[next]=now;
                    ytox[now]=next;
                    return true;
                }
            }else{////不可能小于0
                if(t<minVal)minVal=t;//取个最小的t,看了t怎么来的就是知道，这意味着val最大，所以去min确找的是最大权值匹配
            }
        }
    }
    return false;
}
int KM(){
    int i,j,ans;
    memset(xtoy,0,sizeof(xtoy));
    memset(ytox,0,sizeof(ytox));
    memset(lx,0,sizeof(lx));
    memset(ly,0,sizeof(ly));
    for(i=1;i<=g.V1;i++){//初始化
        for(j=1;j<=g.V2;j++){
            lx[i]=max(lx[i],g.adMat[i][j]);
        }
    }
    for(i=1;i<=g.V1;i++){
        while(1){
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            minVal=INF;
            if(KM_dfs(i))
                break;
            for(j=1;j<=g.V1;j++)//更新x标顶,x的减去，加到y上
                if(visx[j])
                    lx[j]-=minVal;
            for(j=1;j<=g.V2;j++)//更新y标顶,x的减去，加到y上
                if(visy[j])
                    ly[j]+=minVal;
        }
    }
    for(i=1,ans=0;i<=g.V2;i++)//通过遍历g.V2到最大边权和,也可以遍历g.V1,道理一样
        ans+=g.adMat[i][ytox[i]];
    /*for(i=1,ans=0;i<=g.V1;i++)//通过遍历g.V2到最大边权和,也可以遍历g.V1,道理一样,但是本题输出y到x集合的权值,这是题意定的
        ans+=g.adMat[xtoy[i]][i];
        */
    return ans;
}
int main(){//链式前向星写法
	int i,j,k,T=0,n,cost;
    while(~scanf("%d",&n)){
        g.clear();
        for(i=1;i<=n;i++){
            for(j=1;j<=n;j++){
                scanf("%d",&g.adMat[i][j]);
            }
        }
        g.V1=g.V2=n;
        printf("%d\n",KM());
    }
return 0;
}

