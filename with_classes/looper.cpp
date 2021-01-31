#include "looper.h"

looper::looper(pcap_t* p, int cnt, pcap_handler callback, u_char* user) {
	/* start the capture */
	pcap_loop(p, cnt, callback, user);
}

looper::~looper() {
	pcap_t* p;
	pcap_breakloop(p);
}