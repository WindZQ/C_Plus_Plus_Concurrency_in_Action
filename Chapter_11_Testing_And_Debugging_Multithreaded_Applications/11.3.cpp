class CX
{
public:
    CX() = default;
    CX(int a_, int b_) : a(a_), b(b_)
    {}

    int get_a(void) const
    {
        return a;
    }

    int get_b(void) const
    {
        return b;
    }

    int foo(void) const
    {
        return a + b;
    }
};
