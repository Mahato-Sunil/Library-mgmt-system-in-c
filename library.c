/* Library Management System */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// global declaration
int ch = 0;
int choice;
long int offsetposition;
int flag = 0;
char temp_choice[20] = {0};

// functions
void menu();
void user_data();
void admin_data();
void verification();
void add_book();
void edit_book();
void book_list();
void delete ();
void search();

void exit_message();
void return_to_menu();
void clear_screen();

struct library
{
	char book_name[20];
	char author[20];
	char book_code[4];
};
struct library book;

FILE *fp, *temp;

// main function
int main()
{
	clear_screen();
	char exit_program = 'n';
	do
	{
		menu();
		printf("\n Enter Your choice : \t");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			user_data();
			break;
		case 2:
			verification();
			break;
		case 3:
			exit_program = 'y';
			break;
		default:
			printf("\n Sorry! Couldn't Find your choice! ");
		}
	} while (exit_program != 'y');
	exit_message();
	return 0;
}

void menu()
{
	clear_screen();
	printf("\n************************************************************");
	printf("\n\t Welcome to Library Management System ");
	printf("\n************************************************************");
	printf("\n############################################################");
	printf("\n\t #########\t [ 1 ] >> [ USER ]\t#########");
	printf("\n\t #########\t [ 2 ] >> [ ADMIN ]\t#########");
	printf("\n\t #########\t [ 3 ] >> [ EXIT ]\t#########");
	printf("\n************************************************************");
	printf("\n############################################################");
}

// show the users data
void user_data()
{
	clear_screen();
	printf("\n************************************************************");
	printf("\n\t Welcome to Library Management System ");
	printf("\n************************************************************");
	printf("\n { USER PANEL } ");
	printf("\n############################################################");
	printf("\n\t #########\t [ 1 ] >> [ BOOK LIST ]\t#########");
	printf("\n\t #########\t [ 2 ] >> [ SEARCH ]\t#########");
	printf("\n\t #########\t [ 3 ] >> [ EXIT ]\t#########");
	printf("\n************************************************************");
	printf("\n############################################################");
	printf("\n Enter your choice :\t ");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		book_list();
		break;
	case 2:
		search();
		break;
	case 3:
		exit_message();
	default:
		printf("\n Invalid Choice");
	}
}

// show admin data
void admin_data()
{
	clear_screen();
	printf("\n************************************************************");
	printf("\n\t Welcome to Library Management System ");
	printf("\n************************************************************");
	printf("\n { ADMIN PANEL } ");
	printf("\n############################################################");
	printf("\n\t #########\t [ 1 ] >> [ BOOK LIST ]\t#########");
	printf("\n\t #########\t [ 2 ] >> [ SEARCH ]\t#########");
	printf("\n\t #########\t [ 3 ] >> [ ADD BOOK ]\t#########");
	printf("\n\t #########\t [ 4 ] >> [ EDIT ]\t#########");
	printf("\n\t #########\t [ 5 ] >> [ Delete ]\t#########");
	printf("\n\t #########\t [ 6 ] >> [ EXIT ]\t#########");
	printf("\n************************************************************");
	printf("\n############################################################");
	printf("\n Enter your choice :\t ");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		book_list();
		break;
	case 2:
		search();
		break;
	case 3:
		add_book();
		break;
	case 4:
		edit_book();
		break;
	case 5:
		delete ();
		break;
	case 6:
		exit_message();
		break;
	default:
		printf("\n Sorry! Your choice couldn't' be verified.");
	}
}

// verification  for admin
void verification()
{
	clear_screen();
	int default_pwd = 1234;
	int user_pwd;
	printf("\n************************************************************");
	printf("\n\t Welcome to Library Management System ");
	printf("\n************************************************************");
	printf("\n Welcome Admin !! \n Please verify your identity :");
	printf("\n Enter the password :\t");
	scanf("%d", &user_pwd);
	if (user_pwd == default_pwd)
	{
		admin_data();
	}
	else
		return;
}

