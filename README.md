# stm32-l2hal - STM32 MCU level 2 HAL

Open-source (GPLv3+) extension (second level HAL, L2HAL) over STM's HAL for STM32 MCUs.

STM's HAL is designed to provide abstractions over operations like sending data over I2C bus or changing GPIOs states.

My own HAL is designed to provide second level of abstraction like "turn on pixel on display, connected over I2C" or "get incremental encoder turn angle". Actually it's just a set of drivers for various hardware.

Note, that you need my https://github.com/WhiteFossa/stm32-fmgl/ library in your project too, because display drivers included in L2HAL depends on it.

## Features
- Well-written code (I hope). I've tried to implement everything in understandable, enterprise-style, sacrifice performance for sake of portability and clarity.
- Each function is documented.
- GPLv3 license.
