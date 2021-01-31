#include "bpf.h"

bpf::bpf(pcap_t* p, struct bpf_program* fp,	const char* str, int optimize, bpf_u_int32 netmask) {
	//compile the filter
	if (pcap_compile(p, fp, str, optimize, netmask) < 0)
	{
		fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");
		return;
	}
}

bpf::~bpf() {
	struct bpf_program* fp;
	pcap_freecode(fp);
}

void bpf::set_filter() {
	//set the filter
	struct bpf_program* fp;
	pcap_t* p;
	if (pcap_setfilter(p, fp) < 0)
	{
		fprintf(stderr, "\nError setting the filter.\n");
		return;
	}
}