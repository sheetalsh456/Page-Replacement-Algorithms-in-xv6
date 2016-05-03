#include<stdio.h>
#define SIZE 3
int full=0;//To check whether all frames are filled
int a[21],n;//To take the input
int frame[SIZE];
int ctr[SIZE]={0};//Counter to know the frequency, intially all have zero frequency of use
int repptr;
int b[21] = {0};
int freq[21] = {0};
int m = 0;
int count=0;
int display()
{
    int i;
    printf("\nThe elements in the frame are\n");
    for(i=0;i<full;i++)
    {    printf("%d\n",frame[i]);
       // printf("%d\t",b[i] );
        //printf("%d\n",freq[i] );
}

}
int Longestopt()
{
    int i,min,min_val=100;
    min=0;
    //for(i=0;i<SIZE;i++)//The page with least frequency is selected as victim
        //if(ctr[min]>ctr[i])
    for(i=0;i<m;i++)//The page with least frequency is selected as victim
    {
        if(freq[i]==-1)
        {
            //min++;
            continue;
        }
        else 
        {
            if (min_val>freq[i])
            {   min_val=freq[i];
                min = i;
            }
        }

        
    }
    repptr=min;
    return repptr;
}
int x = 1;
int Pagerep(int ele)
{
    
    int temp,u;
    repptr=Longestopt();//The victim page is selected with the help of a function
    for(int i=0;i<full;i++)
    {
        if(b[repptr]==frame[i])
            u =i;
    }
    temp=frame[u];
    frame[u]=ele;
    for(int g=0;g<m;g++)
    {
        if(b[g]==temp)
        {
            b[g] = -1;
            freq[g] = -1;
        }
    }
    for(int h=0;h<m;h++)
    {
        if(b[h]==ele)
        {
            freq[h]++;
            x = 0;
            break;
        }
    }
    if(x==1)
    {
        b[m] = ele;
        freq[m]++;   
        m++;
    }
    //for(int i=0;i<m;i++){
      //  printf(" %d \t",freq[i] );
   // }

    //ctr[repptr]=1;//A new page is brought, hence it's counter is set to 1
    return temp;   
}
int Pagefault(int ele)
{
    if(full!=SIZE)
    {
        ctr[full]++;//The counters will increase initially for all frames till they are full
        frame[full++]=ele;
        b[m] = ele;
        freq[m]++;
        m++;

    }
    else
    printf("The page replaced is %d",Pagerep(ele));
}
int Search(int ele)
{
    int i,flag;
    flag=0;
    if(full!=0)
    {
        for(i=0;i<full;i++)
            if(ele==frame[i])
            { 
                flag=1;
                ctr[i]++;//Whenever a reference is made the counter is incremented

                for(int o=0;o<m;o++)
                {
                    if(ele==b[o])
                    {
                        freq[o]++;
                    }
                }
                break;
            }
    }
    return flag;   
}
int main()
{
    int i;
	//printf("Enter the no.of elements\n"); 
    FILE *fp;
    fp=fopen("Input.txt","r");
    printf("The number of elements in the reference string are :");
    fscanf(fp,"%d",&n);
    printf("%d",n);
    for(i=0;i<n;i++)
        fscanf(fp,"%d",&a[i]);
    printf("\nThe elements present in the string are\n");
    for(i=0;i<n;i++)
        printf("%d  ",a[i]);
    printf("\n\n");
    for(i=0;i<n;i++)
    {
        if(Search(a[i])!=1)
        {
            Pagefault(a[i]);
            display();
            count++;
        }
        else 
            display();
    }

    printf("\nThe number of page faults are %d\n",count);
    float hr,mr;
    mr = (count *1.0)/n;
    hr = ((n-count)*1.0)/n;
    printf("Hit ratio is : %f\nMiss ratio is : %f\n",hr,mr);
	return 0;
}
 