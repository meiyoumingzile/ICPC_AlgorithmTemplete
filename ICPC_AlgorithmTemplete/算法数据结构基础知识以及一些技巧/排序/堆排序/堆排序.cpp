#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define cint const int &
const int INF=2147483647;////2139062143
const int MAX=100010;
int A[MAX];
void heapSort(int *A,int n){//����,�����1��ʼ
    int i,j,t;
    for(i=2;i<=n;i++){
        for(j=i;j>1&&A[j]>A[j/2];j/=2){
            swap(A[j],A[j/2]);
        }
    }
    for(i=n;i>1;i--){
        swap(A[1],A[i]);
        for(j=2;j<i-1;j*=2){
            if(A[j/2]<A[j]&&A[j]>=A[j+1]){//��ߴ�
                swap(A[j/2],A[j]);
            }else if(A[j/2]<A[j+1]&&A[j]<A[j+1]){//�ұߴ�
                swap(A[j/2],A[j+1]);
                j++;
            }else{
                break;
            }
        }
        if(j==i-1&&A[j/2]<A[j]){
           swap(A[j/2],A[j]);
        }
    }
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,t,T,n,m;
	while(~scanf("%d",&n)){
        for(i=1;i<=n;i++){
            scanf("%d",&A[i]);
        }
        heapSort(A,n);
        for(i=1;i<=n;i++){
            printf("%d ",A[i]);
        }printf("\n");
	}
return 0;
}
/*
5
4 2 4 5 1

*/
