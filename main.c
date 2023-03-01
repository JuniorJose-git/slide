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

    //count the number of characters (columns), in the first row, of the block (input)
    int block_col_count = 0;

    int blank_row, blank_col;
    
    bool firt_row_end, blank_col_is_odd = 0;
    
    char* block;

    char* str;
    
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
            firt_row_end = 1;
        } 
        else if (firt_row_end == 0)
        {
            if(((unsigned char)block[i] >> 6) != 0b10)
            {
                block_col_count++;
            }
        }
    }

    if (w.ws_col > block_col_count)
    {
        blank_col = w.ws_col - block_col_count;
    }
    else
    {
        blank_col = 0;
    }

    if (w.ws_row > block_row_count)
    {
        blank_row = w.ws_row - block_row_count;
    }
    else
    {
        blank_row = 0;
    }
    
    
    if (blank_col % 2 != 0)
    {
        blank_col_is_odd = 1; 
    }
    
    for(int i = 1; i < blank_row/2; i++)
    {
        print_space(w.ws_col);
        putchar('\n');
    }

    print_space(blank_col/2);
    for (int i = 0; block[i] != '\0'; i++)
    {
        if (block[i] == '\n')
        {
            print_space(blank_col/2);

            if (blank_col_is_odd == 1)
            {
                putchar(' ');
            }
        }
        putchar(block[i]);
        
        
        if ( block[i] == '\n' )
        {
            print_space(blank_col/2);
        }
    }
    print_space(blank_col/2);

    if ( blank_col_is_odd == 1 )
    {
        putchar(' ');
    }

    putchar('\n');
    
    for(int i = 0; i < blank_row/2; i++ )
    {
        print_space(w.ws_col);
        putchar('\n');

    }

    if (blank_row % 2 != 0)
    {
        print_space(w.ws_col);
        putchar('\n');
    }
    return 0;
}