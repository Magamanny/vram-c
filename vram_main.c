/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include "vram.h"

void sequence_rw()
{
    for(uint16_t i=0;i<VRAM_SIZE;i++)
    {
        vram_write(i,i);
    }
    printf("reading\r\n");
    for(uint16_t i=0;i<VRAM_SIZE;i++)
    {
        if(vram_read(i) != i%256)
        {
            printf("SQ-Test Error %d %d\r\n",i,vram_read(i));
            flash_dump();
            break;
        }
    }
}
void random_rw()
{
    int addr[10]={153,8,203,194,183,248,105,1,228,121};
    for(int i=0;i<10;i++)
    {
        vram_write(addr[i],addr[i]);
    }
    for(int i=0;i<10;i++)
    {
        if(vram_read(addr[i])!=addr[i])
        {
            printf("RD-Test Error %d\r\n",i);
            flash_dump();
            break;
        }
    }
}
int main()
{
    char r[50];
    char temp[256]="0422,07,1,D,000000.99,0280.15,000277.35,00200940.51,05:21:15,2000-01-02\r\n";
    printf("Start.\r\n");
    //vram_write('A',125);
    //printf("%c",vram_read(125));
    for(uint16_t i=0;i<730;i++)
    {
        vram_write(temp[i%73],i);
    }
    //flash_dump();
    printf("Reaing Vram\r\n");
    for(int i=0;i<730;i++)
    {
        printf("%c",vram_read(i));
    }
    printf("\r\n");
    // test
    sequence_rw();
    random_rw();
    printf("sequence_rw\r\n");
    printf("random_rw\r\n");
    flash_dump();
    return 0;
}
