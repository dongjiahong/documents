Linux日常运维日志
----

### yum指令
如果你执行`yum search **` 时发现 **Segmentation fault** 这一般是你自己编译了`libz.so`这个包造成的，这里一般清理缓存就好，执行`yum clean all`如果还是不行那么需要你重新将`libz.so`的包链接会久版本.

### libc.so问题
这里一个很关键的包缺少这个包会导致几乎所有的指令都不能用了，这时你需要将软连接给链会去就好，执行如下：
```shell
#LD_PRELOAD=/lib/libc-2.6.1.so ln -s /lib/libc-2.6.1.so libc.so.6
```
还有一个问题是，一但你修改了这个libc.so.6的软链，yum就不能用了，就想上面的问题，可以使用`yum clean all` 解决，但是这样`libc.so.6`的软链将会被修改回去

### 防火墙iptables
防火墙的配置在文件`/etc/sysconfig/iptables` 
公司里默认是只有`22`端口给打开的别的都给墙了，所以如果你想用一个自己定义的端口,那么需要打开防火墙在防火墙里添加如下一条信息
```sh
# 65000 是我自定义的端口
-A INPUT -m state --state NEW -m tcp -p tcp --dport 65000 -j ACCEPT 
```
当添加白名单后需要更新防火墙`iptables`执行下面指令
```sh
service iptables restart
```
### curl指令
curl指令是我们常用的指令，默认使用`GET`方法如：
```sh
curl "www.baidu.com" -v
```

`-v`选项是说让返回显示详细内容,那么如果我们想使用`POST`方法呢？

```sh
curl -d "param2=nickwolfe&param2=12345" "http://www.example.com/a1" -v
```
没错就是`-d`选项；当然我们也可以使用`-H`来指定请求的头部如：
```sh
curl "localhost:22222/appinfo" -H 'Content-Type: application/json' -d '[{"id":1,"app_name":"xyz"},{"id":2,"app_name":"abc"}]' -v
```

### vmstat
使用`vmstat`命令来查看机器当前的任务状态使用方式 `vmstat n`其中n是数字表示刷新频率

```
procs -----------memory---------- ---swap-- -----io---- --system-- -----cpu-----
r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
2  0      0 1786124  14536 13011576    0    0     1   155   51  106 18  4 79  0  0	
5  0      0 1783380  14536 13013116    0    0     0    20 45871 16803 41 15 43  0  1	
1  0      0 1781892  14544 13014880    0    0     0    12 47247 17795 36 16 47  0  1	
1  0      0 1781148  14552 13015988    0    0     0    12 45041 17319 33 12 54  0  1	
3  0      0 1776932  14552 13017768    0    0     0     0 47765 17296 38 15 47  0  1
```

上面发现第一列表示任务队列，变化`2-5-1-1-3`表示2个任务后加了3个任务然后完成4各任务...

### 磁盘挂载
如果获取一个磁盘在`/dev/sdb` 想让它挂载在系统需要下面几步：

* 格式化 `mkfs -t ext4 /dev/sdb`
* 创建挂载路径 `mkdir -p /pdata1`
* 挂载磁盘 `mount /dev/sdb /pdata1`

如上操作就将磁盘挂载到目录 `/pdata1`
