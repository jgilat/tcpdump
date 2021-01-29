# tcpdump
tcpdump implemented on windows 10.

tcmpdump is a standard in network sniffing: parses a readable filter expression -> prints filtered packets received from the network tap. "the cmd equiv of wireshark".

Resources used
-

BPF Syntax: https://biot.com/capstats/bpf.html just a standard for defining a filter for incoming packets.

How tcpdump looks like on Linux: https://www.poftut.com/tcpdump-tutorial-with-examples/

Linux tcpdump's man: https://www.tcpdump.org/manpages/tcpdump.1.html

Npcap dev tutorial: https://nmap.org/npcap/guide/npcap-tutorial.html


Suggestion for an architecture of a Windows tcpdump:
-
1. Get a list of attached network adapters: pcap_if_t *alldevs;
2. Receive BPF filter from user via cmd
3. Sniff packets from selected network adapter: pcap_open()
4. Filter according to BPF selection: pcap_compile(), pcap_setfilter(). Specific BPF convention can be found here: https://nmap.org/npcap/guide/wpcap/pcap-filter.html
5. Print packets to cmd: printf()
