#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<map>
#include<bitset>
using namespace std;
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LL long long
#define ll long long
#define inf 1e-5
const int MAXDOT=10010;
const int MAXEDGE=10010;
const int INF=2147483647;


struct Edge{//��ʾ�ߣ���������ߴӡ�b����e;w��Ȩֵ
    int b,e,val;
    void sett(int b,int e,int val){
        this->b=b;
        this->e=e;
        this->val=val;
    }
};
vector<Edge>edge;//�͵Ͻ�˹�����㷨��һ����Ҫ����ͨ���鴢����Ǳߣ��ڽӱ����鷳
int dist[MAXDOT];//�͵Ͻ�˹�����㷨һ����dist���Ǵ���ԭ�㵽���Ϊi�ıߵ����·

int N,M,S,E;//N�ǵ������M�Ǳ߸�����B������ţ�E���յ�ı��

int BellmanFord(int start,int N){
    int i,j;
    bool isDistUpdate=true;
    for(i=1;i<=N;i++){//��ʼ�����˵�һ����0�������������
        dist[i]=INF;
    }
    dist[start]=0;
    for(j=1;j<N&&isDistUpdate==true;j++){//ѭ��dotNum-1�Ρ�
        isDistUpdate=false;
        for(i=0;i<edge.size();i++){//����ÿһ��������������Distant[u] + w(u, v) < Distant[v]������Distant[v] = Distant[u]+w(u, v)
            if(dist[edge[i].b]+edge[i].val<dist[edge[i].e]){
                dist[edge[i].e]=dist[edge[i].b]+edge[i].val;
                isDistUpdate=true;
            }
        }
    }
    for(i=0;i<edge.size();i++){//�ٱ���һ�Σ��ж��Ƿ��и���������Distant[u] + w(u, v)>Distant[v]���и�������-1
        if(dist[edge[i].b]+edge[i].val<dist[edge[i].e]){
            return -1;
        }
    }
    return 1;
}


int main(int argc,char *argv[]){
    int i,j,k;
    Edge w;
    cin>>N>>M>>S>>E;
    edge.reserve(MAXEDGE);
    for(i=0,j=0;i<M;i++){
        scanf("%d%d%d",&w.b,&w.e,&w.val);
        edge.push_back(w);
    }
    if(BellmanFord(S,N)!=-1){
        for(i=1;i<=N;i++){
            printf("%d%c",dist[i],i==N?'\n':' ');
        }
    }
    /*for(i=E;i!=0;i=last[i]){
        printf("%d ",i);
    }*/
return 0;
}
/*
4 5
1 2 2
2 3 4
4 3 1
4 2 -2
1 4 1
*/
