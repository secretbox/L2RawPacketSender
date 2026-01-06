/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 */
 /*It's a raw socket example*/

#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>

#define MY_DEST_MAC0	0xff
#define MY_DEST_MAC1	0xff
#define MY_DEST_MAC2	0xff
#define MY_DEST_MAC3	0xff
#define MY_DEST_MAC4	0xff
#define MY_DEST_MAC5	0xff

#define DEFAULT_IF	"eth0"
#define BUF_SIZ		1024

int main(int argc, char *argv[])
{
	int sockfd;
	struct ifreq if_idx;

	struct ifreq if_mac;
	int tx_len = 0;
	char sendbuf[BUF_SIZ];
	struct ether_header *eh = (struct ether_header *) sendbuf;
	struct iphdr *iph = (struct iphdr *) (sendbuf + sizeof(struct ether_header));
	struct sockaddr_ll socket_address;
	char ifName[IFNAMSIZ];
	
	/* Get interface name */
	if (argc > 1)
		strcpy(ifName, argv[1]);
	else
		strcpy(ifName, DEFAULT_IF);

	/* Open RAW socket to send on */
	if ((sockfd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW)) == -1) {
	    perror("socket");
	}

	/* Get the index of the interface to send on */
	memset(&if_idx, 0, sizeof(struct ifreq));
	strncpy(if_idx.ifr_name, ifName, IFNAMSIZ-1);
	if (ioctl(sockfd, SIOCGIFINDEX, &if_idx) < 0)
	    perror("SIOCGIFINDEX");
	/* Get the MAC address of the interface to send on */
	memset(&if_mac, 0, sizeof(struct ifreq));
	strncpy(if_mac.ifr_name, ifName, IFNAMSIZ-1);
	if (ioctl(sockfd, SIOCGIFHWADDR, &if_mac) < 0)
	    perror("SIOCGIFHWADDR");

	/* Construct the Ethernet header */
	memset(sendbuf, 0, BUF_SIZ);
	/* Ethernet header */
	eh->ether_shost[0] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[0];
	eh->ether_shost[1] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[1];
	eh->ether_shost[2] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[2];
	eh->ether_shost[3] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[3];
	eh->ether_shost[4] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[4];
	eh->ether_shost[5] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[5];
	eh->ether_dhost[0] = MY_DEST_MAC0;
	eh->ether_dhost[1] = MY_DEST_MAC1;
	eh->ether_dhost[2] = MY_DEST_MAC2;
	eh->ether_dhost[3] = MY_DEST_MAC3;
	eh->ether_dhost[4] = MY_DEST_MAC4;
	eh->ether_dhost[5] = MY_DEST_MAC5;
	/* Ethertype field */
	/*eh->ether_type = htons(ETH_P_IP);*/
	eh->ether_type = htons(0x0802);
	tx_len += sizeof(struct ether_header);

	/* Packet data */
	sendbuf[tx_len++] = 0x00;
	sendbuf[tx_len++] = 0x01;
	/*0x010*/
	sendbuf[tx_len++] = 0x00;
	sendbuf[tx_len++] = 0x00;
	sendbuf[tx_len++] = 0x00;
	sendbuf[tx_len++] = 0x06;
	sendbuf[tx_len++] = 0x00;
	sendbuf[tx_len++] = 0x4e;
	sendbuf[tx_len++] = 0x00;
	sendbuf[tx_len++] = 0x8d;
	
	sendbuf[tx_len++] = 0x00;
	sendbuf[tx_len++] = 0x08;
	sendbuf[tx_len++] = 0x00;
	sendbuf[tx_len++] = 0x00;
	sendbuf[tx_len++] = 0x00;
	sendbuf[tx_len++] = 0x02;
	sendbuf[tx_len++] = 0x00;
	sendbuf[tx_len++] = 0x8c;
	
	/* 0x0020 */
	sendbuf[tx_len++] = 0x00;
	sendbuf[tx_len++] = 0x34;
	sendbuf[tx_len++] = 0xc0;
	sendbuf[tx_len++] = 0xa8;
	sendbuf[tx_len++] = 0x7f;
	sendbuf[tx_len++] = 0xf0;
	sendbuf[tx_len++] = 0x00;
	sendbuf[tx_len++] = 0x90;

	sendbuf[tx_len++] = 0xe8;
	sendbuf[tx_len++] = 0x48;
	sendbuf[tx_len++] = 0x01;
	sendbuf[tx_len++] = 0xd8;
	sendbuf[tx_len++] = 0xc0;
	sendbuf[tx_len++] = 0xa8;
	sendbuf[tx_len++] = 0x7f;
	sendbuf[tx_len++] = 0x05;

	/*0x0030*/
	sendbuf[tx_len++] = 0xb8;
	sendbuf[tx_len++] = 0x27;
	sendbuf[tx_len++] = 0xeb;
	sendbuf[tx_len++] = 0x79;
	sendbuf[tx_len++] = 0x95;
	sendbuf[tx_len++] = 0x27;
	sendbuf[tx_len++] = 0x00;
	sendbuf[tx_len++] = 0x00;
	
	sendbuf[tx_len++] = 0x0c;
	sendbuf[tx_len++] = 0xfb;
	sendbuf[tx_len++] = 0xc0;
	sendbuf[tx_len++] = 0xa8;
	sendbuf[tx_len++] = 0x7f;
	sendbuf[tx_len++] = 0xf1;
	sendbuf[tx_len++] = 0x00;
	sendbuf[tx_len++] = 0x90;
	
	/*0x0040*/

	sendbuf[tx_len++] = 0xe8;
	sendbuf[tx_len++] = 0x43;
	sendbuf[tx_len++] = 0x8d;
	sendbuf[tx_len++] = 0x9c;
	sendbuf[tx_len++] = 0xc0;
	sendbuf[tx_len++] = 0xa8;
	sendbuf[tx_len++] = 0x7f;
	sendbuf[tx_len++] = 0x05;
	
	sendbuf[tx_len++] = 0xb8;
	sendbuf[tx_len++] = 0x27;
	sendbuf[tx_len++] = 0xeb;
	sendbuf[tx_len++] = 0x79;
	sendbuf[tx_len++] = 0x95;
	sendbuf[tx_len++] = 0x27;
	sendbuf[tx_len++] = 0x00;
	sendbuf[tx_len++] = 0x00;

	/* 0x0050 */

	sendbuf[tx_len++] = 0x0c;
	sendbuf[tx_len++] = 0xfb;
	sendbuf[tx_len++] = 0x00;
	sendbuf[tx_len++] = 0x88;
	sendbuf[tx_len++] = 0x00;
	sendbuf[tx_len++] = 0x0a;
	sendbuf[tx_len++] = 0xa2;
	sendbuf[tx_len++] = 0x90;

	sendbuf[tx_len++] = 0xe8;
	sendbuf[tx_len++] = 0x69;
	sendbuf[tx_len++] = 0x17;
	sendbuf[tx_len++] = 0x22;

	
	
	/* Index of the network device */
	socket_address.sll_ifindex = if_idx.ifr_ifindex;
	/* Address length*/
	socket_address.sll_halen = ETH_ALEN;
	/* Destination MAC */
	socket_address.sll_addr[0] = MY_DEST_MAC0;
	socket_address.sll_addr[1] = MY_DEST_MAC1;
	socket_address.sll_addr[2] = MY_DEST_MAC2;
	socket_address.sll_addr[3] = MY_DEST_MAC3;
	socket_address.sll_addr[4] = MY_DEST_MAC4;
	socket_address.sll_addr[5] = MY_DEST_MAC5;

	/* Send packet */
	if (sendto(sockfd, sendbuf, tx_len, 0, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll)) < 0)
	    printf("Send failed\n");

	return 0;
}
