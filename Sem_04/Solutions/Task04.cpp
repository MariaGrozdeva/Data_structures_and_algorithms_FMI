#include <iostream>
#include <string>

struct Node
{
    std::string data;
    Node* next;

    Node(const std::string& data, Node* next = nullptr) : data(data), next(next) {}
};

void free(Node* iter)
{
    if (!iter)
    {
        return;
    }

    Node* first = iter;
    do
    {
        Node* toDelete = iter;
        iter = iter->next;
        delete toDelete;
    }
    while (iter != first);
}

void print(Node* iter)
{
    if (!iter)
    {
        return;
    }

    Node* first = iter;
    do
    {
        std::cout << iter->data << std::endl;
        iter = iter->next;
    }
    while (iter != first);
}

bool shouldUnite(const std::string& lhs, const std::string& rhs)
{
    if (lhs.empty() || rhs.empty())
    {
        return false;
    }
    return lhs[lhs.size() - 1] == rhs[0];
}

void absorb(Node* lhs, Node* rhs)
{
    lhs->data.append(" -> ");
    lhs->data.append(rhs->data);

    lhs->next = rhs->next;
    delete rhs;
}

void unite(Node* list)
{
    if (!list)
    {
        return;
    }
    
    Node* first = list;
    Node*& lexMin = first;

    bool shouldFinish = false;

    do
    {
        if (list->next == first)
        {
            shouldFinish = true;
        }

        if (list != list->next && shouldUnite(list->data, list->next->data))
        {
            if (list->next == first) // If absorbing the first node
            {
                first = list;
            }
            absorb(list, list->next);
        }
        else
        {
            list = list->next;
            if (list->data < lexMin->data)
            {
                lexMin = list;
            }
        }
    }
    while (!shouldFinish);

    print(lexMin);
    free(lexMin);
}

int main()
{
    Node* f1 = new Node("street");
    Node* f2 = new Node("taxi");
    Node* f3 = new Node("ink");
    Node* f4 = new Node("dog");
    Node* f5 = new Node("smile");
    Node* f6 = new Node("eat");
    Node* f7 = new Node("tall");
    Node* f8 = new Node("pass");

    f1->next = f2;
    f2->next = f3;
    f3->next = f4;
    f4->next = f5;
    f5->next = f6;
    f6->next = f7;
    f7->next = f8;
    f8->next = f1;

    unite(f6);
}
