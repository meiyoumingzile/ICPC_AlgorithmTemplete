#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=100010;
const int mod=1e9+7;
int A[MAX];
void HeapAdjust(int *A,int s,int e){//�������������϶���
    int i,rc=A[s];//��¼ԭ���������֣����ⱻ���渲��
    for(i=2*s;i<=e;i<<=1){
        if(i<e && A[i]<A[i+1])//����ұߴ�Ϳ��ұ�
            i++;
        if(rc>=A[i])//������ڵ������˳�ѭ�����������
            break;
        A[s]=A[i];//�Ѹ���������Ǹ�
        s=i;//��Ϊ��ĳ�����ӽ����ˣ���������һ�������Ǹ����ӿ����µĸ�
    }
    A[s]=rc;//��ʱ��s��һ����Ҷ��
}
void HeapSort(int *A,int n){//A[0]λ�ÿ��У���1��ʼ
    for(int i=n/2;i>0;i--)
        HeapAdjust(A,i,n);//���ѣ����ŵ�������n/2,����൱�ڴӺ���ǰһ��һ�㵹�ŵ�������
    for(int i=n;i>1;i--){
        swap(A[i],A[1]);
        HeapAdjust(A,1,i-1);
    }
}//��ε���Ĵ��뽨�Ѻ��Ҳ�ͬ���������϶��µ���
//��ÿ�˴�Ҷ�һ�����ǴӶ��˵�����ֻ��д����һ��


int main(int argc,char *argv[]){
    int n,i,j;
    scanf("%d",&n);
    for(i=1;i<=n;i++){//0λ�ÿ���
        scanf("%d",&A[i]);
    }
    HeapSort(A,n);
    for(i=1;i<=n;i++){
        printf("%d ",A[i]);
    }printf("\n");
return 0;
}
/*
5
2 4 6 7 1
*/
