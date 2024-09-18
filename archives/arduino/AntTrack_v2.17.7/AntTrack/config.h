//================================================================================================= 
//================================================================================================= 
//
//                                    C O N F I G U R A T I O N 

#define MAJOR_VERSION      2
#define MINOR_VERSION      17
#define PATCH_LEVEL        7

/*
=================================================================================================== 
                                M o s t    R e c e n t   C h a n g e s
=================================================================================================== 
  Complete change log and debugging options are at the bottom of this tab
  
GitHub Tag
----------                

V2.17.0   2021-03-16 Add "GPS on the Tracker" option, aka movable tracker.  
          2021-03-17 Use ap33_alt_ag instead of ap33_amsl. Still calcs relative alt above field.   
          2021-03-24 Beta. Support dynamic (moving) tracker with mag and GPS on the box. 
                     Bug fixes.  
V2.17.1   2021-03-29 Rationalise patches and simplify servo code  
V2.17.2   2021-04-02 Clean build of STM32F103, Maple Mini and Teensy 3.x code.   
V2.17.3   2021-04-07 Clean compile and test - WiFi UDP in    
          2021-04-09 ESP Servo lib, degrees not PWM like STM32
V2.17.4   2021-04-16 Clean compile Mavlink BT input option    
V2.17.5   2021-04-17 Alpha code - not tested:  Add FrSky BT input option       
V2.17.6   2021-04-19 For Frsky input only, hbGood = gpsGood    
V2.17.7   2021-04-19 pan-sattan : #ReverseElevation typo 
                     Complete coding for HMC5883L magnetometer  
                    
*/
//================================== Please select your options below before compiling ==================================

#define Device_sysid     251                     // Our Mavlink Identity - APM FC is 1, Mission Planner is 255, QGC default is 0 
#define Device_compid    MAV_COMP_ID_PERIPHERAL  // 158 Generic autopilot peripheral - APM FC is 1, MP is 190, QGC is  https://mavlink.io/en/messages/common.html


// Choose one only of these input channels 
// How does telemetry enter the tracker?
#define Telemetry_In  0    // Serial Port (default) - all protocols        
//#define Telemetry_In  1    // Mavlink BlueTooth Classic- ESP32 
//#define Telemetry_In  2    // Mavlink WiFi - ESP only
//#define Telemetry_In  3    // FrSky UDP - ESP only
//#define Telemetry_In  4    // FrSky BT - ESP32 only



// Select a heading source. We need this to relate the external world of co-ordinates to the internal tracker co_ordinates.
#define Heading_Source  2     // 1=Flight_GPS, 2=Flight_Computer, 3=Trackerbox_Compass  4=Trackerbox_GPS_And_Compass

//#define HMC5883L            // Select compass type
#define QMC5883L



// If the tracker box has a GPS AND a compass attached, we support a moving tracker. For example,
// the tracker could be on one moving vehicle and track a second moving vehicle, or a 'plane could 
// always point an antenna at home base.


#define home_decay_secs 60  // Home data decay secs. if power lost and restored within decay secs, Home is restored from NVM.


// NOTE: The Bluetooth class library uses a lot of application memory. During Compile/Flash
//  you may need to select Tools/Partition Scheme: "Minimal SPIFFS (1.9MB APP ...)


//#define BT_Master_Mode true    // Master connects to BT_Slave_Name --- false for BT Slave Mode
const char* BT_Slave_Name   =   "Crossfire 0277";  // Example


//#define QLRS           // Un-comment if you use the QLRS variant of Mavlink 


//=========================================================================================================
//                                    S E R V O   S E T T I N G S
//=========================================================================================================

  //#define Az_Servo_360         // Means the azimuth servo can point in a 360 deg circle, elevation servo 90 deg
                                 // Default (comment out #define above) is 180 deg azimuth and flip over 180 deg elevation 

  // Set the degree range of the servos here. Do not adjust servo mechanical limits here.                         
  #if defined Az_Servo_360   // 1 x 360, 1 x 90 (or 180) servos  
    int16_t minAz = 0;          // Az lower limit in degrees, left of tracker facing flying field
    int16_t maxAz = 359;        // Az upper limit in degrees
    int16_t minEl = 0;          // El lower limit in degrees, horizontal 
    int16_t maxEl = 90;         // El upper limit in degrees, straight up
  #else                      // 2 x 180 deg servos
    int16_t minAz = 0;          // Az lower limit in degrees, left of tracker facing flying field
    int16_t maxAz = 180;        // Az upper limit in degrees, right of tracker facing flying field
    int16_t minEl = 0;          // El lower limit in degrees, horizontal and forward
    int16_t maxEl = 180;        // El upper limit in degrees, horizontal and rearward
  #endif 

  // Sometimes the mechanical movement of a servo is reversed due to the orientation of its mounting
  // Its movement may be reversed here to compensate
  #define ReverseAzimuth          // my azimuth servo has a reversed action
  //#define ReverseElevation


  // Default values for SG90 servos; 500 and 2400
  // My 180 deg servos have a PWM range of 700 through 2300 microseconds. Your's may differ. 
  // ADJUST THE MECHANICAL LIMITS OF MOVEMENT OF YOUR SERVOS HERE BELOW

  uint16_t minAzPWM = 625;   // right (because mine is reversed)
  uint16_t maxAzPWM = 2265;  // left 
  uint16_t minElPWM = 565;   // front
  uint16_t maxElPWM = 2257;  // back


