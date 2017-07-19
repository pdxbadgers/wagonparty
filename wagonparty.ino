/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <BLEPeripheral.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "sprites.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// bluetooth
BLEPeripheral blePeriph;
BLEService bleServ("0503");
BLECharacteristic bannerText("0503", BLERead | BLEWrite,20);

int wagonscore=0;
int gamemode=0;
int lastflip=0;
String banner="503.PARTY!";

// hunter variables
int hunterx=30;
int huntery=30;
int hunterDirection=0;

int benderx=5;
int bendery=5;
int benderscore=0;

// party mode variables
int lastParty=0;

void setup()   {     

  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();

  // Clear the buffer.
  display.clearDisplay();

  pinMode(3, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);

  pinMode(8, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);

  setupBLE();
}

void setupBLE()
{
  // Advertise name and service:
  blePeriph.setDeviceName("503WAGON");
  blePeriph.setLocalName("503WAGON");
  blePeriph.setAdvertisedServiceUuid(bleServ.uuid());

  // Add service
  blePeriph.addAttribute(bleServ);

  // Add characteristic
  blePeriph.addAttribute(bannerText);

  // Now that device6, service, characteristic are set up,
  // initialize BLE:
  blePeriph.begin();

  // Set led characteristic to default value:

  bannerText.setValue("503.PARTY!");  
}

void loop()
{
  // check for mode change
  bool e=false;
  if (digitalRead(6) == LOW)e=true;
  if(e && (millis()-lastflip>1000))
  {
    lastParty=0; // reset party mode counter
    display.stopscroll(); // stop the party
    
    gamemode=(gamemode+1)%3; // switch game mode
    lastflip=millis();
  }

  // check for dysentery
  if(banner=="DYSENTERY")
  {
    display.stopscroll(); // stop the party
    display.fillRect(20,19,87,22,BLACK);
    display.drawRect(21,20,85,20,WHITE);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(25,22);
    display.print("You have died");
    display.setCursor(26,30);
    display.print("of dysentery.");
    display.display();
    delay(10*60*1000); // sleep for 10 minutes  
    int wagonscore=0;
    int benderscore=0;
  }
              
  if(banner=="WannaCry")
  {
    display.stopscroll(); // stop the party
    display.fillRect(20,19,87,22,BLACK);
    display.drawRect(21,20,85,20,WHITE);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(25,22);
    display.print("You have died");
    display.setCursor(28,30);
    display.print("of WannaCry.");
    display.display();
    delay(4*24*60*60*1000); // sleep for 4 days
    int wagonscore=0;
    int benderscore=0;
  }

  radioloop();
  if(gamemode==0)wagonloop();
  if(gamemode==1)huntloop();
  if(gamemode==2)partyloop();
}

void radioloop()
{
  blePeriph.poll();

  if (bannerText.written())
  {
    char textValue[20];
    memset(textValue,0,20);
    strncpy(textValue,(char*)bannerText.value(),20);
    textValue[bannerText.valueLength()]=0;
    banner=String(textValue);
  }
}

