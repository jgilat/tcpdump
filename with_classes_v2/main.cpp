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
	pcap_if_t* alldevs;
	pcap_if_t* d;
	pcap_t* adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	u_int netmask;
	char packet_filter[256];
	struct bpf_program fcode;

	/* Load Npcap and its functions. */
	if (!LoadNpcapDlls())
	{
		fprintf(stderr, "Couldn't load Npcap\n");
		exit(1);
	}

	{
		device_list device{alldevs, errbuf, d};
		//implement here: copy to another location in memory the device the user chose
	} //out of scope -> device obj destructs

	printf("Enter the bpf filter:");
	scanf_s("%s", packet_filter, 256);

	{
		capture_device capture{adhandle, d, errbuf};
		capture.check_datalink();

		if (d->addresses != NULL)
			/* Retrieve the mask of the first address of the interface */
			netmask = ((struct sockaddr_in*)(d->addresses->netmask))->sin_addr.S_un.S_addr;
		else
			/* If the interface is without addresses we suppose to be in a C class network */
			netmask = 0xffffff;

		{
			bpf filter{adhandle, &fcode, packet_filter, 1, netmask};
			filter.set_filter();

		} //out of scope -> filter obj destructs

		printf("\nlistening on %s...\n", d->description);

		{
			looper loop{adhandle, 0, capture.packet_handler, NULL};
			//add an option for user interrupt here
		} //out of scope -> loop obj destructs
	} //out of scope -> capture obj destructs

	return 0;
}