#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>


#ifndef _STRUCT_H
#include "st.h"
#endif


int displayflights(char *rfile) {
	FILE *read_fp;
	struct flights record;

	read_fp=fopen(rfile,"rb");
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

int deleteflight(char *del_f, char *del_flight) {

	FILE *del_file;
	FILE *del_newfile;
	int found=0;
	struct flights record;

	del_file=fopen(del_f, "r");
	if (!del_file) {
		printf("Unable to open file %s", del_f);
		return -1;
	}
	del_newfile=fopen("tmp_flights.txt", "w");
	if (!del_newfile) {
		printf("Unable to open new temp file.");
		return -1;
	}
	
	while (fread(&record,sizeof(struct flights),1,del_file)) {
		if (!strcmp (del_flight, record.number)) {
			printf("\nA Flight with requested ID %s found and deleted.\n\n",record.number);
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

	remove(del_f);
	rename("tmp_flights.txt", del_f);

	return 0;
}
void p_input(char p_ch[50]) {
	fgets(p_ch, 50, stdin);
	p_ch[strlen(p_ch) - 1] = 0;
}

int addflight(char *add_f){
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

int check_email(char *em){
	int e;
	for(e=0;e<strlen(em);e++){
		printf("%c\n",em[e]);
		// 64 is ASCII value of @
		if(em[e]==64){
			return 0;
		}}
		
		
			printf("\n Give a valid email address!!");
			Beep(900,300);
			return 1;
		
	
}
void main(){
	char mail[50];
	int r_mail=0;
	email:
	printf("\n Enter your email:\t");
	p_input(mail);
	r_mail=check_email(mail);
	if(r_mail){
		goto email;
		
	}
	
}