//=============================================================================================
//=====================   S E L E C T   E S P   B O A R D   V A R I A N T   ===================

//#define ESP32_Variant     1    //  ESP32 Dev Module - there are several sub-variants that work
//#define ESP32_Variant     4    //  Heltec Wifi Kit 32 
#define ESP32_Variant     5    //  LILYGO® TTGO T-Display ESP32 1.14" ST7789 Colour LCD
//#define ESP32_Variant     6    // LILYGO® TTGO T2 ESP32 OLED Arduino IDE board = "ESP32 Dev Module"
//#define ESP32_Variant     7    // ESP32 Dev Module with ILI9341 2.8" colour TFT SPI 240x320
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//=============================================================================================
//                            D E F A U L T   W I F I   S E T T I N G S   
//=============================================================================================

#define Start_WiFi                              // Start WiFi at startup, override startWiFi pin

#define HostName             "MavToPass"        // This translator's host name
#define APssid               "MavToPassthru"    // The AP SSID that we advertise         ====>
#define APpw                 "password"         // Change me! Must be >= 8 chars
#define APchannel            9                  // The wifi channel to use for our AP
#define STAssid              "MavToPassthru"      // Target AP to connect to (in STA mode) <====
#define STApw                "password"         // Target AP password (in STA mode). Must be >= 8 chars      

// Choose one default mode for ESP only - AP means advertise as an access point (hotspot). STA means connect to a known host
//#define WiFi_Mode   1  //AP            
#define WiFi_Mode   2  // STA
//#define WiFi_Mode   3  // (STA>AP) STA failover to AP 

// Choose one default protocol - for ESP only
//#define WiFi_Protocol 1    // TCP/IP
#define WiFi_Protocol 2    // UDP 

//  const char    *STAssid =     "EZ-WifiBroadcast";    
//  const char    *STApw =       "wifibroadcast";         

//  const char    *STAssid =     "TXMOD-54-DD-FE";   
//  const char    *STApw =       "txmod123"; 

uint16_t  TCP_localPort = 5760;     
uint16_t  TCP_remotePort = 5760;    
uint16_t  UDP_localPort = 14550;    // Mav readPort,  Frsky +1
uint16_t  UDP_remotePort = 14555;   // Mav sendPort,  FrSky +1


//=========================== Auto Determine Target Platform =====================================
//
//                Don't change anything here
//
#if defined (__MK20DX128__) || defined(__MK20DX256__)
  #define TEENSY3X
  #define Target_Board   0      // Teensy 3.1 and 3.2    
      
#elif defined (__BluePill_F103C8__) ||  defined (MCU_STM32F103RB)
  #define Target_Board   1      // Blue Pill STM32F103C  
  #define STM32F103C
         
#elif defined (STM32_MEDIUM_DENSITY) 
  #define Target_Board   2      // Maple_Mini STM32F103C     
#elif defined (_BOARD_MAPLE_MINI_H_)
  // LeafLabs high density
  #define Target_Board   2      // Maple_Mini 
  #define MAPLE_MINI
#elif defined STM32_HIGH_DENSITY
  // LeafLabs high density
  #define Target_Board   2      // Maple_Mini 
  #define MAPLE_MINI
#elif defined ESP32
  #define Target_Board   3      // Espressif ESP32 Dev Module

#elif defined ESP8266
  #define Target_Board   4      // Espressif ESP8266
  
#else
  #error "No board type defined!"
#endif


  #if (defined ESP32 || defined ESP8266) && ((Telemetry_In == 2) || (Telemetry_In == 3))
    #define wifiBuiltin   //  for this feature we need wifi support compiled in
  #endif    

   #if (defined ESP32 || defined ESP8266) && ( (Telemetry_In == 1) || (Telemetry_In == 4) )
    #define btBuiltin   //  for this feature we need bluetooth support compiled in
  #endif



