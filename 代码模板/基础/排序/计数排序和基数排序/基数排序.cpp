#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define cint const int &
const int INF=2147483647;////2139062143
const int MAX=100010;
int A[MAX];
queue<int>li[10];
ll p10[10];
void radixSort(int *A,int n){//�Ǹ���
    int i,j,k;
    p10[0]=1;
    for(i=1;i<10;i++)
        p10[i]=p10[i-1]*10;
    for(k=0;k<10;k++){
        for(i=0;i<n;i++){
            li[A[i]/p10[k]%10].push(A[i]);
        }
        for(i=j=0;i<10;i++){
            while(!li[i].empty()){
                A[j++]=li[i].front();
                li[i].pop();
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
	radixSort(A,n);
	for(i=0;i<n;i++){
        printf("%d ",A[i]);
	}
return 0;
}
/*
5
42121 22 42 54 1213
*/
