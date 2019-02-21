#!/bin/bash

#获取当前路径
CUR_PATH=`pwd`
echo $CUR_PATH

echo "该程序用来配置vim的，准备工作如下："
echo -e "\033[31m 1、下载并安装vundle插件管理器 \033[0m"
echo -e "\033[31m 2、安装必要的软件，cmake、gcc、ctags、git、vim-nox、python-dev \033[0m"
echo -e "\033[31m 3、将bundle.bz2.tar文件拷贝到当前目录中 \033[0m"
echo -e "\033[35m 4、准备好了吗？Y/N \033[0m"
read x
if [ $x != 'Y' -a $x != 'y' ];then
    echo -e "\033[33m Sorry, Just do it with the tip! \033[0m"
    exit -1
fi
echo -e "\033[32m OK! Good Job! \033[0m"
#判断当前目录下是否有bundle.bz2.tar文件
if [ ! -f ${CUR_PATH}/bundle.bz2.tar ];then
    echo -e "\033[31m No, cant't find the file bundle.bz2.tar \033[0m"
    exit -1
fi
#解压文件并拷贝到~/.vim文件夹下
if [ ! -d ~/.vim ];then
    mkdir ~/.vim
fi
set -x
cp ~/.vimrc ~/.vimrc.bak
cp ${CUR_PATH}/vim_make.vim ~/.vimrc
(cd ${CUR_PATH}| tar jxvkf bundle.bz2.tar)
cp -r ${CUR_PATH}/bundle/ ~/.vim
#修改配置文件
cp ~/.vim/bundle/YouCompleteMe/third_party/ycmd/cpp/ycm/.ycm_extra_conf.py ~/.ycm_extra_conf.py
set +x

echo -e "\033[35m Good! Join it! \033[0m"
