# ITI Graduation Project 
# Firmware Over The Air (FOTA)
## INTRODUCTION
Firmware Over-The-Air (FOTA) is a project aimed at enabling remote updates of
firmware on embedded devices. It provides a mechanism to deploy software patches,
and feature enhancements to devices in the field without requiring physical access.
FOTA simplifies the process of keeping devices up to date, improving functionality,
security, and reliability. By leveraging wireless communication channels, FOTA
minimizes downtime and reduces the need for manual interventions, making it a
valuable tool for managing firmware across many distributed devices.


## Project Diagram

![1](https://github.com/Mina267/GP_4M_SV2_Intake3_FOTA_18/assets/71601701/2e2e26c0-6bb6-4586-b6e7-e61cf3ace267)

![2](https://github.com/Mina267/GP_4M_SV2_Intake3_FOTA_18/assets/71601701/15791888-de52-4459-8e02-5c2150e7cf07)
### BOOTLOADER APPLICATION
A bootloader is a small program residing in the microcontroller that enables the
firmware update process. It is responsible for receiving the new software image and
writing it to the microcontroller's memory.

The bootloader is the first piece of software that runs when the microcontroller is
powered up or reset. One of the key functions of a bootloader is to facilitate the
firmware update process. It provides mechanisms for transferring new firmware images
from an external source.

#### Bootloader Development
I. Develop or obtain a bootloader that can handle the swapping of firmware between memory banks. The bootloader should have the capability to select the active memory bank at boot time and facilitate the firmware update process.

II. Implement a fail-safe mechanism in the bootloader to handle situations where the newly updated firmware fails to work correctly. This may involve reverting
#### Bootloader Operation
I. The bootloader checks the currently active memory bank and determines which version of the firmware is running.

II. During the boot process, the bootloader verifies the integrity of both firmware versions and selects the appropriate version to execute.


<p align="center">
	<img src="https://github.com/Mina267/GP_4M_SV2_Intake3_FOTA_18/assets/71601701/a8494035-72d8-4908-992a-378ccab474f2" width="450" height="600" />
</p>


## UDS standard
UDS (Unified Diagnostic Services) is a protocol commonly used in the automotive
industry for communication between a tester or diagnostic tool and an electronic control
unit (ECU) in a vehicle. While UDS is primarily used for diagnostics, it can also be
used for firmware updates or flashing new software to microcontrollers or ECUs.

Connect the Raspberry Pi (Main ECU) to the STM32F401 ARM microcontroller using
a suitable communication interface, such as UART (or any other communication).
Ensure that both devices are powered and properly configured. Transfer the firmware
Using the UDS protocol, send the firmware image from the Raspberry Pi (Main ECU)
to the STM32F401 ARM microcontroller. The bootloader on the microcontroller
receives the image and writes it to the appropriate memory location.

Using two banks for an application typically refers to a technique used in
microcontrollers with dual or multiple memory banks. This technique allows you to
store and execute two different versions of firmware or software in separate memory
banks, providing benefits such as redundancy, flexibility, and easier firmware updates.
After the firmware transfer is complete, send verification (CRC) to ensure the integrity
of the transferred data. Once verified, exit the bootloader mode, and reset the
microcontroller to start running the new firmware. When performing the process of
flashing a new update using UDS, you will require various UDS services.

    1- Diagnostic Session Control   (SID: 0x10)
        - Default Session           (SF: 0x01)
        - Programming Session       (SF: 0x02)
        - Extended Session          (SF: 0x03)

    2- ECU Reset                    (SID: 0x11)
        - software Reset            (SF: 0x03)
    
    3- Security Access              (SID: 0x27)
        - Request Seed              (SF: 0x01)
        - Send key                  (SF: 0x02)

    4- Routine Control              (SID: 0x31)
        - Start Routine             (SF: 0x01)
        - Erase Routine             (DID: 0xFF00)
        - CRC check Routine         (DID: 0x0202) 

    5- Request Download             (SID: 0x34)
    6- Data Transmission            (SID: 0x36)
    7- Request Transfer Exit        (SID: 0x37)



<p align="center">
	<img src="https://github.com/Mina267/GP_4M_SV2_Intake3_FOTA_18/assets/71601701/765cbe58-2e5b-47c0-965d-6ea425495b96" width="450" height="400" />
</p>

## Positive and Negative responses

Transmit to the main ECU suitable Positive and Negative responses.

#### NRC enum

```http
/* Negative Response NRC */
typedef enum
{
	GENERAL_REJECT = 0x10,
	SERVICE_NOT_SUPPORTED = 0x11,
	SF_NOT_SUPPORTED = 0x12,
	INVALID_MESSAGE_LENGTH_OR_FORMAT = 0x13,
	FAILURE_PREVENTS_EXECUTION_OF_REQUESTED_ACTION = 0x26,
	REQUEST_OUT_OF_RANGE = 0x31,
	SECURITY_ACCESS_DENIED = 0x33,
	INVALID_KEY = 0x35,
	EXCEEDED_NUMBER_OF_ATTEMPTS = 0x36,
	UPLOAD_DOWNLOAD_NOT_ACCEPTED = 0x70,
	PROGRAMMING_FAILURE = 0x72,
	SF_NOT_SUPPORTED_IN_ACTIVE_SESSION = 0x7E,
	SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION = 0x7F

}UDS_NRC_t;

```

## communication services

#### Basic communication module

That provides total abstraction between Application and hardware ‎
By providing two communication Queues for Transmitting and receiving using ‎interrupts

<p align="center">
	<img src="https://github.com/Mina267/Parallel-AutoParking/assets/71601701/ec5f18e7-1eb7-4d92-be66-fd557f346636" width="500" height="400" />
</p>


## FEE
By introducing a simple FEE (Flash EEPROM Emulator) structure, developers and administrators can ensure the secure storage and retrieval of flags during the FOTA process. These flags, which represent specific settings or configurations within the firmware, play a crucial role in determining the behavior and functionality of the device or software being updated.

In our FOTA project we created a simple FEE driver mainly to store flags in two bytes of data in sector one in flash memory, this driver supports three main functions for read and write and the Init function in case of reset to restore the last data stored.

![frame](https://github.com/Mina267/Parallel-AutoParking/assets/71601701/f5dcb585-cb4f-4c1a-aa27-9a172ea81b09)



## RASPBERRY PI
On the Raspberry Pi, after enabling the UART protocol to communicate with STM, three main Python code files are used:
### Server.py
The server code acts as a bridge between the Raspberry Pi and the mobile app, listening for user actions. It creates a server socket and waits for incoming connections from the mobile app. Once a connection is established, it receives user commands or actions, such as requesting an update or checking. Based on the received action, the server code initiates the corresponding subprocess whether it is update or checking for updates.
### Check_For_Update.py
The check for update code is responsible for checking for available firmware updates. It connects to the OEM server repository and retrieves information about the latest firmware version. Using this information, it compares the current firmware version of the Raspberry Pi and determines if an update is available or not.
### Update.py
The update code fetches the update file from the OEM server and then decrypts it, after that initiate UART protocol communicates with STM to initiate the update process by extracting information from the update file and sending it to STM and waiting for a response to continue in this process until last line in update file.

## MOBILE APPLICATION
The mobile application will serve as an intuitive friendly GUI, allowing users to easily check for updates and choose between updating and not updating. This will simplify the updating process and ensure that users get the latest features and improvements easily. Actions taken by the user send an indication to the server which chooses the suitable response according to the user's action.

<p align="center">
	<img src="https://github.com/Mina267/GP_4M_SV2_Intake3_FOTA_18/blob/main/Images/Picture1.jpg" width="450" height="500" />
</p>

## OEM SERVER
### Firebase
The OEM Firebase platform serves as an innovative and reliable foundation for seamlessly managing software updates in various applications, including automotive systems. Leveraging the platform, developers can effortlessly create projects that facilitate the uploading of updated text files from any location. This versatility ensures that updates can be deployed conveniently, enhancing the overall efficiency of the update process. By employing a Raspberry Pi along with Python code, the platform enables the retrieval of these updated files. The integration of the UART protocol ensures effective communication between the Raspberry Pi and the STM32F401CC ARM microcontroller, specifically designed for automotive applications. This streamlined approach empowers the efficient dissemination of updated application code to the car's microcontroller, enabling swift and secure software updates for enhanced functionality and performance.
### GUI
We created a web page to choose and upload the file that we want to be downloaded on Raspberry Pi to be flashed on STM. This page was designed with HTML, CSS, and JavaScript. It consists of two buttons, one to choose a file from a local device and another button to upload the chosen file on the Firebase storage section. The code of this page includes a part for Firebase. This part links the web page to Firebase and it is necessary to write configurations of the Firebase project in HTML code but between script tags.

<p align="center">
	<img src="https://github.com/Mina267/GP_4M_SV2_Intake3_FOTA_18/blob/main/Images/Picture2.png" width="450" height="500" />
</p>
## APPLICATION using FreeRTOS

Using API's



### RGB application

Using Three PWM to provide various color ranges.

Hasing two modes Set color and ShowRoom mode.

<p align="center">
	<img src="https://github.com/Mina267/GP_4M_SV2_Intake3_FOTA_18/blob/main/Images/RGB1.png" width="450" height="500" />
</p>

### Obstacle Avoidance

The Avoid Obstacle application incorporates a showroom RGB LED and leverages 
FreeRTOS for effective task management. FreeRTOS allows for concurrent execution 
of multiple tasks, optimizing the utilization of system resources. The application 
focuses on obstacle detection and avoidance, ensuring a safe and efficient navigation 
experience

Avoid Obstacle by using one UltraSonic Sensor and four IR sensors and speed control using PWM.‎

### Bluetooth Control
The Bluetooth robotic car application with an RGB LED and utilizes FreeRTOS for 
efficient task management. FreeRTOS enables concurrent execution of multiple tasks, 
optimizing resource utilization. The application allows users to control the car's 
movement wirelessly through Bluetooth communication. FreeRTOS manages tasks 
such as Bluetooth communication, motor control, and RGB LED control. and speed control using PWM.‎

