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
	//�������������� � ������ ��������� �������
	//������������� ������ � ������
	//switch case �� �������� �� �������� std::string poroSad :(
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
			std::cout << " >>>> ���������� � �����: " << std::endl;
			std::cout << "�����: " << this->_author << std::endl;
			std::cout << "��������: " << this->_title << std::endl;
			std::cout << "������������: " << this->_publisher << std::endl;
			std::cout << "��� �������: " << this->_year << std::endl;
			std::cout << "���������� �������: " << this->_pages << std::endl;
			std::cout << " <<<< " << std::endl;
			std::cout << std::endl;
		} else {
			std::cout << " >> �����: " << this->_author << " | ��������: " << this->_title << " || " << this->_publisher << " | " << this->_year << " | " << this->_pages << std::endl;
		}
	}

	//custom method
	string generateId() { return this->_author + this->_pages + this->_title; };
};

//������� ���������, ��� �� ������� � ������ �����
bool isAllDigits(string str) {
	for (int i = 0; i < str.length(); i++) if (!std::isdigit(str[i])) return false;
	return true;
}

//����� �� ��������� ��� ����������� � ������
bool exit() {
	string input;
	std::cout << "1. ��������� � ������\n2. ��������� ������" << std::endl;
	std::cout << "�������� ��������: ";
	std::cin >> input;
	if (isAllDigits(input) && std::stoi(input) == 1) return false;
	return true;
}

bool dialogSortTemplate(string coutProp, string prop, vector<Book> books, string err, string filter = "exact") {
	string input;
	if (filter == "exact") {
		
		string value;
		//��������� �������� �������� ������ ��������������� obj[prop]
		std::cout << coutProp;
		std::cin.ignore();
		std::getline(std::cin, value);

		//��������� ������� ������ ����
		std::cout << "1. ������\n2. ��������" << std::endl;
		std::cout << "�������� ������ ������: ";
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
		else std::cout << "���������� ���� = " << counter << std::endl;

	} 
	else if (filter == "higher than") {
		int value;
		string temp;
		std::cout << coutProp;
		std::cin.ignore();
		std::getline(std::cin, temp);
		if (!isAllDigits(temp)) {
			std::cout << "���������� ������ �����" << std::endl;
			return false;
		}
		value = std::stoi(temp);

		//��������� ������� ������ ����
		std::cout << "1. ������\n2. ��������" << std::endl;
		std::cout << "�������� ������ ������: ";
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
		else std::cout << "���������� ���� = " << counter << std::endl;
	} 
	return exit();
}

bool actionHandler(string action, vector<Book> books) {
	int act = isAllDigits(action) ? std::stoi(action) : 0;
	switch (act) {
	case 1: {
		//���������� ������ ������ ������������ ������ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		return dialogSortTemplate("������� ��� ������: ", "author", books, "� ��������� ������� ������ ��� � ������", "exact");
	}
	case 2: {
		//���������� ������ ������ ������������ ������ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		return dialogSortTemplate("������� �������� ������������: ", "publisher", books, "� ��������� ������� ������������ ��� � ������", "exact");
	}
	case 3: {
		//���������� ������� ������ ������������ ������ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		return dialogSortTemplate("������� ��� ����� �������� ����� ������ ���� �����: ", "year", books, "� ��������� ���� ����� ��������� ���� ������� ��� � ������", "higher than");
	}

	case 4: {
		return true;
	}
	default:
		std::cout << "����� ������� �� ����������" << std::endl;
		return false;
	}
	return true;
}


int main() {
	//������� ���� ��� ������������� std::getline;
	SetConsoleCP(1251);
	setlocale(LC_ALL, "Russian");
	ifstream txt;
	txt.open("Books.txt");
	
	//������ ����
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
		std::cout << "1. �������� ������ ���� ��������� ������" << std::endl;
		std::cout << "2. �������� ������ ����, ���������� �������� �������������" << std::endl;
		std::cout << "3. �������� ������ ���� ���������� ����� ��������� ����" << std::endl;
		std::cout << "4. ����� �� ���������" << std::endl;
		std::cout << "�������� ��������: ";
		std::cin >> action;
		exit = actionHandler(action, books);
	};

	return 0;
}