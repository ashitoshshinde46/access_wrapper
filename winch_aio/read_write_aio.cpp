#include "read_write_aio.h"

AIOWriteRead::AIOWriteRead(){


   	printf("Control Value: %08X\n", ADC_BuildControlValue(1,6,1,1,1,0));
	printf("Control Value: %08X\n", ADC_BuildControlValue(1,7,0,1,1,0));
    
    uint32_t Version = 0;
	apci_read32(apci, 1, BAR_REGISTER, 0x68, &Version);
	printf("\nmPCIe-AIO16-16F/mPCIe-ADIO16-8F Family ADC Sample 0+ [FPGA Rev %08X]\n", Version);
    
    apci = -1;

				// if (argc > 1)
				// {
				// 	apci = open(argv[1], O_RDONLY);	// open device file from command line
				// 	if (apci < 0)
				// 		printf("Couldn't open device file on command line: do you need sudo? /dev/apci? [%s]\n", argv[1]);
				// }

				if (apci < 0) // if the command line didn't work, or if they didn't pass a parameter
				{
					apci = open(DEVICEPATH, O_RDONLY);
					if (apci < 0)
					{
						printf("Device file %s could not be opened. Please ensure the APCI driver module is loaded or try sudo?.\nTrying Alternate [ %s ]...\n", DEVICEPATH, DEV2PATH);
						apci = open(DEV2PATH, O_RDONLY);
						if (apci < 0)
						{
							
							exit(0);
						} else
						{    
                            printf("Device file %s opened.", DEV2PATH);
                            BRD_Reset(apci);
                            double Hz = 100.0;
                            set_acquisition_rate(apci, &Hz);
                            printf("ADC Rate: (%lf Hz)\n", Hz);
							CHANNEL_COUNT = 8;
							printf("CHANNEL_COUNT: %d\n", CHANNEL_COUNT);
                            
						}
					}
				}
}


int AIOWriteRead::readChannel(int in_ch, double *data){
        uint32_t ADCFIFODepth;
		uint32_t ADCDataRaw;

		BRD_Reset(apci);

		apci_write32(apci, 1, BAR_REGISTER, ADCRATEDIVISOROFFSET, 0); // setting ADC Rate Divisor to zero selects software start ADC mode
		for (int ch=0; ch<8; ++ch)
		{
			uint32_t controlValue = ADC_BuildControlValue(1,ch,0,0,0,0);

			apci_write32(apci, 1, BAR_REGISTER, ADCControlOffset, controlValue );	// start one conversion on selected channel
			usleep(10); // must not write to +38 faster than once every 10 microseconds in Software Start mode
				apci_read32(apci,1, BAR_REGISTER, ADCControlOffset, &readControlValue);
				if ((controlValue&0x0000FFFF) != (readControlValue&0x0000FFFF))
				{
					readbackerrcount++;
					printf("%08X/%08X ", readControlValue, controlValue);
				}
		}

		if (CHANNEL_COUNT == 16)
			for (int ch=0; ch<8; ++ch)
			{
				uint32_t controlValue = ADC_BuildControlValue(1,ch,0,0,0,0);
				apci_write32(apci, 1, BAR_REGISTER, ADCControlOffset + 4, controlValue );	// start one conversion on selected channel of second ADC
				usleep(10); // must not write to +3C faster than once every 10 microseconds in Software Start mode
				apci_read32(apci,1, BAR_REGISTER, ADCControlOffset + 4, &readControlValue);
				if ((controlValue&0x0000FFFF) != (readControlValue&0x0000FFFF))
				{
					readbackerrcount++;
					printf("%08X/%08X ", readControlValue, controlValue);
				}
			}


		apci_read32(apci, 1, BAR_REGISTER, ADCFIFODepthOffset, &ADCFIFODepth);
		printf("  ADC FIFO has %d entries\n", ADCFIFODepth); // debug/diagnostic; should match the number of ADC Control writes
		if (ADCFIFODepth != CHANNEL_COUNT)
			errcount++;
		else
			passcount++;
		testcount++;
		int bTemp=0, bAux=0;

		for (int ch=0; ch < ADCFIFODepth; ++ch)	// read and display data from FIFO
		{
			apci_read32(apci, 1, BAR_REGISTER, ADCDataRegisterOffset, &ADCDataRaw);
			pretty_print_ADC_raw_data(ADCDataRaw, 0);
			if (in_ch==ch){
			unsigned int iChannel;
			double ADCDataV;
			uint8_t gainCode;
			int bTemp, bAux, bDifferential, bRunning;
			uint16_t digitalData;

			ParseADCRawData(ADCDataRaw, &iChannel, &ADCDataV, &gainCode, &digitalData, &bDifferential, &bTemp, &bAux, &bRunning);
			*data=ADCDataV;
			}
			//ParseADCRawData(ADCDataRaw, &chan,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
			//printf("%02d ",chan);
		}
		printf("\n");
		//printf("Done with one scan of software-started conversions.\n\n\n");

		printf("\n%d failures, %d passes. Failure%% = %f.  Control readback failures: %d",errcount,passcount,(double)errcount/(double)testcount*100.0, readbackerrcount);
        
        
        
        
        
        
        
    /***    
        
        int status;
        uint32_t ADCFIFODepth;
        uint32_t ADCDataRaw;
        printf("before ADCFIFODepth:%d\n",ADCFIFODepth);
        apci_read32(apci, 1, BAR_REGISTER, ADCFIFODepthOffset, &ADCFIFODepth);
        	printf("ADCFIFODepth:%d\n",ADCFIFODepth);
		if (ADCFIFODepth == 0)
			return -1;

		//do{
			apci_read32(apci, 1, BAR_REGISTER, ADCDataRegisterOffset, &ADCDataRaw); // read data, 1st conversion result
			pretty_print_ADC_raw_data(ADCDataRaw, 1);

			apci_read32(apci, 1, BAR_REGISTER, ADCDataRegisterOffset, &ADCDataRaw); // read data, 2nd conversion result
			pretty_print_ADC_raw_data(ADCDataRaw, 1);
		//}while(--ADCFIFODepth > 0);
		***/
        //*data=ADCDataRaw;
    return 0;
}

