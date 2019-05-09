#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=100010;
const int mod=1e9+7;
int tail2[MAX];//tail[i]��ʾ����Ϊi����������Сĩβ,����������
int tail1[MAX];//tail[i]��ʾ����Ϊi�����������ĩβ,����������
int A[MAX];
//�������У�������Ĳ��������г��ȣ��͵��������г���
int bin_down(int *d,int ex,int left,int right){//�Ӵ�С������,��һ�����ڵ���ex�����һ����
    if(left==right-1){
        if(d[left]>=ex){//ע��=���ǲ���������
            return left;
        }else{
            return left-1;
        }
    }
    int mid=(left+right)/2;
    if(d[mid]>=ex){
        return bin_down(d,ex,mid,right);
    }else{
        return bin_down(d,ex,left,mid);
    }
}

int bin_up(int *d,int ex,int left,int right){//��С���������,��һ��С��ex�����һ����
    if(left==right-1){
        if(d[left]<ex){//ע�����ϸ������������
            return left;
        }else{
            return left-1;
        }
    }
    int mid=(left+right)/2;
    if(d[mid]>ex){
        return bin_up(d,ex,left,mid);
    }else{
        return bin_up(d,ex,mid,right);
    }
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i=0,j,k,n,a,maxLen1=1,maxLen2=1,ind;
    while(~scanf("%d",&A[i++]));
    n=i-1;
    tail1[1]=tail2[1]=A[0];
    for(i=1;i<n;i++){
        ind=bin_down(tail1,A[i],1,maxLen1+1);
        tail1[ind+1]=A[i];
        if(ind==maxLen1){
            maxLen1++;
        }

        ind=bin_up(tail2,A[i],1,maxLen2+1);
        tail2[ind+1]=A[i];
        if(ind==maxLen2){
            maxLen2++;
        }
    }
    printf("%d\n%d\n",maxLen1,maxLen2);
return 0;
}
