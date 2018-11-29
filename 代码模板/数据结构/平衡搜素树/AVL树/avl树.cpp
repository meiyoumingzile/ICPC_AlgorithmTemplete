#include<bits/stdc++.h>
using namespace std;

struct Data{
    int d;
};
struct AVL{//根节点是root的右边
    struct Node{
        Data val;
        int bf_r=0,bf_l=0;//右-左；1代表右高，1代表左高
        Node *right=NULL,*left=NULL;
        Node(){}
        Node(Data e){
            val=e;
        }
        int getbf(){
            return bf_r-bf_l;
        }
    };
    Node *root=NULL;
    AVL(){}
    ~AVL(){
        Del(root);
        delete root;
    }

    void * insert(Data e){
        root=__insert(root,e);
    }
    Node* __insert(Node *tree,Data e){//建树插入操作，由于AVL树是在插入时旋转，递归得每次插入就分步旋转，
        if(tree==NULL){
            tree=new Node(e);
        }else{
            if(e.d>=tree->val.d){
                tree->right=__insert(tree->right,e);
                change_h(tree);//改变树高度平衡因子
                tree=change(tree);//旋转当前深度的树
            }else{
                tree->left=__insert(tree->left,e);
                change_h(tree);
                tree=change(tree);
            }
        }
        return tree;
    }

    void change_h(Node* tree){
        if(tree->left!=NULL){
            tree->bf_l=max(tree->left->bf_l,tree->left->bf_r)+1;
        }
        if(tree->right!=NULL){
            tree->bf_r=max(tree->right->bf_l,tree->right->bf_r)+1;
        }
    }
    Node* change(Node* tree){
        int bf=tree->getbf();
        if(bf==2&&tree->right->getbf()==1){
            return rotate_right_right(tree);
        }else if(bf==2&&tree->right->getbf()==-1){
            return rotate_right_left(tree);
        }else if(bf==-2&&tree->left->getbf()==1){
            return rotate_left_right(tree);
        }else if(bf==-2&&tree->left->getbf()==-1){
            return rotate_left_left(tree);
        }else{
            return tree;
        }
    }
    /*int omit(Node* tree,Data e,bool f){
        if(tree==NULL){
            return -1;
        }else if(e.d==tree->val.d){
            if(f){
                om(tree->right,f,tree);
                tree=tree->right;
            }else{
                om(tree->left,f,tree);
                tree=tree->left;
            }
            return 0;
        }else if(e.d>=tree->val.d){
            return omit(tree->right,e,1);
        }else{
            return omit(tree->left,e,0);
        }
    }
    void om(Node* tree,bool f,Node* father){
        if(tree==NULL){
            return;
        }
        if(f){
            om(tree->right,f,tree);
            tree->left=father->left;
        }else{
            om(tree->left,f,tree);
            tree->right=father->right;
        }
    }*/
    Node* rotate_left_left(Node* tree){//tree是当前旋转的树根节点
        Node *e=tree->left;
        tree->bf_l=e->bf_r;
        e->bf_r=tree->bf_r+1;
        tree->left=e->right;
        e->right=tree;
        return e;
    }
    Node* rotate_left_right(Node* tree){
        Node* e=tree->left;
        if(e->right->getbf()<=-1){
            tree->left=rotate_right_left(e);
        }else if(e->right->getbf()>=1||e->left==NULL){
            tree->left=rotate_right_right(e);
        }
        return rotate_left_left(tree);
    }
    Node* rotate_right_right(Node* tree){
        Node *e=tree->right;
        tree->bf_r=e->bf_l;
        e->bf_l=tree->bf_l+1;
        tree->right=e->left;
        e->left=tree;
        return e;
    }
    Node* rotate_right_left(Node* tree){
        Node* e=tree->right;
        if(e->left->getbf()<=-1||e->right==NULL){
            tree->right=rotate_left_left(e);
        }else if(e->left->getbf()>=1){
            tree->right=rotate_left_right(e);
        }
        return rotate_right_right(tree);
    }

    void LDRprint(Node *tree){
        if(tree==NULL)
            return;
        LDRprint(tree->left);
        printf("%d ",tree->val.d);
        LDRprint(tree->right);
    }
    void Del(Node *tree){
        if(tree->left!=NULL){
            Del(tree->left);
            delete tree->left;
        }
        if(tree->right!=NULL){
            Del(tree->right);
            delete tree->right;
        }
    }
};
int main(){
    int i,j,n,e;
    Data data;
    printf("输入大小");
    scanf("%d",&n);
    AVL *t=new AVL();
    printf("输入一个数组\n");
    for(i=0;i<n;i++){
        scanf("%d",&data.d);
        t->insert(data);
    }
    printf("结果:\n");
    t->LDRprint(t->root);
    printf("\n");
    delete t;
return 0;
}
/*
6
67 65 80 67 87 69
10
878 6 4554 334 7898 2 9 10000 5 23
20
50 40 30 60 80 67 55 33 10 15 24 65 87 67 69 89 90 39 57 62
*/
