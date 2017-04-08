#ifndef Mini_Arcade_Synth_synth_display_h
#define Mini_Arcade_Synth_synth_display_h

#include <Sprite.h>  // Sprite before Matrix
#include <Matrix.h>
#define DELAY 90
#define DELAY_N 700
#define DELAY_L 2000
const int numChips = 2;

struct sDisplay
{
   uint8_t Update, type, count, repeat;
   uint16_t timer, Delay;
   int16_t index;
};


//                   DIN, CLK, LOAD, #chips
Matrix myLeds = Matrix(7, 8, 9, numChips);

/* Display Functions
 *  MODES:
 *  Ionian(&sDsiplay, repeat, offset)
 *  Dorian(&sDsiplay, repeat, offset)
 *  Phrygian(&sDsiplay, repeat, offset)
 *  Lydian(&sDsiplay, repeat, offset)
 *  Mixolydian(&sDsiplay, repeat, offset)
 *  Aeolian(&sDsiplay, repeat, offset)
 *  Locrian(&sDsiplay, repeat, offset)
 *  PentaMin(&sDsiplay, repeat, offset)
 *  PentaMaj(&sDsiplay, repeat, offset)
 *  Egyptian(&sDsiplay, repeat, offset)
 *  Spanish(&sDsiplay, repeat, offset)
 *  Gypsy(&sDsiplay, repeat, offset)
 *  Arabic(&sDsiplay, repeat, offset)
 *  WholeTone(&sDsiplay, repeat, offset)
 * 
 * HARMONIES:
 *  off(&sDsiplay, repeat, offset)
 *  d_2nd(&sDsiplay, repeat, offset)
 *  d_3rd(&sDsiplay, repeat, offset)
 *  d_4th(&sDsiplay, repeat, offset)
 *  d_5th(&sDsiplay, repeat, offset)
 *  d_6th(&sDsiplay, repeat, offset)
 *  d_7th(&sDsiplay, repeat, offset)
 *  d_8th(&sDsiplay, repeat, offset)
 *  d_9th(&sDsiplay, repeat, offset)
 *  d_10th(&sDsiplay, repeat, offset)
 *  triad(&sDsiplay, repeat, offset)
 *  triad2(&sDsiplay, repeat, offset)
 *  n7th_triad(&sDsiplay, repeat, offset)
 *  n7th_triad2(&sDsiplay, repeat, offset)
 *  drone(&sDsiplay, repeat, offset)
 * 
 * KEY:
 *  c(&sDsiplay, repeat, offset)
 *  cS(&sDsiplay, repeat, offset)
 *  d(&sDsiplay, repeat, offset)
 *  dS(&sDsiplay, repeat, offset)
 *  e(&sDsiplay, repeat, offset)
 *  f(&sDsiplay, repeat, offset)
 *  fS(&sDsiplay, repeat, offset)
 *  g(&sDsiplay, repeat, offset)
 *  gS(&sDsiplay, repeat, offset)
 *  a(&sDsiplay, repeat, offset)
 *  aS(&sDsiplay, repeat, offset)
 *  b(&sDsiplay, repeat, offset)
 * 
 * ARPEGGIATOR MODE:
 *  rise(&sDsiplay, repeat, offset)
 *  fall(&sDsiplay, repeat, offset)
 *  both(&sDsiplay, repeat, offset)
 * 
 * ARPEGGIATOR OCTAVE:
 *  arp0(&sDsiplay, repeat, offset)
 *  arp1(&sDsiplay, repeat, offset)
 *  arp12(&sDsiplay, repeat, offset)
 *  arp123(&sDsiplay, repeat, offset)
 *  arp1234(&sDsiplay, repeat, offset)
 *  
 * MENU:
 *  Key(&sDsiplay, repeat, offset)
 *  Scale(&sDsiplay, repeat, offset)
 *  Harmony(&sDsiplay, repeat, offset)
 *  ArpeggiatorMode(&sDsiplay, repeat, offset)
 *  ArpeggiatorOct(&sDsiplay, repeat, offset)
 * 
 */


