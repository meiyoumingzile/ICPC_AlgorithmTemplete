#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<map>
#include<set>
//#include<windows.h>
using namespace std;
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LL long long
#define ll long long
#define inf 1e-5
const int INF=2147483647;
const int MAX=1010;
const int mod=1e9+7;

struct Edge{//�ߣ�����ֻ������ֹ��
    int e;
};

vector<Edge>adList[MAX];
int V,E;//V������ٸ��㣬E�����������

int dfn[MAX],low[MAX];//dfn�������˳���ţ�low������ӽڵ�����С��
bool vis[MAX];
int root,cutPointCnt,rootSonCnt;

void tarjan(int now,int p,int &len){//�ݹ���룬dot������[1,V]��ʼ�����ԣ���Ҫע����ܲ��ᱻ���ߵ���len�������
    int i,j,k,next;
    dfn[now]=low[now]=len++;
    vis[now]=1;
    bool v=true;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        if(vis[next]==0){//��dfn����dfs��vis�����ж���û�߹�
            tarjan(next,now,len);
            low[now]=min(low[now],low[next]);
            if(now==root){//�Ǹ�,�Ѹ��ڵ㣬�ܵ������Ŀ��һ
                rootSonCnt++;//���ڵ��������������
            }else if(dfn[now]<=low[next]&&v){//�����ظ�������v���
                cutPointCnt++;
                v=false;
            }
        }else if(dfn[next] < dfn[now]&&next!=p){//��������ģ���ԭͼ������ͼ��Ҫ����ǲ��Ǹ��ڵ�,���ܸ��¸��ڵ�
             //���next���ʹ��ˣ���ôҲ���ٸ��µ��ڵ�now��low���Լ���dfn[next]��Сc
            // ����Ϊ����ջ���ظ��Ͷ��࣬��������ͼӦ��ֻ��dfnС��now��next��������Ϊ�ϴ��û������
            low[now]=min(low[now],dfn[next]);
        }
    }
}

int getCutPoint(){
    int len,i,j;
    memset(vis,0,sizeof(vis));
    cutPointCnt=0;//����ʼ��
    for(i=1;i<=V;i++){
        if(vis[i]==0){
            root=i;//��ʼ�����ڵ����ĸ�
            len=1;//��ʼ������˳��
            rootSonCnt=0;//��ʼ�����ڵ����������
            tarjan(root,-1,len);
            if(rootSonCnt>1)
                cutPointCnt++;
        }
    }
    return cutPointCnt;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,j,k,b,e,n;
    Edge edge;
    while(~scanf("%d",&V)&&V>0){
        for(i=1;i<=V;i++){
            adList[i].clear();
        }
        while(~scanf("%d",&b)&&b>0){
            while(getchar() != '\n'){
                scanf("%d",&e);
                edge.e=e;
                adList[b].push_back(edge);
                edge.e=b;
                adList[e].push_back(edge);
            }
        }
        //ͼ�����ǲ���ͨ�ģ�Ӧ�ö���ж�֪�����е㶼���߹�tarjanΪֹ�����������ҵ�ÿһ��ĸ�㣬���忴����
        printf("%d\n",getCutPoint());
    }
return 0;
}

