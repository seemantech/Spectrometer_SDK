#ifndef _SPECTROMETER_H_
#define _SPECTROMETER_H_

#define u8  unsigned char  
#define u16 unsigned short 
#define s32 int	
#define u32 unsigned int		  

#define PIXELS 3694

#define READ_MODE_PIXEL_NUM  1
#define READ_MODE_WAVELENGTH 2
#define READ_MODE_INTENSITY  3
#define READ_MODE_INTENSITY_SECTION 4
#define READ_MODE_SET_XE_FREQUENCY  5
#define READ_MODE_SERIAL_NUMBER		6

typedef struct  _t_spectrometer_command_
{
	u32 nCMDMode;

	u8  nBuffer[PIXELS * 2];
	u32 nBytesToReceive;
	u32 nBytesReaded;

	u8  nCommand[64];
	u32 nBytesToSend;
}T_SPECTROMETER_COMMAND;

typedef struct  _t_spectrometer_
{
	float fWavelength[PIXELS];
	u16 nIntensity[PIXELS];
	u32 nPixelNum;
	float fExposureTimeMS;
	u32 nPixelBeg;
	u32 nPixelEnd;
	char strSN[64];

	T_SPECTROMETER_COMMAND cmd;
}T_SPECTROMETER;

extern T_SPECTROMETER g_tSP;

void SpectrometerInit(T_SPECTROMETER *sp);

u32  ReadWavelengthReady(T_SPECTROMETER *sp);
u32  ReadWavelengthParse(T_SPECTROMETER *sp);

u32  ReadIntensityReady(T_SPECTROMETER *sp);
u32  ReadIntensityParse(T_SPECTROMETER *sp);

u32  ReadPixelNumReady(T_SPECTROMETER *sp);
u32  ReadPixelNumParse(T_SPECTROMETER *sp);

u32  ReadSerialNumberReady(T_SPECTROMETER *sp);
u32  ReadSerialNumberParse(T_SPECTROMETER *sp);

u32 ReadIntensitySectionReady(T_SPECTROMETER *sp,float fWavelengthBeg,float fWavelengthEnd);//must call this function after ReadWavelength(),otherwise an error will occur.
u32 ReadIntensitySectionParse(T_SPECTROMETER *sp);

u32 SetXeFrequency(T_SPECTROMETER *sp,float fHz);


u32  WavelengthToPixel(T_SPECTROMETER *sp,float fWavelength);
float GetIntensityAtWavelength(T_SPECTROMETER *sp,float fWavelength);


#endif