#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;
struct Data{
    int d;
    int cnt=1;//�ýڵ���ִ���
    int sumcnt=0;//�Լ��ڵ����ĸ����������ͬ�����ȥ
    bool com=0;//1����������ң�0�����Ҵ�����
};
Data A[MAX];

struct Node{
    Node *parent; //�ý��ĸ��ڵ㣬�������
    Node *son[2];//son[0]������son[1]������
    Data val; //���ֵ
    Node(){
        parent=son[0]=son[1]=NULL;
    }
    Node(Data val){
        parent=son[0]=son[1]=NULL;
        this->val=val;
    }
    int getfp(){//���ص�ǰ�ڵ��Ǹ��ڵ���ĸ����ӣ��󷵻�0���ҷ���1��û�и��ڵ㷵��-1
        if(parent==NULL)
            return -1;
        return parent->son[0]==this?0:1;
    }
    void updataSumcnt(){//���µ�ǰ���sumcnt��ֵ
        val.sumcnt=0;
        for(int i=0;i<2;i++){
            if(son[i]){
                val.sumcnt+=son[i]->val.sumcnt+son[i]->val.cnt;
            }
        }
    }
    void updataSumcnt(int k){//���ϸ���sumcntֱ��ǰ���ڵ�Ϊֹ
        for(Node *now=parent;now;now=now->parent)
            now->val.sumcnt+=k;
    }
    int getSum(int fp){//���ص�ǰ�ڵ���߻����ұߵĵ㣬�������ܺ�
        if(son[fp])
            return son[fp]->val.sumcnt+son[fp]->val.cnt;
        return 0;
    }
};

struct Splay{
    void reversal(Node *now);
    Node *root=NULL;//ԭʼ�ڵ㣬��߲��������ĸ�

    void linkNode(Node *now,Node *next,int fp){//fp 0������1������
        if(now&&fp!=-1)
            now->son[fp]=next;
        if(next)
            next->parent=now;
    }

    void build(int l,int r){//��һ��d��l��r����[l,r]
        Data data;
        data.d=l;
        root=new Node(data);
        Node *now=root,*node;
        int i;
        for(i=l+1;i<=r;i++,now=now->son[1]){//�����
            data.d=i;
            node=new Node(data);
            linkNode(now,node,1);
        }
        //printf("d");
        for(i=0;now;now=now->parent){//����sumcnt
            now->val.sumcnt=i++;
        }
    }

    void insertNode(Data val){
        Node *node=new Node(val);
        return insertNode(node);
    }
    void insertNode(Node *node){
        Node *now=root;//��ʼG��d�����޴�
        int fp;
        while(now){
            if(now->val.d == node->val.d){
                now->val.cnt++;
                now->updataSumcnt(1);
                delete node;
                return;
            }
            node->parent=now;
            fp=now->val.d > node->val.d?0:1;
            now=now->son[fp];
        }
        if(now!=root){
            linkNode(node->parent,node,fp);
            node->updataSumcnt(1);
        }else{
            root=node;
        }
    }

    Node *findNode(Data val){//ͬBST��
        int fp;
        for(Node *now=root; now ;now=now->son[fp]){
            if(now->val.d == val.d){
                if(now!=root)
                   topRoot(now);
                return now;
            }
            fp=now->val.d > val.d?now->val.com:1-now->val.com;
        }
        return NULL;
    }

