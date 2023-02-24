#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
using namespace std;

class Book {
private:
	string _author, _title, _publisher, _year, _pages;
public:
	//Редактирование и чтение приватных свойств
	//Универсальные сеттер и геттер
	//switch case не работает со строками std::string poroSad :(
	string getProp(string prop) {
		if (prop == "author") return this->_author;
		if (prop == "title") return this->_title;
		if (prop == "publisher") return this->_publisher;
		if (prop == "year") return this->_year;
		if (prop == "pages") return this->_pages;
	}
	void setProp(string prop, string value) {
		if (prop == "author") { this->_author = value; return; }
		if (prop == "title") { this->_title = value; return; }
		if (prop == "publisher") { this->_publisher = value; return; }
		if (prop == "year") { this->_year = value; return; }
		if (prop == "pages") { this->_pages = value; return; }
	}

	Book(string author, string title, string publisher, string year, string pages) {
		this->_author = author;
		this->_title = title;
		this->_publisher = publisher;
		this->_year = year;
		this->_pages = pages;
	}

	void show(string info = "full") {
		if (info == "full") {
			std::cout << " >>>> Информация о книге: " << std::endl;
			std::cout << "Автор: " << this->_author << std::endl;
			std::cout << "Название: " << this->_title << std::endl;
			std::cout << "Издательство: " << this->_publisher << std::endl;
			std::cout << "Год выпуска: " << this->_year << std::endl;
			std::cout << "Количество страниц: " << this->_pages << std::endl;
			std::cout << " <<<< " << std::endl;
			std::cout << std::endl;
		} else {
			std::cout << " >> Автор: " << this->_author << " | Название: " << this->_title << " || " << this->_publisher << " | " << this->_year << " | " << this->_pages << std::endl;
		}
	}

	//custom method
	string generateId() { return this->_author + this->_pages + this->_title; };
};

//Функция проверяет, все ли символы в строке цифры
bool isAllDigits(string str) {
	for (int i = 0; i < str.length(); i++) if (!std::isdigit(str[i])) return false;
	return true;
}

//Выход из программы или возвращение в начало
bool exit() {
	string input;
	std::cout << "1. Вернуться в начало\n2. Завершить работу" << std::endl;
	std::cout << "Выберите действие: ";
	std::cin >> input;
	if (isAllDigits(input) && std::stoi(input) == 1) return false;
	return true;
}

bool dialogSortTemplate(string coutProp, string prop, vector<Book> books, string err, string filter = "exact") {
	string input;
	if (filter == "exact") {
		
		string value;
		//Получение значение которому должен соответствовать obj[prop]
		std::cout << coutProp;
		std::cin.ignore();
		std::getline(std::cin, value);

		//Получение способа вывода книг
		std::cout << "1. Полный\n2. Неполный" << std::endl;
		std::cout << "Выберите способ вывода: ";
		std::getline(std::cin, input);

		input = isAllDigits(input) && std::stoi(input) == 1 ? "full" : "short";
		
		int counter = 0;
		for (int i = 0; i < books.size(); i++) {
			if (books[i].getProp(prop) == value) {
				counter++;
				books[i].show(input);
			};
		}
		if (counter == 0) std::cout << err << std::endl;
		else std::cout << "Количество книг = " << counter << std::endl;

	} 
	else if (filter == "higher than") {
		int value;
		string temp;
		std::cout << coutProp;
		std::cin.ignore();
		std::getline(std::cin, temp);
		if (!isAllDigits(temp)) {
			std::cout << "Необходимо ввести число" << std::endl;
			return false;
		}
		value = std::stoi(temp);

		//Получение способа вывода книг
		std::cout << "1. Полный\n2. Неполный" << std::endl;
		std::cout << "Выберите способ вывода: ";
		std::getline(std::cin, input);

		input = isAllDigits(input) && std::stoi(input) == 1 ? "full" : "short";

		int counter = 0;
		for (int i = 0; i < books.size(); i++) {
			if (std::stoi(books[i].getProp(prop)) > value) {
				counter++;
				books[i].show(input);
			};
		}
		if (counter == 0) std::cout << err << std::endl;
		else std::cout << "Количество книг = " << counter << std::endl;
	} 
	return exit();
}

bool actionHandler(string action, vector<Book> books) {
	int act = isAllDigits(action) ? std::stoi(action) : 0;
	switch (act) {
	case 1: {
		//Реализация первой задачи лабораторной работы !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		return dialogSortTemplate("Введите имя автора: ", "author", books, "К сожалению данного автора нет в списке", "exact");
	}
	case 2: {
		//Реализация второй задачи лабораторной работы !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		return dialogSortTemplate("Введите название издательства: ", "publisher", books, "К сожалению данного издательства нет в списке", "exact");
	}
	case 3: {
		//Реализация третьей задачи лабораторной работы !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		return dialogSortTemplate("Введите год после которого книга должна была выйти: ", "year", books, "К сожалению книг после заданного года выпуска нет в списке", "higher than");
	}

	case 4: {
		return true;
	}
	default:
		std::cout << "Такой команды не существует" << std::endl;
		return false;
	}
	return true;
}


int main() {
	//Русский язык при использовании std::getline;
	SetConsoleCP(1251);
	setlocale(LC_ALL, "Russian");
	ifstream txt;
	txt.open("Books.txt");
	
	//Массив книг
	vector<Book> books = {};
	vector<string> props;
	string line, temp;
	int index, curr;

	while (!txt.eof()) {
		getline(txt, line);
		if (line.find('|') == -1) continue;

		props = {};
		curr = 0;
		do {
			index = line.find('|', curr);
			props.push_back(line.substr(curr, index - curr));
			curr = index + 1;
			if (index == -1) props.push_back(line.substr(curr));
		} while (index != -1);
		Book book(props[0], props[1], props[2], props[3], props[4]);
		books.push_back(book);
	}
	txt.close();
	string action;
	bool exit = false;
	while (!exit) {
		std::cout << " >> " << std::endl;
		std::cout << "1. Получить список книг заданного автора" << std::endl;
		std::cout << "2. Получить список книг, выпущенных заданным издательством" << std::endl;
		std::cout << "3. Получить список книг выпущенных после заданного года" << std::endl;
		std::cout << "4. Выйти из программы" << std::endl;
		std::cout << "Выберите действие: ";
		std::cin >> action;
		exit = actionHandler(action, books);
	};

	return 0;
}