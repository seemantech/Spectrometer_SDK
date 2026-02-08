#Python 3.7.4
import serial#pip install pyserial
import serial.tools.list_ports
from array import array
import struct
import time
from tkinter import *
import threading
#import matplotlib.pyplot as plt


ser=serial.Serial("COM8",921600,timeout=0.5)#Windows system uses COM3 port to connect to serial port【Please modify according to the actual COM port of the device】
# ser=serial.Serial("/dev/ttyAMA0",921600,timeout=0.5) #Linux system uses Raspberry Pi GPIO port to connect to serial port
# ser=serial.Serial("/dev/ttyS1",921600,timeout=0.5)#Linux system uses com1 port to connect to serial port
#ser = serial.Serial("/dev/ttyACM0", 115200, timeout=3)#Please select the corresponding serial port for this machine

if( ser.isOpen()):
    print('Open Spectrometer Success!')
else:
    print('Open Spectrometer Failed!')

#1 Read Intensity with integration time user defined
#The following is the spectrometer reading parameter configuration section
fMS = float(10) # 10ms Integration Time in ms.
waveBeg = 200 #Starting wavelength nm
waveEnd = 1050 #Ending wavelength nm
waveInt = 0.5 #Wavelength interval nm, recommended to use 1nm, 0.5nm, 0.25nm, 0.2nm
count = int((waveEnd - waveBeg) / waveInt) + 1
print(count)
nIntensity = array('H',[0] * count)# H = u16
cbPayload = count * 2 + 64 # Data + spectrometer sampling parameters (64 Bytes)
fWavelength = array('f',[0] * count)  # f = float f32
for i in range(count):  
    fWavelength[i] = waveBeg + waveInt * i #Wavelength initialization

strSN = "SN"

#The following is the spectrometer data reading section
def ReadIntensity():
    m = 1
    strCMD = "{data.read64(%.3f,%d,%d,%.3f)}" % (fMS, waveBeg, waveEnd , waveInt)
    
    rtn = ser.write(strCMD.encode('utf-8'))
    if( rtn < 5):
        print("Read Intensity Failed. #1")
        return
    try:
        buffer = ser.read(cbPayload)
        if( len(buffer) != cbPayload):
            print("Read Intensity Failed. #2")
            return 0
        for i in range(count):
            nIntensity[i] = buffer[i * 2] * 256 + buffer[i * 2 + 1] # MSB + LSB
        SN = ()
        for i in range(16):
            if( buffer[count*2 + i] == 0x00):
                break
            SN += struct.unpack('b',buffer[count*2 + i : count*2 +i+1])#Cannot use 'c' type
        ls2 = [chr(i) for i in SN] # chr(97) displays as a  while str(97) displays as 97
        global strSN
        strSN = "S/N: " + ''.join(ls2)


    except:
        ser.close()
        print("Device Reset!")


#The following is the interface display section
root = Tk()
root.title("Spectrometer")

#Set window size
width  = 1300 
height = 800

#Set whether the window is resizable in length and width, True: resizable, False: not resizable
root.geometry('%dx%d' % (width,height)) 
screenwidth = root.winfo_screenwidth()
screenheight = root.winfo_screenheight()
alignstr = '%dx%d+%d+%d' % (width, height, (screenwidth-width)/2, (screenheight-height)/2)
root.geometry(alignstr)
root.resizable(width=True, height=True)

# Create and add Canvas
cv = Canvas(root, background='white')
cv.pack(fill=BOTH, expand=YES)

flagRunning = threading.Event()

#Drawing Canvas
def Draw(nLoops):
    cv.delete(ALL)# Delete Previous drawings
    cv.create_text(500, 20, text=strSN)
    cv.create_text(700, 20, text= "Loops: " + str(nLoops),fill='red',font=('Times',15))

    LeftX = 100  #Left position of Graph Rectangle (Screen Pixel)
    RightX= 1200 #Right position of Graph Rectangle 
    TopY = 50    #Top position of Graph Rectangle
    BottomY = height - 50 #Bottom position of Graph Rectangle
    ratioY = 600 / 60000  # Ratio: screen pixel to intensity counts

    #Draw Spectrum Red Line
    pt = []
    pt.append(fWavelength[0])
    pt.append(BottomY)
    for i in range(count):
        pt.append(fWavelength[i])
        pt.append(BottomY - nIntensity[i] * ratioY )

    pt.append(fWavelength[count - 1])
    pt.append(BottomY)
    cv.create_polygon(pt,outline="red",fill='white') 

    # Draw Coordinate XY
    cv.create_text(width / 2 - 5, height - 15, text='Wavelength(nm)')
    cv.create_text(LeftX - 10,30, text='Intensity(counts)')
    cv.create_line(LeftX, BottomY,RightX, BottomY,fill='black') # Coordinate X
    cv.create_line(LeftX, BottomY,LeftX, TopY,fill='black') # Coordinate Y

    # Coordinate Y dash line
    for i in range(1,7):
        posY = BottomY - i * 100
        cv.create_line(LeftX-5, posY,LeftX,posY,fill='black') # Coordinate Y
        cv.create_text(LeftX-25,posY, text='%d' % (i * 100 / ratioY))
        cv.create_line(LeftX,posY,RightX,posY,fill='black',dash=(4,4)) 

    # Coordinate X dash line
    for i in range(1,11):
        posX = LeftX + i * 100
        cv.create_line(posX,BottomY,posX,BottomY+5,fill='black') # Coordinate X
        cv.create_text(posX,BottomY + 15, text='%d' % (posX))
        cv.create_line(posX,BottomY,posX,TopY,fill='black',dash=(4,4))

def ThreadSpectrometer():
    nLoops = 0
    while(flagRunning.is_set()):#while(flagRunning.isSet()):
        time.sleep(0.1)
        ReadIntensity()
        nLoops += 1
        #Draw(nLoops)
        cv.after(100, Draw,nLoops)
        
    print("Exit Spectrometer Thread")

ThreadSP = threading.Thread(target=ThreadSpectrometer)
ThreadSP.daemon = True#If the daemon attribute is False, the data reading child thread will not end when the main thread ends
flagRunning.set()
ThreadSP.start()

def on_closing():
    flagRunning.clear()
    time.sleep(fMS / 1000.0)
    root.destroy()

root.protocol("WM_DELETE_WINDOW", on_closing)
root.mainloop()
