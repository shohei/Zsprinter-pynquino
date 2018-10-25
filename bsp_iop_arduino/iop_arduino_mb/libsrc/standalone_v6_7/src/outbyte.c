#include "xparameters.h"
#include "mailbox_io.h"

#ifdef __cplusplus
extern "C" {
#endif
void outbyte(char c); 

#ifdef __cplusplus
}
#endif 

void outbyte(char c) {
	 mailbox_outbyte(STDOUT_BASEADDRESS, c);
}
