#include <stdio.h>
#include "Info.h"
#include <string.h>

extern int line_no;

char token[100];
int token_index = 0;

void resettoken()
{
    token[0] = '\0';
    token_index = 0;
}

void addchar(char ch)
{
    token[token_index++] = ch;
    token[token_index] = '\0';
}

void tokenidentifier_keyword(FILE *fp)
{

    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            line_no++;
        }
        if (isalphabet(ch))
        {
            token[token_index++] = ch;
        }
        else if (isalphabet(token[token_index - 1]) && isnumber(ch))
        {
            token[token_index++] = ch;
        }
        else
        {
            break;
        }
    }
    token[token_index] = '\0';
    if (iskeyword(token))
    {
        printf(GREEN"Keyword : %s\n"RESET, token);
    }
    else
    {
        printf(YELLOW"Identifier : %s\n"RESET, token);
    }
    resettoken();
    fseek(fp, -1, SEEK_CUR);
}

void skipincludes(FILE *fp)
{

    char ch;
    while ((ch = fgetc(fp)) != '\n')
        ;
    if (ch == '\n')
    {
        line_no++;
    }
}

void token_number(FILE *fp)
{
    char ch;
    int hasdot = 0;
    int ishex = 0, isoct = 0, isbin = 0;
    int invalid = 0;

    if (token[token_index - 1] == '0')
    {

        char next = fgetc(fp);

        if (next == 'X' || next == 'x')
        {
            ishex = 1;
            token[token_index++] = next;
        }
        else if (next == 'b' || next == 'B')
        {
            isbin = 1;
            token[token_index++] = next;
        }
        else if (isnumber(next))
        {
            isoct = 1;
            token[token_index++] = next;
        }
        else
        {
            fseek(fp, -1, SEEK_CUR);
        }
    }
    while ((ch = fgetc(fp)) != EOF)
    {

        if (ch == ';')
        {
            break;
        }
        if (ch == '\n')
        {
            line_no++;
        }
        if (ishex)
        {

            if (ishexdigit(ch))
            {
                token[token_index++] = ch;
            }
            else
            {
                if (isalphabet(ch))
                {
                    reportError("Invalid hexadecimal number", line_no, ch);
                }
            }
        }
        else if (isbin)
        {
            if (ch == '0' || ch == '1')
            {
                token[token_index++] = ch;
            }
            else
            {
                reportError("Inavlid Binary Number", line_no, ch);
            }
        }
        else if (isoct)
        {
            if (ch >= '0' && ch <= '7')
            {
                token[token_index++] = ch;
            }
            else
            {
                reportError("Invalid Octal Number", line_no, ch);
            }
        }
        else
        {

            if (isnumber(ch))
            {
                token[token_index++] = ch;
            }
            else if (ch == '.' && !hasdot)
            {
                token[token_index++] = ch;
                hasdot = 1;
            }
            else if (ch == '.' && hasdot)
            {
                reportError("Invalid floating conatants (too many dots)", line_no, ch);
            }
            else
            {
                break;
            }
        }
    }
    if (isalphabet(ch) && (!hasdot))
    {
        reportError("invalid suffix on integer constant", line_no, ch);
    }

    int floatf = 0;
    if (ch == 'f' || ch == 'F')
    {
        floatf = 1;
    }
    if (isalphabet(ch) && hasdot && (!floatf))
    {
        reportError("invalid suffix on floating constant", line_no, ch);
    }
    token[token_index] = '\0';

    if (hasdot)
    {
        printf(BLUE"Float Constant : %s\n"RESET, token);
    }
    else
    {
        printf(MAGENTA"Numeric Constant : %s\n"RESET, token);
    }
    resettoken();
    fseek(fp, -1, SEEK_CUR);
}

void token_operator(FILE *fp)
{
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            line_no++;
        }
        if (isoperator(ch))
        {
            token[token_index++] = ch;
        }
        else
        {
            break;
        }
    }
    token[token_index] = '\0';
    if (isoperator(token[0]))
    {
        printf(CYAN"Operator : %s\n"RESET, token);
    }
    resettoken();
    fseek(fp, -1, SEEK_CUR);
}

void token_symbol()
{
    token[token_index] = '\0';
    if (isSymbol(token[0]))
    {
        printf(GRAY"Symbol : %s\n"RESET, token);
    }
    resettoken();
}

void token_StringLiteral(FILE *fp)
{
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            line_no++;
            reportError("Missing Terminating Character", line_no, '"');
        }
        if (ch != '"')
        {
            token[token_index++] = ch;
        }
        else
        {
            break;
        }
    }
    if (ch == EOF)
    {
        reportError("Missing Terminating Character", line_no, '"');
    }
    token[token_index++] = ch;
    token[token_index] = '\0';

    printf(ORANGE"String Literal : %s\n"RESET, token);

    resettoken();
}

void token_character(FILE *fp)
{
    char ch;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            line_no++;
            reportError("Missing Terminating Character", line_no, 39);
        }
        if (ch != 39)
        {
            token[token_index++] = ch;
        }
        else
        {
            break;
        }
    }
    if (ch == EOF)
    {
        reportError("Missing Terminating Character", line_no, 39);
    }
    token[token_index++] = ch;
    token[token_index] = '\0';

    printf(PURPLE"Character Constant : %s\n"RESET, token);

    resettoken();
}

void skipComment(FILE *fp)
{
    char ch;
    ch = fgetc(fp);
    if (ch == '/')
    {
        while ((ch = fgetc(fp)) != EOF)
        {
            if (ch == '\n')
            {
                line_no++;
                break;
            }
        }
    }
    else if (ch == '*')
    {
        char prev = 0;
        while ((ch = fgetc(fp)) != EOF)
        {
            if (ch == '\n')
            {
                line_no++;
            }
            if (prev == '*' && ch == '/')
            {
                break;
            }
            prev = ch;
        }
    }
    else
    {
        fseek(fp, -1, SEEK_CUR);
        token_operator(fp);
    }
    if (ch == EOF)
    {
        reportError("unterminated comment", line_no, '/');
        return;
    }

    resettoken();
}