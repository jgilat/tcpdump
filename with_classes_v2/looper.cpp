#include "looper.h"

looper::looper(pcap_t* p_in, int cnt, pcap_handler callback, u_char* user) {
	/* start the capture */
	p = p_in;
	pcap_loop(p, cnt, callback, user);
}

looper::~looper() {
	pcap_breakloop(p);
}