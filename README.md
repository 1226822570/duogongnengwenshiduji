# 基于涂鸦智能的智能温湿度计

## 项目介绍：
> This project is developed using Tuya SDK, which enables you to quickly develop branded apps connecting and controlling smart scenarios of many devices. For more information, please check Tuya Developer Website.

这是一个使用涂鸦智能模组开发的一个多功能温湿度计，可以使用手机APP实时获取温湿度计的数据，并且提供红外接收和红外发射功能，用于控制其他非联网电器。


> 由于在硬件设计时，没有加入外置flash，导致无法掉电储存红外信号，所以对于要发射的红外信号的设置，必须在编程时完成，即通过就收功能获取后，将红外信号编写进发射程序中来实现更改红外信号的功能。

## 实现的功能
本项目有以下功能
1. 获取温度信息并传输至APP
2. 获取湿度信息并传输至APP
3. 获取遥控器的红外信号
4. 模拟发送红外信号控制电器
5. 使用锂电池供电，板载充电功能

## 使用的硬件相关信息
1. GD32E230K8T6
2. 锂电池充电芯片TP4057ST26P 
3. 线性稳压器XC6210B332MR
4. 温湿度传感器SHT30-DIS
5. 红外发射管E6C0805IRAC1UDA940nm
6. 38KHZ遥控接收头IRM-H638T/TR2(DX) 
7. 0.96寸OLED

## 实物展示
