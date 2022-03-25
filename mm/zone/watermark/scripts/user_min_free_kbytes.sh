#!/bin/bash

sudo bpftrace  -e 'BEGIN{$min = kaddr("user_min_free_kbytes"); printf("user_min_free_kbytes = %d\n", *$min);}'
