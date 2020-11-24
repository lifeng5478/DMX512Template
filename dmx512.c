/************************************************************
  * @brief   DMX512框架，可移植至任意MCU
	* @param   NULL
  * @return  NULL
  * @author  lifeng
  * @github  https://github.com/lifeng5478
  * @date    2020-11-24
  * @version v1.0
  * @note    dmx512.c
  ***********************************************************/

#include "dmx512.h"
__dmx512 dmx512;

/************************************************************
  * @brief   DMX512初始化
	* @param   name : 接收数据回调函数
  * @return  NULL
  * @author  lifeng
  * @github  https://github.com/lifeng5478
  * @date    2020-11-24
  * @version v1.0
  * @note    仅需要给出串口接收数据uint16的返回数据 
  * 		定义一个回调函数，内含串口接收数据，返回接收的数据
  ***********************************************************/
void dmx512_initial(uint16_t (*rec_call)(void))
{
	dmx512.rec_callback = rec_call;
}



/************************************************************
  * @brief   DMX接收函数
	* @param   name : 接收数据回调函数
  * @return  NULL
  * @author  lifeng
  * @github  https://github.com/lifeng5478
  * @date    2020-11-24
  * @version v1.0
  * @note    在串口接收中断里面运行即可
  ***********************************************************/
void dmx512_rec(void)
{
	uint16_t udr;
	udr = (dmx512.rec_callback());
	dmx512.RX8_DATA = (udr&0x0100);
	  dmx512.RX8_DATA = (udr&0x0100);
	if(dmx512.RX8_DATA==0)
	{
	  if(!udr)
	  {
		  dmx512.rx_right = 1;
	  }
	}
	else
	{
	  if(dmx512.rx_right==1)
	  {
		  dmx512.rec_run = 1;
		  dmx512.recbuf[dmx512.bufcount++]=(uint8_t)(dmx512.rec_callback());
		  if(dmx512.bufcount>=512)
		  {
			  dmx512.bufcount = 0;
			  dmx512.rx_right=0;
			  dmx512.rec_end = 1;
		  }
	  }
	}
}

/************************************************************
  * @brief   DMX512帧间隙判定
  * @return  NULL
  * @author  lifeng
  * @github  https://github.com/lifeng5478
  * @date    2020-11-24
  * @version v1.0
  * @note    在定时器内执行
  ***********************************************************/
void dmx512_time(void)
{
	if(dmx512.rec_run == 1)
	{
		dmx512.rec_time++;
		if(dmx512.rec_time>DMX512_REC_TIMEOUT)
		{
			dmx512.rec_time = 0;
			dmx512.rec_run = 0;
			dmx512.rec_end = 1;
			dmx512.rx_right = 0;
		}
	}
}

/************************************************************
  * @brief   DMX512接收数据服务程序
  * @return  NULL
  * @author  lifeng
  * @github  https://github.com/lifeng5478
  * @date    2020-11-24
  * @version v1.0
  * @note    主程序大循环调用，可操作512通道数据
  ***********************************************************/
void dmx512_service(void)
{
	uint16_t value;
	if(dmx512.rec_end== 1)
	{
/*
		用户自定义操作程序，可对512通道数据进行操作
*/
		dmx512.rec_end = 0;
		dmx512.bufcount = 0;
	}
}

