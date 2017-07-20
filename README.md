To reprogram the badge:

1. Connect a 3.3v (NOT 5V) usb-serial cable to the badge

2. Clone this repo into the ~/Arduino/ directory, and open it.

3. Follow the [SparkFun nrf52832 breakout board hookup](https://learn.sparkfun.com/tutorials/nrf52832-breakout-board-hookup-guide#adding-arduino-compatibility) instructions, specifically "Adding Arduino Compatibility".

4. Install the following libraries:
  - Adafruit_SSD1306
  - Adafruit_GFX
  - BLEPeripheral

5. Change the i2c pin settings in  ~/.arduino15/packages/SparkFun/hardware/nRF5/0.2.3/variants/SparkFun_nRF52832_Breakout/variant.h near line 100:
```c
//#define PIN_WIRE_SDA         (20u)
#define PIN_WIRE_SDA         (24)
//#define PIN_WIRE_SCL         (21u)
#define PIN_WIRE_SCL         (25u)
```

6. Change the SSD1306 screen settings in ~/Arduino/libraries/Adafruit_SSD1306/Adafruit_SSD1306.h near line 73:
```c
#define SSD1306_128_64
//   #define SSD1306_128_32
//   #define SSD1306_96_16
```
7. Make nrfutil (~/.arduino15/packages/SparkFun/tools/nrfutil/0.5.2-SFE/dist/nrfutil) executable

8. Press and hold in the center of the left wagon wheel while powering down and powering on the badge to get it into programming mode.  You can release the button once the device is powered.

9. Hit the upload button on the arduino SDK.
