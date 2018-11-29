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
    int e,b;
    void sett(int b,int e){
        this->b=b;
        this->e=e;
    }
};
vector<Edge>adList[MAX];
int V,E;//V������ٸ��㣬E�����������
int dfn[MAX],low[MAX];//dfn�������˳���ţ�low������ӽڵ�����С��
bool vis[MAX];
int root,rootSonCnt,cutPointCnt;
bool isCutPoint[MAX];
stack<Edge>st;//ջ��ά��һЩ�ߣ��������˫��ͨ����
void popStack(stack<Edge> &st,Edge tar){//��ջֱ���ߵ���tar,����Ѱ�ҵ㣬˫��ͨ�����ı�,�õ�����Ҫ��һ������
    Edge now;
    int len=0;
    do{
        now=st.top();
        st.pop();
        printf("(%d %d) ",now.b,now.e);
        len++;
    }while(tar.b!=now.b||tar.e!=now.e);
    if(len==1){
        printf("����߰����ĵ㲻�ǵ�˫��ͨ����");
    }printf("\n");
}

void tarjan(int now,int p,int &len){//�ݹ���룬now������[1,V]��ʼ�����ԣ���Ҫע����ܲ��ᱻ���ߵ���p�����������ĸ��ڵ��ʼ����-1��len�������
    int i,j,k,next;
    dfn[now]=low[now]=len++;
    vis[now]=1;
    bool v=true;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        if(vis[next]==0){//��dfn����dfs��vis�����ж���û�߹�
            st.push(adList[now][i]);
            tarjan(next,now,len);
            low[now]=min(low[now],low[next]);
            if(now==root){//�Ǹ�,�Ѹ��ڵ㣬�ܵ������Ŀ��һ
                rootSonCnt++;//���ڵ��������������
                popStack(st,adList[now][i]);
            }else if(dfn[now]<=low[next]&&v){//�����ظ�������v���
                cutPointCnt++;
                v=false;
                popStack(st,adList[now][i]);
            }

        }else if(dfn[next] < dfn[now]&&next!=p){//��������ģ���ԭͼ������ͼ��Ҫ����ǲ��Ǹ��ڵ�,���ܸ��¸��ڵ�
             //���next���ʹ��ˣ���ôҲ���ٸ��µ��ڵ�now��low���Լ���dfn[next]��Сc
            // ����Ϊ����ջ���ظ��Ͷ��࣬��������ͼӦ��ֻ��dfnС��now��next��������Ϊ�ϴ��û������
            st.push(adList[now][i]);
            low[now]=min(low[now],dfn[next]);
        }
    }
}
int getCutPoint(){
    int len,i,j;
    memset(vis,0,sizeof(vis));
    memset(isCutPoint,0,sizeof(isCutPoint));
    cutPointCnt=0;//����ʼ��
    for(i=1;i<=V;i++){
        if(vis[i]==0){
            root=i;//��ʼ�����ڵ����ĸ�
            len=1;//��ʼ������˳��
            rootSonCnt=0;//��ʼ�����ڵ����������
            tarjan(root,-1,len);
            if(rootSonCnt>1){
                cutPointCnt++;
            }
        }
    }
    return cutPointCnt;
}

int main(int argc,char *argv[]){
    int i,j,k,b,e;
    Edge edge;
    cin>>V>>E;
    for(i=0;i<E;i++){
        scanf("%d%d",&b,&e);
        edge.sett(b,e);
        adList[b].push_back(edge);//����ͼ
        edge.sett(e,b);
        adList[e].push_back(edge);//����ͼ
    }
    //ͼ�����ǲ���ͨ�ģ�Ӧ�ö���ж�֪�����е㶼���߹�tarjanΪֹ�����������ҵ�ÿһ��ĸ�㣬���忴����
    printf("%d\n",getCutPoint());
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
