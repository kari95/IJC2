// tail2.cc
// IJC-DU2
// Author: Miroslav Karásek, FIT
// Date: 2015-04-18

#include <iostream>
#include <string>
#include <fstream>
#include <queue>

typedef struct {
    bool is_help;
    bool is_from;
    unsigned long count;
    const char *filename;
} args_t;

void print_help()
{
    std::cout << 
        "Usage:\n"
        "   tail [ARGUMENTS] [FILE]\n"
        "\n"
        "Arguments:\n"
        "   -h          print help\n"
        "   -n COUNT    specifics number of last lines \n"
        "   -n +COUNT   specifics first line to write\n"
        "   default argument is -n 10\n"
        "\n"
        "File:\n"
        "   if not set it will be use standard input\n";
}

void get_args(args_t &args, int argc, const char **argv)
{
    using namespace std;
    const char *number_argument = NULL;
    
    for (int i = 1; i < argc; i++)
    {
        string argument(argv[i]); 
        if (argv[i][0] == '-')
        {
            if (argv[i][1] == 'n')
            {
                if (number_argument)
                {
                    cerr << "More -n parameters" << endl;
                    throw 1;
                }
                if (argv[i][2] == '\0')
                    i++;
                else
                    argv[i] += 2;
                if (i < argc)
                    number_argument = argv[i];
                else
                {
                    cerr << "After -n must be count" << endl;
                    throw 2;
                }
            }
            else if (argument == "-h" || argument == "--help")
            {
                args.is_help = true;
            }
            else
            {
                cerr << "Unknown argument " << argv[i] << endl;
                throw 3;
            }
        }
        else
        {
            if (args.filename)
            {
                cerr << "More files specified" << endl;
                throw 4;
            }
            args.filename = argv[i];
        }
    }
    if (number_argument != NULL)
    {
        char *ptr;
        args.count = strtol(number_argument, &ptr, 0);
        if (ptr[0] == '\0')
        {
            if (number_argument[0] == '+')
                args.is_from = true;
            else
                args.is_from = false;
        }
        else
        {
            cerr << "Bad format after -n" << endl;
            throw 5;
        }
    }
}

int main(int argc, char const *argv[])
{
    using namespace std;
    args_t args {false, false, 10, NULL};
    ifstream input;
    try
    {
        get_args(args, argc, argv);
    }
    catch (int e)
    {
        cerr << "Use -h or --help for help" << endl;
        return e;
    }
    if (args.is_help)
    {
        print_help();
        return 0;
    }
    if (args.filename)
    {
        input.open(args.filename, ios::in);
        if (!input.is_open())
        {
            cerr << "File " << args.filename << " can not be opened" << endl;
            return 1;
        }
        cin.rdbuf(input.rdbuf());
    }
    if (args.is_from)
    {
        string line;
        for(unsigned long i = 1; getline(cin, line); i++)
        {
            if (i >= args.count)
            {
                cout << line << endl;
            }
        }
    }
    else
    {
        queue<string> buffer;
        string line;
        for(unsigned long i = 0; getline(cin, line); i++)
        {
            buffer.push(line);
            if (i >= args.count)
                buffer.pop();
        }  
        while (!buffer.empty())
        {
            cout << buffer.front() << endl;
            buffer.pop();
        }
    }
    input.close();
    return 0;
}