#include<bits/stdc++.h>
using namespace std;
const int MAX=1010;
char A[1010],B[1010];
int dp[MAX][MAX];
int last[MAX][MAX];
int main(){
    int i,j,k,la,lb;
    scanf("%s",A);
    scanf("%s",B);
    la=strlen(A);
    lb=strlen(B);
    for(i=0;i<la;i++){
        for(j=0;j<lb;j++){
            if(A[i]==B[j]){
                dp[i+1][j+1]=dp[i][j]+1;
                last[i+1][j+1]=0;
            }else if(dp[i][j+1]>dp[i+1][j]){
                dp[i+1][j+1]=dp[i][j+1];
                last[i+1][j+1]=-1;
            }else{
                dp[i+1][j+1]=dp[i+1][j];
                last[i+1][j+1]=1;
            }
        }
    }
    vector<char>ch;
    for(i=la,j=lb;i*j>0;){
        if(last[i][j]==-1){
            i--;
        }else if(last[i][j]==1){
            j--;
        }else{
            ch.push_back(A[i-1]);
            i--;
            j--;
        }
    }
    for(i=ch.size()-1;i>=0;i--){
        printf("%c",ch[i]);
    }
    printf("\n");
return 0;}
