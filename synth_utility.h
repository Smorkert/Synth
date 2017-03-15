//
//  synth_utility.h
//  Mini Arcade Synth
//
//  Created by Steven Morkert on 3/8/17.
//  Copyright (c) 2017 Steven Morkert. All rights reserved.
//

#ifndef Mini_Arcade_Synth_synth_utility_h
#define Mini_Arcade_Synth_synth_utility_h

#include "waveforms.h"

//Frequency Generation Macros & Parameters
#define SAMPLE_RATE 48000.0
#define MIDI_NOTES 128

uint32_t SAMPLES_PER_CYCLE_FIXEDPOINT;
uint16_t SAMPLES_PER_CYCLE = 916;
float TICKS_PER_CYCLE;
uint32_t nMidiPhaseInc[MIDI_NOTES];

//Declare varibales
uint16_t gate[2000+3]; //envelope table
uint16_t adsr_values[4]; //adsr parameters, timers, info
uint32_t SPCFP; //SAMPLES_PER_CYCLE_FIXEDPOINT

/*
 user_mode = 0:normal, 1:harmonizer, 2:osc2 on
 key = value between 0-11 for key offset
 octave = multiple of 12 to +/- for reference frequency
 scale = value between 0-11 for scale/mode (ionian, dorian, etc.)
 osc1 = 0:off, 1:on. if osc1 swich high, reference frequency is determined by the osc1_knob
 osc1_knob = value between 0-119 (midi notes)
 osc2_knob = value between 0-1023
 reference_freq = Middle C(60) + key + octave or osc1_knob
 Mode = main settings for channel_osc function: normal/harmonizer:0 , osc2:1
 harmony = harmony selected in harmonizer mode (0-13)
 adsr_trigger_rate = period of ADSR auto trigger, value between 0-65535
 adsr_trigger = 0:off, 1:on
 arp_map[8] = map of active channels with ID
 arp_rate = arpeggiator rate, value between 0-65535
 arp_timer = arpeggiator timer, value between 0-65535
 arp_mode = arpeggiator mode - 0:rise, 1:fall, 2:both
 waveform[2]; //waveform = {primary, oscillator2} 0:square, 1:triangle, 2:saw, 3:sine
 */
uint16_t adsr_trigger_rate, adsr_trigger;
uint16_t arpeg_timer, arpeg_rate;

//channel structure for function
struct channel
{
    uint8_t keystatus, ADSR_cr, chanID; //button/key status, ADSR control register
    uint16_t ADSR_par[6]; //adsr parameters, timers, info
    uint32_t ulPhaseIncrement[5]; //{freq1, freq2, freq3, freq4}
    uint32_t ulPhaseAccumulator[4]; //{freq1, freq2, freq3, freq4}
    uint16_t trig_timer;
    int8_t QTY;
};

struct main_control
{
    uint8_t user_mode, key, scale, osc1, osc2, reference_freq, osc_mode, harmony, waveform[2], harmonizer;
    int8_t octave;
    uint16_t osc2_knob, osc1_knob, scaleDeg;
};

struct pre_mix{
    int16_t pre_master[8]; //[pre_master_out0,..,pre_master_out8]
    uint8_t active_chan[8]; //[active0,..active8]
};

struct arpeggiator
{
    uint16_t Timer, rate;
    uint8_t arp_map[8], state, mode, active, update, octave;
    int8_t index, oct_count;
    int16_t wavecount;
};


uint8_t diaModes[13][8] = {
    //Ionian
    {0, 2, 4, 5, 7, 9, 11, 12},
    //Dorian
    {0, 2, 3, 5, 7, 9, 10, 12},
    //Phrygian
    {0, 1, 3, 5, 7, 8, 10, 12},
    //Lydian
    {0, 2, 4, 6, 7, 9, 11, 12},
    //Mixolydian
    {0, 2, 4, 5, 7, 9, 10, 12},
    //Aeolian
    {0, 2, 3, 5, 7, 8, 10, 12},
    //Locrian
    {0, 1, 3, 5, 6, 8, 10, 12},
    //Minor Pentatonic
    {0, 3, 5, 7, 10, 12, 15, 17},
    //Major Pentatonic
    {0, 2, 4, 7, 9, 12, 14, 16},
    //Egyptian
    {0, 2, 5, 7, 10, 12, 14, 17},
    //Arabic
    {0, 1, 4, 5, 7, 8, 11, 12},
    //Whole Tone
    {0, 2, 4, 6, 8, 10, 12, 14},
    //delete offset
    {0, 0, 0, 0, 0, 0, 0, 0},
};

