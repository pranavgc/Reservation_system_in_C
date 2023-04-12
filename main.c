#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

#ifndef _STRUCT_H
#include "st.h"
#endif
// ASCII of ENTER 13
// ASCII of TAB 9
// ASCII of BKSPC 8
/*struct user
{
	char name[50];
	char email[50];
	char userid[50];
	char password[16];

};

struct flights {
	char origin[50];
	char dest[50];
	int day;
	char number[15];
	int seats;
	float distance;
};*/

struct pass_data p[4];

void logo()
{
	
	
	printf("\t\t\t\t\t=================================================\n");
	printf("\t\t\t\t\t|                                               |\n");
	printf("\t\t\t\t\t|        -----------------------------          |\n");
	printf("\t\t\t\t\t|             AAO BOOK KAREIN                   |\n");
	printf("\t\t\t\t\t|        -----------------------------          |\n");
	printf("\t\t\t\t\t|                                               |\n");
	printf("\t\t\t\t\t|                                               |\n");
	printf("\t\t\t\t\t|                                               |\n");
	printf("\t\t\t\t\t|              BROUGHT TO YOU BY                |\n");
	printf("\t\t\t\t\t|           |  daud&company.org  |              |\n");
	printf("\t\t\t\t\t|                                               |\n");
	printf("\t\t\t\t\t=================================================\n\n");
	
printf("\t\t\t\t\t=================================================");	
printf("\t\t\t\t\t\t\t\t\t\t\t\tFly higher than SENSEX\n");
printf("\t\t\t\t\t=================================================\n");

printf("------------------------------------------------------------------------------------------------------------------------\n");
		
}
void p_input(char p_ch[50]) {
	fgets(p_ch, 50, stdin);
	p_ch[strlen(p_ch) - 1] = 0;
}

/*int pint_input(int f_ch) {
	scanf("%d", &f_ch);
	fgetc(stdin);
}

float pfloat_input(int ff_ch) {
	scanf("%f", &ff_ch);
	fgetc(stdin);
}*/



void p_pass(char a[16]) {
	char c;
	int i;
	fflush(stdin);
	for (i = 0; i < 16; i++)//loop for password
	{

		fflush(stdin);
		c = _getch();
		a[i] = c;
		if (a[i] == '\b')// For backspace
		{
			printf("\b \b");  //
			i -= 2;
			continue;
		}
		if (a[i] == ' ' || a[i] == '\r') //for space 
			printf(" ");
		else
			printf("*");// replace with *
		if (a[i] == '\r')//For Enter
			break;
	}
	a[i] = '\0'; //replace last enter
}

int checkpass(char *pw){//password check
	int w,c=0,d=0,e=0;
	if (strlen(pw)>16){
			printf("\n---------------------------------------------------------------------------------------------------\n");
			printf("\n\t\t\t\tGive a 16 or less character password only.!!\n");
			printf("\n---------------------------------------------------------------------------------------------------");
			Beep(900,300);
		return 0;}
	else{
		for (w=0;w<strlen(pw);w++){// special character check
			if(!isalnum(pw[w])){
				c=c+1;
			}
			if(isalpha(pw[w])){// alphabet check
				d=d+1;
			}
			if(isdigit(pw[w])){// digit check
				e=e+1;
			}
		}
	if(c==0||d==0||e==0){
		printf("\n---------------------------------------------------------------------------------------------------\n");
			printf("\nGive a 16 or less character password. A password should contain a special character, a number and an alphabet!!\n");
		printf("\n---------------------------------------------------------------------------------------------------");
			Beep(900,300);
		return 0;}
		}
	}
	
	

int check_email(char *em){
	int e,c=0,fe;
	for(e=0;e<strlen(em)-3;e++){
		//printf("%c\n",em[e]);
		
		if(em[e]==64){ 
		for(fe=e;fe<strlen(em)-2;fe++){
			if(em[fe]==46){
				return 0;
			}
			
		}}
		           // 64 is ASCII value of @
		}
		
		printf("\n---------------------------------------------------------------------------------------------------\n");
			printf("\n\t\t\t\t Give a valid email address!!\n");
		printf("\n---------------------------------------------------------------------------------------------------");
			Beep(900,300);
			return 1;
}

int check_upi(char *up){
	int u;
	for(u=0;u<strlen(up);u++){
		//printf("%c\n",up[u]);
		
		if(up[u]==64){             // 64 is ASCII value of @
			return 0;
		}}
		
		printf("\n--------------------------------------------------------------------------------------------------------------\n");
			printf("\n\t\t\t\t Give a valid UPI ID!!\n");
		printf("\n-------------------------------------------------------------------------------------------------------------");
			Beep(900,300);
			return 1;
}


int deleteflight(char *del_f, char *del_flight) {

	FILE *del_file;
	FILE *del_newfile;
	int found=0;
	struct flights record;

	del_file=fopen(del_f, "r");
	if (!del_file) {
		printf("Unable to open file %s", del_f); //checking file is present
		return -1;
	}
	del_newfile=fopen("tmp_flights.txt", "w"); //creating teemp file
	if (!del_newfile) {
		printf("Unable to open new temp file."); 
		return -1;
	}
	
	while (fread(&record,sizeof(struct flights),1,del_file)) {            //find and delete file
		if (!strcmp (del_flight, record.number)) {
			printf("\nA Flight %s is signing off.\n",record.number); 
			found=1;
		} else {
			fwrite(&record, sizeof(struct flights), 1, del_newfile);
		}
	}
	if (!found) {
		printf("\nNo flights found with the requested ID: %s\n\n", del_flight); 
	}

	fclose(del_file);
	fclose(del_newfile);

	remove(del_f);// remove orginal
	rename("tmp_flights.txt", del_f); //rename

	return 0;
}



