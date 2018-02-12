#include<stdio.h>
#include<stdbool.h>
#include<time.h>
#include<stdlib.h>

void usage(void);
bool isleapyear(int);
void print_cal(int,int,int);
char *weekdays[7]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
char *monthes[12]={"January","Febuary","March","April","May","June","July","August","September","October","November","December"};
int BEGINYEAR=1900;
int mdays[2][12]={{31,28,31,30,31,30,31,31,30,31,30,31},{31,29,31,30,31,30,31,31,30,31,30,31}};
int ydays[]={365,366};

int main(int argc, char *args[])
{
    int only_month=1;
    int year=0,month=0,weekday=0,current_year,current_month;
    time_t current_time;
    time(&current_time);
    struct tm *TM=localtime(&current_time);
    current_year=TM->tm_year+1900;
    current_month=TM->tm_mon;

    if(argc==1)
    {
        year=current_year;
        month=current_month+1;
        }
    else if(argc==2)
    {
       only_month=0;
       year=atoi(args[1]);
        }
    else if(argc==3)
   {
        year=atoi(args[1]);
        month=atoi(args[2]);
        }
   else
     {  usage();
        exit(-1);
     }

    printf("\t Year %d \t\n\n",year);
    print_cal(year,month,only_month);
    return 0;
    }

void print_cal(int year,int month,int only_month)
{
    int days=0,y,weekday,yearflag;
    if(isleapyear(year))
        yearflag=1;
    else
        yearflag=0;
    for(y=BEGINYEAR;y<year;y++)
    {
       if(isleapyear(y))
           days+=ydays[1];
       else
           days+=ydays[0];
        }

    if(only_month)
    {
        printf("\t\t%s\t\t\n",monthes[month-1]);
        for(int i=0;i<7;i++)
          printf("%-10s",weekdays[i]);
        putchar('\n');
     for(int j=0;j<month-1;j++)
     {
         days+=mdays[yearflag][j];
         }
     weekday=days%7;
     if(weekday==0)
         weekday=1;
     else
         weekday+=1;

     printf("===================================================================\n");
     for(int k=1;k<weekday;k++)
        printf("%-10s","");
     for(int m=1;m<=mdays[yearflag][month-1];m++)
     {
         printf("%-10d",m);
         if(weekday%7==0)
         {  putchar('\n');
            weekday=0;
         }
         weekday+=1;
        }
    putchar('\n');
    }
    else
    {
        only_month=1;
        for(month=1;month<=12;month++)
           print_cal(year,month,only_month);
        }
}

void usage()
{
    printf("./cal [year] [month]\n");
    }

bool isleapyear(int year)
{
    if((year%400==0)||(year%4==0 && year%100!=0))
        return true;
    else
        return false;
    }

