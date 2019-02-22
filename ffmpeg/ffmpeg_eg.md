## ffmpeg使用示例

### 将MP4转化为gif

```
ffmpeg -i small.mp4 small.gif
```
### 转化视频中的一部分为GIF, 从视频中第二秒开始，截取时长为3秒的片段转化为 gif

```
ffmpeg -t 3 -ss 00:00:02 -i small.webm small-clip.gif
```

### 转化高质量GIF, 默认转化是中等质量模式，若要转化出高质量的 gif，可以修改比特率

```
ffmpeg -i small.mp4 -b 2048k small.gif
```

### 视频属性调整, 缩放视频尺寸

```
ffmpeg -i big.mov -vf scale=360:-1  small.mov
```

注意 sacle 值必须是偶数，这里的 -1 表示保持长宽比，根据宽度值自适应高度。如果要求压缩出来的视频尺寸长宽都保持为偶数，可以使用 -2

### 加倍速播放视频

```
ffmpeg -i input.mov -filter:v "setpts=0.5*PTS" output.mov
```

### 定义帧率 16fps:

```
ffmpeg -i input.mov -r 16 -filter:v "setpts=0.125*PTS" -an output.mov
```

### 慢倍速播放视频

```
ffmpeg -i input.mov -filter:v "setpts=2.0*PTS" output.mov
```

### 静音视频（移除视频中的音频）

```
ffmpeg -i input.mov -an mute-output.mov
```

`-an` 就是禁止音频输出

### 将 GIF 转化为 MP4

```
ffmpeg -f gif -i animation.gif animation.mp4
```

### 也可以将 gif 转为其他视频格式

```
ffmpeg -f gif -i animation.gif animation.mpeg
ffmpeg -f gif -i animation.gif animation.webm
``` 

### GIF 转出来的 MP4 播放不了？ 

有些 GIF 转化出来的 MP4 不能被 Mac QuickTime Player.app 播放，需要添加 pixel formal 参数

```
ffmpeg -i input.gif -vf scale=420:-2,format=yuv420p out.mp4
```

使用 yunv420p 需要保证长宽为偶数，这里同时使用了 scale=420:-2 。

**解释： QuickTime Player 对 H.264 视频只支持 YUV 色域 4:2:0 方式的二次插值算法.**


### 视频比例转化

如果不给color的话。默认将会是黑色的背景,将画面从4：3 切换成16：9

```
# 4:3 转换成 16：9
ffmpeg -i input -vf pad=ih*16/9:ih:(ow-iw)/2:0:color output
# 16:9 转换成 4：3
ffmpeg -i input -vf pad=iw:iw*3/4:0:(oh-ih)/2:color output
```

### 视频的画面大小剪切

将输入的视频的帧，以左上角为坐标原点，剪切成x,y偏移大小,语法：`crop=ow:oh:x:y`

参数解释

```
x,y表示偏移量
ow,oh表示输出的宽和高
iw,ih表示输入的宽和高
a:表示比例、和iw/ih一样
```

示例

```
#高不变，只要左边1/3的视频
ffmpeg -i input -vf crop=iw/3:ih:0:0 output
# 高不变，只要中间1/3的视频，（主要是后面偏移了1/3，所以到中间了）
ffmpeg -i input -vf crop=iw/3:ih:iw/3:0 output
# 高不变，只要右边1/3的视频，（偏移了2/3）
ffmpeg -i input -vf crop=iw/3:ih:iw/3*2:0 output
# 另一种方法，截取视频前3秒
ffmpeg -ss 00:00:00 -t 00:00:03 -i input -vcode copy -acode copy output
* -ss 指定从什么时间开始
* -t 指定需要截取多长时间
```

### 视频的合成

现有文件`list.txt`里面的内容如下

```
file ./video1.mp4
file ./video2.mp4
```

使用`concat`指令进行合并

```
ffmpeg -f concat -i list.txt -c copy concat.mp4
# 如果上面指令出现了’unsafe file name‘错误，我们可以加-safe 0参数，如下：
ffmpeg -f concat -safe 0 -i list.txt -c copy concat.mp4
```

### 给视频或图片加内边距

```
# 下面尺寸是440*256， 内边距是30, 后面跟的事颜色，默认是黑色
ffmpeg -i 01.mp4 -vf pad=440:256:30:30:pink 010.mp4
```

### 翻转和旋转视频(flip filter)

```
#水平翻转(Horizontal flip)
-vf hfilp
#竖直翻转(Vertical flip)
-vf vfilp
# 旋转 transpose参数
#0 - 逆时针旋转+竖直翻转
#1- 顺时针旋转 90
#2- 逆时针旋转 90
#3- 顺时针旋转90 + 竖直的翻转

将视频顺时针旋转90°
ffmpeg -i input -vf transpose=1 output 
```

### [模糊、锐化](./ffmpeg_blur.md)