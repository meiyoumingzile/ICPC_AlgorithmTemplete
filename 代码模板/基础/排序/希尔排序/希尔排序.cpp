#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define cint const int &
const int INF=2147483647;////2139062143
const int MAX=100010;
int A[MAX];
void __shellSort(int *A,int n,int b,int m){//ֱ�Ӳ�������
    for(int i=b+m;i<n;i+=m){
        for(int j=i;j-m>=0&&A[j-m]>A[j];j-=m){
            swap(A[j-m],A[j]);
        }
    }
}
void shellSort(int *A,int n){
    int i,s=n/2;
    while(s){
        for(i=0;i<s;i++){
            __shellSort(A,n,i,s);
        }
        s/=2;
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
	shellSort(A,n);
	for(i=0;i<n;i++){
        printf("%d ",A[i]);
	}
return 0;
}
/*
5
4 2 4 5 1
*/
