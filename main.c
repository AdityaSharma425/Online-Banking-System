#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct payer {
    char name[50];
    char fname[50];
    char mname[50];
    char uid[15];
    char phno[12];
    char dob[15];
    float bal;
    int acno;
    int pass;
    char tr[5];
    float ac;
};

void add_record() {
    struct payer p;

    char temp;

    printf("Enter name: ");
    scanf("%d",&temp);
    scanf("%[^\n]%*c", p.name);

    printf("Enter father's name: ");
    scanf("%[^\n]%*c", p.fname);

    printf("Enter mother's name: ");
    scanf("%[^\n]%*c", p.mname);

    printf("Enter AADHAR Card Number: ");
    scanf("%[^\n]%*c", p.uid);

    printf("Enter Mobile Number: ");
    scanf("%[^\n]%*c", p.phno);

    printf("Enter Date of Birth: ");
    scanf("%[^\n]%*c", p.dob); 

    p.acno=time(0);

    printf("Account Created Successfully!\n");
    printf("Account number is : %d\n", p.acno);

    printf("Create Password (6 digits): ");
    scanf("%d",&p.pass);

    printf("Enter initial deposit (in Rs) :");
    scanf("%f",&p.bal);


    FILE *f = fopen("bankac.txt", "ab");
    if (f == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE *fp = fopen("stat.txt", "ab");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fwrite(&p, sizeof(struct payer), 1, f);
    fwrite(&p, sizeof(struct payer), 1, fp);
    

    fclose(f);
    fclose(fp);

    printf("Record added successfully.\n");

}

void list_records() {
    struct payer p;

    FILE *f = fopen("bankac.txt", "rb");
    if (f == NULL) {
        printf("Error opening file.\n");
        return;
    }
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-20s %-20s %-30s %-30s %-20s %-20s %-20s %-20s\n","Account No", "Name", "Father's Name", "Mother's Name","AADHAR No", "Mobile No", "Date of Birth", "Balance");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    while (fread(&p, sizeof(struct payer), 1, f) == 1) {
        printf("%-20d %-20s %-30s %-30s %-20s %-20s %-20s %-20.2f\n", p.acno, p.name, p.fname, p.mname, p.uid, p.phno, p.dob, p.bal);
    }
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    printf("\n");
    fclose(f);
}

void search_record() {
    char uno[50];
    int password;
    struct payer p;

    printf("Enter AADHAR No to search: ");
    scanf("%s", uno);

    FILE *f = fopen("bankac.txt", "rb");
    if (f == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&p, sizeof(struct payer), 1, f) == 1) {
        if (strcmp(p.uid, uno) == 0) {
            printf("Account Found!\n");
            printf("Name: %s\n", p.name);
            printf("Father's Name: %s\n", p.fname);
            printf("Mother's Name: %s\n", p.mname);
            printf("Aadhar Card No: %s\n", p.uid);
            printf("Mobile No: %s\n", p.phno);
            printf("Date pf Birth: %s\n", p.dob);
            printf("Balance: %.2f\n", p.bal);
            fclose(f);
            return;
        }
    }

    printf("Record not found.\n");

    fclose(f);
}

void edit_record() {
    char uno[50];
    struct payer p;
    int password;
    int found = 0;

    printf("Enter AADHAR No to search: ");
    scanf("%s", uno);

    printf("Enter password : ");
    scanf("%d",&password);

    FILE *f = fopen("bankac.txt", "r+b");
    if (f == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&p, sizeof(struct payer), 1, f) == 1) {
        if ((strcmp(p.uid, uno) == 0)) {
            printf("Enter new password: ");
            scanf("%d", &p.pass);

            fseek(f, -sizeof(struct payer), SEEK_CUR);
            fwrite(&p, sizeof(struct payer), 1, f);
            found = 1;
        break;
    }
}

fclose(f);

if (found)
    printf("Record updated successfully.\n");
else
    printf("Record not found.\n");
}


