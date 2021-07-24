# pico-ir-keyboard
## Add IR remote as input to any PC
- Decoding [NEC protocol IR pulses](https://www.renesas.com/us/en/document/apn/using-infrared-remote-controller-transmission-and-reception?language=en) from remote control with a [Pico](https://www.raspberrypi.org/products/raspberry-pi-pico/) and perform keypress as a USB keyboard (HID).
## Back story
- It all started with adding IR remote support for [Raspberry Pi 3 Model B+](https://www.raspberrypi.org/products/raspberry-pi-3-model-b-plus/) with [custom embedded Linux](https://buildroot.org/) for Web Kiosk ( I know [Raspberry Pi GPIO](https://www.raspberrypi.org/documentation/usage/gpio/) can decode IR. I have also decoded [NEC protocol](https://www.renesas.com/us/en/document/apn/using-infrared-remote-controller-transmission-and-reception?language=en) with [Python](https://www.python.org/) in [Raspberry Pi OS](https://www.raspberrypi.org/software/operating-systems/#raspberry-pi-os-32-bit) ).
- I have no patience in [recompiling the OS](https://buildroot.org/downloads/manual/manual.html#_cross_compilation_toolchain) with [GPIO](https://www.raspberrypi.org/documentation/usage/gpio/) and [Python](https://www.python.org/).
- I thought it would be easy to add [Raspberry Pi Pico](https://www.raspberrypi.org/products/raspberry-pi-pico/) to emulate the keyboard (USB HID). As the [website](http://visionchart.github.io/) already has keyboard support.
- I also found a product by [Adafruit](https://www.adafruit.com) [pIRkey](https://www.adafruit.com/product/3364) which does the same, but they discontinued it.
## Adding HID
 &numsp;✔️ It's a relatively simple and easy process available with [TinyUSB](https://github.com/hathach/tinyusb), via [CircuitPython](https://circuitpython.org/),&nbsp;[Arduino IDE](https://www.arduino.cc/en/software) (or) [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk).
 
 &numsp;❌ but not [MicroPython](https://micropython.org/).
## Decoding IR with pico
1. Try old python code.
    - Moving on, I realised that using [Raspberry Pi Pico](https://www.raspberrypi.org/products/raspberry-pi-pico/) to decode [IR NEC protocol](https://www.renesas.com/us/en/document/apn/using-infrared-remote-controller-transmission-and-reception?language=en) and emulate a keyboard is not that easy.
    - The previous program I used to decode [IR NEC protocol](https://www.renesas.com/us/en/document/apn/using-infrared-remote-controller-transmission-and-reception?language=en) in [Raspberry Pi 3 Model B+](https://www.raspberrypi.org/products/raspberry-pi-3-model-b-plus/) [Python](https://www.python.org/) did not work in either [MicroPython](https://micropython.org/) or [CircuitPython](https://circuitpython.org/).
    - In both time differences between two pulses returned zero.
2. Search for Pico specific code.
    - I found [micropython_ir](https://github.com/peterhinch/micropython_ir) by [peterhinch](https://github.com/peterhinch) in [MicroPython](https://micropython.org/) it :tada: works great in decoding [IR NEC protocol](https://www.renesas.com/us/en/document/apn/using-infrared-remote-controller-transmission-and-reception?language=en).
    - It uses `IRQ`, so no chance of running it in [CircuitPython](https://circuitpython.org/).
    - By default, [MicroPython](https://micropython.org/) doesn't support HID for [Raspberry Pi Pico](https://www.raspberrypi.org/products/raspberry-pi-pico/).
    - I tried including HID in the [MicroPython source](https://github.com/micropython/micropython) and [compile](https://github.com/micropython/micropython/tree/master/ports/rp2) it but had no luck; I should try that in the future.
3. Changing the old code to C.
    - As USB HID support is available in [Arduino IDE](https://www.arduino.cc/en/software), I convert that old [Python](https://www.python.org/) code to C.
    - It didn't work either.
4. Trying with PIO.
    - So, I decided to convert that [Python](https://www.python.org/) code into [PIO assembly language](https://www.raspberrypi.org/blog/what-is-pio/) to include it in [CircuitPython](https://circuitpython.org/).
    - After some searching, I found the same in a pending [pull request](https://github.com/raspberrypi/pico-examples/pull/129) by [mjcross](https://github.com/mjcross) with [PIO](https://www.raspberrypi.org/blog/what-is-pio/) in [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk) Great!
    - Then decided to go with [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk).
## Merging two
- Merging is simple with the [device examples provided in TinyUSB](https://github.com/hathach/tinyusb/tree/master/examples/device) and from the [pending GitHub pull request](https://github.com/raspberrypi/pico-examples/pull/129).
