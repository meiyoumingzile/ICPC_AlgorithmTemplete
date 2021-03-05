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
using namespace std;
//std::ios::sync_with_stdio(false);
//#include<windows.h>
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LL long long
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=400010;
const int mod=1e9+7;
char mapp[100];
int load[MAX];//路径,0表示没走过；
int fp[MAX];//方向
int f[4]={-1,3,1,-3};
//int f[4]={3,1,-1,-3};
int st[10],tarSt[10];
int END;

struct Node{
    int x,code;
    int st[10];
    int dis,len;//表示当前状态到最终状态的曼哈顿距离之和
    void sett(int x,int code,int *st){
        this->x=x;
        this->code=code;
        memcpy(this->st,st,sizeof(this->st));
    }
};
Node head;

struct cmp1{
    bool operator ()(Node &a,Node &b){
        if( a.dis+a.len > b.dis + b.len){
            return true;
        }else if(a.dis+a.len == b.dis + b.len){
            if(a.dis > b.dis ){
                return true;
            }
        }
        return false;
    }
};

int fac[10];
void getFac(int N){
    fac[0]=fac[1]=1;
    for(int i=2;i<=N;i++){
        fac[i]=fac[i-1]*i;
    }
}

int codeArr(int *A,int N){
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


bool isLeg(int b,int j){
    int e=b+f[j];
    if(e<0||e>=9){
        return false;
    }
    if(f[j]==1&&(b==2||b==5)){
        return false;
    }
    if(f[j]==-1&&(b==3||b==6)){
        return false;
    }
    return true;
}

int getNodeDis(int *mapp){
    int ans=0,i,j;
    for(i=0;i<9;i++){
        if(mapp[i]){
            for(j=0;mapp[i]!=tarSt[j];j++);
            ans+=abs(j/3-i/3)+abs(j%3-i%3);
        }
    }
    return ans;
}


int bfs(int bx){
    int i,j,d,nextCode;
    priority_queue<Node,vector<Node>,cmp1>q;
    Node now ,next;
    nextCode=codeArr(st,9);
    if(END==nextCode){
        return -1;
    }
    fp[nextCode]=INF;//初始点不能走
    head.sett(bx,nextCode,st);
    head.dis=getNodeDis(st);
    head.len=0;
    q.push(head);
    while(!q.empty()){

        now=q.top();
        q.pop();
        for(j=0;j<4;j++){
            d=now.x+f[j];
            if(isLeg(now.x,j)){
                next=now;
                swap(next.st[now.x],next.st[d]);
                nextCode=codeArr(next.st,9);
                if(!fp[nextCode]){
                    fp[nextCode]=f[j];
                    next.x=d;
                    next.code=nextCode;
                    next.dis=getNodeDis(next.st);
                    next.len=now.len+1;
                    load[next.code]=now.code;
                    q.push(next);
                    if(nextCode==END){
                        return next.code;
                    }
                }
            }
        }
    }

}

bool isSolve(){//判断对于排列每个数，前面比它小的数个数，这些数之和是奇数还是偶数
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

int main(int argc,char *argv[]){
    //freopen("debug\\in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("debug\\out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//OJ上有的地方不能加这句话
    int i,j,k,beginPos;
    getFac(9);
    for(i=0;i<8;i++){
        tarSt[i]=i+1;
    }
    map<int,char>c;
    c[-3]='u';
    c[3]='d';
    c[-1]='l';
    c[1]='r';
    END=codeArr(tarSt,9);
    while(gets(mapp)!=NULL){
        for(i=0,j=0;i<strlen(mapp);i++){
            k=i-j;
            if(mapp[i]=='x'){
                beginPos=k;
                st[k]=0;
            }else if(mapp[i]==' '){
                j++;
            }else{
                st[k]=mapp[i]-'0';
            }
        }
        if(!isSolve()){
            printf("unsolvable\n");
        }else{
            memset(load,-1,sizeof(load));
            memset(fp,0,sizeof(fp));
            int tail=bfs(beginPos);
            //printf("%d",head.code);
            if(tail==-1){

            }else{
                vector<int>f;
                for(i=tail;i!=-1;i=load[i]){
                    f.push_back(i);
                }
                for(i=f.size()-2;i>=0;i--){
                    printf("%c",c[fp[f[i]]]);
                }
            }
            printf("\n");
        }
    }

return 0;
}
/*
8  7  1  5  2  6  3  4  x
1  2  3  4  5  6  7  8  x
2  3  4  1  5  x  7  6  8
1  2  3  x  4  5  6  7  8
x  1  2  3  4  5  6  7  8
*/
