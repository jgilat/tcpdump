#pragma once
#include <pcap.h>
#include <Winsock2.h>
#include <tchar.h>
#include <time.h>
#include <string>
#include "device_list.h"
#include "bpf.h"
#include "looper.h"


class capture_device {
public:
	pcap_t* adhandle; //pcap handle will be public since looper and bpf need direct access to the specific instance of it
	capture_device(pcap_if_t* d, char* errbuf);
	~capture_device();
	void check_datalink();
	void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data);
};
