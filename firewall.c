#include "firewall.h"

struct nf_hook_ops nf_ops;
struct sk_buff *sock_buff;
struct iphdr *ip_header;
struct udphdr *udp_header;
unsigned int udp_len;

static unsigned int Hook_Func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
    sock_buff = skb;
    /*if IP packet*/
    if (sock_buff->protocol == htons(ETH_P_IP)) {

        ip_header = (struct iphdr *)skb_network_header(sock_buff);

        /* if UDP protocol */
        if (ip_header->protocol == IPPROTO_UDP) {
            udp_header = (struct udphdr *)          skb_transport_header(sock_buff);
            pr_info("[***] received a UDP packet\n");

            /*if packet send to 7777 port*/
            if (udp_header->dest == htons(7777)) {
                udp_header->dest = htons(7778);
                pr_info("[***] port changed to 7778\n");
                pr_info("[***] Old checksum = 0x%x\n", htons(udp_header->check));

                udp_len = ntohs(ip_header->tot_len) - 20;
                udp_header->check = 0;
                udp_header->check = csum_tcpudp_magic(
                                    ip_header->saddr,
                                    ip_header->daddr,
                                    udp_len,
                                    ip_header->protocol,
                                    csum_partial((char *)udp_header, udp_len, 0));

                pr_info("[***] New checksum = 0x%x\n", htons(udp_header->check));
            }
        }
    }
    return NF_ACCEPT;
}

static int  __init mod_init(void)
{
    nf_ops.hook = Hook_Func;
    nf_ops.pf = PF_INET;
    nf_ops.hooknum = NF_INET_PRE_ROUTING;
    nf_ops.priority = NF_IP_PRI_FIRST;

    nf_register_hook(&nf_ops);
    pr_info("[*] FireWall loaded !\n");

    return 0;
}

static void __exit mod_exit(void)
{
    nf_unregister_hook(&nf_ops);
    pr_info("[*] FireWall unload !\n");
}
