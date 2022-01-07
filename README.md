# CALVE HEATER
This product features 3 main parts: the fabric containig a heater and  temperature RTD sensor embedded in it, a PCB that runs the heater and warming process and Firmware that is burnt in to the MCU located on the PCB assembly. 
The product features a modular approach where the controlling PCB can be plugged and unplugged from the fabric at will. It has a small form factor that allows it to be a hand held device that is powered via a Li-Po battery.

![calve_heater](https://user-images.githubusercontent.com/85989401/148527832-ed9df572-df2b-413e-93af-cbba2c7b436f.png)

![calve_heater 4](https://user-images.githubusercontent.com/85989401/148527747-6fef1afc-839d-4003-b079-f2b616777e77.png)

### How it works 🔧
THe PCB contains JST connectors from where the heater and temperature sensor are plugged into the board. Make sure thwy are plugged in. Press the ON button(left od USB) and the device wakes up and starsts the heating process. To turn off the device, Long press the ON button for about 1 sec. This will cause the device to go to sleep.
Temperature level setting is achieved via the use of the temperature button. (Button right of the USB). Default setting is at 40 degrees. Pressing it once increases the level to 44 deg, pressing it once again increases the level to 48 deg. Once at the highest level pressing the button again will take the level back to the initial  40 deg. The temperature level is indicated by use of the LED below the temperature button. 

- Green = 40deg
- Blue = 44deg
- Red = 48deg
<br>
The device uses PID control to warm up the fabric and maintain the desired temperature at all times ensuring safe.bumpless and comfortable use.
When the battery level gets too low the RED led flashes at 1 sec intervals indicating need for charging. 
the device is charged via the Micro-USB port. During charging, 2 leds below the on button are used for monitoring. Red is constantly on if its connected to power, and the Green LED indicates charging status:
- ON = CHarging
- OFF = Done charging <br>
<br>

# HARDWARE COMPONENTS
Heater [link](https://www.alibaba.com/product-detail/High-Temperature-Flexible-Ployimide-PI-Film_60627303766.html)   [link2](https://www.alibaba.com/product-detail/Thermostatic-electric-carbon-fiber-heating-element_62302051301.html?spm=a2700.wholesale.0.0.c5e0bc1cLrvEdd) <br>
Battery [link](https://www.indiamart.com/proddetail/lithium-ion-batteries-3-7v-2500mah-10433305048.html)  <br>
RTD sensor [link](https://www.digikey.com/en/products/detail/te-connectivity-measurement-specialties/R-8203/5277360)<br>
<br>
For the PCB components refer to the BOM folder in the hardware section.

# SAFETY
All the electrical components are on the PCB and can be disconnected in case of any critical situations by the user. Ensure to keep the device free from water and dust that may block the connectors. Disconnect the PCB device when washing the fabric. The Heater is a well made material wwith insulated wires to avoid shocking the user in amy way. When washing ensure not to cut, scrape or peel off any parts. Consider best practices [link](https://www.youtube.com/watch?v=5kIUcR_C9-A)

# BURNING BOOTLOADER AND FIRMWARE TO THE PCB
### Download the Files :arrow_down_small:
From this repo click on the download option at the code :arrow_double_down: 
- You will have two folders inside the main folder i.e 📁 Bootloader and  📁clock_module_code
<br>
##  Burning bootload to the MCU :fire:
 <h3> Note: 
 DO THIS ON A WINDOWS OPERATING SYSTEM!!!
  </h3>
1) To do this you will need an older version of the arduino particularly version 1.6.9 find it here :link: [Old SoftwareReleases Arduino IDE](https://www.arduino.cc/en/main/OldSoftwareReleases) <br/>
2) Once you have it setup to burn the bootloader follow this tutotial keenly:link: [Burning Arduino Bootloader](https://create.arduino.cc/projecthub/techmirtz/arduino-without-external-clock-crystal-on-atmega328-d4fcc4) <br>
3) You can also use a USBASP to burn the bootloader. Note the above instruction will be used but instead of selecting arduino as ISP your programmer the USBASP is selected. 

![image](https://user-images.githubusercontent.com/85989401/146667082-94dd6fc7-de50-4675-a084-ad729f834af0.png)

[buy usbasp](https://aliexpress.ru/af/USBASP-USBISP-AVR-Programmer-USB.html?catId=0&d=y&aff_platform=portals-tool&initiative_id=SB_20201020044645&origin=n&sk=_9JHld5&aff_trace_key=4b1704d992da43b586041dfb7cd31d7e-1606574782769-00350-_9JHld5&SearchText=USBASP%2BUSBISP%2BAVR%2BProgrammer%2BUSB&terminal_id=351d58321dfa473cb106b58978d7c19c)
or here 
 :link: [buy usbasp](https://aliexpress.ru/item/32649685244.html?spm=a2g0o.productlist.0.0.22e26eaf2mIeLt&algo_pvid=b6506204-320d-4244-9d76-c7a1c32c5ee5&algo_expid=b6506204-320d-4244-9d76-c7a1c32c5ee5-16&btsid=0b8b036a16065747853274219e2939&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_)
 <br/>
 
 ## Uploading the codes  :arrow_up:
 1) Open the 📁clock_module_code Folder and open the INO file with your arduino
2) If you use Arduino as your programmer or an FTDI, Follow the instructions here from step 3: [Uploading Code](https://create.arduino.cc/projecthub/techmirtz/arduino-without-external-clock-crystal-on-atmega328-d4fcc4)
3) However if you are using a USBASP, Follow the following instructions:<br>
   a) Insert the ISP programmer cable socket onto ISP header. ...<br>
   b) Open Arduino IDE software. ...<br>
   c) Next, call out any example of source code. ...<br>
   d) Select “USBasp” from the Tools > Programmer menu.<br>
   e) Select “Upload using Programmer” from the File menu.<br>
 You can also explore more from the following tutorial :link:[How to Use USBasp Programmer with Arduino Boards](https://www.youtube.com/watch?v=ToKerwRR-70)
 
