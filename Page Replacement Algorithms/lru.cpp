#include<stdio.h>
main()
{
      double hr,mr;
      int q[20],p[50],c=0,c1,d,f,i,j,k=0,n,r,t,b[20],c2[20];
      printf("\nENTER THE NO.OF PAGES :\n");
      scanf("%d",&n);
      printf("\nENTER THE PAGE NUMBERS :\n");
      for(i=0;i<n;i++)
            scanf("%d",&p[i]);
      printf("\nENTER THE NO.OF FRAMES :\n");
      scanf("%d",&f);
      q[k]=p[k];
      printf("\n\t%d\n",q[k]);
      c++;
      k++;
      for(i=1;i<n;i++)
      {
            c1=0;
            for(j=0;j<f;j++)
            {
                  if(p[i]!=q[j])
                        c1++;
            }
            if(c1==f)
            {
                  c++;
                  if(k<f)
                  {
                        q[k]=p[i];
                        k++;
                        for(j=0;j<k;j++)
                              printf("\t%d",q[j]);
                        printf("\n");
                  }
                  else
                  {
                        for(r=0;r<f;r++)
                        {
                              c2[r]=0;
                              for(j=i-1;j<n;j--)
                              {
                                    if(q[r]!=p[j])
                                    {
                                          c2[r]++;
                                          /*if(i==4&&r==1)
                                          {
                                                printf("%d %d %d ",q[r],p[j],c2[r]);
                                          }*/
                                    }      
                                    else
                                          break;
                              }
                        }
                        /*if(i==4)
                        {
                              printf("HI\n");
                              for(r=0;r<f;r++)
                                    printf("%d ",c2[r]);
                              printf("%s\n","Hello" );
                        }*/
                        for(r=0;r<f;r++)
                               b[r]=c2[r];
                        for(r=0;r<f;r++)
                        {
                              for(j=r;j<f;j++)
                              {
                                    if(b[r]<b[j])
                                    {
                                          t=b[r];
                                          b[r]=b[j];
                                          b[j]=t;
                                    }
                              }
                        }
                        for(r=0;r<f;r++)
                        {
                              if(c2[r]==b[0])
                                    q[r]=p[i];
                              printf("\t%d",q[r]);
                        }
                        printf("\n");
                  }
            }
            else
            {
                  for(k=0;k<f;k++)
                        printf("\t%d",q[k]); 
                  printf("\n");       
            }      
      }
      mr=c*1.0/n;
      hr=(n-c)*1.0/n;
      printf("\nThe no of page faults is %d\n",c);
      printf("\nHit Ratio is %lf\n",hr);
      printf("\nMiss Ratio is %lf\n",mr);
}
