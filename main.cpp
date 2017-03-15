#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include "synth_utility.h"

#define LENGTH 150000
#define N 50 //MAX order for lowpass filter

FILE *fout, *fin;

struct channel channel0, channel1, channel2, channel3, channel4, channel5, channel6, channel7;
struct pre_mix pre_master_out;
struct arpeggiator Arpeggiator;
struct main_control main_control;

int16_t master_out, fMaster_out, n;
int32_t nBuffer[N+3], filter_t, filter_state = 0;

uint8_t keyboard_sim[8] = {1,0,1,0, 0,0,0,0};



int main(void){
    //Open file to write to
    fout = fopen("/Users/steven/Documents/embedXcode/DSP/DSP/data_out.txt", "w+");


    //configure frequency matrix
    createNoteTable(SAMPLE_RATE);
    //configure ADSR wavetable
    ADSR_configure(4095,2000,SAMPLE_RATE, 96,0,gate);
    //configure channel IDs
    channel0.chanID = 0;
    channel1.chanID = 1;
    channel2.chanID = 2;
    channel3.chanID = 3;
    channel4.chanID = 4;
    channel5.chanID = 5;
    channel6.chanID = 6;
    channel7.chanID = 7;
    
    
    for(uint32_t l = 0; l<=LENGTH; l++){


        //MAIN LOOP------------------------------------------------
        
        //READ USER INPUT
        //set ADSR parameters (read knob)
        adsr_values[0] = 30; //set attack level (1:2000 (length))
        adsr_values[1] = 100; //set decay level (1:2000 (length))
        adsr_values[2] = 3500; //set sustain level (1:4095 (max amplitude))
        adsr_values[3] = 20; //set release value (1:2000 (length))
        
        //Main Settings: Key/Mode/Scale/Octave
        main_control.key = 0; //D
        main_control.octave = 0; //no octave offset
        main_control.scale = 0; //dorian
        
        main_control.osc1 = 0; //off
        main_control.osc2 = 0;
        main_control.osc1_knob = 62; //center C
        main_control.osc2_knob = 500; //halfway
        main_control.waveform[0] = 1; //square
        main_control.waveform[1] = 1; //square
        
        main_control.harmonizer = 0;
        main_control.harmony = 11; //no harmony
        
        //Arpeggiator Settings
        Arpeggiator.active = 0; //arpeggiator off
        Arpeggiator.rate = 5000;
        Arpeggiator.mode = 2; //rise
        Arpeggiator.octave = 2;
        
        //ADSR Auto Trigger Settings
        adsr_trigger = 0;
        adsr_trigger_rate = 5000;
        
        //LowPass Filter Settings
        n = 2;
        
        //Start of main algorithms
        //-----------------------------------------------------------------
        //configure reference frequency
        main_control.reference_freq = reference_frequency(&main_control);
        //configure operation mode
        mode_configure(&main_control);
        
        //Simulate button read, check keyboard_sim array
        channel0.keystatus ^= (-keyboard_sim[0]^channel0.keystatus)&(1<<0);
        channel1.keystatus ^= (-keyboard_sim[1]^channel1.keystatus)&(1<<0);
        channel2.keystatus ^= (-keyboard_sim[2]^channel2.keystatus)&(1<<0);
        channel3.keystatus ^= (-keyboard_sim[3]^channel3.keystatus)&(1<<0);
        channel4.keystatus ^= (-keyboard_sim[4]^channel4.keystatus)&(1<<0);
        channel5.keystatus ^= (-keyboard_sim[5]^channel5.keystatus)&(1<<0);
        channel6.keystatus ^= (-keyboard_sim[6]^channel6.keystatus)&(1<<0);
        channel7.keystatus ^= (-keyboard_sim[7]^channel7.keystatus)&(1<<0);
        
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
        }
        
        //Configure ADSR register for ech channel
        ADSR_CR_configure(&channel0);
        ADSR_CR_configure(&channel1);
        ADSR_CR_configure(&channel2);
        ADSR_CR_configure(&channel3);
        ADSR_CR_configure(&channel4);
        ADSR_CR_configure(&channel5);
        ADSR_CR_configure(&channel6);
        ADSR_CR_configure(&channel7);
        
        //Update ADSR envelope
        ADSR(&channel0);
        ADSR(&channel1);
        ADSR(&channel2);
        ADSR(&channel3);
        ADSR(&channel4);
        ADSR(&channel5);
        ADSR(&channel6);
        ADSR(&channel7);
        
        //update arpeggiator
        if(Arpeggiator.active == 1){
            arpeggiate(&Arpeggiator);
        }
        
        //-----------------------------------------------------------
        //Configure channels
        switch(main_control.user_mode){
            case 0: //normal mode
                normal_mode(&channel0, &main_control, Arpeggiator.oct_count);
                normal_mode(&channel1, &main_control, Arpeggiator.oct_count);
                normal_mode(&channel2, &main_control, Arpeggiator.oct_count);
                normal_mode(&channel3, &main_control, Arpeggiator.oct_count);
                normal_mode(&channel4, &main_control, Arpeggiator.oct_count);
                normal_mode(&channel5, &main_control, Arpeggiator.oct_count);
                normal_mode(&channel6, &main_control, Arpeggiator.oct_count);
                normal_mode(&channel7, &main_control, Arpeggiator.oct_count);
                break;
                
            case 1: //harmonizer
                harmonizer(&channel0, &main_control, Arpeggiator.oct_count);
                harmonizer(&channel1, &main_control, Arpeggiator.oct_count);
                harmonizer(&channel2, &main_control, Arpeggiator.oct_count);
                harmonizer(&channel3, &main_control, Arpeggiator.oct_count);
                harmonizer(&channel4, &main_control, Arpeggiator.oct_count);
                harmonizer(&channel5, &main_control, Arpeggiator.oct_count);
                harmonizer(&channel6, &main_control, Arpeggiator.oct_count);
                harmonizer(&channel7, &main_control, Arpeggiator.oct_count);
                break;
                
            case 2: //osc2 is on
                osc2_mode(&channel0, &main_control, Arpeggiator.oct_count);
                osc2_mode(&channel1, &main_control, Arpeggiator.oct_count);
                osc2_mode(&channel2, &main_control, Arpeggiator.oct_count);
                osc2_mode(&channel3, &main_control, Arpeggiator.oct_count);
                osc2_mode(&channel4, &main_control, Arpeggiator.oct_count);
                osc2_mode(&channel5, &main_control, Arpeggiator.oct_count);
                osc2_mode(&channel6, &main_control, Arpeggiator.oct_count);
                osc2_mode(&channel7, &main_control, Arpeggiator.oct_count);
                break;
        }
        ISR();
    }
    
    fclose(fout);
    return 0;
}