void AIOWriteRead::BRD_Reset(int apci)
{
	apci_write32(apci, 1, BAR_REGISTER, RESETOFFSET, 0x1);
}

// int DIOWriteRead::writeall(void *data){
//     if (Status==0){
// AIOUSB::DIO_WriteAll(Device, data);
//         return Status;
// }
//     return -1;
// }

// int DIOWriteRead::readsingle(){
// return -1;
// }


// int DIOWriteRead::writesingle(int i, bool bit){
//      if (Status==0){
//  AIOUSB::DIO_Write1(Device, i, bit);
//          return Status;
// }
//     return -1;
// }



AIOWriteRead::~AIOWriteRead(){
    // MyFile << "in DIOWriteRead destructor"<<std::endl;
 // MyFile.close();
}

int AIOWriteRead::ParseADCRawData(uint32_t rawData, uint32_t *channel, double *volts, uint8_t *gainCode, uint16_t *digitalData, int *differential, int *bTemp, int *bAux, int *bRunning )
{
	int bInvalid = rawData & (1<<31);
	if (!bInvalid)
	{
		if (channel) *channel = (rawData >> RAWchannelshift) & 0x0F;
		if (gainCode) *gainCode = (rawData >> RAWgainshift) & 0x07;
		if (digitalData) *digitalData = (rawData >> RAWdioshift) & 0x0F;
		if (differential) *differential = (rawData >> RAWdiffshift) & 0x01;
		if (bTemp) *bTemp = (rawData >> RAWtempshift) & 0x01;
		if (bAux) *bAux = (rawData >> RAWmuxshift) & 0x01;
		if (bRunning) *bRunning = (rawData >> RAWrunningshift) & 0x01;

		if (volts)
		{
			int16_t Counts = rawData & 0xFFFF;
			if ((bTemp) && (*bTemp))
			{
				/*
					ADC Temp sensor is nonlinear but roughly:
						3800 counts is -45C
						5500 counts is +85C
					thus C = (counts - 3800) / (5500 - 3800) * (85--45) - 45.0;
				*/
				*volts = ((Counts * 1.0) - 3800.0) / (5500.0 - 3800.0) * (85.0 - -45.0) - 45.0;
				p_value=*volts ;
				*channel &= 8; // mask out the actual channel bits as they don't apply if the reading was temperature input, but leave "sequencer" bit
			}
			else
			{
				uint16_t RangeCode = (rawData >> RAWgainshift) & 0x7; // don't rely on "gainCode" being non-null!
				*volts = rawData & (1<<31) // if invalid
					? NAN
					: RangeScale[RangeCode] * Counts;
			}
		}
	}
	return bInvalid;
}

