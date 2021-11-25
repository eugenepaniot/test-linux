#!/bin/bash 
# https://milestone-of-se.nesuke.com/en/sv-advanced/selinux/selinux-summary/

yum -y install attr
touch test1.txt
getfattr -m security.selinux -d test1.txt
# file: test1.txt
#security.selinux="unconfined_u:object_r:admin_home_t:s0"
setfattr -n security.selinux -v system_u:object_r:httpd_sys_content_t:s0 test1.txt
getfattr -m security.selinux -d test1.txt
# file: test1.txt
#security.selinux="system_u:object_r:httpd_sys_content_t:s0"
