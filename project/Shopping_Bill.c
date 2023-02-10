

/*           CODED BY :- SINGH SUKESH                                                      */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items{
    char item[20];                  // no of item take thats is 20
    float price;
    int qty;
};

struct orders{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];                    // to store different types of item 
};
//functions to generate biils
void generateBillHeader(char name[50],char date[30]){              //-------------[1]
    printf("\n\n");
        printf("\t      KRISHNA Restaurant");
        printf("\n--------------------------------------");
        printf("\nDate:%s",date);
        printf("\nInvoice To: %s",name);
        printf("\n");
        printf("---------------------------------------\n");
        printf("Items\t\t");
        printf("Qty\t\t");
        printf("Total\t\t");
        printf("\n---------------------------------------");
        printf("\n\n");
}

void generateBillBody(char item[30],int qty, float price){       //----------------[2]
    printf("%s\t\t",item); 
        printf("%d\t\t",qty); 
        printf("%.2f\t\t",qty * price); 
        printf("\n");
}


void generateBillFooter(float total){                           //----------------[3]
    printf("\n");
    float dis = 0.1*total;
    float netTotal=total-dis;
    float cgst=0.09*netTotal,grandTotal=netTotal + 2*cgst;//netTotal + cgst + sgst
    printf("---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n---------------------------------------\n");
}
int main(){
    
    int opt,n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y',contFlag = 'y';  //countFlage is used to run code continous without using again again new terminal open
    char name[50];    // for case3:
    FILE *fp;
       //dashboard
    while(contFlag == 'y'){
    system("clear");     // to remove unwanted line form the Bill
    float total = 0;
    int invoiceFound = 0;
    printf("\t============KRISHNA RESTAURANT============");
    printf("\n\nPlease select your prefered operation");
    printf("\n\n1.Generate Invoice");   //case1:
    printf("\n2.Show all Invoices");   //case2:
    printf("\n3.Search Invoice");     //case3:
    printf("\n4.Exit");              //case4:

    printf("\n\nYour choice:\t");
    scanf("%d",&opt);
    fgetc(stdin);
    switch(opt){



        case 1:   // FOR Generate Invoice                               //-------------case[1]
        system("clear");
        printf("\nPlease enter the name of the customer:\t");
        fgets(ord.customer,50,stdin);
        ord.customer[strlen(ord.customer)-1] = 0;
        strcpy(ord.date,__DATE__);
        printf("\nPlease enter the number of items:\t");
        scanf("%d",&n);
        ord.numOfItems = n;
        for(int i=0;i<n;i++){
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item %d:\t",i+1);
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf("Please enter the quantity:\t");
            scanf("%d",&ord.itm[i].qty);
            printf("Please enter the unit price:\t");
            scanf("%f",&ord.itm[i].price);
            total += ord.itm[i].qty * ord.itm[i].price;
        }

        generateBillHeader(ord.customer,ord.date);
        for(int i=0;i<ord.numOfItems;i++){
            generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
        }
        generateBillFooter(total);

        printf("\nDo you want to save the invoice [y/n]:\t");
        scanf("%s",&saveBill);

        if(saveBill == 'y'){
            fp = fopen("RestaurantBill.dat","a+");
            fwrite(&ord,sizeof(struct orders),1,fp);
            if(fwrite != 0)
            printf("\nSuccessfully saved");
            else 
            printf("\nError saving");
            fclose(fp);
        }
        break;




        case 2:     //FOR Search Invoice                                   //case-------------[2]
        system("clear");
        fp = fopen("RestaurantBill.dat","r");
        printf("\n  *****Your Previous Invoices*****\n");
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;
            generateBillHeader(order.customer,order.date);
            for(int i=0;i<order.numOfItems;i++){
                generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty * order.itm[i].price;
            }
            generateBillFooter(tot);
        }
        fclose(fp);
        break;




        case 3:                                                        //case----------------[3]
        printf("Enter the name of the customer:\t");
        //fgetc(stdin);
        fgets(name,50,stdin);
        name[strlen(name)-1] = 0;
        system("clear");
        fp = fopen("RestaurantBill.dat","r");
        printf("\t*****Invoice of %s*****",name);   //%s means the name of the customer
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;
            if(!strcmp(order.customer,name)){
            generateBillHeader(order.customer,order.date);
            for(int i=0;i<order.numOfItems;i++){
                generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty * order.itm[i].price;
            }
            generateBillFooter(tot);
            invoiceFound = 1;  // if its found
            }
        
        }
        if(!invoiceFound){     // invoice not found
            printf("Sorry the invoice for %s doesnot exists",name);
        }           // %s means the name of the customer

        fclose(fp);
        break;
        



    case 4:     // FOR exist                                     //case---------------[4]
    printf("\n\t\t Bye Bye :)\n\n");
    exit(0);
    break;




    default:
    printf("Sorry invalid option");
    break;
    }
    
    printf("\nDo you want to perform another operation?[y/n]:\t");
    scanf("%s",&contFlag);
     //  for continous run program without close it
    }
    printf("\n\t\t Bye Bye :)\n\n");
    printf("\n\n");

    return 0;
}
