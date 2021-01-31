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
	bpf(pcap_t* p, struct bpf_program* fp, const char* str, int optimize, bpf_u_int32 netmask);
	~bpf();
	void set_filter();
};