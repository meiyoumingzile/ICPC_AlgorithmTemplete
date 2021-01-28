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
    int k;//key��Ϊ�����ֵ
    int cnt=1;//�ýڵ���ִ���
    int sumcnt=0;//�ӽڵ����ĸ����������ͬ�����ȥ
};
struct Node{
    Node *parent,*son[2];//son[0]������son[1]������
    Data val;
    bool c=0;//0�����ɫ��1�����ɫ
    Node(Data val){
        parent=son[0]=son[1]=NULL;
        this->val=val;
    }
    int getfp(){//�õ���ǰ�ڵ��Ǹ��ڵ���ĸ����ӣ��󷵻�0���ҷ���1��û�и��ڵ㷵��-1
        if(parent==NULL)
            return -1;
        return parent->son[0]==this?0:1;
    }
    Node* getBrother(){
        if(parent)
            return parent->son[0]==this?parent->son[1]:parent->son[0];
        return NULL;
    }
    void updataSumcnt(){//���µ�ǰ���sumcnt��ֵ
        val.sumcnt=0;
        for(int i=0;i<2;i++){
            if(son[i]){
                val.sumcnt+=son[i]->val.sumcnt+son[i]->val.cnt;
            }
        }
    }
    void updataSumcnt(int k){//���ϸ���sumcntֱ�����ڵ�Ϊֹ
        for(Node *now=parent;now;now=now->parent)
            now->val.sumcnt+=k;
    }
    int getSum(int fp){//���ص�ǰ�ڵ���߻����ұߵĵ㣬�������ܺ�
        if(son[fp])
            return son[fp]->val.sumcnt+son[fp]->val.cnt;
        return 0;
    }
    int getSum(){//���ص�ǰ�ڵ��Լ��ӽڵ����������ܺ�
        return val.sumcnt+val.cnt;
    }
};

struct RB_tree{
    Node *root=NULL;
    inline void linkNode(Node *now,Node *next,int fp){//fp 0������1������
        if(now)
            now->son[fp]=next;
        if(next)
            next->parent=now;
    }
    Node *findNode(Data val){//ͬBST��
        int fp;
        for(Node *now=root; now ;now=now->son[fp]){
            if(now->val.k == val.k)
                return now;
            fp=now->val.k > val.k?0:1;
        }
        return NULL;
    }
    void insertNode(Data val){
        Node *node=new Node(val);
        insertNode(node);
    }
    void insertNode(Node *node){
        if(root==NULL){//�ǿ���
            node->c=1;
            root=node;
            return;
        }
        Node *p,*bro,*now=root;
        int fp;
        while(now){
            if(now->val.k== node->val.k){
                now->val.cnt++;
                now->updataSumcnt(1);
                delete node;
                return;
            }
            node->parent=now;
            fp=now->val.k < node->val.k;
            now=now->son[fp];
        }
        now=node;
        p=node->parent;
        p->son[fp]=node;
        bro=p->getBrother();
        now->updataSumcnt(1);
        if(p->c==0){//�����Ǻ�ɫ�޸�,�����Ǻ�ɫʲô������
            while(p&&p->c==0&&bro&&bro->c==0){//��������Ǻ�ɫ
                bro->c=p->c=1;
                now=p->parent;
                now->c=0;
                p=now->parent;
                if(p)
                    bro=p->getBrother();
            }
            root->c=1;
            if(p&&p->c==0){//p���ڣ�˵��û���ʵ����ڵ㣬�Ҹ�һ���Ǻ�ɫ��˵������p���Ҳ�Ǹ��Ķ���
                fp=p->getfp();
                if(fp!=now->getfp()){//����ڵ㲻���ڻ��Ǻ�ɫ��now��p����һ�£�Ҫ��תһ��
                    rotate_zig(p,fp);
                    now=p;
                    p=now->parent;
                }
                p->c=1;////����ڵ㲻���ڻ��Ǻ�ɫ��now��pͬ����
                p->parent->c=0;
                rotate_zig(p->parent,fp^1);
            }
        }
        root->c=1;
    }
    bool deleteNode(Data val){
        Node *now,*temp,*p;
        now=findNode(val);
        if(now==NULL)
            return 0;
        if(now->val.cnt>1){
            now->val.cnt--;
            now->updataSumcnt(-1);
            return 1;
        }
        if(now->son[0]&&now->son[1]){//����������Ӷ��У�������ֵ������ȥ
            for(temp=now->son[0];temp->son[1];temp=temp->son[1]);
            swap(now->val,temp->val);
            now=temp;
            for(;temp;temp=temp->parent){
                temp->updataSumcnt();
            }
        }
        int fp=now->son[0]?0:1;
        p=now->parent;
        int nowfp=now->getfp();
        deleteRBNode(now,p,nowfp);
        if(now==root){
            root=now->son[fp];
        }else{
            linkNode(p,now->son[fp],nowfp);
            now->updataSumcnt(-1);
        }
        if(root){
            root->parent=NULL;
            root->c=1;
        }
        delete now;
        return 1;
    }
    void deleteRBNode(Node *D,Node *p,int fp){
        Node *bro,*nephew1,*nephew2;
        if(D->c==0||D==root){
        }else if(D->son[1]==NULL&&D->son[0]&&D->son[0]->c==0){
            D->son[0]->c=1;
        }else if(D->son[0]==NULL&&D->son[1]&&D->son[1]->c==0){
            D->son[1]->c=1;
        }else{
            p=D->parent;
            bro=D->parent->son[fp^1];
            if(bro->c==0){//
                swap(p->c,bro->c);
                rotate_zig(p,fp);
                bro=p->son[fp^1];
            }
            nephew1=bro->son[fp^1];//Զֶ��
            nephew2=bro->son[fp];//��ֶ��
            if(nephew1&&nephew1->c==0){
                aboveself:;
                swap(p->c,bro->c);
                nephew1->c=1;
                rotate_zig(p,fp);
            }else if(nephew2&&nephew2->c==0){
                rotate_zig(bro,fp^1);
                swap(nephew2->c,bro->c);
                bro=p->son[fp^1];
                nephew1=bro->son[fp^1];//Զֶ��
                goto aboveself;
            }else{
                bro->c=0;
                if(p->c==1)
                    deleteRBNode(p,p->parent,p->getfp());
                else
                    p->c=1;
            }
        }
    }
    Node* rotate_zig(Node* now,int fp){//����ת����nowΪ֧��,fp=0�����now������ת��fp=1�����now������ת
        Node *e, *p=now->parent;
        int nowfp=now->getfp();
        e=now->son[fp^1];
        linkNode(now,e->son[fp],fp^1);
        linkNode(e,now,fp);
        linkNode(p,e,nowfp);
        now->updataSumcnt();
        e->updataSumcnt();
        while(root->parent)
            root=root->parent;
        return e;
    }

