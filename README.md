# Keypad And UART Example | TM4C123

Main Purpose : Finds the average of two numbers entered from the keypad. Writes this value to the screen with putty (or another serial port interface program).

# CONNECTIONS

Keypad :

![image](https://user-images.githubusercontent.com/67158049/124270363-c720b280-db44-11eb-9b63-5868579752fa.png)

I made the ROWs connections as follows:
R1 - R4 => PD0-PD3
I made the COLUMNs connections as follows:
C1-C3 => PC5-PC7

USB TTL CONVERTER :

![image](https://user-images.githubusercontent.com/67158049/124270474-eb7c8f00-db44-11eb-8be3-912f6922c9cb.png)

I connected the USB TTL Converter's GND to
the launch pad's GND.
I made the other pins connections as follows:
RX => PE5
TX => PE4

Youtbe Video Link : https://youtu.be/MFl8qA0JchM

Informative Article About Keypad : https://lastminuteengineers.com/arduino-keypad-tutorial/
TM4C123GH6PM Datasheet  : https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf?ts=1625664852201&ref_url=https%253A%252F%252Fwww.google.com%252F
Informative Text & Article About Uart On TM4C123 : https://microcontrollerslab.com/uart-communication-tm4c123-tiva-c-launchpad/

Also you can look this example : https://github.com/omerkarslioglu/ATM_Module_Designing_On_TM4C123/blob/main/README.md

Thanks for reading ...

Ömer Karslıoğlu
