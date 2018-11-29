#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;
int N;

struct Data{
    int d,a;//d�����������������ң�a����ʵ��ֵ�����������������ǽ���a��
    int cnt=1;//�ýڵ���ִ���
    int sumcnt=0;//���ӽڵ������ܸ����������ͬ�����ȥ
    bool lazy=0;//�Ƿ񽻻�������1������
    void init(int d,int a){
        this->d=d;
        this->a=a;
    }
};

struct Node{
    Node *p; //�ý��ĸ��ڵ㣬�������
    Node *son[2];//son[0]������son[1]������
    Data val; //���ֵ
    Node(){
        p=son[0]=son[1]=NULL;
    }
    Node(Data val){
        p=son[0]=son[1]=NULL;
        this->val=val;
    }
    Node* getFindSon(Data &other){//���ز���Ҫ���ĸ��������com
        if(val.d==other.d)
            return this;
        int fp= val.d < other.d ? 1 : 0;
        return son[fp];
    }
    int getfp(){//���ص�ǰ�ڵ��Ǹ��ڵ���ĸ����ӣ��󷵻�0���ҷ���1��û�и��ڵ㷵��-1
        if(p==NULL)
            return -1;
        return p->son[0]==this?0:1;
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
        for(Node *now=p;now;now=now->p)
            now->val.sumcnt+=k;
    }
    int getSonSum(int fp){//���ص�ǰ�ڵ���߻��ұߵĵ㣬�������ܺ�
        if(son[fp])
            return son[fp]->val.sumcnt+son[fp]->val.cnt;
        return 0;
    }
};

struct Splay{
    int ind[MAX];//����a��Ӧ��dֵ
    void reversal(Node *now);
    void myprint(Node *now);
    Node *root=NULL;//ԭʼ�ڵ㣬��߲��������ĸ�

    void linkNode(Node *now,Node *nex,int fp){//fp 0������1������
        if(now&&fp!=-1)
            now->son[fp]=nex;
        if(nex)
            nex->p=now;
    }
    void pushdown(Node *now){
        if(now&&now->val.lazy==1){
            now->val.lazy=0;
            if(now->son[0]){
                now->son[0]->val.lazy^=1;
                ind[now->son[0]->val.a]=now->son[0]->val.d;
            }
            if(now->son[1]){
                ind[now->son[1]->val.a]=now->son[1]->val.d;
                now->son[1]->val.lazy^=1;
            }
            if(now->son[0]&&now->son[1])
                swap(now->son[0]->val.a,now->son[1]->val.a);
        }
    }
    void pushdown(Node *now,Data &other){//Я�����ݱȽϵ��·������ڲ���
        pushdown(now);
        other.d=ind[other.a];
    }

    void build(int n){//��һ��a����[1,n]�������ڵ�����2*n+1,����ڵ�a��0;
        Data data;
        data.init(2,1);
        ind[1]=2;
        root=new Node(data);
        Node *now=root,*node;
        int i;
        for(i=2;i<=n+1;i++,now=now->son[1]){//�����,
            data.init(now->val.d+2,i);
            ind[i]=now->val.d+2;
            node=new Node(data);
            linkNode(now,node,1);
            data.init(now->val.d-1,0);
            node=new Node(data);
            linkNode(now,node,0);
        }
        for(i=1,now=now->p;now;now=now->p){//����sumcnt
            now->updataSumcnt();
        }
    }

    void insertNode(Data val){
        Node *node=new Node(val);
        return insertNode(node);
    }
    void insertNode(Node *node){//���밴��dѰ��
        Node *now=root;//��ʼG��d�����޴�
        int fp;
        while(now){
            if(now->val.d == node->val.d){
                now->val.cnt++;
                now->updataSumcnt(1);
                delete node;
                return;
            }
            node->p=now;
            now=now->getFindSon(node->val);
        }
        if(now!=root){
            linkNode(node->p,node,fp);
            node->updataSumcnt(1);
        }else{
            root=node;
        }
    }

    Node *findNode(Data val){//ͬBST��
        Node *nex;
        for(Node *now=root; now ;){
            pushdown(now,val);
            nex=now->getFindSon(val);
            if(nex==now)
                return now;
            now=nex;
        }
        return NULL;
    }

