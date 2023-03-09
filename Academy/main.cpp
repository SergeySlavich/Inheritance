//Academy
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
using namespace std;

//TODO:
//Перегрузить констуктор класса Student таким образом,
//чтобы студента можно было создать из уже существующего человека.

#define HUMAN_TAKE_PARAMETERS	const std::string& last_name, const std::string& first_name, int year, int month, int day
#define HUMAN_GIVE_PARAMETERS	last_name, first_name, year, month, day

class Human
{
	std::string last_name;
	std::string first_name;
	tm birth_date;	//tm - timepoint
protected:
	static const int LAST_NAME_WIDTH = 15;
	static const int FIRST_NAME_WIDTH = 10;
	static const int SPECIALTY_WIDTH = 22;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	tm get_birth_date()const
	{
		return birth_date;
	}
	unsigned int get_age()const
	{
		time_t t_today = time(NULL);
		tm* tm_today = localtime(&t_today);
		unsigned int age = tm_today->tm_year - birth_date.tm_year;
		if (tm_today->tm_mon < birth_date.tm_mon)age--;
		if (tm_today->tm_mon == birth_date.tm_mon && tm_today->tm_mday < birth_date.tm_mday)age--;
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_birth_date(int year, int month, int day)
	{
		birth_date.tm_year = year - 1900;
		birth_date.tm_mon = month - 1;
		birth_date.tm_mday = day;
	}

	//				Constructors:
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_birth_date(year, month, day);
	}
	virtual ~Human() {}

	//					Methods:
	virtual std::ostream& info(std::ostream& os)const
	{
		os.width(LAST_NAME_WIDTH);
		os << left;
		os << last_name;
		os.width(FIRST_NAME_WIDTH);
		os << first_name;
		os.width(3);
		os << get_age();
		return os;
	}

	virtual std::ofstream& info(std::ofstream& ofs)const
	{
		ofs.width(LAST_NAME_WIDTH);
		ofs << left;
		ofs << last_name;
		ofs.width(FIRST_NAME_WIDTH);
		ofs << first_name;
		ofs << birth_date.tm_year + 1900 << '.';
		ofs << birth_date.tm_mon << '.';
		ofs << birth_date.tm_mday << '\t';
		return ofs;
	}

	virtual std::ifstream& scan(std::ifstream& ifs)
	{
		ifs >> last_name >> first_name;
		ifs >> birth_date.tm_year; ifs.ignore();
		ifs >> birth_date.tm_mon; ifs.ignore();
		ifs >> birth_date.tm_mday;// ifs.ignore();
		birth_date.tm_year -= 1900;
		return ifs;
	}
};
std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.info(os);
}
std::ofstream& operator<<(std::ofstream& ofs, const Human& obj)
{
	return obj.info(ofs);
}
std::ifstream& operator>>(std::ifstream& ifs, Human& obj)
{
	return obj.scan(ifs);
}

#define STUDENT_TAKE_PARAMETERS	const std::string& specialty, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS	specialty, group, rating, attendance
class Student : public Human
{
	static const int GROUP_WIDTH = 8;
	std::string specialty;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_specialty()const
	{
		return specialty;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->specialty = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//						Constructors:
	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS)
		:Human(HUMAN_GIVE_PARAMETERS)//Вызов конструктора базового класса
	{
		set_speciality(specialty);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
	}
	//TODO:
	//Перегрузить конструктор класса Student таким образом, чтобы студента можно было создать из уже существующего человека.
	Student
	(
		const Human& human,
		const std::string& specialty, const std::string& group, double rating, double attendance
	) :Human(human)
	{
		set_speciality(specialty);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
	}
	~Student() {}
	std::ostream& info(std::ostream& os)const override
	{
		Human::info(os);
		os << left;
		os.width(SPECIALTY_WIDTH);
		os << specialty;
		os.width(GROUP_WIDTH);
		os << group;
		os.width(GROUP_WIDTH);
		os << rating;
		os.width(GROUP_WIDTH);
		os << attendance;
		return os;
	}
	std::ifstream& scan(std::ifstream& ifs) override
	{
		Human::scan(ifs);
		char buffer[SPECIALTY_WIDTH + 1] = {};
		ifs.read(buffer, SPECIALTY_WIDTH);
		//Удаляем лишние пробелы в конце строки	
		for (int i = SPECIALTY_WIDTH - 1; buffer[i] == ' '; i--) buffer[i] = 0;
		this->specialty = buffer;

		ifs >> group;
		ifs >> rating;
		ifs >> attendance;
		return ifs;
	}
	std::ofstream& info(std::ofstream& ofs)const override
	{
		Human::info(ofs);
		ofs << left;
		ofs.width(SPECIALTY_WIDTH);
		ofs << specialty;
		ofs.width(GROUP_WIDTH);
		ofs << group;
		ofs.width(GROUP_WIDTH);
		ofs << rating;
		ofs.width(GROUP_WIDTH);
		ofs << attendance;
		return ofs;
	}
};

