# DMX512Template
DMX512公共模板可移植到任意MCU

## 使用方法

1. 初始化
> uint16_t rec_date(void)
> {
> 	return ((UART2->RBR)&0x1ff);
> }
> int main(void)
> {
> UART2_Init();
> TIMER0_Init();
> dmx512_initial(rec_date);
> }

2. 接收函数加入串口接收中断种
>void UART2_IRQHandler_Callback(void *device, uint32_t wpara, uint32_t lpara)
>{
>   			dmx512_rec();
>}

3. 定时器加入接收超时程序
>   void TIMER_CHANNEL0_IRQHandler_Callback(void *device, uint32_t wpara, uint32_t lpara)
>{
>
 >   /* USER CODE BEGIN TIMER_CHANNEL0_IRQHandler_Callback */
>dmx512_time();
>    /* USER CODE END TIMER_CHANNEL0_IRQHandler_Callback */
>}


4. 主程序大循环加入服务程序
>int main(void)
>{
>       ...
>       ...
>       while(1){
>           dmx512_service();	
>           ...
>           }		
>       ...
>       ...
   >}