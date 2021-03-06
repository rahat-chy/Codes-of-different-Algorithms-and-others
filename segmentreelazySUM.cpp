#include<bits/stdc++.h>
using namespace std;


long long int arr[1000002],tree[4*1000002],lazy[4*1000002];
void build(long long int node,long long int a,long long int b)
{
    if(a>b)
        return;
    if(a==b)
    {
        tree[node]=arr[a];
        return;
    }
    long long int mid=(a+b)/2;
    build(node*2,a,mid);
    build(node*2+1,1+mid,b);
    tree[node]=tree[node*2]+tree[node*2+1];
}
void update(long long int node,long long int a,long long int b,long long int i,long long int j,long long int value)
{
    if(lazy[node]!=0)
    {
        tree[node]+=(((b-a)+1)*lazy[node]);
        if(a!= b)
        {

            lazy[node*2]+=lazy[node];
            lazy[node*2+1]+=lazy[node];
        }

        lazy[node]=0;
    }
    if(a>b || a>j || b<i)
        return;
    if(a>=i && b<=j)
    {
        tree[node]+=(((b-a)+1)*value);
        if(a!=b)
        {

            lazy[node*2]+=value;
            lazy[node*2+1]+=value;
        }

        return;
    }
    int mid=(a+b)/2;
    update(node*2,a,mid,i,j,value);
    update(1+node*2,1+mid,b,i,j,value);
    tree[node]=tree[node*2]+tree[node*2+1];
}
long long int query(long long int node,long long int a,long long int b,long long int i,long long int j)
{
    //long long int res=1;
    if(a>b || a>j || b<i)
        return 0;
    if(lazy[node]!=0)
    {
        tree[node]+=(((b-a)+1)*lazy[node]);
        if(a!= b)
        {

            lazy[node*2]+=lazy[node];
            lazy[node*2+1]+=lazy[node];
        }

        lazy[node]=0;
    }
    if(a>=i && b<=j)
        return tree[node];
    long long int mid=(a+b)/2;
    long long int q1=query(node*2,a,mid,i,j);
    long long int q2=query(1+node*2,1+mid,b,i,j);
    return q1+q2;
}

int main()
{
    ios_base::sync_with_stdio(false);

    long long int i,j,k,f,e,a,b,c,d,t,n,m,q,l,r;
    cin>>t;
    while(t--)
    {
        //memset(tree,0,sizeof(tree));
        cin>>n>>q;
        for(i=0; i<4*n; i++)
            lazy[i]=0;
        for(i=0; i<n; i++)
        {
            arr[i]=0;
        }
        build(1,0,n-1);
        /* for(i=1;i<=15;i++){
             cout<<tree[i];
         }*/
        for(i=1; i<=q; i++)
        {
            cin>>a;
            if(a==1)
            {
                cin>>l>>r;
                cout<<query(1,0,n-1,l-1,r-1)<<"\n";;
            }
            else
            {
                cin>>l>>r>>b;
                update(1,0,n-1,l-1,r-1,b);

            }
        }
    }
    return 0;
}