uint8_t harmonies[14][9] = {
    //{# of frequencies, [f1, f1, f3, f4], [oct_offset1, oct_offset2 ,oct_offset3, oct_offset4]}
    //2nd
    {2, 0,1,0,0, 0,0,0,0},
    //3rd
    {2, 0,2,0,0, 0,0,0,0},
    //4th
    {2, 0,3,0,0, 0,0,0,0},
    //5th
    {2, 0,4,0,0, 0,0,0,0},
    //6th
    {2, 0,5,0,0, 0,0,0,0},
    //7th
    {2, 0,6,0,0, 0,0,0,0},
    //octave
    {2, 0,7,0,0, 0,0,0,0},
    //9th
    {2, 0,1,0,0, 0,12,0,0},
    //10th
    {2, 0,2,0,0, 0,12,0,0},
    //triad - basic
    {3, 0,2,4,0, 0,0,0,0},
    //triad - different voicing
    {4, 0,4,2,0, 0,0,12,24},
    //triad - w/ 7th - basic
    {4, 0,2,4,6, 0,0,0,0},
    //triad -w/ 7th - different voicing
    {4, 0,4,2,6, 0,0,12,12},
    //drone
    {4, 0,4,0,4, 0,0,12,12},
};

//Generate frequencies and time increments
//Fill the note table with the phase increment values we require to generate the note
void createNoteTable(float fSampleRate)
{
    SAMPLES_PER_CYCLE_FIXEDPOINT  = (uint32_t)SAMPLES_PER_CYCLE<<21;
    SPCFP = SAMPLES_PER_CYCLE_FIXEDPOINT;
    TICKS_PER_CYCLE = (float)((float)SAMPLES_PER_CYCLE_FIXEDPOINT/(float)SAMPLE_RATE);
    for(uint32_t unMidiNote = 0;unMidiNote < MIDI_NOTES;unMidiNote++)
    {
        // Correct calculation for frequency
        float fFrequency = ((pow(2.0,(unMidiNote-69.0)/12.0)) * 440.0);
        nMidiPhaseInc[unMidiNote] = fFrequency*TICKS_PER_CYCLE;
    }
}



/* ADSR configure, ADRS_configure(amplitude, length, sample rate, adsr timer, type, gate)
 This function configures and generates an array of values used for
 an adsr gate envelope. In use the ADSR() function, it uses the same
 gate shape to generate all phases of an ADSR envelope. The user can
 select between type: 0: sine gate, or type 1: linear. This defines the
 type of gating.
 -----------------------------------------------------------------------
 gate = [amplitude, adsr timer, n1, n2,...nX]
 adsr timer = multiple of sampling rate to enable adsr at slower rate than Fs
 needs to be even. i.e. Fs = 48kHz, t = 48, 48kHz/48 = 1000 >> envelope will update 1000
 times a second (1KHz). Faster rates will need longer envelope tables.
 
 1) declare uint16_t gate[length+2];
 
 */

float ADSR_configure(uint16_t amp, uint16_t L, uint16_t Fs, uint16_t t, uint8_t type, uint16_t *gate){
    float rate = amp/L;
    switch(type){
        case 0://sine
            for(uint16_t i = 0; i<L;i++){
                gate[i+3] = (uint16_t)(sin(i*(acos(-1)/2)/L)*(amp-1)+1)+0.5;
            }
            break;
        case 1:
            for(uint16_t i = 0; i<L;i++){
                gate[i+3] = (uint16_t)(rate*i+0.5)+1;
            }
            break;
            
    }
    gate[0] = amp;
    gate[1] = L;
    gate[2] = Fs/t;
    return 0;
}

/* ADSR control register configure, ADSR_CR_configure(keymap, adsr_cr)
 This function receives the current bit masked keyboard mapping and
 configures the ADSR contorl register accordingly. It triggers the ADSR
 envelope by discerning button transitions from H-L. To function correctly,
 bit 0 in keystatus must be written 1 or 0 corresponding to button press/release.
 -------------------------------------------------------------------------
 keystatus = [x,x,x,x,x,x,previous state,current state];
 adsr_cr = [on/off, t_LH, t_HL, attack_on, decay_on, sustain_on, release_on, adsr_enable];
 
 */

