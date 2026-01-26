#include "Spectrometer.h"
#include "math.h"
#include "string.h" //strlen()
#include "stdio.h"//sprintf()

T_SPECTROMETER g_tSP;

void SpectrometerInit(T_SPECTROMETER *sp)
{
	u32 i;
	sp->fExposureTimeMS = 100.0f;
	sp->nPixelNum = PIXELS;

	sp->nPixelBeg = 0;
	sp->nPixelEnd = PIXELS - 1;

	for( i = 0 ; i < sp->nPixelNum ; i++)
	{
		sp->fWavelength[i] = (float)i;
	}

	//sp->cmd.nCMDMode = 0;
}

u32 isBigEndian(void)
{
	//0x12345678
	//big-endian     0x12 0x34 0x56 0x78
	//little-endian  0x78 0x56 0x34 0x12
	int  data = 0x1234;
	char bFirst=*(char*)&data;
	if( 0x12 == bFirst)
		return 1; //printf("big-endian\n");
	else
		return 0; //printf("little-endian\n");
}

u32 ReadPixelNumReady(T_SPECTROMETER *sp)
{
	sp->cmd.nCommand[0]  = 0x30;  //COMMAND_INFO_READ;
	sp->cmd.nBytesToSend = 1;
	
	sp->cmd.nBytesToReceive = 2;
	sp->cmd.nBytesReaded = 0;
	sp->cmd.nCMDMode = READ_MODE_PIXEL_NUM;
	return 1;
}

u32 ReadPixelNumParse(T_SPECTROMETER *sp)
{
    sp->nPixelNum  = ((u32)(sp->cmd.nBuffer[0])) * 256 + sp->cmd.nBuffer[1];
    return 1;
}

u32 ReadWavelengthReady(T_SPECTROMETER *sp)
{
	sp->cmd.nCommand[0] = 0x51;  //COMMAND_INFO_READ;
	sp->cmd.nCommand[1] = 30;	//PAGE  
	sp->cmd.nCommand[2] = 6*8;	//
	sp->cmd.nBytesToSend = 3;

	sp->cmd.nBytesToReceive = 64;
	sp->cmd.nBytesReaded = 0;
	sp->cmd.nCMDMode = READ_MODE_WAVELENGTH;
	return 1;
}

u32 ReadWavelengthParse(T_SPECTROMETER *sp)
{
	u8 *pData;
	u32 i,j;
	u8 *pBuffer = sp->cmd.nBuffer;
	double dCoeff[6];
	for( i = 0 ; i < 6 ; i++)
	{
		pData = (u8 *) (&dCoeff[i]);
		
		if( isBigEndian() )
		{
			for(  j = 0 ; j < 8 ; j++)
			{
				pData[j] = pBuffer[ i*8 + 7 - j];//big-endian
			}
		}
		else
		{
			for(  j = 0 ; j < 8 ; j++)
			{
				pData[j] = pBuffer[ i*8 + j]; //little-endian
			}
		}
	}
	
	//unusual
	if(dCoeff[0]  > 2000 || dCoeff[0] < -1000 || dCoeff[0] != dCoeff[0] )
	{
		for( i = 0 ; i < sp->nPixelNum ; i++)
		{
			sp->fWavelength[i] = (float)i;
		}
		return 0;
	}
	
	for( i = 0 ; i < sp->nPixelNum ; i++)
	{
		sp->fWavelength[i] = (float)(
			dCoeff[0]
			+dCoeff[1]*pow(i,1)
			+dCoeff[2]*pow(i,2)
			+dCoeff[3]*pow(i,3)
			+dCoeff[4]*pow(i,4)
			+dCoeff[5]*pow(i,5));
	}
	
	return 1;
}


u32 ReadIntensityReady(T_SPECTROMETER *sp)
{
    u32 nExposureUS = (u32)(sp->fExposureTimeMS * 1000.0f); // integration time 50ms  == 50000us

    //Send = 0x10 00 00 00 00
    //Read Command = 5 Bytes = 1 Byte(Flag) + 4 Bytes(integration time)
    sp->cmd.nCommand[0] = 0x10;  //0x10;COMMAND_READ
    sp->cmd.nCommand[1] = (u8) (nExposureUS >> 24); //MSB
    sp->cmd.nCommand[2] = (u8) (nExposureUS >> 16);
    sp->cmd.nCommand[3] = (u8) (nExposureUS >> 8);
    sp->cmd.nCommand[4] = (u8) nExposureUS;  //LSB 
	sp->cmd.nBytesToSend = 5;

	sp->cmd.nBytesToReceive = sp->nPixelNum * 2;
	sp->cmd.nBytesReaded = 0;
	sp->cmd.nCMDMode = READ_MODE_INTENSITY;

	return 1;
}

u32 ReadIntensityParse(T_SPECTROMETER *sp)
{
	u32 i;
	u8 * pBuffer = sp->cmd.nBuffer;

	for( i = 0 ; i < sp->nPixelNum ; i++)
	{
		sp->nIntensity[i] = pBuffer[2*i] + ((u32)pBuffer[2*i+1]) * 256;
	}
	return 1;
}

