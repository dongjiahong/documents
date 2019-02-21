## 基本操作

1.创建库`create database abc;`
2.删除库`drop database abc;`

### 授权
格式:> `grant 权限1,权限2,…权限n on 数据库名称.表名称 to 用户名@用户地址 identified by '连接口令';`

* 权限1,2...可以被`all privileges`或者`all`代替,表示给用户全部权限
* 数据库名.表名,可以被`*.*`代替表示给用于操作服务器上所有数据库所有表的权限
* 用户地址可以是localhost,ip,域名。也可以是`'%'`表示任何地方都能链接

#### 示例：
`grant all privileges on crawl.* to joe@'%';` 将数据库`crawl`里的所有表的所有权限都给用户`joe`，而
且可以从任何地方访问到该库

### 备份和还原

备份某些表,指令:> `mysqldump -hhostname -uusername -ppassword databasename table1 table2 > bakfile.sql`

还原某些表,指令:> `mysql -hhostname -uusername -ppassword databasename < bakfile.sql`

将数据库转移到新服务器,指令:> `mysqldump -uusername -ppassword databasename | mysql –host=*.*.*.* -C databasename`
