//
// RC pwm read
//

namespace RcPwm {
static const uint32_t 	DefaultDuty = 1500,
						MinDuty = 1000,
						MaxDuty = 2000,
						Offset = 300;
}

namespace Edge {
enum Enum : uint8_t {
	Falling = 0,
	Rissing
};
}

namespace Channels {
enum Enum : uint8_t {
	Channel1 = 0,
	Channel2 = 1,
	Channel3 = 2,
	Channel4 = 3,

	Size
};
}

typedef struct {
	uint32_t duty_time;;
	uint32_t rissing_time;
	Edge::Enum last_edge;
} channelsArgs_t;

static const uint8_t OutputPins[Channels::Size] = { 2, 3, 4, 5 };
static const uint8_t InputPwmPins[Channels::Size] = { 8, 9, A0, 0 };
static channelsArgs_t s_channelArgs[Channels::Size];


void pciSetup(byte pin)
{
	*digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
	PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
	PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

static void PCINT_HANDLER(Channels::Enum channel, Edge::Enum edge) {
	uint32_t current_micros = micros();
	
	if(edge == Edge::Rissing) {
		s_channelArgs[channel].rissing_time =  current_micros; 
	}
	else {
		s_channelArgs[channel].duty_time =  current_micros - s_channelArgs[channel].rissing_time; 
	}
	
	s_channelArgs[channel].last_edge = edge;
}


ISR(PCINT0_vect) // handle pin change interrupt for D8 to D13 here
{
	Edge::Enum channel1_edge = digitalRead(InputPwmPins[Channels::Channel1]);
	Edge::Enum channel2_edge = digitalRead(InputPwmPins[Channels::Channel2]);
	
	if(channel1_edge != s_channelArgs[Channels::Channel1].last_edge) {
		PCINT_HANDLER(Channels::Channel1, channel1_edge);
	}

	else if(channel2_edge != s_channelArgs[Channels::Channel2].last_edge) {
		PCINT_HANDLER(Channels::Channel2, channel2_edge);
	}
}
 
ISR(PCINT1_vect) // handle pin change interrupt for A0 to A5 here
{
	Edge::Enum channel_edge = digitalRead(InputPwmPins[Channels::Channel3]);

	if(channel_edge != s_channelArgs[Channels::Channel3].last_edge) {
		PCINT_HANDLER(Channels::Channel3, channel_edge);
	}
}  
 
ISR(PCINT2_vect) // handle pin change interrupt for D0 to D7 here
{
	Edge::Enum channel_edge = digitalRead(InputPwmPins[Channels::Channel4]);

	if(channel_edge != s_channelArgs[Channels::Channel4].last_edge) {
		PCINT_HANDLER(Channels::Channel4, channel_edge);
	}
}  
 
void setup() {
	int i;
	Serial.begin(250000);
	pinMode(InputPwmPins[Channels::Channel1], INPUT_PULLUP);
	pinMode(InputPwmPins[Channels::Channel2], INPUT_PULLUP);
	pinMode(InputPwmPins[Channels::Channel3], INPUT_PULLUP);
	pinMode(InputPwmPins[Channels::Channel4], INPUT_PULLUP);
	
	// enable interrupt for pin...
	pciSetup(InputPwmPins[Channels::Channel1]);
	pciSetup(InputPwmPins[Channels::Channel2]);
	pciSetup(InputPwmPins[Channels::Channel3]);
	pciSetup(InputPwmPins[Channels::Channel4]);
}
 
 
void loop() {
	
	updateChannels();
	
//	Serial.print(s_channelArgs[Channels::Channel1].duty_time);
//	Serial.print("	");
//	Serial.print(s_channelArgs[Channels::Channel2].duty_time);
//	Serial.print("	");
//	Serial.print(s_channelArgs[Channels::Channel3].duty_time);
//	Serial.print("	");
//	Serial.println(s_channelArgs[Channels::Channel4].duty_time);
//
//	Serial.print(digitalRead(OutputPins[Channels::Channel1]));
//	Serial.print("	");
//	Serial.print(digitalRead(OutputPins[Channels::Channel2]));
//	Serial.print("	");
//	Serial.print(digitalRead(OutputPins[Channels::Channel3]));
//	Serial.print("	");
//	Serial.println(digitalRead(OutputPins[Channels::Channel4]));
}

static void updateChannels() {

	uint32_t current_micros = micros();
	uint32_t last_micros = 0;

	if(current_micros >= (last_micros + 100000)) {	//100 ms

		for(int i =0; i < Channels::Size; i++) {
			updateSingleChannel(i);
		}
		last_micros = current_micros;
	}
}

static void updateSingleChannel(Channels::Enum channel) {
	
	/* KOntrola ci chodi PWM */
	if(micros() >= (s_channelArgs[channel].rissing_time + 1000000)) {
		s_channelArgs[channel].duty_time = 0;
	}

	/* Aktualizovat vystup */
	if(s_channelArgs[channel].duty_time >= (RcPwm::DefaultDuty + RcPwm::Offset)) {
		digitalWrite(OutputPins[channel], HIGH);
	}
	else if(s_channelArgs[channel].duty_time <= (RcPwm::DefaultDuty - RcPwm::Offset)) {
		digitalWrite(OutputPins[channel], LOW);
	}
	
}


