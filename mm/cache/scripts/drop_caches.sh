#!/bin/bash
#
# https://www.kernel.org/doc/html/latest/admin-guide/sysctl/vm.html

# Free pagecache
echo 1 > /proc/sys/vm/drop_caches

# Free reclaimable slab objects
echo 2 > /proc/sys/vm/drop_caches

# Free slab objects and pagecache
echo 3 > /proc/sys/vm/drop_caches