int displayflights(char *rfile) {
	FILE *read_fp;
	struct flights record;

	read_fp=fopen(rfile,"r");  //display all files
	if (!read_fp) {
		printf("Unable to open file!");
		return -1;
	}

	printf("The following flights are registered in the file %s:\n\n", rfile);
	printf(" %-10s | %-25s | %-25s | %-5s | %-5s \n", "Flight-ID", "Origin", "Destination", "Day", "Distance");
	while (fread(&record,sizeof(struct flights),1,read_fp)) {
	printf("---------------------------------------------------------------------------------------------------\n");
	printf(" %-10s | %-25s | %-25s | %-5d | %-5f \n", record.number, record.origin, record.dest,record.day, record.distance );
	}
	fclose(read_fp);
	return 0;
}


int addflight(char *add_f){  //add flights
		FILE *fl_file;
		struct flights admin_flight;
	printf("\n Enter Flight's origin:\t");
	p_input(admin_flight.origin);
	printf("\n Enter Flight's destination:\t");
	p_input(admin_flight.dest);
	printf("\n Enter Flight number:\t");
	p_input(admin_flight.number);
	printf("\n Enter number of available seats:\t");
	scanf("%d",&admin_flight.seats);
	printf("\n Enter day when Flight is operational:\t");
	scanf("%d",&admin_flight.day);
	printf("\n Enter the distance covered by the flight:\t");
	scanf("%f",&admin_flight.distance);

	fl_file = fopen(add_f, "a+");
	fwrite(&admin_flight, sizeof(struct flights), 1, fl_file);
	if (fwrite != 0) {
		printf("\n\t\t\t\t\t Welcome Flight %s :)", &admin_flight.number);
		printf("\n\t\t\t Flight %s takes off from %s to destination %s.", admin_flight.number, admin_flight.origin, admin_flight.dest);
		printf("\n \t\tDistance is %f, Day is %d, Seats is %d", admin_flight.distance, admin_flight.day, admin_flight.seats);
		printf("\n\t\t\t\t\tHappy journey!!");
		fclose(fl_file);
		}


	fclose(fl_file);
	return 0;
}




void information_ticket(char *f, int s_n,int s) // To print the collected information from passenger in the text file generated
{
	FILE *fp;
	fp = fopen(f,"a");
	fprintf(fp,"\n");
	fprintf(fp, "\n%s %d","Number of Passengers:",s_n);
	fprintf(fp,"\n");
	//int l;
	/*for(l=0;l<s_n;l++)
	{
		fprintf(fp, "%s\t\t%d\t\t%s",p[l].pass_fn, p[l].pass_ln,p[l].pass_age,p[l].pass_sex, p[l].pass_fare);
		fprintf(fp,"\n");  
		
		
	}*/

	fprintf(fp, "\n%s %d","Available seats after booking:", s-s_n);
	fclose(fp);
	
	
}


int weekday(int d, int m, int y)
{
	int n= ( d+= m < 3 ? y-- : y - 2 ,  23*m/9 + d + 4 + y/4 - y/100 + y/400) % 7 ;
	return n;
}


int pnr()
{	int n;
	srand(time(NULL));
	n=rand();
	n=n*239;
	return n;
	
}

void clrscr()
{
	system("cls");
}

