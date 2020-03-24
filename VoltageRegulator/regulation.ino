
#include <LiquidCrystal.h>

const uint8_t PwmPin = 6;
const uint8_t RcFeedbackPin = A0;
const uint8_t PotenciometerPin = A1;


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

typedef struct {
	float	Kp;
	float	Ki;
	float	Kd;
	float	dt;
	float	min;
	float	max;
}PidArgs_t;


class Pid{
	const 	PidArgs_t *m_args;
	float	pre_error;
	float	integral;
public:

	Pid(PidArgs_t *m_args);
  
	uint8_t process(uint8_t, uint8_t);

};


PidArgs_t RcCircuitControl;
Pid regulator(&RcCircuitControl);


void setup() {
  	Serial.begin(115200);
	lcd.begin(16, 2);

 
	pinMode(PwmPin, OUTPUT);
	pinMode(RcFeedbackPin, INPUT);
  	pinMode(PotenciometerPin, INPUT);
  
	
	analogWrite(PwmPin, 0);
  

	RcCircuitControl.Kp = 2.5;
	RcCircuitControl.Ki = 20;
	RcCircuitControl.Kd = 0;
	RcCircuitControl.dt = 0.024;		//24 ms - lebo casova konstanta systemu je 240 ms
	RcCircuitControl.min = 0;
	RcCircuitControl.max = 255;
}



void loop() {
  
  	static int main_counter = 0;
  	main_counter++;
  
  
  	if(main_counter % 5){
    	LcdUpdate();
    }
	
  	uint8_t u = map(wishValue(), 0,1023, 0, 255);
  	uint8_t y = map(feedbackValue(), 0,1023, 0, 255);
  
  	analogWrite(PwmPin, regulator.process(u, y));
  
  	Serial.println(feedbackValue());
  
  	delay(RcCircuitControl.dt*1000); //lepsie by bolo cez interrupt volat Pid::process kazdych dt milisekund
  	
}

static void LcdUpdate()
{
  	lcd.setCursor(0, 0);
	lcd.print("Wish[V]");
  
  	lcd.setCursor(0, 1);
	lcd.print(5.0*wishValue()/1023.0);
 
  
  	lcd.setCursor(9, 0);
	lcd.print("Real[V]");
  
  	lcd.setCursor(9, 1);
	lcd.print(5.0*feedbackValue()/1023.0);
}


static uint16_t wishValue()
{
	return  analogRead(PotenciometerPin); 
}

static uint16_t feedbackValue()
{
 	return analogRead(RcFeedbackPin);
}

// Pid implemntaion -----------------------------------------------------------------
Pid::Pid(PidArgs_t *p_args):
	m_args(p_args),
	pre_error(0),
	integral(0)
{}


uint8_t Pid::process(uint8_t set_value, uint8_t feedback_value)
{
	//error
	float error = set_value - feedback_value;

	// Proportional term
	float Pout = m_args->Kp * error;

	// Integral term
	if(error < 0 || integral < m_args->max) {
		integral += error * m_args->dt;	    //upper limit Antiwindup
	}

	float Iout = m_args->Ki * integral;

	// Derivative term
	float derivative = (error - pre_error) / m_args->dt;
	float Dout = m_args->Kd * derivative;

	// Calculate total output
	int64_t output = (Pout + Iout + Dout);

	// Restrict to max/min
	if( output >= m_args->max ) {
		output = m_args->max;
	}
	else if( output < m_args->min) {
		output = m_args->min;
	}

	// Save error to previous error
	pre_error = error;

	return (uint8_t)output;
}
