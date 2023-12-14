#ifndef UTILS_AIO_
#define UTILS_AIO_

#include <stdint.h>
#include <math.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "apcilib.h"
#define DEVICEPATH "/dev/apci/pcie_adio16_16f_0"
#define DEV2PATH "/dev/apci/mpcie_adio16_8e_0"


#define BAR_REGISTER 1

/* Hardware register offsets */
#define RESETOFFSET				0x00
#define ADCBASECLOCKOFFSET		0x0C
#define ADCRATEDIVISOROFFSET	0x10
#define ADCRANGEOFFSET			0x18
#define FAFIRQTHRESHOLDOFFSET	0x20
#define ADCFIFODepthOffset		0x28
#define ADCDataRegisterOffset	0x30
#define ADCControlOffset		0x38
#define IRQENABLEOFFSET			0x40

/* ADC control register bit masks */
#define ADC_RESERVED_MASK		0xFFF88405 // CFG, RSV, REFEN, CPHA are reserved bits
#define ADC_CFG_MASK   			0x00028000
#define ADC_START_MASK 			0x00010000
#define ADC_CHANNEL_MASK		0x00007000
#define ADC_CHANNEL_SHIFT		12
#define ADC_NOT_DIFF_MASK		0x00000800
#define ADC_GAIN_MASK			0x00000380
#define ADC_GAIN_SHIFT			7
#define ADC_NOT_AUX_MASK		0x00000040
#define ADC_ADVANCED_SEQ_MASK	0x00000020
#define ADC_NOT_TEMP_MASK		0x00000008
#define ADC_NOT_FAST_MASK		0x00000002 // clear this bit for speeds > 900kHz

#define RAWrunningshift 30
#define RAWdioshift 26
#define RAWtempshift 25
#define RAWmuxshift 24
#define RAWchannelshift 20
#define RAWdiffshift 19
#define RAWgainshift 16
#define RAWrunningshift 30

// All ranges are bipolar, all counts are 16-bit, so the 0x8000 constant is half the span of counts.
// These numbers include the extra 2.4% margin for calibration (these are uncalibrated).
// The other status bits are useful for streaming.


/* FORWARD REFERENCES */


/* GLOBALS */
// pthread_t worker_thread;
static int terminate;



#pragma region /* UTILITY FUNCTIONS */
// 				void abort_handler(int s)
// 				{
// 					printf("\n\nCaught signal %d\n",s);

// 					terminate = 1;
// 					pthread_join(worker_thread, NULL);

// 					/* put the card back in the power-up state */
// 					BRD_Reset(apci);
// 					exit(1);
// 				}

				/*
					Assemble an ADC control register command uint32 piecemeal
					all params except `channel_lastchannel` are bools, 0==false
					channel is between 0 and 7 inclusive,
					channel is either "the one channel to acquire" (when bSequencedMode is false)
					or channel is "the last channel in the sequence to acquire" (when bSequencedMode is true)
				*/
				
#pragma endregion

class AIOWriteRead{
public:
    AIOWriteRead();
    int readChannel(int ch, uint32_t *data);
    // int writeall(void *data);
    // int readsingle();
    // int writesingle(int i, bool bit);
    ~AIOWriteRead();
private:
    int testcount=0, passcount=0, errcount=0, readbackerrcount=0, chan;
	uint32_t readControlValue;
    uint8_t CHANNEL_COUNT = 16; // change to 8 for M.2-/mPCIe-ADIO16-8F Family cards
    int bDiagnostic = 1;
    int apci;
    const double RangeScale[8] =
{
	24.576 / 0x8000, // code 0
	10.24 / 0x8000, // code 1
	5.12 / 0x8000, // code 2
	2.56 / 0x8000, // code 3
	1.28 / 0x8000, // code 4
	0.64 / 0x8000, // code 5
	NAN, // code 6 is "Invalid" according to ADAS3022 chip spec
	20.48 / 0x8000, // code 7
};
    void BRD_Reset(int apci);
    int ParseADCRawData(uint32_t rawData, uint32_t *channel, double *volts, uint8_t *gainCode, uint16_t *digitalData, int *differential, int *bTemp, int *bAux, int *running );
    uint32_t ADC_BuildControlValue(int bStartADC, int channel_lastchannel, int bDifferential, int gainCode, int bSequencedMode, int bFast);
    int pretty_print_ADC_raw_data(uint32_t AdcRawData, int bCompact);
    void set_acquisition_rate (int fd, double *Hz);
 
};

#endif