//void booking(float payable_amount,int m, float tot_fare, char fn[50], int d, int mon)
void booking(float payable_amount,char o_final[50], char d_final[50], char n_final[50], int d, int mon,int m, char *f, int s)
{
	
    // Payment potal starts
    int i,PNR;
    char    text_1[100] = "Welcome to the Payment Portal";
    char    text_2[100] = "Mode of payment";
    char    text_3[100] = " '0'for card payment and'1'for UPI payment: ";
    int     option,up_mail=0;

	struct pay_details pass_details; // Details to be collected from payer
    
    char card_text_1[100] = "Enter CARD number :";
    char card_text_2[100] = "Enter CARD cvv :";
    char card_text_3[100] = "Enter CARD expiry date :";
    char card_text_4[100] = "Enter CARD expiry month :";

    char UPI_text_1[100] = "Enter UPI Id :";
    char UPI_text_2[100] = "Enter UPI pin :";
	
	PNR=pnr();
	
	payment_portal:
	printf("===============================================================================================================\n");
    printf("\n \t\t\t\t%s ", text_1);
    printf("\n\n===============================================================================================================\n");
    
	
	
	printf("\n\n\t\t\t\t%s\n\n\t\t\t%s", text_2, text_3);
	scanf("%d", &option);

    // Switch choice for card or UPI portal
    switch (option) {
    // Enter details for card
    case 0:
		
        sscanf("Card", "%s", pass_details.pay_type);
        printf("\n\t\t\t\t%s\t",card_text_1);			
        scanf("%lu",&pass_details.card_pay.card_no);	//Ask for Card Number
        printf("\n\t\t\t\t%s\t",card_text_2);
        scanf("%d",&pass_details.card_pay.cvv);			//Ask for CVV
        printf("\n\t\t\t\t%s\t",card_text_3);
        scanf("%d",&pass_details.card_pay.exp_date);	//Ask for expiry date
        printf("\n\t\t\t\t%s\t",card_text_4);
        scanf("%d",&pass_details.card_pay.exp_mon);		//Ask for expiry month
		printf("\n\n\t\t Rs %.2f has been paid through %s . Thank you. Enjoy a safe journey.", payable_amount, pass_details.pay_type);
		sleep(4); 	
		system("cls");
		printf("\n\n\n\t\t\t Please collect your ticket\n\n");
		printf(" %-10s | %-25s | %-25s | %-5s | %-5s \n", "Flight-ID", "Origin", "Destination", "Date", "Month");
		printf("---------------------------------------------------------------------------------------------------\n");
		printf(" %-10s | %-25s | %-25s | %-5d | %-5d \n", n_final, o_final, d_final,d, mon );
		printf("\nPNR= %d\n",PNR);
		printf("%-25s | %-24s | %-6s | %-2s | %-7s\n", "First name","Last name","Gender","Age","Fare(in Rs)");
	printf("---------------------------------------------------------------------------------------------------\n");
	for( i=0;i<m;i++)
	{
		printf("%-25s",p[i].pass_fn);
		printf("| %-25s ",p[i].pass_ln);
		printf("| %-7s",p[i].pass_sex);
		printf("| %-3d",p[i].pass_age);
		printf("| %-7.2f",p[i].pass_fare);
		printf("\n");
	}
	printf("\n\n\n");
	//printf("Total Fare: %.2f", tot_fare);
	information_ticket(f,m,s);
	//printtf("\n\n\n\t\t\t\t\t\t\tPress any key to book another ticket........");
	//getch();
	//sleep(4);
		break;
    
    case 1:
	// Enter details for UPI
	upi_id:
		sscanf("UPI", "%s", pass_details.pay_type);
        printf("\n\t\t\t\t%s\t",UPI_text_1);
        scanf("%s", pass_details.UPI_pay.UPI_id);         //Ask for UPI ID
        up_mail=check_upi(pass_details.UPI_pay.UPI_id);
	if(up_mail){
		goto upi_id;
		
	}
				

        printf("\n\t\t\t\t%s\t",UPI_text_2);
        scanf("%d", &pass_details.UPI_pay.UPI_pin);		//Ask for UPI Password
		printf("\n\n\t\t Rs %.2f has been paid through %s . Thank you. Enjoy a safe journey.", payable_amount, pass_details.pay_type);
		sleep(4); 	
		system("cls");
		printf("\n\n\n\t\t\t Please collect your ticket\n\n");
		printf(" %-10s | %-25s | %-25s | %-5s | %-5s \n", "Flight-ID", "Origin", "Destination", "Date", "Month");
		printf("---------------------------------------------------------------------------------------------------\n");
		printf(" %-10s | %-25s | %-25s | %-5d | %-5d \n", n_final, o_final, d_final,d, mon );
		printf("\n\nPNR= %d\n",PNR);
		printf("%-25s | %-24s | %-6s | %-2s | %-7s\n", "First name","Last name","Gender","Age","Fare(in Rs)");
	printf("---------------------------------------------------------------------------------------------------\n");
	for( i=0;i<m;i++)
	{
		printf("%-25s",p[i].pass_fn);
		printf("| %-25s ",p[i].pass_ln);
		printf("| %-7s",p[i].pass_sex);
		printf("| %-3d",p[i].pass_age);
		printf("| %-7.2f",p[i].pass_fare);
		printf("\n");
	}
	
	printf("\n\n\n");
	//printf("Total Fare: %.2f", tot_fare);

	information_ticket(f,m,s);	
	//sleep(4);
	//printf("\n\n\n\t\t\t\t\t\t\tPress any key to book another ticket........");
	//getch();				
        break;
    
    default:
	// In case invalid choice is selected
		
        printf("\n\nInvalid choice selected... returning back\n\n");
        goto payment_portal;
        break;
    }; 
	
	// Final statement saying that payment has been recieved
	
}

float p_fare_c(int age, float d_fare, float dist)
{
	float b_fare, b_charges = 100.0, total;
	
	if(age<3)						b_fare = 200;		//Base fare for infant
	else if(age>=3 && age <=5)		b_fare = 600;		//Base fare for child
	else if(age>5 && age <=65)		b_fare = 1000;		//Base fare for adult
	else							b_fare = 500;		// Base for senior citizen

	
	total = b_fare + dist*d_fare + b_charges;	//Total fare without taxes
	total = total + 0.16*total;	                  //Total fare plus 16% taxes
	//printf("in p_fare_c %f",total);	
	//sleep(10);					
	return total;
}




int s_information(char *f) // To calculate the remaining seats after booking
{ 
  FILE *s_fp;

  s_fp = fopen(f, "r");
  int s_n;
  if(s_fp == NULL)
  {
  	s_fp = fopen(f,"a");
  	s_n = 30;
  	fprintf(s_fp,"Seats available %d", s_n);
  	
  	fclose(s_fp);
  	
  }
  else
  {
  	fseek(s_fp,-2,SEEK_END);
  	fscanf(s_fp, "%d", &s_n);
  	//printf("%d",s_n);
  	
  }
  fclose(s_fp);
	return s_n;
	
}	
	


