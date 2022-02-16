/* Assignment 1                     */
/*                                  */
/* Author : Jiancong Zhu(Kevin Zhu) */
/*                                  */
/* Modification：                   */
/* 01/03/2022 Final version         */

#include <stdio.h>

int main(void)
{
    // Input section : For user to input the day,month,and year
    int d; // To store the input of the day.
    int dtemp; // To temporay store the day.
    int m; // To store the input of the month.
    int mtemp; // To temporay store the month.
    int y; // To store the input of the year.
    int ytemp; // To temporay store the year.
    int K; // To store the year of the century
    int J;
    int w; // To store the result of day of week
    printf("Please enter a canlender date:\n");
    printf("Day, d = ");
    scanf("%d",&d);
    dtemp = d;
    printf("Month, m = ");
    scanf("%d",&m);
    mtemp = m;
    printf("Year, y = ");
    scanf("%d",&y);
    ytemp = y;
    
    //Data Preprocessing
    if(mtemp<3){
        mtemp = mtemp + 12;
        ytemp = ytemp - 1;
    }
    
    //Computation section
    J = ytemp / 100;
    K = ytemp % 100;
    w = (dtemp + ((mtemp+1)*13)/5 + K + K/4 + J/4 - 2*J)%7;
    
    // Output section
    if(w == 0){
        printf("For the calender date %d/%d/%d, the day of the week is %d.\n",m,d,y,w);
        printf("This is a Saturday\n");
    }
    else if(w == 1){
        printf("For the calender date %d/%d/%d, the day of the week is %d.\n",m,d,y,w);
        printf("This is a Sunday\n");
    }
    else if(w == 2){
        printf("For the calender date %d/%d/%d, the day of the week is %d.\n",m,d,y,w);
        printf("This is a Monday\n");
    }
    else if(w == 3){
        printf("For the calender date %d/%d/%d, the day of the week is %d.\n",m,d,y,w);
        printf("This is a Tuesday\n");
    }
    else if(w == 4){
        printf("For the calender date %d/%d/%d, the day of the week is %d.\n",m,d,y,w);
        printf("This is a Wednesday\n");
    }
    else if(w == 5){
        printf("For the calender date %d/%d/%d, the day of the week is %d.\n",m,d,y,w);
        printf("This is a Thursday\n");
    }
    else{
        printf("For the calender date %d/%d/%d, the day of the week is %d.\n",m,d,y,w);
        printf("This is a Friday\n");
    }
}


