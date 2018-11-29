/*

�ڽӱ�,
��������
vectorʵ�֣�


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
vector<int>p[MAX];//p[u][i]�ڵ�u��������2^i�����ĸ��ڵ�
void printp(){
    int i,j;
    for(i=1;i<=V;i++){
        printf("%d:",p[i].size());
        for(j=0;j<p[i].size();j++){
            printf("%d ",p[i][j]);
        }printf("\n");
    }
}
void dfsh(int now){//�Ż����������ξ������٣���Ҫ�����
    int i,j,k,next;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        h[next]=h[now]+1;
        for(j=0;;j++){//���±�������
            k=p[next][j];
            if(p[k].size()>j){
                p[next].push_back(p[k][j]);
            }else{
                break;
            }
        }
        dfsh(next,deep+1);
    }
}
void toSameh(int &c,int minh){
    int i,k;
    for(i=0;i<p[c].size()&&h[p[c][i]]>=minh;i++);//�����������ͬ
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
    for(i=0;i<p[a].size()&&p[a][i]!=p[b][i];i++);//���������ͬ
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
        p[i].reserve(25);
        for(j=0;j<adList[i].size();j++){
            p[adList[i][j].e].push_back(i);//e�ڵ��2^0�Ĳ�����b
        }
    }
    for(i=1;i<=V;i++){//Ѱ�Ҹ�
        if(p[i].size()==0){
            root=i;
            break;
        }
    }
    printf("%d\n",root);
    dfsh(root,0);//��ʼ���߶Ⱥͱ�������
    printp();
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
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
