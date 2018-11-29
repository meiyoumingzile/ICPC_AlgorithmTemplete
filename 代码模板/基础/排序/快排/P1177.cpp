#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=100010;
const int mod=1e9+7;
int A[MAX];

void mysort(int *as, int left, int right){//[b,e]֮��
    int i=left,j=right;
    int m=as[(j+i)/2];
    while(i<=j){
        while(as[i]<m)
            i++;
        while(as[j]>m)
            j--;
        if(i<=j){
            swap(as[i],as[j]);
            i++;j--;
        }
    }
    if(i<right)
        mysort(as,i,right);
    if(left<j)
        mysort(as,left,j);
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int N,i,j;
    scanf("%d",&N);
    for(i=0;i<N;i++){
        scanf("%d",&A[i]);
    }
    mysort(A,0,N-1);
    printf("%d",A[0]);
    for(i=1;i<N;i++){
        printf(" %d",A[i]);
    }
return 0;
}
