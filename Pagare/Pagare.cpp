#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <vector>

constexpr auto DATA_PATH = "C:\\Users\\alex2\\data.csv";

using namespace std;

struct Invoice
{
	string guid;
	string name;
	string email;
	string description;
	string amount;
	string phone;
};

static string create_guid()
{
	string guid = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
	for (int i = 0; i < guid.size(); i++)
	{
		auto& c = guid[i];
		if (c == 'x')
		{
			c = rand() % 16;
			c = c < 10 ? '0' + c : 'a' + c - 10;
		}
		else if (c == 'y')
		{
			c = rand() % 4;
			c = '8' + c;
		}
	}
	return guid;
}

static void create_file()
{
	// Check if exists file
	ifstream inputFile(DATA_PATH);
	if (inputFile.is_open())
	{
		inputFile.close();
		return;
	}

	// Create file
	ofstream outputFile(DATA_PATH);
	outputFile.close();
}

static void add_invoice(Invoice invoice)
{
	// Add line to file
	ofstream file(DATA_PATH, ios::app);
	file << invoice.name << "," << invoice.email << "," << invoice.description << "," << invoice.amount << "," << invoice.phone << "\n";
	file.close();
}

static vector<Invoice> get_invoices()
{
	vector<Invoice> invoices;
	ifstream file(DATA_PATH);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			Invoice invoice;
			int pos = 0;
			pos = line.find(",");
			invoice.name = line.substr(0, pos);
			line.erase(0, pos + 1);
			pos = line.find(",");
			invoice.email = line.substr(0, pos);
			line.erase(0, pos + 1);
			pos = line.find(",");
			invoice.description = line.substr(0, pos);
			line.erase(0, pos + 1);
			pos = line.find(",");
			invoice.amount = std::stod(line.substr(0, pos));
			line.erase(0, pos + 1);
			invoice.phone = line;
			invoices.push_back(invoice);
		}
		file.close();
	}
	return invoices;
}

static void print_table(vector<Invoice> invoices)
{
	// Imprime el encabecado de la tabla
	cout << std::left << std::setw(45) << "GUID";
	cout << std::left << std::setw(20) << "NAME";
	cout << std::left << std::setw(30) << "EMAIL";
	cout << std::left << std::setw(30) << "DESCRIPTION";
	cout << std::left << std::setw(10) << "AMOUNT";
	cout << std::left << "PHONE" << std::endl;

	// Imprime una línea separadora
	cout << std::left << std::setw(45) << std::setfill('-') << "";

	// Imprime las filas de la tabla
	for (auto invoice : invoices)
	{
		cout << std::left << std::setw(45) << invoice.guid;
		cout << std::left << std::setw(20) << invoice.name;
		cout << std::left << std::setw(30) << invoice.email;
		cout << std::left << std::setw(30) << invoice.description;
		cout << std::left << std::setw(10) << invoice.amount;
		cout << std::left << invoice.phone << std::endl;
	}
}

int main()
{
	create_file();

	// Menu:
	cout << "Menu" << endl;
	cout << "1. Add invoice" << endl;
	cout << "2. Show invoices" << endl;

	// Request option
	int option;
	cin >> option;
	cout << endl;

	switch (option)
	{
	case 1:
	{
		Invoice invoice;
		string name, email, description, amount, phone;
		invoice.guid = create_guid();
		cout << "Name:" << endl;
		getline(cin, name);
		cout << "Email:" << endl;
		getline(cin, email);
		cout << "Description:" << endl;
		getline(cin, description);
		cout << "Amount:" << endl;
		getline(cin, amount);
		cout << "Phone:" << endl;
		getline(cin, phone);

		add_invoice(invoice);
		break;
	}
	case 2:
	{
		auto invoices = get_invoices();
		print_table(invoices);
		break;
	}
	default:
		cout << "Opción inválida" << endl;
		break;
	}
}
