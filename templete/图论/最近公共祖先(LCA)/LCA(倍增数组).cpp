/*
�ڽӱ�,
��������
����ʵ�֣�
*/
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
int V,E;//V����
int h[MAX];//�߶�
int p[MAX][15];//p[u][i]�ڵ�u��������2^i�����ĸ��ڵ�
int pLen[MAX];

void dfsh(int now){
    int i,j,k,next;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        h[next]=h[now]+1;
        for(j=0;;j++){//���±�������
            k=p[next][j];
            if(pLen[k]>j){
                p[next][pLen[next]++]=p[k][j];
            }else{
                break;
            }
        }
        dfsh(next);
    }
}
void toSameh(int &c,int minh){
    int i,k;
    for(i=0;i<pLen[c]&&h[p[c][i]]>=minh;i++);//�����������ͬ
    i--;
    c=p[c][i];
    if(h[c]>minh){
        toSameh(c,minh);
    }
}
int toSameDot(int a,int b){
    if(a==b)
        return a;
    int i;
    for(i=0;i<pLen[a]&&p[a][i]!=p[b][i];i++);//���������ͬ
    i--;
    if(i==-1){
        return p[a][0];
    }
    return toSameDot(p[a][i],p[b][i]);
}

int getLCA(int a,int b){
    int i,j,k;
    if(h[a]!=h[b]){//��һ������Ƚ�С�ĵ�ᵽ���ڵ�
        int &c=h[a]>h[b]?a:b;//�õ����ǵ�����
        toSameh(c,min(h[a],h[b]));
    }
    return toSameDot(a,b);
}
void init(){
    int i,k,j,root;
    for(i=1;i<=V;i++){//��ʼ����������
        for(j=0;j<adList[i].size();j++){
            k=adList[i][j].e;
            p[k][pLen[k]++]=i;
        }
    }
    for(i=1;i<=V;i++){//Ѱ�Ҹ�
        if(pLen[i]==0){
            root=i;
            break;
        }
    }
    dfsh(root);//��ʼ���߶Ⱥͱ�������
}

int main(int argc,char *argv[]){
    int i,j,k,n,m,T,b,e,a,root,Q;
    Edge edge;
    scanf("%d%d",&V,&Q);//V����Q�β�ѯ
    for(i=1;i<V;i++){//V-1����,��֤������һ�������ҵ�һ�����ǵڶ������ĸ��ڵ�
        scanf("%d%d",&b,&e);
        edge.sett(b,e);
        adList[b].push_back(edge);
    }
    init();
    for(i=0;i<Q;i++){//Q�β�ѯ
        scanf("%d%d",&a,&b);
        printf("LCA:%d\n",getLCA(a,b));
    }
return 0;
}
/*
12 999
1 2
1 3
1 4
3 5
3 6
6 7
12 1
4 8
8 11
2 9
9 10
*/