int ISR(){
    
    //reset master_out
    master_out = 0;
    
    //configure frequencies present in each channel
    channel_oscillator(&channel0, &pre_master_out, &Arpeggiator, &main_control);
    channel_oscillator(&channel1, &pre_master_out, &Arpeggiator, &main_control);
    channel_oscillator(&channel2, &pre_master_out, &Arpeggiator, &main_control);
    channel_oscillator(&channel3, &pre_master_out, &Arpeggiator, &main_control);
    channel_oscillator(&channel4, &pre_master_out, &Arpeggiator, &main_control);
    channel_oscillator(&channel5, &pre_master_out, &Arpeggiator, &main_control);
    channel_oscillator(&channel6, &pre_master_out, &Arpeggiator, &main_control);
    channel_oscillator(&channel7, &pre_master_out, &Arpeggiator, &main_control);
    
    if(Arpeggiator.active == 1){
        //arpeggiate active channels
        master_out = arpeggiate_ISR(&pre_master_out, &Arpeggiator, &main_control);
    }
    //normal mixing
    else{
        //mix into master channel
        for(uint8_t i = 0; i<8; i++){
            if(pre_master_out.pre_master[i] != 0x2FFF){
                master_out += pre_master_out.pre_master[i];
            }
        }
    }
    //moving average to remove harmonic distortion from mixing
    fMaster_out = LPF(master_out, nBuffer, n);
    fprintf(fout,"%d \n", fMaster_out);
    return 0;
}
