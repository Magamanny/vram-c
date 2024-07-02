#include <stdint.h>
#include <vram.h>
uint8_t ram[PAGE_SIZE];
uint8_t flash[VRAM_SIZE];
int cpage=0;
int page_write_pending=0;
int page_write_wear=0;
int page_read_wear=0;
void flash_dump()
{
    for(int i=0;i<4*PAGE_SIZE;i++)
    {
        if(i%32==0)
        {
            printf("\r\n");
        }
        if(i%PAGE_SIZE==0)
        {
            printf("\r\n");
        }
        printf("%02x ",flash[i]);
    }
    printf("\r\n");
    printf("wear read=%d, write=%d\r\n",page_read_wear,page_write_wear);
}
// swap logic
void vram_swap(int cpage,int npage)
{
    // if address is not in the current page
    //printf("swapping page %d with %d\r\n",cpage,npage);
    // swap the page
    // write if any new data is written in the memory
    if(page_write_pending)
    {
        page_write_pending=0;
        page_write_wear++;
        for(int i=0;i<PAGE_SIZE;i++)
        {
            flash[cpage*PAGE_SIZE+i] = ram[i];
        }
    }
    page_read_wear++;
    for(int i=0;i<PAGE_SIZE;i++)
    {
        ram[i] = flash[npage*PAGE_SIZE+i];
    }
    //flash_dump();
}
uint8_t vram_read(uint16_t i)
{
    int addr_h,addr_l;
    uint8_t byte;
    addr_l = i&0xFF;
    addr_h = i>>8;
    if(addr_h >= PAGE_NUM)
    {
        printf("page %d is out of bond.\r\n",addr_h);
        byte=0;
    }
    else
    {
        if(addr_h != cpage)
        {
            vram_swap(cpage,addr_h);
            cpage = addr_h;
        }
        byte = ram[addr_l];
    }
    //printf("%d %d\r\n",addr_h,addr_l);
    return byte;
}
void vram_write(uint8_t data,uint16_t i)
{
    int addr_h,addr_l;
    addr_l = i&0xFF;
    addr_h = i>>8;
    if(addr_h >= PAGE_NUM)
    {
        printf("page %d is out of bond.\r\n",addr_h);
    }
    else
    {
        if(addr_h != cpage)
        {
            vram_swap(cpage,addr_h);
            cpage = addr_h;
        }
        page_write_pending=1;
        ram[addr_l] = data;
    }
}