#define _CRT_SECURE_NO_WARNINGS  //��� ������������� scanf 
#include <stdio.h> 
#include <Windows.h> //������������ ������� (���������� �������� ����������������� � ��)
#include <time.h>
#include <string.h>
#include <locale.h>
#include <iostream>
#include <fstream>

#define N 100
#define H 90

struct library {
	long long isbn;
	char author[N];
	char name[N];
	int total;
	int free;
};
struct students {
	char number[N];
	char surname[N];
	char name[N];
	char dadname[N];
	char faculty[N];
	char speciality[N];
};
struct entry {
	char login[N];
	char pswrd[N];
	int students;
	int books;
};

int main() {
	SetConsoleCP(1251); //������ ��������� ��� ������ �������� �� ����� �� �������
	SetConsoleOutputCP(1251); //������ ��������� ��� ����� �������� � ���������� � ������� �� �������
	setlocale(LC_ALL, "Rus"); //����� �����������

	int navigator = 0;  // ������ ���������� � ���� ���������
	struct library book[H];
	struct students person[H];
	struct entry user[H];



	FILE* users; // ��������� FILE �������� ����������� ���������� � ����� csv �������
	system("cls"); //������� ������ �������
	users = fopen("users.csv", "r");
	if (users == NULL) {
		printf("�� ������� ������� ����");
	}

	int i = 1;
	char mas[N];
	int j = 0;
	while ((mas[j] = fgetc(users)) != '\n') {
		if (mas[j] == ';') {
			mas[j] = '\0';
			strncpy(user[i].login, mas, N);
			j = 0;
			break;
		}
		else j++;
	}
	int flag = 0;
	while (flag != 1) {
		j = 0;
		while ((mas[j] = fgetc(users)) != '\n') {
			if (mas[j] == ';') {
				mas[j] = '\0';
				strncpy(user[i].pswrd, mas, N);
				j = 0;
				break;
			}
			else j++;
		}

		fscanf(users, "%d;%d\n", &user[i].students, &user[i].books);
		i++;
		while ((mas[j] = fgetc(users)) != '\n') {
			if (j == 90)
			{
				flag = 1;
				break;
			}
			if (mas[j] == ';') {
				mas[j] = '\0';
				strncpy(user[i].login, mas, N);
				j = 0;
				break;
			}
			else j++;
		}
		if (flag == 1)
		{
			break;
		}
	}
	fclose(users);

	printf("������������!\n");
	char mas1[N];
	int pos;
	int mode;
	int checker_user = 0;
	users = fopen("users.csv", "r");
	while (checker_user == 0) {
		printf("������� �����: ");
		j = -1;
		while (mas[j] != '\n') {
			j++;
			mas[j] = getchar();
		}
		mas[j] = '\0';

		j = -1;
		printf("������� ������: ");
		while (mas1[j] != '\n') {
			j++;
			mas1[j] = getchar();
		}
		mas1[j] = '\0';

		for (int k = 1; k < i; k++) {
			if ((strcmp(mas, user[k].login) == 0) and (strcmp(mas1, user[k].pswrd) == 0))
			{
				checker_user = 1;
				pos = k;
			}
		}
		if (checker_user == 0) {
			printf("������������ � ����� ������� ��� ������� �� ������!\n");
			Sleep(2000);
		}
	}
	checker_user = 0;
	if ((user[pos].students == 1) && (user[pos].books == 1))   //������������ ���� ��� ������������ ( ����� ����� �������� � ��� ��� - 1)
	{
		mode = 1;
	}
	else if ((user[pos].students == 1) && (user[pos].books == 0))
	{
		mode = 2;
	}
	else if ((user[pos].students == 0) && (user[pos].books == 1))
	{
		mode = 3;
	}

	int type;
	while (1) {
		system("cls");
		Sleep(1000);
		if (mode == 1) {
			printf("���� ������ ��������������� ����������: ������� ����\n");
			putchar('\n');
			printf("----------------------------------------------------------------------------------------------------------------\n");
			printf("��������:\n");
			putchar('\n');
			printf("1) �������� � �������������� ���������� �� ������\n");
			printf("2) �������� � �������������� ���������� �� ���������\n");
			printf("----------------------------------------------------------------------------------------------------------------\n");
			printf("\n");
			printf(">>>");
			scanf("%d", &type);
		}

		if (mode == 2) {
			type = 2;
		}
		if (mode == 3) {
			type = 1;
		}

		if (type == 1)
		{

			int exit = 0;
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

				printf("%19s%30s%30s%15s%17s\n", a, b, c, d, e);
				printf("----------------------------------------------------------------------------------------------------------------\n");


				int i = 1;
				char mas[N];
				fscanf(books, "%lld;", &book[i].isbn);
				int j = 0;
				while (book[i].isbn > 0) {            //���� ������ ���������� � ������������ 
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
				printf("����:\n");
				printf("----------------------------------------------------------------------------------------------------------------\n");
				printf("�������� �������� �� ���������:\n");
				if (mode == 1) { printf("0) ��������� � �������� ����\n"); }
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
				if ((navigator != 0) && (navigator != 1) && (navigator != 2) && (navigator != 3) && (navigator != 4) && (navigator != 5)) {
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
				case 0:
					exit = 1;
					break;

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
				if (exit == 1) { break; }
			}
			if (exit == 1) {
				continue;
			}
			printf("������ ������� ���������!");
			putchar('\n');
			return 0;
		}

		else if (type == 2) {
		int exit = 0;
			while (navigator == 0) {
				FILE* students;
				system("cls");
				students = fopen("students.csv", "r");
				if (students == NULL) {
					printf("�� ������� ������� ����");
				}
				
				printf("���� ������ ���������:\n");
				printf("------------------------------------------------------------------------------------------------------------------------\n");
				char a[] = "����� �������";
				char b[] = "�������";
				char c[] = "���";
				char d[] = "��������";
				char e[] = "���-��";
				char f[] = "�������������";

				printf("%15s%16s%11s%16s%9s%50s\n", a, b, c, d, e, f);
				printf("------------------------------------------------------------------------------------------------------------------------\n");

				int i = 1;
				char mas[N];
				int j = 0;
				while ((mas[j] = fgetc(students)) != '\n') {
					if (mas[j] == ';') {
						mas[j] = '\0';
						strncpy(person[i].number, mas, N);
						printf("%15s ", mas);
						j = 0;
						break;
					}
					else j++;
				}
				int flag = 0;
				while (flag != 1) {
					j = 0;
					while ((mas[j] = fgetc(students)) != '\n') {
						if (mas[j] == ';') {
							mas[j] = '\0';
							printf("%15s ", mas);
							strncpy(person[i].surname, mas, N);
							j = 0;
							break;
						}
						else j++;
					}
					while ((mas[j] = fgetc(students)) != '\n') {
						if (mas[j] == ';') {
							mas[j] = '\0';
							printf("%10s ", mas);
							strncpy(person[i].name, mas, N);
							j = 0;
							break;
						}
						else j++;
					}
					while ((mas[j] = fgetc(students)) != '\n') {
						if (mas[j] == ';') {
							mas[j] = '\0';
							printf("%15s ", mas);
							strncpy(person[i].dadname, mas, N);
							j = 0;
							break;
						}
						else j++;
					}
					while ((mas[j] = fgetc(students)) != '\n') {
						if (mas[j] == ';') {
							mas[j] = '\0';
							printf("%7s ", mas);
							strncpy(person[i].faculty, mas, N);
							j = 0;
							break;
						}
						else j++;
					}

					while ((mas[j] = fgetc(students)) != feof(students)) {
						if (mas[j] == '\n' || feof(students)) {
							if (mas[j] = feof(students))
							{
								flag = 1;
							}
							mas[j] = '\0';
							printf("%50s\n", mas);
							strncpy(person[i].speciality, mas, N);
							j = 0;
							break;
						}
						else j++;
					}
					i++;
					if (flag == 1)
					{
						break;
					}
					while ((mas[j] = fgetc(students)) != '\n' || '\0') {
						if (j == 90)
						{
							flag = 1;
							break;
						}
						if (mas[j] == ';') {
							mas[j] = '\0';
							printf("%15s ", mas);
							strncpy(person[i].number, mas, N);
							j = 0;
							break;
						}
						else j++;
					}
					if (flag == 1)
					{
						break;
					}
				}
				fclose(students);
				
				printf("------------------------------------------------------------------------------------------------------------------------\n");
				putchar('\n');
				printf("����:\n");
				printf("------------------------------------------------------------------------------------------------------------------------\n");
				printf("�������� �������� �� ���������:\n");
				putchar('\n');
				if (mode == 1) { printf("0) ��������� � �������� ����\n"); }
				printf("1) �������� ��������\n");
				printf("2) ������� �������� �� ������ �������� ������\n");
				printf("3) ������������� ���������� �� ��������\n");
				printf("4) ����������� ���������� �� �������� �� ������ �������� ������\n");
				printf("5) ����������� � ��������� ������ ���������\n");
				printf("------------------------------------------------------------------------------------------------------------------------\n");
				printf("\n");
				printf(">>>");
				scanf("%d", &navigator);
				printf("\n");
				if ((navigator != 0) && (navigator != 1) && (navigator != 2) && (navigator != 3) && (navigator != 4) && (navigator != 5)) {
					printf("��������� ������! �������� ������������ �������� �� ����.");
					navigator = 0;
					Sleep(2000);
					continue;
				}

				int checker_number = 1;
				int checker2_number = 0;
				long long checker_delete_number = 0;
				int delete_number = 0;
				long long checker_change_number = 0;
				int change_number = 0;
				int show_number = 0;
				int wait;

				switch (navigator)
				{
				case 0:
					exit = 1;
					break;

				case 1:
					students = fopen("students.csv", "w");
					while (checker_number == 1) {
						printf("������� ����� �������: ");
						j = -1;
						checker_number = 0;
						getchar();
						while (mas[j] != '\n') {
							j++;
							mas[j] = getchar();
						}
						mas[j] = '\0';
						strncpy(person[i].number, mas, N);
						j = -1;

						if (person[i].number == NULL) {
							printf("������������ ����� �������.\n");
							Sleep(2000);
							checker_number = 1;
							continue;
						}
						for (int k = 1; k < i; k++) {
							if (strcmp(person[i].number, person[k].number) == 0)
							{
								checker_number = 1;
							}
						}
						if (checker_number == 1) {
							printf("������� � ����� ������� ������� ��� ����������.\n");
							Sleep(2000);

						}
					}
					checker_number = 1;
					printf("������� ������� ��������: ");
					while (mas[j] != '\n') {
						j++;
						mas[j] = getchar();
					}
					mas[j] = '\0';
					strncpy(person[i].surname, mas, N);
					j = -1;
					printf("������� ��� ��������: ");
					while (mas[j] != '\n') {
						j++;
						mas[j] = getchar();
					}
					mas[j] = '\0';
					strncpy(person[i].name, mas, N);
					j = -1;
					printf("������� �������� ��������: ");
					while (mas[j] != '\n') {
						j++;
						mas[j] = getchar();
					}
					mas[j] = '\0';
					strncpy(person[i].dadname, mas, N);
					j = -1;
					printf("������� ��������� ��������: ");
					while (mas[j] != '\n') {
						j++;
						mas[j] = getchar();
					}
					mas[j] = '\0';
					strncpy(person[i].faculty, mas, N);
					j = -1;
					printf("������� ������������� ��������: ");
					while (mas[j] != '\n') {
						j++;
						mas[j] = getchar();
					}
					mas[j] = '\0';
					strncpy(person[i].speciality, mas, N);
					j = 0;

					for (int x = 1; x <= i; x++) {
						fprintf(students, "%s;%s;%s;%s;%s;%s\n", person[x].number, person[x].surname, person[x].name, person[x].dadname, person[x].faculty, person[x].speciality);
					}

					fclose(students);
					navigator = 0;
					system("cls");
					printf("������� ��������!");
					Sleep(2000);
					break;

				case 2:
					students = fopen("students.csv", "w");
					while (checker2_number == 0) {
						printf("������� ����� ������� ���� ��������, �������� ������ �������: ");
						j = -1;
						getchar();
						while (mas[j] != '\n') {
							j++;
							mas[j] = getchar();
						}
						mas[j] = '\0';


						for (int k = 1; k < i; k++) {
							if (strcmp(mas, person[k].number) == 0)
							{
								checker2_number = 1;
								delete_number = k;
							}
						}
						if (checker2_number == 0) {
							printf("������� � ����� ������� ������� �� ������.\n");
							Sleep(2000);
						}
					}
					checker2_number = 0;
					i--;
					for (int x = 1; x < delete_number; x++) {
						fprintf(students, "%s;%s;%s;%s;%s;%s\n", person[x].number, person[x].surname, person[x].name, person[x].dadname, person[x].faculty, person[x].speciality);

					}
					for (delete_number; delete_number < i; delete_number++) {
						strncpy(person[delete_number].number, person[delete_number + 1].number, N);
						strncpy(person[delete_number].surname, person[delete_number + 1].surname, N);
						strncpy(person[delete_number].name, person[delete_number + 1].name, N);
						strncpy(person[delete_number].dadname, person[delete_number + 1].dadname, N);
						strncpy(person[delete_number].faculty, person[delete_number + 1].faculty, N);
						strncpy(person[delete_number].speciality, person[delete_number + 1].speciality, N);
						fprintf(students, "%s;%s;%s;%s;%s\n", person[delete_number].number, person[delete_number].surname, person[delete_number].name, person[delete_number].dadname, person[delete_number].faculty, person[delete_number].speciality);
					}
					fclose(students);
					navigator = 0;
					system("cls");
					printf("������� ������!");
					Sleep(2000);
					break;


				case 3:
					students = fopen("students.csv", "w");
					while (checker2_number == 0) {
						printf("������� ����� ������� ���� ��������, �������� ������ ��������: ");
						j = -1;
						getchar();
						while (mas[j] != '\n') {
							j++;
							mas[j] = getchar();
						}
						mas[j] = '\0';
						for (int k = 1; k < i; k++) {
							if (strcmp(mas, person[k].number) == 0)
							{
								checker2_number = 1;
								change_number = k;
							}
						}
						if (checker2_number == 0) {
							printf("������� � ����� ������� ������� �� ������.\n");
							Sleep(2000);
						}
					}
					checker2_number = 0;

					for (int x = 1; x < change_number; x++) {
						fprintf(students, "%s;%s;%s;%s;%s;%s\n", person[x].number, person[x].surname, person[x].name, person[x].dadname, person[x].faculty, person[x].speciality);
					}

					j = -1;
					printf("������� ����� ��������� ��������: ");
					while (mas[j] != '\n') {
						j++;
						mas[j] = getchar();
					}
					mas[j] = '\0';
					strncpy(person[change_number].faculty, mas, N);
					j = -1;
					printf("������� ����� ������������� ��������: ");
					while (mas[j] != '\n') {
						j++;
						mas[j] = getchar();
					}
					mas[j] = '\0';
					strncpy(person[change_number].speciality, mas, N);
					j = 0;



					fprintf(students, "%s;%s;%s;%s;%s;%s\n", person[change_number].number, person[change_number].surname, person[change_number].name, person[change_number].dadname, person[change_number].faculty, person[change_number].speciality);
					for (change_number; change_number < i; change_number++) {
						fprintf(students, "%s;%s;%s;%s;%s;%s\n", person[change_number + 1].number, person[change_number + 1].surname, person[change_number + 1].name, person[change_number + 1].dadname, person[change_number + 1].faculty, person[change_number + 1].speciality);
					}

					fclose(students);
					navigator = 0;
					system("cls");
					printf("���������� �� �������� ��������!");
					Sleep(2000);

					break;

				case 4:
					students = fopen("students.csv", "r");
					while (checker2_number == 0) {
						printf("������� ����� ������� ���� ��������, ���������� � ������� �� ������ �����������: ");
						j = -1;
						getchar();
						while (mas[j] != '\n') {
							j++;
							mas[j] = getchar();
						}
						mas[j] = '\0';
						for (int k = 1; k < i; k++) {
							if (strcmp(mas, person[k].number) == 0) {
								checker2_number = 1;
								show_number = k;
							}
						}
						if (checker2_number == 0) {
							printf("������� � ����� ������� ������� �� ������.\n");
							Sleep(2000);
						}
					}
					checker2_number = 0;

					printf("������� �������:\n\n");
					printf("%s %s %s %s %s %s\n\n", person[show_number].number, person[show_number].surname, person[show_number].name, person[show_number].dadname, person[show_number].faculty, person[show_number].speciality);
					printf("��� ����������� ������� Enter...\n");
					wait = getchar();
					fclose(students);
					navigator = 0;
					Sleep(500);

					break;

				case 5:
					students = fopen("students.csv", "w");
					for (int x = 1; x < i; x++) {
						fprintf(students, "%s;%s;%s;%s;%s;%s\n", person[x].number, person[x].surname, person[x].name, person[x].dadname, person[x].faculty, person[x].speciality);
					}
					fclose(students);
					printf("���������� ������...\n");
					putchar('\n');
					Sleep(1500);
					exit;
				}

				if (exit == 1) { break; }
			}
			if (exit == 1) {
				continue;
			}
			printf("������ ������� ���������!");
			putchar('\n');
			return 0;

		}
	}
}