//************************************** Macro Logic Checks ************************************* 
  #ifndef Target_Board
    #error Please choose at least one target board
  #endif

  #if (Target_Board == 0) 
    //#error Teensy 3.x not yet supported. 
  #endif  

  #if (Target_Board == 1) 
    #if defined displaySupport
     #error Blue Pill  version does not yet support a display
    #endif  
  #endif  

  #if (Target_Board == 2) 
    #if defined displaySupport
      #error Maple Mini version does not yet support a display
    #endif  
  #endif  

  #if not defined Heading_Source
   #error Please define a Heading_Source
  #endif
  #if ((Heading_Source == 3) || (Heading_Source == 4))
    #if ( (not defined HMC5883L) && (not defined QMC5883L) )
      #error Please define a compass type 
    #endif
  #endif  

  uint8_t headingSource = Heading_Source;
 
  #if (Target_Board == 4) 
    #error ESP8266 should work but you need to work out the detail yourself
  #endif 
 
  #if (Target_Board != 3) 
     #if (Telemetry_In  == 1) || (Telemetry_In  == 2) 
       #error WiFi or Bluetooth works only on an ESP32 board, rather select serial in
     #endif  
  #endif

  #ifndef Telemetry_In  
    #error Please choose at least one Mavlink input type, Serial, Bluetooth or WiFi 
  #endif  
  
  #if (Target_Board == 3)
    #ifndef WiFi_Mode 
      #error Please define WiFi_Mode
    #endif  
    #ifndef WiFi_Protocol
      #error Please define WiFi_Protocol
    #endif
  #endif 
//================================= P L A T F O R M   D E P E N D E N T   S E T U P S =============================

//======================================= LEDS, OLED SSD1306, rx pin =====================================

  
#if (Target_Board == 0)           //   (TEENSY3X) 
  #include <PWMServo.h>     
  #define in_rxPin        0       // rx1 tx1 - Serial1
  #define in_txPin        1
  uint8_t gps_rxPin =     9;      // rx2 tx2 - Serial2 for tracker box GPS if applicable
  #define gps_txPin      10  
  bool rxInvert = true;           // ONLY FOR FrSky S.Port, NOT F.Port, NOT MAVLINK     
  #define frOneWire     true      // ONLY FOR FrSky S.Port
  #define SetHomePin     11
  #define StatusLed      14
  #define azPWM_Pin       5
  #define elPWM_Pin       6
  #define BuiltinLed     13
  #undef  displaySupport 
  #define SDA            17  // I2C OLED board and/or Compass - default must be changed in Wire.h 
  #define SCL            16  // I2C OLED board and/or Compass - default must be changed in Wire.h 
  //=========================================================================   
#elif (Target_Board == 1)         // Blue Pill
  #include <Servo.h>  
  uint8_t in_rxPin =        PA03;  // rx2 Serial1
  #define in_txPin          PA02   // tx2 Serial1
  uint8_t gps_rxPin =       PA10;  // rx3 Serial2
  #define gps_txPin         PA09   // tx3 Serial2
  bool rxInvert = true;           // ONLY FOR FrSky S.Port, NOT F.Port, NOT MAVLINK    
  #define SetHomePin        PA0;    
  #define StatusLed         PA06  // Off=No good GPS yet, flashing=good GPS but home not set yet, solid = ready to track
  #define azPWM_Pin         PA07  // azimuth servo 
  #define elPWM_Pin         PA08  // elevation servo
  #define BuiltinLed        PC13  
  #define SDA               PB07  // I2C OLED board and/or Compass - default must be changed in Wire.h 
  #define SCL               PB06  // I2C OLED board and/or Compass - default must be changed in Wire.h 
  //=========================================================================   
#elif (Target_Board == 2)         // Maple Mini

  #include <Servo.h>  
  uint8_t in_rxPin =       26;  // rx1 Serial1
  #define in_txPin         25   // tx1 Serial1
  uint8_t gps_rxPin =       8;  // rx2 Serial2
  #define gps_txPin         9   // tx2 Serial2
   bool rxInvert = true;        // ONLY FOR FrSky S.Port, NOT F.Port, NOT MAVLINK    
  #define SetHomePin        5    
  #define StatusLed         6   // Off=No good GPS yet, flashing=good GPS but home not set yet, solid = ready to track
  #define azPWM_Pin         4   // azimuth servo 
  #define elPWM_Pin         5   // elevation servo  consider pin 10  this pin=rx2 (9=tx2)
  #define BuiltinLed       33   // PB1   
  #define SDA              15   // I2C OLED board and/or Compass - default must be changed in Wire.h 
  #define SCL              16   // I2C OLED board and/or Compass - default must be changed in Wire.h 
  
