# set_serial_buffer
这个程序示例尝试获取串口的当前输出缓冲区大小，然后尝试设置新的缓冲区大小，并再次读取缓冲区大小以确认更改。对于输入缓冲区大小，通常由驱动程序内部管理，无法通过类似方法直接修改.

在Linux中，串口数据的缓冲区大小通常与驱动程序和硬件相关，直接通过`ioctl`设置缓冲区大小可能不会生效。

- 并不是所有的串口驱动都支持修改缓冲区大小。某些硬件的缓冲区大小是固定的，无法通过软件更改。
- `TIOCGSERIAL` 和 `TIOCSSERIAL` 是特定于Linux的`ioctl`命令，其他操作系统可能不支持这些命令。

## Dependence

## Test

- **compile**

```shell
gcc -o set_serial_buffer_size set_serial_buffer_size.c
```

- **run**

```shell
./set_serial_buffer_size /dev/ttyS0
```

