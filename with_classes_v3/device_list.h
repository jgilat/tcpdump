#pragma once
#include <pcap.h>
#include <Winsock2.h>
#include <tchar.h>
#include <time.h>
#include <string>
#include "capture_device.h"
#include "bpf.h"
#include "looper.h"

class device_list
{
public:
	pcap_if_t** alldevs;
	pcap_if_t* alldevs_s;
	device_list(char* errbuf, pcap_if_t* d);
	~device_list();
};