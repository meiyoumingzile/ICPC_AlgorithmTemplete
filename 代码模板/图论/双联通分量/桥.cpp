#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;

struct Edge{//�ߣ�����ֻ������ֹ��
    int e=0;
};
vector<Edge>adList[MAX];
int V,E,cutEdgeCnt;//V������ٸ��㣬E�����������
int dfn[MAX],low[MAX];//dfn�������˳���ţ�low������ӽڵ�����С��
bool vis[MAX];
void tarjan(int now,int p,int &len){//�ݹ���룬now������[1,V]��ʼ�����ԣ���Ҫע����ܲ��ᱻ���ߵ���p�����������ĸ��ڵ��ʼ����-1��len�������
    int i,j,k,next;
    dfn[now]=low[now]=len++;
    vis[now]=1;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        if(vis[next]==0){//��dfn����dfs��vis�����ж���û�߹�
            tarjan(next,now,len);
            low[now]=min(low[now],low[next]);
            if(dfn[now]<low[next]){//�����ظ�������v���
                cutEdgeCnt++;
            }
         }else if(dfn[next] < dfn[now]&&next!=p){//��������ģ���ԭͼ������ͼ��Ҫ����ǲ��Ǹ��ڵ�,���ܸ��¸��ڵ�
             //���next���ʹ��ˣ���ôҲ���ٸ��µ��ڵ�now��low���Լ���dfn[next]��Сc
            // �Ҷ�������ͼӦ��ֻ��dfnС��now��next��������Ϊ�ϴ��û������
            low[now]=min(low[now],dfn[next]);
        }
    }
}
int getCutEdge(){
    int len,i,j;
    memset(vis,0,sizeof(vis));
    cutEdgeCnt=0;//����ʼ��
    for(i=1;i<=V;i++){
        if(vis[i]==0){
            len=1;//��ʼ������˳��
            tarjan(i,-1,len);
        }
    }
    return cutEdgeCnt;
}
int main(int argc,char *argv[]){
    int i,j,k,b,e;
    Edge edge;
    cin>>V>>E;
    for(i=0;i<E;i++){
        scanf("%d%d",&b,&e);
        edge.e=e;
        adList[b].push_back(edge);//����ͼ
        edge.e=b;
        adList[e].push_back(edge);//����ͼ
    }
    //ͼ�����ǲ���ͨ�ģ�Ӧ�ö���ж�֪�����е㶼���߹�tarjanΪֹ�����������ҵ�ÿһ��ĸ�㣬���忴����
    printf("%d\n",getCutEdge());
return 0;
}
/*
7 9
1 2
2 3
3 4
4 5
3 5
2 4
6 7
1 6
1 7
*/