#define TEACHER_TAKE_PARAMETERS	const std::string& specialty, unsigned int experience
class Teacher :public Human
{
	static const int EXPERIENCE_WIDTH = 3;
	std::string specialty;
	unsigned int experience;
public:
	const std::string& get_specialty()const
	{
		return specialty;
	}
	unsigned int get_experience()const
	{
		return experience;
	}
	void set_specialty(const std::string& specialty)
	{
		this->specialty = specialty;
	}
	void set_experience(unsigned int experience)
	{
		this->experience = experience;
	}

	//				Constructor:
	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_specialty(specialty);
		set_experience(experience);
	}
	~Teacher() {}
	std::ostream& info(std::ostream& os)const override
	{
		Human::info(os);
		os << left;
		os.width(SPECIALTY_WIDTH);
		os << specialty;
		os.width(EXPERIENCE_WIDTH);
		os << experience;
		return os;
	}
	std::ifstream& scan(std::ifstream& ifs) override
	{
		Human::scan(ifs);
		char buffer[SPECIALTY_WIDTH + 1] = {};
		ifs.read(buffer, SPECIALTY_WIDTH);
		for (int i = SPECIALTY_WIDTH - 1; buffer[i] == ' '; i--) buffer[i] = 0;
		specialty = buffer;
		ifs >> experience;
		return ifs;
	}
	std::ofstream& info(std::ofstream& ofs)const override
	{
		Human::info(ofs);
		ofs << left;
		ofs.width(SPECIALTY_WIDTH);
		ofs << specialty;
		ofs.width(8);
		ofs << experience;
		return ofs;
	}
};

class Graduate :public Student
{
	std::string subject;
public:
	const std::string& get_subject()const
	{
		return subject;
	}
	void set_subject(const std::string& subject)
	{
		this->subject = subject;
	}
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, const std::string& subject)
		:Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
	{
		set_subject(subject);
	}
	~Graduate() {}
	std::ostream& info(std::ostream& os)const override
	{
		return Student::info(os) << " " << subject;
	}
	std::ofstream& info(std::ofstream& ofs)const override
	{
		Student::info(ofs) << " " << subject;
		return ofs;
	}
	std::ifstream& scan(std::ifstream& ifs) override
	{
		Student::scan(ifs);
		std::getline(ifs, subject);
		return ifs;
	}
};

template<typename T> void print(T group[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << *group[i] << endl;
		cout << "\n--------------------------------------------\n";
	}
}
template<typename T> void save(T group[], const int n, const char* filename)
{
	std::ofstream fout(filename);
	for (int i = 0; i < n; i++)
	{
		fout << typeid(*group[i]).name() << ":\t";
		fout << *group[i] << endl;
		cout << "\n--------------------------------------------\n";
	}
	fout.close();
}
Human* HumanFactory(const std::string& type)
{
	if (type.find("Student") != std::string::npos) return new Student("", "", 0, 0, 0, "", "", 0, 0);
	if (type.find("Teacher") != std::string::npos) return new Teacher("", "", 0, 0, 0, "", 0);
	if (type.find("Graduate") != std::string::npos) return new Graduate("", "", 0, 0, 0, "", "", 0, 0, "");
}
Human** load(int& n, const char* filename)
{
	std::ifstream fin(filename);
	Human** group = nullptr;
	if (fin.is_open())
	{
		//1) Определяем количество участников группы:
		std::string buffer;
		while (!fin.eof())
		{
			buffer.clear();
			std::getline(fin, buffer);
			if (buffer.size() == 0) continue;
			n++;
		}
		cout << "В группе " << n << " участников\n";

		//2) Выделяем память под массив
		group = new Human*[n]{};

		//3) Возвращаемся в начало файла, чтобы загрузить строки в массив
		cout << "Текущая позиция курсора после чтения файла: " << fin.tellg() << endl;
		fin.clear();
		fin.seekg(0);
		cout << "Теперь курсор должен вернуться в начало файла: " << fin.tellg() << endl;

		//4) Выполняем чтение файла, и загрузку объектов в массив
		for (int i = 0; i < n; i++)
		{
			std::string type;
			std::getline(fin, type, ':');
			if (type.empty()) continue;
			group[i] = HumanFactory(type);
			fin.ignore();
			fin >> *group[i];
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found." << endl;
	}
	return group;
}

void main()
{
	setlocale(LC_ALL, "Russian");

	Human* group[] =
	{
		new Student("Pinkman", "Jessie", 1990, 03,04, "Chemistry", "WW_220", 90, 95),
		new Teacher("White", "Walter", 1960, 9, 20, "Chemistry", 25),
		new Graduate("Schrader", "Hank", 1970, 06,07, "Criminalistic", "WW_220", 75, 80, "How to catch Heizenberg"),
		new Student("Vercetty", "Tomas", 1970, 05, 25, "Criminalistic", "Vice", 90, 95),
		new Teacher("Diaz", "Ricardo", 1960, 03,03, "Weapons distribution", 20)
	};

	char filename[] = "new_group.txt";
	
	print(group, sizeof(group) / sizeof(group[0]));
	save(group, sizeof(group) / sizeof(group[0]), filename);

	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		delete group[i];
	}
	char sz_command[_MAX_FNAME] = "notepad ";
	strcat_s(sz_command, _MAX_FNAME, filename);
	system(sz_command);


	int n = 0;
	Human** load_group = load(n, filename);
	print(load_group, n);
}