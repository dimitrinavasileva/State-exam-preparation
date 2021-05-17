#include <fstream>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

//July2016, Ex.2

struct Node
{
    Node(int data) : data{ data }
    {}

    int data;
    std::vector<Node*> children;

    bool isLeaf() const
    {
        return children.empty();
    }
};

Node* generateTree(std::ifstream& ifs, Node* current);

Node* readTreeFromFile(const std::string& file)
{
    std::ifstream ifs{ file };
    if (!ifs)
    {
        throw std::runtime_error{ "Could not open file!" };
    }

    char c;
    ifs >> c;

    if (c != '(') throw std::runtime_error{ "Wrong input" };

    int data;
    ifs >> data;

    if (!ifs)  // means we have only ()
    {
        return nullptr;
    }

    Node* root = new Node{ data };  // we have read for example (5
    generateTree(ifs, root);
    return root;
}

Node* generateTree(std::ifstream& ifs, Node* current)
{
    int data;
    ifs >> data;

    if (const bool numberReadSuccessfully = static_cast<bool>(ifs))
    {
        char bracket;
        ifs >> bracket;
        // always '(' after a number
        if (bracket != '(') throw std::runtime_error("Wrong input");
        auto node = new Node{ data };
        generateTree(ifs, node);
        return node;
    }

    ifs.clear();

    char c;
    ifs >> c;

    while (c != ')' && ifs)
    {
        auto child = generateTree(ifs, current);
        if (child)
        {
            current->children.push_back(child);
        }
        ifs >> c;
    }

    ifs >> c;  // reads the ')'
    return nullptr;
}

void print(Node* root)
{
    if (root && !root->isLeaf())
    {
        for (auto child : root->children)
        {
            std::cout << root->data << " -> " << child->data << std::endl;
            print(child);
        }
    }
}

void maxSumRec(Node* node, int& currentMax, int currentSum);

int maxSum(Node* root)
{
    if (!root)
    {
        throw std::runtime_error{ "Invalid tree" };
    }

    int max = -99999;
    maxSumRec(root, max, 0);
    return max;
}

void maxSumRec(Node* node, int& currentMax, int currentSum)
{
    currentSum += node->data;
    if (node->isLeaf())
    {
        if (currentSum > currentMax)
        {
            currentMax = currentSum;
        }
    }
    else
    {  // not a leaf
        for (auto child : node->children)
        {
            maxSumRec(child, currentMax, currentSum);
        }
    }
}

int main()
{
    Node* root1 = readTreeFromFile("test_tree1");
    Node* root2 = readTreeFromFile("test_tree2");
    //   print(root1);
    //   print(root2);
    std::cout << maxSum(root1) << '\n';
    std::cout << maxSum(root2) << '\n';
}