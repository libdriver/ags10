### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(ags10 REQUIRED)
```

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
./ags10 -i

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
./ags10 -p

ags10: SCL connected to GPIO3(BCM).
ags10: SDA connected to GPIO2(BCM).
```

```shell
./ags10 -t read --times=3

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
./ags10 -e read --times=3

ags10: 1/3.
ags10: tvoc is 85ppb.
ags10: 2/3.
ags10: tvoc is 85ppb.
ags10: 3/3.
ags10: tvoc is 83ppb.
```

```shell
./ags10 -h

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

#### 3.3 Command Problem

1. There is some unknown problem in the iic interface of ags10 on the raspberry board, one command may try many times to run successfully or run failed.
