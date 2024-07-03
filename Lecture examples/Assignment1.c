/* EECS22 Winter 2024: */
/* Assignment "hw1" submission for emalekza */
/* Due date: Wednesday January 17 12:00:00  2024*/

//Create an input selection for users to enter a valid calendar date

#include <stdio.h>
#include <stdlib.h>

int main(void){

    int q;  //day of the month
    int m;  //month of the year
    int y;  //year
    int h; //day of the week

    printf("Please enter a calendar date: \n");

    printf("Day, q = ");
    scanf("%d", &q);

    printf("Month, m = ");
    
    scanf("%d", &m);

    printf("Year, y = ");
    scanf("%d", &y);

    if (m < 3){
        m += 12;
        y -= 1;
    }
    
    int k = y % 100; //year of the century
    int J = y / 100; //zero-based century

    //Use zeller's congruence formula to calculate the day of the week
    h = ((q + (13 * (m + 1) / 5) + k + (k / 4) + (J / 4) + (5 * J)) % 7);

    //Output the day in numerical identifier (0-6) for each weekday
        printf("For the calendar date %d/%d/%d, the day of the week is %d. \n", m, q, y, h);
        switch(h){
            case 0:
                printf("This is a Saturday.\n");
                break;
            case 1:
                printf("This is a Sunday.\n");
                break;
            case 2:
                printf("This is a Monday.\n");
                break;
            case 3:
                printf("This is a Tuesday.\n");
                break;
            case 4:
                printf("This is a Wednesday.\n");
                break;
            case 5:
                printf("This is a Thursday.\n");
                break;
            case 6:
                printf("This is a Friday.\n");
                break;
            default:
                break;
        }
        
    return 0;

}