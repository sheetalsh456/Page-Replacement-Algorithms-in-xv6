#include<stdio.h>
int main()
{
	double hr,mr;
	int i,j,n,a[50],frame[10],no,k,avail,count=0;
    printf("\n ENTER THE NUMBER OF PAGES:\n");
	scanf("%d",&n);
	printf("\n ENTER THE PAGE NUMBERS :\n");
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    printf("\n ENTER THE NUMBER OF FRAMES :\n");
    scanf("%d",&no);
	for(i=0;i<no;i++)
        frame[i]= -1;
    j=0;
    printf("\tref string\t page frames\n");
	for(i=1;i<=n;i++)
    {
        printf("%d\t\t",a[i]);
        avail=0;
        for(k=0;k<no;k++)
			if(frame[k]==a[i])
            {
            	avail=1;
            }    
        if(avail == 1)
        {
        	for(k=0;k<no;k++)
        		printf("%d\t",frame[k]);
        }    
        if (avail == 0)
       	{
       		frame[j]=a[i];
            j=(j+1)%no;
           	count++;
            for(k=0;k<no;k++)
               	printf("%d\t",frame[k]);
		}
        printf("\n");
	}
    printf("Page Fault is %d\n",count);
	hr=(n-count)*1.0/n;
	mr=count*1.0/n;
	printf("Hit Ratio is %lf\n",hr);
	printf("Miss Ratio is %lf\n",mr);
    return 0;
}
