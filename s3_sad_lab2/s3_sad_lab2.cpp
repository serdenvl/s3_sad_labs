// s3_sad_lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

using val_type = double;

class QueueNode
{
private:
    val_type value;
    QueueNode* next;

    friend class Queue;

public:
    QueueNode(val_type value, QueueNode* next = nullptr) : value(value), next(next)
    {}
};

class Queue
{
private:
    QueueNode* head;
    QueueNode* tail;

public:

    Queue()
    {
        head = nullptr;
        tail = nullptr;
    }

    ~Queue()
    {
        while (!is_empty())
            pop();
    }

    void push(val_type val)
    {
        if (head == nullptr)
        {
            head = tail = new QueueNode(val);
            if (head == nullptr)
                throw "new returned nullptr";
            return;
        }

        tail = tail->next = new QueueNode(val);
        if (tail == nullptr)
            throw "new returned nullptr";
    }

    val_type pop()
    {
        if (is_empty())
        {
            throw "pop() when queue is empty";
        }

        val_type res = head->value;

        delete exchange(head, head->next);
        if (head == nullptr)
            tail = nullptr;

        return res;
    }

    val_type front() const
    {
        if (is_empty())
        {
            throw "front() when queue is empty";
        }

        return head->value;
    }

    bool is_empty() const
    {
        return head == nullptr;
    }
};

void do_task(string filename)
{
    fstream input(filename, fstream::in);
    if (!input.is_open())
    {
        throw filename + " didn`t open";
    }

    // init

    Queue X = Queue();
    Queue Y = Queue();

    size_t length;
    double buffer;

    cout << "Input: " << endl;

    cout << "Queue X: ";
    input >> length;
    for (size_t i = 0; i < length; ++i)
    {
        input >> buffer;
        X.push(buffer);

        cout << buffer << " ";
    }
    cout << endl;

    cout << "Queue Y: ";
    input >> length;
    for (size_t i = 0; i < length; ++i)
    {
        input >> buffer;
        Y.push(buffer);

        cout << buffer << " ";
    }
    cout << endl;

    cout << endl;

    // do

    cout << "Output: " << endl;

    size_t count = 0;

    while (!X.is_empty() && !Y.is_empty())
    {
        if (X.front() < Y.front())
            X.push(X.pop() + Y.pop());
        else
            Y.push(X.pop() - Y.pop());

        ++count;
    }

    cout << "The number of iterations: " << count << endl;
}

int main()
{
    try
    {
        do_task("input.txt");
    }
    catch (const char* message)
    {
        cout << "error: " << message;
        getchar();
    }
}