//BFS and DFS traversals using Adjacency list

#include<iostream>
using namespace std;

class node
{
    int data;
    node* next;
public :
    friend class graph;
    node(int x)
    {
        data=x;
        next=NULL;
    }
};

class graph
{
    node* G[20];
    int visited[20];
public :
    graph(int n)
    {
        for(int i=0; i<n; i++){
            G[i] = new node(i);
        }
    }

    void create(int n)
    {
        node *temp, *q;
        int s, d;
        cout<<"Enter source and destination for each edge : "<<endl;
        for(int i=0; i<n; i++){
            cout<<"Edge "<<i<<" : ";
            cin>>s>>d;
            temp = G[s];
            while(temp->next!=NULL)
                temp=temp->next;
            q = new node(d);
            temp->next = q;
            temp = G[d];
            while(temp->next!=NULL)
                temp=temp->next;
            q = new node(s);
            temp->next = q;
        }
    }

    void BFS(int v1)
    {
        node *temp;
        int Q[20], f=0, r=-1;
        for(int i=0; i<20; i++){
            Q[i]=-1;
            visited[i]=0;
        }
        Q[++r] = v1;
        visited[v1] = 1;
        while(Q[f]!=-1){
            int x = Q[f];
            cout<<x<<" ";
            temp = G[x];
            while(temp!=NULL){
                if(visited[temp->data]==0){
                    Q[++r]=temp->data;
                    visited[temp->data]=1;
                }
                temp=temp->next;
            }
            f++;
        }
    }

    void DFS(int v1)
    {
        for(int i=0; i<20; i++) visited[i]=0;
        dfs(v1, visited);
    }

    void dfs(int v,int visited[])
    {
        cout<<v<<" ";
        visited[v]=1;
        node* temp = G[v];
        while(true){
            while(temp!=NULL && visited[temp->data]!=0)
                temp = temp->next;
            if(temp!=NULL)
                dfs(temp->data, visited);
            else break;
        }
    }

    void search()
    {
        while(true){
            int n;
            cout<<"\nEnter the vertex to be searched : (enter -1 to exit) : ";
            cin>>n;
            if(n<0) break;
            else if(visited[n]==1) cout<<"Vertex found";
            else cout<<"Vertex not found";
        }
    }
};

int main()
{
    int n;
    cout<<"Enter number of vertices in the graph : ";
    cin>>n;
    graph g(n);

    cout<<"Enter number of edges in your graph : ";
    cin>>n;
    g.create(n);

    cout<<"Enter the vertex for initiating BFS : ";
    cin>>n;
    g.BFS(n);

    cout<<"\nEnter the vertex for initiating DFS : ";
    cin>>n;
    g.DFS(n);

    g.search();
}

/*				0
			   / \
			  1   2
			 / \   \
			3  4    5
			\ /      \
			 6        7
*/
/*
 			0
 		  / | \
 		 /  |  \
 		1   4   3
 		 \  |  /
 		  \ | /
 		 	2
 */