uint16_t ADSR_CR_configure(struct channel *chan){
    //compare current keystatus to previous, "if different"
    if(((chan->keystatus>>0)&1) != ((chan->keystatus>>1)&1)){
        //if previous was 0 set LH transition bit, indicates new button press
        if(((chan->keystatus>>1)&1) == 0){
            chan->ADSR_cr |= (1<<0);//set on/off high
            chan->ADSR_cr |= (1<<1);//set t_LH high
            chan->ADSR_cr |= (1<<7);//set enable bit high (over-ride timer)
        }
        if(((chan->keystatus>>0)&1) == 0){
            chan->ADSR_cr &= ~(1<<0); //set on/off low
            chan->ADSR_cr |= (1<<2); //set t_HL high
            chan->ADSR_cr |= (1<<7);//set enable bit high (over-ride timer)
        }
    }
    //store current keymap in previous
    chan->keystatus ^= ((-((chan->keystatus>>0)&1))^chan->keystatus)&(1<<1);
    return 0;
}


/* ADSR Envelope, ADSR(input, channel)
 This function implements an adsr gating on an input signal. it is configured with
 ADRS_configure and controled with ADSR_CR_configure. works in part with struct channels
 ----------------------------------------------------------------------------------
 //chan.ADSR_par = [cA, cD, cR, timer, envelope, p_sustain] *each key
 //adsr_values = [attack, decay, sustain, release] *global
 //chan.ADSR_cr = [on/off, t_LH, t_HL, attack_on, decay_on, sustain_on, release_on, adsr_enable]; *each key
 //gate = [amplitude, length, adsr timer, n1, n2,...nX] *global
 
 example:
 
 //Declare varibales:
 //These are GLOBAL, must have titled "gate" and "adsr_values" to work in function
 uint16_t gate[2000+3]; //envelope table
 uint16_t adsr_values[4]; //attack, sustain, decay, release
 
 struct channel channel0,..,channelX;
 
 int main(){
 
 //configure ADSR wavetable
 ADSR_configure(4095,2000,SAMPLE_RATE, 96,0,gate);
 
 //simulate button press, where x is 1 or 0
 channel0.keystatus ^= (-x^channel0.keystatus)&(1<<0);
 //configure adsr control register
 ADSR_CR_configure(&channel0);
 
 //set ADSR parameters
 adsr_values[0] = 100; //set attack level (1:2000 (length))
 adsr_values[1] = 100; //set decay level (1:2000 (length))
 adsr_values[2] = 3500; //set sustain level (1:4095 (max amplitude))
 adsr_values[3] = 40; //set release value (1:2000 (length))
 
 //update ADSR envelope if ready
 ADSR(&channel0);
 
 ISR{
 //gate input waveform
 output = ADSR_ISR(input, &channel0);
 }
 */

//ADSR function to be used in ISR

int16_t ADSR_ISR(int16_t Input, struct channel *chan){
    int16_t ntemp16;
    int32_t ntemp32;
    //increment adsr timer
    chan->ADSR_par[3] += 1;
    //check if full
    if(chan->ADSR_par[3] >= gate[2]){
        chan->ADSR_par[3] = 0;
        chan->ADSR_cr |= (1<<7);//set adsr_enable high
    }
    //combine Input+gate[0]
    ntemp16 = (int16_t)(Input+gate[0]);
    ntemp32 = ntemp16*(chan->ADSR_par[4]<<1);
    //reutrn gated input
    return (int16_t)(ntemp32/(gate[0]<<1)-chan->ADSR_par[4]);
}

//ADSR function to be used outside of ISR

