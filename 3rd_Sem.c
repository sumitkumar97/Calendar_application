//The following program prints calendar for a specified year provided by the user or prints the month if the user specifies a particular month

#include <stdio.h>

int days_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31} ; // global integer array that stores no. of days for each month

int umonth = -1 ,da , ma , ya ;

int inputyear() //takes year as input from the user
{
  int year;
  printf("Please enter a year (example: 2016) : ");
  scanf("%d", &year);
  return year;
}

void inputmonth()
{
  printf("Enter the month (eg. 10)  : ") ;
  scanf("%d",&umonth) ;
}

void determineleapyear(int year) //determines whether provided year is leap year or not
{
  if(year% 4 == 0 && year%100 != 0 || year%400 == 0)
    {
      days_in_month[2] = 29;
    }
  else
    {
      days_in_month[2] = 28;
    }
}

//2-d character array that stores name of the months
char months[14][25]= { " ", "\n\n\nJanuary" , "\n\n\nFebruary" , "\n\n\nMarch" , "\n\n\nApril" , "\n\n\nMay" , "\n\n\nJune" , "\n\n\nJuly" , "\n\n\nAugust" , "\n\n\nSeptember", "\n\n\nOctober" , "\n\n\nNovember" , "\n\n\nDecember" };
char month_s[14][25]= { " ", "January" , "February" , "March" , "April" , "May" , "June" , "July" , "August" , "September", "October" , "November" , "December" };

int evaluate_day_code(int year) //evaluates day code  for the first day of the year
{
  int daycode;
  int a , b , c;

  a = (year - 1)/ 4 ;
  b = (year - 1)/ 100 ;
  c = (year - 1)/ 400 ;
  daycode = (year + a - b + c ) %7 ;
  return daycode ;
}



int calculate_no_of_days( int sd , int sm , int sy , int ed , int em , int ey )
{
  int iter , flag = 0 , nod = 0 , month , day ;
  if ( ey < sy )
    return -1 ;
  if ( ey == sy )
    if ( em < sm )
      return -1 ;
  if ( ey == sy )
    if ( em == sm )
      if ( ed <= sd )
	return -1 ;
  for ( iter = sy ; iter <= ey ; iter ++ )
    {
      determineleapyear(iter) ;
      printf("\n\n") ;
      for ( month = 1; month <= 12; month++ )
        {
	  if ( flag == 1)
	    printf("\n") ;
	  for ( day = 1; day <= days_in_month[month]; day++ )
            {
	      if ( day == ed && month == em && iter == ey )
		flag = 0 ;
	      if ( flag == 1 )
                {
		  printf( "%2d%12s%8d\n", day , month_s[month] , iter ) ;
		  nod++ ;
                }
	      if ( day == sd && month == sm && iter == sy )
		flag = 1 ;
            }
        }
    }
  return nod ;
}


int age_calculator ( int sd , int sm , int sy , int ed , int em , int ey )
{
  int iter , month , day ;
  da=0 , ma=0 , ya=0 ;
  if ( ey < sy )
    return -1 ;
  if ( ey == sy )
    if ( em < sm )
      return -1 ;
  if ( ey == sy )
    if ( em == sm )
      {
	if ( ed < sd )
	  return -1 ;
	else if ( ed == sd )
	  return 1 ;
      }



  if ( sy == ey )
    {
      if ( sm == em )
        {
	  ya = 0 ;
	  ma = 0 ;
	  da = ed - sd ;
        }
      else
        {
	  if ( ed >= sd )
            {
	      ya =  0 ;
	      ma = em - sm ;
	      da = ed - sd ;
            }
	  else
            {
	      ya = 0 ;
	      ma = em - sm - 1 ;
	      determineleapyear(ey) ;
	      da = days_in_month[em-1] - sd + ed ;
            }
        }
    }
  else
    {
      if ( em >= sm )
        {
	  if ( ed >= sd )
            {
	      ya =  ey - sy ;
	      ma = em - sm ;
	      da = ed - sd ;
            }
	  else
            {
	      ya = ey - sy ;
	      ma = em - sm - 1 ;
	      determineleapyear(ey) ;
	      da = days_in_month[em-1] - sd + ed ;
            }
        }
      else
        {
	  if ( ed >= sd )
            {
	      ya =  ey - sy - 1 ;
	      ma = 12 - sm + em ;
	      da = ed - sd ;
            }
	  else
            {
	      ya = ey - sy - 1 ;
	      ma = 12 - sm + em - 1 ;
	      determineleapyear(ey) ;
	      da = days_in_month[em-1] - sd + ed ;
            }
        }
    }


  if ( sm == em && sd == ed )
    printf("\nHAPPY BIRTHDAY !\n") ;
  return 1 ;
}



