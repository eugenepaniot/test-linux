#!/bin/bash 

kvm=`egrep -c '(vmx|svm)' /proc/cpuinfo`
if [ kvm = 0 ]; then
	echo "Not support vmx or svm"
else
	echo "Support KVM"
fi
