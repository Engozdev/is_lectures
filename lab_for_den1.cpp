// lab_for_den1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    string input, name;//строка для считывания и имя файла
    //name = "text.txt";
    int cl = 0; // количество строк в файле
    int start = 0;//с начала (0) или с конца (1)
    int n = -1;//количество вывлжимых строк (если 0 вывести все)
    char end = '\n';//каким символом заканчивается строка
    for (int i = 1; i < argc; i++) {
        string stem = argv[i];
        if (stem.find(".txt") != (-1)) {
            name = stem;
        }
        else if (stem.find("--l") != (-1)) {
            n = stoi(argv[i + 1]);
        }
        else if (stem.find("-lines") != (-1)) {
            n = stoi(stem.substr(7));
        }
        else if ((stem == "--tail") || (stem == "-t")) {
            start = 1;
        }
        else if (stem == "-d") {
            end = argv[i + 1][0];
        }
        else if (stem.find("--delimiter") != (-1)) {
            end = stem[12];
        }
    }
    //end = 's';
    //cout << "end " <<end;
    ifstream file(name);//файл для считывания
    //if (end == ("/n")) {
        //вывести n первый строк файла
    if ((start == 0) && (n > (-1))) {
        for (int i = 0; i < n; i++) {
            getline(file, input, end);
            cout << input << "\n";
        }
    }
    //вывести весь файл
    else if (n == (-1)) {
        while (getline(file, input, end)) {
            cout << input << "\n";
        }
    }
    // вывести n последних строк
    else if (start == 1) {
        while (getline(file, input, end)) {
            cl += 1;
        }
        file.close();
        ifstream file(name);
        int nom = 0;
        while (getline(file, input, end)) {
            nom += 1;
            if (nom > (cl - n)) {
                cout << input << "\n";
            }
        }
    }
}
    //если конец строки не "\n"
    
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
