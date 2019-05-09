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


vector<Edge > adList[MAXDOT];
int dist[MAXDOT];//ά�������������ڶ�̬�滮��dp���飻�����������ʵ��ȡ���ڵ��������ͬ,�±����㣬һ���1��ʼ
int updateTimes[MAXDOT];

int V,E,S,T;//V�ǵ������E�Ǳ߸�����S������ţ�T���յ�ı��
int SPFA(int start,int V){//start������ţ�V�ǵ����
    int i,j;
    queue<int>dotQue;
    memset(updateTimes,0,sizeof(updateTimes));
    for(i=0;i<=V;i++){//��ʼ�����˵�һ����0�������������
        dist[i]=INF;
    }
    dist[start]=0;
    dotQue.push(start);
    while(!dotQue.empty()){
        int que_head=dotQue.front();
        dotQue.pop();
        for(i=0;i<adList[que_head].size();i++){
            int endDot=adList[que_head][i].e;
            if(dist[que_head]+adList[que_head][i].val<dist[endDot]){
                dist[endDot]=dist[que_head]+adList[que_head][i].val;
                dotQue.push(endDot);
                if(++updateTimes[endDot]>=V){
                    return -1;
                }
            }
        }
    }
    return 1;
}

int main(int argc,char *argv[]){
    int i,j,k;
    Edge w;
    cin>>V>>E>>S>>T;
    for(i=0;i<E;i++){
        scanf("%d%d%d",&w.b,&w.e,&w.val);
        adList[w.b].push_back(w);
    }
    if(SPFA(S,V)!=-1){
        for(i=1;i<=V;i++){
            printf("%d%c",dist[i],i==V?'\n':' ');
        }
    }
return 0;
}
