## GnuMakeManual
### 1.简介
GnuMake 需要一个文档被命名为`makefile`、`Makefile`等。这里推荐使用`Makefile`，其主要规则：
```make
target1: target2
	command
target2: prerequiries
	command
...
```
就是你的编译`目标`回去寻找`依赖`,而`依赖`也可以是`目标`，然后是执行的命令，这里需要一个`tab`的分隔
当然可以编写多个`target` 但是只有第一个目标被认为是默认目标，也就是你执行`make`后面不跟目标所执行的
那个目标。通常将第一个目标定位编译全部目标一般命名为`all`

### 2.使用变量 
在make中我们可以使用变量来简化书写，常用的变量语法如下：
```make
VPATH = src:../headers

variable = deferred #基本赋值会将整个makefile展开后再决定变量值
variable := deferred #覆盖之前的赋值,直接赋值而不是跟上面一样要完全展开makefile
variable ?= deferred #条件赋值操作符,只有此变量在之前没有赋值的情况下才会赋值
variable += deferred or variable #对变量进行追加操作

define variable
	deferred
endef
```

make变量`VPATH`的值指定了make搜索的目录，经常是那些包含依赖的目录，可以指定多个目录用冒号分隔`:`
```make
VPATH = src:../headers
foo:foo.c
```
make会现在本目录找`foo.c`如果没哟找到会去`src`和`../headers`目录去寻找
当然还有另一个小写的`vpath`这个和大写的指令功能类似，但是更加的灵活，`vpath`一共有三种形式的
```make
#vpath pattern directories
vpath %.h ../headers
# 1.对一定格式类型的问价指定一个搜索路径，搜索路径由一列要搜寻的目标构成，他们用冒号分隔,而pattern
#是一个包含一个'$'的字符串。上面表示在../headers目录中寻找所有的.h文件
vpath pattern
# 2.清除和一定类型格式相关联的搜索路径
vpath
# 3.清除所有前面由vpath指定的搜索路径
# example:
vpath %.c foo/
vpath % blish
vpath %.c bar
#上面表示先搜索.c文件在目录foo;然后在目录blish;最后在bar
```

三个神奇的自动变量:

```make
foo:a b c
	$@ $^ $<
a:
	@echo  a
b:
	@echo b
	-include *.ss
#上面的$@表示make指令时后面跟的目标，
#$^表示依赖列表就是a b c，
#$<表示依赖列表的第一个依赖就是a
#上面的echo命令前面使用@符号表示echo b这条命令不回显,当然如果你使用了-s选项即：`make -s`那么所有的都
#不回显
#在命令前加一个短杠如 -include 表示有关include指令的错误信息都不表示
```

内建的特殊变量名
```make
.PHONY: xxx
#phony的依赖是假想目标，make将会无条件的执行它的命令；跟他的依赖是否更新么有关系
.SUFFIXES: xxx
#特殊目標.SUFFIXES 的依賴是一列用於尾碼規則檢查的尾碼。
.DEFAULT: xxx
#指定一些命令,這些命令用於那些沒有找到規則(具體規則或隱含規則)更新的目標
.

```

### 3.指令

make中有不少自带的指令，下面将会对一些常用的指令进行说明
##### 3.1指令include
`include` 指令告诉make暂停当前的makefile文档，先去读取`include`指令指定的makefile文档。该指令单独占
一行，其格式如下：
```make
include filename1 filename2 *.mk
```
上面表示需要包含`filename1`、`filename2`和所有以`.mk`结尾的文件

### 4.通用的匹配符

一个小例子
```make
object = *.o

foo:$(object)
	rm -f $(object)
%:
	touch $@
```
通配符`%`，它可以和任何目标匹配，也就是说如果你执行了`make bar'`而这个`bar`目标并没有被定
义这时将会被`%`给匹配，所以将会执行下面的指令`touch $@`而这个`$@`就是输入中你的target,这里是`bar`

通配符`*`，这里表示所有的`.o`文件在make里使用`$()`来获取变量里的内容

### 5.函数

### 6.小知识点
#### 6.1连接库的搜索目录
当一个依赖的名字是`-lname`的形式时，make特别的在：
* 当前目录下
* vpath目录下
* VPATH目录下
* 以及`/lib`、`/usr/lib`、`prefix/lib`一般prefix为`/usr/local/lib`
中依次去寻找名字为`libname.so`的文件，如果没有找到会寻找`libname.a`文件。它其实使用了一个
`.LIBPATTERNS`的变量，这个变量的默认值："lib%.so lib%.a",该值对前面描述的缺省行为提供支持。

#### 6.2假想目标
假想目标并不是一个正真的文件名，它仅仅是制定一个具体规则所执行的一些命令的名称，使用假想目标有两个原
因：避免和具有相同名称的文件冲突和改善性能。假想目标声明为`.PHONY: clean`一旦你这样声明，`make clean`
命令无论目录下是否存在名為clean的文件,該目標的命令都會執行。

#### 6.3命令的执行
make给每条shell命令一个独立的环境，这就意味着命令之间相互不影响；如果你的命令之间需要用相同的环境
那么请将两个命令放在同一行并用分号进行分割就好
```make
foo:
	cd xxx/xxx; touch xxx

bar:
	cd xxx/xxx
	touch xxx
```

上面的两个例子是不同的foo将会在`xxx/xxx`建立`xxx`文件；而bar会在当前目录建立xxx文件
#### 6.4忽略命令错误
当make中的shell指令执行出错，那么会将整个make给中断，如果这个并不是一个重要的命令，那么这次中断将不是
我们所希望的这时可以用`-`字符加载shell命令前以忽略错误
```make
foo: aa
	echo aa
aa:
	#rm xx
	-rm xx
```

上面的例子中如果aa的指令rm没有发现xx那么将会中断也就是看不到aa了，但是如果使用`-`字符，将会忽略命令的
错误继续执行`echo aa`