    Node* rotate_zig(Node *now,int fp){//now�����ĸ��ڵ�Ϊ����fp��Ҫתnow����߻����ұ�
        Node *p=now->parent;
        Node *e=now->son[fp];
        int nowfp=now->getfp();
        linkNode(now,e->son[1-fp],fp);
        linkNode(e,now,1-fp);
        linkNode(p,e,nowfp);
        now->updataSumcnt();
        e->updataSumcnt();
        return e;
    }
    Node* rotate_zigzig(Node* now,int fp){//ͬ��˫��ת����fp��ָ��fp��1����������ҵ��ң�0������������
        Node *e,*pe, *p=now->parent;
        int nowfp=now->getfp();
        e=now->son[fp]->son[fp],pe=now->son[fp];//e��Ҫ��ת�����Ľڵ㣬pe��e�ĸ��ڵ㣬now��pe�ĸ��ڵ�
        linkNode(now,pe->son[1-fp],fp);
        linkNode(pe,e->son[1-fp],fp);
        linkNode(e,pe,1-fp);
        linkNode(pe,now,1-fp);
        now->updataSumcnt();
        pe->updataSumcnt();
        e->updataSumcnt();
        linkNode(p,e,nowfp);//������ת��ĸ��׽ڵ�
        return e;
    }
    Node* rotate_zigzag(Node* now,int fp){//����˫��ת��fp��1����������ҵ���0������������
        Node *e,*pe, *p=now->parent;
        int nowfp=now->getfp();
        e=now->son[fp]->son[1-fp],pe=now->son[fp];//e��Ҫ��ת�����Ľڵ㣬pe��e�ĸ��ڵ㣬now��pe�ĸ��ڵ�
        linkNode(now,e->son[1-fp],fp);
        linkNode(pe,e->son[fp],1-fp);
        linkNode(e,pe,fp);
        linkNode(e,now,1-fp);
        now->updataSumcnt();
        pe->updataSumcnt();
        e->updataSumcnt();
        linkNode(p,e,nowfp);//������ת��ĸ��׽ڵ�
        return e;
    }
    void topRoot(Node *node){//�����ڵ㵽��
        Node *tem,*p;
        for(tem=node;tem->parent;){
            p=tem->parent->parent;
            if(p==NULL){
                tem=rotate_zig(tem->parent,tem->getfp());
                break;
            }else if(tem->getfp()==tem->parent->getfp()){
                tem=rotate_zigzig(p,tem->getfp());
            }else{
                tem=rotate_zigzag(p,1 - tem->getfp());
            }
        }
        root=node;
    }
    bool deleteNode(Data val){
        Node *now,*temp,*p;
        now=findNode(val);
        if(now==NULL)
            return 0;
        if(now->val.cnt > 1){
            now->val.cnt--;
            now->updataSumcnt(-1);
            return 1;
        }
        temp=now;
        if(now->son[0]&&now->son[1]){
            for(temp=now->son[0];temp->son[1]!=NULL;temp=temp->son[1]);
            swap(now->val,temp->val);

            if(now->son[0]==temp){
                linkNode(now,temp->son[0],0);
            }else{
                linkNode(temp->parent,temp->son[0],1);
            }
            temp->updataSumcnt(- now->val.cnt);
            now->updataSumcnt();
            now->updataSumcnt(now->val.cnt-1);
        }else{
            int fp=now->son[0]?0:1;;
            if(now==root){
                root=now->son[fp];
                if(root)
                    root->parent=NULL;
            }else{
                linkNode(now->parent,now->son[fp],now->getfp());
                now->updataSumcnt(-1);
            }
        }
        delete temp;
        return 1;
    }

