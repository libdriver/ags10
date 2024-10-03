### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. AGS10

#### 3.1 Command Instruction

1. Show ags10 chip and driver information.

   ```shell
   ags10 (-i | --information)
   ```

2. Show ags10 help.

   ```shell
   ags10 (-h | --help)
   ```

3. Show ags10 pin connections of the current board.

   ```shell
   ags10 (-p | --port)
   ```

4. Run ags10 read test, num means test times. 

   ```shell
   ags10 (-t read | --test=read) [--times=<num>]
   ```

5. Run ags10 read function, num means test times.

   ```shell
   ags10 (-e read | --example=read) [--times=<num>]
   ```

#### 3.2 Command Example

```shell
ags10 -i

ags10: chip is ASAIR AGS10.
ags10: manufacturer is ASAIR.
ags10: interface is IIC.
ags10: driver version is 1.0.
ags10: min supply voltage is 2.9V.
ags10: max supply voltage is 3.1V.
ags10: max current is 25.00mA.
ags10: max temperature is 85.0C.
ags10: min temperature is -40.0C.
```

```shell
ags10 -p

ags10: SCL connected to GPIOB PIN8.
ags10: SDA connected to GPIOB PIN9.
```

```shell
ags10 -t read --times=3

ags10: chip is ASAIR AGS10.
ags10: manufacturer is ASAIR.
ags10: interface is IIC.
ags10: driver version is 1.0.
ags10: min supply voltage is 2.9V.
ags10: max supply voltage is 3.1V.
ags10: max current is 25.00mA.
ags10: max temperature is 85.0C.
ags10: min temperature is -40.0C.
ags10: start read test.
ags10: version is 0x0C.
ags10: tvoc is 83ppb.
ags10: tvoc is 83ppb.
ags10: tvoc is 83ppb.
ags10: resistance is 9313700.00ohm.
ags10: zero point calibration 0xF6F7.
ags10: current resistance zero point calibration.
ags10: reset zero point calibration.
ags10: modify slave address 0x1A.
ags10: finish read test.
```

```shell
ags10 -e read --times=3

ags10: 1/3.
ags10: tvoc is 85ppb.
ags10: 2/3.
ags10: tvoc is 85ppb.
ags10: 3/3.
ags10: tvoc is 83ppb.
```

```shell
ags10 -h

Usage:
  ags10 (-i | --information)
  ags10 (-h | --help)
  ags10 (-p | --port)
  ags10 (-t read | --test=read) [--times=<num>]
  ags10 (-e read | --example=read) [--times=<num>]

Options:
  -e <read>, --example=<read>    Run the driver example.
  -h, --help                     Show the help.
  -i, --information              Show the chip information.
  -p, --port                     Display the pin connections of the current board.
  -t <read>, --test=<read>       Run the driver test.
      --times=<num>              Set the running times.([default: 3])
```

