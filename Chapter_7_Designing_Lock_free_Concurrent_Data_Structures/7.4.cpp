#include <atomic>
#include <memory>

template<typename T>
class lock_free_stack
{
public:
    std::shared_ptr<T> pop(void)
    {
        ++threads_in_pop;
        node *old_head = head.load();
        while(old_head && !head.compare_exchange_weak(old_head, old_head->next));
        std::shared_ptr<T> res;
        if(old_head)
        {
            res.swap(old_head->data);
        }
        try_reclaim(old_head);
        returnres;
    }

private:
    std::atomic<unsigned> threads_in_pop;
    void try_reclaim(node *old_head);
};
