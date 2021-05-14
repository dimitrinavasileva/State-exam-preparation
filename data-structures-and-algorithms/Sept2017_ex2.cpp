#include <iostream>

// September 2017, Ex.2

template <typename T>
struct Node
{
    Node(const T& data) : data{ data } {}
    T data;
    Node* next;
};

template <typename T>
void addElem(Node<T>*& list, const T& newElem)
{
    if (!list)
    {
        list = new Node<T>{ newElem };
        return;
    }

    Node<T>* it = list;
    while (it->next)
    {
        it = it->next;
    }

    // it->next == nullptr
    it->next = new Node<T>{ newElem };
    it->next->next = nullptr;
}

// Add add elements from l2 to l1
template <typename T>
void addAll(Node<T>*& l1, Node<T>* l2)
{
    if (!l2) return;

    auto l2_it = l2;
    while (l2_it)
    {
        addElem(l1, l2_it->data);
        l2_it = l2_it->next;
    }
}

// Merge two sorted lists into one newly created
template <typename T>
Node<T>* merge(Node<T>* l1, Node<T>* l2)
{
    Node<T>* result = nullptr;

    if (!l1)
    {
        addAll(result, l2);
        return result;
    }
    if (!l2)
    {
        addAll(result, l1);
        return result;
    }

    while (l1 && l2) {
        if (l1->data <= l2->data)
        {
            addElem(result, l1->data);
            l1 = l1->next;
        }
        else
        {
            addElem(result, l2->data);
            l2 = l2->next;
        }
    }

    // Add remaning elements if any
    addAll(result, l1);
    addAll(result, l2);

    return result;
}

template <typename T>
bool isSorted(Node<T>* list)
{
    if (!list || !list->next) return true;

    auto it1 = list;
    auto it2 = it1->next;

    while (it2)
    {
        if (it1->data > it2->data) return false;
        it1 = it2;
        it2 = it2->next;
    }

    return true;
}

// Merge all sorted lists into one resulting in a newly created sorted list.
Node<int>* mergeSorted(Node<Node<int>*>* lists)
{
    Node<int>* result = nullptr;

    while (lists)
    {
        auto currentList = lists->data;
        if (isSorted(currentList))
        {
            auto tempResult = result;
            result = merge(result, currentList);
            delete tempResult; // avoid memory leaks
        }
        lists = lists->next;
    }

    return result;
}

// Prints list of int
void print(Node<int>* xs)
{
    std::cout << "[ ";
    while (xs != nullptr)
    {
        std::cout << xs->data << ' ';
        xs = xs->next;
    }
    std::cout << "]\n";
}

// Prints list of lists of int
void print(Node<Node<int>*>* lists) {
    while (lists != nullptr) {
        print(lists->data);
        lists = lists->next;
    }
}

int main()
{
    Node<int>* l1 = nullptr;  // sorted
    addElem(l1, 1);
    addElem(l1, 8);
    addElem(l1, 11);

    Node<int>* l2 = nullptr;  // not sorted
    addElem(l2, 4);
    addElem(l2, 6);
    addElem(l2, 5);

    Node<int>* l3 = nullptr;  // sorted
    addElem(l3, 3);
    addElem(l3, 4);
    addElem(l3, 18);

    Node<int>* l4 = nullptr;  // sorted
    addElem(l4, 5);
    addElem(l4, 20);
    addElem(l4, 25);

    Node<Node<int>*>* lists = nullptr;
    addElem(lists, l1);
    addElem(lists, l2);
    addElem(lists, l3);
    addElem(lists, l4);

    print(lists);
    std::cout << "After merging sorted: ";
    print(mergeSorted(lists));  // should print [ 1 3 4 5 8 11 18 20 25 ]
}
