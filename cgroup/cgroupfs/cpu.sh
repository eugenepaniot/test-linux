#!/bin/bash 
# Rong Tao 2021.11.16
# test cgroup
# Need `libcgroup-tools`, you can install with
# $ sudo yum install libcgroup-tools

# create cgroup CPU
# will create cgroupfs: /sys/fs/cgroup/cpu/rongtao/
cgcreate -g cpu:rongtao

# limits cgroup CPU util 30%
echo 30000 >  /sys/fs/cgroup/cpu/rongtao/cpu.cfs_quota_us

# execute two processes
while :; do :; done &
while :; do :; done &

# use pidof or ps check above processes PID 
# and add to cgroup
cgclassify -g cpu:rongtao 181481
cgclassify -g cpu:rongtao 181482

# check cgroup's processes
# will show 
# 181481
# 181482
more /sys/fs/cgroup/cpu/rongtao/tasks

# delete cgroup
# will delete cgroupfs: /sys/fs/cgroup/cpu/rongtao/
cgdelete -g cpu:rongtao

