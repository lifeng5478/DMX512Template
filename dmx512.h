#ifndef __dmx512_h_
#define __dmx512_h_

#include "ac780x.h"//添加自己的mcu头文件
#include "main.h"

#define DMX512_REC_TIMEOUT 10	//DMX512接收数据超时时间

typedef struct{
	uint16_t recbuf[513];	//接收缓存
	uint16_t bufcount;		//接收计数
	uint8_t rec_end;		//接收结束标志
	uint8_t rec_run;		//接收开始标志
	uint8_t rec_time;		//接收结束计时
	uint16_t RX8_DATA;		//DMX512第9位
	uint8_t rx_right;			
	uint16_t	(*rec_callback)(void);	//接收回调函数
}__dmx512;

extern __dmx512 dmx512;

void dmx512_initial(uint16_t (*rec_call)(void));
void dmx512_rec(void);
void dmx512_time(void);
void dmx512_service(void);

#endif
