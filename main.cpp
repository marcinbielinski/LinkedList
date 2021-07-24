#include <memory>
#include <iostream>

template <typename T> class LinkedList;
template <typename T> std::ostream& operator << (std::ostream&, const LinkedList<T>&);

template <typename T>
struct Node
{
    Node(T arg1, std::unique_ptr<Node> arg2) :
                data(std::move(arg1)), next_node(std::move(arg2)){};
    T data;
    std::unique_ptr<Node> next_node;
};

template <typename T>
class LinkedList
{
public:
    LinkedList() = default;

    void insert_back(T param)
    {
        if (!head_node)
        {
            head_node = std::make_unique<Node<T>>(param, nullptr);
        }
        else
        {
            Node<T>* current_node = head_node.get();
            while (current_node->next_node != nullptr)
            {
                current_node = current_node->next_node.get();
            }
            current_node->next_node = std::make_unique<Node<T>>(param, nullptr);
        }
    }

    void insert_after_N(T param, T N)
    {
        Node<T>* current_node = head_node.get();
        while (current_node != nullptr)
        {
            if (current_node->data != N)
            {
                current_node = current_node->next_node.get();
            }
            else
            {
                break;
            }
        }
        if (current_node->data == N) {
            std::unique_ptr<Node<T>> temp = std::move(current_node->next_node);

            std::unique_ptr<Node<T>> new_node =
                    std::make_unique<Node<T>>(param, std::move(temp));
            current_node->next_node = std::move(new_node);
        }
    }

    void insert_front(T param)
    {
        if (!head_node)
        {
            head_node = std::make_unique<Node<T>>(param, nullptr);
        }
        else
        {
            std::unique_ptr<Node<T>> new_node =
                    std::make_unique<Node<T>>(param, std::move(head_node));
            head_node = std::move(new_node);
        }
    }

    void delete_front()
    {
        if (!head_node)
        {
            std::cout << "List is empty!" << std::endl;
        }
        else
        {
            std::unique_ptr<Node<T>> temporary_node = std::move(head_node);
            head_node = std::move(temporary_node->next_node);
        }

    }

    [[maybe_unused]] void print_list()
    {
        if (!head_node)
        {
            std::cout << "List is empty!" << std::endl;
        }
        else
        {
            Node<T>* current_node = head_node.get();
            while (current_node != nullptr)
            {
                std::cout << current_node->data << std::endl;
                current_node = current_node->next_node.get();
            }
        }
    }

    // overload ostream operator<< declaration
    friend std::ostream& operator<< <T>(std::ostream& os, const LinkedList<T>& list);

    void clean()
    {
        std::cout << "Performing clean-up!" << std::endl;
        while (head_node)
        {
            head_node = std::move(head_node->next_node);
        }
    }
    ~LinkedList()
    {
        clean();
    }

private:
    std::unique_ptr<Node<T>> head_node;
};

// overloaded ostream operator << definition
template <typename T>
std::ostream& operator<< (std::ostream& os, const LinkedList<T>& list)
{
    Node<T>* head_node = list.head_node.get();
    while (head_node)
    {
        if (head_node->next_node != nullptr)
        {
            os << head_node->data << '-';
            head_node = head_node->next_node.get();
        }
        else
        {
            os << head_node->data;
            head_node = head_node->next_node.get();
        }
    }
    return os;
}

int main() {
    LinkedList<int> list1;
    list1.insert_back(10);
    list1.insert_back(20);
    list1.insert_back(30);
    std::cout << list1 << std::endl;

    for (int i = 0; i < 10; ++i)
    {
        list1.insert_front(i);
    }
    std::cout << list1 << std::endl;

    list1.insert_front(100);
    std::cout << list1 << std::endl;

    list1.insert_after_N(50, 100);
    std::cout << list1 << std::endl;

    list1.delete_front();
    std::cout << list1 << std::endl;

//    list1.print_list();
    return 0;
}