void wagonloop() {

  wagonscore++;

  display.clearDisplay();

  if(wagonscore%2)display.drawBitmap(46,32,wagon1,88,30,1);
  else display.drawBitmap(46,34,wagon2,88,30,1);
  
  display.drawBitmap(wagonscore%272,0,mountains,272,30,1); // mind the gap
  display.drawBitmap(wagonscore%272-272,0,mountains,272,30,1);
  
  display.setTextSize(1);
  display.setTextColor(WHITE);

    display.setCursor(0,34);
//    display.setCursor(0,5);
//  display.setCursor(wagonscore%128,5);
    display.print(banner);
//  display.setCursor(wagonscore%128-128,5);
//  display.print(banner);

  // print the score on the bottom left
  display.setCursor(2,57);
  display.println(String(millis()/100000)+"mi");  
  display.display();
  delay(500);
}

 void huntloop() {
  
  bool a=false;
  bool b=false;
  bool c=false;
  bool d=false;
  bool e=false;
  
  bool f=false;
  bool g=false;
  bool h=false;
  bool i=false;
  bool j=false;

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (digitalRead(3) == LOW)a=true;
  if (digitalRead(5) == LOW)b=true;
  if (digitalRead(2) == LOW)c=true;
  if (digitalRead(4) == LOW)d=true;
  if (digitalRead(6) == LOW)e=true;
  
  if (digitalRead(8) == LOW)f=true;
  if (digitalRead(12) == LOW)g=true;
  if (digitalRead(7) == LOW)h=true;
  if (digitalRead(11) == LOW)i=true;
  if (digitalRead(13) == LOW)j=true;
  
  //testscrolltext(a+b+c+d+e+"\n"+f+g+h+i+j);

  // change which direction the hunter is facing
  if(a){if(huntery>0){huntery-=1;}hunterDirection=3;}
  if(b){if(huntery<60){huntery+=1;}hunterDirection=0;}
  if(c){if(hunterx>0){hunterx-=1;}hunterDirection=1;}
  if(d){if(hunterx<112){hunterx+=1;}hunterDirection=2;}

  // change which direction the hunter is facing due to laser
  if(f){hunterDirection=3;}
  else if(g){hunterDirection=0;}
  else if(h){hunterDirection=1;}
  else if(i){hunterDirection=2;}

  display.clearDisplay();
  if(hunterDirection==0)display.drawBitmap(hunterx,huntery,hunter_down,16,22,1); // mind the gap
  if(hunterDirection==1)display.drawBitmap(hunterx,huntery,hunter_left,16,22,1); // mind the gap
  if(hunterDirection==2)display.drawBitmap(hunterx,huntery,hunter_right,16,22,1); // mind the gap
  if(hunterDirection==3)display.drawBitmap(hunterx,huntery,hunter_up,16,22,1); // mind the gap

  // draw bender
  display.drawBitmap(benderx,bendery,bender,16,16,1);

  // draw laser and detect bender collision
  if(f){display.drawLine(hunterx+10,huntery+7,hunterx+10,huntery+7-100,1);
    if(bendery<huntery&&(abs(hunterx-benderx)<8))newBender();}
  else if(g){display.drawLine(hunterx+5,huntery+5,hunterx+5,huntery+5+100,1);
    if(bendery>huntery&&(abs(hunterx-benderx-2)<8))newBender();}
  else if(h){display.drawLine(hunterx+7,huntery+7,hunterx+7-100,huntery+7,1);
    if(benderx<hunterx&&(abs(huntery-bendery)<8))newBender();}
  else if(i){display.drawLine(hunterx+7,huntery+7,hunterx+7+100,huntery+7,1);
    if(benderx>hunterx&&(abs(huntery-bendery)<8))newBender();}

  // print the score
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2,57);
  display.println(benderscore);

  // display and delay
  display.display();
  delay(10);
}

void newBender()
{
  benderscore+=1;
  benderx=random(128-16);
  bendery=random(64-16);
}

void partyloop() 
{
    displayText(banner);
}

void displayText(String input) {

  if((millis()-lastParty)>5000)
  {
    lastParty=millis(); // only party every 5 seconds
    
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(5,20);
    display.clearDisplay();
    display.println(input);
    display.display();
    delay(1);
    display.invertDisplay(true);
    delay(20);
    display.invertDisplay(false);
    delay(20);
    display.invertDisplay(true);
    delay(20);
    display.invertDisplay(false);
    delay(20);
    display.invertDisplay(true);
    delay(20);
    display.invertDisplay(false);
    delay(20);

    
    int partydirection=random(4);
    
    if(partydirection==0)display.startscrollright(0x00, 0x0F); 
    if(partydirection==1)display.startscrollleft(0x00, 0x0F); 
    if(partydirection==2)display.startscrolldiagright(0x00, 0x0F); 
    if(partydirection==3)display.startscrolldiagleft(0x00, 0x0F); 
  
  }

}
