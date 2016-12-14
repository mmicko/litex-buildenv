#include <generated/csr.h>
#include <generated/mem.h>
#ifdef ENCODER_BASE

#include <stdio.h>
#include <console.h>
#include <time.h>

#include "processor.h"
#include "encoder.h"

void encoder_write_reg(unsigned int adr, unsigned int value) {
		MMPTR(ENCODER_BASE+adr) = value;
}

unsigned int encoder_read_reg(unsigned int adr) {
		return MMPTR(ENCODER_BASE+adr);
}

const char luma_rom_100[64] = {
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
};

const char luma_rom_85[64] = {
	0x05, 0x03, 0x04, 0x04, 0x04, 0x03, 0x05, 0x04,
	0x04, 0x04, 0x05, 0x05, 0x05, 0x06, 0x07, 0x0C,
	0x08, 0x07, 0x07, 0x07, 0x07, 0x0F, 0x0B, 0x0B,
	0x09, 0x0C, 0x11, 0x0F, 0x12, 0x12, 0x11, 0x0F,
	0x11, 0x11, 0x13, 0x16, 0x1C, 0x17, 0x13, 0x14,
	0x1A, 0x15, 0x11, 0x11, 0x18, 0x21, 0x18, 0x1A,
	0x1D, 0x1D, 0x1F, 0x1F, 0x1F, 0x13, 0x17, 0x22,
	0x24, 0x22, 0x1E, 0x24, 0x1C, 0x1E, 0x1F, 0x1E
};

const char luma_rom_75[64] = {
	0x08, 0x06, 0x06, 0x07, 0x06, 0x05, 0x08, 0x07,
	0x07, 0x07, 0x09, 0x09, 0x08, 0x0A, 0x0C, 0x14,
	0x0D, 0x0C, 0x0B, 0x0B, 0x0C, 0x19, 0x12, 0x13,
	0x0F, 0x14, 0x1D, 0x1A, 0x1F, 0x1E, 0x1D, 0x1A,
	0x1C, 0x1C, 0x20, 0x24, 0x2E, 0x27, 0x20, 0x22,
	0x2C, 0x23, 0x1C, 0x1C, 0x28, 0x37, 0x29, 0x2C,
	0x30, 0x31, 0x34, 0x34, 0x34, 0x1F, 0x27, 0x39,
	0x3D, 0x38, 0x32, 0x3C, 0x2E, 0x33, 0x34, 0x32
};

const char luma_rom_50[64] = {
	0x10, 0x0B, 0x0C, 0x0E, 0x0C, 0x0A, 0x10, 0x0E,
	0x0D, 0x0E, 0x12, 0x11, 0x10, 0x13, 0x18, 0x28,
	0x1A, 0x18, 0x16, 0x16, 0x18, 0x31, 0x23, 0x25,
	0x1D, 0x28, 0x3A, 0x33, 0x3D, 0x3C, 0x39, 0x33,
	0x38, 0x37, 0x40, 0x48, 0x5C, 0x4E, 0x40, 0x44,
	0x57, 0x45, 0x37, 0x38, 0x50, 0x6D, 0x51, 0x57,
	0x5F, 0x62, 0x67, 0x68, 0x67, 0x3E, 0x4D, 0x71,
	0x79, 0x70, 0x64, 0x78, 0x5C, 0x65, 0x67, 0x63
};

const char chroma_rom_100[64] = {
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
};

const char chroma_rom_85[64] = {
	0x08, 0x06, 0x06, 0x07, 0x06, 0x05, 0x08, 0x07,
	0x07, 0x07, 0x09, 0x09, 0x08, 0x0A, 0x0C, 0x14,
	0x0D, 0x0C, 0x0B, 0x0B, 0x0C, 0x19, 0x12, 0x13,
	0x0F, 0x14, 0x1D, 0x1A, 0x1F, 0x1E, 0x1D, 0x1A,
	0x1C, 0x1C, 0x20, 0x24, 0x2E, 0x27, 0x20, 0x22,
	0x2C, 0x23, 0x1C, 0x1C, 0x28, 0x37, 0x29, 0x2C,
	0x30, 0x31, 0x34, 0x34, 0x34, 0x1F, 0x27, 0x39,
	0x3D, 0x38, 0x32, 0x3C, 0x2E, 0x33, 0x34, 0x32
};

