#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"

int pindex;

void initialize(Products *products)
{
    *products = (Products){0};
    loadproducts(products);
}

void saveItems(Products *products)
{
    FILE *fptr;
    fptr = fopen("Items.csv", "w+");

    for (int i = 0; i < max_ids; i++)
    {
        fprintf(fptr, "%d,%s,%lf\n", products->id[i], products->product[i].name, products->product[i].price);
    }
    fclose(fptr);
    // exit(EXIT_SUCCESS);
}

void Addproduct(Products *products)
{
    int id;
    int flag;
    int flag1;
    do
    {
        printf("Enter id for product to add : ");
        scanf("%d", &id);
        if (!validateid(id))
        {
            printf("\nIds Should be Between 0 to 99\n");
        }
        else if (products->id[id] == 1)
        {
            printf("\n❌ Entered ID is Not available Try With Different \n");
        }
        else
        {
            products->id[id] = 1;
            printf("Enter Product Name : ");
            scanf(" %[^\n]", products->product[id].name);
            getchar();
            printf("Enter Product Price : ");
            scanf("%lf", &products->product[id].price);
            flag = 0;
            printf("✅ Product Added Successfully ");
        }
    } while (flag != 0);
}

void SearchProduct(Products *products)
{
    int choice;
    do
    {
        printf("\nSearch Product\n");
        printf("1.Search by Id\n");
        printf("2.Search by name\n");
        printf("3.Search ny price\n");
        printf("4.Back to Menu\n");
        printf("\nEnter Your Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            SearchId(products);
            break;

        case 2:
            SearchName(products);
            break;

        case 3:
            SearchPrice(products);
            break;

        case 4:
            break;

        default:
            printf("\n❌ InValid Choice !! Please try Again \n");
        }
    } while (choice != 4);
}

void EditProduct(Products *products)
{
    int choice;
    SearchProduct(products);
    do
    {
        printf("\nEdit Product Menu\n");
        printf("1.Edit Product Id\n");
        printf("2.Edit Product Name\n");
        printf("3.Edit Product Price\n");
        printf("4.Back to menu\n");
        printf("Enter Choice : ");
        scanf("%d", &choice);
        __fpurge(stdout);

        switch (choice)
        {
        case 1:
            EditId(products);
            break;
        case 2:
            Editbyname(products);
            break;
        case 3:
            Editprice(products);
            break;
        case 4:
            break;
        default:
            printf("\n❌ Invalid Choice , Enter Valid choice !!\n");
            break;
        }
    } while (choice != 4);
}

void DeleteProduct(Products *products)
{
    SearchProduct(products);
    if (pindex == -1)
    {
        printf("\n❌ please search Product first and then Come to delete\n");
        return;
    }

    int index;
    printf("\nEnter id of product from search result to delete : ");
    scanf("%d", &index);

    products->id[index] = 0;
    strcpy(products->product[index].name, "");
    products->product[index].price = 0;

    printf("\n✅ Product Deleted Successfully !!\n");
}

void displayproducts(Products *products)
{
    int i = 0;
    printf(" --- All Products --- \n");
    while (i < max_ids)
    {
        if (products->id[i] == 1)
        {
            // printf(" --- All Products --- ");
            printf("product ID : %d\n", i);
            printf("product Name : %s\n", products->product[i].name);
            printf("product Price : %lf\n", products->product[i].price);
            printf("-----------------------------------\n");
        }
        i++;
    }
}

void SearchId(Products *products)
{
    int Id;
    printf("Enter Id (0 - 99): ");
    scanf("%d", &Id);
    // int j = 0;
    printf("\nSearched Product\n");
    if (products->id[Id] == 1)
    {
        pindex = 1;
        printf("Product ID : %d\n", Id);
        printf("Product Name : %s\n", products->product[Id].name);
        printf("Product Price : %lf\n", products->product[Id].price);
        printf("----------------------------\n");
    }
    else
    {
        printf("❌ Entered Id Doesn't have any details\n");
        pindex = -1;
    }
}

void SearchName(Products *products)
{
    char name[20];
    printf("Enter Product Name : ");
    scanf(" %[^\n]", name);
    int flag = 0;
    int i = 0;
    printf("\nSearched Product\n");
    while (i < max_ids)
    {

        if (!strcasecmp(products->product[i].name, name))
        {
            flag = 1;
            pindex = 1;
            printf("Product ID : %d\n", i);
            printf("Product Name : %s\n", products->product[i].name);
            printf("Product Price : %lf\n", products->product[i].price);
            printf("----------------------------\n");
        }
        i++;
    }
    if (!flag)
    {
        pindex = -1;
        printf("❌ Entered name Not found\n");
    }
}

