
/* AUTO-GENERATED by gen_isr_tables.py, do not edit! */

#include <toolchain.h>
#include <linker/sections.h>
#include <sw_isr_table.h>
#include <arch/cpu.h>

#if defined(CONFIG_GEN_SW_ISR_TABLE) && defined(CONFIG_GEN_IRQ_VECTOR_TABLE)
#define ISR_WRAPPER ((uintptr_t)&_isr_wrapper)
#else
#define ISR_WRAPPER NULL
#endif

typedef void (* ISR)(const void *);
uintptr_t __irq_vector_table _irq_vector_table[39] = {
	ISR_WRAPPER,
	163243,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	163187,
	ISR_WRAPPER,
	ISR_WRAPPER,
	163217,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
};
struct _isr_table_entry __sw_isr_table _sw_isr_table[39] = {
	{(const void *)0x27dd5, (ISR)0x27ddf},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x28b9c, (ISR)0x27c23},
	{(const void *)0x209d1, (ISR)0x27ddf},
	{(const void *)0x209e1, (ISR)0x27ddf},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x20205, (ISR)0x27ddf},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x200025f0, (ISR)0x1e9b9},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)0x1ed6d},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)0x1f9fd},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
};
