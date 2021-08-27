#include <vector>
    class command
    {
        virtual void function() = 0;
    };

    class minus : public command
    {
        void function()
        {

        }
    };

    class plus : command
    {
        void function()
        {
            
        }
    };

    class right : command
    {
        void function()
        {
            
        }
    };

    class left : command
    {
        void function()
        {
            
        }
    };

    class left_bracket : command
    {
        void function()
        {
            
        }
    };

    class right_bracket : command
    {
        void function()
        {
            
        }
    };

int main()
{
    std::vector<command> cmds;
    command * m = & minus();
    cmds.push_back(minus());
}