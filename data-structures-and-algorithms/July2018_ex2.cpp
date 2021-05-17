#include <fstream>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

//July 2018, Ex.2

struct Node
{
  char c;
  std::vector<Node*> children;
  
  Node(char c) : c{c} 
  {}
};

std::string readLast(Node* root)
{
  if (!root) return "";

  std::queue<Node*> q;
  Node sentinel{'#'};
  Node* const pSentinel = &sentinel;

  q.push(root);
  q.push(pSentinel);

  std::string word;

  while (q.size() > 1)
  {  // size of 1 means only sentinel is left
    Node* cur = q.front();
    std::cout << "Front of queue: " << cur->c << '\n';
    q.pop();

    if (cur == pSentinel)
    {
      // prepare for next level word
      word.clear();
      q.push(pSentinel);
      std::cout << "Reset on sentinel...\n";
    } 
    else
    {
      word += cur->c;
      for (auto child : cur->children)
      {
        if (child != nullptr) q.push(child);
      }
    }
  }

  return word;
}

void serialize_rec(Node* cur, std::string& str);

void serialize(Node* root, const std::string& file) 
{
  std::ofstream ofs{file};
  if (!ofs) 
  {
    throw std::runtime_error{"Could not open file " + file};
  }

  std::string serialized;
  serialize_rec(root, serialized);
  std::cout << "Serialization: " << serialized << '\n';
  ofs << serialized;
}

void serialize_rec(Node* cur, std::string& str)
{
  if (!cur)
  {
    str += "*";
  } 
  else
  {
    str += "(";
    str += cur->c;
    for (auto child : cur->children)
    {
      serialize_rec(child, str);
    }
    str += ")";
  }
}

int main() 
{
  // create test tree

  // level 0
  Node* b = new Node('b');  // root

  // level 1
  Node* x = new Node('x');
  Node* y = new Node('y');

  // level 2
  Node* p = new Node('p');
  Node* q = new Node('q');
  Node* r = new Node('r');
  Node* s = new Node('s');

  // level 3
  Node* c = new Node('c');
  Node* a = new Node('a');
  Node* t = new Node('t');

  b->children = {x, y, nullptr};

  x->children = {p, q, r};
  y->children = {nullptr, nullptr, s};

  p->children = {nullptr, nullptr, nullptr};
  q->children = {nullptr, nullptr, nullptr};
  r->children = {c, nullptr, a};
  s->children = {nullptr, t, nullptr};

  c->children = {nullptr, nullptr, nullptr};
  a->children = {nullptr, nullptr, nullptr};
  t->children = {nullptr, nullptr, nullptr};

  auto lastLevelWord = readLast(b);
  std::cout << "Last level word: " << lastLevelWord << '\n';
  serialize(b, "serialized.txt");
}