#pragma once
#include <pcap.h>
#include <Winsock2.h>
#include <tchar.h>
#include <time.h>
#include <string>
#include "device_list.h"
#include "capture_device.h"
#include "looper.h"

class bpf
{
public:
	pcap_t* p;
	struct bpf_program* fp;
	bpf(pcap_t* p_in, const char* str, int optimize, bpf_u_int32 netmask);
	~bpf();
	void set_filter();
};