#define _CRT_SECURE_NO_WARNINGS  //��� ������������� scanf 
#include <stdio.h> 
#include <Windows.h> //������������ ������� (���������� �������� ����������������� � ��)
#include <time.h>
#include <string.h>
#include <locale.h>
#include <iostream>
#include <fstream>

#define N 100
#define H 50

struct library {
	long long isbn;
	char author[N];
	char name[N];
	int total;
	int free;
};

int main() {
	SetConsoleCP(1251); //������ ��������� ��� ������ �������� �� ����� �� �������
	SetConsoleOutputCP(1251); //������ ��������� ��� ����� �������� � ���������� � ������� �� �������
	setlocale(LC_ALL, "Rus"); //����� �����������
	
	int navigator = 0;  // ������ ���������� � ���� ���������
	struct library book[H];

	while (navigator == 0) {
		FILE* books; // ��������� FILE �������� ����������� ���������� � ����� csv �������
		system("cls"); //������� ������ �������
		books = fopen("books.csv", "r");
		if (books == NULL) {
			printf("�� ������� ������� ����");
		}

		printf("���� ������ ��������������� ����������:\n");
		printf("----------------------------------------------------------------------------------------------------------------\n");
		char a[] = "ISBN";
		char b[] = "�����";
		char c[] = "��������";
		char d[] = "����� ����";
		char e[] = "�������� ����";

		printf("%19s%30s%30s%15s%17s\n", a,b,c,d,e);
		printf("----------------------------------------------------------------------------------------------------------------\n");


		int i = 1;
		char mas[N];
		fscanf(books, "%lld;", &book[i].isbn);
		int j = 0;
		while (book[i].isbn > 0) {            //���� ������ ����������
			printf("%19lld", book[i].isbn);
			while ((mas[j] = fgetc(books)) != '\n') {
				if (mas[j] == ';') {
					mas[j] = '\0';
					printf("%30s", mas);
					strncpy(book[i].author, mas, N);
					j = 0;
					break;
				}
				else j++;
			}
			while ((mas[j] = fgetc(books)) != '\n') {
				if (mas[j] == ';') {
					mas[j] = '\0';
					printf("%30s ", mas);
					strncpy(book[i].name, mas, N);
					j = 0;
					break;
				}
				else j++;
			}

			fscanf(books, "%d;%d", &book[i].total, &book[i].free);
			printf("%13d ", book[i].total);
			printf("%15d\n", book[i].free);
			i++;
			fscanf(books, "%lld;", &book[i].isbn);
		}
		fclose(books);
		
		printf("----------------------------------------------------------------------------------------------------------------\n");
		putchar('\n');
		printf("���� ���������:\n");
		printf("----------------------------------------------------------------------------------------------------------------\n");
		printf("�������� �������� �� ���������:\n");
		printf("1) �������� ����� �����\n");
		printf("2) ������� ����� �� ������ ISBN\n");
		printf("3) ������������� ���������� �� �����\n");
		printf("4) �������� ���������� ���� � ���������� �� ������ ISBN\n");
		printf("5) ����������� � ��������� ������ ���������\n");
		printf("----------------------------------------------------------------------------------------------------------------\n");
		printf("\n");
		printf(">>>");
		scanf("%d", &navigator);
		printf("\n");
		if ((navigator != 1) && (navigator != 2) && (navigator != 3) && (navigator != 4) && (navigator != 5)) {
			printf("��������� ������! �������� ������������ �������� �� ����.");
			navigator = 0;
			Sleep(2000);
			continue;
		}
		
		int checker_isbn = 1;
		int checker2_isbn = 0;
		long long checker_delete_isbn = 0;
		int delete_isbn = 0;
		long long checker_change_isbn = 0;
		int change_isbn = 0;
	
		switch (navigator)
		{
		case 1:
			books = fopen("books.csv", "w");
			while (checker_isbn == 1) { 
				printf("������� ISBN �����:");
				checker_isbn = 0;
				scanf("%lld", &book[i].isbn);
				if (book[i].isbn == 0) {
					printf("������������ ISBN.\n");
					Sleep(2000);
					checker_isbn = 1;
					continue;
				}
				for (int k = 1; k < i; k++) {
					if (book[i].isbn == book[k].isbn) {
						checker_isbn = 1;
					}
				}
				if (checker_isbn == 1) {
					printf("����� � ����� ISBN ��� ����������.\n");
					Sleep(2000);

				}
			}
			checker_isbn = 1;
			mas[j] = getchar();
			printf("������� ������ �����: ");
			mas[j] = getchar();
			while (mas[j] != '\n') {
				j++;
				mas[j] = getchar();
			}
			mas[j] = '\0';
			strncpy(book[i].author, mas, N);
			j = 0;
			printf("������� �������� �����: ");
			mas[j] = getchar();
			while (mas[j] != '\n') {
				j++;
				mas[j] = getchar();
			}
			mas[j] = '\0';
			strncpy(book[i].name, mas, N);
			j = 0;
			printf("������� ������� ���� ����� � ����������: ");
			scanf("%d", &book[i].total);
			printf("������� ������� ���� ��������: ");
			scanf("%d", &book[i].free);
			
			for (int x = 1; x <= i; x++) {
				fprintf(books, "%lld;%s;%s;%d;%d\n", book[x].isbn, book[x].author, book[x].name, book[x].total, book[x].free);
			}
			
			fclose(books);
			navigator = 0;
			system("cls");
			printf("����� ���������!");
			Sleep(2000);
			break;
		
		case 2:
			books = fopen("books.csv", "w");
			while (checker2_isbn == 0) { 
				printf("������� ISBN ��� �����, ������� ������ �������: ");
				scanf("%lld", &checker_delete_isbn);
				for (int k = 1; k < i; k++) {
					if (checker_delete_isbn == book[k].isbn) {
						checker2_isbn = 1;
						delete_isbn = k;
					}
				}
				if (checker2_isbn == 0) {
					printf("����� � ����� ISBN �� �������.\n");
					Sleep(2000);
				}
			}
			checker2_isbn = 0;
			i--;
			for (int x = 1; x < delete_isbn; x++) {
				fprintf(books, "%lld;%s;%s;%d;%d\n", book[x].isbn, book[x].author, book[x].name, book[x].total, book[x].free);

			}
			for (delete_isbn; delete_isbn < i; delete_isbn++) {
				book[delete_isbn].isbn = book[delete_isbn + 1].isbn;
				strncpy(book[delete_isbn].author, book[delete_isbn + 1].author, N);
				strncpy(book[delete_isbn].name, book[delete_isbn + 1].name, N);
				book[delete_isbn].total = book[delete_isbn + 1].total;
				book[delete_isbn].free = book[delete_isbn + 1].free;
				fprintf(books, "%lld;%s;%s;%d;%d\n", book[delete_isbn].isbn, book[delete_isbn].author, book[delete_isbn].name, book[delete_isbn].total, book[delete_isbn].free);
			}
			fclose(books);
			book[i].isbn = NULL;
			navigator = 0;
			system("cls");
			printf("����� �������!");
			Sleep(2000);
			break;
		
		case 3:
			books = fopen("books.csv", "w");
			while (checker2_isbn == 0) {
				printf("������� ISBN ��� �����, ������� ������ ��������: ");
				scanf("%lld", &checker_change_isbn);
				for (int k = 1; k < i; k++) {
					if (checker_change_isbn == book[k].isbn) {
						checker2_isbn = 1;
						change_isbn = k;
					}
				}
				if (checker2_isbn == 0) {
					printf("����� � ����� ISBN �� �������.\n");
					Sleep(2000);
				}
			}
			checker2_isbn = 0;

			for (int x = 1; x < change_isbn; x++) {
				fprintf(books, "%lld;%s;%s;%d;%d\n", book[x].isbn, book[x].author, book[x].name, book[x].total, book[x].free);
			}

			mas[j] = getchar();
			printf("������� ������ ������ �����: ");
			mas[j] = getchar();
			while (mas[j] != '\n') {
				j++;
				mas[j] = getchar();
			}
			mas[j] = '\0';
			strncpy(book[change_isbn].author, mas, N);
			j = 0;
			
			printf("������� ����� �������� �����: ");
			mas[j] = getchar();
			while (mas[j] != '\n') {
				j++;
				mas[j] = getchar();
			}
			mas[j] = '\0';
			strncpy(book[change_isbn].name, mas, N);
			j = 0;
			
			fprintf(books, "%lld;%s;%s;%d;%d\n", book[change_isbn].isbn, book[change_isbn].author, book[change_isbn].name, book[change_isbn].total, book[change_isbn].free);
			for (change_isbn; change_isbn < i; change_isbn++) {
				fprintf(books, "%lld;%s;%s;%d;%d\n", book[change_isbn + 1].isbn, book[change_isbn + 1].author, book[change_isbn + 1].name, book[change_isbn + 1].total, book[change_isbn + 1].free);
			}
			
			fclose(books);
			book[i].isbn = NULL;
			navigator = 0;
			system("cls");
			printf("����� ��������!");
			Sleep(2000);

			break;

		case 4:
			books = fopen("books.csv", "w");
			while (checker2_isbn == 0) {
				printf("������� ISBN ��� �����, ���������� ������� �� ������ ��������: ");
				scanf("%lld", &checker_change_isbn);
				for (int k = 1; k < i; k++) {
					if (checker_change_isbn == book[k].isbn) {
						checker2_isbn = 1;
						change_isbn = k;
					}
				}
				if (checker2_isbn == 0) {
					printf("����� � ����� ISBN �� �������.\n");
					Sleep(2000);
				}
			}
			checker2_isbn = 0;

			for (int x = 1; x < change_isbn; x++) {
				fprintf(books, "%lld;%s;%s;%d;%d\n", book[x].isbn, book[x].author, book[x].name, book[x].total, book[x].free);
			}

			printf("������� ����� ���������� ���� � ���������: ");
			scanf("%d", &book[change_isbn].total);

			fprintf(books, "%lld;%s;%s;%d;%d\n", book[change_isbn].isbn, book[change_isbn].author, book[change_isbn].name, book[change_isbn].total, book[change_isbn].free);
			for (change_isbn; change_isbn < i; change_isbn++) {
				fprintf(books, "%lld;%s;%s;%d;%d\n", book[change_isbn + 1].isbn, book[change_isbn + 1].author, book[change_isbn + 1].name, book[change_isbn + 1].total, book[change_isbn + 1].free);
			}

			fclose(books);
			book[i].isbn = NULL;
			navigator = 0;
			system("cls");
			printf("���������� ���� � ���������� ��������!");
			Sleep(2000);

			break;

		case 5:
			books = fopen("books.csv", "w");
			for (int x = 1; x < i; x++) {
				fprintf(books, "%lld;%s;%s;%d;%d\n", book[x].isbn, book[x].author, book[x].name, book[x].total, book[x].free);
			}
			fclose(books);
			printf("���������� ������...\n");
			putchar('\n');
			Sleep(1500);
			exit;
		}

	}
	printf("������ ������� ���������!");
	putchar('\n');
	return 0;
}