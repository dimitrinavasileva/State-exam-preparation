#include <iostream>

// July 2017, Ex. 2

struct Node
{
    Node(int data) : data{ data } {}
    int data;
    Node* next = nullptr;
};

void sortList(Node* first)
{
    // do nothing if there are only 0 or 1 elements
    if (!first || !first->next) return;

    // selection sort
    Node* i = first;
    while (i)
    {
        Node* min = i;
        Node* j = i->next;
        while (j) 
        {
            if (j->data < min->data)
            {
                min = j;
            }

            j = j->next;
        }

        // swap two values
        int temp = i->data;
        i->data = min->data;
        min->data = temp;

        i = i->next;
    }
}

void print(Node* first)
{
    while (first)
    {
        std::cout << first->data << ' ';
        first = first->next;
    }
    std::cout << '\n';
}

int main()
{
    Node* n1 = new Node{ 5 };
    Node* n2 = new Node{ 3 };
    Node* n3 = new Node{ 4 };
    Node* n4 = new Node{ 1 };
    Node* n5 = new Node{ 2 };

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;

    print(n1);
    sortList(n1);
    print(n1);
}