//ALPHABET----------------------------------------------
//3x5 Alphabet, Upper Case (except n)

Sprite lA = Sprite(3, 5,
  B010,
  B101,
  B111,
  B101,
  B101
 );

Sprite lB = Sprite(3, 5,
  B110,
  B101,
  B110,
  B101,
  B110
 );

Sprite lC = Sprite(3, 5,
  B011,
  B100,
  B100,
  B100,
  B011
 );

Sprite lD = Sprite(3, 5,
  B110,
  B101,
  B101,
  B101,
  B110
 );

Sprite lE = Sprite(3, 5,
  B111,
  B100,
  B111,
  B100,
  B111
 );

Sprite lF = Sprite(3, 5,
  B111,
  B100,
  B111,
  B100,
  B100
 );

Sprite lG = Sprite(4, 5,
  B0111,
  B1000,
  B1011,
  B1001,
  B0110
 );


Sprite lH = Sprite(3, 5,
  B101,
  B101,
  B111,
  B101,
  B101
 );

 
Sprite lI = Sprite(3, 5,
  B111,
  B010,
  B010,
  B010,
  B111
 );

Sprite lJ = Sprite(3, 5,
  B111,
  B010,
  B010,
  B010,
  B110
 );

Sprite lK = Sprite(3, 5,
  B101,
  B110,
  B100,
  B110,
  B101
 );

Sprite lL = Sprite(3, 5,
  B100,
  B100,
  B100,
  B100,
  B111
 );

Sprite lM = Sprite(5, 5,
  B11011,
  B10101,
  B10101,
  B10101,
  B10101
 );

Sprite lN = Sprite(5, 5,
  B11001,
  B11001,
  B10101,
  B10011,
  B10011
 );

Sprite lO = Sprite(3, 5,
  B111,
  B101,
  B101,
  B101,
  B111
 );

Sprite lP = Sprite(3, 5,
  B110,
  B101,
  B111,
  B100,
  B100
 );

Sprite lQ = Sprite(3, 6,
  B111,
  B101,
  B101,
  B101,
  B111,
  B001
 );

Sprite lR = Sprite(3, 5,
  B111,
  B101,
  B110,
  B101,
  B101
 );

Sprite lS = Sprite(3, 5,
  B111,
  B100,
  B111,
  B001,
  B111
 );

Sprite lT = Sprite(3, 5,
  B111,
  B010,
  B010,
  B010,
  B010
 );

Sprite lU = Sprite(3, 5,
  B101,
  B101,
  B101,
  B101,
  B111
 );

Sprite lV = Sprite(3, 5,
  B101,
  B101,
  B101,
  B101,
  B010
 );

Sprite lW = Sprite(5, 5,
  B10101,
  B10101,
  B10101,
  B10101,
  B01110
 );

Sprite lX = Sprite(3, 5,
  B101,
  B101,
  B010,
  B101,
  B101
 );

Sprite lY = Sprite(3, 5,
  B101,
  B101,
  B111,
  B010,
  B010
 );

Sprite lZ = Sprite(3, 5,
  B111,
  B001,
  B010,
  B100,
  B111
 );

//---------------------------------------------------------------------
//3 x 5 Alphabet, Lower Case (no n)
Sprite la = Sprite(3, 5,
  B110,
  B001,
  B111,
  B101,
  B011
 ); 

Sprite lb = Sprite(3, 5,
  B100,
  B100,
  B110,
  B101,
  B111
 );

Sprite lc = Sprite(3, 5,
  B000,
  B011,
  B100,
  B100,
  B011
 );

Sprite ld = Sprite(3, 5,
  B001,
  B001,
  B011,
  B101,
  B111
 );

Sprite le = Sprite(3, 5,
  B011,
  B101,
  B111,
  B100,
  B011
 );

Sprite lf = Sprite(3, 5,
  B011,
  B100,
  B111,
  B100,
  B100
 );

