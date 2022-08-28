#include "tss.h"
#include <string.h>

// Note: some of the GDT entry struct field names may not match perfectly to the TSS entries.
tss_entry_t tss_entry;

extern void flush_tss(void); 

void write_tss(struct gdt_entry_bits *g) {
	// Compute the base and limit of the TSS for use in the GDT entry.
	uint32_t base = (uint32_t) &tss_entry;
	uint32_t limit = sizeof tss_entry;
 
	// Add a TSS descriptor to the GDT.
	g->limit_low = limit;
	g->base_low = base;
	g->accessed = 1; // With a system entry (`code_data_segment` = 0), 1 indicates TSS and 0 indicates LDT
	g->read_write = 0; // For a TSS, indicates busy (1) or not busy (0).
	g->conforming_expand_down = 0; // always 0 for TSS
	g->code = 1; // For a TSS, 1 indicates 32-bit (1) or 16-bit (0).
	g->code_data_segment=0; // indicates TSS/LDT (see also `accessed`)
	g->DPL = 0; // ring 0, see the comments below
	g->present = 1;
	g->limit_high = (limit & (0xf << 16)) >> 16; // isolate top nibble
	g->available = 0; // 0 for a TSS
	g->long_mode = 0;
	g->big = 0; // should leave zero according to manuals.
	g->gran = 0; // limit is in bytes, not pages
	g->base_high = (base & (0xff << 24)) >> 24; //isolate top byte
 
	// Ensure the TSS is initially zero'd.
	memset(&tss_entry, 0, sizeof tss_entry);
 
	tss_entry.ss0  = REPLACE_KERNEL_DATA_SEGMENT;  // Set the kernel stack segment.
	tss_entry.esp0 = REPLACE_KERNEL_STACK_ADDRESS; // Set the kernel stack pointer.
	//note that CS is loaded from the IDT entry and should be the regular kernel code segment
}
 
void set_kernel_stack(uint32_t stack) { // Used when an interrupt occurs
	tss_entry.esp0 = stack;
}

