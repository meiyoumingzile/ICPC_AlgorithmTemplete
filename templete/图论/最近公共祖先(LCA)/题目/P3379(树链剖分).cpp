#include<bits/stdc++.h>
using namespace std;
const int MAX=500010;

list<int>adList[MAX];//������,����ͼ
int V,E;//V����
int sz[MAX],//�ӽڵ���Ŀ
p[MAX],//���ڵ���
h[MAX],//�߶�
top[MAX];//�����������˵��ؽڵ㣬����������ؽڵ����0
//bool isheavy[MAX];//�ӽڵ����ؽڵ���
int son[MAX];//�ӽڵ��У��ؽڵ���
inline void dfsh(int now){
    int k=0,next,maxsz=-1;
    for(list<int>::iterator i=adList[now].begin();i!=adList[now].end();++i){//�ȼ���c++11�﷨ for(auto i: adList[now]){next=i;
        next=*i;
        if(next!=p[now]){
            p[next]=now;
            h[next]=h[now]+1;
            dfsh(next);
            sz[now]+=sz[next]+1;
            if(maxsz<sz[next]){
                maxsz=sz[next];
                k=next;
            }
        }
    }
    son[now]=k;
}
inline void dfstop(int now){
    int next;
   // if(son[now]>0){//���Ǹ�������sz����
        top[son[now]]=top[now];//����if�ж����now��Ҷ�ӽ�㣬son[now]==0
   // }
    for(list<int>::iterator i=adList[now].begin();i!=adList[now].end();++i){//�ȼ���c++11�﷨ for(auto i: adList[now]){next=i;
        next=*i;
        if(next!=p[now]){
            dfstop(next);

        }
    }
}
inline int getLCA(int a,int b){
    while(1){
        if(top[a]==top[b])
            return h[a]<h[b]?a:b;
        else if(h[top[a]] > h[top[b]])
            a=p[top[a]];
        else
            b=p[top[b]];
    }
}
inline void init(int root){
    int i,k;
    for(i=1;i<=V;i++){//��ʼ��p
        top[i]=i;//��ʼ��top
    }
    dfsh(root);
    dfstop(root);
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
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
16 999 8
8 5
8 4
8 1
5 9
4 6
4 10
1 14
1 13
6 15
6 7
10 11
10 16
10 2
16 3
16 12


*/
