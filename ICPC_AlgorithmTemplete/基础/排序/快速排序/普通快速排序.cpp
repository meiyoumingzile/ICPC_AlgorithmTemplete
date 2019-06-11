#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=100010;
const int mod=1e9+7;
int A[MAX];
void quickSort(int *as, int left, int right){//[b,e]֮��
    int i=left,j=right;
    int m=as[(i+j)/2];
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
        quickSort(as,i,right);
    if(left<j)
        quickSort(as,left,j);
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
    quickSort(A,0,N-1);
    for(i=0;i<N;i++){
        printf("%d ",A[i]);
    }
return 0;
}
