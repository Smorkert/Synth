int32_t attenuator(int32_t Input, uint8_t a){
    int32_t Output;
    if(a > 31){
        a = 31;
    }
    switch(a){
            //attenuation in steps of .03125
        case 0: //no attenuation
            Output = Input - (Input>>6);
            break;
        case 1: //.96875
            Output = Input - (Input>>5);
            break;
        case 2: //.9375
            Output = Input - (Input>>4);
            break;
        case 3: //.90625
            Output = Input - (Input>>3)+(Input>>5);
            break;
        case 4: //.875
            Output = Input - (Input>>3);
            break;
        case 5: //.84375
            Output = Input - (Input>>3)-(Input>>5);
            break;
        case 6: //.8125
            Output = Input - (Input>>2)+(Input>>4);
            break;
        case 7: //.78125
            Output = Input - (Input>>2)+(Input>>5);
            break;
        case 8: //.75
            Output = Input - (Input>>2);
            break;
        case 9: //.71875
            Output = Input - (Input>>2)-(Input>>5);
            break;
        case 10: //.6875
            Output = Input - (Input>>2)-(Input>>4);
            break;
        case 11: //.65625
            Output = Input - (Input>>1)+(Input>>3)+(Input>>5);
            break;
        case 12: //.625
            Output = (Input>>1) + (Input>>3);
            break;
        case 13: //.59375
            Output = Input - (Input>>1)+(Input>>3)-(Input>>5);
            break;
        case 14: //.5625
            Output = (Input>>1) + (Input>>4);
            break;
        case 15: //.53125
            Output = (Input>>1) + (Input>>5);
            break;
        case 16: //.5
            Output = Input>>1;
            break;
        case 17: //.46875
            Output = (Input>>1) - (Input>>5);
            break;
        case 18: //.4375
            Output = (Input>>1) - (Input>>4);
            break;
        case 19: //.40625
            Output = (Input>>2) + (Input>>3) + (Input>>5);
            break;
        case 20: //.375
            Output = (Input>>1) - (Input>>3);
            break;
        case 21: //.34375
            Output = (Input>>2) + (Input>>3) - (Input>>5);
            break;
        case 22: //.3125
            Output = (Input>>2)+(Input>>4);
            break;
        case 23: //.281250
            Output = (Input>>2)+(Input>>5);
            break;
        case 24: //.25
            Output = (Input>>2);
            break;
        case 25: //.21875
            Output = (Input>>2)-(Input>>4)+(Input>>5);
            break;
        case 26: //.1875
            Output = (Input>>3)+(Input>>4);
            break;
        case 27: //.15625
            Output = (Input>>3)+(Input>>5);
            break;
        case 28: //.125
            Output = (Input>>3);
            break;
        case 29: //.09375
            Output = (Input>>3)-(Input>>5);
            break;
        case 30: //.0625
            Output = (Input>>4);
            break;
        case 31: //.03125
            Output = (Input>>5);
            break;
    }
    return Output;
}

/* Fast Reverb
 This functions implements a fast 2 tap delay line reverb. Filter orders must be power of 2.
 */

struct fastTap{
    fastTap(uint16_t Size, int16_t uN){
        unSize = Size;
        tap = new int32_t[unSize];
        n = uN;
        lpf_buffer = new int32_t[n];
        count = uN;
        //extract order
        while(count != 2){
            count = count>>1;
            shift+=1;
        }
        shift+=1;
        //initialize filter buffer
        for(uint16_t i = 0; i<n; i++){
            lpf_buffer[i] = 1;
        }
        sum = n;
        //clear memory array 
        for(uint32_t i = 0; i<unSize; i++){
          tap[i] = 0;
        }
    }
    //variables
    uint8_t shift, count;
    uint16_t unSize, tap_index, lpf_index, n;
    int32_t *tap, *lpf_buffer, sum, Output, f_output;
    
    int32_t tap_reverb(int32_t Input, uint8_t a){
        //increment index
        tap_index += 1;
        //check overflow
        if(tap_index >= unSize){
            //reset
            tap_index = 0;
        }
        //create output with delay/feedback
        Output = tap[tap_index]+Input;
        //lowpass filter
        sum = (sum+Output-lpf_buffer[lpf_index]);
        //shift samples
        lpf_buffer[lpf_index] = Output;
        lpf_index += 1;
        //reset indexer
        if(lpf_index >= n){
            lpf_index = 0;
        }
        //filtered Output
        f_output = sum>>shift;
        //store filtered/attenuated Output
        tap[tap_index] = attenuator(f_output, a);
        //send output
        return Output;
    }
    
};

struct fastReverb{
    fastReverb(int32_t Max_delay){
        //store variables
        max_delay = Max_delay;
        //declare size array
        sizes = new int32_t[2];
        outputs = new int32_t[2];
        //fill size array
        for(uint8_t i = 0; i<2; i++){
            ftemp = fscale[i]*max_delay;
            sizes[i] = (int32_t)ftemp;
        }
    }
    //variables
    float fscale[2] = {0.8182, 1.0}, ftemp;
    int32_t *sizes, *outputs, max_delay, sum;
    uint8_t a;
    
    int32_t reverberate(int32_t Input, struct fastTap *t1, struct fastTap *t2){
        //run Input through taps
        outputs[0] = t1->tap_reverb(Input, a);
        outputs[1] = t2->tap_reverb(Input, a+4);
        //sum outputs and normalize
        sum = outputs[0];
        sum += outputs[1];
        
        return (int16_t)attenuator(sum, 20);
    }
};
