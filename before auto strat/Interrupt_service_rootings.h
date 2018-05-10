/*
 * Interrupt_service_rootings.h
 *
 * Created: 5/16/2017 10:42:48 AM
 *  Author: DhanushkaC
 */ 


#ifndef INTERRUPT_SERVICE_ROOTINGS_H_
#define INTERRUPT_SERVICE_ROOTINGS_H_

void EXinterruptRooting() {
	// On AVR this forces compiler to save registers r18-r31.
	CH_IRQ_PROLOGUE();
	/* IRQ handling code, preemptable if the architecture supports it.*/
	
	// Only ISR processing is to save time
	//tIsr = micros();
	
	chSysLockFromISR();
	/* Invocation of some I-Class system APIs, never preemptable.*/
	
	// signal handler task
	chBSemSignalI(&isrStepperSync);
	
	currentSPI++;
	SPIdetect = true;
	SPI_updated=true;
	
	// save timing
	unsigned long nowt=micros();
	tIsr = nowt;
	currentSPI_register_time = nowt - previousSPI_register_time;
	previousSPI_register_time = nowt;
	chSysUnlockFromISR();
	
	/* More IRQ handling code, again preemptable.*/
	
	// Perform rescheduling if required.
	CH_IRQ_EPILOGUE();
}


void InterruptRooting_creasing() {
	
	// On AVR this forces compiler to save registers r18-r31.
	CH_IRQ_PROLOGUE();
	/* IRQ handling code, preemptable if the architecture supports it.*/
	
	// Only ISR processing is to save time
	//tIsr = micros();
	
	chSysLockFromISR();
	/* Invocation of some I-Class system APIs, never preemptable.*/
	// signal handler task
//	if (!digitalRead(creasingIn))
//	{
	//	delayMicroseconds(60000);
	//	if (!digitalRead(creasingIn))
	//	{
		
		//chBSemSignalI(&creasingSem);
		
		//}
	//}
	
	chSysUnlockFromISR();
	
	/* More IRQ handling code, again preemptable.*/
	
	// Perform rescheduling if required.
	CH_IRQ_EPILOGUE();
	
}


#endif /* INTERRUPT_SERVICE_ROOTINGS_H_ */