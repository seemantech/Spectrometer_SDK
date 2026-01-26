#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <iconv.h>
#include <string>
#include <iostream>
#include "Spectrometer.h"

int open_port(int com_port);
int set_uart_config(int fd, int baud_rate, int data_bits, char parity, int stop_bits);
 

int open_port(int com_port)
{
    int fd;
    // TODO:: Add list of Comport 
    char* dev[] = { "/dev/ttyACM0", "/dev/ttyUSB0" };
 
    //O_NDELAY == O_NONBLOCK。
    fd = open(dev[com_port], O_RDWR | O_NOCTTY);
    if (fd < 0)
    {
        perror("open serial port");
        return(-1);
    }
 
    //恢复串口为阻塞状态 
    //非阻塞：fcntl(fd,F_SETFL,FNDELAY)  
    //阻塞：fcntl(fd,F_SETFL,0) 
    if (fcntl(fd, F_SETFL, 0) < 0)
    {
        perror("fcntl F_SETFL\n");
    }
    //测试是否为终端设备
    if (isatty(STDIN_FILENO) == 0)
    {
        perror("standard input is not a terminal device");
    }
 
    return fd;
}


int set_uart_config(int fd, int baud_rate, int data_bits, char parity, int stop_bits)
{
    struct termios opt;
    int speed;
    if (tcgetattr(fd, &opt) != 0)
    {
        perror("tcgetattr");
        return -1;
    }
 
    //Set Baudrate
    switch (baud_rate)
    {
    case 2400:  speed = B2400;  break;
    case 4800:  speed = B4800;  break;
    case 9600:  speed = B9600;  break;
    case 19200: speed = B19200; break;
    case 38400: speed = B38400; break;
    case 921600: speed = B921600; break;
    default:    speed = B115200; break;
    }
    cfsetispeed(&opt, speed);
    cfsetospeed(&opt, speed);
    tcsetattr(fd, TCSANOW, &opt);
 
    opt.c_cflag &= ~CSIZE;
 
    //Set DataBits
    switch (data_bits)
    {
    case 7: {opt.c_cflag |= CS7; }break;//7个数据位  
    default: {opt.c_cflag |= CS8; }break;//8个数据位 
    }
 
    //Set Parity
    switch (parity) //N
    {
    case 'n':case 'N':
    {
        opt.c_cflag &= ~PARENB;//校验位使能     
        opt.c_iflag &= ~INPCK; //奇偶校验使能  
    }break;
    case 'o':case 'O':
    {
        opt.c_cflag |= (PARODD | PARENB);//PARODD使用奇校验而不使用偶校验 
        opt.c_iflag |= INPCK;
    }break;
    case 'e':case 'E':
    {
        opt.c_cflag |= PARENB;
        opt.c_cflag &= ~PARODD;
        opt.c_iflag |= INPCK;
    }break;
    case 's':case 'S': //as no parity
    {
        opt.c_cflag &= ~PARENB;
        opt.c_cflag &= ~CSTOPB;
    }break;
    default:
    {
        opt.c_cflag &= ~PARENB;//校验位使能     
        opt.c_iflag &= ~INPCK; //奇偶校验使能          	
    }break;
    }
 
    //Set StopBits
    switch (stop_bits)
    {
    case 1: {opt.c_cflag &= ~CSTOPB; } break;
    case 2: {opt.c_cflag |= CSTOPB; }   break;
    default: {opt.c_cflag &= ~CSTOPB; } break;
    }
 
    /*处理未接收字符*/
    tcflush(fd, TCIFLUSH);
 
    //Set TIME_OUT
    opt.c_cc[VTIME] = 1000;//TIME_OUT
    opt.c_cc[VMIN] = 0;
 
    /*关闭串口回显*/
    opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | NOFLSH);
 
    /*禁止将输入中的回车翻译为新行 (除非设置了 IGNCR)*/
    opt.c_iflag &= ~ICRNL;
    /*禁止将所有接收的字符裁减为7比特*/
    opt.c_iflag &= ~ISTRIP;
 
    //Actviate New Attributes
    if ((tcsetattr(fd, TCSANOW, &opt)) != 0)
    {
        perror("tcsetattr");
        return -1;
    }
 
    return 0;
}