void ticket_disp(int m, float tot_fare, char fn[50], int d, int mon,char o_final[50], char d_final[50], char n_final[50],char g[4]) // To display the ticket in terminal
{	clrscr();
	int k=0,i;
	printf("========================================================================================================================\n");
	printf("\n Check your Flight details and Passengers details\n");
	printf("\n======================================================================================================================\n");
	struct flights f;
	FILE *fs_file;
	fs_file = fopen("flights.txt", "r");
	while (fread(&f, sizeof(struct flights), 1, fs_file)) {
	//printf("%d",i1);
	//i1++;
	if (!strcmp(fn, f.number)) {
		k=1;
			printf("\n Flight details:\n\n");
	printf(" %-10s | %-25s | %-25s | %-5s | %-5s \n", "Flight-ID", "Origin", "Destination", "Date", "Month");
	printf("---------------------------------------------------------------------------------------\n");
	printf(" %-10s | %-25s | %-25s | %-5d | %-5d \n\n", f.number, f.origin, f.dest,d, mon );
	strcpy(d_final,f.dest);
	strcpy(o_final,f.origin);
	strcpy(n_final,f.number);
	//fclose(c_file);
	//return 0;
	

	printf("\n Passenger details:\n\n");
	printf("%-25s | %-24s | %-6s | %-2s | %-7s\n", "First name","Last name","Gender","Age","Fare(in Rs)");
	printf("---------------------------------------------------------------------------------------------------\n");
	for(i=0;i<m;i++)
	{
		printf("%-25s",p[i].pass_fn);
		printf("| %-25s ",p[i].pass_ln);
		printf("| %-7s",p[i].pass_sex);
		printf("| %-3d",p[i].pass_age);
		printf("| %-7.2f",p[i].pass_fare);
		printf("\n");
	}
	printf("\n\n\n");
	printf("Total Fare: %.2f", tot_fare);
	break;
}
	
}
	/*if(!k){
	printf("\n\n\t\t\t\t\t\tIncorrect Flight-ID!!!!!!\n");
	printf("\n\n\t\t\t\t\t\tPress any key to try again!!!!!!\n");
	getch();
	//printf("\n\t\t\t\tur journen\n");
	strcpy(g,"toto");
	//printf("%s",g);
	fclose(fs_file);
	fgetc(stdin);
	
	//goto flight_search;
	}*/
	fclose(fs_file);
	
	
}



void info_collect(char *f, int m, int s, char fn[50], int d, int mon,char o_final[50], char d_final[50], char n_final[50],char g[4], float dist) // To collect the information from passenger
{	printf("\n========================================================================================\n");
	printf("\t\t\tPlease fill the Passenger details");
	printf("\n========================================================================================\n");
	int i;
	float tot_fare=0.0;
	float d_fare = 20.0;
	for(i=0;i<m;i++)
	{
		printf("\n First Name:\t");
		scanf("%s",&p[i].pass_fn);
		printf("\n Last Name:\t");
		scanf("%s",&p[i].pass_ln);
		printf("\n Age:\t");
		scanf("%d", &p[i].pass_age);
		printf("\n Gender(M/F/O):\t");
		scanf("%s",p[i].pass_sex);
		p[i].pass_fare = p_fare_c(p[i].pass_age, d_fare, dist);
		tot_fare = tot_fare + p[i].pass_fare;
		printf("\n\n");
	}
	 
	//information_ticket(f,m,s);
	ticket_disp(m, tot_fare, fn, d, mon,o_final,d_final,n_final,g);
	
}
int total_fare(int n, float dist)
{	
	int i;
	float tot_fare=0.0;
	float d_fare = 20.0;
	for(i=0;i<n;i++)
		{
		p[i].pass_fare = p_fare_c(p[i].pass_age, d_fare, dist);
		tot_fare = tot_fare + p[i].pass_fare;	
		}
	return tot_fare;	
}

