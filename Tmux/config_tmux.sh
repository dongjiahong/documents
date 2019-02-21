#!/bin/bash

cmd="/usr/bin/tmux" # tmux path
session=RenRen   # session name

echo jiahong@@.1 | kinit jiahong.dong

  $cmd new -d -n Home -s $session
#创建第一个窗口并连接到bo.wang33@10.4.27.15
  $cmd neww -n AdCode 'ssh bo.wang33@10.4.27.15'
  $cmd neww -n AdControl 'ssh xce@10.4.35.48'
  $cmd neww -n AdTest 'ssh xce@10.4.29.175'
  $cmd neww -n dsp_strategy 'ssh dsp_strategy@10.4.24.80' 
  $cmd neww -n 数据库 'ssh root@10.4.32.189'
  $cmd neww -n 查log 'ssh -l jiahong.dong proxy.opi.com' 
# $cmd neww -n  -t $session "irssi"
#  $cmd neww -n cmus -t $session "cmus"
#  $cmd neww -n zsh -t $session "zsh"
#  $cmd splitw -h -p 50 -t $session "zsh"
  $cmd selectw -t $session:1

$cmd attach -t $session


exit 0