void ADSR(struct channel *chan){
    /*GLOBAL VARIBALES (must have same name):
     1) adsr_values = [attack, decay, sustain, release];
     2) gate = [amplitude, length, adsr timer, n1, n2,...nX];
     LOCAL VARIBALES:
     1) chan.ADSR_par = [cA, cD, cR, timer, envelope, p_sustain];
     2) chan.ADSR_cr = [on/off, t_LH, t_HL, attack_on, decay_on, sustain_on, release_on, adsr_enable];
     3) Input
     */
    uint32_t untemp32;
    
    //if adsr_enable high, update envelope
    if(((chan->ADSR_cr>>7)&1) == 1){
        //KEY PRESSED--------------------------------------------------------------
        //if button pressed...
        if(((chan->ADSR_cr>>0)&1) == 1){
            //LOW-HIGH TRANSITION--------------------------------------------------
            //if t_LH set high
            if(((chan->ADSR_cr>>1)&1) == 1){
                chan->ADSR_par[0] = 3; //reset to beginning of gate table
                chan->ADSR_par[1] = 3;
                chan->ADSR_par[2] = 3;
                chan->ADSR_cr &= ~(1<<1); //set t_LH low
                chan->ADSR_cr |= (1<<3);//set attack_on high
            }
            //ATTACK---------------------------------------------------------------
            //if attack_on set high
            if(((chan->ADSR_cr>>3)&1) == 1){
                chan->ADSR_par[4] = gate[chan->ADSR_par[0]]; //set current envelope value to cA
                chan->ADSR_par[0] += adsr_values[0]; //increment attack value
                if(chan->ADSR_par[0] >= gate[1]){
                    chan->ADSR_cr &= ~(1<<3); //set attack_on low
                    chan->ADSR_cr |= (1<<4);//set decay_on high
                }
            }
            //DECAY-----------------------------------------------------------------
            //If decay_on set high
            if(((chan->ADSR_cr>>4)&1) == 1){
                //set current envelope value
                untemp32 = ((gate[0]-gate[chan->ADSR_par[1]])-1)*(gate[0]-adsr_values[2]);
                chan->ADSR_par[4] = (uint16_t)((untemp32/(gate[0]-1))+adsr_values[2]);
                chan->ADSR_par[1] += adsr_values[1];
                if(chan->ADSR_par[1] >= gate[1]){
                    chan->ADSR_cr &= ~(1<<4); //set decay_on low
                    chan->ADSR_cr |= (1<<5);//set sustain_on high
                }
            }
            //SUSTAIN---------------------------------------------------------------
            //If sustain_on set high
            if(((chan->ADSR_cr>>5)&1) == 1){
                //set current envelope value
                chan->ADSR_par[4] = adsr_values[2];
            }
        }
        //KEY RELEASED--------------------------------------------------------------
        //if button released...
        if(((chan->ADSR_cr>>0)&1) == 0){
            //HIGH-LOW TRANSITION--------------------------------------------------
            //if t_HL set high
            if(((chan->ADSR_cr>>2)&1) == 1){
                chan->ADSR_par[5] = chan->ADSR_par[4]; //set "off" sustain to previous envelope value
                chan->ADSR_cr &= ~(1<<5); //set sustain_on low
                chan->ADSR_cr &= ~(1<<4); //set decay_on low
                chan->ADSR_cr &= ~(1<<3); //set attack_on low
                chan->ADSR_cr &= ~(1<<2); //set t_HL low
                chan->ADSR_cr |= (1<<6);//set release_on high
            }
            //RELEASE---------------------------------------------------------------
            //if release_on set high
            if(((chan->ADSR_cr>>6)&1) == 1){
                //set current envelope value
                //use fast multiply function
                untemp32 = ((gate[0]-gate[chan->ADSR_par[2]])-1)*chan->ADSR_par[5];
                chan->ADSR_par[4] = (uint16_t)(untemp32/gate[0]-1);
                chan->ADSR_par[2] += adsr_values[3];
                if(chan->ADSR_par[2] >= gate[1]){
                    chan->ADSR_cr &= ~(1<<6); //set release_on low
                }
            }
            
        }
        chan->ADSR_cr &= ~(1<<7); //set adsr_enable low
    }
}

/* Channel Oscillator channel_oscillator(channel)
 This function receives a channel structure then configures and outputs a normailzed amplitude
 value to the master out. Uses ADSR function as well. Steps below:
 1) Phase accumulation for each frequency present
 2) Grab amplitude info based off phase value for each frequency from correct wavetable
 3) Add amplitude values if more than one and then normalize
 4) Gate through ADSR function
 5) Output value to master output
 ----------------------------------------------------------------------------------------------
 */

