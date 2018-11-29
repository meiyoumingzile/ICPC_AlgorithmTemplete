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
    //freopen("in->txt","r",stdin); //输入重定向，输入数据将从in->txt文件中读取
    //freopen("out->txt","w",stdout); //输出重定向，输出数据将保存在out->txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
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
