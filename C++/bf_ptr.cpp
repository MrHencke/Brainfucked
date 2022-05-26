#include <iostream>
#include <string>
#include <fstream>

using std::ifstream;
using std::string;

// forward declarations
string getFileContents(string fileName);
void interpret(string instructions);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Please input a file to be interpreted";
        return 0;
    }

    string instructions = getFileContents(argv[1]);
    interpret(instructions);
    return 0;
}

void interpret(string instructions)
{
    char tape[30000];
    char *pt = tape;
    char *ptt = &instructions[0];
    char *pttr;
    bool ignoreOps = false;
    while (ptt != NULL)
    {
        if (ignoreOps)
        {
            if (*ptt == ']')
            {
                ignoreOps = 0;
                ptt++;
            }
            else
            {
                ptt++;
                continue;
            }
        }

        switch (*ptt)
        {
        case '>':
            pt++;
            break;
        case '<':
            pt--;
            break;
        case '+':
            (*pt)++;
            break;
        case '-':
            (*pt)--;
            break;
        case '[':
            if (*pt == 0)
            {
                ignoreOps = 1;
            }
            else
            {
                pttr = ptt;
            }
            break;
        case ']':
            ptt = pttr;
            continue;
        case '.':
            std::cout << *pt;
            break;
        case ',':
            std::cin >> *pt;
            break;
        default:
            break;
        }
        ptt++;
    }
    delete pt;
    delete ptt;
    delete pttr;
}

string getFileContents(string fileName)
{
    string instructions;
    ifstream file;
    file.open(fileName);
    string line;
    while (std::getline(file, line))
    {
        instructions += line;
    }
    return instructions;
}