void channel_oscillator(struct channel *chan, struct pre_mix *pre_mast, struct arpeggiator *arpeg, struct main_control *main){
    //GLOBAL varibales used: SPCFP, 4 waveforms (squarewave, trianglewave, sawwave, sinewave)
    //if channel is active gating will still be occuring, if not skip it
    if(chan->ADSR_par[4] >=1 || ((chan->ADSR_cr>>0)&1) == 1){
        int16_t Output=0, output_final = 0;
        
        //if harmonizer and arpeggiator, special calculations need to occur
        if(arpeg->active == 1 && main->user_mode == 1){
            chan->ulPhaseAccumulator[0] += chan->ulPhaseIncrement[arpeg->index];// 32 bit phase increment
            //check overflow
            if(chan->ulPhaseAccumulator[0] > SPCFP){
                //carry the remainder of the phase accumulator
                chan->ulPhaseAccumulator[0] -= SPCFP;
            }
            switch(main->waveform[0]){
                case 0: //squarewave
                    Output=(int16_t)squarewave[(chan->ulPhaseAccumulator[0]>>21)];
                    break;
                case 1: //trianglewave
                    Output=(int16_t)trianglewave[(chan->ulPhaseAccumulator[0]>>21)];
                    break;
                case 2: //sawwave
                    Output=(int16_t)sawwave[(chan->ulPhaseAccumulator[0]>>21)];
                    break;
                case 3: //sinewave
                    Output=(int16_t)sinewave[(chan->ulPhaseAccumulator[0]>>21)];
                    break;
            }
        }
        
        //arpeggiator off
        else{
            //phase increment for each frequency present in channel
            for(uint8_t i = 0; i<chan->QTY;i++){
                chan->ulPhaseAccumulator[i] += chan->ulPhaseIncrement[i];// 32 bit phase increment
                //check overflow
                if(chan->ulPhaseAccumulator[i] > SPCFP){
                    //carry the remainder of the phase accumulator
                    chan->ulPhaseAccumulator[i] -= SPCFP;
                }
            }
            switch(main->osc_mode){
                case 0: //if normal mode or harmonizer mode (1+ frequencies, same waveform)
                    for(uint8_t i = 0;i<chan->QTY;i++){ //loop for quantity of frequencies
                        switch(main->waveform[0]){
                            case 0: //squarewave
                                Output+=(int16_t)squarewave[(uint16_t)(chan->ulPhaseAccumulator[i]>>21)];
                                break;
                            case 1: //trianglewave
                                Output+=(int16_t)trianglewave[(uint16_t)(chan->ulPhaseAccumulator[i]>>21)];
                                break;
                            case 2: //sawwave
                                Output+=(int16_t)sawwave[(uint16_t)(chan->ulPhaseAccumulator[i]>>21)];
                                break;
                            case 3: //sinewave
                                Output+=(int16_t)sinewave[(uint16_t)(chan->ulPhaseAccumulator[i]>>21)];
                                break;
                        }
                    }
                    //normailze and scale
                    Output = Output/chan->QTY;
                    break;
                    
                case 1: //oscllator 2 is activated, 2 different possible waveforms
                    for(uint8_t i = 0;i<2;i++){ //loop for quantity of frequencies
                        switch(main->waveform[i]){
                            case 0: //squarewave
                                Output+=(int16_t)squarewave[(uint16_t)(chan->ulPhaseAccumulator[i]>>21)];
                                break;
                            case 1: //trianglewave
                                Output+=(int16_t)trianglewave[(uint16_t)(chan->ulPhaseAccumulator[i]>>21)];
                                break;
                            case 2: //sawwave
                                Output+=(int16_t)sawwave[(uint16_t)(chan->ulPhaseAccumulator[i]>>21)];
                                break;
                            case 3: //sinewave
                                Output+=(int16_t)sinewave[(uint16_t)(chan->ulPhaseAccumulator[i]>>21)];
                                break;
                        }
                    }
                    Output = Output>>1; //divide by 2
                    break;
            }
        }
        //ADSR Gate result and output
        output_final  = ADSR_ISR(Output, chan);
        pre_mast->pre_master[chan->chanID] = output_final;
        pre_mast->active_chan[chan->chanID] = ((chan->ADSR_cr>>0)&1);
    }
    else{
        //if channel is inactive, this value is output signaling master channel to skip.
        //value will never exceed -4095 to 4095, 0x2FFF = 12287
        pre_mast->pre_master[chan->chanID] = 0x2FFF;
    }
}

/* Reference frequency calculator reference_frequency(main_control)
 This function calculates the reference frequency from the user input
 if the free pitch knob (osc1) is activated, special calculations need to occur to 
 adjust the pitch to the relative scale. osc1_knob range should be from 12-119
------------------------------------------------------------------------------------------
 */
