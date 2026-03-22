# aide 设备树引脚分配

## GPIO
| 功能 | GPIO | 备注 |
|------|------|------|
| LED_STATUS | GPIO0_A4 | 状态灯 |
| LED_POWER | GPIO0_A5 | 电源灯 |
| BTN_RESET | GPIO0_A2 | 复位按键 |
| BTN_WAKE | GPIO0_A3 | 唤醒按键 |

## UART
| 接口 | 设备 | 波特率 |
|------|------|--------|
| UART2 | 调试串口 | 115200 |

## I2C
| 总线 | 设备 | 地址 |
|------|------|------|
| I2C1 | 光 sensor | 0x39 |
| I2C1 | 加速度计 | 0x68 |
| I2C1 | 音频Codec | 0x10 |

## SPI
| 总线 | 设备 | 备注 |
|------|------|------|
| SPI0 | 显示屏 | ST7789 |

## 摄像头
- CSI2: OV5640

## WiFi/BT
- RTL8189FS (WiFi)
- RTL8723DS (蓝牙)
