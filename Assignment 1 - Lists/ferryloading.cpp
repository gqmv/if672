/**
 * Except where otherwise noted, the following code is licensed under the Creative Commons Attribution 4.0 International license (CC BY 4.0):
 * http://creativecommons.org/licenses/by/4.0/
 * Copyright 2021 Gabriel Vieira
 * https://github.com/gqmv
 *
 * Whenever using, citing, or modifying this work, be sure to include a copy of the license and this notice.
 */

#include <iostream>

using namespace std;

struct Car
{
    int length;

    Car(int length)
    {
        this->length = length;
    }

    Car()
    {
        this->length = 0;
    }
};

template <typename T>
class Queue
{
private:
    struct Node
    {
        T data;
        Node *next;

        Node(T data)
        {
            this->data = data;
            this->next = nullptr;
        }
    };

    int size;
    Node *front;
    Node *rear;

public:
    Queue()
    {
        this->size = 0;
        this->front = nullptr;
        this->rear = nullptr;
    }

    int getSize()
    {
        return this->size;
    }

    void enqueue(T data)
    {
        Node *newNode = new Node(data);

        if (this->size == 0)
        {
            this->front = newNode;
            this->rear = newNode;
        }
        else
        {
            this->rear->next = newNode;
            this->rear = newNode;
        }

        this->size++;
    }

    T dequeue()
    {
        if (this->size == 0)
        {
            throw "Queue is empty";
        }

        T data = this->front->data;
        Node *temp = this->front;
        this->front = this->front->next;
        this->size--;

        delete temp;

        return data;
    }

    T peek()
    {
        return this->front->data;
    }
};

int main()
{
    int test_case_count;
    cin >> test_case_count;

    for (int i = 0; i < test_case_count; i++)
    {
        int ferry_length, car_count;
        cin >> ferry_length >> car_count;

        ferry_length = ferry_length * 100;

        Queue<Car> left;
        Queue<Car> right;

        for (int j = 0; j < car_count; j++)
        {
            int car_length;
            string car_side;
            cin >> car_length >> car_side;

            if (car_side == "left")
            {
                left.enqueue(Car(car_length));
            }
            else
            {
                right.enqueue(Car(car_length));
            }
        }

        int river_crosses = 0;
        bool left_side = true;

        while (left.getSize() > 0 || right.getSize() > 0)
        {
            Queue<Car> *queue;

            if (left_side)
            {
                queue = &left;
            }
            else
            {
                queue = &right;
            }

            if (queue->getSize() > 0)
            {
                Car front = queue->peek();
                int used_length = 0;
                while (used_length + front.length <= ferry_length)
                {
                    used_length += front.length;
                    queue->dequeue();
                    if (queue->getSize() == 0)
                    {
                        break;
                    }
                    front = queue->peek();
                }
            }

            left_side = !left_side;
            river_crosses++;
        }

        cout << river_crosses << endl;
    }
}