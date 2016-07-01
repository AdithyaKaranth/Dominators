#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
struct Dominator
{
	std::vector<int> v;
};
typedef struct Dominator dom;
void insert(vector<int> &,int);
void display(vector<int>);
void find_predecessor(int,int,dom[],int [],int [][2]);
void dominator(int [][2],int,dom [],int);
int main()
{
	int n,i,j,graph[100][2],large=0,flag;
	cin>>n;
	for(i=0;i<n;i++)
		for(j=0;j<2;j++)
			cin>>graph[i][j];
	for(i=0;i<n;i++)
		for(j=0;j<2;j++)
			if(graph[i][j]>large)
				large=graph[i][j];
	dom *d=new dom[large];
	std::vector<int> *v=new std::vector<int>[large];
	for(i=0;i<large;i++)
	{
		insert(d[i].v,1);//root is a dominator for al elements
		insert(d[i].v,i+1); 
	}
	while(true)//repeat until no change
	{
		flag=1;
		for(i=0;i<large;i++)
			v[i]=d[i].v;
		dominator(graph,n,d,large);
		for(i=0;i<large;i++)
		{
			if(d[i].v!=v[i])
			{
				flag=0;
				break;
			}
		}
		if(flag)
			break;
	}
	for(i=0;i<large;i++)
	{
		cout<<"Dominator of "<<(i+1)<<":";
		display(d[i].v);
	}
}
void insert(vector<int> &v,int item)
{
	std::vector<int>::iterator it;
	for(it=v.begin();it!=v.end();++it)
		if(*it==item)
			return;
	v.insert(it,item);
}
void display(vector<int> v)
{
	std::vector<int>::iterator it;//iterator to move through the vector 
	for(it=v.begin();it!=v.end();++it)
		cout<<*it<<" ";
	cout<<"\n";
}
void dominator(int graph[][2],int n,dom d[],int large)
{
	int i,j,a[20];
	for(i=1;i<large;i++)
	{
		std::memset(a,0,sizeof(a));
		find_predecessor(i+1,n,d,a,graph);
		std::vector<int>v(d[i].v);
		std::vector<int> temp(d[a[1]-1].v);
		std::vector<int> inter;
		for(j=2;j<=a[0];j++)
		{
			std::set_intersection(temp.begin(),temp.end(),d[a[j]-1].v.begin(),d[a[j]-1].v.end(),std::back_inserter(inter));
			temp.clear();//to insert inter to temp
			temp.insert(temp.begin(),inter.begin(),inter.end());
			inter.clear();///to insert inter to temp
		}
		std::set_union(d[i].v.begin(),d[i].v.end(),temp.begin(),temp.end(),std::back_inserter(inter));//inter used to store the intermediate variable
		d[i].v.clear();
		d[i].v.insert(d[i].v.begin(),inter.begin(),inter.end());
	}

}
void find_predecessor(int item,int n,dom d[],int a[],int graph[][2])
{
	int i,j;
	for(i=0;i<n;i++)
		if(graph[i][1]==item)
			a[++(a[0])]=graph[i][0];
}
