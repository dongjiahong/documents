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
== 解释： QuickTime Player 对 H.264 视频只支持 YUV 色域 4:2:0 方式的二次插值算法。==
