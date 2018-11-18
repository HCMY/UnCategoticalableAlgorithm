#include<stdio.h>

void main()
{
    int bursting_time[20],process[20],waiting_time[20],turnaround_wating_time[20];
    int i,j,n,total=0,pos,temp;
    float avg_wt,avg_tat;
    printf("number of process:");
    scanf("%d",&n);

    printf("\nEnter Bursting Time:\n");
    for(i=0;i<n;i++)
    {
        printf("p%d:",i+1);
        scanf("%d",&bursting_time[i]);
        process[i]=i+1;           //contains process number
    }

    //sorting burst time in ascending order using selection sort
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(bursting_time[j]<bursting_time[pos])
                pos=j;
        }

        temp=bursting_time[i];
        bursting_time[i]=bursting_time[pos];
        bursting_time[pos]=temp;

        temp=process[i];
        process[i]=process[pos];
        process[pos]=temp;
    }

    waiting_time[0]=0;            //waiting time for first process will be zero

    //calculate waiting time
    for(i=1;i<n;i++)
    {
        waiting_time[i]=0;
        for(j=0;j<i;j++)
            waiting_time[i]+=bursting_time[j];

        total+=waiting_time[i];
    }

    avg_wt=(float)total/n;      //average waiting time
    total=0;

    printf("\nProcess\t    Bursting Time    \tWaiting Time\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        turnaround_wating_time[i]=bursting_time[i]+waiting_time[i];     //calculate turnaround time
        total+=turnaround_wating_time[i];
        printf("\np%d\t\t  %d\t\t    %d\t\t\t%d",process[i],bursting_time[i],waiting_time[i],turnaround_wating_time[i]);
    }

    avg_tat=(float)total/n;     //average turnaround time
    printf("\n\nAverage Waiting Time=%f",avg_wt);
    printf("\nAverage Turnaround Time=%f\n",avg_tat);
}
