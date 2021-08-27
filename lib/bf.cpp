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
        virtual void function(char * head) = 0;
        virtual ~command(){}
        virtual void print() = 0;
    };

    char cpu[30000]={0};
    std::vector<command *> cmds;
    char * head;
    static std::vector<command *>::iterator cmds_begin;
    static std::vector<command *>::iterator cur_cmd;

    struct minus : command
    {
        void function(char * head)
        {
            (*head)--;
        }

        void print()
        {
            std::cout<<'-';
        }
    };

    struct plus : command
    {
        void function(char * head)
        {
            (*head)++;
        }
        void print()
        {
            std::cout<<'+';
        }
    };

    struct right : command
    {
        void function(char * head)
        {
            head++;
        }
        void print()
        {
            std::cout<<'>';
        }
    };

    struct left : command
    {
        void function(char * head)
        {
            head--;
        }
        void print()
        {
            std::cout<<'<';
        }
    };

    struct left_bracket : command
    {
        size_t right_ind;

        void function(char * head)
        {
            if(*head == 0)
            {
                cur_cmd = ++(cmds_begin+right_ind);
            }
            else
            {
                cur_cmd++;
            }
        }

        void set_right_br_ind(size_t ind)
        {
            right_ind = ind;
        }

        void print()
        {
            std::cout<<'[';
        }
    };

    struct right_bracket : command
    {
        size_t left_ind;

        void function(char * head)
        {
            if(*head != 0)
            {
                cur_cmd = ++(cmds_begin+left_ind);
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

        void print()
        {
            std::cout<<']';
        }
    };

    struct point : command
    {
        void function(char * head)
        {
            std::cout<<*head;
        }
        void print()
        {
            std::cout<<'.';
        }
    };

    struct coma : command
    {
        void function(char * head)
        {
            std::cout<<(char)*head;
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
                default: break;
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
                    break;
                }
                case LEFT_BRACKET:
                {
                    i_l_brs.push_back(cmds.size());
                    cmds.push_back(new left_bracket());
                    break;
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
            (*cur_cmd)->function(head);
            cur_cmd++;
        }

        for(char ch:cpu)
        {
            std::cout<<ch;
        }
    }    
};
std::vector<compiller::command *>::iterator compiller::cmds_begin={};
std::vector<compiller::command *>::iterator compiller::cur_cmd={};


int main()
{
    compiller c("++++++++++[>+>+++>+++++++>++++++++++<<<<-]>>>++.>+.+++++++..+++.<<++.>+++++++++++++++.>.+++.------.--------.<<+.<.");
    c.execute();
}