    Node* rotate_zig(Node *now,int fp){//now�����ĸ��ڵ�Ϊ����fp��Ҫתnow����߻����ұ�
        Node *p=now->p;
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
        Node *e,*pe, *p=now->p;
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
        Node *e,*pe, *p=now->p;
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
        Node *temp,*p,*pp;
        for(temp=node;temp->p;){
            p=temp->p;
            pp=p->p;
            if(p==root){
                temp=rotate_zig(p,temp->getfp());
                break;
            }else if(temp->getfp()==p->getfp()){
                temp=rotate_zigzig(pp,temp->getfp());
            }else{
                temp=rotate_zigzag(pp,1 - temp->getfp());
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
                linkNode(temp->p,temp->son[0],1);
            }
            temp->updataSumcnt(- now->val.cnt);
            now->updataSumcnt();
            now->updataSumcnt(now->val.cnt-1);
        }else{
            int fp=now->son[0]?0:1;
            if(now==root){
                root=now->son[fp];
                if(root)
                    root->p=NULL;
            }else{
                linkNode(now->p,now->son[fp],now->getfp());
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
            sum+=now->getSonSum(fp);
        for(;now!=root;now=now->p){
            if(now->getfp()!=fp){//�Ǹ������ұ߲ſ�����
                sum+=now->p->val.cnt+now->p->getSonSum(fp);
            }
        }
        return sum;
    }
    Node *findRankNode(int x,int fp){//���ؽڵ��Dָ�룬fp=0(��KС����),fp=1(��K�����),
        int fp1,pr=0,r=root->getSonSum(fp)+1;
        Node *now=root,*last=NULL;
        while(1){
            if(x==r)
                return now;
            fp1=x>r?1-fp:fp;
            if(now->son[fp1]==NULL){
                for(now;fp1==fp&&now;now=now->p)
                    fp1=now->getfp();
                return now;
            }
            now=now->son[fp1];
            if(fp1!=fp){
                pr=r;
                last=now->p;
                r=pr +  now->getSonSum(fp) + now->p->val.cnt;
            }else{
                r=pr+now->getSonSum(fp);
                r+=last==NULL?1:last->val.cnt;
            }
        }
    }
    Node *getAdjoin(Node *now,int fp){//����ָ��,�Ҳ�������NULL��������now��������ڣ�fp==0��ʾС��now���������fp==1��ʾ����now����С��
        Node *e=now->son[fp];
        if(e){
            for(;e->son[1-fp];e=e->son[1-fp]);
        }else{
            for(e=now;e->getfp()==fp;e=e->p);//û��fp�����ϵ��ӽڵ������£�������һ��һ����
            e=e->p;
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
            for(now=last;now!=root&&now->getfp()==fp;now=now->p);
            if(now!=root)
                return now->p;
            return NULL;
        }else{
            return last;
        }
    }

    //�������:[l,r],����֮ǰbuild��������[1,r+2],[2,r+1]��ʾԭ������,
    //getSection��root���ҵ��󣬾���Ҫ�ҵ����䣬����������
    void getSection(int l,int r){//�õ�����:[l,r],�㷨�ǰ�l-1����������r1����������
        Data val;
        val.init(ind[l-1],l-1);
        findNode(val);//��l-1Ų�����ڵ�
        Node *now,*temp,*p,*pp,*nex;
        val.init(ind[r+1],r+1);
         temprint(root);
            printf("\n");
        for(now=root; now ;){//�ҵ�r+1�Ľڵ㣬
            pushdown(now,val);
            nex=now->getFindSon(val);
            if(nex==now)
                break;
            now=nex;
        }

        for(temp=now;temp->p!=root;  ){//r+1�Ľڵ�,����������ת�ڸ��ڵ��Ҷ���
            p=temp->p;
            pp=p->p;

            if(p==root->son[1]){
                temp=rotate_zig(p,temp->getfp());
                break;
            }else{
                if(temp->getfp()==p->getfp())
                    temp=rotate_zigzig(pp,temp->getfp());
                else
                    temp=rotate_zigzag(pp,1 - temp->getfp());
            }

        }
        // printf("%d \n",root->son[1]->val.d);
    }

    void temprint(Node *now){
        if(now){
            printf("%d %d %d --%d\n",now->val.d,now->son[0]!=NULL?now->son[0]->val.d:0,now->son[1]!=NULL?now->son[1]->val.d:0,now->val.a);
            temprint(now->son[0]);
            temprint(now->son[1]);
        }

    }
};

void Splay::reversal(Node *now){//�������䣬������ĳ���ڵ�Ϊ���������ӽڵ㣬�����ƻ�ƽ�����ṹ
    if(now){
        now->val.lazy^=1;//������Ǳ��
    }
}

int id=0;
void Splay::myprint(Node *now){
    if(now){
        pushdown(now);
        myprint(now->son[0]);
        if(now->val.a>1&&now->val.a<=N+1){
            printf("%d%s",now->val.a-1,id==N-1?"\n":" ");
            id++;
        }
        myprint(now->son[1]);
    }
}
int main(int argc,char *argv[]){
    //freopen("text/my1.in","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("myout.out","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,j,m,l,r;
    Node *e;
    Splay *t=new Splay();
    scanf("%d%d",&N,&m);

    t->build(N+2);
    //t->println();
    for(i=0;i<m;i++){
        scanf("%d%d",&l,&r);
        t->getSection(l+1,r+1);
        t->reversal(t->root->son[1]->son[0]);
        t->temprint(t->root);
        printf("\n");
        //id=0;
        //t->getSection(2,N+1);
       // t->myprint(t->root);
    }
    t->getSection(2,N+1);
    t->myprint(t->root);

return 0;
}
/*
5 2
1 5
2 4

6 3
1 2
5 6
2 5
*/
