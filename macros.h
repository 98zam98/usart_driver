#ifndef __MACROS_H__
#define __MACROS_H__

// macros start

#define setbit(reg,shift) reg|=(1<<shift)
#define clearbit(reg,shift) reg&=~(1<<shift)
#define togglebit(reg,shift) reg^=(1<<(shift))
#define checkbit(reg,shift) ((reg) & (1<<(shift)))
#define checkbit0(reg,shift) (((reg) & (1<<(shift)))>>shift)
#define assignbit(reg,shift,val) reg|=(val<<shift)
// macros end

#endif