#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=100010;
const int mod=1e9+7;
int A[MAX];
void HeapAdjust(int *A,int s,int e){//调整函数，自上而下
    int i,rc=A[s];//记录原本根的数字，避免被后面覆盖
    for(i=2*s;i<=e;i<<=1){
        if(i<e && A[i]<A[i+1])//如果右边大就看右边
            i++;
        if(rc>=A[i])//如果根节点最大就退出循环，无需调整
            break;
        A[s]=A[i];//把根变成最大的那个
        s=i;//因为和某个儿子交换了，故向下走一步，把那个儿子看成新的根
    }
    A[s]=rc;//此时的s不一定是叶子
}
void HeapSort(int *A,int n){//A[0]位置空闲，从1开始
    for(int i=n/2;i>0;i--)
        HeapAdjust(A,i,n);//建堆，倒着调整，从n/2,如此相当于从后往前一层一层倒着调整回来
    for(int i=n;i>1;i--){
        swap(A[i],A[1]);
        HeapAdjust(A,1,i-1);
    }
}//严蔚敏的代码建堆和我不同，他是自上而下调整
//序每趟大家都一样都是从顶端调整，只是写法不一样


int main(int argc,char *argv[]){
    int n,i,j;
    scanf("%d",&n);
    for(i=1;i<=n;i++){//0位置空闲
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
