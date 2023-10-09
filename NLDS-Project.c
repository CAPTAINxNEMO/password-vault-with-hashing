#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
char password[100], reference[100], encrypted[100], key[100], decrypted[100];
void key_generator(char *key, int n)
{
	srand((unsigned int)(time(NULL)));
	int index = 0;
	char strings[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	for (index = 0; index < n; index++)
	{
		key[index] = strings[rand() % (sizeof strings - 1)];
	}
	key[index] = '\0';
}
void cipher(char *input, char *output, char *key)
{
	int i;
	for (i = 0; i < strlen(input); i++)
	{
		output[i] = input[i] ^ key[i];
	}
	output[i] = '\0';
}
void save_password()
{
	printf("Enter your reference: ");
	scanf("%s", reference);
	printf("Enter your password: ");
	scanf("%s", password);
	key_generator(key, strlen(password));
	cipher(password, encrypted, key);
	FILE *fp;
	fp = fopen("password-vault/vault.txt", "a");
	if (fp == NULL)
	{
		printf("File failed to open");
	}
	else
	{
		fprintf(fp, "%s %s %s", reference, encrypted, key);
		fputs("\n", fp);
	}
	fclose(fp);
	puts("Your password has been encrypted and saved");
}
void open_password()
{
	char input_reference[40];
	printf("Enter reference word: ");
	scanf("%s", input_reference);
	FILE *fp;
	fp = fopen("password-vault/vault.txt", "r");
	if (fp == NULL)
	{
		printf("Reference not found.");
	}
	else
	{
		for (int i = 0; i < 40; i++)
		{
			fscanf(fp, "%s %s %s \n", reference, encrypted, key);
			if (strcmp(reference, input_reference) == 0)
			{
				break;
			}
		}
		cipher(encrypted, decrypted, key);
		printf("Decrypted password: %s", decrypted);
		printf("\nHash: %s", key);
	}
}
void display_references()
{
	printf("The references are:\n");
	FILE *fp;
	fp = fopen("password-vault/vault.txt", "r");
	if (fp == NULL)
	{
		printf("File failed to open");
	}
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "\n%s %s %s", reference, encrypted, key);
			puts(reference);
		}
	}
}
int main()
{
	system("cls");
	int choice;
	printf("Welcome to the Password Manager");
	do
	{
		printf("\n1. Save a new password\n2. Open a saved password\n3. Display all the references\n4. Exit");
		printf("\nEnter your choice: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			save_password();
			break;
		case 2:
			open_password();
			break;
		case 3:
			display_references();
			break;
		case 4:
			exit(0);
			break;
		default:
			printf("Enter a valid choice");
			break;
		}
	} while (choice != 4);
}