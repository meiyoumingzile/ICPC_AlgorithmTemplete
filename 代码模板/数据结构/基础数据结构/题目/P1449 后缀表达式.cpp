#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1010;
const int mod=1e9+7;
char str[MAX];
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    stack<int>st;
    stack<int>num;
    int i,j,k,lens,a,b,c;
    cin>>str;
    lens=strlen(str);
    for(i=0;i<lens&&str[i]!='@';i++){
        if(str[i]-'0'>=0&&str[i]-'9'<10){
            num.push(str[i]-'0');
        }else if(str[i]=='.'){
            for(j=0,k=0;!num.empty();j++){
                k+=(int)pow(10,j)*num.top();
                num.pop();
            }
            st.push(k);
        }else{
            a=st.top();
            st.pop();
            b=st.top();
            st.pop();
            if(str[i]=='+'){
                c=a+b;
            }else if(str[i]=='-'){
                c=b-a;
            }else if(str[i]=='*'){
                c=b*a;
            }else if(str[i]=='/'){
                c=b/a;
            }
            st.push(c);
        }
    }
    printf("%d\n",st.top());
return 0;
}
