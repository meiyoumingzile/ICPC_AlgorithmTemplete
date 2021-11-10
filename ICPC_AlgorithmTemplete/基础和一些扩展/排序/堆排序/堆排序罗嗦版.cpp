#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define cint const int &
const int INF=2147483647;////2139062143
const int MAX=100010;
int A[MAX];
struct Heap{
    int heap[MAX];
    int sz;//sz�������鳤�ȣ�sz-1�Ƕ���Ԫ�ظ���
    Heap(){
        clear();
    }
    void clear(){
        sz=1;
    }
    void push(cint x){
        int now=sz,next;
        heap[sz++]=x;
        while(now>1){
            next=now>>1;
            if(heap[now]>=heap[next])//�ȽϺ���
                return;
            swap(heap[now],heap[next]);
            now=next;
        }
    }
    int pop(){//����Ԫ�أ����û�з���INF
        if(sz==1)
            return INF;
        int now,next,r=heap[1];
        heap[1]=heap[--sz];//ע����sz--,������--sz
        now=1;
        while(now*2<=sz){
            next=now*2;
            if(next<sz&&heap[next+1]<heap[next])////�ȽϺ���
                next++;
            if(heap[now]<=heap[next])//�ȽϺ���
                return r;
            swap(heap[now],heap[next]);
            now=next;
        }
        return r;
    }
    int size(){
        return sz-1;
    }
    bool empty(){
        return sz<=1;
    }
};
Heap que;
void heapSort(int *A,int n){
    que.clear();
    int i,j;
    for(i=0;i<n;i++){
        que.push(A[i]);
    }
    for(i=0;i<n;i++){
        A[i]=que.pop();
    }
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,t,T,n,m;
	scanf("%d",&n);
	for(i=0;i<n;i++){
        scanf("%d",&A[i]);
	}
	heapSort(A,n);
	for(i=0;i<n;i++){
        printf("%d ",A[i]);
	}
return 0;
}
/*
5
4 2 4 5 1
*/
