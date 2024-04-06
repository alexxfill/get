#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

// Структура для красно-черного дерева
struct Node
{
    int data;
    Node* left; // левый потомок
    Node* right; // правый потомок
    Node* parent;
    bool isRed;

    Node(int value, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr, bool isRed = true)
        : data(value), parent(parent), left(left), right(right), isRed(isRed) {}
};

class RedBlackTree {
public:
    RedBlackTree() : root(nullptr) {}

    // Метод для добавления элемента в дерево
    void insert(int value)
    {
        Node* newNode = new Node(value);
        if (!root)
        {
            root = newNode;
        }
        else
        {
            Node* current = root;
            Node* parent = nullptr;
            while (current)
            {
                parent = current;
                if (value < current->data)
                {
                    current = current->left;
                }
                else
                {
                    current = current->right;
                }
            }
            newNode->parent = parent;
            if (value < parent->data)
            {
                parent->left = newNode;
            }
            else
            {
                parent->right = newNode;
            }
        }
        fixInsertion(newNode);
    }

    // Метод для поиска элемента в дереве
    bool find(int value)
    {
        Node* current = root;
        while (current)
        {
            if (value == current->data)
            {
                return true;
            }
            else if (value < current->data)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        return false;
    }

private:
    Node* root;

    // Метод для балансировки после вставки элемента
    void fixInsertion(Node* h)
    {
        // Пока родитель элемента красный
        while (h != root && h->parent->isRed)
        {
            // Родитель элемента - левый
            if (h->parent == h->parent->parent->left)
            {
                // Дядя - правый (брат родителя)
                Node* uncle = h->parent->parent->right;
                if (uncle && uncle->isRed)
                {
                    h->parent->isRed = false;
                    uncle->isRed = false;
                    h->parent->parent->isRed = true;
                    h = h->parent->parent;
                }

                else
                {
                    // Элемент - правый
                    if (h == h->parent->right)
                    {
                        h = h->parent;
                        rotateLeft(h);
                    }
                    h->parent->isRed = false;
                    h->parent->parent->isRed = true;
                    rotateRight(h->parent->parent);
                }
            }

            else
            {
                // Дядя - левый (брат родителя)
                Node* uncle = h->parent->parent->left;
                if (uncle && uncle->isRed)
                {
                    h->parent->isRed = false;
                    uncle->isRed = false;
                    h->parent->parent->isRed = true;
                    h = h->parent->parent;
                }

                // Элемент - левый
                else
                {
                    if (h == h->parent->left)
                    {
                        h = h->parent;
                        rotateRight(h);
                    }
                    h->parent->isRed = false;
                    h->parent->parent->isRed = true;
                    rotateLeft(h->parent->parent);
                }
            }
        }
        root->isRed = false; // Корень дерева всегда черный
    }

    // Метод для ротации влево (для LR и RL)
    void rotateLeft(Node* h)
    {
        Node* rightChild = h->right;
        h->right = rightChild->left;

        // Если правый потомок элемента обладает левым потомком
        if (rightChild->left)
        {
            rightChild->left->parent = h;
        }
        rightChild->parent = h->parent;

        // Если элемент - корень
        if (h->parent == nullptr)
        {
            root = rightChild;
        }

        // Если элемент - левый
        else if (h == h->parent->left)
        {
            h->parent->left = rightChild;
        }

        else // Если элемент - правый
        {
            h->parent->right = rightChild;
        }
        rightChild->left = h;
        h->parent = rightChild;
    }

    // Метод для ротации вправо (для LL и RR)
    void rotateRight(Node* h)
    {
        Node* leftChild = h->left;
        h->left = leftChild->right;

        // Если левый потомок элемента обладает правым потомком
        if (leftChild->right)
        {
            leftChild->right->parent = h;
        }
        leftChild->parent = h->parent;

        // Если элемент - корень
        if (h->parent == nullptr)
        {
            root = leftChild;
        }

        // Если элемент - правый
        else if (h == h->parent->right)
        {
            h->parent->right = leftChild;
        }

        // Если элемент - левый
        else
        {
            h->parent->left = leftChild;
        }
        leftChild->right = h;
        h->parent = leftChild;
    }
};

int main() {
    // Создание и заполнение контейнеров
    RedBlackTree rbTree;
    vector<int> vec;
    srand(time(0));
    for (int i = 0; i < 500; i++)
    {
        int num = rand() % 10000;
        rbTree.insert(num);
        vec.push_back(num);
    }


    // Сравнение времени поиска элемента
    auto start_t = steady_clock::now();
    for (int i = 0; i < 10000; i++)
    {
        rbTree.find(rand() % 10000);
    }
    auto end_t = steady_clock::now();
    auto rbTreeSearch_time = duration_cast<microseconds>(end_t - start_t);

    start_t = steady_clock::now();
    for (int i = 0; i < 10000; i++)
    {
        find(vec.begin(), vec.end(), rand() % 10000);
    }
    end_t = steady_clock::now();
    auto vecSearch_time = duration_cast<microseconds>(end_t - start_t);

    cout << "Red-Black Tree search time: " << rbTreeSearch_time.count() << " microseconds" << endl;
    cout << "Vector search time: " << vecSearch_time.count() << " microseconds" << endl;


    // Сравнение времени добавления нового элемента
    start_t = steady_clock::now();
    for (int i = 0; i < 10000; i++)
    {
        rbTree.insert(rand() % 10000);
    }
    end_t = steady_clock::now();
    auto rbTreeInsertionTime = duration_cast<microseconds>(end_t - start_t);

    start_t = steady_clock::now();
    for (int i = 0; i < 10000; i++)
    {
        vec.push_back(rand() % 10000);
    }
    end_t = steady_clock::now();
    auto vecInsertionTime = duration_cast<microseconds>(end_t - start_t);

    cout << "Red-Black Tree insertion time: " << rbTreeInsertionTime.count() << " microseconds" << endl;
    cout << "Vector insertion time: " << vecInsertionTime.count() << " microseconds" << endl;

    return 0;
}
