#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=10010;
const int mod=1e9+7;

struct Edge {
    int b,e,val;
    void sett(int b,int e){
        this->b=b;
        this->e=e;
        this->val=0;
    }
};
vector<Edge>adList[MAX];//������,����ͼ
vector<Edge>li[MAX];//�����ѯ
int V,E;//V����
bool lcavis[MAX];
int p[MAX];//��ǰ�ڵ�ĸ��ڵ����ĸ�,����ȷ���Ǹ��Ǹ�����Ϊ���ڵ�û�и��ڵ�

struct Union{
    int father[MAX];
    int rank[MAX];
    void init(int n){
        for(int i=0;i<n;i++){
            father[i]=i;
            rank[i]=1;
        }
    }
    int GetFather(int son) {
        if(father[son]!=son)
            father[son]=GetFather(father[son]);
        return father[son];
    }
    void merge(int x, int y){//��ͨ�ϲ�����y���x���������ܽ��Ͳ�ѯЧ�ʣ����ǿ��Կ��Ƹ��ڵ����ĸ�
        father[y]=x;
    }
    bool isSameSet(int x, int y) {
        return GetFather(x)==GetFather(y);
    }
};
Union un;
void tarjan(int now,Union &un){//������now�ǵ�ǰ���ĵ㣬un��һ�����鼯����
    int i,k,next;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        tarjan(next,un);
        un.merge(now,next);//����ͨ���ӽ�next����now
        lcavis[next]=1;
    }
    for(i=0;i<li[now].size();i++){
        k=li[now][i].e;
        if(lcavis[k]){
            printf("(%d,%d)==%d\n",now,k,un.GetFather(k));//������˵Ҫ������Ŀ������˳��������浽li���valֵ�Ｔ��
        }
    }
}

int main(int argc,char *argv[]){
    int i,j,k,n,m,T,b,e,root;
    Edge edge;
    cin>>T;
    while(T--){
        scanf("%d",&V);

        for(i=1;i<=V;i++){
            adList[i].clear();
            li[i].clear();
        }
        memset(lcavis,0,sizeof(lcavis));
        memset(p,0,sizeof(p));
        for(i=0;i<V-1;i++){
            scanf("%d%d",&b,&e);
            edge.sett(b,e);
            adList[b].push_back(edge);
            p[e]=b;
        }
        for(i=1;i<=V;i++){//Ѱ�Ҹ��ڵ�
            if(p[i]==0){
                root=i;
                break;
            }
        }
        scanf("%d",&m);
        for(i=0;i<m;i++){
            scanf("%d%d",&b,&e);
            edge.sett(b,e);
            li[b].push_back(edge);
            edge.sett(e,b);
            li[e].push_back(edge);//��¼��ѯ�Ĺ������
        }
        un.init(V+1);
        tarjan(root,un);
    }
return 0;
}
/*
1
9
1 3
1 2
2 4
2 5
3 6
5 7
5 8
7 9
5
9 8
4 6
7 5
1 9
5 3
*/
