#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./compiler <inputfile>\n");
        return 1;
    }

    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen("../output/out.bytecode", "w");

    if (!in || !out)
    {
        printf("Error opening files\n");
        return 1;
    }

    char line[256];
    char var[50];
    char var1[50];
    char text[100];
    int val1, val2;

    while (fgets(line, sizeof(line), in))
    {

        // Case 1
        if (sscanf(line, "int %s = %d;", var, &val1) == 2)
        {
            fprintf(out, "PUSH %d\n", val1);
            fprintf(out, "STORE %s\n", var);
        }

        // Case 2
        else if (sscanf(line, "int %s = %d + %d;", var, &val1, &val2) == 3)
        {
            fprintf(out, "PUSH %d\n", val1);
            fprintf(out, "PUSH %d\n", val2);
            fprintf(out, "ADD\n");
            fprintf(out, "STORE %s\n", var);
        }

        // Case 3
        else if (sscanf(line, "int %s = %[^+]+ %d;", var, var1, &val2) == 3)
        {
            fprintf(out, "LOAD %s\n", var1);
            fprintf(out, "PUSH %d\n", val2);
            fprintf(out, "ADD\n");
            fprintf(out, "STORE %s\n", var);
        }

        // print("text")
        else if (sscanf(line, "print(\"%[^\"]\");", text) == 1)
        {
            fprintf(out, "PRINT_STR %s\n", text);
        }

        // input(x)
        else if (sscanf(line, "input(%[^)]);", var) == 1)
        {
            fprintf(out, "INPUT %s\n", var);
        }

        // print(a)
        else if (sscanf(line, "print(%[^)]);", var) == 1)
        {
            fprintf(out, "LOAD %s\n", var);
            fprintf(out, "PRINT\n");
        }
    }
}