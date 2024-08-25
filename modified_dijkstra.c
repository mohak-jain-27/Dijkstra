#include <stdio.h>

void initialize(int path[],int visited[],float cost[],int n,float dist[])//initializing the arrays
{
    int i;
    for(i=0;i<n;i++)
    {
        path[i]=-1;//tracks the shortest path
        visited[i]=0;//tracks if node i is visited or not
        cost[i]=999.0;//tracks the shortest path distance
        dist[i]=999.0;
    }
}

void relaxation(int u,int n,float cost[],int input[n][n],int visited[],int path[],int initial_energy[],int current_energy[],float alpha,float dist[])//relaxes the cost[] if possible
{
    int i;
    for(i=0;i<n;i++)
    {
        if(input[u][i]!=999 && visited[i]==0)//checks if direct edge is present
        {
            if(cost[i]>cost[u]+input[u][i]+(float)alpha*(initial_energy[i]-current_energy[i]))//if the new cost is less than the previous cost
            {
                dist[i]=dist[u]+input[u][i];
                cost[i]=cost[u]+input[u][i]+(float)alpha*(initial_energy[i]-current_energy[i]);//updates it
                path[i]=u;
            }
        }
    }
}

void dijkstra(int n,int input[n][n])
{
    int path[n],visited[n];
    float cost[n],dist[n];
    int u,i,s,d;
    int count=0,min,pos;
    int initial_energy[n];
    int current_energy[n];
    float alpha;


    printf("Enter the weighing factor : ");
    scanf("%f",&alpha);



    printf("Enter the current energy level of :\n");
    for(i=0;i<n;i++)
    {
        initial_energy[i]=100;
        printf("Node %d : ",(i+1));
        scanf("%d",&current_energy[i]);
    }

    initialize(path,visited,cost,n,dist);

    printf("Enter the source node : v");
    scanf("%d",&s);

    printf("Enter the destination node : v");
    scanf("%d",&d);

    u=s-1;
    dist[u]=0;
    cost[u]=0;//distance from source node is always 0
    visited[u]=1;//marking the source node as visited
    path[u]=-1;//this node does not have any previous node ,therefore -1

    while(visited[d-1]==0)//while the destination node isn't reached
    {
        relaxation(u,n,cost,input,visited,path,initial_energy,current_energy,alpha,dist);//relax all adjacent nodes if required

        min=999;
        for(i=0;i<n;i++)//loop to find the nearest node to u
        {
            if(min>cost[i] && visited[i]==0)
            {
                min=cost[i];
                pos=i;
            }
        }

        u=pos;//the nearest node to u is now the new node in the shortest path
        visited[u]=1;
    }
    printf("\nThe value of cost function is : %f\n",cost[d-1]);
    printf("\nThe shortest distance while distributing energy uniformly from v%d to v%d is %f\n",s,d,dist[d-1]);

    printf("\nPath - ");
    i=d-1;
    while(i!=-1)//printing the path by backtracking
    {
        current_energy[i]=current_energy[i]-10;
        if(path[i]==-1)
            printf("v%d",(i+1));
        else
            printf("v%d <-- ",(i+1));
        i=path[i];
    }

    printf("\n\nThe Current Energy Levels of nodes after tansmission :\n");
    for(i=0;i<n;i++)
    {
        printf("Node %d : %d\n",(i+1),current_energy[i]);
    }
    printf("\n");

        
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