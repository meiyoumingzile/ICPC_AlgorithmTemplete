#include<stdio.h>
#include<queue>
#include<iostream>
#include<string.h>
using namespace std;
char mapp[101][101];
bool vis[101][101];
int n;
int fx[4]={1,-1,0,0};
int fy[4]={0,0,1,-1};
struct node{
 int x,y;
};
node BEGIN,END;
void bfs()
{
 int i;
    memset(vis,0,sizeof(vis));
    node d,nextd;
    queue<node> q;
    q.push(BEGIN);
    vis[BEGIN.x][BEGIN.y]=1;
    while(!q.empty())
 {
        d=q.front();
        q.pop();
        //printf("%d  %d\n",d.x,d.y);
        if(d.x==END.x&&d.y==END.y)
  {
            printf("YES\n");
            return;
        }
        for(i=0;i<4;i++)
  {
            nextd.x=d.x+fx[i];
            nextd.y=d.y+fy[i];
            printf("%d %d %d %c\n",nextd.x,nextd.y,vis[nextd.x][nextd.y],mapp[nextd.x][nextd.y]);
            if(nextd.x>=0&&nextd.x<n&&nextd.y>=0&&nextd.y<n
               &&vis[nextd.x][nextd.y]==0&&mapp[nextd.x][nextd.y]!='#')
   {
    printf("d");
                vis[nextd.x][nextd.y]=1;
                q.push(nextd);
            }
        }
    }
    printf("NO\n");
    return ;
}


int main(){
  int k;
  scanf("%d",&k);
  while(k--){
  int i,j;
  scanf("%d",&n);
  for(i=0;i<n;i++)
  {
   getchar();
   for(j=0;j<n;j++)
   {
    scanf("%c",&mapp[i][j]);
   }
  }
  for(i=0;i<n;i++)
  {
   for(j=0;j<n;j++)
   {
    printf("%c",mapp[i][j]);
   }
   printf("\n");
  }
  scanf("%d%d",&BEGIN.x,&BEGIN.y);
  scanf("%d%d",&END.x,&END.y);
  bfs();
 }
}
