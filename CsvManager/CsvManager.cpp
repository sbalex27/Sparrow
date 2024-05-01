#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <vector>

using namespace std;

constexpr auto DATA_PATH = "C:\\Users\\alex2\\data.csv";
//constexpr auto LOG_PATH = "C:\\Users\\alex2\\OneDrive\\Documentos\\CsvManager\\log.txt";

class GuidFactory
{
public:
	/// <summary>
	/// Create a new random guid.
	/// </summary>
	/// <returns></returns>
	static string create()
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
};

struct Person
{
	string guid;
	string name;
	string lastName;
	int age;
};

class CsvManager
{
private:
	/// <summary>
	/// Create the main file.
	/// </summary>
	void init_file()
	{
		ofstream file(DATA_PATH);
		
		if (file.is_open())
		{
			//file << "guid,name,lastName,age" << endl;
			file.close();
		}
		else
		{
			throw "Could not create file";
		}
	}

	bool assert_file() {
		ifstream file(DATA_PATH);
		auto isCreated = file.good();

		// Throw exception if the file does not exist.
		if (!isCreated) {
			throw "File does not exist";
		}
	}

	/// <summary>
	/// Factory to create new guids.
	/// </summary>
	GuidFactory* guidFactory;

public:
	CsvManager(GuidFactory* guidFactory)
	{
		this->guidFactory = guidFactory;
	}

	/// <summary>
	/// Check if the file exists, if not, create it.
	/// </summary>
	void create_if_no_exists()
	{
		ifstream file(DATA_PATH);
		auto isCreated = file.good();
		if (!isCreated) init_file();
	}

	/// <summary>
	/// Create a new person in the file. If the guid is empty, a new one will be created.
	/// </summary>
	/// <param name="person"></param>
	void insert(Person person)
	{
		if (person.guid.empty()) {
			person.guid = guidFactory->create();
		}

		ofstream file(DATA_PATH, ios::app);
		file << person.guid << "," << person.name << "," << person.lastName << "," << person.age << endl;
		file.close();
	}

	/// <summary>
	/// Find and replace a person in the file.
	/// </summary>
	/// <param name="id">Id to find</param>
	/// <param name="person">Person to replace</param>
	/// <returns></returns>
	bool update(string guid, Person person)
	{
		ifstream file(DATA_PATH);
		ofstream temp("temp.csv");

		string line;
		while (getline(file, line))
		{
			auto& data = line;
			auto lastIdentifierIndex = data.find(",");
			auto guidMatch = data.substr(0, lastIdentifierIndex);
			if (guidMatch == guid)
			{
				temp << guid << "," << person.name << "," << person.lastName << "," << person.age << endl;
			}
			else
			{
				temp << line << endl;
			}
		}

		file.close();
		temp.close();

		auto removed = remove(DATA_PATH);
		auto renamed = rename("temp.csv", DATA_PATH);

		return removed == 0 && renamed == 0;
	}

	void erase(string guid)
	{
		ifstream file(DATA_PATH);
		ofstream temp("temp.csv");

		string line;
		while (getline(file, line))
		{
			auto& data = line;
			auto lastIdentifierIndex = data.find(",");
			auto guidMatch = data.substr(0, lastIdentifierIndex);
			if (guidMatch != guid)
			{
				temp << line << endl;
			}
		}

		file.close();
		temp.close();

		auto removed = remove(DATA_PATH);
		auto renamed = rename("temp.csv", DATA_PATH);
	}

	Person search(string guid)
	{
		ifstream file(DATA_PATH);
		string line;
		while (getline(file, line))
		{
			auto& data = line;
			auto lastIdentifierIndex = data.find(",");
			auto guidMatch = data.substr(0, lastIdentifierIndex);
			if (guidMatch == guid)
			{
				auto nameIndex = lastIdentifierIndex + 1;
				auto lastNameIndex = data.find(",", nameIndex);
				auto ageIndex = data.find(",", lastNameIndex + 1);

				auto name = data.substr(nameIndex, lastNameIndex - nameIndex);
				auto lastName = data.substr(lastNameIndex + 1, ageIndex - lastNameIndex - 1);
				auto age = stoi(data.substr(ageIndex + 1));

				return { guid, name, lastName, age };
			}
		}

		return { "", "", "", 0 };
	}

	vector<Person> select()
	{
		assert_file();
		ifstream file(DATA_PATH);
		vector<Person> people;
		string line;
		while (getline(file, line))
		{
			auto& data = line;
			auto lastIdentifierIndex = data.find(",");
			auto guid = data.substr(0, lastIdentifierIndex);
			auto nameIndex = lastIdentifierIndex + 1;
			auto lastNameIndex = data.find(",", nameIndex);
			auto ageIndex = data.find(",", lastNameIndex + 1);

			auto name = data.substr(nameIndex, lastNameIndex - nameIndex);
			auto lastName = data.substr(lastNameIndex + 1, ageIndex - lastNameIndex - 1);
			auto age = stoi(data.substr(ageIndex + 1));

			people.push_back({ guid, name, lastName, age });
		}

		return people;
	}

