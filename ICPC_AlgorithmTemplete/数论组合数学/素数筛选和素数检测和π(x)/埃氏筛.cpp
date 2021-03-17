#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
#define ll long long
const int MAX=100000010;

bool flag[MAX];
int primes[MAX];
int primesCount;
void eratosthenes_sieve(int n){
    int i,j,sqrtn;
    primesCount=0;
    memset(flag,0,sizeof(flag));
    sqrtn=(int)ceil(sqrt(n));
    for(i=2;i<=sqrtn;i++){
        if(!flag[i]){
            primes[primesCount++]=i;
            for(j=i*i;j<n;j+=i)
                flag[j]=true;
        }
    }
    for(i=sqrtn+1;i<n;i++){
        if(!flag[i]){
            primes[primesCount++]=i;
        }
    }

}

int main(int argc,char *argv[]){
    int n,i;
    n=MAX;
    eratosthenes_sieve(n);


return 0;
}
