


//There is no API defined to get the number of DACs or the number of ADCs like
//there is for the DIO Bytes and Counters. For convenience these helper
//functions are generated from the header file the driver uses for information.
//They are used by samples to make them a little more flexible
//They are not intended for production use, but since they are by PID they will
//always be backwards compatible.
int GetNumAdcsImm(uint32_t Pid)
{
	switch(Pid)
	{
	case 0x807E: return 2;
	case 0x807C: return 2;
	case 0x807A: return 2;
	case 0x8078: return 2;
	case 0x8076: return 2;
	case 0x8074: return 2;
	case 0x8072: return 2;
	case 0x8070: return 2;
	case 0x8036: return 2;
	default: return 0;
	};
}
int GetNumDacs(uint32_t Pid)
{
	switch(Pid)
	{
	case 0x4003: return 8;
	case 0x4002: return 8;
	case 0x815C: return 4;
	case 0x815B: return 4;
	case 0x815A: return 4;
	case 0x8158: return 4;
	case 0x8157: return 4;
	case 0x8156: return 4;
	case 0x8155: return 4;
	case 0x8154: return 4;
	case 0x8153: return 4;
	case 0x8152: return 4;
	case 0x8151: return 4;
	case 0x8150: return 4;
	case 0x814F: return 4;
	case 0x814D: return 4;
	case 0x814C: return 4;
	case 0x814B: return 4;
	case 0x814A: return 4;
	case 0x8149: return 4;
	case 0x8148: return 4;
	case 0x8147: return 4;
	case 0x8146: return 4;
	case 0x8145: return 4;
	case 0x8144: return 4;
	case 0x8143: return 4;
	case 0x8142: return 4;
	case 0x8141: return 4;
	case 0x815f: return 4;
	case 0x8140: return 4;
	case 0x807F: return 4;
	case 0x807E: return 4;
	case 0x807D: return 8;
	case 0x807C: return 8;
	case 0x807B: return 12;
	case 0x807A: return 12;
	case 0x8079: return 16;
	case 0x8078: return 16;
	case 0x8077: return 4;
	case 0x8076: return 4;
	case 0x8075: return 8;
	case 0x8074: return 8;
	case 0x8073: return 12;
	case 0x8072: return 12;
	case 0x8071: return 16;
	case 0x8070: return 16;
	case 0x8068: return 1;
	case 0x8037: return 2;
	case 0x800F: return 1;
	case 0x800E: return 1;
	case 0x800D: return 1;
	case 0x800C: return 1;
	default: return 0;
	};
}
int GetNumAdcMuxChan(uint32_t Pid)
{
	switch(Pid)
	{
	case 0x8180: return 2;
	case 0x815C: return 128;
	case 0x815B: return 128;
	case 0x815A: return 128;
	case 0x8158: return 96;
	case 0x8157: return 96;
	case 0x8156: return 96;
	case 0x8155: return 96;
	case 0x8154: return 96;
	case 0x8153: return 64;
	case 0x8152: return 64;
	case 0x8151: return 64;
	case 0x8150: return 64;
	case 0x814F: return 32;
	case 0x814D: return 32;
	case 0x814C: return 32;
	case 0x814B: return 32;
	case 0x814A: return 32;
	case 0x8149: return 64;
	case 0x8148: return 64;
	case 0x8147: return 64;
	case 0x8146: return 64;
	case 0x8145: return 64;
	case 0x8144: return 16;
	case 0x8143: return 16;
	case 0x8142: return 16;
	case 0x8141: return 16;
	case 0x815f: return 16;
	case 0x8140: return 16;
	case 0x8068: return 128;
	case 0x805D: return 128;
	case 0x805C: return 128;
	case 0x805B: return 128;
	case 0x805A: return 128;
	case 0x8059: return 128;
	case 0x8058: return 96;
	case 0x8057: return 96;
	case 0x8056: return 96;
	case 0x8055: return 96;
	case 0x8054: return 96;
	case 0x8053: return 64;
	case 0x8052: return 64;
	case 0x8051: return 64;
	case 0x8050: return 64;
	case 0x804F: return 64;
	case 0x804E: return 32;
	case 0x804D: return 32;
	case 0x804C: return 32;
	case 0x804B: return 32;
	case 0x804A: return 32;
	case 0x8049: return 64;
	case 0x8048: return 64;
	case 0x8047: return 64;
	case 0x8046: return 64;
	case 0x8045: return 64;
	case 0x8044: return 16;
	case 0x8043: return 16;
	case 0x8042: return 16;
	case 0x8041: return 16;
	case 0x8040: return 16;
	default: return 0;
	};
}
