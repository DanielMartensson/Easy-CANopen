# Easy CANopen

Easy CANopen is a protocol for shaping the CAN-bus message in a specific way that suits industrail automation.

CANopen is a very difficult protocol to use, due to the complexitivity of CANopen. So therefore I’m writing a Easy CANopen protocol available for free to use on any embedded systems such as STM32, Arduino, AVR, PIC etc or PC.

To learn to build on this project, you need to use my examples. I have written this project in `C` language because C is an industry standard. The `C` language dialect I have chosen is `C99` and I don't use dynamical memory allocation in this library. So it will work with `MISRA C` standard.

With this library, you can communicate with valves, engines, actuators, machinery, hardware and all other things that are suitable for industrial automation. I have build up a basic structure of the project and the purpose with my basic structure is to make Easy CANopen work for very small embedded CAN-bus systems. 

Looking for SAE J1939 library?
https://github.com/DanielMartensson/Open-SAE-J1939/

# Status of the project
2023-05-04

New goals for the project

- ANSI C (C89) standard must be applied. See Open-SAE-J1939 library
- Work more on MISRA C compability 
- Make a basic CANopen library with a manual how to add new own features and functionality 
- Test for bugs. I have changed to Microsoft Visual Studio Community and notice that MSVC is more sensitive than GCC compiler.

C coding help is appreciated.

# Getting started

Learn the structure of the project, else you won't be able to understand Easy CANopen. The project structure follows the same pattern. 
After you have got a basic understanding of the project, you are able to build on it. Keep it simple and follow how the manufatures implement the their CANopen protocol.
I don't recomend to implement the complete protocol from `CiA` beacause they are too heavy. Only use the documents from `CiA` as reference manual.

After you have understand the structure of the project, then select processor choice in `Hardware -> Hardware.h` file.
Here you can select for example `STM32`, `Arduino`, `PIC`, `AVR` etc. or if you want to run it on PC first, then select `PROCESSOR_CHOICE 0` and run some examples.
That's the debugging mode for internal CAN feedback.

# How to use the project

 - Step 1: Download this repository
 - Step 2: Go to `Hardware -> Hardware.h` and select your processor, if it's not available, please write code for it and send me a pull request
 - Step 3: Copy over the `Src` folder to your project folder inside your IDE. Rename `Src` to for example `Easy CANopen`. That's a good name.
 - Step 4: Use the `Examples -> Startup.txt` example as your initial starting code for an Easy CANopen project.
 
```c
#include <stdlib.h>
#include <stdio.h>

/* Include Easy CANopen */
#include "Easy_CANopen/Easy_CANopen.h"

int main() {

	/* Code will update soon */

	return 0;
}
```
See the examples in `Examples` folder for more examples.

# The structure of the project

![a](https://raw.githubusercontent.com/DanielMartensson/Easy-CANopen/main/Src/Documentation/Pictures/Project%20structure.png)

# Easy CANopen functionality
 
 - User functions:
 	- Set node ID address
 	- Get node ID address
 	- Set vendor ID, product code, revision number and serial number
 	- Get vendor ID, product code, revision number and serial number
 	- Check if vendor ID, product code, revision number low, revision number high, serial number low, serial number high exist
 	- Set baud rate
 	- Activate baud rate
 	- Save baude rate and node ID
	- Check if there are non configured node ID
 	- Send guard status request
 - Internal functions:
 	- EMCY message produce and consume
 	- Send bootup message
 	- Send heartbeat status
 	
# Questions and answers
 - Q: Can this library be used with `C++`?
 	- A: Yes it can be used with `C++`
 - Q: I want to build on this library, what should I do?
 	- A: First you need to know `C99` and bitwise operations. Then you need to understand the Easy CANopen structure.
 - Q: Can I use this on my Arduino?
 	- A: Yes, this `C` code is 100% pure `C` code and only using `C` standard library and also the code does not take account of what hardware you are using.
 - Q: Do I need to install the library for to use the library?
 	- A: No, just copy over the `.c` and `.h` files to your project and compile. I have used this with QT framework.
 - Q: This project is quite old now and not so much updates, is it still worth to use it?
 	- A: Yes, this library only updates when I or other includes more functionality from Easy CANopen. The reason why I wrote this in `C99` is because it's an industry standard and will you will always be able to compile this library and use it.
 - Q: What is your plan with the library?
 	- A: To make CANopen easy to use
 - Q: I don't have CAN-bus, but can I use this library anyway with UART, USB, WiFi etc?
 	- A: Yes. This is only a way to shape a massage in a specific way.
 - Q: Can I send data with this library, even if I don't have CAN-bus?
 	- A: Yes. There are something called PDO transfer. Use that if you want to transfer data in an industrial way.
 - Q: Can I send multi package messages from from multiple nodes to one node at the same time?
 	- A: No. If you starting to send multipackages from multiple nodes to another node, then that node cannot understand the message. 
# Issues and answers

