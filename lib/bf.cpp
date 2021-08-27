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
    static char * head;
    static std::vector<command *>::iterator cmds_begin;
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
            ++head;
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
        }

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
        void function()
        {
            std::cout<<(char)(*head);
        }
    };

    struct coma : command
    {
        void function()
        {
            std::cout<<"";
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
        cmds_begin = cmds.begin();
        cur_cmd = cmds.begin();
    }

    void execute()
    {
        do
        {
            (*cur_cmd)->function();
            cur_cmd++;
        }
        while(cur_cmd != cmds.end());
    }

    virtual ~compiller()
    {
        for(auto cmd:cmds)
        {
            delete cmd;
        }
    }  
};
char * compiller::head = nullptr;
std::vector<compiller::command *>::iterator compiller::cmds_begin={};
std::vector<compiller::command *>::iterator compiller::cur_cmd={};


int main()
{
    compiller c("[       99 bottles in 1752 brainfuck instructions          ][       by jim crawford (http://www.goombas.org/)          ]>++++++++++[<++++++++++>-]<->>>>>+++[>+++>+++<<-]<<<<+<[>[>+>+<<-]>>[-<<+>>]++++>+<[-<->]<[[-]>>-<<]>>[[-]<<+>>]<<[[-]>>>>>>[[-]<++++++++++<->>]<-[>+>+<<-]>[<+>-]+>[[-]<->]<<<<<<<<<->>]<[>+>+<<-]>>[-<<+>>]+>+<[-<->]<[[-]>>-<<]>>[[-]<<+>>]<<<[>>+>+<<<-]>>>[-<<<+>>>]++>+<[-<->]<[[-]>>-<<]>>[[-]<<+>>]<<[>+<[-]]<[>>+<<[-]]>>[<<+>>[-]]<<<[>>+>+<<<-]>>>[-<<<+>>>]++++>+<[-<->]<[[-]>>-<<]>>[[-]<<+>>]<<[>+<[-]]<[>>+<<[-]]>>[<<+>>[-]]<<[[-]>>>++++++++[>>++++++<<-]>[<++++++++[>++++++<-]>.<++++++++[>------<-]>[<<+>>-]]>.<<++++++++[>>------<<-]<[->>+<<]<++++++++[<++++>-]<.>+++++++[>+++++++++<-]>+++.<+++++[>+++++++++<-]>.+++++..--------.-------.++++++++++++++>>[>>>+>+<<<<-]>>>>[-<<<<+>>>>]>+<[-<->]<[[-]>>-<<]>>[[-]<<+>>]<<<<[>>>+>+<<<<-]>>>>[-<<<<+>>>>]+>+<[-<->]<[[-]>>-<<]>>[[-]<<+>>]<<<[>>+<<[-]]>[>+<[-]]++>>+<[-<->]<[[-]>>-<<]>>[[-]<<+>>]<+<[[-]>-<]>[<<<<<<<.>>>>>>>[-]]<<<<<<<<<.>>----.---------.<<.>>----.+++..+++++++++++++.[-]<<[-]]<[>+>+<<-]>>[-<<+>>]+>+<[-<->]<[[-]>>-<<]>>[[-]<<+>>]<<<[>>+>+<<<-]>>>[-<<<+>>>]++++>+<[-<->]<[[-]>>-<<]>>[[-]<<+>>]<<[>+<[-]]<[>>+<<[-]]>>[<<+>>[-]]<<[[-]>++++++++[<++++>-]<.>++++++++++[>+++++++++++<-]>+.-.<<.>>++++++.------------.---.<<.>++++++[>+++<-]>.<++++++[>----<-]>++.+++++++++++..[-]<<[-]++++++++++.[-]]<[>+>+<<-]>>[-<<+>>]+++>+<[-<->]<[[-]>>-<<]>>[[-]<<+>>]<<[[-]++++++++++.>+++++++++[>+++++++++<-]>+++.+++++++++++++.++++++++++.------.<++++++++[>>++++<<-]>>.<++++++++++.-.---------.>.<-.+++++++++++.++++++++.---------.>.<-------------.+++++++++++++.----------.>.<++++++++++++.---------------.<+++[>++++++<-]>..>.<----------.+++++++++++.>.<<+++[>------<-]>-.+++++++++++++++++.---.++++++.-------.----------.[-]>[-]<<<.[-]]<[>+>+<<-]>>[-<<+>>]++++>+<[-<->]<[[-]>>-<<]>>[[-]<<+>>]<<[[-]++++++++++.[-]<[-]>]<+<]");
    c.execute();
}