#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=20010;
const int mod=1e9+7;

struct Edge{
    int e,val,k;
    Edge(){}
    Edge(const int &e,const int &val,const int &k){
        this->e=e;
        this->val=val;
        this->k=k;
    }
};
struct Graphic{
    int V,E,S,T,size=0;
    int head[MAX];
    Edge edge[200010];
    void push(const int &b,const int &e,const int &val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
    }
	void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
};
Graphic g;
int dfn[MAX],low[MAX];//dfn�������˳���ţ�low������ӽڵ�����С��
bool vis[MAX],isCut[MAX];//isCut�����ǲ��Ǹ��
int root,rootSonCnt,cutPointCnt;//root������ڵ㣬rootSonCnt������ڵ�����������cutPointCnt�����Ѿ��ҵ��ĸ������
void tarjan(int now,int p,int &len){//�ݹ���룬now������[1,V]��ʼ�����ԣ���Ҫע����ܲ��ᱻ���ߵ���p�����������ĸ��ڵ��ʼ����-1��len�������
    dfn[now]=low[now]=len++;
    vis[now]=1;
    isCut[now]=0;
    for(int i=g.head[now];i!=-1;i=g.edge[i].k){
        int e=g.edge[i].e;
        if(vis[e]==0){//��dfn����dfs��vis�����ж���û�߹�
            tarjan(e,now,len);
            low[now]=min(low[now],low[e]);
            if(now==root){//�Ǹ�,�Ѹ��ڵ㣬�ܵ������Ŀ��һ
                rootSonCnt++;//���ڵ��������������
            }else if(dfn[now]<=low[e]&&isCut[now]==0){//�����ظ�������v���
                cutPointCnt++;
                isCut[now]=1;//�ҵ�һ�����
            }
        }else if(dfn[e] < dfn[now]&&e!=p){//��������ģ���ԭͼ������ͼ��Ҫ����ǲ��Ǹ��ڵ�,���ܸ��¸��ڵ�
             //���e���ʹ��ˣ���ôҲ���ٸ��µ��ڵ�now��low���Լ���dfn[e]��Сc
            // �Ҷ�������ͼӦ��ֻ��dfnС��now��e��������Ϊ�ϴ��û������
            low[now]=min(low[now],dfn[e]);
        }
    }
}
int getCutPoint(){//ͼ�����ǲ���ͨ�ģ�Ӧ�ö���ж�֪�����е㶼���߹�tarjanΪֹ�����������ҵ�ÿһ��ĸ�㣬���忴����
    int len,i;
    memset(vis,0,sizeof(vis));
    memset(isCut,0,sizeof(isCut));
    cutPointCnt=0;//����ʼ��
    for(i=1;i<=g.V;i++){
        if(vis[i]==0){
            root=i;//��ʼ�����ڵ����ĸ�
            len=1;//��ʼ������˳��
            rootSonCnt=0;//��ʼ�����ڵ����������
            tarjan(root,-1,len);
            if(rootSonCnt>1){//�����ڵ��ǲ��Ǹ��
                isCut[root]=1;
                cutPointCnt++;
            }
        }
    }
    return cutPointCnt;
}
int main(int argc,char *argv[]){
    int i,b,e;
    while(~scanf("%d%d",&g.V,&g.E)){
        g.clear();
        for(i=0;i<g.E;i++){
            scanf("%d%d",&b,&e);
            g.push(b,e,0);
            g.push(e,b,0);
        }
        printf("%d\n",getCutPoint());//����
        for(i=1;i<=g.V;i++){
            if(isCut[i]){
                printf("%d ",i);
            }
        }
    }
return 0;
}
/*
8 8
1 2
2 3
3 4
4 5
3 5
2 4
6 7
7 8
*/
