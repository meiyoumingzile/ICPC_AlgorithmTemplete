#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;
int A[MAX];

unordered_map<int,int>ind;
int toval[MAX];
int compress(int *A,int n){//������ɢ���������ѹ�����ݣ�����ֻ����ȥ�أ����ı���ֵ
    int i,k=0,t;
    for(i=0;i<n;i++){
        toval[i]=A[i];
    }
    sort(toval,toval+n);
    ind[toval[0]]=k++;
    t=toval[0];
    for(i=1;i<n;i++){
        if(toval[i]!=t){
            t=toval[i];
            toval[k]=toval[i];
            ind[toval[i]]=k++;
        }
    }
    return k;
}


int main(int argc,char *argv[]){
	int i,j,k,t,T,n,m,x,up;
	cin>>n;
    for(i=0;i<n;i++){
        cin>>A[i];
    }
    up=compress(A,n);
    for(i=0;i<up;i++){
        printf("%d ",toval[i]);
    }
    while(~scanf("%d",&x)){
        x=lower_bound(toval,toval+up,x)-toval;//���ֲ��Һ��������Բ鿴�ǵڼ���
        printf("%d\n",x);
    }
return 0;
}

