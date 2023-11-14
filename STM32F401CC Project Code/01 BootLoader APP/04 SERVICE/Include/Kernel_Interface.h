
#ifndef KERNEL_INTERFACE_H_
#define KERNEL_INTERFACE_H_

void RTOS_voidStart(void);
/* Periodicity system tick = 1ms */
Error_type RTOS_Error_typeCreateTask(u8 LocalPriority, void (*Local_PTaskFunc)(void), u16 Localperiodicity, u16 localFirstDelay);
 
void RTOS_voidSuspendTask(u8 LocalPriority);

void RTOS_voidResumeTask(u8 LocalPriority);

void RTOS_voidDeleteTask(u8 LocalPriority);


#endif /* KERNEL_INTERFACE_H_ */