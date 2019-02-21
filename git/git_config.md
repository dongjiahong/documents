## git简介

>>> Git是一款免费、开源的分布式版本控制系统，用于敏捷高效地处理任何或小或大的项目.

## 安装

```sh
# debian || ubuntu
sudo aptitude install git
# red hat || centos
sudo yum install git
```

### git的公钥

```sh
ssh-keygen -t rsa -C "dongjiahong@hotmail.com"
#接着三个回车
cat ~/.ssh/id_rsa.pub
```

### 日常git的常用配置

```sh
git config --global user.name "董家宏"
git config --global user.email "dongjiahong@hotmail.com"
git config --global color.diff auto # git diff 要顯示顏色
git config --global color.status auto # git status 要顯示顏色
git config --global color.branch auto
```

### git的常用指令
```sh
# 将误加入版本库的文件给删除，但是在本地还是保留 这里要加--cache
git rm --cache <file>
# 将错误的本地commit取消,但是修改的文件还在
git reset commit_id
# 将错误的本地commit取消，代码回到reset的版本状态
git reset --hard commit_id
# 将工作区文件保存在git的内部栈中
git stash
# 列出git内部栈中保存的工作区文件列表
git stash list
# 恢复工作区到指定的内部栈状态
git stash apply stash_id
# 恢复工作区到上一个内部栈状态
git stash pop
# 清空git内部栈
git stash clear
# push推送指令 
git push <远程仓库> <本地分支>:<远程分支>
# pull拉取指令
git pull <远程仓库> <远程分支>:<本地分支>
# merge,将分支dev合并到分支master， 先checkout master
git merge dev
# 删除本地分支
git branch -d develop
# git diff [<options>] [<commit> [<commit>]] [--] [<path>...]
git diff commit1 commit2
# 显示出所有有差异的文件的详细差异
git diff branch1 branch2
# 显示出所有有差异的文件列表
git diff branch1 branch2 --stat
# 显示指定文件的详细差异
git diff branch1 branch2 filename
# 合并其他分支的文件git checkout -p, --patch  select hunks interactively
git checkout -p example src/a.h  # 不切换分支，将example分支下，src/a.h文件合并到本分支
```

### git的pull冲突
在使用`git pull`代码时，经常会碰到有冲突的情况，如下提示:

```sh
error: Your local changes to 'c/environ.c' would be overwritten by merge.  Aborting.
Please, commit your changes or stash them before you can merge.
```
上面说的是本地和远程仓库有冲突，一般解决这样的冲突我们可以按照下面几步:
#### 1.保存修改

```sh
git stash 
```

使用`stash`指令将所有修改都暂时的保存起来，可以使用`git stash list`来查看保存的信息：

```sh
stash@{0}: WIP on master: a80c24d
```

上面的`stash@{0}`就是刚才保存的标记

#### 2.pull内容
暂存了本地修改后，就可以pull了。

```sh
git pull
```

#### 3.还原暂存内容

```sh
git stash pop stash@{0}
```
执行上面的内容你可以得到如下类似的信息:

```
Auto-merging src/sender.lua
CONFLICT (content): Merge conflict in src/sender.lua
Auto-merging README.md
```
意思就是系统自动合并修改内容，但是其中有冲突，需要解决其中的冲突

#### 4.解决文件中的冲突部分
打开冲突的文件，会看到类似如下的内容：

```sh
<<<<<<< Update upstream
	int i, j;
======= 
	int i, z;
>>>>>>> Stashed changes
```

其中`Update upstream`和`=======`之间的内容是`pull`下来的内容，`=======`和`Stashed
changes`之间的内容就是本地修改的内容，碰到这样的情况，git也不知道如何解决，需要你
自己解决后就可以正常提交了。

### git仓库迁移
如果你有项目本来在gitos上，但是现在想github上可以使用如下流程

1.查看现有git情况
```
# git remote -v
origin	git@git.oschina.net:CloudTech/render_king.git (fetch)
origin	git@git.oschina.net:CloudTech/render_king.git (push)
```

2.添加github的仓库链接
```
# git remote add github git@github.com:xxxxx/xxxxx.git
# git remote -v 
github	git@github.com:cloudadrd/render_king.git (fetch)
github	git@github.com:cloudadrd/render_king.git (push)
origin	git@git.oschina.net:CloudTech/render_king.git (fetch)
origin	git@git.oschina.net:CloudTech/render_king.git (push)
```

3.将代码上传到github仓库，注意所对应的分支
```
git push -u github master:master
git push -u github develop:develop
```
