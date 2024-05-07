#include <sys/ioctl.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int print_space(int size)
{

    for(int i = 0; i < size; i++)
    {
        putchar(' ');
    }
    return 0;
}

int main(int argc, char**argv) 
{
    struct winsize w;
    ioctl(2, TIOCGWINSZ, &w);

    //count the number of rows of the block (input)
    int block_row_count = 1;

    int line_col_count;

    int blank_row, blank_col;
    
    char* block;
    
    int stdin_lengh = 0;
    char stdin_buffer[5000];

    if(isatty(0))
    {
        for(int i = 1; i < argc;i++)
        {
            for (int j = 0; argv[i][j] !='\0' ;j++,stdin_lengh++) {
                stdin_buffer[stdin_lengh] = argv[i][j];
            }

            stdin_buffer[stdin_lengh] = ' ';
            stdin_lengh++;
        }
    }
    else
    {
        stdin_lengh = read(STDIN_FILENO,stdin_buffer,sizeof (stdin_buffer));
    }
    
    block = stdin_buffer;
    block[stdin_lengh - 1] = '\0';
    
    for(int i=0; block[i]!='\0'; i++ )
    {
        if (block[i] == '\n')
        {
            block_row_count++;
        }
    }

    if (w.ws_row > block_row_count)
    {
        blank_row = w.ws_row - block_row_count;
    }
    else
    {
        blank_row = 0;
    }
 
    for(int i = 1; i < blank_row/2; i++)
    {
        print_space(w.ws_col);
        putchar('\n');
    }

    if (blank_row % 2 != 0)
    {
        print_space(w.ws_col);
        putchar('\n');
    }

    int i = 0;
    int o = 0;
    
    for(int j = 0; j < block_row_count; j++)
    {
        blank_col = 0, line_col_count = 0;

        while(block[o] != '\n' && block[o] != '\0')
        {
            if(((unsigned char)block[o] >> 6) != 0b10)
            {
                line_col_count++;
            }
            o++;
        }
            o++;

        blank_col = w.ws_col - line_col_count;

        print_space(blank_col/2);

        while(block[i] != '\n' && block[i] != '\0')
        {
            putchar(block[i]);
            i++;
        }
            i++;
        
        print_space(blank_col/2);

        if (blank_col % 2 != 0)
        {
            putchar(' ');
        }
        
        putchar('\n');
    }
    
    for(int i = 0; i < blank_row/2; i++ )
    {
        print_space(w.ws_col);
        putchar('\n');

    }



    return 0;
}
