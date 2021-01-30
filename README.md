# tcpdump
tcpdump implemented on windows 10.

tcmpdump is a standard in network sniffing: parses a readable filter expression -> prints filtered packets received from the network tap. "the cmd equiv of wireshark".

Resources used
-

BPF Syntax: https://biot.com/capstats/bpf.html just a standard for defining a filter for incoming packets.

How tcpdump looks like on Linux: https://www.poftut.com/tcpdump-tutorial-with-examples/

Linux tcpdump's man: https://www.tcpdump.org/manpages/tcpdump.1.html

Npcap dev tutorial: https://nmap.org/npcap/guide/npcap-tutorial.html


Header files (one for each proposed class) and their main functions
-

- BPF.h
  - Init: LoadNpcapDlls()
  - Get a list of network adapters from computer: pcap_findalldevs_ex()
  - Get BPF from user: scanf_s()
  - Open the adapter and free device list: pcap_open(), pcap_freealldevs()
  - Compile and set BPF: pcap_compile(), pcap_setfilter()
  
- Sniffer.h
  - Start the capture: pcap_loop()
  - Handle the packets: packet_handler()
