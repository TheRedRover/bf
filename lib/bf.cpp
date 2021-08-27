#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

enum commands
{
    MINUS = '-',
    PLUS = '+',
    RIGHT = '>',
    LEFT = '<',
    POINT = '.',
    COMA = ',',
    RIGHT_BRACKET = ']',
    LEFT_BRACKET = '['
};

struct compiller
{    
    struct command
    {
        public:
        virtual void function() = 0;
        virtual ~command(){}
    };

    char cpu[30000]={0};
    std::vector<command *> cmds;
    static std::vector<command *>::iterator cmds_begin;
    static char * head;
    static std::vector<command *>::iterator cur_cmd;

    struct minus : command
    {
        void function()
        {
            (*head)--;
        }
    };

    struct plus : command
    {
        void function()
        {
            (*head)++;
        }
    };

    struct right : command
    {
        void function()
        {
            head++;
        }
    };

    struct left : command
    {
        void function()
        {
            head--;
        }
    };

    struct left_bracket : command
    {
        size_t right_ind;

        void function()
        {
            if(*head == 0)
            {
                cur_cmd = cmds_begin+right_ind;
            }
            else
            {
                cur_cmd++;
            }
        }

        public:
        void set_right_br_ind(size_t ind)
        {
            right_ind = ind;
        }
    };

    struct right_bracket : command
    {
        size_t left_ind;

        void function()
        {
            if(*head != 0)
            {
                cur_cmd = cmds_begin+left_ind;
            }
            else
            {
                cur_cmd++;
            }
        }

        public:
        void set_left_br_ind(size_t ind)
        {
            left_ind = ind;
        }
    };

    struct point : command
    {
        void function()
        {
            std::cout<<*head;
        }
    };

    struct coma : command
    {
        void function()
        {
            
        }
    };

public:
    compiller(std::string str)
    {
        head = cpu;
        std::vector<size_t> i_l_brs;
        for (auto ch:str)
        {
            switch (ch)
            {
                default:
                case MINUS: cmds.push_back(new minus());
                break;
                case PLUS: cmds.push_back(new plus());
                break;
                case RIGHT: cmds.push_back(new right());
                break;
                case LEFT: cmds.push_back(new left());
                break;
                case POINT: cmds.push_back(new point());
                break;
                case RIGHT_BRACKET:
                {
                    auto ptr = new right_bracket();
                    ptr->set_left_br_ind(i_l_brs.back());
                    static_cast<left_bracket* >(cmds[i_l_brs.back()])->set_right_br_ind(cmds.size());
                    i_l_brs.pop_back();
                }
                case LEFT_BRACKET:
                {
                    i_l_brs.push_back(cmds.size());
                    cmds.push_back(new left_bracket());
                }
            }
        }
        cmds_begin = cmds.begin();
        cur_cmd = cmds.begin();
    }

    void execute()
    {
        while(cur_cmd != cmds.end())
        {
            (*cur_cmd)->function();
        }
    }    
};

int main()
{
    compiller c("++++++++++[>+>+++>+++++++>++++++++++<<<<-]>>>++.>+.+++++++..+++.<<++.>+++++++++++++++.>.+++.------.--------.<<+.<.");
    c.execute();
}