    int findRank(Data val,int fp){//fp==0��ѯval.k��������,�ڼ�С(���ж����ͬ�����������С������),fp==1�෴
        int sum=1,_fp;
        for(Node *now=root; now ;now=now->son[_fp]){
            if(now->val.k == val.k)
                return sum+now->getSum(fp);
            _fp=now->val.k > val.k ? 0:1;
            if(_fp==fp^1){
                sum+=now->val.cnt+now->getSum(fp);
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
            fp1=x>r?fp^1:fp;
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
            for(;e->son[fp^1];e=e->son[fp^1]);
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
            if(now->val.k == val.k)
                return getAdjoin(now,fp);//������now���������
            last=now;
            fp1=now->val.k > val.k ? 0:1;
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
    void LDRprint(Node *now){//�������
        if(now){
            printf("%d %d %d,��ɫ��%d\n",now->val.k,now->son[0]?now->son[0]->val.k:-1,now->son[1]?now->son[1]->val.k:-1,now->c);
            LDRprint(now->son[0]);
            LDRprint(now->son[1]);
        }
    }
};

int main(int argc,char *argv[]){
   // freopen("data//P6136_6.in","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
   // freopen("data//my.out","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));
    int i,id,k,T,n,m,last=0;
    Node *e;
    scanf("%d%d",&n,&m);
    RB_tree *t=new RB_tree();
    Data data;
    for(i=0;i<n;i++){
        scanf("%d",&data.k);
        t->insertNode(data);
    }
    int ans=0;
    while(m--){
        scanf("%d%d",&id,&data.k);
        data.k^=last;
        //if(m<3)
           // printf("%d %d %d\n",m,id,last);
        if(id==1){
            t->insertNode(data);
        }else if(id==2){
            t->deleteNode(data);
        }else if(id==3){
            last=t->findRank(data,0);
            ans^=last;
        }else if(id==4){
            e=t->findRankNode(data.k,0);
            last=e->val.k;
            ans^=last;
        }else if(id==5){
            e=t->getAdjoin(data,0);
            last=e->val.k;
            ans^=last;
        }else if(id==6){
            e=t->getAdjoin(data,1);
            last=e->val.k;
            ans^=last;
        }
       // printf("%d\n",ans);
    }
    printf("%d\n",ans);
return 0;
}
/*
6 7
1 1 4 5 1 4
2 1
1 9
4 1
5 8
3 13
6 7
1 4
*/
