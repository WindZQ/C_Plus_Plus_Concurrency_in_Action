#include <atomic>

template<typename T>
class lock_free_stack
{
public:
    void push(T const &data)
    {
        node *const new_node = new node(data);
        new_node->next = head.load();
        while(!head.compare_exchange_weak(new_node->next, new_node));
    }

private:
    struct node
    {
        T data;
        node* next;
        node(T const &data_)
            :data(data_)
        {}
    };

    std::atomic<node*> head;
};
