#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"

int productindex[100] = {0};

void initialize(Products *products)
{
    *products = (Products){0};
    loadcontacts(products);
}

void saveItems(Products *products){
    FILE *fptr;
    fptr = fopen("Items.csv","w+");

    for(int i=0;i<max_ids;i++){
        fprintf(fptr,"%d,%s,%lf\n",products->id[i],products->product[i].name,products->product[i].price);
    }
    fclose(fptr);
    //exit(EXIT_SUCCESS);
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
        flag = 0;
        flag1 = 0;
        if(id >= 100){
            flag1 = 1;
        }        
            if (products->id[id] == 1)
            {
                flag = 1;
                
            }
        if (flag)
        {
            printf("\nEntered ID is Not available Try With Different \n");
        }else if(flag1){
            printf("\nIds Should be Between 0 to 99\n");
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
            printf("\nInValid Choice !! Please try Again \n");
        }
    } while (choice != 4);
}

void EditProduct(Products *products)
{
    int choice;
    do{
        printf("\nEdit Product Menu\n");
        printf("1.Edit Product Id\n");
        printf("2.Edit Product Name\n");
        printf("3.Edit Product Price\n");
        printf("4.Back to menu\n");
        printf("Enter Choice : ");
        scanf("%d",&choice);
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
            printf("\nInvalid Choice , Enter Valid choice !!\n");
            break;
        }
    }while(choice != 4);
}

void DeleteProduct(Products *products)
{
    
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
    int j = 0;
    printf("\nSearched Product\n");
    if (products->id[Id] == 1)
    {
        productindex[j] = Id;
        printf("Product ID : %d\n", Id);
        printf("Product Name : %s\n", products->product[Id].name);
        printf("Product Price : %lf\n", products->product[Id].price);
        printf("----------------------------\n");

        j++;
    }
    else
    {
        printf("Entered Id Doesn't have any details\n");
        productindex[j] = 0;
    }
}

void SearchName(Products *products)
{
    char name[20];
    printf("Enter Product Name : ");
    scanf(" %[^\n]", name);
    int flag = 0;
    int i = 0,j=0;
    printf("\nSearched Product\n");
    while (i < max_ids)
    {
        
        if (!strcasecmp(products->product[i].name, name))
        {
            flag = 1;
            productindex[j] = i;
            printf("Product ID : %d\n", i);
            printf("Product Name : %s\n", products->product[i].name);
            printf("Product Price : %lf\n", products->product[i].price);
            printf("----------------------------\n");
            j++;
        }
        i++;
    }
    if(!flag){
        productindex[j] = 0;
        printf("Entered name Not found\n");
    }
}

void SearchPrice(Products *products){
    double price;
    printf("Enter price : ");
    scanf("%lf",&price);
    int flag = 0;
    int i = 0,j = 0;
    printf("\nSearched Product\n");
    while (i < max_ids)
    {
        
        if (products->product[i].price == price)
        {
            flag = 1;
            productindex[j] = i;
            printf("Product ID : %d\n", i);
            printf("Product Name : %s\n", products->product[i].name);
            printf("Product Price : %lf\n", products->product[i].price);
            printf("----------------------------\n");
            j++;
        }
        i++;
    }
    if(!flag){
        printf("Entered name Not found\n");
    }
}

void loadcontacts(Products *products){
    FILE *fptr;
    fptr = fopen("Items.csv","r+");
    
    int i = 0,id;
    while(i < max_ids){

        if(fscanf(fptr,"%d,",&id) != 1){
            fscanf(fptr,"%*[^\n]");
            continue;
        }else{
            products->id[i] = id;
            fscanf(fptr,"%[^,],%lf",products->product[i].name,&products->product[i].price);
        }
        i++;
    }

    fclose(fptr);
}

void EditId(Products *products){

}

void Editbyname(Products *products){

}

void Editprice(Products *products){

}