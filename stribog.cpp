#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <exception>
#include <vector>

#include "types.h"
#include "stribog.h"

using namespace std;

void print_hash(struct stribog *ctx, ostream &s)
{
	u8 i;

    s.fill('0');
    s.width(2);

	for (i = 0; i < 32; i++)
		s << std::hex << (int)ctx->h[i];
}

void processing(char *s, struct stribog *ctx)
{

}

char symbol_to_hex(char c) {
    if (c >= 'a' && c <= 'f') {
        return (char) 10 + c - 'a';
    }
    if (c >= 'A' && c <= 'F') {
        return (char) 10 + c - 'A';
    }
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    throw std::logic_error("Invalid hex character");
}

int main(int argc, char *argv[])
{
    try {
        struct stribog ctx;
        
        if (argc != 2) {
            throw std::logic_error("1 argument is required");
        }
        
        string path(argv[1]);
        
        string arg_prefix("--path=");
        
        auto iterators = std::mismatch(path.begin(), path.end(), arg_prefix.begin());
        
        if (iterators.second != arg_prefix.end()) {
            throw std::logic_error("Not valid argument");
        }
        
        fstream f(string(iterators.first, path.end()));
        
        if (!f.good()) {
            throw std::logic_error("File opening failed");
        }
        
        auto ii = istreambuf_iterator<char>(f.rdbuf());
        auto eof = istreambuf_iterator<char>();
        
        string input;
        
        copy_n(ii, 6, std::back_inserter(input));
        ii++;
        
        std::transform(input.begin(), input.end(), input.begin(), ::toupper);
        
        if (input != string("INPUT=")) {
            throw std::logic_error("Wrong file structure");
        }
        
        vector<u8> data;
        
        while (ii != eof && *ii != '\n') {
            char ch1 = 0, ch2 = 0;
            ch1 = *(ii++);
            if (ii != eof && *ii != '\n') {
                ch2 = *(ii++);
            }
            char res = symbol_to_hex(ch1)*16 + symbol_to_hex(ch2);
            data.push_back(res);
        }
        
        init(&ctx, HASH256);
        stribog(&ctx, &data[0], data.size()*sizeof(u8));
        
        f << "OUTPUT=";
        print_hash(&ctx, f);
        f << endl;
    } catch (logic_error e) {
        cerr << "ERROR!!! ";
        cerr << e.what() << endl;
    }

	return 0;
}
