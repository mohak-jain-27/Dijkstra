#include <stdio.h>

void initialize(int path[],int visited[],int dist[],int n)//initializing the arrays
{
    int i;
    for(i=0;i<n;i++)
    {
        path[i]=-1;//tracks the shortest path
        visited[i]=0;//tracks if node i is visited or not
        dist[i]=999;//tracks the shortest path distance
    }
}

void relaxation(int u,int n,int dist[],int input[n][n],int visited[],int path[])//relaxes the dist[] if possible
{
    int i;
    for(i=0;i<n;i++)
    {
        if(input[u][i]!=999 && visited[i]==0)//checks if direct edge is present
        {
            if(dist[i]>dist[u]+input[u][i])//if the new dist is less than the previous distance
            {
                dist[i]=dist[u]+input[u][i];//updates it
                path[i]=u;
            }
        }
    }
}

void dijkstra(int n,int input[n][n])
{
    int path[n],visited[n], dist[n];
    int u,i,s,d;
    int count=0,min,pos;

    initialize(path,visited,dist,n);

    printf("Enter the source node : v");
    scanf("%d",&s);

    printf("Enter the destination node : v");
    scanf("%d",&d);

    u=s-1;
    dist[u]=0;//distance from source node is always 0
    visited[u]=1;//marking the source node as visited
    path[u]=-1;//this node does not have any previous node ,therefore -1

    while(visited[d-1]==0)//while the destination node isn't reached
    {
        relaxation(u,n,dist,input,visited,path);//relax all adjacent nodes if required

        min=999;
        for(i=0;i<n;i++)//loop to find the nearest node to u
        {
            if(min>dist[i] && visited[i]==0)
            {
                min=dist[i];
                pos=i;
            }
        }

        u=pos;//the nearest node to u is now the new node in the shortest path
        visited[u]=1;
    }

    printf("\nThe shortest distance from v%d to v%d is %d\n",s,d,dist[d-1]);

    printf("\nPath - ");
    i=d-1;
    while(i!=-1)//printing the path by backtracking
    {
        if(path[i]==-1)
            printf("v%d",(i+1));
        else
            printf("v%d <-- ",(i+1));
        i=path[i];
    }

    // printf("Path matrix - ");
    // for(i=0;i<n;i++)
    // {
    //     printf("%d",path[i]);
    // }

        
}

void main ()
{
    int n,i,j;
    printf("Enter the number of nodes : ");
    scanf("%d",&n);
    
    int input[n][n];

    printf("Enter the matrix (0-for itself 999-for no direct edge) :\n");//taking the input matrix as input
    for (i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&input[i][j]);
        }
    }

    printf("\nThe input matrix :\n");//printing the input matrix in more readable form
    for (i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(input[i][j]>99)
                printf("%d ",input[i][j]);    
            else if(input[i][j]>9)
                printf(" %d ",input[i][j]);
            else
                printf(" %d  ",input[i][j]);
        }
        printf("\n");
    }
    dijkstra(n,input);
}