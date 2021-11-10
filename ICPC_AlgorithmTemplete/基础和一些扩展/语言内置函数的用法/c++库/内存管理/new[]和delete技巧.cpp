#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b,i;
    int *k=new int[10000];
    memset(k,0,sizeof(int)*10000);
       for(i=0;i<10000;i++){
            delete k+i;
       }
}
