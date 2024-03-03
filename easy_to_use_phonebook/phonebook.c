#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>

struct born{
	int date;
	int mth;
	int year;
};

struct person{
    char name[15];
    char lastname[15];
    char address[30];
    char mble_no[14];
    char sex[8];
    char mail[35];
    struct born dob;
};

void menu();
void got();
void start();
void back();
void addrecord();
void listrecord();
void modifyrecord();
void deleterecord();
void searchrecord();
void ext();

/*for loading screen*/
#define BAR_SIZE 40
void print_n_chars(int n, int c) {
    while (n-- > 0) putchar(c);
}
void progress_bar(int x) {
    putchar('\r');
    printf("\t\t      ");
    putchar('[');
    print_n_chars(BAR_SIZE*x/60, '|');
    print_n_chars(BAR_SIZE-BAR_SIZE*x/60, ' ');
    putchar(']');
}

void main(){
    system("color 5f");
    start();
    getch();
}
void back(){
    start();
}
void start(){
    int x;
    printf("\n\n\n\t\t\t\t\tLOADING\n\n");
    for(x=0; x<=60; ++x){
        progress_bar(x);
        Sleep(60);
    }
    menu();
}

void menu(){
	int n;
	char charac;
    system("cls");		/*to clear the screen*/
    printf("\n\t\t******************************************");
	printf("\n\t\t*          WELCOME TO PHONEBOOK          *");
	printf("\n\t\t******************************************");
	printf("\n\t\t\t __________MENU__________\n\n");
	printf("\t\t1. Add New \t\t2. List \n\t\t3. Search \t\t4. Modify \n\t\t5. Delete \t\t6. Exit\n\n");
	printf("\t\tEnter the number: ");
	scanf("%d",&n);
	
	/*switch: makes your program go to that place where the work is to be done*/
	switch(n){
		case 1:
			addrecord();
    	break;
		case 2: 
			listrecord();
    	break;
    	case 3: 
			searchrecord();
    	break;
    	case 4: 
    		modifyrecord();
    	break;
    	case 5:
			deleterecord();
    	break;
    	case 6:
    		exit(0);
    	break;
    	default:
    		system("cls");
    	    printf("\n\t\tEnter 1 to 6 only!!!\n\a");
    	    printf("\n\t\tEnter any key...");
        	getch();
			menu();
	}
}

/*to add new record in the file*/
void addrecord(){
	system("cls");
	FILE *f;
	struct person p;
    f=fopen("data.dat","ab+");
    char cha;
    printf("\n\t\t\t__________NEW RECORD__________\n\n");
    do{
    	printf("\n\tEnter the Data Here:");
    	printf("\n\t\tFirst Name: ");
    	got(p.name);
    	printf("\n\t\tLast Name: ");
    	got(p.lastname);
    	printf("\n\t\tSex: ");
    	got(p.sex);
    	printf("\n\t\tDOB (YYYY-MM-DD): "); /*to give input in YYYY-MM-DD format*/
    	scanf("%d-%d-%d",&p.dob.year,&p.dob.mth,&p.dob.date);
    	fflush(stdin);
    	printf("\t\tAddress: ");
    	got(p.address);
		printf("\n\t\tPhone No.: ");
    	got(p.mble_no);
    	printf("\n\t\tE-mail: ");
    	got(p.mail);
		fprintf(f,"%-10s  %-10s  %-6s  %4d-%2d-%2d  %-16s  %-14s  %s\n",p.name,p.lastname,p.sex,p.dob.year,p.dob.mth,p.dob.date,p.address,p.mble_no,p.mail);
		fflush(stdin);
		printf("\n\t\tDo you want to add more records? (Y/y)\n\t\t-> ");
		scanf("%c",&cha);
	}while(cha=='Y' || cha=='y');
    printf("\n\tRecord Saved!");
	fclose(f);
    printf("\n\n\tEnter any key...");
	getch();
    menu();
}

/*to list all the records*/
void listrecord(){
	system("cls");
	printf("\n\t\t\t\t __________LIST OF RECORD__________\n");
    struct person p;
    FILE *f;
	f=fopen("data.dat","rb");
	if(f==NULL){
		printf("\n\tFile opening error in listing!!!\a");
		printf("\n\tEnter any key...");
		getch();
		menu();
	}
	printf("\n\n\tYOUR RECORDS ARE:\n");
	printf("\n\t\tName\t    Last Name\tSex\tDOB\t    Address\t      Mobile No.      E-mail");
	while(fscanf(f,"%s %s %s %d-%d-%d %s %s %s",p.name,p.lastname,p.sex,&p.dob.year,&p.dob.mth,&p.dob.date,p.address,p.mble_no,p.mail)!=EOF)
        printf("\n\t\t%-10s  %-10s  %-6s  %4d-%2d-%2d  %-16s  %-14s  %s",p.name,p.lastname,p.sex,p.dob.year,p.dob.mth,p.dob.date,p.address,p.mble_no,p.mail);
	fclose(f);
	printf("\n\n\tEnter any key...");
	getch();
	menu(); 
}

