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

    while (fgets(line, sizeof(line), in))
    {
        char var[50];
        int val1, val2;

        // Case: int a = 5;
        if (sscanf(line, "int %s = %d;", var, &val1) == 2)
        {
            fprintf(out, "PUSH %d\n", val1);
            fprintf(out, "STORE %s\n", var);
        }

        // Case: int a = 2 + 3;
        else if (sscanf(line, "int %s = %d + %d;", var, &val1, &val2) == 3)
        {
            fprintf(out, "PUSH %d\n", val1);
            fprintf(out, "PUSH %d\n", val2);
            fprintf(out, "ADD\n");
            fprintf(out, "STORE %s\n", var);
        }

        // Case: int b = a + 4;
        else if (sscanf(line, "int %s = %[^+]+ %d;", var, var, &val2) == 3)
        {
            char var1[50];
            sscanf(line, "int %s = %[^+]+ %d;", var, var1, &val2);

            fprintf(out, "LOAD %s\n", var1);
            fprintf(out, "PUSH %d\n", val2);
            fprintf(out, "ADD\n");
            fprintf(out, "STORE %s\n", var);
        }

        // Case: print(a);
        else if (sscanf(line, "print(%[^)]);", var) == 1)
        {
            fprintf(out, "LOAD %s\n", var);
            fprintf(out, "PRINT\n");
        }
    }

    fclose(in);
    fclose(out);

    printf("Compilation complete. Output: out.bytecode\n");
    return 0;
}