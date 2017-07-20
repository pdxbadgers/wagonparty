To reprogram the badge:

1. Connect a 3.3v (NOT 5V) usb-serial cable to the badge

2. Walk through the sparkfun hookup guide to get things working normally: https://learn.sparkfun.com/tutorials/nrf52832-breakout-board-hookup-guide starting from "Adding Arduino Compatibility".

3. Change the i2c pin settings in  ~/.arduino15/packages/SparkFun/hardware/nRF5/0.2.3/variants/SparkFun_nRF52832_Breakout/variant.h near line 100:
//#define PIN_WIRE_SDA         (20u)
#define PIN_WIRE_SDA         (24)
//#define PIN_WIRE_SCL         (21u)
#define PIN_WIRE_SCL         (25u)

4. Install the Adafruit_SSD1306 Adafruit_GFX libraries.

5. Press and hold in the center of the left wagon wheel while powering down and powering on the badge to get it into programming mode.

6. Hit the upload button on the arduino SDK.
