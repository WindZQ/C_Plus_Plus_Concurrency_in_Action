class X
{
public:
    X(): data(new int[1000000])
        {}

    ~X(void)
    {
        delete []data;
    }

    X(const X& other): data(new int[1000000])
    {
        std::copy(other.data, other.data + 1000000, data);
    }

    X(X&& other) : data(other.data)
    {
        other.data = nullptr;
    }
};
