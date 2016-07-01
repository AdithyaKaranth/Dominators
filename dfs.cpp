#include<iostream>
#include<cstring>
using namespace std;
struct NODE
{
	int n;
	bool visited;
};
typedef struct NODE node;
int c=0;
void search(node [],int,int [][2],int[],int);
int main()
{
	int graph[40][2],dfs[40][2],n,i,j,large=0,count=0;
	cin>>n;
	for(i=0;i<n;i++)
		for(j=0;j<2;j++)
		{
			cin>>graph[i][j];
			if(graph[i][j]>large)
				large=graph[i][j];
		}
	int *dfn=new int [large];
	node *nod=new node [large];
	for(i=0;i<large;i++)
	{
		nod[i].n=i+1;
		nod[i].visited=false;
	}
	c=large;
	search(nod,1,graph,dfn,n);//to specify the node
	//for(i=0;i<large;i++)
		//cout<<(i+1)<<":"<<dfn[i]<<endl;
	for(i=0;i<n;i++)
		if(dfn[graph[i][0]-1]<dfn[graph[i][1]-1])
		{
			dfs[count][0]=graph[i][0];
			dfs[count++][1]=graph[i][1];
		}
	cout<<count<<endl;
	for(i=0;i<count;i++)
		cout<<dfs[i][0]<<" "<<dfs[i][1]<<endl;
}	
void search(node n[],int nod,int graph[][2],int dfn[],int edges)//no of edges
{
	int a[20],num=0,i;
	std::memset(a,0,sizeof(a));
	n[nod-1].visited=true;
	for(i=0;i<edges;i++)
		if(graph[i][0]==n[nod-1].n)//to find successors
			a[num++]=graph[i][1];
	for(i=0;i<num;i++)
		if(!(n[a[i]-1].visited))
			search(n,a[i],graph,dfn,edges);
	dfn[nod-1]=c--;
	
}
