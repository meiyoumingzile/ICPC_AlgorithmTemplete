#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define cint const int &
const int INF=2147483647;////2139062143
const int MAX=100010;
int A[MAX];
void bubbleSort(int *A,int n){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n-i-1;j++){
            if(A[j]>A[j+1]){
                swap(A[j+1],A[j]);
            }
        }
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
	bubbleSort(A,n);
	for(i=0;i<n;i++){
        printf("%d ",A[i]);
	}
return 0;
}
/*
5
4 2 4 5 1
*/
