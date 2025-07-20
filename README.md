# IoT_LoadCell_Calibration

                                                          ⚖️ LoadCell Calibration
                                                      
  This project demonstrates the implementation of a digital weighing system using a Load Cell, HX711 amplifier module, and a 16x2 I2C LCD, all integrated with an ESP32 microcontroller. The system accurately measures and displays weight in real time, making it ideal for smart weighing scales, kitchen scales, industrial automation, and IoT-based weight monitoring solutions.
The HX711 module amplifies and converts the analog signal from the Load Cell into a digital value readable by the ESP32. The measured weight is then displayed on the LCD screen. With proper calibration, the system offers high precision and reliability.

                                                        🧰 Components & Their Functions
 
 Component	                                   Function
 
 1) ESP32	                      Microcontroller that reads digital data from the HX711 and controls the LCD to display the weight.
 2) Load Cell	                  Measures weight or force applied and outputs a small analog voltage proportional to the load.
 3) HX711 Amplifier Module	    Converts the small analog signal from the Load Cell into a digital signal for the ESP32.
 4) 16x2 LCD with I2C Module   	Displays the weight in real-time; I2C reduces the number of pins needed for connection.