Sprite lg = Sprite(3, 5,
  B011,
  B101,
  B111,
  B001,
  B011
 );

Sprite lh = Sprite(3, 5,
  B100,
  B100,
  B110,
  B101,
  B101
 );

Sprite li = Sprite(3, 5,
  B010,
  B000,
  B010,
  B010,
  B010
 );

Sprite lj = Sprite(3, 5,
  B001,
  B000,
  B001,
  B001,
  B010
 );

Sprite lk = Sprite(3, 5,
  B100,
  B101,
  B110,
  B110,
  B101
 );

Sprite ll = Sprite(3, 5,
  B010,
  B010,
  B010,
  B010,
  B001
 );

Sprite lm = Sprite(5, 5,
  B00000,
  B01110,
  B10101,
  B10101,
  B10101
 );

Sprite ln = Sprite(3, 5,
  B000,
  B110,
  B101,
  B101,
  B101
 );


Sprite lo = Sprite(3, 5,
  B000,
  B010,
  B101,
  B101,
  B010
 );

Sprite lp = Sprite(3, 5,
  B000,
  B011,
  B101,
  B110,
  B100
 );

Sprite lq = Sprite(3, 5,
  B000,
  B011,
  B101,
  B111,
  B001
 );

Sprite lr = Sprite(3, 5,
  B000,
  B011,
  B100,
  B100,
  B100
 );

Sprite ls = Sprite(3, 5,
  B000,
  B011,
  B100,
  B011,
  B110
 );

Sprite lt = Sprite(3, 5,
  B000,
  B010,
  B111,
  B010,
  B011
 );

Sprite lu = Sprite(3, 5,
  B000,
  B101,
  B101,
  B101,
  B111
 );

Sprite lv = Sprite(3, 5,
  B000,
  B101,
  B101,
  B101,
  B010
 );

Sprite lw = Sprite(5, 5,
  B00000,
  B10101,
  B10101,
  B10101,
  B01110
 );

Sprite lx = Sprite(3, 5,
  B000,
  B101,
  B101,
  B010,
  B101
 );

Sprite ly = Sprite(3, 5,
  B000,
  B101,
  B101,
  B010,
  B100
 );

Sprite lz = Sprite(3, 5,
  B000,
  B111,
  B001,
  B010,
  B111
 );

//NUMBERS, 3 x 5

Sprite n0 = Sprite(3, 5,
  B010,
  B101,
  B101,
  B101,
  B010
 );

Sprite n1 = Sprite(3, 5,
  B110,
  B010,
  B010,
  B010,
  B111
 );

Sprite n2 = Sprite(3, 5,
  B110,
  B001,
  B010,
  B100,
  B111
 );

Sprite n3 = Sprite(3, 5,
  B110,
  B001,
  B111,
  B001,
  B110
 );

Sprite n4 = Sprite(3, 5,
  B101,
  B101,
  B111,
  B001,
  B001
 );

Sprite n5 = Sprite(3, 5,
  B111,
  B100,
  B110,
  B001,
  B110
 );

Sprite n6 = Sprite(3, 5,
  B011,
  B100,
  B111,
  B101,
  B111
 );

Sprite n7 = Sprite(3, 5,
  B111,
  B001,
  B010,
  B010,
  B010
 );

Sprite n8 = Sprite(3, 5,
  B111,
  B101,
  B111,
  B101,
  B111
 );

Sprite n9 = Sprite(3, 5,
  B011,
  B101,
  B111,
  B001,
  B011
 );

Sprite sharp = Sprite(5, 5,
  B01010,
  B11111,
  B01010,
  B11111,
  B01010
 );

Sprite colon = Sprite(3, 5,
  B000,
  B010,
  B000,
  B010,
  B000
 );



 
//Function calls for display------------------------------------------
//-----------MODES---------------
//Ionian
void Ionian(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){

  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -20){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lI);
  myLeds.write((disp->index+4), Offset, lo);
  myLeds.write((disp->index+8), Offset, ln);
  myLeds.write((disp->index+11), Offset, li);
  myLeds.write((disp->index+14), Offset, la);
  myLeds.write((disp->index+18), Offset, ln);
  myLeds.write(0,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2); //set bit 2 high
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(0,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  }
}

