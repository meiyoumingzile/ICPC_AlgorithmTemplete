#include<bits/stdc++.h>
using namespace std;
const int MAX=500010;
list<int>adList[MAX];//������,����ͼ
int V,E;//V����
int h[MAX];//�߶�
int p[MAX][25];//p[u][i]�ڵ�u��������2^i�����ĸ��ڵ�
int pLen[MAX];
inline  void dfsh(int now,int father){
    int k,j,next;
    for(list<int>::iterator i=adList[now].begin();i!=adList[now].end();++i){//�ȼ���c++11�﷨ for(auto i: adList[now]){next=i;
        next=*i;
        if(next!=father){
            h[next]=h[now]+1;
            p[next][pLen[next]++]=now;
            for(j=0;;j++){//���±�������
                k=p[next][j];
                if(pLen[k]>j){
                    p[next][pLen[next]++]=p[k][j];
                }else{
                    break;
                }
            }
            dfsh(next,now);
        }
    }
}
inline  void toSameh(int &c,int minh){
    int i,k;
    for(i=pLen[c]-1;i>=0&&h[p[c][i]]<minh;--i);//�����������ͬ
    c=p[c][i];
    if(h[c]>minh){
        toSameh(c,minh);
    }
}
inline  int toSameDot(int a,int b){
    if(a==b)
        return a;
    int i;
    for(i=0;i<pLen[a]-1&&p[a][i]!=p[b][i];++i);//���������ͬ
    --i;
    if(i==-1){
        return p[a][0];
    }
    return toSameDot(p[a][i],p[b][i]);
}
inline  int getLCA(int a,int b){
    int i,j,k;
    if(h[a]!=h[b]){//s��ȵ�����ͬ
        int &c=h[a]>h[b]?a:b;//�õ����ǵ�����
        toSameh(c,min(h[a],h[b]));
    }
    return toSameDot(a,b);
}
inline void init(int root){
    dfsh(root,0);//��ʼ���߶Ⱥͱ�������,��1��������
}
int main(int argc,char *argv[]){
    int i,j,k,n,m,T,b,e,a,root,Q;
    scanf("%d%d%d",&V,&Q,&root);//V����Q�β�ѯ
    for(i=1;i<V;i++){//V-1����,��֤������һ�������ҵ�һ�����ǵڶ������ĸ��ڵ�
        scanf("%d%d",&b,&e);
        adList[b].push_back(e);
        adList[e].push_back(b);
    }
    init(root);
    for(i=0;i<Q;i++){//Q�β�ѯ
        scanf("%d%d",&a,&b);
        printf("%d\n",getLCA(a,b));
    }
return 0;
}

/*
12 999 12
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
