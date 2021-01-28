# tcpdump
tcpdump implemented on windows 10


tcmpdump is a standard in network sniffing: parses a readable filter expression -> prints filtered packets received from the network tap. "the cmd equiv of wireshark".


BPF Syntax:
https://biot.com/capstats/bpf.html

Just a standard for defining a filter for incoming packets.

How tcpdump looks like on Linux:
https://www.poftut.com/tcpdump-tutorial-with-examples/


Linux tcpdump's man: https://www.tcpdump.org/manpages/tcpdump.1.html


Suggestion for an architecture of a Windows tcpdump:
1. Receive input from user via cmd
2. Class that receives packets from network card
3. Class that filters them according to the input from the user
4. Class that prints output to the user
(update the above to include interfaces to npcap and the pcap interface)
