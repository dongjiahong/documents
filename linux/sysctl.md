## Linux内核网络参数调整

+ net.ipv4.tcp_syncookies 
 - 1：表示开启；0：表示关闭
 - 推荐：1
 - 当出现SYN等待队列溢出时，启用cookie来处理，可以防范syn攻击
+ net.ipv4.tcp_tw_reuse
 - 1：表示开启；0：表示关闭
 - 推荐：1
 - 表示开启重用，允许将TIME-WAIT sockets重新用于新的TCP连接
+ net.ipv4.tcp_keepalive_time
 - 整数数值（秒）
 - 推荐：1200
 - 表示当keepalive启用时，TCP发送keepalive消息的频度，默认2小时，推荐20分钟
+ net.ipv4.ip_local_port_range
 - 端口范围
 - 推荐：1024 65000
 - 表示用于向外连接的端口范围。默认：32768-61000，改为1024-65000。
+ net.ipv4.tcp_max_syn_backlog
 - 整数
 - 推荐：8192
 - 表示SYN队列的长度，默认为1024，加大队列长度为8192，可以容纳更多等待连接的网络连接数
+ net.ipv4.tcp_max_tw_buckets
 - 整数
 - 推荐：5000
 - 表示系统同时保持TIME_WAIT套接字的最大数量，如果超过这个数字，TIME_WAIT套接字将立刻被清除并打印警告信息。默认为180000，改为5000
+ net.core.netdev_max_backlog
 - 整数
 - 推荐：8192
 - 每个网络接口接受数据包的速率比内核处理这些包的速率快时，运行送到队列的数据包的最大数目。
+ net.ipv4.ip_forward = 0 禁用包过滤功能
+ net.ipv4.conf.default.rp_filter = 1 启用源路由核查功能
+ kernel.msgmnb = 65536 每个消息队列的大小
+ kernel.msgmax = 65536 系统最大消息队列数量限制
+ net.ipv4.tcp_window_scaling = 1 支持更大的TCP窗口。如果TCP窗口最大超过64k，必须为1
+ fs.file-max = 102400 文件句柄最大数量
+ net.ipv4.tcp_syn_recycle = 1 开启TCP链接中time_wait sockets的快速回收