void calendar(int daycode , int year) // prints the calendar for a year
{
  int month, day;
  printf("\n\t%d",year) ;
  if ( umonth == -1 )
    {
      for ( month = 1; month <= 12; month++ )
        {
	  printf("%s", months[month]);
	  printf("\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n" );
	  // Corrects the position for the first date by adding spaces
	  for ( day = 1; day <= 1 + daycode * 5; day++ )
            {
	      printf(" ");
            }
	  // Prints all the dates for one month
	  for ( day = 1; day <= days_in_month[month]; day++ )
            {
	      printf("%2d", day ); //prints first day of the month

	      // Is the next day before Sat? If yes then add a space , Else add newline.
	      if ( ( day + daycode ) % 7 > 0 )
		printf("   " );
	      else
		printf("\n " );
            }
	  // Set position for next month
	  daycode = ( daycode + days_in_month[month] ) % 7;
        }
    }
  else
    {
      for ( month = 1; month <= 12; month++ )
        {
	  if ( month == umonth )
            {
	      printf("%s", months[month]);
	      printf("\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n" );
	      // Corrects the position for the first date by adding spaces
	      for ( day = 1; day <= 1 + daycode * 5; day++ )
                {
		  printf(" ");
                }
	      // Prints all the dates for one month
	      for ( day = 1; day <= days_in_month[month]; day++ )
                {
		  printf("%2d", day ); //prints first day of the month
		  // Is the next day before Sat? If yes then add a space , Else add newline.
		  if ( ( day + daycode ) % 7 > 0 )
		    printf("   " );
		  else
		    printf("\n " );
                }
            }
	  // Set position for next month
	  daycode = ( daycode + days_in_month[month] ) % 7;
        }
    }
}



void print_calendar( int daycode , int year )
{
  int month, day;
  FILE *fp1 ;
  fp1 = fopen ("output.txt","w") ;
  fprintf(fp1,"\n\t%d",year) ;
  for ( month = 1; month <= 12; month++ )
    {
      fprintf(fp1,"%s", months[month]);
      fprintf(fp1,"\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n" );
      // Corrects the position for the first date by adding spaces
      for ( day = 1; day <= 1 + daycode * 5; day++ )
        {
	  fprintf(fp1," ");
        }
      // Prints all the dates for one month in the file
      for ( day = 1; day <= days_in_month[month]; day++ )
        {
	  fprintf(fp1,"%2d", day ); //prints first day of the month
	  // Is the next day before Sat? If yes then add a space , Else add newline.
	  if ( ( day + daycode ) % 7 > 0 )
	    fprintf(fp1,"   " );
	  else
	    fprintf(fp1,"\n " );
        }
      // Set position for next month
      daycode = ( daycode + days_in_month[month] ) % 7;
    }
  fclose(fp1) ;
}


