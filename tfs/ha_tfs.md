### TFS的HA部署

#### 安装heartbeat

参考文档：[tfs_ha部署](http://www.docin.com/p-534458301.html)
安装heartbeat我们需要执行`yum install heartbeat`但是可能得到的是`No package heartbeat available.` 这时我们需要如下指令：
```sh
# wget http://mirrors.sohu.com/fedora-epel/6/i386/epel-release-6-8.noarch.rpm
# rpm -ivh epel-release-6-8.noarch.rpm

# 执行上面的指令后我们在次安装就好了，这里安装的是3.0版本
# yum install heartbeat
```
#### 设置虚拟ip
我们先查看目前的本机ip信息
```sh
# ifconfig 
inet addr:10.21.13.21  Bcast:10.21.15.255  Mask:255.255.240.0

# 配置虚拟ip
ifconfig eth0:0 10.21.13.100 netmask 255.255.240.0 up

# 再次查看 ifconfig
eth0:0    Link encap:Ethernet  HWaddr 06:48:AA:67:1E:65  
          inet addr:10.21.13.100  Bcast:10.21.15.255  Mask:255.255.240.0
```