#elif (Target_Board == 3)         // ESP32 Platform
// For info: Avoid SPI pins - generally   CS=5    MOSI=23   MISO=19   SCK=18  
  #include <ESP32_Servo.h>  
  //=========================================================================   
  #if (ESP32_Variant == 1)          // ESP32 Dev Module
  uint8_t in_rxPin =        27;  // uart1
  #define in_txPin          17 
  uint8_t gps_rxPin =       13;  // uart2 for tracker box GPS if applicable
  #define gps_txPin          4  
  bool rxInvert = true;          // ONLY FOR FrSky S.Port, NOT F.Port, NOT MAVLINK
  #define SetHomePin        18    
  #define StatusLed         25  // Off=No good GPS yet, flashing=good GPS but home not set yet, solid = ready to track
  #define BuiltinLed        99
  #define azPWM_Pin         32  // azimuth servo (can't be 34,35,36,39 because input only !!)
  #define elPWM_Pin         33  // elevation servo(can't be 34,35,36,39 because input only !!)
  #define BuiltinLed        02  // PB1   

    //#define displaySupport       // uncomment me if you have a SSD1306 display
    #if (defined displaySupport)   // Display type defined with # define displaySupport   
      #define SSD1306_Display         // OLED display type    
      /* Below please choose either Touch pin-pair or Digital pin-pair for display scrolling
       *  Pin == 99 means the pin-pair is not used
       */ 
      #define Pup           99        // Board Button 1 to scroll the display up
      #define Pdn           99        // Board Button 2 to scroll the display down   
      #define Pinfo         99        // Digital pin to toggle information/log page
      #define Tup           33        // Touch pin to scroll the display up
      #define Tdn           32        // Touch pin to scroll the display down 
      #define Tinfo         99        // 02 Touch pin to toggle information/log page   
          
      #define SDA           21        // I2C OLED board and/or Compass
      #define SCL           22        // I2C OLED board and/or Compass
      #define display_i2c_addr      0x3C       // I2C OLED board
    #endif   
    /*  
      SPI/CS                       Pin 05   For optional TF/SD Card Adapter
      SPI/MOSI                     Pin 23   For optional TF/SD Card Adapter
      SPI/MISO                     Pin 19   For optional TF/SD Card Adapter
      SPI/SCK                      Pin 18   For optional TF/SD Card Adapter  
    */
  #endif
  //=========================================================================   
  #if (ESP32_Variant == 4)       // Heltec Wifi Kit 32 (NOTE! 8MB) 
  uint8_t in_rxPin =        18;  // uart1
  #define in_txPin          17 
  uint8_t gps_rxPin =       13;  // uart2 for tracker box GPS if applicable
  #define gps_txPin         14    
  bool rxInvert = true;          // ONLY FOR FrSky S.Port, NOT F.Port, NOT MAVLINK
  #define SetHomePin        23    
  #define StatusLed         19   // Off=No good GPS yet, flashing=good GPS but home not set yet, solid = ready to track
  #define BuiltinLed        99 
  #define azPWM_Pin         32   // azimuth servo (can't be 34,35,36,39 because input only !!)
  #define elPWM_Pin         33   // elevation servo(can't be 34,35,36,39 because input only !!)

    #if !defined displaySupport       // I2C OLED board is built into Heltec WiFi Kit 32
      #define displaySupport
    #endif  
    #define SSD1306_Display         // OLED display type  
    #define SCR_ORIENT   1          // 1 Landscape or 0 Portrait 
    /* Below please choose either Touch pin-pair or Digital pin-pair for display scrolling
     *  Pin == 99 means the pin-pair is not used
     */ 
    #define Pup           99        // Board Button to scroll the display up
    #define Pdn           99        // Board Button to scroll the display down
    #define Pinfo         99        // 02 Digital pin to toggle information/log page
    #define Tup           12        // 33 Touch pin to scroll the display up
    #define Tdn           11        // 32 Touch pin to scroll the display down 
    #define Tinfo         02        // 02 Touch pin to toggle information/log page
    
    #define SDA           04        // I2C OLED board and/or Compass
    #define SCL           15        // I2C OLED board and/or Compass
    #define display_i2c_addr      0x3C       // I2C OLED board
    #define OLED_RESET    16        // RESET here so no reset lower down     

    /*  
      SPI/CS               05   For optional TF/SD Card Adapter
      SPI/MOSI             23   For optional TF/SD Card Adapter
      SPI/MISO             19   For optional TF/SD Card Adapter
      SPI/SCK              18   For optional TF/SD Card Adapter  
    */

  #endif
  //=========================================================================   
  #if (ESP32_Variant == 5)          // LILYGO® TTGO T-Display ESP32 1.14" ST7789 Colour LCD, IDE board = "ESP32 Dev Module"
    uint8_t in_rxPin =        27;       // uart1 for general serial in, including flight gps
    #define in_txPin          17 
    uint8_t gps_rxPin =       13;       // uart2 for tracker box GPS if applicable
    #define gps_txPin         15
    bool rxInvert = false;              // ONLY FOR FrSky S.Port, NOT F.Port, NOT MAVLINK
    #define SetHomePin        12
    #define StatusLed         25        // Add your own LED with around 1K series resistor
    #define BuiltinLed        99    
    #define azPWM_Pin         32  // azimuth servo (can't be 34,35,36,39 because input only !!)
    #define elPWM_Pin         33  // elevation servo(can't be 34,35,36,39 because input only !!)    
    #define startWiFiPin  99      // 99=none. No input pin available (non touch!) Could use touchpin with a bit of messy work.    
    
    #if !defined displaySupport    // I2C TFT board is built into TTGO T-Display
      #define displaySupport
    #endif    
    #define ST7789_Display          // TFT display type - if you have a display you must define which type
    #define SCR_ORIENT   1          // 1 Landscape or 0 Portrait    
    
    /* Below please choose either Touch pin-pair or Digital pin-pair for display scrolling
     *  Pin == 99 means the pin-pair is not used
     */ 
    #define Pinfo          2        //    Digital pin to toggle information/log page     
    #define Pup            0        //  0 Board Button 1 to scroll the display up
    #define Pdn           35        // 35 Board Button 2 to scroll the display down 
    #define Tinfo         99        //    Touch pin to toggle information/log page       
    #define Tup           99        // 33 Touch pin to scroll the display up
    #define Tdn           99        // 32 Touch pin to scroll the display down   
    
    #define SCR_ORIENT     1        // 1 Landscape or 0 Portrait
 
    #define SDA           21        // I2C TFT board and/or Compass (grey wire)
    #define SCL           22        // I2C TFT board and/or Compass (brown wire)
    #define display_i2c_addr      0x3C     
    #define compass_i2c_addr      0x1E   // 0x1E for HMC5883L   0x0D for QMC5883
  #endif
   //=========================================================================   
  #if (ESP32_Variant == 6)          // LILYGO® TTGO T2 ESP32 OLED Arduino IDE board = "ESP32 Dev Module"
    uint8_t in_rxPin =        17;       // uart1 for general serial in, including flight gps
    #define in_txPin          18 
    uint8_t gps_rxPin =       19;       // uart2 for tracker box GPS
    #define gps_txPin         21  
    bool rxInvert = true;               // ONLY FOR FrSky S.Port, NOT F.Port, NOT MAVLINK
    #define SetHomePin        15
    #define StatusLed         25        // Add your own LED with around 1K series resistor
    #define BuiltinLed        99    
    #define azPWM_Pin         14  // azimuth servo (can't be 34,35,36,39 because input only !!)
    #define elPWM_Pin         16  // elevation servo(can't be 34,35,36,39 because input only !!)    
    #if !defined displaySupport      // I2C OLED board is built into TTGO T2
      #define displaySupport
    #endif
    #if !defined SSD1306_Display    
      #define SSD1306_Display         // OLED display type
    #endif 
    #undef ST7789_Display 
    /* Below please choose either Touch pin-pair or Digital pin-pair for display scrolling
     *  Pin == 99 means the pin-pair is not used
     */ 
    #define Pinfo         99        // Digital pin to toggle information/log page          
    #define Pup           99        // Board Button 1 to scroll the display up
    #define Pdn           99        // Board Button 2 to scroll the display down  
    #define Tinfo         99        //    Touch pin to toggle information/log page         
    #define Tup           33        // 33 Touch pin to scroll the display up
    #define Tdn           32        // 32 Touch pin to scroll the display down  
     
    #define SDA           13        // I2C OLED board 
    #define SCL           14        // I2C OLED board
    #define display_i2c_addr      0x3C       // I2C OLED board
  #endif 
  //=========================================================================  
  #if (ESP32_Variant == 7)          // ESP32 Dev Module with ILI9341 2.8" colour TFT SPI 240x320
    uint8_t in_rxPin =        16;       // uart1 for general serial in, including flight gps
    #define in_txPin          17 
    uint8_t gps_rxPin =       13;       // uart2 for tracker box GPS if applicable
    #define gps_txPin          4
    bool rxInvert = false;              // ONLY FOR FrSky S.Port, NOT F.Port, NOT MAVLINK
    #define SetHomePin         5
    #define StatusLed          2        // Add your own LED with around 1K series resistor
    #define BuiltinLed        99    
    #define azPWM_Pin         32  // azimuth servo (can't be 34,35,36,39 because input only !!)
    #define elPWM_Pin         33  // elevation servo(can't be 34,35,36,39 because input only !!)    
    #define startWiFiPin  99      // 99=none. No input pin available (non touch!) Could use touchpin with a bit of messy work.
    #if !defined displaySupport     
      #define displaySupport
    #endif
    #define ILI9341_Display         // ILI9341 2.8" COLOUR TFT SPI 240x320 V1.2  
    #define SCLK          18        // blue wire on my test setup
    #define MOSI          23        // yellow wire
    #define CS            25        // white wire
    #define DC            26        // green wire  
    #define RST           27        // brown wire
    // LED=3.3V,  Vcc=5v,  Gnd 
    // MISO                not used by Adafruit     
    
    /* Below please choose either Touch pin-pair or Digital pin-pair for display scrolling
     *  Pin == 99 means the pin-pair is not used
     */ 
               
    #define Pup           99        // 35 Board Button 1 to scroll the display up
    #define Pdn           99        //  0 Board Button 2 to scroll the display down     
    #define Tup           12        // Touch pin to scroll the display up
    #define Tdn           14        // Touch pin to scroll the display down   

    #define SDA           21        // I2C for tracker box compass
    #define SCL           22        // I2C 

  #endif     
