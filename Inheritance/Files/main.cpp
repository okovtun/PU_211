#define _CRT_SECURE_NO_WARNINGS
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

	const int NUMBER_SIZE = 20;
	char room_number[NUMBER_SIZE];
	char sz_source_filename[FILENAME_MAX] = {};
	char sz_ready_filename[FILENAME_MAX] = {};
	
	cout << "������� ����� ���������: "; cin >> room_number;
	strcat(sz_source_filename, room_number);
	strcat(sz_ready_filename, room_number);

	strcat(sz_source_filename, " RAW.txt");
	strcat(sz_ready_filename, " ready.txt");

	const int IP_BUFFER_SIZE = 16;
	const int MAC_BUFFER_SIZE = 18;
	char sz_ip_buffer[IP_BUFFER_SIZE] = {};
	char sz_mac_buffer[MAC_BUFFER_SIZE] = {};

	std::ofstream fout(sz_ready_filename);
	std::ifstream fin(sz_source_filename);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			//TODO: exchange
			fin >> sz_ip_buffer >> sz_mac_buffer;
			fout << sz_mac_buffer << "\t" << sz_ip_buffer << endl;
			cout << sz_mac_buffer << "\t" << sz_ip_buffer << endl;
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
	fout.close();

	char sz_command[FILENAME_MAX] = "notepad ";
	strcat(sz_command, sz_ready_filename);
	system(sz_command);
}