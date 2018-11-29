#include<bits/stdc++.h>
using namespace std;

struct Node{
    int val;
    Node(int i){
        val=i;
    }
    Node *left,*right;
};
Node* stu[MAX];
Node *beginLeft;
void contact(Node *self,int p,Node *other){
    if(p){
        Node *riNode=self->right;
        self->right=other;
        other->left=self;
        if(riNode!=NULL){
            riNode->left=other;
            other->right=riNode;
        }
    }else{
        Node *leNode=self->left;
        self->left=other;
        other->right=self;
        if(leNode!=NULL){
            leNode->right=other;
            other->left=leNode;
        }else{
            beginLeft=other;
        }
    }
}

int main(int argc,char *argv[]){
    //freopen("in->txt","r",stdin); //�����ض����������ݽ���in->txt�ļ��ж�ȡ
    //freopen("out->txt","w",stdout); //����ض���������ݽ�������out->txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int N,M,i,j,val,k,p;
    stu[1]=new Node(1);
    beginLeft=stu[1];
    Node *now;
    cin>>N;
    for(i=2;i<=N;i++){
        scanf("%d%d",&k,&p);
        stu[i]=new Node(i);
        contact(stu[k],p,stu[i]);
    }
    cin>>M;
    for(i=0;i<M;i++){
        scanf("%d",&k);
        stu[k]->val=0;
    }
    for(now=beginLeft;now!=NULL;now=now->right){
        if(now->val){
            printf("%d%c",now->val,now->right==NULL?'\n':' ');
        }
    }
return 0;
}
