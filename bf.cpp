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
    bool ignoreOps = false;
    int index = 0;
    int loop = 0;
    for (int i = 0; i < instructions.length(); i++)
    {
        if (ignoreOps)
        {
            if (instructions[i] == ']')
            {
                ignoreOps = false;
                i++;
            }
            else
                continue;
        }

        switch (instructions[i])
        {
        case '>':
            index += 1;
            break;
        case '<':
            index -= 1;
            break;
        case '+':
            tape[index] += 1;
            break;
        case '-':
            tape[index] -= 1;
            break;
        case '[':
            if (tape[index] == 0)
            {
                ignoreOps = true;
            }
            else
            {
                loop = i;
            }
            break;
        case ']':
            i = loop - 1;
            break;
        case '.':
            std::cout << tape[index];
            break;
        case ',':
            std::cin >> tape[index];
            break;
        default:
            break;
        }
    }
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