int UART_fd = 0;

unsigned int  send(u8* pData,u32 nLens,u32 nTimeout)
{
	return write(UART_fd, pData, nLens);	
	//return 0;//Error
}

unsigned int read(u8* pData,u32 nLens,u32 nTimeout)
{
	int cbReaded = 0;
    
	while (1)
	{
        int nByteReaded = read(UART_fd, pData, nLens - cbReaded);
		
        if( nByteReaded > 0)
        {
			pData += nByteReaded;
            cbReaded += nByteReaded;
		}

        if( cbReaded >= nLens)
            return cbReaded;//return the total bytes readed

        //if time out, return 0;
	}
}


int main()
{
    // begin:: initializing the comport
    UART_fd = open_port(0);
	if (set_uart_config(UART_fd, 115200, 8, 'N', 1) < 0)
	{
		perror("set_com_config");
		exit(1);
	}
    // end::initializing the comport
    
    //int PIXELS = 2088;//S5000 

    u32 i;
	SpectrometerInit(&g_tSP);

	//Read PixelNum
	ReadPixelNumReady(&g_tSP);
	send(g_tSP.cmd.nCommand,g_tSP.cmd.nBytesToSend,WRITE_TIMEOUT_MS);
	read(g_tSP.cmd.nBuffer ,g_tSP.cmd.nBytesToReceive,READ_TIMEOUT_MS);
	ReadPixelNumParse(&g_tSP);

	//Read Wavelength
	ReadWavelengthReady(&g_tSP);
	send(g_tSP.cmd.nCommand,g_tSP.cmd.nBytesToSend,WRITE_TIMEOUT_MS);
	read(g_tSP.cmd.nBuffer ,g_tSP.cmd.nBytesToReceive,READ_TIMEOUT_MS);
	ReadWavelengthParse(&g_tSP);

	printf(" Wavelength begin at: %.0f nm \r\n",GetIntensityAtWavelength(&g_tSP,400.0f) );
	while(1)
	{
		//ReadIntensity
		g_tSP.fExposureTimeMS = 100.0f;
		ReadIntensityReady(&g_tSP);
		send(g_tSP.cmd.nCommand,g_tSP.cmd.nBytesToSend,WRITE_TIMEOUT_MS);
		read(g_tSP.cmd.nBuffer ,g_tSP.cmd.nBytesToReceive,(s32)(READ_TIMEOUT_MS + g_tSP.fExposureTimeMS * 1.5f) );
		ReadIntensityParse(&g_tSP);

		for( i = 0 ; i < g_tSP.nPixelNum ; i++)
		{
			float fWavelength = g_tSP.fWavelength[i];
			u16 fIntensity    = g_tSP.nIntensity[i];
		}
		printf("Intensity At Wavelength 400nm is: %.0f \r\n",GetIntensityAtWavelength(&g_tSP,400.0f) );
		
		//ReadIntensitySection such as from 300nm to 400nm
//		g_tSP.fExposureTimeMS = 20.0f;
// 		ReadIntensitySectionReady(&g_tSP,300.0f,400.0f);	
// 		send(g_tSP.cmd.nCommand,g_tSP.cmd.nBytesToSend);
// 		read(g_tSP.cmd.nBuffer ,g_tSP.cmd.nBytesToReceive);
// 		ReadIntensitySectionParse(&g_tSP);
// 
//  	float fIntensityAt350nm = GetIntensityAtWavelength(&g_tSP,350.0f);
// 		printf("Intensity At Wavelength 350nm is: %.0f \r\n",fIntensityAt350nm );
	}

    //printf("content:%s\n",str);
    
    return 0;
}
//https://blog.csdn.net/qq_25662827/article/details/122581819

 