	vector<Person> select_where(string value) {
		ifstream file(DATA_PATH);
		vector<Person> people;
		string line;

		while (getline(file, line))
		{
			auto& data = line;
			auto lastIdentifierIndex = data.find(",");
			auto guid = data.substr(0, lastIdentifierIndex);
			auto nameIndex = lastIdentifierIndex + 1;
			auto lastNameIndex = data.find(",", nameIndex);
			auto ageIndex = data.find(",", lastNameIndex + 1);

			auto name = data.substr(nameIndex, lastNameIndex - nameIndex);
			auto lastName = data.substr(lastNameIndex + 1, ageIndex - lastNameIndex - 1);
			auto age = stoi(data.substr(ageIndex + 1));

			auto containsName = name.find(value) != string::npos;
			auto containsLastName = lastName.find(value) != string::npos;
			if (containsName || containsLastName) {
				people.push_back({ guid, name, lastName, age });
			}
		}

		return people;
	}

	bool drop_database()
	{
		return remove(DATA_PATH) == 0;
	}

	void refresh_database()
	{
		remove(DATA_PATH);
		init_file();
	}
};

class ConsoleUi {

public:
	void displayMenu() {
		cout << "Menu" << endl;
		cout << "Seleccione una opcion" << endl;
		cout << "----------------" << endl;
		cout << "1. Nuevo" << endl;
		cout << "2. Actualizar" << endl;
		cout << "3. Borrar" << endl;
		cout << "4. Buscar por GUID" << endl;
		cout << "5. Mostrar Todos" << endl;
		cout << "6. Buscar Donde" << endl;
		cout << "7. Borrar Base de Datos" << endl;
		cout << "8. Volver a crear base de datos" << endl;
		cout << "9. Salir" << endl;
	}

	void display_person(Person person) {
		cout << "Guid: " << person.guid << endl;
		cout << "Name: " << person.name << endl;
		cout << "Last name: " << person.lastName << endl;
		cout << "Age: " << person.age << endl;
	}

	void print_table(const std::vector<Person>& people) {
		// Imprime el encabezado de la tabla
		std::cout << std::left << std::setw(45) << "GUID";
		std::cout << std::left << std::setw(30) << "Name";
		std::cout << std::left << std::setw(30) << "Last Name";
		std::cout << std::left << "Age" << std::endl;

		// Imprime una línea separadora
		std::cout << std::setw(120) << std::setfill('-') << "" << std::setfill(' ') << std::endl;

		// Imprime los datos de cada persona
		for (const auto& person : people) {
			std::cout << std::left << std::setw(45) << person.guid;
			std::cout << std::left << std::setw(30) << person.name;
			std::cout << std::left << std::setw(30) << person.lastName;
			std::cout << std::left << person.age << std::endl;
		}
	}

	void clear_screen() {
		system("cls");
	}

	Person input_person() {
		Person person;
		cout << "Name: ";
		cin >> person.name;
		cout << "Last name: ";
		cin >> person.lastName;
		cout << "Age: ";
		cin >> person.age;
		return person;
	}

	int request_input() {
		int option;
		cin >> option;
		return option;
	}
};

int main()
{
	GuidFactory* guidFactory = new GuidFactory();
	ConsoleUi* ui = new ConsoleUi();
	CsvManager* manager = new CsvManager(guidFactory);

	manager->create_if_no_exists();

	do
	{
		ui->displayMenu();
		auto option = ui->request_input();
		//ui->clear_screen();

		switch (option)
		{
		case 1:
		{
			auto person = ui->input_person();
			manager->insert(person);
			break;
		}
		case 2:
		{
			auto person = ui->input_person();
			string guid;
			cout << "Guid: ";
			cin >> guid;
			manager->update(guid, person);
			break;
		}
		case 3:
		{
			string guid;
			cout << "Guid: ";
			cin >> guid;
			manager->erase(guid);
			break;
		}
		case 4:
		{
			string guid;
			cout << "Guid: ";
			cin >> guid;
			auto person = manager->search(guid);
			ui->display_person(person);
			break;
		}
		case 5:
		{
			auto people = manager->select();
			ui->print_table(people);
			break;
		}
		case 6:
		{
			string value;
			cout << "Value: ";
			cin >> value;
			auto people = manager->select_where(value);
			ui->print_table(people);
			break;
		}
		case 7:
		{
			manager->drop_database();
			break;
		}
		case 8:
		{
			manager->refresh_database();
			break;
		}
		case 9:
		{
			cout << "Adios!" << endl;
			return 0;
		}
		default:
			break;
		}
	} while (true);
}
