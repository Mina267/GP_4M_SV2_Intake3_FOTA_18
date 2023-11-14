import serial
import os

#UDS Commands
Extended         = "02 10 03"      		#                                                          +ve response --> 02 50 03
Programming      = "02 10 02"       		#                                                          +ve response --> FE 02 50 02
Request_seed     = "02 27 01"       		#                                                          +ve response --> 07 67 01 xx xx xx xx xx
Send_Key         = "06 27 02 00 00 00 FF"       #+4 bytes (sum of 5 bytes of seed),           		   +ve response --> 02 67 02
Erase_Sector     = "05 31 01 FF 00 0" 		#+1 byte for sector number,                                +ve response --> 04 71 01 FF 00
Request_Download = "09 34"          		#+4 bytes for flashing address and +4 bytes for data size, +ve response --> 02 74 08
Flashing_Exit    = "01 37"          		#                                                          +ve response --> 01 77 
Reset            = "02 11 03"       		#                                                          +ve response --> FE 02 41 03

check_path = 'Check.txt'
if os.path.exists(check_path):
    #Run UART
    port = serial.Serial('/dev/ttyS0',9600)
    
    #Check Update exist or not
    path = 'update.txt'
    if os.path.exists(path):
        lines = open('update.txt')
        lines= [line.rstrip() for line in lines]
    else:
        print("No Updates Found")
        exit()
    
    #
    
    #Session control --> Extended
    port.write(bytearray.fromhex(Extended))
    print("start")
    print((port.read(3)).hex())
    #Session control --> Programming
    port.write(bytearray.fromhex(Programming))
    print((port.read(4)).hex())
    
    #Session control(Security) --> Request seed
    port.write(bytearray.fromhex(Request_seed))
    print((port.read(8)).hex())
    
    
    #Session control --> Send Key
    port.write(bytearray.fromhex(Send_Key))
    print((port.read(3)).hex())
    
    #Erase Sector
    main_Add = f"{lines[1][9:13]}"
    print(main_Add)
    if main_Add == '0801':
        Sector_Num = 4
    elif main_Add == '0802':
        Sector_Num = 5
    Erase_Sector += f"{Sector_Num}"
    port.write(bytearray.fromhex(Erase_Sector))
    print((port.read(5)).hex())
    
    ##Flashing --> Request download
    #Address for flash
    Request_Download += f" {lines[1][9:11]} {lines[1][11:13]} {lines[2][3:5]} {lines[2][5:7]}"
    #Data size
    Data_size = str(hex((len(lines)-4)*16))
    
    if (len(Data_size)-2) == 4:
        Request_Download += f" 00 00 {Data_size[2:4]} {Data_size[4:6]}"
        port.write(bytearray.fromhex(Request_Download))
    elif (len(Data_size)-2) == 5:
        Request_Download += f" 00 0{Data_size[2]} {Data_size[3:5]} {Data_size[5:7]}"
        port.write(bytearray.fromhex(Request_Download))
    print((port.read(3)).hex())
    
    
    #Flashing --> Transfer data
    for i in range(2,len(lines)-3):
    #for i in range(2,4):
        Data_long = int(len(lines[i])-11)
        if Data_long < 26:
            temp = hex(int(lines[i][1:3],16)+3)           
            Data_send = f"0{temp[2]} 36 {lines[i][3:5]} {lines[i][5:7]} "
        else:
            temp = hex(int(lines[i][1:3],16)+3)
            Data_send = f"{temp[2:4]} 36 {lines[i][3:5]} {lines[i][5:7]} "
        for j in range(0,Data_long,2):
            Data_send += f"{lines[i][j+9:j+11]} "
        print(Data_send)
        port.write(bytearray.fromhex(Data_send))
        print((port.read(4)).hex())
    #Flashing --> Exit
    port.write(bytearray.fromhex(Flashing_Exit))
    print((port.read(2)).hex())
    #extra for reset and jump
    port.write(bytearray.fromhex(Reset))
    #print((port.read(4)).hex())
    
    #Erase Check.txt --> which indicates if update not complete
    os.remove("Check.txt")
else:
    exit(0)