#endif

  //=================================================================================================   
  //                                D I S P L A Y   S U P P O R T   
  //=================================================================================================  

  #if defined displaySupport
    #if (!( (defined SSD1306_Display) || (defined SSD1331_Display) || (defined ST7789_Display) || (defined ILI9341_Display) ))
      #error please define a display type in your board variant configuration, or disable displaySupport
    #endif   

    #if not defined SD_Libs_Loaded    // by SD block
      #include <SPI.h>                // for SD card and/or Display
    #endif  

    typedef enum display_mode_set { logg = 1 , flight_info = 2 } display_mode_t;
    
    display_mode_t      display_mode;     
        
    bool infoPressBusy = false;
    bool infoNewPress = false;         
    bool infoPressed = false;
    bool show_log = true;    
    uint32_t info_debounce_millis = 0; 
    uint32_t  info_millis = 0; 
    uint32_t  last_log_millis = 0;
    const uint16_t db_period = 1000; // debounce period mS

/*
    // Generic colour definitions
    #define BLACK           0x0000
    #define BLUE            0x001F
    #define RED             0xF800
    #define GREEN           0x07E0
    #define CYAN            0x07FF
    #define MAGENTA         0xF81F
    #define YELLOW          0xFFE0
    #define WHITE           0xFFFF 
*/
    //==========================================================
    
    #if (defined ST7789_Display)      // TTGO T_Display 1.14 TFT display 135 x 240 SPI
      #include <TFT_eSPI.h>           // Remember to select the T_Display board in User_Setup_Select.h in TFT_eSPI library (135 x 240)                        
      TFT_eSPI display = TFT_eSPI();
      #define SCR_W_PX      240       // OLED display width, in pixels
      #define SCR_H_PX      135       // OLED display height, in pixels

      #if (SCR_ORIENT == 0)           // portrait
        #define SCR_H_CH     20       // characters not pixels
        #define SCR_W_CH     11       // ?
        #define CHAR_W_PX    12       // pixels    
        #define CHAR_H_PX    12       // pixels 
        #define TEXT_SIZE     1                
      #elif (SCR_ORIENT == 1)         // landscape
        #define SCR_H_CH      8       // characters not pixels 
        #define SCR_W_CH     20  
        #define CHAR_W_PX    12       // 12 x 20 = 240  
        #define CHAR_H_PX    16       // 16 x 8 =  128
        #define TEXT_SIZE     2                       
      #endif 
      
    //==========================================================
    
    #elif (defined SSD1306_Display)    // SSD1306 OLED display     (128 x 64) 
      #include <Adafruit_GFX.h>
      #include <Adafruit_SSD1306.h> 
      #define SCR_W_PX 128     // OLED display width, in pixels
      #define SCR_H_PX 64      // OLED display height, in pixels
      #define SCR_ORIENT  1    // 0 portrait  1 landscape
      #define TEXT_SIZE   1
      #define SCR_H_CH    8    // characters not pixels 
      #define SCR_W_CH   21   
      #define CHAR_W_PX   6    // 6 x 21 = 126  
      #define CHAR_H_PX   8    // 8 x 8 = 64    
      #ifndef OLED_RESET
        #define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
      #endif  
      Adafruit_SSD1306 display(SCR_W_PX, SCR_H_PX, &Wire, OLED_RESET); 
          
    //==========================================================  
    #elif (defined SSD1331_Display)    // SSD1331 0.95" TTGO T2 colour TFT display (96 x 64)
      #include <Adafruit_GFX.h>
      #include <Adafruit_SSD1331.h>
      #define SCR_W_PX    96     // OLED display width, in pixels
      #define SCR_H_PX    64     // OLED display height, in pixels
      #define SCR_ORIENT   1     // 0 portrait  1 landscape
      #define TEXT_SIZE    1
      #define SCR_H_CH     8     // characters not pixels 
      #define SCR_W_CH    16        
      #define CHAR_W_PX    6     // 6 x 16 = 96   
      #define CHAR_H_PX    8     // 8 x 8  = 64 
      Adafruit_SSD1331 display = Adafruit_SSD1331(CS, DC, MOSI, SCLK, RST);  
      
    //========================================================== 
    #elif  (defined ILI9341_Display)    // ILI9341 2.8" COLOUR TFT SPI 240x320 V1.2  
      #include "Adafruit_GFX.h"   
      #include "Adafruit_ILI9341.h"
      // Uses hardware SPI
      
      Adafruit_ILI9341 display = Adafruit_ILI9341(CS, DC, RST);    // LED=3.3V,  Vcc=5v,  Gnd 
         
      #define SCR_ORIENT   1            // 0 for portrait or 1 for landscape
      #define TEXT_SIZE    2            // default, may be changed on the fly
        
      #if (SCR_ORIENT == 0)      // portrait
        #define SCR_H_PX  320
        #define SCR_W_PX  240  
      #elif (SCR_ORIENT == 1)    // landscape
        #define SCR_H_PX  240
        #define SCR_W_PX  320
      #endif 

      #if (TEXT_SIZE == 1) 
        #define CHAR_W_PX    6     // 40 / 53 ch wide   portrait / landscape
      #elif  (TEXT_SIZE == 2)       
        #define CHAR_W_PX    12    // 20 / 26 ch wide  
      #elif  (TEXT_SIZE == 3)  
        #define CHAR_W_PX    18    // 13 / 17 ch wide
      #elif  (TEXT_SIZE == 4)  
        #define CHAR_W_PX    24    // 10 / 13 ch wide
      #elif  (TEXT_SIZE == 5)  
        #define CHAR_W_PX    30    // 10 / 8 ch wide
      #endif
      
     #define CHAR_H_PX   (CHAR_W_PX) + ( (CHAR_W_PX) / 3)    // so vertical spacing is h spacing plus 1/3
     #define SCR_W_CH   (SCR_W_PX) / (CHAR_W_PX)     
     #define SCR_H_CH  (SCR_H_PX) / (CHAR_H_PX)  
      
    #endif   
    //==========================================================   

    #if (!(defined SCR_ORIENT) )
      #error please define a desired screen orientation,  0 portrait or 1 landscape for your board variant or display type
    #endif 

    char clear_line[SCR_W_CH+1];
    
    // allocate space for screen buffer   
    #define max_col   SCR_W_CH+1  // +1 for terminating line 0x00        
    #define max_row   64
  
    static const uint16_t threshold = 40;
    volatile bool upButton = false;
    volatile bool dnButton = false;
    
    #if (not defined Tup) 
      #define Tup         99
    #endif

    #if (not defined Tdn) 
      #define Tdn         99
    #endif

    #if (not defined Pup) 
      #define Tup         99
    #endif

    #if (not defined Pdn) 
      #define Tdn         99
    #endif

    typedef enum scroll_set { non = 0, up = 1, down = 2 } scroll_t;
    scroll_t up_down = non; 

    typedef enum last_row_set { omit_last_row = 0, show_last_row = 1} last_row_t;
    last_row_t last_row_action;   

    struct row_t {
      char x[max_col];
      };
  
     row_t ScreenRow[max_row]; 
     
    uint8_t   row = 0;
    uint8_t   col = 0;
    uint8_t   scroll_row = 0;
    uint32_t  scroll_millis =0 ;

  #endif   // end of displaySupport

  //=================================================================================================   
  //                     B L U E T O O T H   S U P P O R T -  E S P 3 2  O n l y
  //================================================================================================= 

