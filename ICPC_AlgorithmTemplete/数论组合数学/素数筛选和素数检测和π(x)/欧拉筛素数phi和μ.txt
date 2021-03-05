int prime[MAX],mob[MAX],phi[MAX],pcnt;
bool vis[MAX];
void getPrime(int n){
    rg int i,j,k;
    pcnt=0;
    mob[1]=phi[1]=vis[1]=1;
    for(i=2;i<n;i++){
        if(!vis[i]){
            prime[pcnt++]=i;
            phi[i]=i-1;
            mob[i]=-1;
        }
        for(j=k=0;i*prime[j]<n;j++){
            k=i*prime[j];
            vis[k]=1;
            if(i%prime[j]==0){
                phi[k]=phi[i]*prime[j];
                mob[k]=0;
                break;
            }else{
                mob[k]=-mob[i];
                phi[k]=phi[i]*(prime[j]-1);
            }
        }
    }
}