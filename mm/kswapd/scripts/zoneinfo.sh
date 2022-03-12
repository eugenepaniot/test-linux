#!/bin/bash

cat /proc/zoneinfo | grep -e DMA -e normal -i  -A 30 | grep -e low -e high -e min -e "pages free"
