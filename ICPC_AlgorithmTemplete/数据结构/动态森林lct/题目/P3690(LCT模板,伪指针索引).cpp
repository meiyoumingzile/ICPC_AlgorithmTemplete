#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
const int INF=2147483647;////2139062143
const int MAX=3000010;

void println(int *arr,int b,int e){//[b,e)
    printf("(%d:%d)",b,arr[b]);
    for(int i=b+1;i<e;i++){
        printf(" (%d:%d)",i,arr[i]);
    }printf("\n");
}
struct LCT{
    int n,p[MAX],son[MAX][2],val[MAX],xorsum[MAX];
    bool lz[MAX];//�����ǣ�������splay�����䷭ת��
    /*p[i]��i���ڵ�; son[i]��i���Ҷ���,0������ߣ�1�����ұ�,son[i][0]=0�����ָ�룬son��ָsplay�Ķ���
    val[i]�ǵ�iȨֵ��xorsum[i]��i����
    */

    LCT(){
       // memset();
    }

    void pushdown(){

    }
    void pushup(){

    }
    int makeroot(int now){//����ͨ������ĸ������µĽڵ�x��Ϊ��ͨ������ĸ�
        access(x);
        splay(x);
        reversal(x);
    }
    void access(int now){//��now���ö�����ĸ��ڵ��·�������splay
        for(int ch=0;now;ch=now,now=p[now]){//ch��now�Ķ��ӣ�ch=0�����ʼ�ǿգ���ʼ
            splay(now);
            son[now][1]=ch;
            update(now);//���ӱ��ˣ���Ҫ��ʱ�ϴ���Ϣ
        }
    }
    void splay(int now){//��now��ת�������ڵĸ��ڵ�
        stack<int>st;
        int p=now;
        st.push(now);
        while(){//���Ҫ�������¸���

        }
        for(int fp=getfp(now);fp!=-1;fp=getfp(now)){
            p=p[now];
            rotate(p,fp);
        }
    }
    int query(int x,int y){//��ѯ����
        split(x,y);
        return xorsum[y];
    }

    void linkNode(int x,int next,int fp){
        son[x][fp]=next;
        p[next]=x;
    }
    int getfp(int x){//����-1��ʾ�˵��Ǹ�,���򷵻ط���
        if(son[p[x]][0]==x)
            return 0;
        if(son[p[x]][1]==x)
            return 1;
        return -1;
    }
    int rotate(int x,int fp){//����ת��fp��ָ��Ҫתx����߻����ұߣ�1����תx���ұߣ�����������ת��
        int p=p[x],e=son[x][fp];
        int xfp=getfp(x);
        linkNode(x,son[e][fp^1],fp);
        linkNode(e,x,fp^1);
        linkNode(p,e,xfp);
        update(x);
        update(e);
        return e;
    }
    void reversal(int now){//Splay���䷭ת����
        swap(son[x][0],son[x][1]);
        lz[x]^=1;//rΪ���䷭ת���������
    }
    void update(int x){//���µ�ǰ���ֵ,���Լ������ͣ������Ҷ��������val[x]�����忴��Ŀ����
        xorsum[x]=xorsum[son[x][0]]^xorsum[son[x][0]]^val[x];
    }
    void pushdown(int x){//�жϲ��ͷ������
        if(lz[x]){
            if(son[x][0])reversal(son[x][0]);
            if(son[x][1])reversal(son[x][1]);
            lz[x]=0;
        }
    }
};
LCT lct;
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
	int i,j,k,t,T,n,m,id,x,y;
    scanf("%d%d",&n,&m);
    for(i=0;i<n;i++){
        scanf("%d",&lct.val[i]);
    }
    while(m--){
        scanf("%d%d%d",&id,&x,&y);
        switch(id){
            case 0://���ش� x �� y ��·���ϵĵ��Ȩֵ��xor �͡���֤ x �� y ����ͨ��
                lct.split(x,y);
                printf("%d\n",lct.xorsum[y]);
                break;
            case 1://����edge(x,y)�����ڣ�����������������ʲô������
                lct.link(x,y);
                break;
            case 2://����edge(x,y)���ڣ���ɾ��������������ʲô������
                lct.cut(x,y);
                break;
            case 3://�ѵ�x���Ȩֵ���y
                lct.splay(x);
                lct.val[x]=y;//�Ȱ�xת��ȥ�ٸģ���Ȼ��Ӱ��Splay��Ϣ����ȷ��
                break;
        }
    }
return 0;
}
