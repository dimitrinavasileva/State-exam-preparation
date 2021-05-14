#include <iostream>
#include <queue>
#include <vector>

// September 2016, Ex.2

struct Node
{
    Node(int data) : data{ data } {}
    int data;
    std::vector<Node*> children;
};

Node* buildTree(int K, const std::vector<int>& A)
{
    if (A.empty()) return nullptr;

    Node* root = new Node{ A[0] };
    int nextToProcess = 1;

    std::queue<Node*> waitingForChildrenQueue;  // holds Nodes waiting for their
                                                // children to be added

    waitingForChildrenQueue.push(root);

    while (!waitingForChildrenQueue.empty() && nextToProcess < A.size())
    {
        Node* cur = waitingForChildrenQueue.front();
        waitingForChildrenQueue.pop();

        for (int i = 0; i < K; i++)
        {
            Node* newChild = new Node{ A[nextToProcess] };
            ++nextToProcess;
            cur->children.push_back(newChild);
            if (nextToProcess == A.size()) return root;
            waitingForChildrenQueue.push(newChild);
        }
    }

    return root;
}

void print(Node* node)
{
    if (!node)
    {
        std::cout << "()";
        return;
    }

    std::cout << " ( " << node->data;

    for (Node* child : node->children)
    {
        print(child);
    }

    std::cout << " ) ";
}

int main()
{
    const std::vector<int> A{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    constexpr int K = 3;
    Node* tree = buildTree(K, A);

    print(tree);
}