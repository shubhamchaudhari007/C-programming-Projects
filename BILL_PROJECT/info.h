#ifndef INFO_H
#define INFO_H

#define max_ids 100

typedef struct 
{
    char name[50];
    double price;
}Product;

typedef struct{
    int id[max_ids] ;
    Product product[max_ids];
}Products;

void CalculateBill(Products *products);

void initialize(Products *products);
void Addproduct(Products *products);
void SearchProduct(Products *products);
void EditProduct(Products *products);
void DeleteProduct(Products *products);
void saveItems(Products *products);

void displayproducts(Products *products);

void SearchId(Products *products);
void SearchName(Products *products);
void SearchPrice(Products *products);
void loadproducts(Products *products);

void EditId(Products *products);
void Editbyname(Products *products);
void Editprice(Products *products);

int validateid(int id);
void billhistory(Products *products);

#endif