#include "brainfuck.h"

int main(int argc, char *argv[])
{
    bfmachine c;
    switch (argc)
    {
        case 2:
        {
            c.init(argv[1]);
            c.execute();
            break;
        }
        case 3:
        {
            if(std::string(argv[1])=="-f")
            {
                std::string file_name = argv[2];
                std::ifstream f(file_name);
                if(!f.good())
                {
                    throw std::invalid_argument("Such file doesn't exist");
                }
                std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
                std::cout<<str;
                c.init(str);
                c.execute();
            }
            break;
        }
        default:
        {
            std::cout<<"To compile string use command ' bfmachine \"code_string\"'\n"<<
                     "To compile program from file use command ' bfmachine -f \"src_file\"'";
        }
    }
}