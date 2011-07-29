#include "bauds.h"
#include "baseIO.h"

extern void baud_prompt_msg(void);

void print_bauds(void)
{	int i;

	for(i=0; i<BAUD_MSG_LEN; i++)
	{	if((i%3)==0)  UART1TX(__builtin_tblrdl((int)&baud_prompt_msg+((i/3)<<1))&0x00FF);
		if((i%3)==1) UART1TX((__builtin_tblrdl((int)&baud_prompt_msg+((i/3)<<1))>>8)&0xFF);
		if((i%3)==2)  UART1TX(__builtin_tblrdh((int)&baud_prompt_msg+((i/3)<<1))&0x00FF);
	}
	bpBR;
}