int main() {
	int p_opt, i=0, ad_opt,ad_opt2, u_mail=0, ad_mail=0;
	int p_member = 0, Enter2,pp=1,ap=1;
	int found2=0;
	int ad_member = 0;
	FILE *p_file=NULL;
	FILE *ad_file;
	
	FILE *c_file;
	FILE *r_fp;
	
	char cpass[16], adpass[16];
	char p_userid[50];
	char p_pword[50],ad_fid[50],flightid[50];
	int ad_d, ad_m, ad_y;	
	char ad_org[50], ad_dest[50];
	struct user reg_user;
	struct user login_user;
	struct user admin_user;
	struct flights record;
	char useriddummy[50];
	
	Home:
	system("cls");
	logo();
	
	printf(" Select an option:\n");
	printf(" \n1.User Login");
	printf(" \n2.User Register");
	printf(" \n3.Admin");
	printf("\n\n\n Please Enter your choice:\t");
	scanf("%d", &p_opt);
	fgetc(stdin);

	switch (p_opt) {
	case 2:
		system("cls");
		printf("======================================================================================================================\n");
		printf("\n\t\t\t\t\tWelcome to the Registration Portal:\n");
		printf("\n====================================================================================================================\n");
		printf("\n Enter your userid:\t");
		//scanf("%s", &useriddummy);
		//fgetc(stdin);
		p_input(useriddummy);


		c_file = fopen("User.dat", "a+");
		while (fread(&reg_user, sizeof(struct user), 1, c_file)) {
			//printf("%d",i1);
			//i1++;
			if (!strcmp(reg_user.userid, useriddummy)) {
				system("cls");
				printf("\n-----------------------------------------------------------------------------------------------");
				printf("\n\t\t\t\tUserid already taken. You 'came' second ;)");
				printf("\n-----------------------------------------------------------------------------------------------\n\n");
				fclose(c_file);
				sleep(3);
				goto Home;
				return 0;

			}
		}
		fclose(c_file);
		printf("\n Confirm userid:\t");
		p_input(reg_user.userid);
		printf("\n Enter your name:\t");
		p_input(reg_user.name);
		reg_email:
		printf("\n Enter your email:\t");
		p_input(reg_user.email);
		u_mail=check_email(reg_user.email);
		if(u_mail){
		goto reg_email;
		}
		reg_pass:
		printf("\nGive a 16 or less character password. A password should contain a special character, a number and an alphabet.");
		printf("\n Enter your password:\t");
		p_pass(reg_user.password);
		pp=checkpass(reg_user.password);
		if(!pp){
			goto reg_pass;
		}
		printf("\n Confirm your password:\t");
		p_pass(cpass);
		//printf("\n %s",cpass);
		//printf("\n %s", reg_user.password);
		//printf("\n %d", strcmp(reg_user.password, cpass));
		if (!strcmp(reg_user.password, cpass)) {
			//printf("\n Your passwords match.");
			p_file = fopen("User.dat", "a+");
			fwrite(&reg_user, sizeof(struct user), 1, p_file);
			if (fwrite != 0) {
				printf("\t\t\t\t\tRegistration succesfull !!!!!");
				printf("\n-----------------------------------------------------------------------------------------------");
				printf("\n\t\t\tFly with us before Adani takes us :)");
				printf("\n-----------------------------------------------------------------------------------------------");
				printf("\n\nPress any key to take off for Login portal");
				fclose(p_file);
				getch();
				//fgetc(stdin);
				goto Login_home;
				
			}
		}
		else {
			system("cls");
			printf("\n-----------------------------------------------------------------------------------------------");
			printf("\n Oops!!! Your passwords do not match :( Going back to Home.");
			printf("\n-----------------------------------------------------------------------------------------------\n");
			Beep(900, 300);
			fclose(p_file);
			sleep(2);
			//fgetc(stdin);
			goto Home;
		}
		fclose(p_file);
		break;

	case 1:
		Login_home:
		system("cls");
		printf("======================================================================================================================\n");
		printf("\n\t\t\t\t\t\tWelcome to the Login Portal\n");
		printf("\n======================================================================================================================\n");
		printf("\n Enter your User ID:\t");
		p_input(p_userid);
		printf("\n Enter your password:\t");
		p_pass(p_pword);
		p_file = fopen("User.dat", "r");
		while (fread(&login_user, sizeof(login_user), 1, p_file)) {
			//printf("iteration %d", i);
			//i++;
			if (!strcmp(login_user.userid, p_userid)) {
				if (!strcmp(login_user.password, p_pword)) {
					system("cls");
					
					printf("-----------------------------------------------------------------------------------------\n");
					printf("\t\t\t\t\t Welcome %s !!!!\n", login_user.name);
					printf("-----------------------------------------------------------------------------------------\n");
					Beep(300,200);
					Beep(350,200);
					//printf("email %s, password %s, userid %s",login_user.email,login_user.password,login_user.userid);
					sleep(2);
					
					char flight_no[50];
	char date[2];
	char month[2];
	char flight_dummy[50],o_final[50],d_final[50],n_final[50];
	float f_dist;
	int Enter, dd,mm;
	
	int d, m, y, wd, k=0,kf=0;
	
	char g[4];
	char org[50], dest[50];
	
	flight_search:
	//fgetc(stdin);
	clrscr();
	printf("======================================================================================================================\n");
	printf("\n\t\t\t\t\tWelcome to Flight Booking Portal\n");
	printf("\n======================================================================================================================\n\n");
	printf("Write full name for searching city. e.g. For Kolkata write 'Kolkata'.\n");
	printf("\n-----------------------------------------------------------------------------------------------------------------------");
		
		
	printf("\n\n From:\t");
	p_input(org);
	printf("\n To:\t");
	p_input(dest);
	printf("\n Enter date of travel(dd format):\t");
	scanf("%d", &d);
	printf("\n Enter month of travel(mm format):\t");
	scanf("%d", &m);
	printf("\n Enter year of travel(yyyy format):\t");
	scanf("%d", &y);
	printf("\n-----------------------------------------------------------------------------------------------------------------------");
	printf("\n\n");
	wd=weekday(d,m,y);

	struct flights flight;
	
	
	FILE *c_file;
	
	
	printf(" %-10s | %-25s | %-25s | %-5s\n", "Flight-ID", "Origin","Destination","Distance");
	printf("---------------------------------------------------------------------------------------------------\n");
	c_file = fopen("flights.txt", "r");
	while (fread(&flight, sizeof(struct flights), 1, c_file)) {
	//printf("%d",i1);
	//i1++;
	if (flight.day==wd && !strcmp(org,flight.origin) && !strcmp(dest, flight.dest)) {
		k=1;
	
	printf(" %-10s | %-25s | %-25s | %-5.2f\n\n", flight.number, flight.origin, flight.dest, flight.distance);
	//fclose(c_file);
	//return 0;
	}
	
	}
	if(!k){
	printf("\n\n\t\t\t\t\t\tNO FLIGHTS AVAILABLE!!!!!!\n");
	printf("\n\t\t\t\tSorry for the inconvenience, try some other dates for your journey\n\n");
	printf("\n\n\t\t\t\t\t\tPress any key to retry!!!!!!\n");
	getch();
	fclose(c_file);
	fgetc(stdin);
	goto flight_search;
	}
	fclose(c_file);
	
	flight_max_info:
	
	fgetc(stdin);	
	printf("\n Choose the Flight ID\t");
	p_input(flight_no);
	//printf("Origin %s, Dest %s, fno %s",org,dest,flight_no);
	c_file = fopen("flights.txt", "r");
	while (fread(&flight, sizeof(struct flights), 1, c_file)) {
	//printf("%d",i1);
	//i1++;
	if (!strcmp(flight_no,flight.number) && !strcmp(org,flight.origin) && !strcmp(dest, flight.dest)) {
		kf=1;
		//printf("\nif main ghus gaye");
		f_dist=flight.distance;
		fclose(c_file);
		break;
	}
	
	}
	//printf("in main %d",kf);
	fclose(c_file);
	if(!kf){
		printf("\n------------------------------------------------------------------------------------------------------------------\n");
			printf("\n\n\t\t\t\t\t\tIncorrect Flight-ID!!!!!!\n");
	printf("\n\n\t\t\t\t\t\tPress any key to re-enter flight ID!!!!!!\n");
	printf("\n------------------------------------------------------------------------------------------------------------------");
	//getch();
	//fgetc(stdin);
	goto flight_max_info;
		
	}
	strcpy(flight_dummy,flight_no);
	printf("\n------------------------------------------------------------------------------------------------------------------\n");
	flight_date:
	printf("\n Please confirm the date(dd format)\t");
	p_input(date);
	dd=atoi(date);
	
	printf("\n Please confirm month(mm format)\t");
	p_input(month);
	mm=atoi(month);
	if(!(dd==d && mm==m)) {
			printf("\n------------------------------------------------------------------------------------------------------------------\n");
	printf("\n\t\t\tDates entered do not match!!!!!\n\t\t\tPlease re-enter the date of travel.");
		printf("\n------------------------------------------------------------------------------------------------------------------\n");
		goto flight_date;}
	
	strcat(strcat(strcat(flight_no,date),month),".txt"); // file name is stored in flight_no
	
	int req_seat,max_seat;
	
	max_seat= s_information(flight_no);
	printf("\n------------------------------------------------------------------------------------------------------------------\n");
	printf("\n\tAvailable seats\t: %d",max_seat);
	printf("\n------------------------------------------------------------------------------------------------------------------\n");
	
	function_seat:	
	
	printf("\n Number of passenger\n (More than 4 not allowed):\t");
	scanf("%d",&req_seat);
	
	if(req_seat>4)
	{printf("\n------------------------------------------------------------------------------------------------------------------\n");
		printf("\n\n\t\t\t\t\t\t Sorry!! Only 4 allowed at a time.\n\n");
		printf("\n\n\t\t\t\t\t\tPress any key to retry!!!!!!\n");
	printf("\n------------------------------------------------------------------------------------------------------------------\n");
		getch();
		fgetc(stdin);
		goto function_seat;
		
	}
	else if(req_seat>max_seat)
	{	printf("\n------------------------------------------------------------------------------------------------------------------\n");	
		printf("\t\t\t\t\t\tCurrently unavailable\n");
		printf("\t\t\t\t\t\tPress any key to retry!!!!!!");
		printf("\n------------------------------------------------------------------------------------------------------------------\n");
		
		getch();
		fgetc(stdin);
		goto flight_search;
	}
	else
	{//printf(" In main %f",f_dist);
	//sleep(10);
		info_collect(flight_no,req_seat,max_seat, flight_dummy, d, m,o_final,d_final,n_final,g, f_dist);
		//printf("%s",g);
		/*if(!strcmp(g,"toto")){
			goto flight_search;
		}*/
	}
	printf("\n===================================================================================================================\n");
	printf("\nPress '1' to confirm your booking and proceed to Payment \n\t\t\tOR\n press '2' to book another ticket:\t");
	
	scanf("%d", &Enter);
	//fgetc(stdin);
	switch(Enter){
		case 1: 
			system ("cls");
			booking(total_fare(req_seat, f_dist),o_final,d_final,n_final,d, m,req_seat,flight_no,max_seat);
		case 2:
			printf("\n===================================================================================================================\n");
			printf("Press '0' to exit \n\t\t\tOR\n press '1' to book another ticket:\t");
			//fgetc(stdin);
			scanf("%d", &Enter2);
			switch(Enter2){
				case 0:
					fclose(p_file);
					goto Home;
				case 1:
					fgetc(stdin);
						goto flight_search;
					
			}
		
	}
	//booking(total_fare(req_seat),o_final,d_final,n_final,d, m,req_seat,flight_no,max_seat);
	
					
					
					//printf("\n\t\t\t\t\t password %s.", login_user.password);
					//printf("\n\t\t\t\t\t email %s.", login_user.email);
					//printf("\n\t\t\t\t\t userid %s.", login_user.userid);
					//printf("\n\t\t\t\t\t Welcome %s.", login_user.name);
					return 1;

				}
				else {
					system("cls");
					printf("\n\n--------------------------------------------------------------------------------------------");
					printf("\n\t\t\t\tUser ID and Password don't match !!!");
					printf("\n--------------------------------------------------------------------------------------------\n\n");
					Beep(900,300);
					fclose(p_file);
					sleep(2);
					goto Home;
					return 0;
				}
			}
		}

		if (!p_member) {
			system("cls");
			printf("\n\n--------------------------------------------------------------------------------------------");
			printf(" \n\t\t\t\tUser not registered !!!! Getting back to Home.");
			printf("\n--------------------------------------------------------------------------------------------\n");
			fclose(p_file);
			sleep(2);
			goto Home;
			return 0;
		}

	case 3:
		admin_home:
		system("cls");
		printf("======================================================================================================================\n");
		printf("\n\t\t\t\tWelcome to Admin Zone\n\n");
		printf("======================================================================================================================\n");
		printf("\n Enter your Admin ID:\t");
		p_input(p_userid);
		printf("\n Enter your password:\t");
		p_pass(p_pword);
		ad_file = fopen("Admins.dat", "r");
		while (fread(&login_user, sizeof(struct user), 1, ad_file)) {
			if (!strcmp(login_user.userid, p_userid)) {
				if (!strcmp(login_user.password, p_pword)) {
					ad_task:
					system ("cls");
					printf("\n-----------------------------------------------------------------------------------------------");
					printf("\n\t\t\t\tWelcome  Admin %s.", login_user.name);
					printf("\n-----------------------------------------------------------------------------------------------\n");
					printf("\t\t\t\t\tHow can I serve you?");
					printf("\n1.Add an admin.");
					printf("\n2.Modify flight schedule.");
					printf("\n3.Exit.");
					printf("\n\n Your choice:\t");
					scanf("%d", &ad_opt);
					fgetc(stdin);
					switch (ad_opt) {
					case 3:
						goto Home;
					case 1:
						system("cls");
						printf("\n-----------------------------------------------------------------------------------------------");
						printf("\n \t\t\t\tEnter new admin's details");
						printf("\n-----------------------------------------------------------------------------------------------\n\n");
						printf("\n Enter new admin's userid:\t");
						//scanf("%s", &useriddummy);
						//fgetc(stdin);
						p_input(useriddummy);


						c_file = fopen("Admins.dat", "a+");
						while (fread(&reg_user, sizeof(struct user), 1, c_file)) {
							//printf("%d",i1);
							//i1++;
							if (!strcmp(reg_user.userid, useriddummy)) {
								system ("cls");
								printf("\n-----------------------------------------------------------------------------------------------");
								printf("\nOops!!! Admin id already taken :( Please try with a different id. Getting back to Home screen :)");
								printf("\n-----------------------------------------------------------------------------------------------\n\n");
								fclose(c_file);
								sleep(2);
								goto admin_home;
								return 0;

							}
						}
						fclose(c_file);
						printf("\n Confirm userid:\t");
						p_input(admin_user.userid);
						printf("\n Enter new admin's name:\t");
						p_input(admin_user.name);
						ad_email:
						printf("\n Enter new admin's email:\t");
						p_input(admin_user.email);
						ad_mail=check_email(admin_user.email);
						if(ad_mail){
						goto ad_email;
						}
						adminpass:
								printf("\nGive a 16 or less character password. A password should contain a special character, a number and an alphabet!!");
						printf("\n Enter new admin's password:\t");
						p_pass(admin_user.password);
						ap=checkpass(admin_user.password);
						if(!ap){
							goto adminpass;
						}
						
						printf("\n Confirm your password:\t");
						p_pass(adpass);
						if (!strcmp(admin_user.password, adpass)) {
							//printf("\nYour passwords match!!!");
							ad_file = fopen("Admins.dat", "a+");
							fwrite(&admin_user, sizeof(struct user), 1, ad_file);
							if (fwrite != 0) {
								system ("cls");
					
								printf("\n-----------------------------------------------------------------------------------------------");
								printf("\n Admin registered !!! Going to Home screen :)");
								printf("\n-----------------------------------------------------------------------------------------------\n");
								//printf("\n\t\t\t\t\t password %s.", admin_user.password);
					//printf("\n\t\t\t\t\t email %s.", admin_user.email);
					//printf("\n\t\t\t\t\t userid %s.", admin_user.userid);
					//printf("\n\t\t\t\t\t Welcome %s.", admin_user.name);
								sleep(2);
								system ("cls");
								fclose(ad_file);
								goto Home;
							}


						}
						else {
							system ("cls");
							printf("\n-----------------------------------------------------------------------------------------------");
							printf("\nYour passwords do not match!");
							printf("\n-----------------------------------------------------------------------------------------------\n");
							Beep(900, 300);
							fclose(ad_file);
							
							goto Home;
							
							
						}
						fclose(ad_file);
						break;
					case 2:
						system("cls");
						printf("\n-----------------------------------------------------------------------------------------------");
					printf("\n\t\t\t\tWelcome  Admin %s.", login_user.name);
					printf("\n-----------------------------------------------------------------------------------------------\n");
						printf("\n Select your task.\n");
						printf("1.Add a flight.\n");
						printf("2.Delete a flight.\n");
						printf("3.View all available flights.\n");
						printf("4.Search with Flight ID.\n");
						printf("5.Search flight with origin and destination.\n");
						printf("6.Exit.\n");
						printf("Your choice:\t");
						scanf("%d",&ad_opt2);
						fgetc(stdin);
						switch(ad_opt2){
							case 1:
								system("cls");
									printf("\n-----------------------------------------------------------------------------------------------");
						printf("\n\t\t\t\tEnter new flight details.");
						printf("\n-----------------------------------------------------------------------------------------------\n");
						addflight("flights.txt");
							printf("\n===================================================================================================================\n");
						printf("Press '0' to exit \n\t\t\tOR\n press '1' to go to Admin Home:\t");
						scanf("%d", &Enter2);
						switch(Enter2){
							case 0:
							goto Home;
							case 1:
							fgetc(stdin);
							goto ad_task;
							}
						break;
					
			
						
						case 2:
							system("cls");
								printf("\n-----------------------------------------------------------------------------------------------");
						printf("\n\t\t\t\tFlight Deletion Portal");
						printf("\n-----------------------------------------------------------------------------------------------\n");
						
						displayflights("flights.txt");
						printf("\n Enter Flight ID of flight you want to delete:\t");
						p_input(ad_fid);
						deleteflight("flights.txt",ad_fid);
						sleep(2);
						system("cls");
						displayflights("flights.txt");
						printf("\n===================================================================================================================\n");
						printf("Press '0' to exit \n\t\t\tOR\n press '1' to go to Admin Home:\t");
						scanf("%d", &Enter2);
						switch(Enter2){
							case 0:
							goto Home;
							case 1:
							fgetc(stdin);
							goto ad_task;
							}
						break;
						case 3:
							system("cls");
								printf("\n-----------------------------------------------------------------------------------------------");
						printf("\n\t\t\t\t Operational Flights");
						printf("\n-----------------------------------------------------------------------------------------------\n");
						displayflights("flights.txt");
						printf("\n===================================================================================================================\n");
						printf("Press '0' to exit \n\t\t\tOR\n press '1' to go to Admin Home:\t");
						scanf("%d", &Enter2);
						switch(Enter2){
							case 0:
							goto Home;
							case 1:
							fgetc(stdin);
							goto ad_task;
							}
						break;
						case 4:
							system("cls");
							printf("Enter Flight ID:");
							p_input(flightid);
							r_fp=fopen("flights.txt","r");  //display all files
	if (!r_fp) {
		printf("Unable to open file!");
		return -1;
	}
	
	while (fread(&record,sizeof(struct flights),1,r_fp)) {            //find and delete file
		if (!strcmp (flightid, record.number)) {
	printf(" %-10s | %-25s | %-25s | %-5s | %-5s \n", "Flight-ID", "Origin", "Destination", "Day", "Distance");
			printf("---------------------------------------------------------------------------------------------------\n");
	printf(" %-10s | %-25s | %-25s | %-5d | %-5f \n", record.number, record.origin, record.dest,record.day, record.distance );
			found2=1;
		} 
		}
		if(!found2){
			printf("No such flight present.");
			
		}
	fclose(r_fp);
	printf("\nPress any key to continue....");
	getch();
	goto ad_task;						
	case 5:
		system("cls");
			printf("\n\n From:\t");
	p_input(ad_org);
	printf("\n To:\t");
	p_input(ad_dest);
	/*printf("\n Enter date of travel(dd format):\t");
	scanf("%d", &ad_d);
	printf("\n Enter month of travel(mm format):\t");
	scanf("%d", &ad_m);
	printf("\n Enter year of travel(yyyy format):\t");
	scanf("%d", &ad_y);
	printf("\n-----------------------------------------------------------------------------------------------------------------------");
	printf("\n\n");
	int ad_wd,ad_k=0;
	ad_wd=weekday(ad_d,ad_m,ad_y);*/
	int ad_k=0;

	struct flights flight;
	
	
	FILE *q_file;
	
	
	printf("\n %-10s | %-25s | %-25s | %-5s | %-5s \n", "Flight-ID", "Origin", "Destination", "Day", "Distance");
	printf("---------------------------------------------------------------------------------------------------\n");
	q_file = fopen("flights.txt", "r");
	while (fread(&flight, sizeof(struct flights), 1, q_file)) {
	//printf("%d",i1);
	//i1++;
	if (!strcmp(ad_org,flight.origin) && !strcmp(ad_dest, flight.dest)) {
		ad_k=1;
	
	printf(" %-10s | %-25s | %-25s | %-5d | %-5f \n", flight.number, flight.origin, flight.dest,flight.day, flight.distance );
	//fclose(c_file);
	//return 0;
	}
	
	}
	if(!ad_k){
	printf("\n\n\t\t\t\t\t\tNO FLIGHTS AVAILABLE!!!!!!\n");
	printf("\n\t\t\t\tSorry for the inconvenience, try some other dates for your journey\n\n");
	printf("\n\n\t\t\t\t\t\tPress any key to retry!!!!!!\n");
	getch();
	fclose(q_file);
	fgetc(stdin);
	goto ad_task;
	}
	fclose(q_file);
	printf("\nPress any key to continue....");
	getch();
	goto ad_task;
	
	case 6:
		goto Home;
	
		
		}
	}
				}
				else {
				printf("\n-----------------------------------------------------------------------------------------------");
				printf("\n Oops!!!Admin ID and Password don't match :( Going back to Home.");
				printf("\n-----------------------------------------------------------------------------------------------\n");
				Beep(900, 300);
					fclose(ad_file);
				sleep(2);
					goto admin_home;
				}
			}
		}
		if (!ad_member) {
			printf("\n-----------------------------------------------------------------------------------------------");
			printf("\n Admin not registered.");
			printf("\n-----------------------------------------------------------------------------------------------\n");
			Beep(900, 300);
			sleep(2);
			goto admin_home;
		}



	}



}





