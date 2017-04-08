#include "synth_utility.h"
#include "synth_display.h"
#include "DSP_toolkit.h"
#include <SPI.h>
#include <spi4teensy3.h>

#define mN 50 //MAX order for lowpass filter
#define mDELAY 1
#define ENC1A 0
#define ENC1B 1
#define ENC1_BUT 2
#define pKEYS 3
#define a0 4
#define a1 5
#define a2 6
#define DAC_enable 10

//Structures 
struct channel channel0, channel1, channel2, channel3, channel4, channel5, channel6, channel7, channelmono;
struct pre_mix pre_master_out;
struct arpeggiator Arpeggiator;
struct main_control Main_control;
struct encoder_options encoderA_menu;
struct sDisplay Display;
struct KeyBoard keyBoard;


//FX
fastReverb reverb(1300);
fastTap tap1(reverb.sizes[0], 4);
fastTap tap2(reverb.sizes[1], 8);


//ISR Varibales 
int16_t master_out, fMaster_out, n;
uint16_t ufMaster_out;
int32_t nBuffer[mN+3];
uint8_t low_byte, high_byte;

//Encoder variables 
volatile int8_t enc1Value, enc2Value;
volatile uint8_t enc1State = 0, enc2State = 0;

//Utility
uint8_t poll_enable, Button, mono_switch;

//simulation variables (active low)
uint8_t keyboard_sim[8] = {1,1,1,1, 1,1,1,1};

//Interval Timers 
IntervalTimer DACsampleRate;
IntervalTimer UtilityTimer;

void setup(){
    spi4teensy3::init(0,0,0); 
    //configure frequency matrix
    createNoteTable(SAMPLERATE);
    //configure ADSR wavetable
    ADSR_configure(4095,GATE,SAMPLERATE, 96,0,gate);
    
    Serial.begin(9600);
    
    //configure channel IDs
    channel_init(&channel0, 0);
    channel_init(&channel1, 1);
    channel_init(&channel2, 2);
    channel_init(&channel3, 3);
    channel_init(&channel4, 4);
    channel_init(&channel5, 5);
    channel_init(&channel6, 6);
    channel_init(&channel7, 7);
    
    pinMode(ENC1A, INPUT); //encoder 1 A pin
    pinMode(ENC1B, INPUT); //encoder 1 B pin
    pinMode(ENC1_BUT, INPUT); //encoder 1 button
    pinMode(pKEYS, INPUT); //input for keys
    pinMode(a0, OUTPUT); //multiplexer a0 
    pinMode(a1, OUTPUT); //multiplexer a1
    pinMode(a2, OUTPUT); //multiplexer a2
    pinMode(DAC_enable, OUTPUT); //chip select for DAC output

    digitalWrite(ENC1_BUT, HIGH); //enable pull up resistor for encoder button
    
    DACsampleRate.begin(WaveformGen, 22.675);  // write value to ADC every sample period
    DACsampleRate.priority(0);
    SPI.usingInterrupt(DACsampleRate);
    //1KHz timer to provide consistent timing for various functions
    UtilityTimer.begin(Timer, 1000);
    //attach interrrupt to encoder pins
    attachInterrupt(digitalPinToInterrupt(ENC1A), enc1A, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC1B), enc1B, CHANGE);
    
    myLeds.clear();
    myLeds.setBrightness(1);

    adc->setResolution(12); //Write analog value from 0 to 4095
    adc->setConversionSpeed(ADC_HIGH_SPEED);
    adc->setSamplingSpeed(ADC_HIGH_SPEED);
 
    // First reassign pin 13 to the default so that it is not SCK
    CORE_PIN13_CONFIG = PORT_PCR_MUX(0);
    CORE_PIN12_CONFIG = PORT_PCR_MUX(0);
    // and then reassign pin 14 to SCK
    CORE_PIN14_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);

}

