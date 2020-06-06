#define _CRT_SECURE_NO_WARNINGS  //для использования scanf 
#include <stdio.h> 
#include <Windows.h> //русифицируем консоль (библиотека помогает взаимодействовать с ОС)
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
	SetConsoleCP(1251); //задаем кодировку для вывода символов на экран на русском
	SetConsoleOutputCP(1251); //задаем кодировку для ввода символов с клавиатуры в консоль на русском
	setlocale(LC_ALL, "Rus"); //также русификация

	int navigator = 0;  // служит навигацией в меню программы
	struct library book[H];
	struct students person[H];
	struct entry user[H];



	FILE* users; // Структура FILE содержит необходимую информацию о файле csv формата
	system("cls"); //очистка экрана консоли
	users = fopen("users.csv", "r");
	if (users == NULL) {
		printf("Не удалось открыть файл");
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

	printf("Здравствуйте!\n");
	char mas1[N];
	int pos;
	int mode;
	int checker_user = 0;
	users = fopen("users.csv", "r");
	while (checker_user == 0) {
		printf("Введите логин: ");
		j = -1;
		while (mas[j] != '\n') {
			j++;
			mas[j] = getchar();
		}
		mas[j] = '\0';

		j = -1;
		printf("Введите пароль: ");
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
			printf("Пользователь с таким логином или паролем не найден!\n");
			Sleep(2000);
		}
	}
	checker_user = 0;
	if ((user[pos].students == 1) && (user[pos].books == 1))   //присваивание мода для пользователя ( админ может выбирать и его мод - 1)
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
			printf("База данных университетской библиотеки: главное меню\n");
			putchar('\n');
			printf("----------------------------------------------------------------------------------------------------------------\n");
			printf("Выберите:\n");
			putchar('\n');
			printf("1) Просмотр и редактирование информации по книгам\n");
			printf("2) Просмотр и редактирование информации по студентам\n");
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
				FILE* books; // Структура FILE содержит необходимую информацию о файле csv формата
				system("cls"); //очистка экрана консоли
				books = fopen("books.csv", "r");
				if (books == NULL) {
					printf("Не удалось открыть файл");
				}

				printf("База данных университетской библиотеки:\n");
				printf("----------------------------------------------------------------------------------------------------------------\n");
				char a[] = "ISBN";
				char b[] = "Автор";
				char c[] = "Название";
				char d[] = "Всего книг";
				char e[] = "Доступно книг";

				printf("%19s%30s%30s%15s%17s\n", a, b, c, d, e);
				printf("----------------------------------------------------------------------------------------------------------------\n");


				int i = 1;
				char mas[N];
				fscanf(books, "%lld;", &book[i].isbn);
				int j = 0;
				while (book[i].isbn > 0) {            //цикл вывода библиотеки и присваивания 
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
				printf("Меню:\n");
				printf("----------------------------------------------------------------------------------------------------------------\n");
				printf("Выберите операцию из доступных:\n");
				if (mode == 1) { printf("0) Вернуться в основное меню\n"); }
				printf("1) Добавить новую книгу\n");
				printf("2) Удалить книгу по номеру ISBN\n");
				printf("3) Редактировать информацию по книге\n");
				printf("4) Изменить количество книг в библиотеке по номеру ISBN\n");
				printf("5) Сохраниться и завершить работу программы\n");
				printf("----------------------------------------------------------------------------------------------------------------\n");
				printf("\n");
				printf(">>>");
				scanf("%d", &navigator);
				printf("\n");
				if ((navigator != 0) && (navigator != 1) && (navigator != 2) && (navigator != 3) && (navigator != 4) && (navigator != 5)) {
					printf("Произошла ошибка! Выберите существующее действие из меню.");
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
						printf("Введите ISBN книги:");
						checker_isbn = 0;
						scanf("%lld", &book[i].isbn);
						if (book[i].isbn == 0) {
							printf("Некорректный ISBN.\n");
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
							printf("Книга с таким ISBN уже существует.\n");
							Sleep(2000);

						}
					}
					checker_isbn = 1;
					mas[j] = getchar();
					printf("Введите автора книги: ");
					mas[j] = getchar();
					while (mas[j] != '\n') {
						j++;
						mas[j] = getchar();
					}
					mas[j] = '\0';
					strncpy(book[i].author, mas, N);
					j = 0;
					printf("Введите название книги: ");
					mas[j] = getchar();
					while (mas[j] != '\n') {
						j++;
						mas[j] = getchar();
					}
					mas[j] = '\0';
					strncpy(book[i].name, mas, N);
					j = 0;
					printf("Введите сколько книг всего в библиотеке: ");
					scanf("%d", &book[i].total);
					printf("Введите сколько книг доступно: ");
					scanf("%d", &book[i].free);

					for (int x = 1; x <= i; x++) {
						fprintf(books, "%lld;%s;%s;%d;%d\n", book[x].isbn, book[x].author, book[x].name, book[x].total, book[x].free);
					}

					fclose(books);
					navigator = 0;
					system("cls");
					printf("Книга добавлена!");
					Sleep(2000);
					break;

				case 2:
					books = fopen("books.csv", "w");
					while (checker2_isbn == 0) {
						printf("Введите ISBN той книги, которую хотите удалить: ");
						scanf("%lld", &checker_delete_isbn);
						for (int k = 1; k < i; k++) {
							if (checker_delete_isbn == book[k].isbn) {
								checker2_isbn = 1;
								delete_isbn = k;
							}
						}
						if (checker2_isbn == 0) {
							printf("Книга с таким ISBN не найдена.\n");
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
					printf("Книга удалена!");
					Sleep(2000);
					break;

				case 3:
					books = fopen("books.csv", "w");
					while (checker2_isbn == 0) {
						printf("Введите ISBN той книги, которую хотите изменить: ");
						scanf("%lld", &checker_change_isbn);
						for (int k = 1; k < i; k++) {
							if (checker_change_isbn == book[k].isbn) {
								checker2_isbn = 1;
								change_isbn = k;
							}
						}
						if (checker2_isbn == 0) {
							printf("Книга с таким ISBN не найдена.\n");
							Sleep(2000);
						}
					}
					checker2_isbn = 0;

					for (int x = 1; x < change_isbn; x++) {
						fprintf(books, "%lld;%s;%s;%d;%d\n", book[x].isbn, book[x].author, book[x].name, book[x].total, book[x].free);
					}

					mas[j] = getchar();
					printf("Введите нового автора книги: ");
					mas[j] = getchar();
					while (mas[j] != '\n') {
						j++;
						mas[j] = getchar();
					}
					mas[j] = '\0';
					strncpy(book[change_isbn].author, mas, N);
					j = 0;

					printf("Введите новое название книги: ");
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
					printf("Книга изменена!");
					Sleep(2000);

					break;

				case 4:
					books = fopen("books.csv", "w");
					while (checker2_isbn == 0) {
						printf("Введите ISBN той книги, количество которой вы хотите изменить: ");
						scanf("%lld", &checker_change_isbn);
						for (int k = 1; k < i; k++) {
							if (checker_change_isbn == book[k].isbn) {
								checker2_isbn = 1;
								change_isbn = k;
							}
						}
						if (checker2_isbn == 0) {
							printf("Книга с таким ISBN не найдена.\n");
							Sleep(2000);
						}
					}
					checker2_isbn = 0;

					for (int x = 1; x < change_isbn; x++) {
						fprintf(books, "%lld;%s;%s;%d;%d\n", book[x].isbn, book[x].author, book[x].name, book[x].total, book[x].free);
					}

					printf("Введите новое количество книг в библотеке: ");
					scanf("%d", &book[change_isbn].total);

					fprintf(books, "%lld;%s;%s;%d;%d\n", book[change_isbn].isbn, book[change_isbn].author, book[change_isbn].name, book[change_isbn].total, book[change_isbn].free);
					for (change_isbn; change_isbn < i; change_isbn++) {
						fprintf(books, "%lld;%s;%s;%d;%d\n", book[change_isbn + 1].isbn, book[change_isbn + 1].author, book[change_isbn + 1].name, book[change_isbn + 1].total, book[change_isbn + 1].free);
					}

					fclose(books);
					book[i].isbn = NULL;
					navigator = 0;
					system("cls");
					printf("Количество книг в библиотеке изменено!");
					Sleep(2000);

					break;

				case 5:
					books = fopen("books.csv", "w");
					for (int x = 1; x < i; x++) {
						fprintf(books, "%lld;%s;%s;%d;%d\n", book[x].isbn, book[x].author, book[x].name, book[x].total, book[x].free);
					}
					fclose(books);
					printf("Завершение работы...\n");
					putchar('\n');
					Sleep(1500);
					exit;

				}
				if (exit == 1) { break; }
			}
			if (exit == 1) {
				continue;
			}
			printf("Работа успешно завершена!");
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
					printf("Не удалось открыть файл");
				}
				
				printf("База данных студентов:\n");
				printf("------------------------------------------------------------------------------------------------------------------------\n");
				char a[] = "Номер зачетки";
				char b[] = "Фамилия";
				char c[] = "Имя";
				char d[] = "Отчество";
				char e[] = "Фак-ет";
				char f[] = "Специальность";

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
				printf("Меню:\n");
				printf("------------------------------------------------------------------------------------------------------------------------\n");
				printf("Выберите операцию из доступных:\n");
				putchar('\n');
				if (mode == 1) { printf("0) Вернуться в основное меню\n"); }
				printf("1) Добавить студента\n");
				printf("2) Удалить студента по номеру зачетной книжки\n");
				printf("3) Редактировать информацию по студенту\n");
				printf("4) Просмотреть информацию по студенту по номеру зачетной книжки\n");
				printf("5) Сохраниться и завершить работу программы\n");
				printf("------------------------------------------------------------------------------------------------------------------------\n");
				printf("\n");
				printf(">>>");
				scanf("%d", &navigator);
				printf("\n");
				if ((navigator != 0) && (navigator != 1) && (navigator != 2) && (navigator != 3) && (navigator != 4) && (navigator != 5)) {
					printf("Произошла ошибка! Выберите существующее действие из меню.");
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
						printf("Введите номер зачетки: ");
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
							printf("Некорректный номер зачетки.\n");
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
							printf("Студент с таким номером зачетки уже существует.\n");
							Sleep(2000);

						}
					}
					checker_number = 1;
					printf("Введите фамилию студента: ");
					while (mas[j] != '\n') {
						j++;
						mas[j] = getchar();
					}
					mas[j] = '\0';
					strncpy(person[i].surname, mas, N);
					j = -1;
					printf("Введите имя студента: ");
					while (mas[j] != '\n') {
						j++;
						mas[j] = getchar();
					}
					mas[j] = '\0';
					strncpy(person[i].name, mas, N);
					j = -1;
					printf("Введите отчество студента: ");
					while (mas[j] != '\n') {
						j++;
						mas[j] = getchar();
					}
					mas[j] = '\0';
					strncpy(person[i].dadname, mas, N);
					j = -1;
					printf("Введите факультет студента: ");
					while (mas[j] != '\n') {
						j++;
						mas[j] = getchar();
					}
					mas[j] = '\0';
					strncpy(person[i].faculty, mas, N);
					j = -1;
					printf("Введите специальность студента: ");
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
					printf("Студент добавлен!");
					Sleep(2000);
					break;

				case 2:
					students = fopen("students.csv", "w");
					while (checker2_number == 0) {
						printf("Введите номер зачетки того студента, которого хотите удалить: ");
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
							printf("Студент с таким номером зачетки не найден.\n");
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
					printf("Студент удален!");
					Sleep(2000);
					break;


				case 3:
					students = fopen("students.csv", "w");
					while (checker2_number == 0) {
						printf("Введите номер зачетки того студента, которого хотите изменить: ");
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
							printf("Студент с таким номером зачетки не найден.\n");
							Sleep(2000);
						}
					}
					checker2_number = 0;

					for (int x = 1; x < change_number; x++) {
						fprintf(students, "%s;%s;%s;%s;%s;%s\n", person[x].number, person[x].surname, person[x].name, person[x].dadname, person[x].faculty, person[x].speciality);
					}

					j = -1;
					printf("Введите новый факультет студента: ");
					while (mas[j] != '\n') {
						j++;
						mas[j] = getchar();
					}
					mas[j] = '\0';
					strncpy(person[change_number].faculty, mas, N);
					j = -1;
					printf("Введите новую специальность студента: ");
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
					printf("Информация по студенту изменена!");
					Sleep(2000);

					break;

				case 4:
					students = fopen("students.csv", "r");
					while (checker2_number == 0) {
						printf("Введите номер зачетки того студента, информацию о котором вы хотите просмотреть: ");
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
							printf("Студент с таким номером зачетки не найден.\n");
							Sleep(2000);
						}
					}
					checker2_number = 0;

					printf("Искомый студент:\n\n");
					printf("%s %s %s %s %s %s\n\n", person[show_number].number, person[show_number].surname, person[show_number].name, person[show_number].dadname, person[show_number].faculty, person[show_number].speciality);
					printf("Для продолжения нажмите Enter...\n");
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
					printf("Завершение работы...\n");
					putchar('\n');
					Sleep(1500);
					exit;
				}

				if (exit == 1) { break; }
			}
			if (exit == 1) {
				continue;
			}
			printf("Работа успешно завершена!");
			putchar('\n');
			return 0;

		}
	}
}