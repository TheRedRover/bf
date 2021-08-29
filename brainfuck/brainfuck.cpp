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
        throw std::range_error("Head position is bigger than buffer");
}

void mvlc::fn(int & hd, char * fst, ci & cf, ci & cc )
{
    if((hd-=n)<0)
        throw std::range_error("Head position is less than buffer");
}

void bcc::fn(int & hd, char * fst, ci & cf, ci & cc )
{
    if(fst[hd] == 0)
    {
        cc = cf+right_ind;
    }
}

void bcc::sete(size_t ind)
{
    right_ind = ind;
}

void ecc::fn(int & hd, char * fst, ci & cf, ci & cc )
{
    if(fst[hd] != 0)
    {
        cc = (cf+left_ind);
    }
}

void ecc::setb(size_t ind)
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

std::vector<char_amount>> bfmachine::s_to_ps(const std::string & str)
{
    if(str.empty())
        throw std::invalid_argument("Code string is empty");

    std::vector<char_amount>> sps;
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
    std::vector<size_t> i_l_brs;
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
                if(i_l_brs.empty())
                    throw std::logic_error("Left bracket '[' is missing");
                auto ptr = new ecc();
                ptr->setb(i_l_brs.back());
                dynamic_cast<bcc* >(cmds[i_l_brs.back()])->sete(cmds.size());
                cmds.emplace_back(ptr);
                i_l_brs.pop_back();
                break;
            }
            case LEFT_BRACKET:
            {
                i_l_brs.emplace_back(cmds.size());
                cmds.emplace_back(new bcc());
                break;
            }
        }
    }
    if(i_l_brs.size()>0)
    {
        throw std::logic_error("Right bracket ']' is missing");
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