void loop(){
  //MAIN LOOP------------------------------------------------
 
  
        //READ USER INPUT
        //set ADSR parameters (read knob)
        adsr_values[0] = 2000; //set attack level (1:2000 (length))
        adsr_values[1] = 100; //set decay level (1:2000 (length))
        adsr_values[2] = 4000; //set sustain level (1:4095 (max amplitude))
        adsr_values[3] = 10; //set release value (1:2000 (length))
        
        //Main Settings: Key/Mode/Scale/Octave
        //Main_control.key = 0; //D
        Main_control.octave =  -12; //no octave offset
        //Main_control.scale = 1; //dorian

        //Main_control.harmonizer = 0;
        //Main_control.harmony = 11; //no harmony
        
        Main_control.osc1 = 0; //off
        Main_control.osc2 = 0;
        Main_control.osc1_knob = 62; //center C
        Main_control.osc2_knob = 500; //halfway
        Main_control.waveform[0] = 3; //square
        Main_control.waveform[1] = 3; //square
        
        //Arpeggiator Settings
        Arpeggiator.Active = 0; //arpeggiator off
        Arpeggiator.rate = 10000;
        //Arpeggiator.Mode = 2; //rise
        //Arpeggiator.octave = 2;
        
        //ADSR Auto Trigger Settings
        adsr_trigger = 0;
        adsr_trigger_rate = 200;

        //monophonic or polyphonic
        mono_switch = 0;
        keyBoard.rate = 40;
        if(mono_switch == 1){
          if(Arpeggiator.Active == 1 && Main_control.user_mode != 1){
            //disable mono mode so arpeggiator works 
            Main_control.mono = 0;
          }
          else{
            Main_control.mono = 1;
          }
        }

        //FX
        Main_control.reverb = 1;
        reverb.a = 3;
        
        //LowPass Filter Settings
        //If sinewave chosen, higher order LPF
        if(Main_control.waveform[0] == 3 && Main_control.waveform[1] == 3){
          n = 16;
        }
        else{
          n = 1;
        }
        
        //start of main algorithms
        //-----------------------------------------------------------------

        //configure menu
        menu_configure(&encoderA_menu, &Main_control, &Arpeggiator, &enc1Value, ENC1_BUT, &Display, &channelmono, &keyBoard);
        if(Display.Update == 1 || Display.Update == 2){
          //configure display
          display_configure(&encoderA_menu, &Main_control, &Arpeggiator, &Display);
        }
        //configure reference frequency
        Main_control.reference_freq = reference_frequency(&Main_control);
        //configure operation mode
        mode_configure(&Main_control, &Arpeggiator);

        if(poll_enable == 1){
          //READ KEYS AND SWITCHES-----------------------------------------------------
          //set channel 0: 000
          digitalWriteFast(a0, LOW);
          digitalWriteFast(a1, LOW); 
          digitalWriteFast(a2, LOW);  
          delayMicroseconds(mDELAY);
          //read pin
          Button = digitalRead(pKEYS);
          //polyphonic mode
          channel0.keystatus ^= (-(Button)^channel0.keystatus)&(1<<0);
          //monophonic mode
          keyBoard.current ^= (-(Button)^keyBoard.current)&(1<<0);
          
          //set channel 1: 001
          digitalWriteFast(a0, HIGH);
          digitalWriteFast(a1, LOW);
          digitalWriteFast(a2, LOW);
          delayMicroseconds(mDELAY);
          //read pin
          Button = digitalRead(pKEYS);
          //polyphonic mode
          channel1.keystatus ^= (-(Button)^channel1.keystatus)&(1<<0);
          //monophonic mode
          keyBoard.current ^= (-(Button)^keyBoard.current)&(1<<1);
          
          //set channel 2: 010
          digitalWriteFast(a0, LOW);
          digitalWriteFast(a1, HIGH);
          digitalWriteFast(a2, LOW);
          delayMicroseconds(mDELAY);
          //read pin
          Button = digitalRead(pKEYS);
          //polyphonic mode
          channel2.keystatus ^= (-(Button)^channel2.keystatus)&(1<<0);
          //monophonic mode
          keyBoard.current ^= (-(Button)^keyBoard.current)&(1<<2);

          //set channel 3: 011
          digitalWriteFast(a0, HIGH);
          digitalWriteFast(a1, HIGH);
          digitalWriteFast(a2, LOW);
          delayMicroseconds(mDELAY);
          //read pin
          Button = digitalRead(pKEYS);
          //polyphonic mode
          channel3.keystatus ^= (-(Button)^channel3.keystatus)&(1<<0);
          //monophonic mode
          keyBoard.current ^= (-(Button)^keyBoard.current)&(1<<3);

          //set channel 4: 100
          digitalWriteFast(a0, LOW);
          digitalWriteFast(a1, LOW);
          digitalWriteFast(a2, HIGH);
          delayMicroseconds(mDELAY);
          //read pin
          Button = digitalRead(pKEYS);
          //polyphonic mode
          channel4.keystatus ^= (-(Button)^channel4.keystatus)&(1<<0);
          //monophonic mode
          keyBoard.current ^= (-(Button)^keyBoard.current)&(1<<4);
 
          //set channel 5: 101
          digitalWriteFast(a0, HIGH);
          digitalWriteFast(a1, LOW);
          digitalWriteFast(a2, HIGH);
          delayMicroseconds(mDELAY);
          //read pin
          Button = digitalRead(pKEYS);
          //polyphonic mode
          channel5.keystatus ^= (-(Button)^channel5.keystatus)&(1<<0);
          //monophonic mode
          keyBoard.current ^= (-(Button)^keyBoard.current)&(1<<5);

          //set channel 6: 110
          digitalWriteFast(a0, LOW);
          digitalWriteFast(a1, HIGH);
          digitalWriteFast(a2, HIGH);
          delayMicroseconds(mDELAY);
          //read pin
          Button = digitalRead(pKEYS);
          //polyphonic mode
          channel6.keystatus ^= (-(Button)^channel6.keystatus)&(1<<0);
          //monophonic mode
          keyBoard.current ^= (-(Button)^keyBoard.current)&(1<<6);

          //set channel 7: 111
          digitalWriteFast(a0, HIGH);
          digitalWriteFast(a1, HIGH);
          digitalWriteFast(a2, HIGH);
          delayMicroseconds(mDELAY);
          //read pin
          Button = digitalRead(pKEYS);
          //polyphonic mode
          channel7.keystatus ^= (-(Button)^channel7.keystatus)&(1<<0);
          //monophonic mode
          keyBoard.current ^= (-(Button)^keyBoard.current)&(1<<7);

          //configure chanID for monophonic mode
          mono_keyboard_configure(&channelmono, &keyBoard);
          //activate adsr envelope, all keys will simulate as one
          if(keyBoard.count >= 1){
            channelmono.keystatus ^= (-1^channelmono.keystatus)&(1<<0);
          }
          else if(keyBoard.count == 0){
            channelmono.keystatus ^= (-0^channelmono.keystatus)&(1<<0);
          }

          //If auto_tigger is on
          if(adsr_trigger == 1){
              ADSR_auto_trigger(&channel0);
              ADSR_auto_trigger(&channel1);
              ADSR_auto_trigger(&channel2);
              ADSR_auto_trigger(&channel3);
              ADSR_auto_trigger(&channel4);
              ADSR_auto_trigger(&channel5);
              ADSR_auto_trigger(&channel6);
              ADSR_auto_trigger(&channel7);
              ADSR_auto_trigger(&channelmono);
          }
        
          //Configure ADSR register for each channel
          ADSR_CR_configure(&channel0);
          ADSR_CR_configure(&channel1);
          ADSR_CR_configure(&channel2);
          ADSR_CR_configure(&channel3);
          ADSR_CR_configure(&channel4);
          ADSR_CR_configure(&channel5);
          ADSR_CR_configure(&channel6);
          ADSR_CR_configure(&channel7);
          ADSR_CR_configure(&channelmono);

          //Clear poll_enable
          poll_enable = 0;
        }
        
        //Update ADSR envelope
        ADSR(&channel0, &pre_master_out);
        ADSR(&channel1, &pre_master_out);
        ADSR(&channel2, &pre_master_out);
        ADSR(&channel3, &pre_master_out);
        ADSR(&channel4, &pre_master_out);
        ADSR(&channel5, &pre_master_out);
        ADSR(&channel6, &pre_master_out);
        ADSR(&channel7, &pre_master_out);
        ADSR(&channelmono, &pre_master_out);
        //update arpeggiator
        if(Arpeggiator.Active == 1){
            arpeggiate(&Arpeggiator);
        }
        
        //-----------------------------------------------------------
        //Implement Main Algorithms

        //determine user mode and configure channels
        switch(Main_control.user_mode){
            case 0: //normal mode
                if(Main_control.mono == 1){
                    normal_mode(&channelmono, &Main_control, &keyBoard, Arpeggiator.oct_count);
                }
                else{
                    normal_mode(&channel0, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    normal_mode(&channel1, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    normal_mode(&channel2, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    normal_mode(&channel3, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    normal_mode(&channel4, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    normal_mode(&channel5, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    normal_mode(&channel6, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    normal_mode(&channel7, &Main_control, &keyBoard, Arpeggiator.oct_count);
                }
                break;
                
            case 1: //harmonizer
                if(Main_control.mono == 1){
                    harmonizer(&channelmono, &Main_control, &keyBoard, Arpeggiator.oct_count);
                }
                else{
                    harmonizer(&channel0, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    harmonizer(&channel1, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    harmonizer(&channel2, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    harmonizer(&channel3, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    harmonizer(&channel4, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    harmonizer(&channel5, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    harmonizer(&channel6, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    harmonizer(&channel7, &Main_control, &keyBoard, Arpeggiator.oct_count);
                }
                break;

            case 2: //osc2 is on
                if(Main_control.mono == 1){
                    osc2_mode(&channelmono, &Main_control, &keyBoard, Arpeggiator.oct_count);
                }
                else{
                    osc2_mode(&channel0, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    osc2_mode(&channel1, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    osc2_mode(&channel2, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    osc2_mode(&channel3, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    osc2_mode(&channel4, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    osc2_mode(&channel5, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    osc2_mode(&channel6, &Main_control, &keyBoard, Arpeggiator.oct_count);
                    osc2_mode(&channel7, &Main_control, &keyBoard, Arpeggiator.oct_count);
                }
                break;
        }
}

//Interrupt Service Routines------------------------------------------------------------------------------------

//Waveform generator at sample rate 
void WaveformGen()
{
    //reset master_out
    master_out = 0;
    
    //polyphonic
    switch(Main_control.mono){
      case 0: //polyphonic
        //clear active channel count
        channel_oscillator(&channel0, &pre_master_out, &Arpeggiator, &Main_control);
        channel_oscillator(&channel1, &pre_master_out, &Arpeggiator, &Main_control);
        channel_oscillator(&channel2, &pre_master_out, &Arpeggiator, &Main_control);
        channel_oscillator(&channel3, &pre_master_out, &Arpeggiator, &Main_control);
        channel_oscillator(&channel4, &pre_master_out, &Arpeggiator, &Main_control);
        channel_oscillator(&channel5, &pre_master_out, &Arpeggiator, &Main_control);
        channel_oscillator(&channel6, &pre_master_out, &Arpeggiator, &Main_control);
        channel_oscillator(&channel7, &pre_master_out, &Arpeggiator, &Main_control);
        
        if(Arpeggiator.Active == 1){
            //arpeggiate active channels
            master_out = arpeggiate_ISR(&pre_master_out, &Arpeggiator, &Main_control, &channelmono, &keyBoard);
        }
        //normal mixing
        else{
            //mix into master channel
            for(uint8_t i = 0; i<8; i++){
                if(pre_master_out.Active[i] == 1){
                    master_out += pre_master_out.pre_master[i];
                }
            }
        }
      break;
      
      case 1: //monophonic
        channel_oscillator(&channelmono, &pre_master_out, &Arpeggiator, &Main_control);
        if(Arpeggiator.Active == 1){
            //arpeggiate active channels
            master_out = arpeggiate_ISR(&pre_master_out, &Arpeggiator, &Main_control, &channelmono, &keyBoard);
        }
        else{
          //normal mixing
          master_out = pre_master_out.pre_master[channelmono.chanID];
        }
      break;
    }

    //Reverb effect
    if(Main_control.reverb == 1){
      master_out = reverb.reverberate(master_out, &tap1, &tap2);
    }
    
    //moving average to remove harmonic distortion from sinewave
    if(n == 0){
      ufMaster_out = (uint16_t)((master_out) + 0x7FFF);
    }
    else{
      fMaster_out = LPF(master_out, nBuffer, n);
      ufMaster_out = (uint16_t)((fMaster_out) + 0x7FFF);
    }
    
    
    //separate into bytes for SPI transfer
    high_byte = ufMaster_out & 0xFF;
    low_byte = ufMaster_out >> 8;
    
    //write to DAC via SPI
    digitalWriteFast(DAC_enable, LOW);
    spi4teensy3::send(low_byte);
    spi4teensy3::send(high_byte);
    digitalWriteFast(10, HIGH);
}

// Timer function
//Provdes timing/polling for adsr_auto_trigger, button polling, and updating the display
void Timer(){
  //Button Polling
  poll_enable = 1;

  //glide timer
  keyBoard.timer += 1;
  if(keyBoard.timer >= 5){
    //reset
    keyBoard.timer = 0;
    //glide enable
    keyBoard.glide_enable = 1;
  }

  //Display Timer
  //If delay timer activated 
  if(((Display.Update>>2)&1) == 1){ //if bit 2 is high, delay timer activated 
    Display.timer += 1;
    //check overflow 
    if(Display.timer >= Display.Delay){
      //clear
      Display.timer = 0;
      //enable display update 
      Display.Update = Display.type; //set bit 0 or 1 high
    }
  }
}

//ISRs for Encoders------------------------------------------
//Encoder 1
void enc1A(){
  if(digitalReadFast(ENC1B) == enc1State){
    enc1Value+=1;
    enc1State ^= 1;
    //reset and update display
    Display.index = 2;
    Display.Update = 2; 
    Display.count = 0;
    Display.timer = 0;
    Display.type = 2;
    Display.repeat = 0;
  }
  enc1State ^= 1;
}

void enc1B(){
  if(digitalReadFast(ENC1A) == enc1State){
    enc1Value-=1;
    enc1State ^= 1;
    //reset and update display
    Display.index = 2;
    Display.Update = 2; 
    Display.count = 0;
    Display.timer = 0;
    Display.type = 2;
    Display.repeat = 0;
  }
  enc1State ^= 1;
}
    
        
       
      
      
   
