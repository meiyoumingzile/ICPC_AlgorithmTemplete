#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define cint const int &
const int INF=2147483647;////2139062143
const int MAX=100010;
int A[MAX];
void selSort(int *A,int n){
    int i,j,mina,k;
    for(i=0;i<n-1;i++){
        mina=A[i];
        for(j=i+1;j<n;j++){
            if(mina>A[j]){
                mina=A[j];
                k=j;
            }
        }
        if(mina<A[i]){
            swap(A[k],A[i]);
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
	selSort(A,n);
	for(i=0;i<n;i++){
        printf("%d ",A[i]);
	}
return 0;
}
/*
5
4 2 4 5 1
*/
