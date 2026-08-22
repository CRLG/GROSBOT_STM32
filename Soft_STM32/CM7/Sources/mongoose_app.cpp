#include "mongoose.h"


struct mg_mgr g_mgr;  // Mongoose event manager
struct mg_connection *mgr_tcp_connection = NULL;


// ____________________________________________
unsigned char send_tcp_buffer(unsigned char *buff, size_t size)
{
	//if (HAL_GetTick() < 20000) return false;
	if (mgr_tcp_connection == NULL) return 0;
	return mg_send(mgr_tcp_connection, buff, size);
}

// ____________________________________________
void tcp_callback(struct mg_connection *c, int ev, void *ev_data)
{
  if (ev == MG_EV_ACCEPT) {
	mgr_tcp_connection = c;
  }
  else if (ev == MG_EV_CLOSE) {
	mgr_tcp_connection = NULL;
  }
  else if (ev == MG_EV_READ) {
	 receive_tcp_buffer(c->recv.buf, c->recv.len);
    // Clear the receive buffer
    c->recv.len = 0;
    mgr_tcp_connection = c;
  }
}


// ____________________________________________
void mongoose_init(unsigned int mg_debug_level)
{
  mg_log_set(mg_debug_level);  // Set log level to debug
  mg_mgr_init(&g_mgr);      // Initialise event manager

  MG_INFO(("Starting TCP Server 234596"));
  if (mg_listen(&g_mgr, "tcp://0.0.0.1:234596", tcp_callback, NULL) == NULL) {
    MG_INFO(("Failed to start UDP server"));
  }

  MG_INFO(("Mongoose init complete"));
}

// ____________________________________________
void mongoose_poll(void) 
{
  mg_mgr_poll(&g_mgr, 0);
}

