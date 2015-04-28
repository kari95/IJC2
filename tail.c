// tail.c
// IJC-DU2
// Author: Miroslav Karásek, FIT
// Date: 2015-04-10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ring.h"

#define MAX_LENGTH 500

typedef struct {
    bool is_help;
    bool is_from;
    unsigned long count;
    char *filename;
} args_t;

bool get_args(args_t *args, int argc, char **argv)
{
    char *number_argument = NULL;
    
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (argv[i][1] == 'n')
            {
                if (number_argument)
                {
                    fprintf(stderr, "More -n parameters\n");
                    return false;
                }
                if (argv[i][2] == '\0')
                    i++;
                else
                    argv[i] += 2;
                if (i < argc)
                    number_argument = argv[i];
                else
                {
                    fprintf(stderr, "After -n must be count\n");
                    return false;
                }
            }
            else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
            {
                args->is_help = true;
            }
            else
            {
                fprintf(stderr, "Unknown argument '%s'\n", argv[i]);
                return false;
            }
        }
        else
        {
            if (args->filename)
            {
                fprintf(stderr, "More files specified\n");
                return false;
            }
            args->filename = argv[i];
        }
    }
    if (number_argument != NULL)
    {
        char *ptr;
        args->count = strtol(number_argument, &ptr, 0);
        if (ptr[0] == '\0')
        {
            if (number_argument[0] == '+')
                args->is_from = true;
            else
                args->is_from = false;
        }
        else
        {
            fprintf(stderr, "Bad format after -n\n");
            return false;
        }
    }
    return true;
}

void print_help()
{
    printf(
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
        "   if not set it will be use standard input\n"
    );
}

int getline(char *buffer, int length, FILE *file)
{
    int ch;
    int i;
    for (i = 0; (ch = fgetc(file)) != EOF; i++)
    {
        if (i < length - 1)
            buffer[i] = ch;
        else if (i == length - 1)
        {
            buffer[i - 1] = '\n';
            buffer[i] = '\0';
        }
        if (ch == '\n')
        {
            i++;
            break;
        }
    }
    if (i)
    {
        if (i < length)
        {
            buffer[i - 1] = '\n';
            buffer[i] = '\0';
        }
    }
    return i;
}

int main (int argc, char **argv)
{
    args_t args = {false, false, 10, NULL};
    FILE *file = NULL;
    
    if(!get_args(&args, argc ,argv))
    {
        fprintf(stderr, "Use -h or --help for help\n");
        return 1;
    }
    if (args.is_help)
    {
        print_help();
        return 0;
    }
    if (args.filename)
    {
        file = fopen(args.filename, "r");
        if (file == NULL)
        {
            fprintf(stderr, "File '%s' can not be opened\n", args.filename);
            return 1;
        }
    }
    else
        file = stdin;
    
    ring_t *ring = NULL;
    if (!args.is_from)
    {
        ring = ring_init(args.count, MAX_LENGTH + 2);
    }
    char buffer[MAX_LENGTH + 2];
    int length;
    bool all_in_limit = true;
    for (unsigned long i = 1; (length = getline(buffer, MAX_LENGTH + 2, file)); i++)
    {
        if (length > MAX_LENGTH + 1 && all_in_limit)
        {
            fprintf(stderr, "Line %lu is longer than maximal length %d\n", i, MAX_LENGTH);
            all_in_limit = false;
        }
        if (args.is_from)
        {
            if (i >= args.count)
                printf("%s", buffer);
        }
        else
            ring_write_buffer(ring, buffer);
        
    }
    if (!args.is_from)
    {
        char *line;
        while ((line = ring_read_buffer(ring)) != NULL)
            printf("%s", line);
    }
    ring_free(ring);
    fclose(file);
    if (all_in_limit)
        return 0;
    else
        return 1;
}