void delete_record() {
char name[50];
struct payer p;
int found = 0;
char temp;

printf("Enter Account Name to delete: ");
scanf("%d",&temp);
scanf("%[^\n]%*c", name);

FILE *f1 = fopen("bankac.txt", "rb");
if (f1 == NULL) {
    printf("Error opening file.\n");
    return;
}

FILE *fp = fopen("stat.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

FILE *f2 = fopen("temppr.txt", "wb");
if (f2 == NULL) {
    printf("Error creating temporary file.\n");
    fclose(f1);
    return;
}

FILE *f2p = fopen("tempor.txt", "wb");
if (f2p == NULL) {
    printf("Error creating temporary file.\n");
    fclose(f1);
    return;
}

while (fread(&p, sizeof(struct payer), 1, f1) == 1) {
    if (strcmp(p.name, name) != 0) {
        fwrite(&p, sizeof(struct payer), 1, f2);
    } else {
        found = 1;
    }
}

fclose(f1);
fclose(f2);

if (!found) {
    printf("Record not found.\n");
    remove("temppr.txt");
    return;
} 

remove("bankac.txt");
rename("temppr.txt", "bankac.txt");


while (fread(&p, sizeof(struct payer), 1, fp) == 1) {
    if (strcmp(p.name, name) != 0) {
        fwrite(&p, sizeof(struct payer), 1, f2p);
    } else {
        found = 1;
    }
}

fclose(fp);
fclose(f2p);

if (!found) {
    printf("Record not found.\n");
    remove("tempor.txt");
    return;
} 

remove("stat.txt");
rename("tempor.txt", "stat.txt");

printf("Record deleted successfully.\n");
}


void edit_bal() {
    char uno[50];
    struct payer p;
    int password;
    int found = 0;
    int ch=0;
    float dep;
    float wdraw;
    char temp;

    printf("Enter AADHAR No to search: ");
    scanf("%s", uno);

    printf("Enter password : ");
    scanf("%d",&password);

    FILE *f = fopen("bankac.txt", "r+b");
    if (f == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE *fp = fopen("stat.txt", "r+b");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&p, sizeof(struct payer), 1, f) == 1) {
        if (strcmp(p.uid, uno) == 0) {

            printf("1. Deposit\n");
            printf("2. Withdraw\n");
            printf("Enter your Choice : ");
            scanf("%d",&ch);

            switch(ch) {
                case 1:
                printf("Enter Amount to Deposit (in Rs.) : ");
                scanf("%f",&dep);
                p.bal=p.bal+dep;
                p.ac=dep;
                printf("PRESS CR for confirmation : ");
                scanf("%d",&temp);
                scanf("%[^\n]%*c", p.tr);

                break;

                case 2:
                printf("Enter Amount to Withdraw(in Rs.) : ");
                scanf("%f",&wdraw);
                p.bal=p.bal-wdraw;
                p.ac=wdraw;
                printf("PRESS DB for confirmation : ");
                scanf("%d",&temp);
                scanf("%[^\n]%*c", p.tr);

                break;
            
            }

            fseek(f, -sizeof(struct payer), SEEK_CUR);
            fwrite(&p, sizeof(struct payer), 1, f);

            fseek(fp, -sizeof(struct payer), SEEK_CUR);
            fwrite(&p, sizeof(struct payer), 1, fp);

            found = 1;
        break;
    }
}

fclose(f);
fclose(fp);

if (found)
    printf("Record updated successfully.\n");
else
    printf("Record not found.\n");

}

void view_stat(){
    char uno[15];
    struct payer p;

    printf("-------------------------\n");
    printf("Enter AADHAR No. : ");
    scanf("%s", uno);
    printf("-------------------------\n");
    printf("Showing Last Transaction.......\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");


    FILE *f = fopen("stat.txt", "rb");
    if (f == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("%-20s %-20s %-20s %-30s %-20s\n","Account No", "Name", "Transactions", "Status", "Available Balance");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    while (fread(&p, sizeof(struct payer), 1, f) == 1) {
        if (strcmp(p.uid, uno) == 0){
        printf("%-20d %-20s %-20.2f %-30s %-20.2f\n", p.acno, p.name, p.ac, p.tr, p.bal);
        }
    }
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    fclose(f);
    
}




void admin_panel(){
    int a_choice;
    printf("-------ADMIN PANEL-------\n");
    printf("1. Display all accounts\n");
    printf("2. Delete an account\n");
    printf("3. Back\n");
    printf("-------------------------\n");

    printf("Enter your choice : ");
    scanf("%d",&a_choice);
    printf("-------------------------\n");

    switch (a_choice){
        case 1:
        list_records();
        break;

        case 2:
        delete_record();
        break;

        case 3:
        main();
        break;

        default:
        printf("Invalid choice!\n");
    }
return;

}

void user_panel(){
    int u_choice;
    printf("--------USER PANEL-------\n");
    printf("1. Account Status\n");
    printf("2. New Account\n");
    printf("3. Change Password\n");
    printf("4. Payee Management\n");
    printf("5. View Statements\n");
    printf("6. Back\n");

    printf("-------------------------\n");
    printf("Enter your choice : ");
    scanf("%d",&u_choice);
    printf("-------------------------\n");

    switch (u_choice)
    {
    case 1:
        search_record();
        break;

    case 2:
        add_record();
        break;

    case 3:
        edit_record();
        break;
    
    case 4:
        edit_bal();
        break;

    case 5:
        view_stat();
        break;
    
    case 6:
        main();
        break;
    
    default:
        printf("Invalid Choice!\n");
    }
}

int main() {
int choice;
int sel;

while (1) {
    printf("-----------MENU----------\n");
    printf("1. Admin Panel\n");
    printf("2. User Panel\n");
    printf("3. Exit\n");
    printf("-------------------------\n");

    printf("Enter your choice : ");
    scanf("%d",&sel);
    printf("-------------------------\n");

    switch (sel){
        case 1:
        admin_panel();
        break;

        case 2:
        user_panel();
        break;

        case 3:
        printf("Thanks for running the program!\n");
        exit(0);

        default:
        printf("Invalid choice!\n");
    }

}

return 0;
}
