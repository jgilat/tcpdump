#include <pcap.h>
#include <Winsock2.h>
#include <tchar.h>
#include <time.h>
#include <string>
#include "device_list.h"
#include "capture_device.h"
#include "bpf.h"
#include "looper.h"
#pragma comment (lib, "ws2_32.lib")

BOOL LoadNpcapDlls()
{
	_TCHAR npcap_dir[512];
	UINT len;
	len = GetSystemDirectory(npcap_dir, 480);
	if (!len) {
		fprintf(stderr, "Error in GetSystemDirectory: %x", GetLastError());
		return FALSE;
	}
	_tcscat_s(npcap_dir, 512, _T("\\Npcap"));
	if (SetDllDirectory(npcap_dir) == 0) {
		fprintf(stderr, "Error in SetDllDirectory: %x", GetLastError());
		return FALSE;
	}
	return TRUE;
}

int main()
{
	pcap_if_t* d;
	char errbuf[PCAP_ERRBUF_SIZE];

	/* Load Npcap and its functions. */
	if (!LoadNpcapDlls())
	{
		fprintf(stderr, "Couldn't load Npcap\n");
		exit(1);
	}

	{
		device_list device{errbuf, d};
	} //out of scope -> device obj destructs

	{
		char packet_filter[256];
		printf("Enter the bpf filter:");
		scanf_s("%s", packet_filter, 256);

		capture_device capture{d, errbuf};
		capture.check_datalink();
		{
			u_int netmask;
			if (d->addresses != NULL)
				/* Retrieve the mask of the first address of the interface */
				netmask = ((struct sockaddr_in*)(d->addresses->netmask))->sin_addr.S_un.S_addr;
			else
				/* If the interface is without addresses we suppose to be in a C class network */
				netmask = 0xffffff;
				bpf filter{capture.adhandle, packet_filter, 1, netmask};
				filter.set_filter();
		} //out of scope -> filter obj & netmask destruct

		{
			printf("\nlistening on %s...\n", d->description);
			looper loop{capture.adhandle, 0, capture.packet_handler, NULL}; //change to work with pcap_next, work with a loop, ...
			//... add an option for user interrupt. 
		} //out of scope -> loop obj destructs
	} //out of scope -> capture obj, packet_filter destruct

	return 0;
}