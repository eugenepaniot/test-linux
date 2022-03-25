#!/bin/bash

sudo bpftrace  -e 'BEGIN{$min = kaddr("min_free_kbytes"); printf("min_free_kbytes = %d\n", *$min);}'
