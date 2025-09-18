#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"
static int billNo ;

void CalculateBill(Products *products)
{
    int id, Quant, choice, index = 0;
    
    int ids[100];
    int quan[100];
    time_t t;
    struct tm *tm_info;
    char datebuf[20], timebuf[20];
    time(&t); // get current time
    tm_info = localtime(&t);

    strftime(datebuf, sizeof(datebuf), "%Y-%m-%d", tm_info);
    strftime(timebuf, sizeof(timebuf), "%r", tm_info);

    //     printf("Date: %s\n", datebuf);
    // printf("Time: %s\n", timebuf);

    do
    {

        printf("Enter Product code : ");
        scanf("%d", &id);
        if (products->id[id] == 1)
        {

            printf("Enter Quantity : ");
            scanf("%d", &Quant);

            ids[index] = id;
            quan[index] = Quant;
            index++;

            printf("You Want to add more Items (1 / 0) : ");
            scanf("%d", &choice);
        }
        else
        {
            printf("Enter Valid id !!\n");
            printf("You Want to add more Items (1 / 0) : ");
            scanf("%d", &choice);
        }

    } while (choice != 0);

    if (index > 0)
    {
        double total = 0, grandttl = 0;
        printf("\n               --BILL OF CAFE--\n");
        printf("Bill No : %d     Date : %s     Time : %s\n", billNo++, datebuf, timebuf);
        //printf("\nALL Items : \n");
        printf("\n");
        printf("%-15s %10s %10s %10s\n","Item Name","Cost","Quantity","Total");
        printf("--------------------------------------------------------\n");
        for (int i = 0; i < index; i++)
        {
            total = products->product[ids[i]].price * quan[i];
            printf("%-15s %10.2lf %10d %10.2lf\n", products->product[ids[i]].name, products->product[ids[i]].price, quan[i], total);
            grandttl += total;
        }
        printf("--------------------------------------------------------\n");
        printf("%-15s %32.2lf\n","Grand Total : ", grandttl);
    }
}