//Dorian
void Dorian(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -20){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lD);
  myLeds.write((disp->index+4), Offset, lo);
  myLeds.write((disp->index+8), Offset, lr);
  myLeds.write((disp->index+11), Offset, li);
  myLeds.write((disp->index+14), Offset, la);
  myLeds.write((disp->index+18), Offset, ln);
  myLeds.write(1,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(1,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  }
}

//Phrygian
void Phrygian(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -28){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lP);
  myLeds.write((disp->index+4), Offset, lh);
  myLeds.write((disp->index+8), Offset, lr);
  myLeds.write((disp->index+12), Offset, ly);
  myLeds.write((disp->index+16), Offset, lg);
  myLeds.write((disp->index+19), Offset, li);
  myLeds.write((disp->index+22), Offset, la);
  myLeds.write((disp->index+26), Offset, ln);
  myLeds.write(2,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(2,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  }
}

//Lydian
void Lydian(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){

  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -20){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lL);
  myLeds.write((disp->index+4), Offset, ly);
  myLeds.write((disp->index+8), Offset, ld);
  myLeds.write((disp->index+11), Offset, li);
  myLeds.write((disp->index+14), Offset, la);
  myLeds.write((disp->index+18), Offset, ln);
  myLeds.write(3,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(3,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

//Mixolydian
void Mixolydian(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){

  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -36){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lM);
  myLeds.write((disp->index+5), Offset, li);
  myLeds.write((disp->index+8), Offset, lx);
  myLeds.write((disp->index+12), Offset, lo);
  myLeds.write((disp->index+15), Offset, ll);
  myLeds.write((disp->index+19), Offset, ly);
  myLeds.write((disp->index+23), Offset, ld);
  myLeds.write((disp->index+26), Offset, li);
  myLeds.write((disp->index+29), Offset, la);
  myLeds.write((disp->index+33), Offset, ln);
  myLeds.write(4,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(4,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  }
}

//Aeolian
void Aeolian(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
  
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -24){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lA);
  myLeds.write((disp->index+4), Offset, le);
  myLeds.write((disp->index+8), Offset, lo);
  myLeds.write((disp->index+11), Offset, ll);
  myLeds.write((disp->index+14), Offset, li);
  myLeds.write((disp->index+17), Offset, la);
  myLeds.write((disp->index+21), Offset, ln);
  myLeds.write(5,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(5,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

//Locrian
void Locrian(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -24){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lL);
  myLeds.write((disp->index+4), Offset, lo);
  myLeds.write((disp->index+8), Offset, lc);
  myLeds.write((disp->index+12), Offset, lr);
  myLeds.write((disp->index+15), Offset, li);
  myLeds.write((disp->index+18), Offset, la);
  myLeds.write((disp->index+22), Offset, ln);
  myLeds.write(6,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(6,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

//Minor Pentatonic
void PentaMin(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
  
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -54){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lP);
  myLeds.write((disp->index+4), Offset, le);
  myLeds.write((disp->index+8), Offset, ln);
  myLeds.write((disp->index+12), Offset, lt);
  myLeds.write((disp->index+16), Offset, la);
  myLeds.write((disp->index+20), Offset, lt);
  myLeds.write((disp->index+24), Offset, lo);
  myLeds.write((disp->index+28), Offset, ln);
  myLeds.write((disp->index+31), Offset, li);
  myLeds.write((disp->index+34), Offset, lc);
  myLeds.write((disp->index+39), Offset, lM);
  myLeds.write((disp->index+44), Offset, li);
  myLeds.write((disp->index+47), Offset, ln);
  myLeds.write((disp->index+51), Offset, lo);
  myLeds.write((disp->index+55), Offset, lr);
  myLeds.write(7,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(7,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

//Major Pentatonic
void PentaMaj(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
  
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -54){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lP);
  myLeds.write((disp->index+4), Offset, le);
  myLeds.write((disp->index+8), Offset, ln);
  myLeds.write((disp->index+12), Offset, lt);
  myLeds.write((disp->index+16), Offset, la);
  myLeds.write((disp->index+20), Offset, lt);
  myLeds.write((disp->index+24), Offset, lo);
  myLeds.write((disp->index+28), Offset, ln);
  myLeds.write((disp->index+31), Offset, li);
  myLeds.write((disp->index+34), Offset, lc);
  myLeds.write((disp->index+39), Offset, lM);
  myLeds.write((disp->index+45), Offset, la);
  myLeds.write((disp->index+48), Offset, lj);
  myLeds.write((disp->index+52), Offset, lo);
  myLeds.write((disp->index+56), Offset, lr);
  myLeds.write(8,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(8,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

//Egyptian
void Egyptian(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -28){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lE);
  myLeds.write((disp->index+4), Offset, lg);
  myLeds.write((disp->index+8), Offset, ly);
  myLeds.write((disp->index+12), Offset, lp);
  myLeds.write((disp->index+16), Offset, lt);
  myLeds.write((disp->index+19), Offset, li);
  myLeds.write((disp->index+22), Offset, la);
  myLeds.write((disp->index+26), Offset, ln);
  myLeds.write(9,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(9,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

//Spanish
void Spanish(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -24){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lS);
  myLeds.write((disp->index+4), Offset, lp);
  myLeds.write((disp->index+8), Offset, la);
  myLeds.write((disp->index+12), Offset, ln);
  myLeds.write((disp->index+15), Offset, li);
  myLeds.write((disp->index+18), Offset, ls);
  myLeds.write((disp->index+22), Offset, lh);
  myLeds.write(10,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(10,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

//Gypsy
void Gypsy(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -16){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lG);
  myLeds.write((disp->index+5), Offset, ly);
  myLeds.write((disp->index+9), Offset, lp);
  myLeds.write((disp->index+13), Offset, ls);
  myLeds.write((disp->index+17), Offset, ly);
  myLeds.write(11,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(11,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

//Arabic
void Arabic(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -20){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lA);
  myLeds.write((disp->index+4), Offset, lr);
  myLeds.write((disp->index+8), Offset, la);
  myLeds.write((disp->index+12), Offset, lb);
  myLeds.write((disp->index+15), Offset, li);
  myLeds.write((disp->index+18), Offset, lc);
  myLeds.write(12,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(12,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

//WholeTone
void WholeTone(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -32){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lW);
  myLeds.write((disp->index+6), Offset, lh);
  myLeds.write((disp->index+10), Offset, lo);
  myLeds.write((disp->index+13), Offset, ll);
  myLeds.write((disp->index+17), Offset, le);
  myLeds.write((disp->index+22), Offset, lT);
  myLeds.write((disp->index+25), Offset, lo);
  myLeds.write((disp->index+29), Offset, ln);
  myLeds.write((disp->index+33), Offset, le);
  myLeds.write(13,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(13,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

//---------------HARMONIES------------------------------------------------------
//off
void off(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, lO);
  myLeds.write(5, Offset, lf);
  myLeds.write(9, Offset, lf);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}
//2nd
void d_2nd(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, n2);
  myLeds.write(5, Offset, ln);
  myLeds.write(9, Offset, ld);
  myLeds.write(0,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(0,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//3rd
void d_3rd(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, n3);
  myLeds.write(5, Offset, lr);
  myLeds.write(9, Offset, ld);
  myLeds.write(1,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(1,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//4th
void d_4th(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, n4);
  myLeds.write(5, Offset, lt);
  myLeds.write(9, Offset, lh);
  myLeds.write(2,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(2,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//5th
void d_5th(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, n5);
  myLeds.write(5, Offset, lt);
  myLeds.write(9, Offset, lh);
  myLeds.write(3,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(3,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//6th
void d_6th(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, n6);
  myLeds.write(5, Offset, lt);
  myLeds.write(9, Offset, lh);
  myLeds.write(4,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(4,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//7th
void d_7th(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, n7);
  myLeds.write(5, Offset, lt);
  myLeds.write(9, Offset, lh);
  myLeds.write(5,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(5,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//Octave
void d_8th(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, n8);
  myLeds.write(5, Offset, lt);
  myLeds.write(9, Offset, lh);
  myLeds.write(6,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(6,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//9th
void d_9th(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, n9);
  myLeds.write(5, Offset, lt);
  myLeds.write(9, Offset, lh);
  myLeds.write(7,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(7,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//10th
void d_10th(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, n1);
  myLeds.write(5, Offset, n0);
  myLeds.write(9, Offset, lt);
  myLeds.write(13, Offset, lh);
  myLeds.write(8,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(8,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//Triad
void triad(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -16){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lT);
  myLeds.write((disp->index+3), Offset, lr);
  myLeds.write((disp->index+6), Offset, li);
  myLeds.write((disp->index+9), Offset, la);
  myLeds.write((disp->index+13), Offset, ld);
  myLeds.write(9,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(9,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

//Triad 2
void triad2(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){

  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -20){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lT);
  myLeds.write((disp->index+3), Offset, lr);
  myLeds.write((disp->index+6), Offset, li);
  myLeds.write((disp->index+9), Offset, la);
  myLeds.write((disp->index+13), Offset, ld);
  myLeds.write((disp->index+18), Offset, n2);
  myLeds.write(10,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(10,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

//Triad with 7ths
void n7th_triad(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -28){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, n7);
  myLeds.write((disp->index+3), Offset, lt);
  myLeds.write((disp->index+7), Offset, lh);
  myLeds.write((disp->index+12), Offset, lT);
  myLeds.write((disp->index+15), Offset, lr);
  myLeds.write((disp->index+18), Offset, li);
  myLeds.write((disp->index+21), Offset, la);
  myLeds.write((disp->index+25), Offset, ld);
  myLeds.write(11,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(11,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

//Triad with 7ths 2
void n7th_triad2(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -32){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, n7);
  myLeds.write((disp->index+3), Offset, lt);
  myLeds.write((disp->index+7), Offset, lh);
  myLeds.write((disp->index+12), Offset, lT);
  myLeds.write((disp->index+15), Offset, lr);
  myLeds.write((disp->index+18), Offset, li);
  myLeds.write((disp->index+21), Offset, la);
  myLeds.write((disp->index+25), Offset, ld);
  myLeds.write((disp->index+30), Offset, n2);
  myLeds.write(12,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(12,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

//Drone
void drone(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
  
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -16){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lD);
  myLeds.write((disp->index+4), Offset, lr);
  myLeds.write((disp->index+8), Offset, lo);
  myLeds.write((disp->index+12), Offset, ln);
  myLeds.write((disp->index+16), Offset, le);
  myLeds.write(13,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //reset
         disp->count = 0;
         disp->index = 2;
         //disable display update
         disp->Update = 0;
         myLeds.clear();
         myLeds.write(13,7,HIGH);
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

//-------------------KEYS------------------------------------------------------------------
//C
void c(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, lK);
  myLeds.write(4, Offset, colon);
  myLeds.write(7, Offset, lC);
  myLeds.write(0,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(0,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//C#
void cS(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, lK);
  myLeds.write(4, Offset, colon);
  myLeds.write(7, Offset, lC);
  myLeds.write(11, Offset, sharp);
  myLeds.write(1,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(1,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//D
void d(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, lK);
  myLeds.write(4, Offset, colon);
  myLeds.write(7, Offset, lD);
  myLeds.write(2,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(2,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//D#
void dS(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, lK);
  myLeds.write(4, Offset, colon);
  myLeds.write(7, Offset, lD);
  myLeds.write(11, Offset, sharp);
  myLeds.write(3,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(3,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//E
void e(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, lK);
  myLeds.write(4, Offset, colon);
  myLeds.write(7, Offset, lE);
  myLeds.write(4,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(4,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//F
void f(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, lK);
  myLeds.write(4, Offset, colon);
  myLeds.write(7, Offset, lF);
  myLeds.write(5,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(5,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//F#
void fS(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, lK);
  myLeds.write(4, Offset, colon);
  myLeds.write(7, Offset, lF);
  myLeds.write(11, Offset, sharp);
  myLeds.write(6,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(6,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//G
void g(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, lK);
  myLeds.write(4, Offset, colon);
  myLeds.write(7, Offset, lG);
  myLeds.write(7,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(7,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//G#
void gS(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, lK);
  myLeds.write(4, Offset, colon);
  myLeds.write(7, Offset, lG);
  myLeds.write(11, Offset, sharp);
  myLeds.write(8,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(8,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//A
void a(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, lK);
  myLeds.write(4, Offset, colon);
  myLeds.write(7, Offset, lA);
  myLeds.write(9,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(9,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//A#
void aS(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
   
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, lK);
  myLeds.write(4, Offset, colon);
  myLeds.write(7, Offset, lA);
  myLeds.write(11, Offset, sharp);
  myLeds.write(10,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(10,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//B
void b(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, lK);
  myLeds.write(4, Offset, colon);
  myLeds.write(7, Offset, lB);
  myLeds.write(11,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(11,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//----------------ARPEGGIATOR MODES----------------------------------------------------------------

//Rise
void rise(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, lR);
  myLeds.write(4, Offset, li);
  myLeds.write(7, Offset, ls);
  myLeds.write(11, Offset, le);
  myLeds.write(0,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(0,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//Fall
void fall(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, lF);
  myLeds.write(5, Offset, la);
  myLeds.write(8, Offset, ll);
  myLeds.write(11, Offset, ll);
  myLeds.write(1,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(1,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//both
void both(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, lB);
  myLeds.write(5, Offset, lo);
  myLeds.write(9, Offset, lt);
  myLeds.write(13, Offset, lh);
  myLeds.write(2,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(2,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//-------------------ARPEGGIATOR OCTAVE---------------------------------------------------------------
//0
void arp0(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, n0);
  myLeds.write(0,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(0,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//1
void arp1(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, n1);
  myLeds.write(1,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(1,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//2
void arp12(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, n1);
  myLeds.write(5, Offset, n2);
  myLeds.write(2,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(2,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//3
void arp123(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, n1);
  myLeds.write(5, Offset, n2);
  myLeds.write(9, Offset, n3);
  myLeds.write(3,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(3,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//4
void arp1234(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, n1);
  myLeds.write(5, Offset, n2);
  myLeds.write(9, Offset, n3);
  myLeds.write(13, Offset, n4);
  myLeds.write(4,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    myLeds.clear();
    myLeds.write(4,7,HIGH);
    disp->repeat = 2;
    //clear Update display bits 
    disp->Update = 0;
  }
}

//-------------------MENU--------------------------------------------------------------------------
//Key
void Key(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
  //write to LED Matrix
  myLeds.clear();
  myLeds.write(1, Offset, lK);
  myLeds.write(5, Offset, lE);
  myLeds.write(9, Offset, lY);
  myLeds.write(0,7,HIGH);

  if(disp->repeat <= repeat){
    //normal delay
    disp->Delay = DELAY_L;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    disp->repeat += 1;
  }
  else{
    //trigger sub menu update
    disp->index = 2;
    disp->Update = 2; 
    disp->count = 0;
    disp->timer = 0;
    disp->type = 2;
    disp->repeat = 0;
    myLeds.clear();
  }
}

//Scale
void Scale(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -16){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lS);
  myLeds.write((disp->index+4), Offset, lC);
  myLeds.write((disp->index+8), Offset, lA);
  myLeds.write((disp->index+12), Offset, lL);
  myLeds.write((disp->index+16), Offset, lE);
  myLeds.write(1,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
          //trigger sub menu update 
          disp->index = 2;
          disp->Update = 2; 
          disp->count = 0;
          disp->timer = 0;
          disp->type = 2;
          disp->repeat = 0;
          myLeds.clear();
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

//Harmony
void Harmony(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -24){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lH);
  myLeds.write((disp->index+4), Offset, lA);
  myLeds.write((disp->index+8), Offset, lR);
  myLeds.write((disp->index+12), Offset, lM);
  myLeds.write((disp->index+18), Offset, lO);
  myLeds.write((disp->index+22), Offset, lN);
  myLeds.write((disp->index+28), Offset, lY);
  myLeds.write(2,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
          //trigger sub menu update 
          disp->index = 2;
          disp->Update = 2; 
          disp->count = 0;
          disp->timer = 0;
          disp->type = 2;
          disp->repeat = 0;
          myLeds.clear();
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

//Arpeggiator Mode
void ArpeggiatorMode(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -56){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lA);
  myLeds.write((disp->index+4), Offset, lR);
  myLeds.write((disp->index+8), Offset, lP);
  myLeds.write((disp->index+12), Offset, lE);
  myLeds.write((disp->index+16), Offset, lG);
  myLeds.write((disp->index+21), Offset, lG);
  myLeds.write((disp->index+26), Offset, lI);
  myLeds.write((disp->index+30), Offset, lA);
  myLeds.write((disp->index+34), Offset, lT);
  myLeds.write((disp->index+38), Offset, lO);
  myLeds.write((disp->index+42), Offset, lR);
  myLeds.write((disp->index+47), Offset, lM);
  myLeds.write((disp->index+53), Offset, lO);
  myLeds.write((disp->index+57), Offset, lD);
  myLeds.write((disp->index+61), Offset, lE);
  myLeds.write(3,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //trigger sub menu update 
          disp->index = 2;
          disp->Update = 2; 
          disp->count = 0;
          disp->timer = 0;
          disp->type = 2;
          disp->repeat = 0;
          myLeds.clear();
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

//Arpeggiator Octave
void ArpeggiatorOct(struct sDisplay *disp, uint8_t repeat, uint8_t Offset){
  //Begin (set x to 2 in setup)
  disp->index-=1;
  if(disp->index <= -68){
      disp->index = 1;
      if(repeat > 1){
       disp->count += 1;
     }
  }

  //write to LED Matrix
  myLeds.clear();
  myLeds.write(disp->index, Offset, lA);
  myLeds.write((disp->index+4), Offset, lR);
  myLeds.write((disp->index+8), Offset, lP);
  myLeds.write((disp->index+12), Offset, lE);
  myLeds.write((disp->index+16), Offset, lG);
  myLeds.write((disp->index+21), Offset, lG);
  myLeds.write((disp->index+26), Offset, lI);
  myLeds.write((disp->index+30), Offset, lA);
  myLeds.write((disp->index+34), Offset, lT);
  myLeds.write((disp->index+38), Offset, lO);
  myLeds.write((disp->index+42), Offset, lR);
  myLeds.write((disp->index+47), Offset, lO);
  myLeds.write((disp->index+51), Offset, lC);
  myLeds.write((disp->index+55), Offset, lT);
  myLeds.write((disp->index+59), Offset, lA);
  myLeds.write((disp->index+63), Offset, lV);
  myLeds.write((disp->index+67), Offset, lE);
  myLeds.write(4,7,HIGH);

  if(disp->index == 1){
    //New iteration, display longer
    disp->Delay = DELAY_N;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
    // clear display
    if(disp->count >= repeat){
         //trigger sub menu update 
          disp->index = 2;
          disp->Update = 2; 
          disp->count = 0;
          disp->timer = 0;
          disp->type = 2;
          disp->repeat = 0;
          myLeds.clear();
    }
  }
  else{
    //normal delay
    disp->Delay = DELAY;
    //enable delay timer
    disp->Update ^= (-1^disp->Update)&(1<<2);
    //clear Update display bits 
    disp->Update &= ~(1<<0);
    disp->Update &= ~(1<<1);
  } 
}

#endif
