#!/bin/bash 

function dmesg_tail() {
	dmesg | tail
}
function dmesg_kernel_tail() {
	dmesg -k | tail
}
dmesg_tail
