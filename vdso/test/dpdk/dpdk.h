/**
 * File: dpdk.h
 * Author: Rong Tao (rongtao.cestc.cn)
 * Date: 2022-03-11
 *
 * Get tsc frequency
 */

#pragma once

uint64_t
get_tsc_freq_arch(void);

uint64_t
get_tsc_freq(void);