void AIOWriteRead::set_acquisition_rate (int fd, double *Hz)
{
	uint32_t base_clock;
	uint32_t divisor;

	apci_read32(fd, 1, BAR_REGISTER, ADCBASECLOCKOFFSET, &base_clock);
	printf("  set_acquisition_rate: base_clock (%d) / ", base_clock);

	divisor = round(base_clock / *Hz);
	*Hz = base_clock / divisor; /* actual Hz selected, based on the limitation caused by integer divisors */
	printf("divisor (%d) = ", divisor);

	apci_write32(fd, 1, BAR_REGISTER, ADCRATEDIVISOROFFSET, divisor);
	printf("DAC Waveform Playback Rate: (%lf Hz)\n", *Hz);
}

uint32_t AIOWriteRead::ADC_BuildControlValue(int bStartADC, int channel_lastchannel, int bDifferential, int gainCode, int bSequencedMode, int bFast)
				{
					int bTemp = 0; // temp readings are for factory use only
					int bAux = 0;  // the aux inputs aren't connected to anything

					uint32_t controlValue = 0x00000000;
					controlValue |= ADC_CFG_MASK;
					if (bStartADC)
						controlValue |= ADC_START_MASK;

					if ((channel_lastchannel < 8) && (channel_lastchannel >= 0))
						controlValue |= channel_lastchannel << ADC_CHANNEL_SHIFT;
					else
						return -1;	// invalid channel / last_channel

					if (! bDifferential)
						controlValue |= ADC_NOT_DIFF_MASK;

					if ((gainCode < 8) && (gainCode >= 0))
						controlValue |= gainCode << ADC_GAIN_SHIFT;
					else return -2;	// invalid gain code


					// TEMP and AUX are interpreted differently in Sequenced vs "On Demand Conversion" ("Immediate") mode
					if (bSequencedMode)
					{
						controlValue |= ADC_ADVANCED_SEQ_MASK;
						if (! bAux)
							controlValue |= ADC_NOT_AUX_MASK;
						if (! bTemp)
							controlValue |= ADC_NOT_TEMP_MASK;

						// sequenced differential only accepts even channel#s
						if (bDifferential)
							controlValue &= ~(1 << ADC_CHANNEL_SHIFT);
					}
					else // "On Demand Conversion Mode" uses the AUX and TEMP bits differently:
					{
						if (bAux && bTemp) return -3;	// invalid to select both Aux and Temp inputs in Immediate mode (On Demand Conversion Mode)

						if (!bAux && !bTemp)
							controlValue = controlValue | ADC_NOT_AUX_MASK | ADC_NOT_TEMP_MASK;

						if (bAux || bTemp)
							controlValue = controlValue & ~(ADC_NOT_AUX_MASK | ADC_NOT_TEMP_MASK);

						if (!bTemp)
							controlValue |= ADC_NOT_TEMP_MASK; // select NOT temp thus AUX
					}

					if (! bFast)
						controlValue |= ADC_NOT_FAST_MASK;

					if (bDiagnostic)
						printf("  ADC Control Value %8X %s %s CH%2d%s%s\n", controlValue, bTemp?"TEMP":"", bAux?"AUX":"", channel_lastchannel,bSequencedMode?" SEQ":" Imm", bDifferential?" Diff":" S.E.");

					return controlValue;
				}

				/* print ADC data as Volts etc., and if bDiagnostic, in parsed-raw and raw-raw forms */
				int AIOWriteRead::pretty_print_ADC_raw_data(uint32_t AdcRawData, int bCompact)
				{
					unsigned int iChannel;
					double ADCDataV;
					uint8_t gainCode;
					int bTemp, bAux, bDifferential, bRunning;
					uint16_t digitalData;

					ParseADCRawData(AdcRawData, &iChannel, &ADCDataV, &gainCode, &digitalData, &bDifferential, &bTemp, &bAux, &bRunning);
					if ((iChannel == 0) && (!bTemp)) printf("\n  ");

					if (bDiagnostic > 0)
					{
						printf(" [%08X", AdcRawData);
						if (bDiagnostic > 1)
						{
							uint16_t AdcStatusWord = AdcRawData >> 16;
							printf(" %s %s CH%02d G%d DIO%2x %s", bTemp?"TEMP":"", bAux?"AUX":"", iChannel, gainCode, digitalData, bDifferential?"Diff":"S.E.");
						}
						printf("] ");
					}

					{
						if (bTemp)
							printf("ADC %d Temp =% 5.1fC",iChannel?1:0, ADCDataV);
						else
						if (bAux)
							printf("ADC %d Aux =% 5.1f",iChannel?1:0, ADCDataV);
						else
							printf("CH %2d =% 8.4f", iChannel, ADCDataV);
					}

					if (bCompact)
						printf(", ");
					else
						printf("\n  ");
				}
