#include "Servo.h"

// 20 millisecond period config.  For a 1-based prescaler,
//
//    (prescaler * overflow / CYC_MSEC) msec = 1 timer cycle = 20 msec
// => prescaler * overflow = 20 * CYC_MSEC
//
// This picks the smallest prescaler that allows an overflow < 2^16.
#define MAX_OVERFLOW    ((1 << 16) - 1)
#define CYC_MSEC        (VARIANT_MCK / 1000) //(1000* CYCLES_PER_MICROSECOND)=1000*72 = 72000000/1000
#define TAU_MSEC        20
#define TAU_USEC        (TAU_MSEC * 1000)
#define TAU_CYC         (TAU_MSEC * CYC_MSEC)
#define SERVO_PRESCALER (TAU_CYC / MAX_OVERFLOW + 1)
#define SERVO_OVERFLOW  ((uint16_t)round((double)TAU_CYC / SERVO_PRESCALER))

// Unit conversions
#define US_TO_COMPARE(us) ((uint16_t)map((us), 0, TAU_USEC, 0, SERVO_OVERFLOW))
#define COMPARE_TO_US(c)  ((uint32_t)map((c), 0, SERVO_OVERFLOW, 0, TAU_USEC))
#define ANGLE_TO_US(a)    ((uint16_t)(map((a), this->minAngle, this->maxAngle, \
this->minPW, this->maxPW)))
#define US_TO_ANGLE(us)   ((int16_t)(map((us), this->minPW, this->maxPW,  \
this->minAngle, this->maxAngle)))

Servo::Servo() {
  this->resetFields();
}

bool Servo::attach(uint8_t pin,
uint16_t minPW,
uint16_t maxPW,
int16_t minAngle,
int16_t maxAngle) {
  TIM_TypeDef* tdev = g_APinDescription[pin].ulTimerPeripheral;
  uint8_t tchan = g_APinDescription[pin].ulTimerChannel;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
  if (tdev == NULL) {
    // don't reset any fields or ASSERT(0), to keep driving any
    // previously attach()ed servo.
    return false;
  }

  if (this->attached()) {
    this->detach();
  }

  this->pin = pin;
  this->minPW = minPW;
  this->maxPW = maxPW;
  this->minAngle = minAngle;
  this->maxAngle = maxAngle;

  pinMode(pin, AF_OUTPUT_PUSHPULL);
  TIM_Cmd(tdev, DISABLE);
  
  // TIM clock enable
    if(tdev == TIM1)
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
#if defined (STM32F40_41xxx)
      GPIO_AF_TIM = GPIO_AF_TIM1;
#endif
    }
    else if(tdev == TIM2)
    {
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
#if defined (STM32F40_41xxx)
      GPIO_AF_TIM = GPIO_AF_TIM2;
#endif
    }
    else if(tdev == TIM3)
    {
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
#if defined (STM32F40_41xxx)
      GPIO_AF_TIM = GPIO_AF_TIM3;
#endif
    }
    else if(tdev == TIM4)
    {
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
#if defined (STM32F40_41xxx)
      GPIO_AF_TIM = GPIO_AF_TIM4;
#endif
    }
    else if(tdev == TIM5)
    {
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
#if defined (STM32F40_41xxx)
      GPIO_AF_TIM = GPIO_AF_TIM5;
#endif
    }
    else if(tdev == TIM8)
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 , ENABLE);
#if defined (STM32F40_41xxx)
      GPIO_AF_TIM = GPIO_AF_TIM8;
#endif
    }
    
