>这是一个之前做过的小课设，主要是利用LD3320语音模块进行模拟智能家居，通过不同命令的特征提取，实现不同指令的控制。项目已经开源整理至github。

@[toc]
# 1.Background
- 随着人工智能市场规模持续增长，智能语音将居于重要地位。
- 智能语音设备可以实现自主学习，融入家庭，扮演陪伴者角色，并且极大提高人们的生活效率，还使得难以自理的群体，让他们的生活更方便。

# 2.Hardware
## 2.1 LD3320语音识别模块
>- LD3320 芯片是一款“语音识别”专用芯片。该芯片集成了语音识别处理器 和一些外部电路，包括 AD、DA 转换器、麦克风接口、声音输出接口等。本芯片 不需要外接任何的辅助芯片如 Flash、RAM 等，直接集成在现有的产品中即可以 实现语音识别/声控/人机对话功能。并且，识别的关键词语列表是可以任意动态编辑的。

>- 一体化语音识别模块是基于STC11 单片机和LD3320 语音芯片组合而成的一款语音识别模块，此模块具备一个 5V TTL 串口和 16 个 IO 口引出，可与外部单片机进行通信交互信息。



## 2.2 STM32
>主驱一体板是基于 STM32F103C8T6 单片机进行硬件电路设计，主要包括 STM32 最小系统电路、OLED 显示电路，驱动电路，串行口接口电路，电源电路等。

STM32主驱一体板：[https://github.com/Hyf338/Remote-Sensing/tree/master/hardware/STM32_Controller](https://github.com/Hyf338/Remote-Sensing/tree/master/hardware/STM32_Controller)

<table>
		<td ><center><img src="https://img-blog.csdnimg.cn/20200612214418154.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mjg4MTQxOQ==,size_16,color_FFFFFF,t_70,size_16,color_FFFFFF,t_70"  >图1 原理图</center></td>
         <td ><center><img src="https://img-blog.csdnimg.cn/2020061221470184.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mjg4MTQxOQ==,size_10,color_FFFFFF,t_70"  >图2 PCB3D模型</center></td>
</table>


## 2.3连接示意图
>- 一体化语音识别模块是基于STC11 单片机和LD3320 语音芯片组合而成的一款语音识别模块，此模块具备一个 5V TTL 串口和 16 个 IO 口引出，可与外部单片机进行通信交互信息。

![连接示意图](https://img-blog.csdnimg.cn/20200612222246160.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mjg4MTQxOQ==,size_16,color_FFFFFF,t_70)

# 3.Software

选用 LD3320 语音识别芯片采样识别到的业务存储在 LD3320 寄存器中，并连接 STC11 单片机，应用串口发送到 STM32F103C8T6 的单片机进行处理，需完成系统界面设计，识别并处理语音模块发送的开机、关机、一级界面与二级界面的切换、LED 灯的点亮、电机的转动与停止、调速等指令。


## 3.1系统整体流程图
![系统整体流程图](https://img-blog.csdnimg.cn/20200616231244575.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mjg4MTQxOQ==,size_16,color_FFFFFF,t_70)
## 3.2 LD3320语音模块程序流程图
![LD3320语音模块程序流程图](https://img-blog.csdnimg.cn/2020061623101864.png)
