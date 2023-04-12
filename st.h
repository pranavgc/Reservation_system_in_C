#pragma once
#ifndef _STRUCT_H
#define _STRUCT_H
#endif

struct pass_data
{
	int pass_seq,
		pass_age;
	char pass_age_c[100],
		pass_fn[100],
	 	pass_ln[100],
	 	pass_sex[100];
	float pass_fare;
};

struct user
{
	char name[50];
	char email[50];
	char userid[50];
	char password[16];
	
};

struct flights{
	char origin[50];
	char dest[50];
	int day;
	char number[15];
	int seats;
	float distance;
};

struct card_payment
{
    
    unsigned long int card_no;
    unsigned int cvv,
				 exp_date,
				 exp_mon;
};

struct UPI_payment{
    char 	UPI_id[50];
    int     UPI_pin;
};

struct pay_details{
    char pay_type[10];
    struct card_payment card_pay;
    struct UPI_payment UPI_pay;
};
