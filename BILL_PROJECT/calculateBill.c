#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"
int billNo;

// Append a completed bill to dayhistory.csv using a simple tagged format:
// D,<date>
// B,<billNo>,<time>
// I,<name>,<quantity>,<total>
// E
static void append_bill_history(const char *date, int bill_number, const char *timebuf, Products *products, int ids[], int quan[], int count)
{
    char lastDate[32] = "";
    char buf[128];
    FILE *fr = fopen("dayhistory.csv", "r");
    if (fr)
    {
        while (fgets(buf, sizeof(buf), fr))
        {
            if (buf[0] == 'D' && buf[1] == ',')
            {
                // store most recent date header
                char *d = buf + 2;
                // trim newline
                char *nl = strchr(d, '\n');
                if (nl)
                    *nl = '\0';
                strncpy(lastDate, d, sizeof(lastDate) - 1);
                lastDate[sizeof(lastDate) - 1] = '\0';
            }
        }
        fclose(fr);
    }

    FILE *fa = fopen("dayhistory.csv", "a");
    if (!fa)
        return;

    if (lastDate[0] == '\0' || strcmp(lastDate, date) != 0)
        fprintf(fa, "D,%s\n", date);

    fprintf(fa, "B,%d,%s\n", bill_number, timebuf);

    for (int i = 0; i < count; ++i)
    {
        char namebuf[51];
        // copy product name (max 50) and strip commas
        strncpy(namebuf, products->product[ids[i]].name, sizeof(namebuf) - 1);
        namebuf[sizeof(namebuf) - 1] = '\0';
        for (char *p = namebuf; *p; ++p)
            if (*p == ',')
                *p = ' ';
        double price = products->product[ids[i]].price;
        double total = price * quan[i];
        // Write: name,price,quantity,total  (price placed in 2nd position as requested)
        fprintf(fa, "I,%s,%.2lf,%d,%.2lf\n", namebuf, price, quan[i], total);
    }

    fprintf(fa, "E\n");
    fclose(fa);
}

// Read dayhistory.csv and return the next bill number for given date.
// If date not present or no bills, return 1.
static int get_next_billno(const char *date)
{
    FILE *f = fopen("dayhistory.csv", "r");
    if (!f)
        return 1;
    char buf[128];
    int in_date = 0;
    int last = 0;
    while (fgets(buf, sizeof(buf), f))
    {
        if (buf[0] == 'D' && buf[1] == ',')
        {
            char *d = buf + 2;
            char *nl = strchr(d, '\n');
            if (nl)
                *nl = '\0';
            if (strcmp(d, date) == 0)
                in_date = 1;
            else if (in_date)
                break;
        }
        else if (in_date && buf[0] == 'B' && buf[1] == ',')
        {
            int bno = 0;
            if (sscanf(buf + 2, "%d", &bno) == 1)
                if (bno > last)
                    last = bno;
        }
    }
    fclose(f);
    return last + 1;
}

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

    strftime(datebuf, sizeof(datebuf), "%d-%m-%Y", tm_info);
    strftime(timebuf, sizeof(timebuf), "%r", tm_info);

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
    // printf("Enter Payment Mode :\n");
    // printf("1. Cash\n");

    if (index > 0)
    {
        // initialize bill number from history so numbering persists across runs
        int currentBill = get_next_billno(datebuf);
        billNo = currentBill + 1; // set global for next in-memory bills
        double total = 0, grandttl = 0;
        printf("\n               --BILL OF CAFE--\n");
        printf("Bill No : %d     Date : %s     Time : %s\n", currentBill, datebuf, timebuf);
        // printf("\nALL Items : \n");
        printf("\n");
        printf("%-30s %6s %10s %12.2s\n", "Item Name", "Cost", "Qty", "Total");
        printf("-----------------------------------------------------------------\n");
        for (int i = 0; i < index; i++)
        {
            total = products->product[ids[i]].price * quan[i];
            printf("%-30s %6.3lf %10d %12.3lf\n", products->product[ids[i]].name, products->product[ids[i]].price, quan[i], total);
            grandttl += total;
        }
        printf("-----------------------------------------------------------------\n");
        printf("%-30s %6s %10s %12.2lf\n", "Grand Total : ", "", "", grandttl);

        // Append this bill to history file (use currentBill)
        append_bill_history(datebuf, currentBill, timebuf, products, ids, quan, index);
    }
}