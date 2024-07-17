# m3boot for e8372h-153 (hisilicon balong v7r11)

for build you should install cross-compiler with support Cortex-M3

## example
type this to build
```bash
CROSS_COMPILE=armv7a-unknown-linux-gnueabihf- make
```
result binary is output/lib/m3boot.bin

now you can flash this binary to m3boot partiton in your modem
for flashing you may use [forth32's tool](https://github.com/forth32/balong-usbdload)
