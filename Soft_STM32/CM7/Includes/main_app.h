#ifndef _CM7_MAIN_APP_H_
#define _CM7_MAIN_APP_H_

#ifdef __cplusplus
extern "C" {
#endif

int main_app(void);
void irq_uart3();
void irq_dma_uart6();

void receive_tcp_buffer(unsigned char *buff, size_t size);


#ifdef __cplusplus
}
#endif

#endif /* _CM7_MAIN_APP_H_ */