int16_t reference_frequency(struct main_control *main){
    uint16_t B,div_f,div_max; //modulus operator variables
    uint16_t ref_freq;
    float A;
    //if osc1 switch on, determine reference frequency
    if(main->osc1 == 1){
        if(main->scale  == 7 || main->scale == 8 || main->scale == 9){
            div_f = 5;
            div_max = 45;
        }
        else if(main->scale == 11){
            div_f = 6;
            div_max = 54;
        }
        else{
            div_f = 7;
            div_max = 63;
        }
        
        A = ((main->osc1_knob-12.0)*div_max)/(119.0-12.0);//scale value to 0-9*(octave range)
        B = A/div_f; //determine octave
        main->scaleDeg = A-div_f*B; //remainder (scale degree)
        ref_freq = (B+1)*12 + diaModes[main->scale][main->scaleDeg]; //actual adjusted note (0-119)
        if(main->user_mode != 1){
            main->scale = 12; //all keys/buttons will no longer have an offset and contain the same pitch
        }
    }
    else{
        ref_freq = 60 + main->key + main->octave;
    }
    return ref_freq;
}
                            //scale, osc1, osc1_knob, diaModes

/* Channel Harmonizer harmonizer(channel, channelID)
 This function configures the harmonies present in each channel based on user input
------------------------------------------------------------------------------------
 */

void harmonizer(struct channel *chan, struct main_control *main, int8_t oct){
    //set number of frequencies
    chan->QTY = harmonies[main->harmony][0];
    //enter frequencies in channel
    //if osc1 switch on, offset frequencies need to be calculated
    if(main->osc1 == 1){
        int8_t offset_harm, A, offset;
        for(uint8_t i = 0; i<chan->QTY; i++){
            A = main->scaleDeg + harmonies[main->harmony][i+1]; //offset harmony scale degree
            offset_harm = A-7*(A/7); //offset harmony normalized between 0-7
            if(A > 7){
                offset = (diaModes[main->scale][offset_harm]+12)-diaModes[main->scale][main->scaleDeg];
            }
            else{
                offset = diaModes[main->scale][A]-diaModes[main->scale][main->scaleDeg];
            }
            chan->ulPhaseIncrement[i] = nMidiPhaseInc[main->reference_freq + harmonies[main->harmony][i+5] + offset + oct*12];
        }
    }
    //osc1 switch off
    else{
        for(uint8_t i = 0; i<chan->QTY; i++){
            chan->ulPhaseIncrement[i] = nMidiPhaseInc[main->reference_freq+diaModes[main->scale][harmonies[main->harmony][i+1]+chan->chanID]+harmonies[main->harmony][i+5]+oct*12];
        }

    }
    
}

/* Normal Channel Mode normal_mode(channel, channelID)
 This function configures the channel frequencies in normal mode
 ------------------------------------------------------------------------------------
 */

void normal_mode(struct channel *chan, struct main_control *main, int8_t oct){
    //set number of frequencies
    chan->QTY = 1;
    //enter frequency in channel
    chan->ulPhaseIncrement[0] = nMidiPhaseInc[main->reference_freq + diaModes[main->scale][chan->chanID]+oct*12];
}

/* Oscillator 2 Mode osc2_mode(channel, channelID)
 This function configures the channel frequencies when oscillator 2 is on. The harmonizer
 will be disabled and the 2nd frequency will be calculated always relative to the reference freq
 ------------------------------------------------------------------------------------
 */

void osc2_mode(struct channel *chan, struct main_control *main, int8_t oct){
    //computationally intensive, skip if channel is inactive
    if(chan->ADSR_par[4] >= 1){
        //variables
        float aRefFreq, aRefFreqL, aRefFreqH, osc2_freq;
        //actual midi note of key pressed
        uint8_t ref_freq2 = main->reference_freq + diaModes[main->scale][chan->chanID] + oct*12;
    
        //extract actual frequency from reference_freq
        aRefFreq = ((pow(2.0,(ref_freq2-69.0)/12.0)) * 440.0);
        //compute 2 octave range
        aRefFreqL = aRefFreq/2;
        aRefFreqH = aRefFreq*2;
        //scale to user input
        if(main->osc2_knob <= 511){
            //scale to osc2_knob: 0-511
            osc2_freq = main->osc2_knob*(aRefFreq-aRefFreqL)/511+aRefFreqL;
        }
        else{
            //scale to osc2_knob: 512-1023
            osc2_freq = (main->osc2_knob-512)*(aRefFreqH-aRefFreq)/511+aRefFreq;
        }
        //compute fixed point phase increment
        uint32_t osc2PhaseIncrement = TICKS_PER_CYCLE*osc2_freq;
    
        //set number of frequencies
        chan->QTY = 2;
        chan->ulPhaseIncrement[0] = nMidiPhaseInc[ref_freq2];
        chan->ulPhaseIncrement[1] = osc2PhaseIncrement;
    }
}

