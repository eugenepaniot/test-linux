#!/bin/bash

sudo perf record -e block:block_rq_issue -ag
sudo perf report
