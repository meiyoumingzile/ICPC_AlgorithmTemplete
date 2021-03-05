#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<map>
#include<bitset>
//#include<windows.h>
using namespace std;
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LL long long
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=370000;
const int mod=1e9+7;
int st[10],stEnd[10];
int END,BEGIN,MINLEN;
int fp[4]={3,-1,1,-3};
map<int,char>cc;
int Hash[11];
char eight_num[9][10] = {"012345678" , "102345678" ,  "120345678" , "123045678" ,
                        "123405678" , "123450678" , "123456078" , "123456708" , "123456780" };

int load[9][MAX],parent[9][MAX],vis[MAX];
int fac[100];
struct Node{
    int len,x,code;
    int st[10];//空间换时间，这样可以少一次康拓展开
    void sett(int len,int x,int *st,int code){
        this->len=len;
        memcpy(this->st,st,sizeof(this->st));
        this->code=code;
        this->x=x;
    }
};
void getFac(int n){
    fac[0]=fac[1]=1;
    for(int i=2;i<=n;i++){
        fac[i]=fac[i-1]*i;
    }
}

bool v[1000];
vector<int> getArr(int N,int n){
    vector<int>res;
    memset(v,0,sizeof(v));
    int i,j,k,m,l;
    for(i=N-1;i>=0;i--){
        k=n/fac[i];
        n=n%fac[i];
        for(j=0,l=1;j<=k;l++){
            if(!v[l]){
                j++;
            }
        }
        res.push_back(l-2);
        v[l-1]=true;
    }

    return res;
}

int codeArr(int *A,int N){//效率问题
    int ans=0,i,j,cnt;
    for(i=0;i<N-1;i++){
        for(j=i+1,cnt=0;j<N;j++){
            if(A[i]>A[j]){
                cnt++;
            }
        }
        ans+=cnt*fac[N-i-1];
    }
    return ans;
}

bool isMove(int pos,int f){
    int d=pos+f;
    if(d<0||d>=9){
        return false;
    }else if(f==1&&(pos==2||pos==5)){
        return false;
    }else if(f==-1&&(pos==3||pos==6)){
        return false;
    }
    return true;
}

int getHash(){
    int i,j,k;
    for(i=0;i<9;i++){
        if(st[i]==0){
            k=i;
            break;
        }
    }
    for(j=0;j<9;j++){
        Hash[st[j]]=eight_num[i][j]-'0';
    }
    Hash[0]=0;
    for(i=0;i<9;i++){
        st[i]=Hash[st[i]];
        stEnd[i]=Hash[stEnd[i]];
        //printf("%d ",stEnd[i]);
    }//printf("\n");
    return k;
}

int bfs(int b){
     memset(vis,false,sizeof(vis));
    int i,j,k,d,code,nowcode;
    Node next,now;
    BEGIN=codeArr(st,9);
    END=codeArr(stEnd,9);
    queue<Node>q;
    next.sett(0,b,st,BEGIN);
    vis[BEGIN]=1;
    parent[b][BEGIN]=BEGIN;
    q.push(next);
    //printf("hehe");
    while(!q.empty()){
        now=q.front();
        q.pop();
        for(i=0;i<4;i++){
            d=now.x+fp[i];
            if(!isMove(now.x,fp[i])){
                continue;
            }
            next=now;
            swap(next.st[next.x],next.st[d]);
            code=codeArr(next.st,9);
            if(!vis[code]){
                vis[code]=1;
                parent[b][code]=now.code;
                load[b][code]=fp[i];
                next.len=now.len+1;
                next.x=d;
                next.code=code;
                q.push(next);
            }
        }

    }
}

bool isSolve(vector<int> st,vector<int> tarSt){//判断对于排列每个数，前面比它小的数个数，这些数之和是奇数还是偶数
    int i,j,ans1=0,ans2=0;
    for(i=0;i<9;i++){
        for(j=0;j<i&&st[i]!=0;j++){
            if(st[j]<st[i]&&st[j]!=0){
                ans1++;
            }
        }
    }
    for(i=0;i<9;i++){
        for(j=0;j<i&&tarSt[i]!=0;j++){
            if(tarSt[j]<tarSt[i]&&tarSt[j]!=0){
                ans2++;
            }
        }
    }
    if(ans1%2==ans2%2){
        return true;
    }
    return false;
}

void init(){
    int i,j,k;

    memset(load,0,sizeof(load));
    memset(parent,-1,sizeof(parent));
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            st[j]=eight_num[i][j]-'0';
        }
        bfs(i);
    }
}

int main(int argc,char *argv[]){
    //freopen("debug\\in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("debug\\out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//OJ上有的地方不能加这句话
    int t,T,i,j,len,b;
    char c;
    getFac(10);
    cc[-1]='l';cc[1]='r';cc[3]='d';cc[-3]='u';

    init();


    scanf("%d",&T);
    for(t=1;t<=T;t++){
        getchar();
        for(i=0;i<9;i++){
            scanf("%c",&c);
            if(c=='X'){
                st[i]=0;
                b=i;
            }else{
                st[i]=c-'0';
            }
        }
        getchar();
        for(i=0;i<9;i++){
            scanf("%c",&c);
            stEnd[i]=c=='X'?0:c-'0';
        }
        int kind=getHash();
        BEGIN=codeArr(st,9);
        END=codeArr(stEnd,9);
        vector<char>ff;
        for(i=END,j=0;i!=BEGIN;i=parent[kind][i],j++){
            ff.push_back(cc[load[kind][i]]);
            //printf("%d ",i);
        }
        printf("Case %d: %d\n",t,j);
        if(BEGIN==END){
            printf("\n");
        }else{
            for(i=ff.size()-1;i>=0;i--){
                printf("%c",ff[i]);
            }printf("\n");
        }
    }
return 0;
}
/*
30
87152634X
12345678X
12345678X
12345678X
23415X768
12345678X
*/