/* ADSR Auto Trigger ADSR_auto_trigger(channel)
 This function configures the keystaus in each channel to simulate auto triggering of
 the ADSR envelope. Creates a 50% duty cycle of pressing the button on/off with
 adsr_trigger_rate as its period. When button is continuously held and period is greater
 than half its cycle, the keystatus will be updated with a false button release
 reading causing the ADSR_CR_configure function to think that the button isn't pressed.
 ------------------------------------------------------------------------------------
 */

void ADSR_auto_trigger(struct channel *chan){
    //check keystatus
    if(((chan->keystatus>>0)&1) == 1){
        //first half of period
        if(chan->trig_timer < adsr_trigger_rate>>1){
            //set keystatus high
            chan->keystatus ^= (-1^chan->keystatus)&(1<<0);
        }
        else if(chan->trig_timer > adsr_trigger_rate>>1){
            //set keystatus low (false)
            chan->keystatus ^= (-0^chan->keystatus)&(1<<0);
        }
    }
    //increment timer
    chan->trig_timer += 1;
    if(chan->trig_timer >= adsr_trigger_rate){
        //reset
        chan->trig_timer = 0;
    }
}



int16_t LPF(int16_t input, int32_t *nBuffer, int16_t N){
    //declare nBuffer[N+3] as global variable
    //variable to collect mean
    //nBuffer = [indexer, state, sum,1,...,N];
    
    //initialize register
    if(nBuffer[1] == 0){
        nBuffer[3+nBuffer[0]] = input;
        nBuffer[0] += 1;
        //take average
        if(nBuffer[0] == N){
            for(uint16_t i=0;i<N; i++){
                nBuffer[2] += nBuffer[3+i];
            }
            //change state
            nBuffer[1] = 1;
            //reset indexer
            nBuffer[0] = 3;
        }
    }
    else{
        //compute current moving average
        nBuffer[2] = (nBuffer[2]+input-nBuffer[nBuffer[0]]);
        //shift samples
        nBuffer[nBuffer[0]] = input;
        nBuffer[0] += 1;
        //reset indexer
        if(nBuffer[0] >= N+3){
            nBuffer[0] = 3;
        }
    }
    return nBuffer[2]/N;
}

/* Arpeggiator arpeggiate(Arpeggiator)
 This function indexes the frequencies to arpeggiated. There are three modes: rise, fall, both.
 This is used outside the ISR to save time.
 ------------------------------------------------------------------------------------
 */

