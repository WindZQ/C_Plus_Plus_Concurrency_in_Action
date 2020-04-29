#include <string>
#include <mutex>

class some_data
{
    int a;
    std::string b;
public:
    void do_something()
    {}
};

class data_wrapper
{
public:
    template<typename Function>
    void process_data(Function func)
    {
        std::lock_guard<std::mutex> l(m);
        func(data);
    }

private:
    some_data data;
    std::mutex m;
};

some_data *unprotected;
void malicious_function(some_data &process_data)
{
    unprotected = &process_data;
}

data_wrapper x;
void foo(void)
{
    x.process_data(malicious_function);
    unprotected->do_something();
}

int main(void)
{
    foo();

    return 0;
}
