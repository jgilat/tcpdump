#include "bpf.h"

bpf::bpf(pcap_t* p_in, const char* str, int optimize, bpf_u_int32 netmask) {
	p = p_in;

	//compile the filter
	if (pcap_compile(p, fp, str, optimize, netmask) < 0)
	{
		fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");
		return;
	}
}

bpf::~bpf() {
	pcap_freecode(fp);
}

void bpf::set_filter() {
	//set the filter
	if (pcap_setfilter(p, fp) < 0)
	{
		fprintf(stderr, "\nError setting the filter.\n");
		return;
	}
}