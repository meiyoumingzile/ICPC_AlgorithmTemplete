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


vector<int>ind[MAX];//�洢ǿ��ͨ��������ͼ��Ӧ��ı�
int kind[MAX];//���������ͼ��ÿ��������ʲô����
int into[MAX];//��ͼÿ������ȣ�������Ҳû��ϵ

vector<Edge>adList[MAX];
int V,E;//V������ٸ��㣬E�����������


bool vis[MAX];//����ǲ��Ǳ��ҹ���
int dfn[MAX],low[MAX];//dfn�������˳���ţ�low������ӽڵ�����С��
stack<int>st;
bool inSt[MAX];//�Ƿ���ջ����
int cnt=0;

void tarjan(int now,int &len){//�ݹ���룬dot������[1,V]��ʼ�����ԣ���Ҫע����ܲ��ᱻ���ߵ���len�������
    int i,j,k,next;
    st.push(now);
    dfn[now]=low[now]=len++;
    inSt[now]=1;
    vis[now]=1;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        if(dfn[next]==0&&vis[next]==0){//��dfn����dfs��vis�����ж���û�߹�
            tarjan(next,len);
              //�ݹ�ĸ���low,����low�Ķ��壬���ĸ��ڵ�now,Ӧ���Ƕ��ӵ�����С�ģ�ÿ��dfs��������¸��ڵ�now
            low[now]=min(low[now],low[next]);
        }else if(inSt[next]==1){//��ջ��
            low[now]=min(low[now],low[next]);
        }
    }
    if(dfn[now]==low[now]){//û���¹�low,˵����ǿ��ͨ�������������Ϊ��ʼ.��Щ��������ջ���ģ���ô��ջ����Ԫ��ֱ��������ǰ��now
        do{
            k=st.top();
            st.pop();
            inSt[k]=0;//�������³ɲ���ջ�
            ind[cnt+1].push_back(k);
            kind[k]=cnt+1;
        }while(k!=now);
        cnt++;
    }
}

void narrow(){
    int i,j,k;
    Edge edge;
    for(i=1;i<=V;i++){
        for(j=0;j<adList[i].size();j++){
            k=adList[i][j].e;
            if(kind[k]!=kind[i]){
                into[kind[k]]++;
            }
        }
    }

}
int main(int argc,char *argv[]){
   // freopen("p2002_data1.in","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,j,k,b,e,d,len;
    Edge edge;
    cin>>V>>E;
    for(i=0;i<E;i++){
        scanf("%d%d",&b,&edge.e);
        adList[b].push_back(edge);//����ͼ
    }


    cnt=0;
    for(i=1;i<=V;i++){//���ڵ�����Ϊ�����ܲ��ᱻȫ���ҵ���Ҫѭ����ȥ����
        if(vis[i]==0){//����Ҫ����dfn��low����ʱ��Ϊʲô����Ҫ���£���Ϊdfs�����ǻ��ڿ�ʼ��ʼ����
            len=1;
            tarjan(i,len);//
        }
    }
    narrow();
    for(i=1,k=0;i<=cnt;i++){
        if(into[i]==0){
            k++;
        }
    }
    printf("%d\n",k);
return 0;
}
/*
5 9
1 5
1 2
2 5
2 3
3 5
3 4
4 5
4 1
5 2



*/
