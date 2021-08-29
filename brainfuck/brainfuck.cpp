#include "brainfuck.h"


void decc::fn(int & hd, char * fst, ci & cf, ci & cc )
{
    fst[hd]-=n;
}

void incc::fn(int & hd, char * fst, ci & cf, ci & cc )
{
    fst[hd]+=n;
}

void mvrc::fn(int & hd, char * fst, ci & cf, ci & cc )
{
    if((hd+=n)>=BUF_SIZE)
        throw std::range_error("Head position is bigger than buffer\n");
}

void mvlc::fn(int & hd, char * fst, ci & cf, ci & cc )
{
    if((hd-=n)<0)
        throw std::range_error("Head position is less than buffer\n");
}

void blc::fn(int & hd, char * fst, ci & cf, ci & cc )
{
    if(fst[hd] == 0)
    {
        cc = cf+right_ind;
    }
}

void blc::sete(size_t ind)
{
    right_ind = ind;
}

void elc::fn(int & hd, char * fst, ci & cf, ci & cc )
{
    if(fst[hd] != 0)
    {
        cc = (cf+left_ind);
    }
}

void elc::setb(size_t ind)
{
    left_ind = ind;
}

void outc::fn(int & hd, char * fst, ci & cf, ci & cc )
{
    for(auto i = 0; i< n; ++i)
        std::cout<<fst[hd];
}

void inpc::fn(int & hd, char * fst, ci & cf, ci & cc )
{
    std::cout<<"";
}

std::vector<char_amount> bfmachine::s_to_ps(const std::string & str)
{
    if(str.empty())
        throw std::invalid_argument("Code string is empty\n");

    std::vector<char_amount> sps;
    size_t c = 1;
    for(auto i = ++str.begin(); i!=str.end(); ++i)
    {
        if((*i)==*(i-1)&&(*i)!=LEFT_BRACKET&&(*i)!=RIGHT_BRACKET)
            ++c;
        else
        {
            sps.emplace_back(std::make_pair(*(i-1),c));
            c=1;
        }
    }
    sps.emplace_back(std::make_pair(str.back(),1));
    return sps;
}

void bfmachine::init(const std::string & str)
{
    if(!cmds.empty())
    {
        for(auto cmd:cmds)
        {
            delete cmd;
        }
    }
    auto ps = s_to_ps(str);
    if (ps.empty())
        throw std::logic_error("there is no brainfuck code in the code string/file\n");
    std::vector<size_t> ibls;
    for (auto p:ps)
    {
        switch (p.first)
        {
            default: break;
            case MINUS: cmds.push_back(new decc(p.second));
                break;
            case PLUS: cmds.push_back(new incc(p.second));
                break;
            case RIGHT: cmds.push_back(new mvrc(p.second));
                break;
            case LEFT: cmds.push_back(new mvlc(p.second));
                break;
            case POINT: cmds.push_back(new outc(p.second));
                break;
            case RIGHT_BRACKET:
            {
                if(ibls.empty())
                    throw std::logic_error("Left bracket '[' is missing\n");
                auto ptr = new elc();
                ptr->setb(ibls.back());
                dynamic_cast<blc* >(cmds[ibls.back()])->sete(cmds.size());
                cmds.emplace_back(ptr);
                ibls.pop_back();
                break;
            }
            case LEFT_BRACKET:
            {
                ibls.emplace_back(cmds.size());
                cmds.emplace_back(new blc());
                break;
            }
        }
    }
    if(ibls.empty())
    {
        throw std::logic_error("Right bracket ']' is missing\n");
    }
    cf = cmds.begin();
    cc = cmds.begin();
}

void bfmachine::execute()
{
    while(cc != cmds.end())
    {
        (*cc)->fn(hd, fst, cf, cc );
        cc++;
    }
}
