#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/string.h>
#include <linux/inet.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Benny");
MODULE_DESCRIPTION("Log the source and destination Ip's module.");
MODULE_VERSION("0.01");


static unsigned int nf_log_handler(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
    struct iphdr *iph;

    if(!skb)
        return NF_ACCEPT;

    iph = ip_hdr(skb);

    if( &iph->daddr == in_aton("103.86.96.100") ){
        printk(KERN_INFO "NF_DROP - Source IP: %pI4, Destination IP: %pI4\n", &iph->addrs, &iph->daddr);
        return NF_DROP;
    }
    printk(KERN_INFO "NF_ACCEPT - Source IP: %pI4, Destination IP: %pI4\n", &iph->addrs, &iph->daddr);

    return NF_ACCEPT;
}

static struct nf_hook_ops nf_log_ops = {
        .hook       = (nf_hookfn*)nf_log_handler,
        .hooknum    = NF_INET_LOCAL_OUT,
        .pf         = NFPROTO_IPV4,
        .priority   = NF_IP_PRI_FIRST,
};

static int __init log_init(void) {
    nf_register_net_hook(&init_net, &nf_log_ops);
    return 0;
}

static void __exit log_exit(void) {
    nf_unregister_net_hook(&init_net, &nf_log_ops);
}

module_init(log_init);
module_exit(log_exit);