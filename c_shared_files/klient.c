#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

#include"file_operations.h"
#include"file_io.h"
#include"util.h"

int main()
{
    char line_buffer[256];

    lock_server();

    fputs("Dostęp przyznany, możesz pisać:\n",stdout);
    fputs("nazwa użytkownika: ",stdout);
    fgets(line_buffer,256,stdin);
    
    file_d data = open_for_write("dane");
    write_line(data,line_buffer);
    
    fputs("Wiadomość:\n",stdout);
    int flag = 1;
    while(flag) 
    {
        fgets(line_buffer,256,stdin);
        
        int esc_pos = get_esc_position(line_buffer);
        
        if(esc_pos!=-1)
            flag=0;
        
        write_line(data,line_buffer);
    }

    close(data);

    fputs("\nWiadomość wysłana, czekanie na odpowiedź:\n",stdout);
    file_d result = open_for_read("wyniki");
    
    char _s[2];
    _s[1]=(char)0;

    flag = 1;
    while(flag)
    {
        int c = read_byte(result);

        if(c>0)
        {
            if(c==27)
                flag=0;
            else
            {
                _s[0]=(char)c;
                fputs(_s,stdout);
            }
            
        }
        else if(c==-1)
        {
            sleep(2);
        }
        else if(c==-2)
        {
            printf("\nBłąd odczytu\n");
            sleep(2);
        }

    }
    
    close(result);
    clear_file("wyniki");

    return 0;
    
}