//
// Created by theredrover on 29/08/2021.
//

#ifndef BRAINFUCK_BRAINFUCK_H
#define BRAINFUCK_BRAINFUCK_H

#include <cstddef>
#include <exception>
#include <iostream>
#include <vector>
#include <fstream>

const size_t BUF_SIZE = 30000;

enum cmds
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

typedef std::pair<char, size_t> char_amount;

class cmd
{
protected:
    size_t n;
public:
    cmd(){}
    cmd(size_t n_):n(n_){}
    virtual void fn(int & hd, char * fst,
                    std::vector<cmd *>::iterator & cf, std::vector<cmd *>::iterator & cc) = 0;
    virtual ~cmd(){}
};

typedef std::vector<cmd *>::iterator ci;

class decc : public cmd
{
public:
    decc(size_t n):cmd(n){}
    void fn(int & hd, char * fst, ci & cf, ci & cc ) override;
};

class incc : public cmd
{
public:
    incc(size_t n):cmd(n){}
    void fn(int & hd, char * fst, ci & cf, ci & cc ) override;
};

class mvrc : public cmd
{
public:
    mvrc(size_t n):cmd(n){}
    void fn(int & hd, char * fst, ci & cf, ci & cc ) override;
};

class mvlc : public cmd
{
public:
    mvlc(size_t n):cmd(n){}
    void fn(int & hd, char * fst, ci & cf, ci & cc ) override;
};

class blc : public cmd
{
    size_t right_ind;
public:
    blc(){}
    void fn(int & hd, char * fst, ci & cf, ci & cc ) override;
    void sete(size_t ind);
};

class elc : public cmd
{
    size_t left_ind;
public:
    elc(){}
    void fn(int & hd, char * fst, ci & cf, ci & cc ) override;
    void setb(size_t ind);
};

class outc : public cmd
{
public:
    outc(size_t n):cmd(n){}
    void fn(int & hd, char * fst, ci & cf, ci & cc ) override;
};

class inpc : public cmd
{
public:
    inpc(size_t n):cmd(n){}
    void fn(int & hd, char * fst, ci & cf, ci & cc ) override;
};

class bfmachine
{
    std::vector<cmd *> cmds;
    int hd;
    char cpu[BUF_SIZE] = {0};
    char * fst = cpu;
    ci cf;
    ci cc;
    std::vector<std::pair<char, size_t>> s_to_ps(const std::string & str);
public:
    void init(const std::string & str);

    void execute();


    virtual ~bfmachine()
    {
        if(!cmds.empty())
            for(auto cmd:cmds)
            {
                delete cmd;
            }
    }
};

#endif //BRAINFUCK_BRAINFUCK_H
