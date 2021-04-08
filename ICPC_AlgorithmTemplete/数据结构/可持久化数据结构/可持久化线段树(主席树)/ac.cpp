    #include<cstdio>
    #include<cctype>
    #include<iomanip>
    #include<algorithm>
    #include<cmath>
    #include<cstdlib>
    #include<cstring>
    #define lowbit(a) a&(-a)//ֱ�Ӷ��嵽����ò�ƻ����
    #define W while
    #define R register
    #define IN inline
    #define gc getchar()
    #define MAX 200005
    IN void in(int &x)//���
    {
        x=0;R char c=gc;
        W(!isdigit(c))c=gc;
        W(isdigit(c)){x*=10;x+=c-48;c=gc;}
    }
    namespace President_Tree//��ϯ������
    {
        int cnt,siz,dot,idx;
        //�ֱ�����ڴ������±꣬��ͬ��ֵ��ĸ������ܹ��ĵ������޸Ĳ������±�
        struct order//��Ϊ��ϯ���������ߣ����Խ�ָ�������
        {
            bool typ;//�ǲ�ѯ�����޸�
            int from,to,k;
        }command[MAX];
        struct node
        {int son[2],sum;}tree[MAX*250];
        //�ڴ�һ��Ҫ�����㹻����Ϊ�����ﾲ̬��ϯ������״���鹲����������ڵĵ�
        int root[MAX],cpy[MAX],data[MAX];
        //�ֱ𱣴澲̬��ϯ���ĸ��ڵ㣬��ɢ��������ݣ�ԭʼ����
        int build(int lef,int rig)//�������������߶������
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
        int updata(int last,int pos,int val)//��������ڵ���߲��뾲̬��ϯ���ĺ���
        //Ϊ�˷���ɾ��������val�����޸ĵ���
        {
            int now=cnt++,tmp=now,mid;
            int lef=0,rig=siz-1;//��Ϊ��ֵ���߶��������Ա��������ɢ����Ķ�Ӧ�����ı��
            tree[now].sum=tree[last].sum+val;
            W(lef<rig)//�ǵݹ齵�ͳ���
            {
                mid=(lef+rig)>>1;
                if(pos<=mid)//������ڵ���������
                {
                    tree[now].son[1]=tree[last].son[1];//��ô��ǰ�ڵ���������ڵ��֮ǰ���ǿ�Ȩֵ�߶������ýڵ�
                    tree[now].son[0]=cnt++;//�����¿�һ���ڵ�
                    now=tree[now].son[0];
                    last=tree[last].son[0];
                    rig=mid;
                }
                else//ͬ��
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
        IN int ID(int now)//����ĳ��������ɢ����������е�λ��
        {
            return std::lower_bound(cpy,cpy+siz,now)-cpy;
        }
    }
    namespace Bit_Tree//��״�������
    {
        using namespace President_Tree;
        int vir[MAX],use[MAX];
        //�ֱ�Ϊ��״����Ľڵ㣬����ǰ׺��ʱ��ǰ�ߵĽڵ�
        IN void add(int now,int pos,int val)
        //��Ϊ��״����ķ���Ĳ�ǰ׺�͵Ĺ��ܣ����ǰѸı���ÿ���޸��ڶ�Ӧ�Ľڵ���
        {
            W(now<=dot)
            {
                vir[now]=updata(vir[now],pos,val);
                now+=lowbit(now);
            }
        }
        IN int getsum(int now)//��ѯ��ǰ�����ֵ���������Ĵ�С
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
            int left_root=root[left-1];//��̬��ϯ������������ĸ��ڵ�
            int right_root=root[right];
            int lef=0,rig=siz-1;//��ѯʱ���ҷ�Χ
            for(R int i=left-1;i;i-=lowbit(i))
                use[i]=vir[i];//��ʼ������ֵ�Ĳ�ѯ·��
            for(R int i=right;i;i-=lowbit(i))
                use[i]=vir[i];
            W(lef<rig)
            {
                int mid=(lef+rig)>>1;
                int now_sum=getsum(right)-getsum(left-1)+tree[tree[right_root].son[0]].sum-tree[tree[left_root].son[0]].sum;//��ѯ��ǰ���������Ƿ�����ﵽ��k��
                //�ھ�̬��ϯ������״������һ����
                if(now_sum>=kth)//�ﵽ��
                {
                    rig=mid;
                    for(R int i=left-1;i;i-=lowbit(i))
                        use[i]=tree[use[i]].son[0];//��ô���Ǿͽ���ѯ��Χ��С����������
                    for(R int i=right;i;i-=lowbit(i))
                        use[i]=tree[use[i]].son[0];
                    left_root=tree[left_root].son[0];//ͬʱ��̬��ϯ��ҲҪ���
                    right_root=tree[right_root].son[0];
                }
                else//û�ﵽ�����������ڷ�Χ��������
                {
                    lef=mid+1;
                    kth-=now_sum;//��Ϊ������������һ���ֵ㣬����Ҫ��ȥ
                    for(R int i=left-1;i;i-=lowbit(i))
                        use[i]=tree[use[i]].son[1];
                    for(R int i=right;i;i-=lowbit(i))
                        use[i]=tree[use[i]].son[1];
                    left_root=tree[left_root].son[1];
                    right_root=tree[right_root].son[1];
                }
            }
            return lef;//�����ǵڼ�����ɢ����������
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
            in(data[i]);cpy[i-1]=data[i];//cpy��0��ʼ�淽��unique��sort
        }
        char c[10];
        for(R int i=1;i<=num;++i)//��ָ����������
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
                cpy[idx++]=command[i].k;//������޸ĵĻ�����cpy��
            }
        }
        sort(cpy,cpy+idx);
        siz=unique(cpy,cpy+idx)-cpy;
        //��������ɢ������

        root[0]=build(0,siz-1);//�����վ�̬��ϯ��

        for(R int i=1;i<=dot;++i)
            root[i]=updata(root[i-1],ID(data[i]),1);//�������ľ�̬��ϯ��
        for(R int i=1;i<=dot;++i)
            vir[i]=root[0];//��ʼ����״����
        for(R int i=1;i<=num;++i)//����ָ��
        {
            if(!command[i].typ)
            {
                printf("%d\n",cpy[query(command[i].from,command[i].to,command[i].k)]);
            }
            else
            {
                add(command[i].from,ID(data[command[i].from]),-1);
                add(command[i].from,ID(command[i].k),1);
                data[command[i].from]=command[i].k;//Ҫ��ԭ�����޸��������ݣ����򷭳�
            }
        }
        return 0;
}
