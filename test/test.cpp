#include <cstddef>
#include <exception>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

const size_t BUF_SIZE = 30000;

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
    
    std::vector<command *> cmds;
    static int head;
    static char cpu[BUF_SIZE];
    static std::vector<command *>::iterator cmds_begin;
    static std::vector<command *>::iterator cur_cmd;

    struct minus : command
    {
        void function() override
        {
            --cpu[head];
        }
    };

    struct plus : command
    {
        void function() override
        {
            ++cpu[head];
        }
    };

    struct right : command
    {
        void function() override
        {
            if(++head>=BUF_SIZE)
                throw std::range_error("Head position is bigger than buffer");
        }
    };

    struct left : command
    {
        void function() override
        {
            if(--head<0)
                throw std::range_error("Head position is less than buffer");
        }
    };

    struct left_bracket : command
    {
        size_t right_ind;

        void function() override
        {
            if(cpu[head] == 0)
            {
                cur_cmd = cmds_begin+right_ind;
            }
        }

        void set_right_br_ind(size_t ind)
        {
            right_ind = ind;
        }
    };

    struct right_bracket : command
    {
        size_t left_ind;

        void function() override
        {
            if(cpu[head] != 0)
            {
                cur_cmd = (cmds_begin+left_ind);
            }
        }

        void set_left_br_ind(size_t ind)
        {
            left_ind = ind;
        }
    };

    struct point : command
    {
        void function() override
        {
            std::cout<<cpu[head];
        }
    };

    struct coma : command
    {
        void function()
        {
            std::cout<<"";
        }
    };

    compiller(std::string str)
    {
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
                    if(i_l_brs.empty())
                        throw std::logic_error("Left bracket '[' is missing");
                    auto ptr = new right_bracket();
                    ptr->set_left_br_ind(i_l_brs.back());
                    static_cast<left_bracket* >(cmds[i_l_brs.back()])->set_right_br_ind(cmds.size());
                    cmds.push_back(ptr);
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
        if(i_l_brs.size()>0)
        {
            throw std::logic_error("Right bracket ']' is missing");
        }
        cmds_begin = cmds.begin();
        cur_cmd = cmds.begin();
    }

    void execute()
    {
        while(cur_cmd != cmds.end())
        {
            (*cur_cmd)->function();
            cur_cmd++;
        }
    }

    virtual ~compiller()
    {
        for(auto cmd:cmds)
        {
            delete cmd;
        }
    }  
};
int compiller::head = 0;
char compiller::cpu[BUF_SIZE]={0};
std::vector<compiller::command *>::iterator compiller::cmds_begin={};
std::vector<compiller::command *>::iterator compiller::cur_cmd={};


int main(int argc, char *argv[])
{

    
    compiller c(">+++++++++++++++[<+>>>>>>>>++++++++++<<<<<<<-]>+++++[<+++++++++>-]+>>>>>>+[<<+++[>>[-<]<[>]<-]>>[>+>]<[<]>]>[[->>>>+<<<<]>>>+++>-]<[<<<<]<<<<<<<<+[->>>>>>>>>>>>[<+[->>>>+<<<<]>>>>>]<<<<[>>>>>[<<<<+>>>>-]<<<<<-[<<++++++++++>>-]>>>[<<[<+<<+>>>-]<[>+<-]<++<<+>>>>>>-]<<[-]<<-<[->>+<-[>>>]>[[<+>-]>+>>]<<<<<]>[-]>+<<<-[>>+<<-]<]<<<<+>>>>>>>>[-]>[<<<+>>>-]<<++++++++++<[->>+<-[>>>]>[[<+>-]>+>>]<<<<<]>[-]>+>[<<+<+>>>-]<<<<+<+>>[-[-[-[-[-[-[-[-[-<->[-<+<->>]]]]]]]]]]<[+++++[<<<++++++++<++++++++>>>>-]<<<<+<->>>>[>+<<<+++++++++<->>>-]<<<<<[>>+<<-]+<[->-<]>[>>.<<<<[+.[-]]>>-]>[>>.<<-]>[-]>[-]>>>[>>[<<<<<<<<+>>>>>>>>-]<<-]]>>[-]<<<[-]<<<<<<<<]++++++++++.");
    c.execute();
}