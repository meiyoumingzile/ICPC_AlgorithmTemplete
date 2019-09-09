#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=10010;
const int mod=1e9+7;
char str[MAX];

int getStrMin(char *str){
    int i,j,k,len;
    len=strlen(str);
    for(i=k=0,j=1;i<len&&j<len&&k<len;){
        if(str[(i+k)%len]==str[(j+k)%len]){
            k++;
        }else{
            if(str[(i+k)%len]>str[(j+k)%len]){
                i=i+k+1;
            }else{
                j=j+k+1;
            }
            j+=(i+k)%len==(j+k)%len;
            k=0;
        }
    }
    return min(i,j);
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,T;
    cin>>T;
    while(T--){
        scanf("%s",str);
        printf("%d\n",getStrMin(str)+1);
    }
return 0;
}

