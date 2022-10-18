// s3_sad_lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

using ind = size_t;
using val_type = int;

static const ind nullind = 0;

class List
{
private:
    val_type value;
    List* next;

    List(const val_type value, List* next) : value(value), next(next) {}

    List* get_item(ind index)
    {
        List* item = this;
        for (ind i = 0; i < index && item; ++i)
            item = item->next;

        if (item == nullptr)
            throw "index is out of range";

        return item;
    }

public:
    List() : value(0), next(nullptr) {}

    ~List()
    {
        while (next != nullptr)
            remove(1);
    }

    void insert_after(ind index, const val_type value)
    {
        List* item = get_item(index);
        item->next = new List(value, item->next);

        if (next == nullptr)
            throw "new returned nullptr";
    }

    val_type remove(ind index)
    {
        if (index == nullind)
            throw "index is out of range";

        List* item = get_item(index-1);

        if (item->next == nullptr)
            throw "index is out of range";

        val_type val = item->next->value;

        delete exchange(item->next, exchange(item->next->next, nullptr));

        return val;
    }

    val_type get(ind index)
    {
        if (index == nullind)
            throw "index is out of range";

        return get_item(index)->value;
    }

    ind find(val_type value) const
    {
        ind i = 1;
        for (List* item = this->next; item != nullptr; item = item->next, ++i)
            if (item->value == value)
                return i;
        return nullind;
    }

    bool is_empty() const
    {
        return next == nullptr;
    }
};

void init_list(List& list, const string filename, bool with_cout_values = false, string name = "list")
{
    fstream input(filename, fstream::in);
    if (!input.is_open())
    {
        throw filename + " didn`t open";
    }

    cout << name << " : " << "[ ";

    val_type buffer;
    while(input >> buffer)
    {
        list.insert_after(0, buffer);
        cout << buffer << " ";
    }

    cout << "]" << endl;
}

void do_task(const string filenameA, const string filenameB)
{
    List listA, listB;

    cout << "Input: " << endl;

    init_list(listA, filenameA, true, "list A");
    init_list(listB, filenameB, true, "list B");

    cout << endl;

    List res;
    val_type val;
    ind index = nullind;

    while (!listA.is_empty())
    {
        val = listA.remove(1);
        index = listB.find(val);

        if (!index)
        {
            res.insert_after(0, val);
            continue;
        }

        for (; index; index = listB.find(val))
            listB.remove(index);

        for (index = listA.find(val); index; index = listA.find(val))
            listA.remove(index);
    }

    while (!listB.is_empty())
    {
        res.insert_after(0, listB.remove(1));
    }

    cout << "Output: " << endl;
    cout << "[ ";

    while(!res.is_empty())
        cout << res.remove(1) << " ";

    cout << "]" << endl;
}

int main()
{
    try
    {
        do_task("input1.txt", "input2.txt");
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
