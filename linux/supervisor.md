## Supervisor安装和配置

### 安装supervisor
可以使用Python的`pip`进行安装`sudo pip install supervisor`安装后主要有下面三个程序：
+ supervisortd **supervisor的守护进程服务（用于接收进程管理命令）**
+ supervisorctl **supervisor的客户端（用于和守护进程通信，发送管理进程的指令）**
+ echo_supervisord_conf **初始化配置文件**
+ 配置初始化文件`sudo echo_supervisord_conf > /etc/supervisord.conf`

### 修改配置
supervisord.conf文件就是默认的配置文件，我们需要修改`include`项，这样我们可以将不同的
程序写到不同的配置文件中。

```ini
[include]
files = /etc/supervisor.d/*.conf
```
这样我们就可以将配置文件分开写在`/etc/supervisor.d/`目录中

### 启动supervisor
这里我们使用`-c`选项，如果不指定路径会安这个顺序查找配置文件: 
`$CWD/supervisord.conf, $CWD/etc/supervisord.conf, /etc/supervisord.conf`

```sh
supervisord -c /etc/supervisord.conf # 启动

ps -ef | grep supervisord # 验证
```

下面是一个简单的常用配置说明:

```ini
[program:example]	; program表示一个服务，example表示服务的名字

directory = /Users/lele/tmp/supervisor  ; 程序启动目录 
command = go run example.go             ; 程序启动指令
autostart = true                        ; 在supervisord启动时也自动启动  
startsecs = 5                           ; 启动5秒后没有异常退出，就当做正常启动 
startretries = 3                        ; 启动失败自动重试次数，默认是 3                               

; 程序异常退出后重新启动;默认unexpected，表示服务的退出码不是exitcodes配置的值就重启；true表示不管
; 服务的退出状态都重启；false表示不重启
autorestart = unexpected                
exitcodes = 0, 2

user = lele                             ; 那个用户启动,一般不用root。 
redirect_stderr = true                  ; 把stderr重定向到stdout,默认是false                           
stdout_logfile_maxbytes = 20MB  ; stdout 日志文件大小，默认 50MB                                       
stdout_logfile_backups = 20     ; stdout 日志文件备份数                                                
 
; stdout 日志文件，需要注意当指定目录不存在时无法正常启动，所以需要手动创建目录（supervisord 会自动创建日志文件）
stdout_logfile = /Users/lele/tmp/supervisor/example_stdout.log 
```

### 注意事项
supervisor判断是的`command`配置的命令，所以如果你的程序是二进制可执行程序就向如下：
`command = ./echo > log 2>&1 &` 而不要用一个脚本包裹这条命令后在`command`中执行那个脚本，这会导致
服务没法重启。

在`command`中最好将路径都写成绝对路径而不要写相对路径。由于环境变量的问题可能会导致服务部能成功

如果使用`stdout_logfile`字段，后面的路径一定要完整，目录要提前创建好，最后的log文件名称也要给出，
不然可能会报类似于`INFO spawnerr: unknown error making dispatchers for 'tworker': EISDIR`这样的
错误.

一般不要在`command`中配置指令时，将日志重定向也给添加到命令中，我们可以使用下面几个指令来代替该
功能:

```ini
redirect_stderr = true                  ; 把stderr重定向到stdout,默认是false                           
stdout_logfile_maxbytes = 20MB  ; stdout 日志文件大小，默认 50MB                                       
stdout_logfile_backups = 20     ; stdout 日志文件备份数                                                
; stdout 日志文件，需要注意当指定目录不存在时无法正常启动，所以需要手动创建目录（supervisord 会自动创建日志文件）
stdout_logfile = /Users/lele/tmp/supervisor/example_stdout.log 
```
这样就将日志重定向输出到log中了。
