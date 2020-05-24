class interrupt_flag
{
public:
    void set(void);
    bool is_set(void) const;
};
thread_local interrupt_flag this_thread_interrupt_flag;

class interruptible_thread
{
public:
    template<typename FunctionType>
    interruptible_thread(FunctionType F)
    {
        std::promise<interrupt_flag*> p;
        internal_thread = std::thread([f, &p])
            {
                p.set_value(&this_thread_interrupt_flag);
                f();
            });
    flag = p.get_future().get();
    }

    void interrupt(void)
    {
        if(flag)
        {
            flag->set();
        }
    }

private:
    std::thread internal_thread;
    interrupt_flag *flag;
};
