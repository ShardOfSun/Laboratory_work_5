/* 26.Дан целочисленный массив размера N, содержащий большое количество нулевых
элементов. Создать новый массив, заменив все группы подряд встречающихся нулей
на один нуль. */

#include<iostream>
#include<fstream>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::string;

int checkN(string n); // Проверка введеного кол-ва
void mistake(); // Вывод сообщ-я об ошибке
bool contin(); // Интерфейс
void solution(int arrf[], int* arr, int z, int n); // Решение задачи

int main()
{
	setlocale(0, "");

	// Основной цикл прог-мы
	while (true)
	{
		// Чтение файла (не работает краткий путь)
		fstream fin = fstream("D:/Учёба/Технологии программирования/Лабораторная работа 5 (номер 26)/textfile.txt");

		if (!fin)
		{	cout << "Ошибка в чтении файла.";
			break;	}

		// Ввод
		cout << "Сколько элементов из файла поместить в массив?" << endl;
		string inpn;
		getline(cin, inpn);

		// Проверка ввода
		int n = checkN(inpn);
		if (n == 0)
		{	mistake();	continue; }
		if (n == 1)
		{	cout << "Один элемент не является массивом!" << endl;	continue;	}

		int* arrf = new int[n]; // Динам-ский массив (исходный)

		int z = 0; // Счетчик "лишних" нулей

		cout << "Начальный массив:" << endl;
		// Заполнение массива n числами из файла
		for (int i = 0; i < n; ++i)
		{
			// Если конец файла достигнут раньше, чем получили n чисел
			if (fin.eof())
			{	cout << "\nВ файле меньше элементов, чем запрошено." << endl << "Для всего файла:";
				n = i;
				break;	}

			fin >> arrf[i]; // Заполнение массива из файла

			// Определение "лишних" нулей
			if (arrf[i] == 0)
				z++;
			else if (arrf[i] != 0 && arrf[i - 1] == 0)
				z--;

			cout << arrf[i] << " "; // Вывод исходного массива
		}

		int* arr = new int[n - z]; // Дин-ий массив (искомый)

		solution(arrf, arr, z, n); // Решение задачи

		if (contin()) // Интерфейс
			continue;

		// Удаление массивов, закрытие файла, конец основного цикла
		delete[] arrf;
		delete[] arr;
		fin.close();
		break;
	}
	return 0;
}

// Проверка ввода
int checkN(string n)
{
	for (int i = 0; i < n.length(); i++)
	{	if (!isdigit(n[i]) || n[0] == '0')
			return 0;	}

	return atoi(n.c_str());
}

// Решение задачи
void solution(int arrf[], int* arr, int z, int n)
{
	int i = 0, j = 0, c = 0;
	cout << "\nРезультат:" << endl;
	for (; i < n - z; ++i) // Цикл для проходения по искомому массиву
	{
		for (; j < n; ++j) // Цикл для проходения по исходному массиву
		{
			if (arrf[j] != 0 || arrf[j + 1] != 0) // "Если (в исходном массиве) нет двух нулей подряд..."
			{	arr[i] = arrf[j]; // Заполнение искомого массива нужными числами (все, кроме "лишних" нулей - их цикл пропускает)
				cout << arr[i] << " "; // Вывод искомого массива
				c = 1;
				continue;	}
		}
	}

	if (c == 0)
		cout << 0 << endl << "Один элемент не является массивом" << endl;
}

// Интерфейс
bool contin()
{
	while (true)
	{
		string c;
		cout << "\nЗапустить программу сначала (1) / Закрыть программу (0)" << endl;
		getline(cin, c);

		if (c == "0")
		{	return 0;
			cout << "Закрытие программы..." << endl;
			break;	}
		else if (c == "1")
		{	return 1;
			break;	}
		else
		{	mistake();
			continue;	}

		break;
	}
}

// Вывод сообщения об ошибке
void mistake()
{	cout << "Некорректный ввод, попробуйте снова!" << endl << endl;	}