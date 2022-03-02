Cache
=========

1. dcache (dentry slab)
2. pagecache


```bash
$ echo 3 > /proc/sys/vm/drop_caches
```

其中`3` 表示：

```c
int drop_caches_sysctl_handler(struct ctl_table *table, int write,
		void *buffer, size_t *length, loff_t *ppos)
{
	...
		if (sysctl_drop_caches & 1) {
			iterate_supers(drop_pagecache_sb, NULL);
			count_vm_event(DROP_PAGECACHE);
		}
		if (sysctl_drop_caches & 2) {
			drop_slab();
			count_vm_event(DROP_SLAB);
		}
	...
}
```

从而分为两种

* `drop_pagecache_sb()`
* `drop_slab()`