#if (Telemetry_In == 1) || (Telemetry_In == 4)     // Bluetooth

  #if (defined ESP32) 

    #define BT_Setup   // so that WiFi setup does not defien these shared variables again
    // Define link variables
    struct linkStatus {
      uint32_t    packets_received;
      uint32_t    packets_lost;
      uint32_t    packets_sent;
     };

      bool          hb_heard_from = false;;
      uint8_t       hb_system_id = 0;
      uint8_t       hb_comp_id = 0;
      uint8_t       hb_seq_expected = 0;
      uint32_t      hb_last_heartbeat = 0;
      linkStatus    link_status;

      #include "BluetoothSerial.h"
      #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
        #error Bluetooth is not enabled! Please run `make menuconfig in ESP32 IDF` 
      #endif
  #else
      #error Bluetooth only available on ESP32
  #endif   
   
#endif

  //=================================================================================================   
  //                       W I F I   S U P P O R T - ESP32 and ES8266 Only
  //================================================================================================= 

    int16_t   wifi_rssi;
    
#if (defined ESP32) && ( (Telemetry_In == 2) || (Telemetry_In == 3) )  // ESP32 and (Mav-WiFi or FrSky-WiFi)
  
    bool      FtRemIP = true;
    uint8_t   AP_sta_count = 0;
    uint8_t   AP_prev_sta_count = 0;

    #ifndef BT_Setup
      // Define link variables
      struct linkStatus {
        uint32_t    packets_received;
        uint32_t    packets_lost;
        uint32_t    packets_sent;
      };

       bool          hb_heard_from = false;;
       uint8_t       hb_system_id = 0;
       uint8_t       hb_comp_id = 0;
       uint8_t       hb_seq_expected = 0;
       uint32_t      hb_last_heartbeat = 0;
       linkStatus    link_status;
    #endif
    
    #include <WiFi.h>  
    #include <WiFi.h>  
    #include <WiFiClient.h>


    #include <WiFiAP.h>  // SoftAP
  
    #if ( (WiFi_Protocol == 2)  || (Telemetry_In == 3) )    //  UDP libs
      #include <WiFiUDP.h>    // ESP32 and ESP8266
    #endif      


   //====================       W i F i   O b j e c t s 

    #define max_clients    5
    uint8_t active_client_idx = 0; 

    IPAddress localIP;                           // tcp and UDP
    IPAddress TCP_remoteIP(192,168,4,1);         // when we connect to a server in tcp client mode, put the server IP here  

    #if (WiFi_Protocol == 1)     // TCP  
      WiFiClient *clients[max_clients] = {NULL};   // pointers to TCP client objects (we only need one in this application    
    #endif 
    
    #if ( (WiFi_Protocol == 2)  || (Telemetry_In == 3) )    //  UDP 
      IPAddress UDP_remoteIP(192, 168, 1, 255);    // default to broadcast, but likey to change after connect               
      uint8_t   UDP_remoteIP_B3;                   // last byte of remote UDP client IP  
      #if (WiFi_Protocol == 2)      
        WiFiUDP   mav_udp_object;                    // Instantiate Mavlink UDP object    
      #endif
      #if (Telemetry_In == 3)
        WiFiUDP   frs_udp_object;                    // Object for FrSky telemetry input
      #endif     
    #endif   

