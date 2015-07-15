/*
 Reprap heater funtions based on Sprinter
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>. */

/*
 This softwarepart for Heatercontrol is based on Sprinter
 big thanks to kliment (https://github.com/kliment/Sprinter)
 
*/


#include "Configuration.h"
#include "thermistortables.h"

#if defined HEATER_USES_THERMISTOR
#define temp2analogh( c ) temp2analog_thermistor(c,temptable,NUMTEMPS)
#define analog2temp( c ) analog2temp_thermistor(c,temptable,NUMTEMPS)
#elif defined HEATER_USES_AD595
#define temp2analogh( c ) temp2analog_ad595(c)
#define analog2temp( c ) analog2temp_ad595(c)
#elif defined HEATER_USES_MAX6675
#define temp2analogh( c ) temp2analog_max6675(c)
#define analog2temp( c ) analog2temp_max6675(c)
#endif

#if defined BED_USES_THERMISTOR
#define temp2analogBed( c ) temp2analog_thermistor((c),bedtemptable,BNUMTEMPS)
#define analog2tempBed( c ) analog2temp_thermistor((c),bedtemptable,BNUMTEMPS)
#elif defined BED_USES_AD595
#define temp2analogBed( c ) temp2analog_ad595(c)
#define analog2tempBed( c ) analog2temp_ad595(c)
#elif defined BED_USES_MAX6675
#define temp2analogBed( c ) temp2analog_max6675(c)
#define analog2tempBed( c ) analog2temp_max6675(c)
#endif

#if defined (HEATER_USES_THERMISTOR) || defined (BED_USES_THERMISTOR)
int16_t temp2analog_thermistor(int16_t celsius, const short table[][2], int16_t numtemps);
int16_t analog2temp_thermistor(int16_t raw,const short table[][2], int16_t numtemps);
#endif

#if defined (HEATER_USES_AD595) || defined (BED_USES_AD595)
int16_t temp2analog_ad595(int16_t celsius);
int16_t analog2temp_ad595(int16_t raw);
#endif

#if defined (HEATER_USES_MAX6675) || defined (BED_USES_MAX6675)
int16_t temp2analog_max6675(int16_t celsius);
int16_t analog2temp_max6675(int16_t raw);
#endif


extern int16_t target_raw;
extern int16_t target_temp;
extern int16_t current_raw;
extern int16_t current_raw_maxval;
extern int16_t current_raw_minval;
extern int16_t tt_maxval;
extern int16_t tt_minval;
extern int16_t target_bed_raw;
extern int16_t current_bed_raw;
extern unsigned long previous_millis_heater, previous_millis_bed_heater;
extern unsigned char manage_monitor;

#ifdef PIDTEMP
  extern volatile unsigned char g_heater_pwm_val;
 
  extern unsigned char PWM_off_time;
  extern unsigned char PWM_out_on;
  
  extern int16_t temp_iState;
  extern int16_t temp_dState;
  extern int16_t prev_temp;
  extern int16_t pTerm;
  extern int16_t iTerm;
  extern int16_t dTerm;
  extern int16_t error;
  extern int16_t heater_duty;
  
  extern uint16_t PID_Kp, PID_Ki, PID_Kd;
#endif

#if defined(FAN_SOFT_PWM) && (FAN_PIN > -1)
  extern volatile unsigned char g_fan_pwm_val;
#endif

#ifdef AUTOTEMP
    extern float autotemp_max;
    extern float autotemp_min;
    extern float autotemp_factor;
    extern int16_t   autotemp_setpoint;
    extern bool autotemp_enabled;
#endif


#ifdef SMOOTHING
  extern uint32_t nma;
#endif

#ifdef WATCHPERIOD
  extern int16_t watch_raw;
  extern unsigned long watchmillis;
#endif




#if defined(PID_SOFT_PWM) || (defined(FAN_SOFT_PWM) && (FAN_PIN > -1))
 void init_Timer2_softpwm(void);
#endif

#ifdef PID_AUTOTUNE
 void PID_autotune(int16_t PIDAT_test_temp);
#endif

#ifdef PIDTEMP
 void updatePID();
#endif

void manage_heater();
