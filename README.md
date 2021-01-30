# Poor man's tcpdump on Windows

tcmpdump is a standard in network sniffing: parses a readable filter expression -> prints filtered packets received from the network tap. "the cmd equiv of wireshark".

Resources used
-

BPF Syntax: https://biot.com/capstats/bpf.html just a standard for defining a filter for incoming packets.

How tcpdump looks like on Linux: https://www.poftut.com/tcpdump-tutorial-with-examples/

Linux tcpdump's man: https://www.tcpdump.org/manpages/tcpdump.1.html

Npcap dev tutorial: https://nmap.org/npcap/guide/npcap-tutorial.html

New proposition for classes
-

- device_list():  
  - ctor: pcap_findalldevs_ex()
  - dtor: pcap_freealldevs(alldevs)
- capture_device() (when created, receives a device from device_list object):
  - ctor: pcap_open()
  - dtor: pcap_close()
  - funcs: pcap_loop(), packet_handler(), pcap_datalink(), packet_handler() (latter func must be public since looper() ctor will use it)
- BPF() (when created, receives a capture_device object):
  - ctor: pcap_compile()
  - dtor: pcap_freecode()
  - funcs: pcap_setfilter()
- looper() (when created, receives a capture_device object):
  - ctor: pcap_loop()
  - dtor: pcap_breakloop()
- funcs to remain on main():
  - LoadNpcapDlls()
