//Files
#include<iostream>
#include<fstream>
using namespace std;

//TODO:
//	1. Есть файл 201 RAW.txt, из этого файла нужно создать другой файл 201 ready.txt,
//		в котором столбик с IP - адресом и MAC - адресом будут поменяны местами;
//			https://github.com/okovtun/PV_225/blob/master/Inheritance/Files/NetworkTask/201%20RAW.txt
//	2. Из файла 201 RAW.txt создать файл формата 201.dhcpd
//			https ://github.com/okovtun/PV_225/blob/master/Inheritance/Files/NetworkTask/201.dhcpd

//#define WRITE_TO_FILE
//#define READ_FROM_FILE
#define HOMEWORK_1
#define HOMEWORK_2

void main()
{
	setlocale(LC_ALL, "");

#ifdef HOMEWORK_1
	ifstream fin;
	ofstream fout;
	char filename_read[_MAX_FNAME] = "201 RAW.txt";
	char filename_write[_MAX_FNAME] = "201 ready.txt";
	fin.open(filename_read);
	fout.open(filename_write, std::ios_base::app);
	if (fin.is_open())
	{
		const int SIZE = 256;
		char buffer_0[SIZE]{};
		char buffer_1[SIZE]{};
		while (!fin.eof())
		{
			fin >> buffer_0 >> buffer_1;
			fout << buffer_1 << '\t' << buffer_0 << endl;
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found!" << endl;
	}
	fout.close();
	char sz_command[_MAX_FNAME] = "notepad ";
	strcat_s(sz_command, _MAX_FNAME, filename_write);
	system(sz_command);
#endif //HOMEWORK_1

#ifdef HOMEWORK_2
	ifstream fin;
	ofstream fout;
	char filename_read[_MAX_FNAME] = "201 RAW.txt";
	char filename_write[_MAX_FNAME] = "201.dhcpd";
	fin.open(filename_read);
	fout.open(filename_write, std::ios_base::app);
	if (fin.is_open())
	{
		const int SIZE = 256;
		char buffer_0[SIZE]{};
		char buffer_1[SIZE]{};
		int i = 1;
		while (!fin.eof())
		{
			fin >> buffer_0 >> buffer_1;
			for (int i = 0; i < strlen(buffer_1); i++)
			{
				if (buffer_1[i] == '-') buffer_1[i] = ':';
			}
			fout << "host 201-" << i << "\n{\n\thardware ethernet\t" << buffer_1 << ";\n\tfixed - address\t\t" << buffer_0 << ";\n}\n\n";
			i++;
		}
		fin.close();
}
	else
	{
		std::cerr << "Error: File not found!" << endl;
	}
	fout.close();
	char sz_command[_MAX_FNAME] = "notepad ";
	strcat_s(sz_command, _MAX_FNAME, filename_write);
	system(sz_command);
#endif //HOMEWORK_2

#ifdef WRITE_TO_FILE
	char filename[_MAX_FNAME] = {};
	cout << "Введите имя файла: ";
	cin.getline(filename, _MAX_FNAME);
	if (strcmp(filename - (strlen(filename) - 4), ".txt")) strcat_s(filename, _MAX_FNAME, ".txt");
	ofstream fout;								// 1) Создаем поток:	ofstream (класс потока) fout (имя экземпляра потока);
	fout.open(filename, std::ios_base::app);	// 2) Открываем поток	fout (имя экземпляра потока).(вызов метода класса)open (метод, открывающий поток);
	fout << "Hello files" << endl;				// 3) Пишем в поток		fout (имя экземпляра потока) << (оператор передачи в поток) "Текст, передаваемый в поток";
	fout.close();								// 4) Закрываем поток	fout (имя экземпляра потока).close(метод, закрывающий поток);
	
	char sz_command[_MAX_FNAME] = "notepad ";
	strcat_s(sz_command, _MAX_FNAME, filename);
	system(sz_command);			// Открываем файл в программе Блокнот;
#endif //WRITE_TO_FILE

#ifdef READ_FROM_FILE
	ifstream fin;					// 1) Создаем поток чтения файла: ifstream (класс чтения файла) fin (имя экземпляра потока);
	fin.open("File.txt");			// 2) Открываем поток чтения файла: fin (имя экземпляра потока).open(метод, открывающий поток чтения файла);
	if (fin.is_open())				// 3) Проверяем, открылся ли поток
	{
		const int SIZE = 256;		// 4) Задаем размер буфера, в который будем считывать файл
		char sz_buffer[SIZE]{};		// 5) Создаем буфер, в который будем считывать файл
		//https://ru.wikipedia.org/wiki/%D0%92%D0%B5%D0%BD%D0%B3%D0%B5%D1%80%D1%81%D0%BA%D0%B0%D1%8F_%D0%BD%D0%BE%D1%82%D0%B0%D1%86%D0%B8%D1%8F
		while (!fin.eof())			// 6) Цикл чтения файла через буфер
		{
			fin.getline(sz_buffer, SIZE);		//zero-terminated string - строка, ограниченная нулевым символом
			//fin >> sz_buffer;
			cout << sz_buffer << endl;
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
#endif
}