//  tdev.pause();
      // Time base configuration
  TIM_TimeBaseStructure.TIM_Period = SERVO_OVERFLOW;
  TIM_TimeBaseStructure.TIM_Prescaler = SERVO_PRESCALER-1;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    //for TIM1 and TIM8
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(tdev, &TIM_TimeBaseStructure);
  
  // PWM1 Mode configuration
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_Pulse = 0;

  //for TIM1 and TIM8
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
  
	if(tchan == TIM_Channel_1)
	{
		// PWM1 Mode configuration: Channel1
		TIM_OC1Init(tdev, &TIM_OCInitStructure);
		TIM_OC1PreloadConfig(tdev, TIM_OCPreload_Enable);
	}
	else if(tchan == TIM_Channel_2)
	{
		// PWM1 Mode configuration: Channel2
		TIM_OC2Init(tdev, &TIM_OCInitStructure);
		TIM_OC2PreloadConfig(tdev, TIM_OCPreload_Enable);
	}
	else if(tchan == TIM_Channel_3)
	{
		// PWM1 Mode configuration: Channel3
		TIM_OC3Init(tdev, &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(tdev, TIM_OCPreload_Enable);
	}
	else if(tchan == TIM_Channel_4)
	{
		// PWM1 Mode configuration: Channel4
		TIM_OC4Init(tdev, &TIM_OCInitStructure);
		TIM_OC4PreloadConfig(tdev, TIM_OCPreload_Enable);
	}

	TIM_ARRPreloadConfig(tdev, ENABLE);

	// TIM enable counter
	TIM_Cmd(tdev, ENABLE);

  //for TIM1 and TIM8
  TIM_CtrlPWMOutputs(tdev, ENABLE);
//  tdev.setPrescaleFactor(SERVO_PRESCALER - 1);
//  tdev.setOverflow(SERVO_OVERFLOW);
//  tdev.setMode(TIMER_CH1, TIM_OCMode_PWM1);
  // timer_pause(tdev);
  // timer_set_prescaler(tdev, SERVO_PRESCALER - 1); // prescaler is 1-based
  // timer_set_reload(tdev, SERVO_OVERFLOW);
  // timer_generate_update(tdev);
  // timer_resume(tdev);

  return true;
}

bool Servo::detach() {
  if (!this->attached()) {
    return false;
  }

  TIM_TypeDef *tdev = g_APinDescription[this->pin].ulTimerPeripheral;
  uint8_t tchan = g_APinDescription[this->pin].ulTimerChannel;
  TIM_CCxCmd(tdev, tchan, TIM_CCx_Disable);

  this->resetFields();

  return true;
}

void Servo::write(int degrees) {
  degrees = constrain(degrees, this->minAngle, this->maxAngle);
  this->writeMicroseconds(ANGLE_TO_US(degrees));
}

int Servo::read() const {
  int a = US_TO_ANGLE(this->readMicroseconds());
  // map() round-trips in a weird way we mostly correct for here;
  // the round-trip is still sometimes off-by-one for write(1) and
  // write(179).
  return a == this->minAngle || a == this->maxAngle ? a : a + 1;
}

void Servo::writeMicroseconds(uint16_t pulseWidth) {
  if (!this->attached()) {
//    ASSERT(0);
    return;
  }
  TIM_TypeDef *tdev = g_APinDescription[this->pin].ulTimerPeripheral;
  uint8_t tchan = g_APinDescription[this->pin].ulTimerChannel;
  
  pulseWidth = constrain(pulseWidth, this->minPW, this->maxPW);
  if(tchan == TIM_Channel_1) {
    TIM_SetCompare1(tdev, US_TO_COMPARE(pulseWidth));
  }else if(tchan == TIM_Channel_2) {
    TIM_SetCompare2(tdev, US_TO_COMPARE(pulseWidth));
  }else if(tchan == TIM_Channel_3) {
    TIM_SetCompare3(tdev, US_TO_COMPARE(pulseWidth));
  }else if(tchan == TIM_Channel_4) {
    TIM_SetCompare4(tdev, US_TO_COMPARE(pulseWidth));
  }
}

uint16_t Servo::readMicroseconds() const {
  if (!this->attached()) {
//    ASSERT(0);
    return 0;
  }
  TIM_TypeDef *tdev = g_APinDescription[this->pin].ulTimerPeripheral;
  uint8_t tchan = g_APinDescription[this->pin].ulTimerChannel;
  uint16_t compare;
//  stm32_pin_info pin_info = PIN_MAP[this->pin];
  if(tchan == TIM_Channel_1) {
    compare = tdev->CCR1;
  }else if(tchan == TIM_Channel_2) {
    compare = tdev->CCR2;
  }else if(tchan == TIM_Channel_3) {
    compare = tdev->CCR3;
  }else if(tchan == TIM_Channel_4) {
    compare = tdev->CCR4;
  }
//  uint16_t compare = timer_get_compare(pin_info.timer_device,
//  pin_info.timer_channel);

  return COMPARE_TO_US(compare);
}

void Servo::resetFields(void) {
  this->pin = NOT_ATTACHED;
  this->minAngle = SERVO_DEFAULT_MIN_ANGLE;
  this->maxAngle = SERVO_DEFAULT_MAX_ANGLE;
  this->minPW = SERVO_DEFAULT_MIN_PW;
  this->maxPW = SERVO_DEFAULT_MAX_PW;
}
