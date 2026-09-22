#pragma once

void mongoose_init(unsigned int mg_debug_level);
void mongoose_poll(void);
unsigned char send_tcp_buffer(unsigned char *buff, size_t size);

