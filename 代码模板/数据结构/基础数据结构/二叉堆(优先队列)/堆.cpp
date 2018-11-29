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
};
Data A[MAX];

struct Node{
    Data val; //结点值
    Node(Data val){
        this->val=val;
    }
};

struct HEAD{//数组实现,且是小顶堆
    Node *tree[MAX];
    int size=1;
    HEAD(){
        for(int i=0;i<MAX;i++){
            tree[i]=NULL;
        }
    }

    void insertNode(Data val){//堆可以有重复元素
        Node *node=new Node(val);
        insertNode(node);
    }
    void insertNode(Node *node){
        tree[size++]=node;
        adjust(size-1);
    }
    void adjust(){//调整整个堆
        for(int i=size-1;i>1;i--){
            if(tree[i]&&tree[i]->val.d < tree[i/2]->val.d){
                swap(tree[i]->val,tree[i/2]->val);
            }
        }
    }
    void adjust(int i){//调整某一个节点
        for(;i>1;i/=2){
            if(tree[i]&&tree[i]->val.d < tree[i/2]->val.d){
                swap(tree[i]->val,tree[i/2]->val);
            }
        }
    }

    void pop(){//堆只能删除顶端元素
        int i=1,j;
        while(1){
            j=i*2;
            if(tree[j]&&tree[j+1]){
                if(tree[j]->val.d > tree[j+1]->val.d)
                    j++;
            }else if(tree[j]){
            }else if(tree[j+1]){
                j++;
            }else{
                break;
            }
            tree[i]->val=tree[j]->val;
            i=j;
        }
        delete tree[i];
        tree[i]=NULL;
    }


    void printSort(){//排序
        while(tree[1]){
            printf("%d ",tree[1]->val.d);
            pop();
        }
    }
};

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int N,i,j,k;
    HEAD *t=new HEAD();
    scanf("%d",&N);
    for(i=0;i<N;i++){
        scanf("%d",&A[i].d);
        t->insertNode(A[i]);
    }
    Data data;
    while(~scanf("%d",&data.d)){
        t->insertNode(data);
        t->printSort();
        printf("\n");
    }
return 0;
}
/*
7
40 20 80 10 30 60 160
*/
