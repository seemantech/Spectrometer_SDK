clc ;
clear all;
%User manually closes the port to make the program run normally

disp('Close already opened ports');
fclose(instrfind); %Close already opened ports, so that the program can successfully open ports now


s = serial('COM4' , 'BaudRate' , 921600 , 'parity','none','databits',8,'stopbits',1 , 'Terminator','CR');
%Change to available port, change to available port, change to available port
s.InputBufferSize=10000;

fopen(s);
disp('Open port');
% fprintf(s, '*IDN?');
% idn = fscanf(s);  

fwrite(s,48); %Send 0x30 to serial port to request pixel count
temp = fread( s , 2 , 'uchar');%Read 2 bytes of data from serial port, 2 bytes represent the response 08 28
m_nNumPixels = temp(1)  * 256 + temp(2) ; %Calculate, one is for USB port
disp(m_nNumPixels); %Print the response pixel count


fwrite(s , 64); %Get device serial number  0x40 
deviceSN = fscanf(s , '%s', 64); %fscanf reads string data (ASCII format) from serial port s, stores in string format as deviceSN
disp(deviceSN); %Print device serial number


cmd = '<0.wavelength.read/>';%Request wavelength 0x51 0x1E 0x30       81 30  48     <0.wavelength.read/> 
%fwrite(s , cmd);%Write binary data cmd to serial port s in binary format
fprintf( s,cmd); %Write character string cmd to serial port in character string (ASCII format)
temp = fread( s , m_nNumPixels * 4 , 'uchar');
m_fWavelength = zeros(1,m_nNumPixels,'single');%Create 10000 elements, 1-row matrix
for i = 0:1:m_nNumPixels - 1
    % 4 bytes combined into float
    m_fWavelength(i+1) =  typecast(uint8([temp(4*i + 1) temp(4*i +2) temp(4*i +3) temp(4*i +4)]) , 'single');
end
disp(m_fWavelength(1)); %Print the first wavelength

%cmd = [16 00 00 00 00]; %Exposure time is 0  
%cmd = [16 00 00 99 99]; %Exposure time is 25.443    hexadecimal: 0x10 00 00 0x63 0x63    decimal: 16 00 00 99 99
cmd = [16 00 01 134 160]; %Exposure time is 100  hexadecimal: 00 01 86 A0   decimal: 00  1  134  160

disp('Ctrl + C forcibly interrupt while loop');
 while(1) % ctrl + C interrupt loop
%for k=0:1:20
    fwrite(s , cmd);
    temp = fread( s , m_nNumPixels * 2 , 'uchar');
    m_nIntensity = zeros(1,m_nNumPixels,'int32');%Create 10000 elements, 1-row matrix
    for i = 0:1:m_nNumPixels - 1
        m_nIntensity(i+1) = temp(2 * i + 1) + temp(2 * i + 2) * 256 ; 
    end
    
     plot(m_fWavelength,m_nIntensity);
     pause(0.1);%Delay 1 second
end

disp('End');
fclose(s);
delete(s);
clear s;

% quit(0,'force');

%     int nExposureTime = fExposureTimeMS * 1000;
%     //Send 0x10 00 00 00 00
%     char nCommand[5];//Command has 5 bytes total, first byte is flag bit, last 4 bytes contain exposure time
%     unsigned long nExposureUS = nExposureTime; // 50ms exposure time == 50000us exposure time
%     nCommand[0] = 0x10;  //0x10;COMMAND_READ
%     nCommand[1] = (unsigned char) (nExposureUS >> 24); //Exposure time highest byte
%     nCommand[2] = (unsigned char) (nExposureUS >> 16);
%     nCommand[3] = (unsigned char) (nExposureUS >> 8);
%     nCommand[4] = (unsigned char) nExposureUS;  //Exposure time lowest byte
%We force 0x10 00 00 00 00
