#include<bits/stdc++.h>
using namespace std;
int fr[100];
int p[100],pt[100];
int n,f,i,cnt=0,pf=0;
double hr,mr;
int main()
{
	void display();
	printf("\nENTER NO.OF PAGES\n");
	scanf("%d",&n);
	printf("\nENTER THE PAGE NUMBERS\n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&p[i]);
		pt[i]=p[i];
	}
	printf("\nENTER NO.OF FRAMES\n");
	scanf("%d",&f);
	sort(pt,pt+n);
	for(i=0;i<n-1;i++)
	{
		if(pt[i]!=pt[i+1])
		cnt++;
	}
	if(cnt>=f)
		pf=f;
	else
		pf=cnt;
	int max,j,found=0,lg[f],index,k,l,flag1=0,flag2=0,frsize=f;
	for(i=0;i<f;i++)
	{
		fr[i]=-1;
	}
	for(j=0;j<n;j++)
	{
	    flag1=0;
	    flag2=0;
		for(i=0;i<f;i++)
	    {
			if(fr[i]==p[j])
		  	{
		    	flag1=1;
		      	flag2=1;
			    break;
		  	}
	    }
	    if(flag1==0)
		{
		  	for(i=0;i<f;i++)
		    {
			  	if(fr[i]==-1)
				{
				    fr[i]=p[j];
					flag2=1;
					break;
				}
			}
	    }
 
		if(flag2==0)
		{
		    for(i=0;i<f;i++)
				lg[i]=0;
			for(i=0;i<frsize;i++)
			{
				for(k=j+1;k<n;k++)
				{
					if(fr[i]==p[k])
					{
						lg[i]=k-j;
						break;
				    }
				}
			}
			found=0;
			for(i=0;i<frsize;i++)
			{
				if(lg[i]==0)
				{
					index=i;
					found=1;
					break;
				}
			}
			if(found==0)
			{
				max=lg[0];
			    index=0;
				for(i=1;i<frsize;i++)
			   {
					if(max<lg[i])
					{
						max=lg[i];
						index=i;
					}
			    }
		 	}
	       fr[index]=p[j];
	       pf++;
		}
	    display();
	}
	printf("\n no of page faults:%d\n",pf);
	mr=pf*1.0/n;
	hr=(n-pf)*1.0/n;
	printf("\nHit Ratio is %lf\n",hr);
	printf("\nMiss Ratio is %lf\n",mr);
	return 0;
}
void display()
{
	int i;
	printf("\n");
	for(i=0;i<f;i++)
		printf("\t%d",fr[i]);
}