/*to search record by name or DOB*/
void searchrecord(){
	system("cls");
    struct person p;
    int item;
	FILE *f;
	char name[100];
	int flag=0;
	f=fopen("data.dat","rb");
	if(f==NULL){
    	printf("\n\tError in opening!!!\a");
    	printf("\n\tEnter any key...");
		getch();
		menu();
	}
	printf("\n\tEnter the item you want to search from:");
	printf("\n\t\t1. Name \n\t\t2. DOB \n\t\t-> ");
	scanf("%d",&item);
	
	/*to search from name*/
	if(item==1){	
		printf("\n\tEnter name of person to search: ");
		got(name);
		printf("\n\n\tDetail Information About %s:",name);
        printf("\n\t\tName\t    Last Name\tSex\tDOB\t    Address\t      Mobile No.      E-mail");
		while(fscanf(f,"%s %s %s %d-%d-%d %s %s %s",p.name,p.lastname,p.sex,&p.dob.year,&p.dob.mth,&p.dob.date,p.address,p.mble_no,p.mail)!=EOF){
    		if(strcmp(p.name,name)==0){
        		printf("\n\t\t%-10s  %-10s  %-6s  %4d-%2d-%2d  %-16s  %-14s  %s",p.name,p.lastname,p.sex,p.dob.year,p.dob.mth,p.dob.date,p.address,p.mble_no,p.mail);
    			flag=1;
    			continue;
			}
		}
		if(flag==0)
			printf("\n\n\tFile not found!!!\a");
		fclose(f);
	}
	
	/*to search from DOB*/
	else if(item==2){
		int newyr,newmth,newdate;
		printf("\n\tEnter DOB(YYYY-MM-DD) of person to search: ");
		scanf("%d-%d-%d",&newyr,&newmth,&newdate);
		printf("\n\tDetail Information:");
		printf("\n\t\tName\t    Last Name\tSex\tDOB\t    Address\t      Mobile No.      E-mail");
		while(fscanf(f,"%s %s %s %d-%d-%d %s %s %s",p.name,p.lastname,p.sex,&p.dob.year,&p.dob.mth,&p.dob.date,p.address,p.mble_no,p.mail)!=EOF){
    		if(p.dob.year==newyr && p.dob.mth==newmth && p.dob.date==newdate){
        		printf("\n\t\t%-10s  %-10s  %-6s  %4d-%2d-%2d  %-16s  %-14s  %s",p.name,p.lastname,p.sex,p.dob.year,p.dob.mth,p.dob.date,p.address,p.mble_no,p.mail);
				flag=1;
				continue;
			}
		}
		if(flag==0)
			printf("\n\n\tFile not found!!!\a");
		fclose(f);
	}
	
	/* if user enters incorrect number*/
	else{
		printf("\n\tEnter 1 or 2 only!!!\a");
		printf("\n\tEnter any key...");
		getch();
		fclose(f);
		searchrecord();		/*takes you to start of search menu*/
	}
	printf("\n\tEnter any key...");
	getch();
    system("cls");
	menu();
}

/*to delete record*/
void deleterecord(){
	system("cls");
    struct person p;
    FILE *f,*ft;
	int flag=0,yrs,mths,dates;
	char newname[15],lname[15];
	f=fopen("data.dat","rb");
	if(f==NULL){
		printf("\n\n\tCONTACT'S DATA NOT ADDED YET!!!\a");
		printf("\n\tEnter any key...");
		getch();
		menu();
	}
	else{
		ft=fopen("temp.dat","wb+");
		if(ft==NULL)
			printf("\n\n\tFile opening error!!!\a");
		else{
			printf("\n\t\t\t __________DELETE__________\n\n");
			printf("\n\tEnter contact's first name: ");
			scanf("%s",newname);
			printf("\tEnter contact's last name: ");
			scanf("%s",lname);
			printf("\tEnter contact's DOB name: ");
			scanf("%d-%d-%d",&yrs,&mths,&dates);
			while(fscanf(f,"%s %s %s %d-%d-%d %s %s %s",p.name,p.lastname,p.sex,&p.dob.year,&p.dob.mth,&p.dob.date,p.address,p.mble_no,p.mail)!=EOF){
				if(strcmp(newname,p.name)==0 && strcmp(lname,p.lastname)==0 && p.dob.year==yrs && p.dob.mth==mths && p.dob.date==dates)
					flag=1;
				else
                	fprintf(ft,"%-10s  %-10s  %-6s  %4d-%2d-%2d  %-16s  %-14s  %s\n",p.name,p.lastname,p.sex,p.dob.year,p.dob.mth,p.dob.date,p.address,p.mble_no,p.mail);
			}
			fclose(f);
			fclose(ft);
			if(flag==1){
				ft=fopen("temp.dat","rb");
        		f=fopen("data.dat","wb");
        		while(fscanf(ft,"%s %s %s %d-%d-%d %s %s %s",p.name,p.lastname,p.sex,&p.dob.year,&p.dob.mth,&p.dob.date,p.address,p.mble_no,p.mail)!=EOF)
        			fprintf(f,"%-10s  %-10s  %-6s  %4d-%2d-%2d  %-16s  %-14s  %s\n",p.name,p.lastname,p.sex,p.dob.year,p.dob.mth,p.dob.date,p.address,p.mble_no,p.mail);
        		fclose(f);
        		fclose(ft);
				printf("\n\tRecord has been DELETED...");
			}
			else
				printf("\n\tNO RECORD FOUND WITH THE GIVEN DETAILS!!!\a");
		}
	}
	printf("\n\tEnter any key...");
	getch();
	menu();
}

