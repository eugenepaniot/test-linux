# Netfilter

filter package

# hook

* NF_HOOK
* NF_HOOK_COND
* NF_HOOK_THRESH

# nf inet

* NF_INET_PRE_ROUTING
* NF_INET_LOCAL_IN
* NF_INET_FORWARD
* NF_INET_LOCAL_OUT
* NF_INET_POST_ROUTING
* NF_INET_NUMHOOKS

# nf proto

* NFPROTO_UNSPEC
* NFPROTO_INET
* NFPROTO_IPV4
* NFPROTO_ARP
* NFPROTO_NETDEV
* NFPROTO_BRIDGE
* NFPROTO_IPV6
* NFPROTO_DECNET
* NFPROTO_NUMPROTO


# static key

```c
struct static_key nf_hooks_needed[NFPROTO_NUMPROTO][NF_MAX_HOOKS];
```