int main()
{
  int year, daycode , i , j , flag = 0 , k , control = 1 , choice , nod , sd , sm , sy , ed , em , ey , cd,cm,cy ,done=0 ;
  FILE *fp2 ;
  char entry[25] , centry[25] ;
  while ( control )
    {
      printf("\t\tCalendar Applications\n\n\n") ;
      printf("1.Print calendar for a year and save it in a text file\n\n") ;
      printf("2.Print calendar for specific month and year\n\n") ;
      printf("3.Print all the leap years between two given years\n\n") ;
      printf("4.Evaluate number of days between two dates and print them\n\n") ;
      printf("5.Age Calculator\n\n") ;
      printf("6.Make an entry to a particular date\n\n") ;
      printf("7.Check a particular date for entry\n\n") ;
      printf("8.See all the earlier made entries\n\n") ;
      printf("Enter your choice :  ") ;
      scanf("%d",&choice) ;
      umonth = -1 ;
      switch(choice)
        {
	case 1 :
	  year = inputyear();
	  daycode = evaluate_day_code(year);
	  determineleapyear(year);
	  calendar(daycode , year);
	  print_calendar(daycode , year) ;
	  break ;
	case 2 :
	  year = inputyear() ;
	  inputmonth() ;
	  daycode = evaluate_day_code(year) ;
	  determineleapyear(year) ;
	  calendar(daycode , year) ;
	  break ;
	case 3 :
	  printf("Enter the years between which you want to display all the leap years \n(eg.2000 2016)\n") ;
	  scanf("%d%d",&i,&j) ;
	  printf("Leap years :\n") ;
	  for (k = i ; k <= j ; k ++ )
	    {
	      if(k% 4 == 0 && k%100 != 0 || k%400 == 0)
		{
		  printf("%d\n",k) ;
		}
	    }
	  break ;
	case 4 :
	  printf("\nEnter the starting day , month and year respectively ( example : 18 4 2015 )\n") ;
	  scanf("%d%d%d",&sd,&sm,&sy) ;
	  printf("\nEnter the ending day , month and year respectively ( example : 30 10 2016 )\n") ;
	  scanf("%d%d%d",&ed,&em,&ey) ;
	  nod = calculate_no_of_days(sd,sm,sy,ed,em,ey) ;
	  if ( nod < 0 )
	    printf("\nInvalid Input\n") ;
	  else
	    printf("\nNumber of days between the dates provided is %d\n",nod) ;
	  break ;
	case 5 :
	  printf("\nEnter your birth date ( example : 18 4 2015 )\n") ;
	  scanf("%d%d%d",&sd,&sm,&sy) ;
	  printf("\nEnter the date on which you want to find you age or today's date if you want to find your age today ( example : 30 10 2016 )\n") ;
	  scanf("%d%d%d",&ed,&em,&ey) ;
	  nod = age_calculator(sd,sm,sy,ed,em,ey) ;
	  if ( nod < 0 )
	    printf("\nInvalid Input\n") ;
	  else
	    printf("\n%d Years %d Months %d Days\n\n",ya,ma,da) ;
	  break ;
	case 6 :
	  printf("\nEnter the date for which entry is to be made ( eg. 31 10 2016 )\n") ;
	  scanf("%d%d%d",&sd,&sm,&sy) ;
	  printf("\nEnter the entry : ") ;
	  fgets(entry,24,stdin) ;
	  fgets(entry,24,stdin) ;
	  fp2 = fopen("entry.txt","a") ;
	  fprintf(fp2,"%2d %2d %4d\t",sd,sm,sy) ;
	  fprintf(fp2,"%s\n",entry) ;
	  printf("Entry has been made\n") ;
	  fclose(fp2) ;
	  break ;
	case 7 :
	  printf("\nEnter the date for which you want to check entry\n") ;
	  scanf("%d%d%d",&sd,&sm,&sy) ;
	  done = 0 ;
	  fp2 = NULL ;
	  fp2 = fopen("entry.txt","r") ;
	  if ( fp2 == NULL )
	    {
	      printf("File not found") ;
	    }
	  else
	    {
	      while(!feof(fp2))
		{
		  fscanf(fp2 , "%d" , &cd) ;
		  fscanf(fp2 , "%d" , &cm) ;
		  fscanf(fp2 , "%d" , &cy) ;
		  fgets(centry,25,fp2) ;
		  if ( cd == sd && cm == sm && cy == sy )
		    {
		      puts(centry) ;
		      done = 1 ;
		      break ;
		    }
		}
	      if ( done == 0 )
		printf("No entries are made to this date\n") ;
	    }
	  fclose(fp2) ;
	  break ;
	case 8 :
	  fp2 = NULL ;
	  fp2 = fopen("entry.txt","r") ;
	  if(fp2 == NULL)
	    {
	      printf("NO Entries are made\n") ;
	    }
	  else
	    {
	      while(!feof(fp2))
		{
		  fscanf(fp2 , "%d" , &cd) ;
		  fscanf(fp2 , "%d" , &cm) ;
		  fscanf(fp2 , "%d" , &cy) ;
		  fgets(centry,25,fp2) ;
		  if ( !feof(fp2) )
		    printf("%2d %2d %4d %s\n",cd,cm,cy,centry) ;
		}
	    }
	  fclose(fp2) ;
	  break ;
	default :
	  printf("Wrong choice , please enter from the given choices\n") ;
        }
      printf("\n\nPress 1 to continue , 0 to exit\n") ;
      scanf("%d",&control) ;
      printf("\n\n\n") ;
    }
  return 0 ;
}
