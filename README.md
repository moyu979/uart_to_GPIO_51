# uart_to_GPIO_51

注意！这个项目还没经过测试，谨慎使用！！！

将uart数据通过51转化成GPIO

## 简介：

这是一个通过51单片机做中继，将uart方向传来的控制命令转化为低速GPIO动作的C语言工具。

使用uart接口作为命令接收端口，使用P1和P2两个GPIO组作为GPIO端口，P0需要上拉电阻，太麻烦，因此空置。

## 协议定义：

### 时序：

宿主机发送控制命令，包含 $1+n$ 个字节，其中，第一个字节为命令语句，第二个字节为数据。

### 协议

第一字节被分成高

|代号|功能|第一字节(7-4)位|第一字节第3位|第一字节(2-0)|第2字节|
|----|----|----|----|----|----|
|0|反转某个GPIO|0x0|{P1:0,p2:1}|引脚编号|0|
|1|查看某个GPIO引脚的值|0x1|{P1:0,p2:1}|引脚编号|0|
|2|查看某组GPIO的值|0x2|{P1:0,p2:1}|0|0|
|3|反转某组GPIO|0x3|{P1:0,p2:1}|0|0|
|4|写入某个GPIO|0x4|{P1:0,p2:1}|引脚编号|0或1|
|5|将某个GPIO与数据进行与操作|0x5|{P1:0,p2:1}|引脚编号|0或1|
|6|将某个GPIO与数据进行或操作|0x6|{P1:0,p2:1}|引脚编号|0或1|
|7|将某个GPIO与数据进行异或操作|0x7|{P1:0,p2:1}|引脚编号|0或1|
|8|写入某组GPIO|0x8|{P1:0,p2:1}|0|8位数据|
|9|将某组GPIO与数据进行与操作|0x9|{P1:0,p2:1}|0|8位数据|
|10|将某组GPIO与数据进行或操作|0xa|{P1:0,p2:1}|0|8位数据|
|11|将某组GPIO与数据进行异或操作|0xb|{P1:0,p2:1}|0|8位数据|

### 一些解释

需要使用非命令，可以使用异或1替代


# 感谢

https://blog.51cto.com/990487026/1699963

https://ask.csdn.net/questions/7757719
