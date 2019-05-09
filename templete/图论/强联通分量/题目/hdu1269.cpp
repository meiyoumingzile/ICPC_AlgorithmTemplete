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
int N,M,cnt;


bool vis[MAX];//����ǲ��Ǳ��ҹ���
int dfn[MAX],low[MAX];//dfn�������˳���ţ�low������ӽڵ�����С��
stack<int>st;
bool inSt[MAX];//�Ƿ���ջ����
void tarjan(int now,int &len){//�ݹ���룬dot������[1,V]��ʼ�����ԣ���Ҫע����ܲ��ᱻ���ߵ���len�������
    int i,j,k,next;
    st.push(now);
    dfn[now]=low[now]=len++;
    inSt[now]=1;
    vis[now]=1;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        if(inSt[next]==0){//��dfn����dfs��vis�����ж���û�߹�
            tarjan(next,len);
        }
           //�ݹ�ĸ���low,����low�Ķ��壬���ĸ��ڵ�now,Ӧ���Ƕ��ӵ�����С�ģ�ÿ��dfs��������¸��ڵ�now
        low[now]=min(low[now],low[next]);
    }
    if(dfn[now]==low[now]){//û���¹�low,˵����ǿ��ͨ�������������Ϊ��ʼ.��Щ��������ջ���ģ���ô��ջ����Ԫ��ֱ��������ǰ��now
        do{
            k=st.top();
            st.pop();
            inSt[k]=0;//�������³ɲ���ջ��
        }while(k!=now);
        cnt++;
    }
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,j,k,b,e,len;
    Edge edge;
    while(~scanf("%d%d",&N,&M),M>0||N>0){

        for(i=0;i<M;i++){
            scanf("%d%d",&b,&edge.e);
            adList[b].push_back(edge);//����ͼ
        }


        cnt=0;
        memset(vis,0,sizeof(vis));
        for(i=1;i<=N;i++){//���ڵ�����Ϊ�����ܲ��ᱻȫ���ҵ���Ҫѭ����ȥ����
            if(vis[i]==0){
                memset(dfn,0,sizeof(dfn));
                memset(low,0,sizeof(low));
                memset(inSt,0,sizeof(inSt));
                len=1;
                tarjan(i,len);//
            }
        }
        printf("%s\n",cnt==1?"Yes":"No");
        for(i=1;i<=N;i++){
            adList[i].clear();
        }
    }

return 0;
}

