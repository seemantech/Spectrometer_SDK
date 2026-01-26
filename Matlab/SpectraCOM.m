clc ;
clear all;
%没有正常关闭串口 使用这行命令

disp('关闭已打开的串口');
fclose(instrfind); %把已经打开的串口关闭，此时再运行代码，就可以成功打开串口了。


s = serial('COM4' , 'BaudRate' , 921600 , 'parity','none','databits',8,'stopbits',1 , 'Terminator','CR');
%串口改成可用的串口 串口改成可用的串口  串口改成可用的串口
s.InputBufferSize=10000;

fopen(s);
disp('打开串口');
% fprintf(s, '*IDN?');
% idn = fscanf(s);  

fwrite(s,48); %向串口发送 0x30 像素个数
temp = fread( s , 2 , 'uchar');%从串口读取2字节数据，2个字节就是 像素个数 08 28
m_nNumPixels = temp(1)  * 256 + temp(2) ; %错误？  插拔一下USB 和 串口
disp(m_nNumPixels); %打印 像素个数


fwrite(s , 64); %读取序列号  0x40 
deviceSN = fscanf(s , '%s', 64); % fscanf从串口s读取字符或字符串(ASCII码)形式数据，以字符数组形式存于deviceSN
disp(deviceSN); %打印 序列号


cmd = '<0.wavelength.read/>';%读波长 0x51 0x1E 0x30       81 30  48     <0.wavelength.read/> 
%fwrite(s , cmd);% 以二进制形式向s写入数据cmd
fprintf( s,cmd); %以字符(ASCII码)形式向串口写数据cmd(字符或字符串)
temp = fread( s , m_nNumPixels * 4 , 'uchar');
m_fWavelength = zeros(1,m_nNumPixels,'single');%定义 10000行  1列的矩阵
for i = 0:1:m_nNumPixels - 1
    % 4个字节 拼成float
    m_fWavelength(i+1) =  typecast(uint8([temp(4*i + 1) temp(4*i +2) temp(4*i +3) temp(4*i +4)]) , 'single');
end
disp(m_fWavelength(1)); %打印出第一个波长

%  cmd = [16 00 00 00 00]; %曝光时间为0  
%cmd = [16 00 00 99 99]; %曝光时间为25.443    十六进制：0x10 00 00 0x63 0x63    十进制：16 00 00 99 99
cmd = [16 00 01 134 160]; %曝光时间为100  十六进制：00 01 86 A0   十进制：00  1  134  160

disp('Ctrl + C 强制中断 while循环');
 while(1) % ctrl + C 中断循环
%for k=0:1:20
    fwrite(s , cmd);
    temp = fread( s , m_nNumPixels * 2 , 'uchar');
    m_nIntensity = zeros(1,m_nNumPixels,'int32');%定义 10000行  1列的矩阵
    for i = 0:1:m_nNumPixels - 1
        m_nIntensity(i+1) = temp(2 * i + 1) + temp(2 * i + 2) * 256 ; 
    end
    
     plot(m_fWavelength,m_nIntensity);
     pause(0.1);%延时1秒
end

disp('结束');
fclose(s);
delete(s);
clear s;

% quit(0,'force');

%     int nExposureTime = fExposureTimeMS * 1000;
%     //串口发送 0x10 00 00 00 00
%     char nCommand[5];//命令共5个字节，第一个字节是标志位 , 后面4个字节代表曝光时间
%     unsigned long nExposureUS = nExposureTime; // 50ms曝光时间 == 50000us曝光时间
%     nCommand[0] = 0x10;  //0x10;COMMAND_READ
%     nCommand[1] = (unsigned char) (nExposureUS >> 24); //曝光时间的最高字节
%     nCommand[2] = (unsigned char) (nExposureUS >> 16);
%     nCommand[3] = (unsigned char) (nExposureUS >> 8);
%     nCommand[4] = (unsigned char) nExposureUS;  //曝光时间的最低位字节
%读强度 0x10 00 00 00 00
