#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

 struct med{
	char term[100];
	char definition[100];
}med;
void AddRecord(){
	FILE *fp;
	int n,i;
	int serial_number = 1;
	//input the number of records that you want to record
	printf("Enter no of Records that you want to Record:"); 
	scanf("%d",&n);
	for(i=0;i<n;i++){
    fp = fopen("dictionary.txt", "a"); //open the dictionary.txt file
    printf("enter new term:\n"); //input the new term that you want to add to record
	scanf("%s", med.term);
    fflush(stdin);
    printf("Enter The Definition:\n");  //input the definition for the above given term
	scanf("%s", med.definition);
    fflush(stdin);

    fprintf(fp,"%d.%s : %s\n", serial_number,med.term, med.definition);
    serial_number++;
    printf("Record Added To File Successfully!\n");
    fclose(fp);
}
}


typedef struct {
	int serial_number;
    char term[100];
    char definition[200];
} Medical;

void DisplayTerms() {
	FILE *fp;
    Medical med[100];
    int n = 0;

    fp = fopen("dictionary.txt", "r");

    if (fp == NULL) {
        printf("File does not Exist\n");
        return;
    }

    while (fscanf(fp, "%*d.%[^:]: %[^\n]", med[n].term, med[n].definition) == 2) {
        n++;
    }

    fclose(fp);
	int i, j;
    Medical temp;

    for (i = 0; i < n-1; i++) {
        for (j = i+1; j < n; j++) {
            if (strcmp(med[i].term, med[j].term) > 0) {
                temp = med[i];
                med[i] = med[j];
                med[j] = temp;
            }
        }
    }
     printf("Medical Terms in Alphabetical Order:\n");  // print the terms in alphabetical order
     for(i = 0; i < n; i++) {
        printf("%d. %s : %s\n", i+1, med[i].term, med[i].definition);
    }
}
void Update(){
	FILE *fp, *temp ;
    Medical med;
    int serial_number, found = 0;
	// enter the serial number of term that you want to want to update its definition
    printf("Enter the serial number of the term whose definition you want to update: ");
    scanf("%d", &serial_number);

    fp = fopen("dictionary.txt", "r");
    if (fp == NULL) {
        printf("File does not Exist\n");
        return;
    }

    temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Failed to create temporary file\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%d.%[^:]: %[^\n]\n", &med.serial_number, med.term, med.definition) != EOF) {
        if (serial_number == med.serial_number) {
            printf("Enter the new definition for the term '%s': ", med.term); // input new definition for that term
            scanf("%s", med.definition);
            found = 1;
            fprintf(temp, "%d.%s: %s\n", med.serial_number, med.term, med.definition);
            printf("Record updated successfully!\n");
        } 
		else {
            fprintf(temp, "%d.%s: %s\n", med.serial_number, med.term, med.definition);
        }
    }

    if (!found) {
        printf("No record found with the given serial number.\n");
    }

    fclose(fp);
    fclose(temp);


    remove("dictionary.txt");
    rename("temp.txt", "dictionary.txt");
}

void SearchTerm(){
	FILE *fp;
    Medical med;
    char search_term[100];
    int found = 0;

    printf("Enter the name of the term you want to search: ");
    scanf("%s", search_term);

    fp = fopen("dictionary.txt", "r");

    if (fp == NULL) {
        printf("File does not exist.\n");
        return;
    }

    while (fscanf(fp, "%d.%s : %s\n", &med.serial_number, med.term, med.definition) != EOF) {
        if (strcmp(med.term,search_term) == 0) {
            printf("Term Found:\n");
            printf("%d.%s : %s\n", med.serial_number, med.term, med.definition);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No record found with the given term name.\n");
    }

    fclose(fp);
}


void Delete(){
	FILE *fp;
    Medical med[100];
    int n = 0, i, j, delete_index;

    fp = fopen("dictionary.txt", "r");

    if (fp == NULL) {
        printf("File does not Exist\n");
        return;
    }

    while (fscanf(fp, "%d.%[^:]	: %[^\n]", &med[n].serial_number, med[n].term, med[n].definition) == 3) {
        n++;
    }

    fclose(fp);

    printf("Enter the serial number of the record to delete: "); // input the serial number of the term that you want to delete
    scanf("%d", &delete_index);

    if (delete_index < 1 || delete_index > n) {
        printf("Invalid serial number\n");
        return;
    }

    delete_index--;

    for (i = delete_index; i < n-1; i++) {
        med[i] = med[i+1];
    }

    n--;

    fp = fopen("dictionary.txt", "w");

    for (i = 0; i < n; i++) {
        fprintf(fp,"%d.%s : %s\n", med[i].serial_number, med[i].term, med[i].definition);
    }

    fclose(fp);
    printf("Record deleted successfully!\n");
}

int main(){
	int ch;
	int id,pass;
	//User_ID = "1234"
	//Password = "2005"
	printf("Enter the user id:\n"); // input the given user id
	scanf("%d",&id);
	printf("Enter the Password:\n"); // input the given password
	scanf("%d",&pass);

	
	if(id==1234 && pass==2005)
	{
		printf("\t\t\t\tWelcome to our Medical Terminology Dictionary Management\n");
		printf("\t\t\t\t========================================================\n");
	do{
		
		printf("\n1.Add Record to the file");
		printf("\n2.Display All The Term In Alphabetical Order");
		printf("\n3.Update The Definition");
		printf("\n4.Search The Term By Its Name");
		printf("\n5.Delete The Record");
		printf("\n6.Exit");
		printf("\nEnter Your Choice : ");
		scanf("%d",&ch);
		
		switch(ch){
			case 1:
				AddRecord();
			break;
			case 2:
				DisplayTerms();
			break;
			case 3:
				Update();
			break;
			case 4:
				SearchTerm();
			break;
			case 5:
				Delete();
			break;
			case 6:
				printf("Thank You! Visit Again");
			break;
			default:
				printf("Error: Invalid choice\n");
				printf("Choose Valid Option\n");
			break;

		}
			
	}
	while(ch!=6);
	}
	else{
		printf("Login Credentials are wrong!");
	}
}