const char chroma_rom_75[64] = {
	0x09, 0x09, 0x09, 0x0C, 0x0B, 0x0C, 0x18, 0x0D,
	0x0D, 0x18, 0x32, 0x21, 0x1C, 0x21, 0x32, 0x32,
	0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32,
	0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32,
	0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32,
	0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32,
	0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32,
	0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32
};

const char chroma_rom_50[64] = {
	0x11, 0x12, 0x12, 0x18, 0x15, 0x18, 0x2F, 0x1A,
	0x1A, 0x2F, 0x63, 0x42, 0x38, 0x42, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63
};

static void encoder_config_table(unsigned int base, const char *table)
{
	int i;
	for(i=0; i<64; i++)
		encoder_write_reg(base+4*i, table[i]);
}

void encoder_init(int quality) {
	if(quality == 100) {
		encoder_config_table(ENCODER_QUANTIZER_RAM_LUMA_BASE, luma_rom_100);
		encoder_config_table(ENCODER_QUANTIZER_RAM_CHROMA_BASE, chroma_rom_100);
		encoder_quality = 100;
	} else if (quality == 85) {
		encoder_config_table(ENCODER_QUANTIZER_RAM_LUMA_BASE, luma_rom_85);
		encoder_config_table(ENCODER_QUANTIZER_RAM_CHROMA_BASE, chroma_rom_85);
		encoder_quality = 85;
	} else if (quality == 75) {
		encoder_config_table(ENCODER_QUANTIZER_RAM_LUMA_BASE, luma_rom_75);
		encoder_config_table(ENCODER_QUANTIZER_RAM_CHROMA_BASE, chroma_rom_75);
		encoder_quality = 75;
	} else {
		encoder_config_table(ENCODER_QUANTIZER_RAM_LUMA_BASE, luma_rom_50);
		encoder_config_table(ENCODER_QUANTIZER_RAM_CHROMA_BASE, chroma_rom_50);
		encoder_quality = 50;
	}
}

void encoder_start(short resx, short resy) {
	encoder_write_reg(ENCODER_IMAGE_SIZE_REG, (resx << 16) | resy);
	encoder_write_reg(ENCODER_START_REG, 7); /* RGB, SOF */
}

int encoder_done(void) {
	return (encoder_read_reg(ENCODER_STS_REG) & 0x1) == 0;
}

void encoder_enable(char enable) {
	encoder_enabled = enable;
}

int encoder_set_quality(int quality) {
	switch(quality) {
		case 100:
		case 85:
		case 75:
		case 50:
			encoder_quality = quality;
			break;
		default:
			printf("Unsupported encoder quality (50, 75, 85 or 100)\r\n");
			return 0;
	}
	return 1;
}

int encoder_set_fps(int fps) {
	if(encoder_target_fps > 0 && encoder_target_fps <= 60) {
		encoder_target_fps = fps;
		return 0;
	}
	else {
		encoder_target_fps = 30;
		return 1;
	}
}

void encoder_service(void) {

	static int last_event;
	static int last_fps_event;
	static int frame_cnt;

	if(encoder_enabled) {
		if(encoder_done()) {
			encoder_init(encoder_quality);
			encoder_start(processor_h_active, processor_v_active);
			frame_cnt++;
		}
		if (encoder_reader_done_read()) {
			encoder_reader_length_write((processor_h_active*processor_v_active)/8); // FIXME
			encoder_reader_shoot_write(1);
		}
		if(elapsed(&last_fps_event, SYSTEM_CLOCK_FREQUENCY)) {
			encoder_fps = frame_cnt;
			frame_cnt = 0;
		}
	}
}

#endif
