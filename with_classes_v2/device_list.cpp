#include "device_list.h"

device_list::device_list(pcap_if_t** alldevs_in, char* errbuf, pcap_if_t* d) {
	int inum;
	int i = 0;
	alldevs = alldevs_in;
	alldevs_s = *alldevs;

	/* Retrieve the device list */
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	/* Print the list */
	for (d = alldevs_s; d; d = d->next)
	{
		printf("%d. %s", ++i, d->name);
		if (d->description)
			printf(" (%s)\n", d->description);
		else
			printf(" (No description available)\n");
	}

	if (i == 0)
	{
		printf("\nNo interfaces found! Make sure Npcap is installed.\n");
		return;
	}

	printf("Enter the interface number (1-%d):", i);
	scanf_s("%d", &inum);

	if (inum < 1 || inum > i)
	{
		printf("\nInterface number out of range.\n");
		/* Free the device list */
		pcap_freealldevs(alldevs_s);
		return;
	}

	/* Jump to the selected adapter */
	for (d = alldevs_s, i = 0; i < inum - 1; d = d->next, i++);

}



device_list::~device_list() {
	pcap_freealldevs(alldevs_s);
}

