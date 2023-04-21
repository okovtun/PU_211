#include<iostream>
#include<fstream>
using namespace std;

//#define WRITE_TO_FILE
//#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");

#ifdef WRITE_TO_FILE
	//1) Создаем поток вывода (записи в файл):
	ofstream fout;

	//2) Открываем поток. Открыть поток нужно для того, чтобы показать, в какой конкретно файл мы пишем:
	fout.open("File.txt", std::ios_base::app);	//Флаг std::ios_base::app позволяет добавлять содержимое в файл.
	//Флаг - это признак. Как правило, это бит, который может быть установлен, или сброшен.

	//3) Выводим (записываем) информацию в файл:
	fout << "Hello Files!" << endl;

	//4) Потоки обязательно нужно закрывать! 
	//Нельзя оставлять потоки открытыми, это может привести к непредвиденным последствиям!!!
	fout.close();

	system("notepad File.txt");
#endif // WRITE_TO_FILE

#ifdef READ_FROM_FILE
	//0) Объявляем буфер чтения:
	const int SIZE = 256;
	char buffer[SIZE] = {};

	//1) Создаем и открываем поток:
	ifstream fin("File.txt");
	//2) Проверяем, открылся ли поток:
	if (fin.is_open())
	{
		//3) Если поток открылся, читаем файл:
		while (!fin.eof())//Пока НЕ конец файла
		{
			//fin >> buffer;
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}
		//4) Закрываем поток только в том случае, если он открылся
		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
#endif // READ_FROM_FILE


}