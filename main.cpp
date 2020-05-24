#define _CRT_SECURE_NO_WARNINGS  //для использования scanf 
#include <stdio.h> 
#include <Windows.h> //русифицируем консоль (библиотека помогает взаимодействовать с ОС)
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
	SetConsoleCP(1251); //задаем кодировку для вывода символов на экран на русском
	SetConsoleOutputCP(1251); //задаем кодировку для ввода символов с клавиатуры в консоль на русском
	setlocale(LC_ALL, "Rus"); //также русификация
	
	int navigator = 0;  // служит навигацией в меню программы
	struct library book[H];

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

		printf("%19s%30s%30s%15s%17s\n", a,b,c,d,e);
		printf("----------------------------------------------------------------------------------------------------------------\n");


		int i = 1;
		char mas[N];
		fscanf(books, "%lld;", &book[i].isbn);
		int j = 0;
		while (book[i].isbn > 0) {            //цикл вывода библиотеки
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
		printf("Меню программы:\n");
		printf("----------------------------------------------------------------------------------------------------------------\n");
		printf("Выберите операцию из доступных:\n");
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
		if ((navigator != 1) && (navigator != 2) && (navigator != 3) && (navigator != 4) && (navigator != 5)) {
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

	}
	printf("Работа успешно завершена!");
	putchar('\n');
	return 0;
}