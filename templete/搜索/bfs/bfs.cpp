#include<stdio.h>
#include<queue>
#include<cstring>
#include<iostream>
using namespace std;
const int MAX=110;
int n;
int fx[4]={0,0,1,-1};
int fy[4]={1,-1,0,0};
char mapp[MAX][MAX];
bool vis[ MAX][MAX];
struct node{
    int x,y;
    bool isLeg(){
        return x>=0&&y>=0&&x<n&&y<n&&vis[x][y]==0&&mapp[x][y]!='#';
    }
};

node B,E;
void bfs(){
    node d,next;
    queue<node> q;
    memset(vis,0,sizeof(vis));
    vis[B.x][B.y]=1;
    q.push(B);
    while(!q.empty()){
        d=q.front();
        q.pop();
        if(d.x==E.x&&d.y==E.y){
            printf("Yes\n");
            return;
        }
        for(int i=0;i<4;i++){
            next.x=d.x+fx[i];
            next.y=d.y+fy[i];
            if(next.x>=0&&next.x<n&&next.y>=0&&next.y<n&&vis[next.x][next.y]==0&&mapp[next.x][next.y]!='#'){
                vis[next.x][next.y]=1;
                q.push(next);
            }
        }
    }
    printf("No\n");
}
int main(){
    int i,j,k,t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(i=0;i<n;i++){
            getchar();
            for(j=0;j<n;j++){
                scanf("%c",&mapp[i][j]);
            }
        }
        scanf("%d%d%d%d",&B.x,&B.y,&E.x,&E.y);
        bfs();
    }
return 0;}
/*
1
3
..#
..#
#..
0 0 2 2
*/
