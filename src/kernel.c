#include <stdint.h>

#define VGA_ADDRESS 0xb8000
#define VGA_COLOR(character, color) (uint16_t) character | (uint16_t) color << 8
#define VGA_BLACK        0
#define VGA_BLUE         1
#define VGA_GREEN        2
#define VGA_CYAN         3
#define VGA_RED          4
#define VGA_PURPLE       5
#define VGA_BROWN        6
#define VGA_GRAY         7
#define VGA_DARK_GRAY    8
#define VGA_LIGHT_BLUE   9
#define VGA_LIGH_GREEN   10
#define VGA_LIGHT_CYAN   11
#define VGA_LIGHT_RED    12
#define VGA_LIGHT_PURPLE 13
#define VGA_YELLOW       14
#define VGA_WHITE        15

struct stivale_header {
    uint64_t stack;
    // Flags
    // bit 0   0 = text mode,   1 = graphics mode
    uint16_t flags;
    uint16_t framebuffer_width;
    uint16_t framebuffer_height;
    uint16_t framebuffer_bpp;
} __attribute__((packed));

struct stivale_module {
    uint64_t begin;
    uint64_t end;
    char     string[128];
    uint64_t next;
} __attribute__((packed));

struct stivale_struct {
    uint64_t cmdline;
    uint64_t memory_map_addr;
    uint64_t memory_map_entries;
    uint64_t framebuffer_addr;
    uint16_t framebuffer_pitch;
    uint16_t framebuffer_width;
    uint16_t framebuffer_height;
    uint16_t framebuffer_bpp;
    uint64_t rsdp;
    uint64_t module_count;
    uint64_t modules;
    uint64_t epoch;
    uint64_t flags;       // bit 0: 1 if booted with BIOS, 0 if booted with UEFI
} __attribute__((packed));

/**
 * Stack for bootstrapping the kernel
 */
static char stack[4096] = {0};

__attribute__((section(".stivalehdr"), used))
struct stivale_header header = {
    .stack = (uintptr_t)stack + sizeof(stack),
    .framebuffer_bpp = 0,
    .framebuffer_width = 0,
    .framebuffer_height = 0,
    .flags = 0,
};


uint16_t *vga_buffer;

void _start(struct stivale_header *header) {
	vga_buffer = (uint16_t*)VGA_ADDRESS;
	vga_buffer[0] = VGA_COLOR('h', VGA_GREEN);
	vga_buffer[1] = VGA_COLOR('e', VGA_GREEN);
	vga_buffer[2] = VGA_COLOR('l', VGA_GREEN);
	vga_buffer[3] = VGA_COLOR('l', VGA_GREEN);
	vga_buffer[4] = VGA_COLOR('o', VGA_GREEN);
    asm volatile ("hlt");
}
