#ifndef FIREWALL_H
#define FIREWALL_H

#include <linux/module.h>
#include <linux/kernel.h>
// #undef __KERNEL__
#include <linux/netfilter_ipv4.h>
// #define __KERNEL__
#include <linux/netfilter.h>
#include <linux/skbuff.h>
#include <linux/udp.h>
#include <linux/ip.h>
#include <net/ip.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anton Bobrovsky <ileon009@gmail.com>");
MODULE_DESCRIPTION("Test netfilter module for linux kernel");

static int  __init mod_init(void);
static void __exit mod_exit(void);

module_init(mod_init);
module_exit(mod_exit);

#endif /* FIREWALL_H */
