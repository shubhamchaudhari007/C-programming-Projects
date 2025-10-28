#include <stdio.h>
#include <string.h>
#include "info.h"

int main()
{
    Products products;
    initialize(&products);
    int choice;

    do
    {
        printf("\n--BILL MACHINE--\n");
        printf("1.Admin pannel\n");
        printf("2.Calculate bill\n");
        printf("3.Stop Machine\n");
        printf("Enter your Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            printf("\n----Admin Login----\n");
            char name[50];
            int flag;
            do
            {
                flag = 0;
                printf("Enter a UserName : ");
                scanf(" %[^\n]", name);
                char AdminName[20] = "Admin@123";

                if (strcmp(AdminName, name))
                {
                    printf("!! INVALID USERNAME \n");
                    flag = 1;
                }
            } while (flag != 0);
            char pass[50];
            char AdminPass[20] = "12345";
            printf("Enter a Password to Enter Admin Pannel : ");
            scanf(" %[^\n]", pass);
            if (!strcmp(pass, AdminPass))
            {
                int choice1;
                do
                {
                    printf("\n--BILL MACHINE ADMIN--\n");
                    printf("1.Add New Product\n");
                    printf("2.Search Product\n");
                    printf("3.Edit product details\n");
                    printf("4.Delete product\n");
                    printf("5.Display all Products\n");
                    printf("6.Save Items\n");
                    printf("7.Bill History\n");
                    printf("8.Exit\n");
                    printf("Enter Your Choice : ");
                    scanf("%d", &choice1);

                    switch (choice1)
                    {
                    case 1:
                        Addproduct(&products);
                        break;

                    case 2:
                        SearchProduct(&products);
                        break;

                    case 3:
                        EditProduct(&products);
                        break;

                    case 4:
                        DeleteProduct(&products);
                        break;
                    case 5:
                        displayproducts(&products);
                        break;

                    case 6:
                        saveItems(&products);
                        break;

                    case 7:
                        billhistory(&products);

                    case 8:
                        break;

                    default:
                        printf("Invalid Choice ! Please Enter Valid choice !");
                    }

                } while (choice1 != 8);
            }
            else
            {
                printf("\nInvalid Password\n");
            }
            break;

        case 2:
            CalculateBill(&products);
            break;

        case 3:
            break;

        default:
            printf("Invalid Choice! please try again !\n");
        }
    } while (choice != 3);
}