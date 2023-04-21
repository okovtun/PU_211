#include<iostream>
#include<fstream>
using namespace std;

//#define WRITE_TO_FILE
//#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");

#ifdef WRITE_TO_FILE
	//1) ������� ����� ������ (������ � ����):
	ofstream fout;

	//2) ��������� �����. ������� ����� ����� ��� ����, ����� ��������, � ����� ��������� ���� �� �����:
	fout.open("File.txt", std::ios_base::app);	//���� std::ios_base::app ��������� ��������� ���������� � ����.
	//���� - ��� �������. ��� �������, ��� ���, ������� ����� ���� ����������, ��� �������.

	//3) ������� (����������) ���������� � ����:
	fout << "Hello Files!" << endl;

	//4) ������ ����������� ����� ���������! 
	//������ ��������� ������ ���������, ��� ����� �������� � �������������� ������������!!!
	fout.close();

	system("notepad File.txt");
#endif // WRITE_TO_FILE

#ifdef READ_FROM_FILE
	//0) ��������� ����� ������:
	const int SIZE = 256;
	char buffer[SIZE] = {};

	//1) ������� � ��������� �����:
	ifstream fin("File.txt");
	//2) ���������, �������� �� �����:
	if (fin.is_open())
	{
		//3) ���� ����� ��������, ������ ����:
		while (!fin.eof())//���� �� ����� �����
		{
			//fin >> buffer;
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}
		//4) ��������� ����� ������ � ��� ������, ���� �� ��������
		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
#endif // READ_FROM_FILE


}