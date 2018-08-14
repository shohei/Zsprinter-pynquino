#include "xparameters.h"
#include "mailbox_io.h"

#ifdef __cplusplus
extern "C" {
#endif
char inbyte(void);
#ifdef __cplusplus
}
#endif 

char inbyte(void) {
	 return mailbox_inbyte(STDIN_BASEADDRESS);
}