//out of order
void modifyrecord(){
    FILE *f, *ft;
    struct person p;
	int flag=0,yrs,mths,dates;
	char newname[15],lname[15];
	f=fopen("data.dat","rb");
	ft=fopen("temp.dat","wb");
	if(f==NULL){
		printf("\n\tCONTACT'S DATA NOT ADDED YET!!!\a");
		printf("\n\tEnter any key...");
		getch();
		menu();
	}
	if(ft==NULL){
		printf("\n\tCONTACT'S DATA NOT ADDED YET!!!\a");
		menu();
	}
	else{
	    system("cls");
	    printf("\n\t\t\t __________MODIFICATION__________\n\n");
		printf("\tEnter contact's first name: ");
		scanf("%s",newname);
		printf("\tEnter contact's last name: ");
		scanf("%s",lname);
		printf("\tEnter contact's DOB name: ");
		scanf("%d-%d-%d",&yrs,&mths,&dates);
        while(fscanf(f,"%s %s %s %d-%d-%d %s %s %s",p.name,p.lastname,p.sex,&p.dob.year,&p.dob.mth,&p.dob.date,p.address,p.mble_no,p.mail)!=EOF){
            if(strcmp(newname,p.name)==0 && strcmp(lname,p.lastname)==0){
				flag=1;
            	printf("\n\tEnter Name: ");
                got(p.name);
                printf("\n\tEnter Last Name: ");
                got(p.lastname);
                printf("\n\tEnter Sex: ");
                got(p.sex);
    			printf("\n\tEnter DOB: ");
    			scanf("%d-%d-%d",&p.dob.year,&p.dob.mth,&p.dob.date);
    			fflush(stdin);
                printf("\tEnter Address: ");
                got(p.address);
				printf("\n\tEnter Phone No: ");
                got(p.mble_no);
                printf("\n\tEnter E-mail: ");
                got(p.mail);  
            }
            fprintf(ft,"%-10s  %-10s  %-6s  %4d-%2d-%2d  %-16s  %-14s  %s\n",p.name,p.lastname,p.sex,p.dob.year,p.dob.mth,p.dob.date,p.address,p.mble_no,p.mail);
        }
        fclose(ft);
        fclose(f);
        if(flag==1){
        	ft=fopen("temp.dat","rb");
        	f=fopen("data.dat","wb");
        	while(fscanf(ft,"%s %s %s %d-%d-%d %s %s %s",p.name,p.lastname,p.sex,&p.dob.year,&p.dob.mth,&p.dob.date,p.address,p.mble_no,p.mail)!=EOF){
        		fprintf(f,"%-10s  %-10s  %-6s  %4d-%2d-%2d  %-16s  %-14s  %s\n",p.name,p.lastname,p.sex,p.dob.year,p.dob.mth,p.dob.date,p.address,p.mble_no,p.mail);
        	}
			fclose(f);
        	fclose(ft);
			printf("\n\tYour data has been modified...");
		}
        else
            printf("\n\tData is not found!!!\a");
    	printf("\n\n\tEnter any key...");
    	getch();
		menu();
	}
}

/*this is for exit!!!
void ext(){
	char cha;
	printf("\n\t\tAre You Sure?(Y/N)\n\t\t-> ");
	scanf("%s",cha);
    while (cha=='y' || cha=='Y')
		exit(0); 
	menu();
}*/

/*for input of datama such as name, sex, mail etc*/				
void got(char *name){
	int i=0,j;
    char c,ch;
    do{
    	c=getch();
        if(c!=8 && c!=13){
            *(name+i)=c;
            putch(c);
            i++;
        }
        if(c==8){
            if(i>0)
                i--;
            system("cls");
            for(j=0;j<i;j++){
                ch=*(name+j);
                putch(ch);
            }
        }
    }while(c!=13);
    *(name+i)='\0';
}
