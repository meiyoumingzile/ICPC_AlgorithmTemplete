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
int V,E;//V������ٸ��㣬E�����������

int dfn[MAX],low[MAX];//dfn�������˳���ţ�low������ӽڵ�����С��
stack<int>st;
bool inSt[MAX];//�Ƿ���ջ����
void tarjan(int now,int &len){//�ݹ���룬dot������[1,V]��ʼ�����ԣ���Ҫע����ܲ��ᱻ���ߵ���len�������
    int i,j,k,next;
    st.push(now);
    dfn[now]=low[now]=len++;
    inSt[now]=1;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        if(dfn[next]==0){//��dfn����dfs��vis�����ж���û�߹�
            tarjan(next,len);
            low[now]=min(low[now],low[next]);
        }else if(inSt[next]==1){
             //low[now]=min(low[now],dfn[next]),�ǵȼ۵ģ���ΪinSt[next]==1˵����ջ�˵��û���¹�low==dfn,д�ĸ���һ��
            low[now]=min(low[now],low[next]);
        }
    }
    if(dfn[now]==low[now]){//û���¹�low,˵����ǿ��ͨ�������������Ϊ��ʼ.��Щ��������ջ���ģ���ô��ջ����Ԫ��ֱ��������ǰ��now
        do{
            k=st.top();
            st.pop();
            inSt[k]=0;//�������³ɲ���ջ�
            printf("%d ",k);
        }while(k!=now);
        printf("\n");
    }
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,j,k,b,e;
    Edge edge;
    cin>>V>>E;
    for(i=0;i<E;i++){
        scanf("%d%d",&b,&edge.e);
        adList[b].push_back(edge);//����ͼ
    }
    int len=1;
    tarjan(1,len);//��һ�����ҵ����еĻ�����Ϊ�п���1���ܵ���ȫ����,������6�Ǳ�������
return 0;
}
/*
7 9
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