// show book list
void book_list()
{
	clear_screen();
	errno = 0;
	printf("\n************************************************************");
	printf("\n\t Welcome to Library Management System ");
	printf("\n************************************************************");
	fp = fopen("/storage/emulated/0/HOME/Library Management System/library.dat", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "\n Error :  %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
	rewind(fp);
	fseek(fp, 0, SEEK_END);
	offsetposition = ftell(fp);
	if (offsetposition > 0)
	{
		rewind(fp);
		printf("\n Preparing to read the data ! \n");
		printf("\n \t Name : \t Author \t Book code : ");
		printf("\n\t________________________________________");
		while (fread(&book, sizeof(book), 1, fp))
		{
			printf("\n \t%s  \t %s  \t %s ", book.book_name, book.author, book.book_code);
			printf("\n\t________________________________________");
		}
	}
	fclose(fp);
	return_to_menu();
}

// function to add book
void add_book()
{
	clear_screen();
	char file_ch = 'y';
	errno = 0;
	printf("\n************************************************************");
	printf("\n\t Welcome to Library Management System ");
	printf("\n************************************************************");
	printf("\n Add your book details here :\n");
	fp = fopen("/storage/emulated/0/HOME/Library Management System/library.dat", "a");
	if (fp == NULL)
	{
		fprintf(stderr, "\n\t Error :  %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
	while (file_ch != 'n')
	{
		printf("\nBook Name : \t");
		scanf("%s", book.book_name);
		printf("Author : \t");
		scanf("%s", book.author);
		printf("Book Code : \t");
		scanf("%s", book.book_code);
		fwrite(&book, sizeof(book), 1, fp);
		printf("\n Do you want to continue ?\t");
		scanf("%s", &file_ch);
	}
	fclose(fp);
	return_to_menu();
}

// function to edit book
void edit_book()
{
	clear_screen();
	struct library edit;
	errno = 0;
	char has_record = 'n';
	printf("\n************************************************************");
	printf("\n\t Welcome to Library Management System ");
	printf("\n************************************************************");
	temp = fopen("/storage/emulated/0/HOME/Library Management System/temp_library.dat", "w");
	fp = fopen("/storage/emulated/0/HOME/Library Management System/library.dat", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "\n Error :  %s", strerror(errno));
	}
	rewind(fp);
	fseek(fp, 0, SEEK_END);
	offsetposition = ftell(fp);
	if (offsetposition > 0)
	{
		printf("\n Enter the book code to edit :\t");
		scanf("%s", temp_choice);
		rewind(fp);
		while (fread(&book, sizeof(book), 1, fp))
		{
			if (strcmp(temp_choice, book.book_code) == 0)
			{
				has_record='y';
				printf("\n Do you want to edit the following record :\n 1 : Yes , 0 :No?");
				printf("\n%s\t %s \t%s \n\t", book.book_name, book.author, book.book_code);
				scanf("%d", &ch);
				if (ch == 1)
				{
					printf("\n New Book Name : \t");
					scanf("%s", edit.book_name);
					printf("\nAuthor (if changed) : \t");
					scanf("%s", edit.author);
					printf("\n Book Code (If changed)) : \t");
					scanf("%s", edit.book_code);
					fwrite(&edit, sizeof(edit), 1, temp);
				}
				else
					return;
			}
			else
			{
				fwrite(&book, sizeof(book), 1, temp);
			}
		}
		
		if (has_record == 'n')
			printf("\n Sorry the book is not in the library");
	}
	fclose(fp);
	fclose(temp);
	remove("library.dat");
	rename("temp_library.dat", "library.dat");
	return_to_menu();
}

// function to search
void search()
{
	clear_screen();
	char has_record = 'n';
	printf("\n************************************************************");
	printf("\n\t Welcome to Library Management System ");
	printf("\n************************************************************");
	fp = fopen("/storage/emulated/0/HOME/Library Management System/library.dat", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "\n Error :  %s", strerror(errno));
	}
	rewind(fp);
	fseek(fp, 0, SEEK_END);
	offsetposition = ftell(fp);
	if (offsetposition > 0)
	{
		printf("\n Enter the book name to search :\t");
		scanf("%s", temp_choice);
		rewind(fp);
		while (fread(&book, sizeof(book), 1, fp))
		{
			if (strcmp(temp_choice, book.book_name) == 0)
			{
				printf("\n *********************************\n");
				printf("\n\t Book Name : %s ", book.book_name);
				printf("\n\t Author Name  : %s ", book.author);
				printf("\n\t Book Code : %s ", book.book_code);
				printf("\n");
				has_record = 'y';
			}
		}
		if (has_record == 'n')
			printf("\n Sorry the book is not in the library");
	}
	fclose(fp);
	return_to_menu();
}

// function to delete book name
void delete ()
{
	clear_screen();
	printf("\n************************************************************");
	printf("\n\t Welcome to Library Management System ");
	printf("\n************************************************************");
	fp = fopen("/storage/emulated/0/HOME/Library Management System/library.dat", "r");
	temp = fopen("/storage/emulated/0/HOME/Library Management System/temp_library.dat", "w");
	rewind(fp);
	fseek(fp, 0, SEEK_END);
	offsetposition = ftell(fp);
	if (offsetposition > 0)
	{
		printf("\n Enter the book code to delete :\t");
		scanf("%s", temp_choice);
		rewind(fp);
		while (fread(&book, sizeof(book), 1, fp))
		{
			if (strcmp(temp_choice, book.book_code) == 0)
			{
				printf("\n Do you want to delete the following record :\n 1 : Yes , 0 :No?");
				printf("\n\t Name : %s \n\t Author : %s \n\t Code : %s \n", book.book_name, book.author, book.book_code);
				scanf("%d", &ch);
				if (ch == 1)
				{
					flag = 1;
					continue;
				}
				else
					return;
			}
		}
		if (flag == 1)
		{
			rewind(fp);
			while (fread(&book, sizeof(book), 1, fp))
			{
				if (strcmp(temp_choice, book.book_code) != 0)
				{
					fwrite(&book, sizeof(book), 1, temp);
				}
			}
			printf("\n One record deleted ! ");
		}
	}
	else
		printf("\n The file is empty.");
	fclose(fp);
	fclose(temp);
	remove("library.dat");
	rename("temp_library.dat", "library.dat");
	return_to_menu();
}

// function to show exit message
void exit_message()
{
	clear_screen();
	printf("\n************************************************************");
	printf("\n\t ! THANK YOU FOR USING THE PROGRAM ! ");
	printf("\n\n CREATOR : SUNIL MAHATO");
	printf("\n************************************************************");
	fclose(fp);
}

// function to returm to main screen
void return_to_menu()
{
	getchar();
	printf("\nPress ENTER to return on main menu ");
	ch = getchar();
	return;
}

//function to clear the screen
void clear_screen()
{
	printf("\e[1;1H\e[2J");
}