#include <types.h>

#pragma pack(1)
typedef struct command_pkt_s {
	unsigned short magic;
	unsigned char type;
	uint32_t len;
	char data[0];
} command_pkt_t;
