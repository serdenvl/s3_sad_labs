// s3_sad_lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "just_stack.h"

void do_task(string filename)
{
	fstream input(filename, fstream::in);
	if (!input.is_open())
	{
		throw filename + " didn`t open";
	}

	just_stack s(20);

	s.pop();

	char c;
	for (size_t i = 1; input >> c; ++i)
	{
		switch (c)
		{
		case '(':
			if (s.is_empty())
				throw "unpaired ')' in position " + to_string(i);
			s.push(i);
			break;
		case ')':
			cout << "(" << s.pop() << " : " << i << ") ";
			break;
		}
	}
	input.close();

	if (!s.is_empty())
	{
		string str = "unpaired '(' in positions: ";
		do
		{
			str += to_string(s.pop()) + " ";
		} while (!s.is_empty());
		throw str;
	}
}


int main()
{
	try
	{
		do_task("files/input.txt");
	}
	catch (const char* message)
	{
		cout << "error: " << message;
		getchar();
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