    void println(){//�������
        printf(":");
        __LDRprint(root);
        printf("\n");
    }
    void __LDRprint(Node *now){//�������
        if(now){
            __LDRprint(now->son[0]);
            printf("%d ",now->val.d);
            __LDRprint(now->son[1]);
        }
    }
    int findRank(Data val,int fp){//fp==0��ѯval.d��������,�ڼ�С(���ж����ͬ�����������С������),fp==1�෴
        Node *now=findNode(val);
        if(now==NULL)
            return -1;
        int sum=1;
        if(now->son[fp])
            sum+=now->getSum(fp);
        for(;now!=root;now=now->parent){
            if(now->getfp()!=fp){//�Ǹ������ұ߲ſ�����
                sum+=now->parent->val.cnt+now->parent->getSum(fp);
            }
        }
        return sum;
    }
    Node *findRankNode(int x,int fp){//���ؽڵ��Dָ�룬fp=0(��KС����),fp=1(��K�����),
        int fp1,pr=0,r=root->getSum(fp)+1;
        Node *now=root,*last=NULL;
        while(1){
            if(x==r)
                return now;
            fp1=x>r?1-fp:fp;
            if(now->son[fp1]==NULL){
                for(now;fp1==fp&&now;now=now->parent)
                    fp1=now->getfp();
                return now;
            }
            now=now->son[fp1];
            if(fp1!=fp){
                pr=r;
                last=now->parent;
                r=pr +  now->getSum(fp) + now->parent->val.cnt;
            }else{
                r=pr+now->getSum(fp);
                r+=last==NULL?1:last->val.cnt;
            }
        }
    }
    Node *getAdjoin(Node *now,int fp){//����ָ��,�Ҳ�������NULL��������now��������ڣ�fp==0��ʾС��now���������fp==1��ʾ����now����С��
        Node *e=now->son[fp];
        if(e){
            for(;e->son[1-fp];e=e->son[1-fp]);
        }else{
            for(e=now;e->getfp()==fp;e=e->parent);//û��fp�����ϵ��ӽڵ������£�������һ��һ����
            e=e->parent;
        }
        return e;
    }
    Node *getAdjoin(Data val,int fp){//����val���ڵĽڵ��ָ�룬fp==0��ʾС��now���������fp==1��ʾ����now����С��
        Node *now,*last;
        int fp1;
        for(now=root; now ;now=now->son[fp1]){
            if(now->val.d == val.d)
                return getAdjoin(now,fp);//������now���������
            last=now;
            fp1=now->val.d > val.d ? 0:1;
        }
        if(fp1==fp){
            for(now=last;now!=root&&now->getfp()==fp;now=now->parent);
            if(now!=root)
                return now->parent;
            return NULL;
        }else{
            return last;
        }
    }

    //�������:[l,r],����֮ǰbuild��������[1,r+2],[2,r+1]��ʾԭ������,
    //getSection��root����߾���Ҫ�ҵ����䣬����������
    void getSection(int l,int r){//�������:[l,r],����֮ǰbuild��������[1,r+2],[2,r+1]��ʾԭ������,
        Data data;
        data.d=l;
        findNode(data);//��l�����ڵ�
        Node *now,*temp;
        int fp;
        for(now=root; now ;now=now->son[fp]){//�ҵ�r+2�Ľڵ㣬����������ת�ڸ��ڵ��Ҷ���
            if(now->val.d == r+2)
                break;
            fp=now->val.d > r+2 ? now->val.com : 1-now->val.com;
        }
        //printf("%d \n",now->val.d);
       // println();
        for(temp=now;temp->parent!=root;  ){
            if(temp->parent==root->son[1]){
                temp=rotate_zig(temp->parent,temp->getfp());
                break;
            }else if(temp->getfp()==temp->parent->getfp()){
                temp=rotate_zigzig(temp->parent->parent,temp->getfp());
            }else{
                temp=rotate_zigzag(temp->parent->parent,1-temp->getfp());
            }
        }
    }
};


void Splay::reversal(Node *now){//�������䣬������ĳ���ڵ�Ϊ���������ӽڵ㣬�����ƻ�ƽ�����ṹ
    if(now){
        Node *left=now->son[0];
        linkNode(now,now->son[1],0);
        linkNode(now,left,1);
        now->val.com=1-now->val.com;
        reversal(now->son[0]);
        reversal(now->son[1]);
    }
}


int main(int argc,char *argv[]){
   // freopen("in2.in","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("myout.out","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int id,k,T;
    Node *e;
    scanf("%d",&T);
    Splay *t=new Splay();
    while(T--){
        Data data;
        scanf("%d%d",&id,&data.d);
        //printf("%d %d ",id,data.d);
        if(id==1){
            t->insertNode(data);
        }else if(id==2){
            t->deleteNode(data);
        }else if(id==3){
            printf("%d\n",t->findRank(data,0));
        }else if(id==4){
            e=t->findRankNode(data.d,0);
            if(e)
                printf("%d\n",e->val.d);
        }else if(id==5){
            e=t->getAdjoin(data,0);
            if(e){
                printf("%d\n",e->val.d);
            }
        }else if(id==6){
            e=t->getAdjoin(data,1);
            if(e){
                printf("%d\n",e->val.d);
            }
        }
    }
return 0;
}

