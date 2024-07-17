#ifndef __OSL_BIO_H
#define __OSL_BIO_H

static __inline__ void DMB(void)
{
    __asm__ __volatile__ ( "DMB;");
}

static __inline__ void nop(void)
{
    __asm__ __volatile__ ( "NOP;");
}

static __inline__ void writel(unsigned val, unsigned addr)
{
    DMB();
    (*(volatile unsigned *) (addr)) = (val);
    DMB();
}

static __inline__ unsigned readl(unsigned addr)
{
    DMB();
    return (*(volatile unsigned *) (addr));
}

static __inline__ unsigned osl_reg_get_bit(void *reg, unsigned bit_start, unsigned bit_end)
{
	unsigned tmp;
	tmp = readl((unsigned long)reg);
	return ((tmp >> bit_start)&((1 << (bit_end - bit_start + 1))-1));
}

static __inline__ void osl_reg_set_bit(void *reg, unsigned bit_start, unsigned bit_end, unsigned reg_val)
{
	unsigned tmp;
	tmp = readl((unsigned long)reg);
	tmp &= (~(((1 << (bit_end - bit_start + 1))-1) << bit_start));
	tmp |= (reg_val << bit_start);
	writel(tmp, (unsigned long)reg);
}

#endif	/* __OSL_BIO_H */
