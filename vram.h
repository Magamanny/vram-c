#ifndef VRAM_H
#define VRAM_H
// page size should be such that can be address with the addr_l.
#define PAGE_SIZE 256
// number of pages, atleast 1, should be addressable via addr_h
#define PAGE_NUM 16
// vram size = PAGE_SIZE*PAGE_NUM max
#define VRAM_SIZE   (PAGE_SIZE*PAGE_NUM)

void vram_write(uint8_t data,uint16_t i);
uint8_t vram_read(uint16_t i);
void vram_swap(int cpage,int npage);
void flash_dump();

#endif