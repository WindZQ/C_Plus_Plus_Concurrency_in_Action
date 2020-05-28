namespace messaging
{
    class receiver
    {
        queue q;
    public:
        operator sender(void)
        {
            return sender(&q);
        }

        dispatcher wait(void)
        {
            return dispatcher(&q);
        }
    };
}