void arpeggiate(struct arpeggiator *arpeg){
    
    if(arpeg->update == 1){
        switch(arpeg->mode){
            case 0: //rise
                //change index
                arpeg->index += 1;
                if(arpeg->index >= arpeg->wavecount){
                    
                    //if multiple octaves
                    if(arpeg->octave >= 1){
                        //increment octave count
                        arpeg->oct_count+=1;
                        if(arpeg->oct_count > arpeg->octave){
                            arpeg->oct_count = 0;
                        }
                    }
                    
                    //reset index
                    arpeg->index = 0;
                }
                break;
            
            case 1: //fall
                //change index
                arpeg->index -= 1;
                if(arpeg->index < 0 ){
                    
                    //if multiple octaves
                    if(arpeg->octave >= 1){
                        //decrement octave count
                        arpeg->oct_count-=1;
                        if(arpeg->oct_count < 0){
                            arpeg->oct_count = arpeg->octave;
                        }
                    }
                    
                    //reset index
                    arpeg->index = arpeg->wavecount-1;
                }
                break;
            
            case 2: //both
                //if rising
                if(arpeg->state == 0){
                    //change index
                    arpeg->index += 1;
                    if(arpeg->index >= arpeg->wavecount){
                        
                        //if multiple octaves
                        if(arpeg->octave >= 1){
                            //increment octave count
                            arpeg->oct_count+=1;
                            if(arpeg->oct_count > arpeg->octave){
                                //normalize
                                arpeg->oct_count = arpeg->octave;
                                //change state
                                arpeg->state = 1;
                                //normailze
                                arpeg->index = arpeg->wavecount-2;
                            }
                            else{
                                //normalize
                                arpeg->index = 0;
                            }
                        }
                        else{
                            //normalize
                            arpeg->index = arpeg->wavecount-2;
                            //change state
                            arpeg->state = 1;
                        }
                    }
                }
                // if falling
                else if(arpeg->state == 1){
                    //change index
                    arpeg->index -= 1;
                    if(arpeg->index < 0){
                        
                        //if multiple octaves
                        if(arpeg->octave >= 1){
                            //decrement octave count
                            arpeg->oct_count-=1;
                            if(arpeg->oct_count < 0){
                                //normailze
                                arpeg->oct_count = 0;
                                //change state
                                arpeg->state = 0;
                                //normailze
                                arpeg->index = 1;

                            }
                            else{
                                //normalize
                                arpeg->index = arpeg->wavecount-1;
                            }
                        }
                        else{
                            //normalize
                            arpeg->index = 1;
                            //change state
                            arpeg->state = 0;
                        }
                    }
                }
                break;
        }
        arpeg->update = 0;
    }
    
}

/* Arpeggiator arpeggiate_ISR(Arpeggiator)
 This function outputs the correct frequency to be arpeggiated. Must be used in ISR.
 ------------------------------------------------------------------------------------
 */

int16_t arpeggiate_ISR(struct pre_mix *pre_mast, struct arpeggiator *arpeg, struct main_control *main){
    //declare variables
    uint8_t channel_out = 0;
    //reset wavecount
    arpeg->wavecount = 0;
    
    //increment timer
    arpeg->Timer +=1;
    if(arpeg->Timer >= arpeg->rate){
        //reset timer
        arpeg->Timer = 0;
        //set flag to update index
        arpeg->update = 1;
    }
    
    //if harmonizer on
    if(main->user_mode == 1){
        arpeg->wavecount = harmonies[main->harmony][0];
        for(uint8_t i = 0; i<8; i++){
            //lowest note pressed will have priority
            if(pre_mast->pre_master[i] != 0x2FFF){
                if(pre_mast->active_chan[i] == 1){
                    channel_out = i;
                    break;
                }
                else{
                    channel_out = i;
                }
            }
        }
        //this sets the correct active channel
        for(uint8_t j = 0; j<arpeg->wavecount; j++){
            arpeg->arp_map[j] = channel_out;
        }
    }
    //if harmonizer off
    else{
        //calculate active channels & determine channel IDs
        for(uint8_t i = 0; i<8; i++){
            if(pre_mast->pre_master[i] != 0x2FFF){
                arpeg->arp_map[arpeg->wavecount] = i;
                arpeg->wavecount+=1;
            }
        }
    }
    return (pre_mast->pre_master[arpeg->arp_map[arpeg->index]]);
    
}

/* mode_configure(main_control)
 This function configures the correct user_mode and osc_mode for conflicting modes of operation
 ------------------------------------------------------------------------------------
 */

void mode_configure(struct main_control *main_cont){
    uint8_t configure;
    //configures user mode based on user input settings
    configure ^= (-main_cont->harmonizer^configure)&(1<<0); //set bit 0 to harmonizer switch
    configure ^= (-main_cont->osc2^configure)&(1<<1); //set bit 1 to osc2 switch
    
    switch(configure) {
        case 0:
            //normal: no harmonizer, no osc2
            main_cont->user_mode = 0;
            main_cont->osc_mode = 0;
            break;
        
        case 1:
            //harmonizer on, no osc2
            main_cont->user_mode = 1;
            main_cont->osc_mode = 0;
            break;
            
        case 2:
            //osc2 on, no harmonizer
            main_cont->user_mode = 2;
            main_cont->osc_mode = 1;
            break;
        case 3:
            //if osc2 and harmonizer high, disable harmonizer
            main_cont->user_mode = 2;
            main_cont->osc_mode = 1;
            break;
    }
}


#endif
