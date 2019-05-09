struct Graphic{
    int V1,V2;
    int mat[MAX][MAX];
    inline void push(cint b,cint e,cint val){
    	mat[b][e]=val;
    }
    void clear(){
        memset(mat,0,sizeof(mat));//0代表边不存在 
    }
};
Graphic g;
int vis[MAX],ytox[MAX],ind[MAX];
inline bool Hungary_dfs(int now){//找到一个最大匹配
    for(int i=1;i<=g.V2;i++){
        if(!vis[i]&&g.mat[now][i]){
            vis[i]++;
            if(ytox[i]==0||Hungary_dfs(ytox[i])){
                ytox[i]=now;
                return true;
            }
        }
    }
    return false;
}
int Hungary(){
    int i,cnt=0;
    memset(ytox,0,sizeof(ytox));
    for(i=1;i<=g.V1;i++){
       memset(vis,0,sizeof(vis));
       cnt+=Hungary_dfs(i);
    }
    return cnt;
}
