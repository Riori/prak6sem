#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include <stdexcept>
#include <algorithm>

#include "stribog.h"

char symbol_to_hex(char c)
{
    if (c >= 'a' && c <= 'f')
    {
        return (char) 10 + c - 'a';
    }
    if (c >= 'A' && c <= 'F')
    {
        return (char) 10 + c - 'A';
    }
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    throw std::logic_error("Invalid hex character");
}

int main(int argc, char *argv[])
{
    try
    {
        struct stribog ctx;
        
        if (argc != 2)
        {
            throw std::logic_error("1 argument is required");
        }
        
        std::string path(argv[1]);
        
        std::string arg_prefix("--path=");
        
        auto iterators = std::mismatch(path.begin(), path.end(), arg_prefix.begin());
        
        if (iterators.second != arg_prefix.end())
        {
            throw std::logic_error("Not valid argument");
        }
        
        std::fstream f(std::string(iterators.first, path.end()));
        
        if (!f.good())
        {
            throw std::logic_error("File opening failed");
        }
        
        auto ii = std::istreambuf_iterator<char>(f.rdbuf());
        auto eof = std::istreambuf_iterator<char>();
        
        std::string input;
        
        copy_n(ii, 6, std::back_inserter(input));
        ii++;
        
        std::transform(input.begin(), input.end(), input.begin(), ::toupper);
        
        if (input != std::string("INPUT="))
        {
            throw std::logic_error("Wrong file structure");
        }
        
        std::vector<u8> data;
        
        while (ii != eof && *ii != '\n')
        {
            char ch1 = 0, ch2 = 0;
            ch1 = *(ii++);
            if (ii != eof && *ii != '\n')
            {
                ch2 = *(ii++);
            }
            char res = symbol_to_hex(ch1)*16 + symbol_to_hex(ch2);
            data.push_back(res);
        }
        
        init(&ctx, HASH256);
        stribog(&ctx, &data[0], data.size()*sizeof(u8));
        
        f << std::endl << "OUTPUT=";
        print_hash(&ctx, f);
        f << std::endl;
    } catch (std::logic_error e) {
        std::cerr << "ERROR!!! ";
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
