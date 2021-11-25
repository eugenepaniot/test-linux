SELinux - Security Enhanced Linux
=============

# Links

* [https://wiki.centos.org/HowTos/SELinux](https://wiki.centos.org/HowTos/SELinux)

# 介绍

* Security-Enhanced Linux (SELinux) 是在内核中实现的强制访问控制 (MAC) 安全机制。
* SELinux 最初是在 CentOS 4 中引入的，并在后来的 CentOS 版本中得到了显着增强。
* 与内核交互数据方式`netlink`, 见`NETLINK_SELINUX`.

# 访问控制

操作系统有两类访问控制：自主访问控制（`DAC`）和强制访问控制（`MAC`）。
标准Linux安全是一种`DAC`，SELinux为Linux增加了一个灵活的和可配置的的`MAC`。

# SELinux 

configuration: `/etc/selinux/config`
relate commands: `getenforce`, `setenforce`

# SELinux 模式

SELinux 有三个模式（可以由用户设置）。这些模式将规定 SELinux 在主体请求时如何应对。这些模式是：

1. Enforcing强制— SELinux 策略强制执行，基于 SELinux 策略规则授予或拒绝主体对目标的访问
2. Permissive宽容— SELinux 策略不强制执行，不实际拒绝访问，但会有拒绝信息写入日志
3. Disabled禁用— 完全禁用 SELinux

# SELinux 策略 

SELinux 策略有两种：

1. Targeted目标 — 只有目标网络进程（dhcpd，httpd，named，nscd，ntpd，portmap，snmpd，squid，以及 syslogd）受保护
2. Strict严格 — 对所有进程完全的 SELinux 保护

# 相关命令

```bash
id -Z
ls -Z
```
