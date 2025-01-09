#include <stdio.h>
#include "wl_types.h"
#include "gpio.h"
#include "uart.h"

#if defined(ThreadOS)
#include "tx_api.h"
extern uint32_t *_stack_start;
extern  void *_tx_initialize_unused_memory;
extern void *_tx_thread_system_stack_ptr;
uint64_t memory_allocated[1024] = {0};
#define DEMO_STACK_SIZE         1024
#define DEMO_BYTE_POOL_SIZE     9120
#define DEMO_BLOCK_POOL_SIZE    100
#define DEMO_QUEUE_SIZE         100

TX_THREAD               thread_0;
TX_THREAD               thread_1;

TX_QUEUE                queue_0;
TX_SEMAPHORE            semaphore_0;
TX_MUTEX                mutex_0;
TX_EVENT_FLAGS_GROUP    event_flags_0;
TX_BYTE_POOL            byte_pool_0;
TX_BLOCK_POOL           block_pool_0;

volatile uint8_t counter_timer;

ULONG                   thread_0_counter;
ULONG                   thread_1_counter;
ULONG                   thread_1_messages_sent;
ULONG                   thread_2_counter;
ULONG                   thread_2_messages_received;


void    thread_0_entry(ULONG thread_input);
void    thread_1_entry(ULONG thread_input);

#endif

volatile uint32_t count;
void delay(uint32_t time)
{
    count = 0;
    for(uint32_t i=0; i < time; i++)
    {
        count++;
    }
}

int main(void)
{
        char *data = "starting programe\r\n";
     	uint8_t length = strlen(data);
        uart_write(data, length);
#ifndef ThreadOS
Test:
#endif	
	gpio_write(42,1);
        delay(1000000 * 500);

#ifndef ThreadOS
	
        gpio_write(42,0);
        delay(1000000 * 500);
        goto Test;	
#else
gpio_write(42,0);
data = "starring  Threadx Rtos Init....\r\n";
length = strlen(data);
uart_write(data, length);
_tx_thread_system_stack_ptr = _stack_start;
tx_kernel_enter();
#endif

    return 0;
}


#if defined(ThreadOS)

void    tx_application_define(void *_tx_initialize_unused_memory)
{
    gpio_write(42,1);
    CHAR    *pointer = TX_NULL;
    tx_byte_pool_create(&byte_pool_0, "byte pool 0", _tx_initialize_unused_memory, DEMO_BYTE_POOL_SIZE);

    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_STACK_SIZE, TX_NO_WAIT);
    tx_thread_create(&thread_0, "thread 0", thread_0_entry, 0,pointer, DEMO_STACK_SIZE,1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);

    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_STACK_SIZE, TX_NO_WAIT);
    tx_thread_create(&thread_1, "thread 1", thread_1_entry, 1,pointer, DEMO_STACK_SIZE,16, 16, 4, TX_AUTO_START);


    tx_block_allocate(&block_pool_0, (VOID **) &pointer, TX_NO_WAIT);
    tx_block_release(pointer);
}




void  thread_0_entry(ULONG thread_input)
{
     uint8_t val = 0;
     while(1)
     {
	 gpio_write(61,val);
	 val = !val;
         thread_0_counter++;
         tx_thread_sleep(10);
     }
}


void thread_1_entry(ULONG thread_input)
{
    while(1){
    thread_1_counter++;
    tx_thread_sleep(10);
    }
}

void timer1_interrupt(void)
{
    counter_timer++;
}

#endif
