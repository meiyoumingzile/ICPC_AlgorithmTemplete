    #include<cstdio>
    #include<cctype>
    #include<iomanip>
    #include<algorithm>
    #include<cmath>
    #include<cstdlib>
    #include<cstring>
    #define lowbit(a) a&(-a)//直接定义到这里貌似会更快
    #define W while
    #define R register
    #define IN inline
    #define gc getchar()
    #define MAX 200005
    IN void in(int &x)//快读
    {
        x=0;R char c=gc;
        W(!isdigit(c))c=gc;
        W(isdigit(c)){x*=10;x+=c-48;c=gc;}
    }
    namespace President_Tree//主席树部分
    {
        int cnt,siz,dot,idx;
        //分别代表内存分配的下标，不同数值点的个数，总共的点数，修改操作的下标
        struct order//因为主席树必须离线，所以将指令存下来
        {
            bool typ;//是查询还是修改
            int from,to,k;
        }command[MAX];
        struct node
        {int son[2],sum;}tree[MAX*250];
        //内存一定要开的足够大，因为在这里静态主席树和树状数组共用这个数组内的点
        int root[MAX],cpy[MAX],data[MAX];
        //分别保存静态主席树的根节点，离散化后的数据，原始数据
        int build(int lef,int rig)//建立空树，和线段树差不多
        {
            int now=cnt++;
            tree[cnt].sum=0;
            if(lef!=rig)
            {
                int mid=(lef+rig)>>1;
                tree[now].son[0]=build(lef,mid);
                tree[now].son[1]=build(mid+1,rig);
            }
            return now;
        }
        int updata(int last,int pos,int val)//更新虚拟节点或者插入静态主席树的函数
        //为了方便删除，传入val代表修改的量
        {
            int now=cnt++,tmp=now,mid;
            int lef=0,rig=siz-1;//因为是值域线段树，所以保存的是离散化后的对应的数的编号
            tree[now].sum=tree[last].sum+val;
            W(lef<rig)//非递归降低常数
            {
                mid=(lef+rig)>>1;
                if(pos<=mid)//待插入节点在左子树
                {
                    tree[now].son[1]=tree[last].son[1];//那么当前节点的右子树节点和之前的那棵权值线段树共用节点
                    tree[now].son[0]=cnt++;//向左新开一个节点
                    now=tree[now].son[0];
                    last=tree[last].son[0];
                    rig=mid;
                }
                else//同上
                {
                    tree[now].son[0]=tree[last].son[0];
                    tree[now].son[1]=cnt++;
                    now=tree[now].son[1];
                    last=tree[last].son[1];
                    lef=mid+1;
                }
                tree[now].sum=tree[last].sum+val;
            }
            return tmp;
        }
        IN int ID(int now)//返回某个数在离散化后的数组中的位置
        {
            return std::lower_bound(cpy,cpy+siz,now)-cpy;
        }
    }
    namespace Bit_Tree//树状数组相关
    {
        using namespace President_Tree;
        int vir[MAX],use[MAX];
        //分别为树状数组的节点，计算前缀和时向前走的节点
        IN void add(int now,int pos,int val)
        //因为树状数组的方便的查前缀和的功能，我们把改变量每次修改在对应的节点中
        {
            W(now<=dot)
            {
                vir[now]=updata(vir[now],pos,val);
                now+=lowbit(now);
            }
        }
        IN int getsum(int now)//查询当前点更改值的左子树的大小
        {
            int ret=0;
            W(now>0)
            {
                ret+=tree[tree[use[now]].son[0]].sum;
                now-=lowbit(now);
            }
            return ret;
        }
        IN int query(int left,int right,int kth)
        {
            int left_root=root[left-1];//静态主席树的两个相减的根节点
            int right_root=root[right];
            int lef=0,rig=siz-1;//查询时左右范围
            for(R int i=left-1;i;i-=lowbit(i))
                use[i]=vir[i];//初始化更改值的查询路径
            for(R int i=right;i;i-=lowbit(i))
                use[i]=vir[i];
            W(lef<rig)
            {
                int mid=(lef+rig)>>1;
                int now_sum=getsum(right)-getsum(left-1)+tree[tree[right_root].son[0]].sum-tree[tree[left_root].son[0]].sum;//查询当前点的左儿子是否满足达到了k个
                //在静态主席树和树状数组上一起算
                if(now_sum>=kth)//达到了
                {
                    rig=mid;
                    for(R int i=left-1;i;i-=lowbit(i))
                        use[i]=tree[use[i]].son[0];//那么我们就将查询范围缩小至左子树内
                    for(R int i=right;i;i-=lowbit(i))
                        use[i]=tree[use[i]].son[0];
                    left_root=tree[left_root].son[0];//同时静态主席树也要如此
                    right_root=tree[right_root].son[0];
                }
                else//没达到就在右子树内范围继续查找
                {
                    lef=mid+1;
                    kth-=now_sum;//因为有了左子树的一部分点，所以要减去
                    for(R int i=left-1;i;i-=lowbit(i))
                        use[i]=tree[use[i]].son[1];
                    for(R int i=right;i;i-=lowbit(i))
                        use[i]=tree[use[i]].son[1];
                    left_root=tree[left_root].son[1];
                    right_root=tree[right_root].son[1];
                }
            }
            return lef;//返回是第几个离散出来的数据
        }
    }
    using namespace President_Tree;
    using namespace Bit_Tree;
    using std::sort;
    using std::unique;
    using std::printf;
    using std::scanf;
    int main()
    {
        printf("%d",lowbit(7));
        int num;
        in(dot),in(num);
        idx=dot;
        for(R int i=1;i<=dot;++i)
        {
            in(data[i]);cpy[i-1]=data[i];//cpy从0开始存方便unique和sort
        }
        char c[10];
        for(R int i=1;i<=num;++i)//将指令离线下来
        {
            scanf("%s",c);
            if(c[0]=='Q')
            {
                command[i].typ=false;
                in(command[i].from);in(command[i].to);in(command[i].k);
            }
            else
            {
                command[i].typ=true;
                in(command[i].from);in(command[i].k);
                cpy[idx++]=command[i].k;//如果是修改的话存入cpy中
            }
        }
        sort(cpy,cpy+idx);
        siz=unique(cpy,cpy+idx)-cpy;
        //以上是离散化输入

        root[0]=build(0,siz-1);//建立空静态主席树

        for(R int i=1;i<=dot;++i)
            root[i]=updata(root[i-1],ID(data[i]),1);//建立满的静态主席树
        for(R int i=1;i<=dot;++i)
            vir[i]=root[0];//初始化树状数组
        for(R int i=1;i<=num;++i)//处理指令
        {
            if(!command[i].typ)
            {
                printf("%d\n",cpy[query(command[i].from,command[i].to,command[i].k)]);
            }
            else
            {
                add(command[i].from,ID(data[command[i].from]),-1);
                add(command[i].from,ID(command[i].k),1);
                data[command[i].from]=command[i].k;//要将原数据修改至新数据，否则翻车
            }
        }
        return 0;
}