u32 ReadIntensitySectionReady(T_SPECTROMETER *sp,float fWavelengthBeg,float fWavelengthEnd)
{
	char *pCommand = (char*)sp->cmd.nCommand;
    u32 nExposureUS = (u32)(sp->fExposureTimeMS * 1000.0f); // integration time 50ms  == 50000us
	u32 nPixelBeg = WavelengthToPixel(sp,fWavelengthBeg);
	u32 nPixelEnd = WavelengthToPixel(sp,fWavelengthEnd);

	u32 nPixelLens= nPixelEnd - nPixelBeg + 1;

	sp->nPixelBeg = nPixelBeg;
	sp->nPixelEnd = nPixelEnd;

	sprintf(pCommand,"<0.intensity.readsection v='%.3f' beg='%d' end='%d'/>",sp->fExposureTimeMS,nPixelBeg,nPixelEnd);

	sp->cmd.nBytesToSend = strlen(pCommand);
	
	sp->cmd.nBytesToReceive =  nPixelLens  * 2; 
	sp->cmd.nBytesReaded = 0;
	sp->cmd.nCMDMode = READ_MODE_INTENSITY_SECTION;
	return 1;
}

u32 ReadIntensitySectionParse(T_SPECTROMETER *sp)
{
	u32 i,nBufferOffset;
	u8 * pBuffer = sp->cmd.nBuffer;

	for( i = sp->nPixelBeg ; i <= sp->nPixelEnd ; i++)
	{
		nBufferOffset = 2 * ( i - sp->nPixelBeg );
		sp->nIntensity[i] = pBuffer[nBufferOffset ] + ((u32)pBuffer[ nBufferOffset + 1]) * 256;
	}
	return 1;
}

u32 SetXeFrequency(T_SPECTROMETER *sp,float fHz)
{
	char *pCommand = (char*)sp->cmd.nCommand;
    
	sprintf(pCommand,"<0.setting.xe.set hz='%f'/>",fHz);

	sp->cmd.nBytesToSend = strlen(pCommand);
	
	sp->cmd.nBytesToReceive =  64; 
	sp->cmd.nBytesReaded = 0;
	sp->cmd.nCMDMode = READ_MODE_SET_XE_FREQUENCY;
    return 1;
}


u32 ReadSerialNumberReady(T_SPECTROMETER *sp)
{
    sp->cmd.nCommand[0] = 0x40;  
	sp->cmd.nBytesToSend = 1;
	
	sp->cmd.nBytesToReceive = 64;
	sp->cmd.nBytesReaded = 0;
	sp->cmd.nCMDMode = READ_MODE_SERIAL_NUMBER;

	return 1;
}

u32 ReadSerialNumberParse(T_SPECTROMETER *sp)
{
	u16 i;
	for( i = 0 ;i < 64 ; i++ )
	{
		sp->strSN[i] = sp->cmd.nBuffer[i];
		
		if( '\0' == sp->cmd.nBuffer[i] )
		{
			break;
		}
	}
	//sprintf(sp->strSN,"%s",sp->nBuffer);
	return 1;
}

u32 WavelengthToPixel(T_SPECTROMETER *sp,float fWavelength)
{
    int nSize = sp->nPixelNum;
	float *pfWavelength = sp->fWavelength;

	int nFirst = 0;
	int nMid;
    int nLast  = nSize - 1;

	float fDelta1; 
    float fDelta2; 

	////////////////////////////////////////////
    if( nSize <= 3) return 0;

    if( fWavelength >= pfWavelength[nSize - 1])
    {
        return (nSize - 1);
    }
	
    if( fWavelength <= pfWavelength[0])
    {
        return 0;
    }

    if( nLast <= 2) return 0;
	
    /////////////////////////////////////////////
    while (nLast - nFirst > 1 )
    {
        nMid = (nFirst + nLast) / 2;  // compute mid point.
        if (fWavelength >= pfWavelength[nMid])
            nFirst = nMid;  // repeat search in top half.
        else
            nLast  = nMid; // repeat search in bottom half.
    }
    fDelta1 = (float)fabs(pfWavelength[nFirst] - fWavelength);
    fDelta2 = (float)fabs(pfWavelength[nLast]  - fWavelength);
    return ( fDelta1 <= fDelta2) ? nFirst : nLast;
}

float GetIntensityAtWavelength(T_SPECTROMETER *sp,float fWavelength)
{
    int nSize  = sp->nPixelNum;
	int nFirst = 0;
	int nMid;
    int nLast  = nSize - 1;
	float fIntensity;
	float fIntensityFirst;
	float fIntensityLast;
    if( nSize <= 0 ) return 0.0f;
	
    if( fWavelength >= sp->fWavelength[nSize - 1])
    {
        return sp->nIntensity[nSize - 1];
    }
	
    if( fWavelength <= sp->fWavelength[0])
    {
        return sp->nIntensity[0];
    }
	

    if( nLast <= 2) return 0.0f;
	
    
    while (nLast - nFirst > 1 )
    {
        nMid = (nFirst + nLast) / 2;  // compute mid point.
        if (fWavelength >= sp->fWavelength[nMid])
            nFirst = nMid;  // repeat search in top half.
        else
            nLast  = nMid; // repeat search in bottom half.
    }
	
    //if( nFirst == nLast ) return m_fIntensity[nFirst];
	
	fIntensityFirst = (float)sp->nIntensity[nFirst];
	fIntensityLast  = (float)sp->nIntensity[nLast];
    //²åÖµ·¨
    fIntensity = fIntensityFirst +
		(fIntensityLast - fIntensityFirst)
		/(sp->fWavelength[nLast] - sp->fWavelength[nFirst])
		*(fWavelength - sp->fWavelength[nFirst]);
    return fIntensity;
}

