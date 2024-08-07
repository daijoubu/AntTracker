// ESP32 HW-spcific Functions
#ifdef ARDUINO_ARCH_ESP32
#include <MobaTools.h>
#define debugTP
//#define debugPrint
#include <utilities/MoToDbg.h>

//#warning "HW specfic - ESP32 ---"

bool spiInitialized = false;
void IRAM_ATTR stepperISR(int32_t cyclesLastIRQ)  __attribute__ ((weak));
nextCycle_t nextCycle;
static nextCycle_t cyclesLastIRQ = 1;  // cycles since last IRQ

void IRAM_ATTR ISR_Stepper(void) {
    static uint64_t lastAlarm, aktAlarm;
    // Timer running up, used for stepper motor. No reload of timer
    SET_TP1;
    nextCycle = ISR_IDLETIME  / CYCLETIME ;// min ist one cycle per IDLETIME
    portENTER_CRITICAL_ISR(&stepperMux);
    cyclesLastIRQ = (aktAlarm - lastAlarm) / TICS_PER_MICROSECOND;
    if ( stepperISR ) stepperISR(cyclesLastIRQ);
	// next alarm ISR must be at least MIN_STEP_CYCLE/2 beyond last alarm value ( time between to ISR's )
    lastAlarm = aktAlarm;
    aktAlarm = lastAlarm+(nextCycle*TICS_PER_MICROSECOND); // minimumtime until next Interrupt
    uint64_t minNextAlarm = lastAlarm + (MIN_STEP_CYCLE*TICS_PER_MICROSECOND/2);
	if ( aktAlarm < minNextAlarm ) {
		// time till next ISR ist too short, set to mintime and adjust nextCycle
        CLR_TP1;
		aktAlarm =  minNextAlarm;
	}
    //3.0.3 void timerAlarm(hw_timer_t * timer, uint64_t alarm_value, bool autoreload, uint64_t reload_count);
    timerAlarm(stepTimer, aktAlarm , false, 0); // no autorelaod, 0=unlimited - zs6buj
    //timerAlarmEnable(stepTimer);  // auto from esp32 core 3.0
    SET_TP1;
    portEXIT_CRITICAL_ISR(&stepperMux);
    CLR_TP1; // Oszimessung Dauer der ISR-Routine
}
////////////////////////////////////////////////////////////////////////////////////////////
timerConfig_t timerConfig;
portMUX_TYPE stepperMux = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE servoMux = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE softledMux = portMUX_INITIALIZER_UNLOCKED;
hw_timer_t * stepTimer = NULL;

void seizeTimerAS() {
static bool timerInitialized = false;
    // Initiieren des Stepper Timers ------------------------
    if ( !timerInitialized ) {
        // core 3.0.3 hw_timer_t * timerBegin(uint32_t frequency);   // frequency in Hz    
        //stepTimer = timerBegin(STEPPER_TIMER, DIVIDER, true); // true= countup
        stepTimer = timerBegin(80000000);  // zs6buj
        // core 3.0.3void timerAttachInterrupt(hw_timer_t * timer, void (*userFunc)(void));
        //timerAttachInterrupt(stepTimer, &ISR_Stepper, true);  // true= edge Interrupt
        timerAttachInterrupt(stepTimer, &ISR_Stepper); // assume edge - zs6buj
        timerAlarm(stepTimer, ISR_IDLETIME*TICS_PER_MICROSECOND , false, 0); // false = no autoreload );
        //timerAlarmEnable(stepTimer);  // auto from esp32 core 3.0
        timerInitialized = true;  
        MODE_TP1;   // set debug-pins to Output
        MODE_TP2;
        MODE_TP3;
        MODE_TP4;
    }
}


void enableServoIsrAS() {
}


void enableSoftLedIsrAS() {

}


#endif