#endif
  


//************************************************************************** 
//********************************** Serial ********************************

  #define Log                   Serial         // USB  
  #if (Telemetry_In == 0)    
    #define inSerial            Serial1        // ESP32 General telemetry input   
  #endif  
  #if (Heading_Source == 4) 
    #define gpsSerial           Serial2        // ESP32 Tracker box GPS
  #endif  

// ******************************** D E B U G G I N G   O P T I O N S ***************************************

#define Debug_Minimum    //  Leave this as is unless you need the serial port for something else
#define Debug_Status

//#define Debug_All

//#define Debug_Protocol
//#define Debug_Baud

//#define Debug_AzEl
//#define Debug_Servos 

//#define Debug_LEDs
//#define Debug_boxCompass    
                        
//#define Debug_Input

//#define Debug_Mav_Heartbeat  
//#define Debug_Mav_GPS   
//#define Debug_Mav_Buffer  
//#define Debug_FrSky
//#define Debug_LTM
//#define Debug_MSP
//#define Debug_inGPS               // a GPS on the 'plane

//#define Debug_EEPROM
//#define Debug_Time 
//#define Debug_Home

//#define Debug_BT
//#define Debug_WiFi
//#define Debug_CRC
//#define Debug_FrSky_Messages_UDP
//#define Debug_FrSky_Messages
//#define Debug_FrPort_Stream
//#define Debug_FPort_Buffer
//#define Debug_boxGPS             // the GPS on the tracker box
//#define Debug_boxCompass         // The compass on the tracker box

