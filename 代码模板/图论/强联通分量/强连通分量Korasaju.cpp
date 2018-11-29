#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;

vector<int>adList[MAX];
vector<int>invLi[MAX];
int V,E;//V������ٸ��㣬E�����������

int endTime[MAX];
int beginTime[MAX];
int btEdge[MAX];
int vis[MAX];
void dfs(int now,int &bt,int &et){//����endTime���ĵ�ı��
    int i,next;
    if(now)
        beginTime[now]=bt++;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i];
        if(beginTime[next]==0){
            dfs(next,bt,et);
        }
    }
    if(now)
        endTime[now]=et++;
}

void dfsinv(int now){
    int i,next;
    vis[now]=1;
   // printf("%d ",now);
    for(i=0;i<invLi[now].size();i++){
        next=invLi[now][i];
        if(vis[next]==0){
            dfsinv(next);
        }
    }
}
int Kosaraju(){
    memset(vis,0,sizeof(vis));
    memset(beginTime,0,sizeof(beginTime));
    memset(endTime,0,sizeof(endTime));
    memset(btEdge,0,sizeof(btEdge));
    int cnt=0;//�м�����ͨ����
    int i,j,k;
    for(i=1;i<=V;i++){//��0�ܵ����κε�;
        adList[0].push_back(i);
    }
    int bt=1,et=1;
    dfs(0,bt,et);
    for(i=1;i<=V;i++){
        btEdge[endTime[i]]=i;

    }
    for(i=et-1;i>0;i--){
        k=btEdge[i];
        if(vis[k]==0){
            dfsinv(k);
            //printf("\n");
            cnt++;
        }
    }
    return cnt;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    //��Ŀ������hdu1269
    int i,j,k,b,e;
    while(~scanf("%d%d",&V,&E),V>0||E>0){
        for(i=0;i<E;i++){
            scanf("%d%d",&b,&e);
            adList[b].push_back(e);//����ͼ
            invLi[e].push_back(b);//��ͼ
        }
        k=Kosaraju();
        printf("%s\n",k==1?"Yes":"No");
        for(i=0;i<=V;i++){
            adList[i].clear();
            invLi[i].clear();
        }
    }

return 0;
}
/*
8 9
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
