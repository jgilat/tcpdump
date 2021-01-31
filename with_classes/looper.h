#pragma once
#include <pcap.h>
#include <Winsock2.h>
#include <tchar.h>
#include <time.h>
#include <string>
#include "device_list.h"
#include "capture_device.h"
#include "bpf.h"

class looper
{
public:
	looper(pcap_t* p, int cnt, pcap_handler callback, u_char* user);
	~looper();
};