#define Report_Packetloss   2     // F.Port packet loss every n minutes

//#define Debug_Our_FC_Heartbeat
// *****************************************************************************************************************

/*
*****************************************************************************************************************  
Change log:
                                    
Legacy
v0.37 2019-02-12 Reintroduce PacketGood() location reasonability test to mitigate telemetry errors.
v0.38 OLED support added

v2.00 2019-03-03 Unified version auto detect telemetry speed and protocol. Mavlink 1 & 2, FrSky (D, S.Port and Passthru), LTM
      MSP and GPS support outstanding
v2.01 Support for NMEA GPS added     
v2.05 2019/03/17 UNTESTED BETA Support for retoring home settings from EEPROM after power interruption  
v2.06 2019/06/25 Improved auto baud rate detection. Define in_rxPin correctly for Maple Mini
v2.07 2019/08/10 Tidy up mavlink library paths
v2.08 2019/08/13 Fix mavlink ap_fixtype >2 before using lat and lon. Scroll entire Oled screen.
v2.09 2019/08/16 Supports ESP32 Dev Board - BETA
v2.10 2019/08/23 Improve response in baud detect when no telemetry present.
v2.11 2019/09/06 Mavlink WiFi and Bluetooth input added.  BT not tested.
v2.12 2019/09/18 Store most recent mavlink GPS millis.  
v2.13 2019-11-18 Update WiFi, BT (master/slave), board variants setup, autobaud, OledPrint to Mav2Pt v2.46  
v2.14 2019-12-11 When Heading _Source == 3 (compass on tracker), don't need to check ap_hdg in PacketGood()
      2020-01-02 Sloppy exits removed. :)          
v2.15 2020-10-12 Proper TCP client added for outgoing (to telemetry source) connect   
                 Display scrolling added
                 TCP in tests good.     
v2.15.3 2020-11-08 Fix 10 to power calc for FrSky X.  
v2.15.4 2020-11-12 Patch by mric3412 (pointServos bug in some home heading cases) properly included. 
v2.15.5 2021-02-01 Add hardware signal inversion for S.Port input. Notified by @mello73.   
v2.16.0   2021-02-22 Adopt GitHub Tags
          2021-02-27 Add HUD display. Add FrSky UDP telemetry in
V2.16.1   2021-03-03 Add support for F.Port, auto inversion 
V2.16.2   2021-03-04 Debug FrSky frame decode (fix offset)
                     Fix HUD RSSI blank    
V2.16.3   2021-03-04 Always auto detect serial speed. Always sense polarity, autobaud and detect protocol
          2021-03-09 Include sport, fport1 and fport2. 
          2021-03-09 Tidy up.               
*/
