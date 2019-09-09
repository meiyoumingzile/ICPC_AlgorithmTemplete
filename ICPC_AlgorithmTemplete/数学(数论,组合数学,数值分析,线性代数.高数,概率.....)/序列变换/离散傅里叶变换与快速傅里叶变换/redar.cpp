
#include <iostream>
#include <cstdio>
using namespace  std;
const int MAX=2100000;
int seq[MAX];
int N = 1048576;

int p2[60];
void getSeq(int N){
    N--;
    int i,j,k,bit,n;
    for(bit=0,n=N;n;n/=2,bit++);
    p2[0]=1;
    for(i=1;i<bit;i++){
        p2[i]=p2[i-1]*2;
    }
    for(i=1;i<N;i++){
        for(j=k=0,n=i;n;n/=2,j++){
            if(n%2==1){
                k+=p2[bit-j-1];
            }
        }
        seq[i]=k;
    }
}

void rader(int *x,int N){//必须是2的整数幂
    int i,j,k;
    for(i=0;i<N;i++){
        x[i]=i;
    }
    for(j=0,i=0;i<N-1;i++){
        if(i<j){
           swap(x[i],x[j]);
        }
        k=N/2;
        while(j>=k){
            j-=k;
            k/=2;
        }
        j+=k;
    }
}

int main()
{

    rader(seq,N);

   // getSeq(N);

    return 0 ;
}