void SearchPrice(Products *products)
{
    double price;
    printf("Enter price : ");
    scanf("%lf", &price);
    int flag = 0;
    int i = 0;
    printf("\nSearched Product\n");
    while (i < max_ids)
    {

        if (products->product[i].price == price)
        {
            flag = 1;
            pindex = -1;
            printf("Product ID : %d\n", i);
            printf("Product Name : %s\n", products->product[i].name);
            printf("Product Price : %lf\n", products->product[i].price);
            printf("----------------------------\n");
        }
        i++;
    }
    if (!flag)
    {
        pindex = -1;
        printf("❌ Entered name Not found\n");
    }
}

void loadproducts(Products *products)
{
    FILE *fptr;
    fptr = fopen("Items.csv", "r+");

    int i = 0, id;
    while (i < max_ids)
    {

        if (fscanf(fptr, "%d,", &id) != 1)
        {
            fscanf(fptr, "%*[^\n]");
            continue;
        }
        else
        {
            products->id[i] = id;
            fscanf(fptr, "%[^,],%lf", products->product[i].name, &products->product[i].price);
        }
        i++;
    }

    fclose(fptr);
}

void EditId(Products *products)
{
    if (pindex == -1)
    {
        printf("\n❌ Please first search the product and then come to edit  \n");
        return;
    }

    int index1, index2;
    printf("\nEnter id No from above Search results to edit id : ");
    scanf("%d", &index1);
    int flag = 0;
    do
    {
        printf("\nEnter new Id : ");
        scanf("%d", &index2);

        if (products->id[index2] != 1 && validateid(index2))
        {
            products->id[index2] = 1;
            strcpy(products->product[index2].name, products->product[index1].name);
            products->product[index2].price = products->product[index1].price;

            products->id[index1] = 0;
            strcpy(products->product[index1].name, "");
            products->product[index1].price = 0;
            flag = 1;
            printf("\n ✅ Product Id Edit Successfull !!\n");
        }
        else
        {
            flag = 0;
            printf("\n❌ Please enter different id it is already used by another product\n");
        }
    } while (flag != 1);
}

void Editbyname(Products *products)
{
    if (pindex == -1)
    {
        printf("\n❌ Please first search the product and then come to edit  \n");
        return;
    }
    int index1;
    char name[50];
    printf("\nEnter id No from above Search results to edit Name : ");
    scanf("%d", &index1);

    printf("Enter New name : ");
    scanf(" %[^\n]", name);

    strcpy(products->product[index1].name, name);
    printf("\n ✅ product Name Edit Successfully !!\n");
}

void Editprice(Products *products)
{
    if (pindex == -1)
    {
        printf("\n❌ Please first search the product and then come to edit!! \n");
        return;
    }
    int index1;
    double price;
    printf("\nEnter id No from above Search results to edit Name : ");
    scanf("%d", &index1);

    printf("Enter New price : ");
    scanf("%lf", &price);

    products->product[index1].price, price;
    printf("\n✅ product Price Edit Successfully !!\n");
}

int validateid(int id)
{
    if (id >= max_ids)
    {
        return 0;
    }
    return 1;
}

void billhistory(Products *products)
{
    char reqdate[32];
    printf("Enter date (dd-mm-YYYY): ");
    scanf(" %31[^\n]", reqdate);

    FILE *f = fopen("dayhistory.csv", "r");
    if (!f)
    {
        printf("No history file\n");
        return;
    }

    char line[256];
    int show = 0;
    int found = 0; /* becomes 1 when we find a bill for the date */
    double bill_total = 0.0;
    while (fgets(line, sizeof(line), f))
    {
        if (line[0] == 'D' && line[1] == ',')
        {
            char *d = line + 2;
            char *nl = strchr(d, '\n');
            if (nl)
                *nl = '\0';
            show = (strcmp(d, reqdate) == 0);
            continue;
        }
        if (!show)
            continue;

        if (line[0] == 'B' && line[1] == ',')
        {
            int b;
            char t[32] = "";
            if (sscanf(line + 2, "%d,%31[^\n]", &b, t) >= 1)
                printf("\nBill %d  Time: %s\n", b, t);
            found = 1;
            bill_total = 0.0; /* reset for new bill */
            printf("%-25s %6s %8s %8s\n", "Item", "Price", "Qty", "Total");
            printf("-------------------------------------------------------------\n");
            continue;
        }

        if (line[0] == 'I' && line[1] == ',')
        {
            char name[51];
            double price;
            int q;
            double tot;
            if (sscanf(line + 2, "%50[^,],%lf,%d,%lf", name, &price, &q, &tot) == 4) {
                printf("%-25s %6.2lf %8d %8.2lf\n", name, price, q, tot);
                bill_total += tot;
            }
            continue;
        }

        if (line[0] == 'E') {
            printf("-------------------------------------------------------------\n");
            printf("%-25s %6s %8s %8.2lf\n", "Bill Grand Total:", "", "", bill_total);
        }
    }
    fclose(f);
    if (!found)
        printf("No record found for %s\n", reqdate);
}