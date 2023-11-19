/**********************************************************************/
/*This code is not clean and OFFCOURSE will be possible do it better! */ 
/*this is only a group of functions to be used as independent code,  */ 
/*and by this way will be possible to any person can do the changes   */ 
/*of code and see what happen.                                         */
/*The code don't depend of any external library or extenal functions  */
/*complicated.                                                         */
/*I'm let the values to sent as binnary, this allow swap bit by bit */
/* to is possible test segment by segment without convert to HEX    */
/**********************************************************************/
/* This code show how is possible work with the driver LC75823 Sanyo */
/*Begining of Auto generated code by Atmel studio */

#define LCD_in 8  // This is the pin number 8 on Arduino UNO
#define LCD_clk 9 // This is the pin number 9 on Arduino UNO
#define LCD_ce 10 // This is the pin number 10 on Arduino UNO
#define LCD_inh 11 // This is the pin number 11 on Arduino UNO  //If you want, you can put this pin (/INH) at HIGH with a resistor of 10K
//ATT: On the Uno and other ATMEGA based boards, unsigned ints (unsigned integers) are the same as ints in that they store a 2 byte value.
//Long variables are extended size variables for number storage, and store 32 bits (4 bytes), from -2,147,483,648 to 2,147,483,647.

//*************************************************//
unsigned int shiftBit=0;
unsigned int nBitOnBlock=0; // Used to count number of bits and split to 8 bits... (number of byte)
unsigned int nByteOnBlock=0; 
unsigned int sequencyByte=0x00;
byte Aa,Ab,Ac,Ad,Ae,Af,Ag,Ah,Ai,Aj,Ak,Al,Am,An,Ao,Ap,Aq,Ar,As,At;
byte blockBit =0x00;
byte low = 0x00;
byte high = 0x00;

#define BUTTON_PIN 2 //Att check wich pins accept interrupts... Uno is 2 & 3
volatile byte buttonReleased = false;
uint16_t ascii = 0x0000;
int buttonState = 0;  // variable for reading the pushbutton status
//
//Pay attention to the metod to send as 16 bit's or 8 bit's. It is very importante the sequence of words!
const uint16_t asciiMsg[10] ={0x6826,    0x00E0,    0xC000,    0x6114,    0x360C,    0x9802,    0xC418,    0x0091,    0x0000,    0x0000};
unsigned char ascii8Msg[20] ={0x26,0x68, 0xE0,0x00, 0x00,0xC0, 0x14,0x61, 0x0C,0x36, 0x02,0x98, 0x18,0xC4, 0x91,0x00, 0x00,0x00, 0x00,0x00};
/*
*The ASCII table below represents some characters that can be represented in the 14-segment digit
* It is necessary to take into account that the middle vertical segment is not divided, but the horizontal is
* divided what can be a gain when drawing some characters.
*/
const uint16_t asciiChar[65] ={
    0x0000, // Space
    0x0000, // !
    0x0410, // "
    0x0000, // #
    0x0000, // $
    0x0000, // %
    0x0000, // &
    0x0400, // '
    0x0600, // (
    0x0018, // )
    0x0718, // *
    0x0920, // +
    0x0008, // ,
    0x0820, // -
    0x0200, // .
    0x0408, // /
    0x64ce, // 0
    0x6400, // 1
    0x28e4, // 2
    0x68e0, // 3
    0x6822, // 4
    0x48e2, // 5
    0x48e6, // 6
    0x0488, // 7
    0x68e6, // 8
    0x68e2, // 9
    0x0000, // :
    0x0000, // ;
    0x0000, // <
    0x0860, // =
    0x0000, // >
    0x0000, // ?
    0x0000, // @
    0x68a6, // A
    0x69c0, // B
    0x00c6, // C
    0x61c0, // D
    0x08e6, // E
    0x08a6, // F  
    0x48c6, // G
    0x6826, // H
    0x0100, // I 
    0x6044, // J
    0x0700, // K
    0x0046, // L
    0x6416, // M
    0x6216, // N
    0x60c6, // O 
    0x28a6, // P
    0x62c6, // Q
    0x2aa6, // R
    0x48d0, // S
    0x0180, // T
    0x6046, // U
    0x040e, // V
    0x620E, // W
    0x0618, // X
    0x0418, // Y
    0x04c8, // Z
    0x0000, // [
    0x0210, // back slash
    0x7FFF, // ]
    0x0208, // ^
    0x0040, // _
    0x0010  // `
  };
const unsigned short asciiShort[38] ={
    0x0000, // Space
    0x64ce, // 0
    0x6400, // 1
    0x28e4, // 2
    0x68e0, // 3
    0x6822, // 4
    0x48e2, // 5
    0x48e6, // 6
    0x0488, // 7
    0x68e6, // 8
    0x68e2, // 9
    0x68a6, // A
    0x69c0, // B
    0x00c6, // C
    0x61c0, // D
    0x08e6, // E
    0x08a6, // F
    0x48c6, // G
    0x6826, // H
    0x0100, // I
    0x6044, // J
    0x0700, // K
    0x0046, // L
    0x6416, // M
    0x6216, // N
    0x60c6, // O
    0x28a6, // P
    0x62c6, // Q
    0x2aa6, // R
    0x48d0, // S
    0x0180, // T
    0x6046, // U
    0x040e, // V
    0x620E, // W
    0x0618, // X
    0x0418, // Y
    0x04c8  // Z
  };
const unsigned short asciiShortId[38] ={
  's','0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','X','Y','Z'
};
const unsigned short binarySeg[18] = {0x0000,0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000,0x0000};

void setup() 
{
  pinMode(LCD_clk, OUTPUT);
  pinMode(LCD_in, OUTPUT);
  pinMode(LCD_ce, OUTPUT);
 
  pinMode(13, OUTPUT);

// initialize the pushbutton pin as an input:
//pinMode(buttonPin, INPUT);  //Next line is the attach of interruption to pin 2
pinMode(BUTTON_PIN, INPUT);

 attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),
                  buttonReleasedInterrupt,
                  FALLING);

//Dont insert any print inside of interrupt function!!!
//If you run the search function, please active the terminal to be possible print lines,
//Other way the run will be blocked!
//
  Serial.begin(115200); // only to debug
}
void send_char(unsigned char a)
{
 //
 unsigned char transmit = 15; //define our transmit pin
 unsigned char data = 170; //value to transmit, binary 10101010
 unsigned char mask = 1; //our bitmask
  data=a;
  // the validation of data happen when clk go from LOW to HIGH.
  digitalWrite(LCD_ce, LOW); // When strobe is low, all output is enable. If high, all output will be set to low.
  delayMicroseconds(5);
  digitalWrite(LCD_clk,LOW);// need invert the signal to allow 8 bits is is low only send 7 bits
  delayMicroseconds(5);
  for (mask = 0b00000001; mask>0; mask <<= 1) { //iterate through bit mask
  digitalWrite(LCD_clk,LOW);// need invert the signal to allow 8 bits is is low only send 7 bits
  delayMicroseconds(5);
    if (data & mask){ // if bitwise AND resolves to true
      digitalWrite(LCD_in, HIGH);
      //Serial.print(1);
    }
    else{ //if bitwise and resolves to false
      digitalWrite(LCD_in, LOW);
      //Serial.print(0);
    }
    digitalWrite(LCD_clk,HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(5);
    //
    digitalWrite(LCD_ce, HIGH); // When strobe is low, all output is enable. If high, all output will be set to low.
  delayMicroseconds(5);
  }
}
/*********************************************************************/
// I h've created 3 functions to send bit's, one with strobe, other without strobe and one with first byte with strobe followed by remaing bits.
void send_char_without(unsigned char a)
{
 unsigned char data = 170; //value to transmit, binary 10101010
 unsigned char mask = 1; //our bitmask
  data=a;
  for (mask = 0b00000001; mask>0; mask <<= 1) { //iterate through bit mask
  digitalWrite(LCD_clk, LOW);
  delayMicroseconds(5);
    if (data & mask){ // if bitwise AND resolves to true
      digitalWrite(LCD_in, HIGH);
     Serial.print(1);
    }
    else{ //if bitwise and resolves to false
      digitalWrite(LCD_in, LOW);
      Serial.print(0);
    }
    digitalWrite(LCD_clk,HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(5);
  }
  digitalWrite(LCD_clk, LOW);
  Serial.println(" 8 Bits Sent ");
}
void send_ascii_without(uint16_t a)
{
 uint16_t data = 170; //Note here we use a length of 16 bits
 uint16_t mask = 0x0001; //our bitmask
  data=a;
  for (mask = 0x0001; mask >0; mask <<= 1) { //iterate through bit mask and skip the 0, because the LC75823E and the LCD skip the 0 in this panel!
  digitalWrite(LCD_clk, LOW);
  delayMicroseconds(2);
      if (data & mask){ // if bitwise AND resolves to true
       digitalWrite(LCD_in, HIGH);
       Serial.print(1);
      }
      else{ //if bitwise and resolves to false
       digitalWrite(LCD_in, LOW);
       Serial.print(0);
      }
    digitalWrite(LCD_clk,HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(2);
  }
  //digitalWrite(LCD_clk, LOW);
  Serial.println(" 16 Bits Sent ");
}
/*********************************************************************/
void send_char_8bit_stb(unsigned char a)
{
 unsigned char data = 170; //value to transmit, binary 10101010
 unsigned char mask = 1; //our bitmask
 int i = -1;
  data=a;
  for (mask = 0b00000001; mask>0; mask <<= 1) { //iterate through bit mask
   i++;
   digitalWrite(LCD_clk, LOW);
  delayMicroseconds(5);
    if (data & mask){ // if bitwise AND resolves to true
      digitalWrite(LCD_in, HIGH);
      //Serial.print(1);
    }
    else{ //if bitwise and resolves to false
      digitalWrite(LCD_in, LOW);
      //Serial.print(0);
    }
    digitalWrite(LCD_clk,HIGH);// 
    delayMicroseconds(1);
    if (i==7){
    //Serial.println(i);
    digitalWrite(LCD_ce, HIGH);
    delayMicroseconds(2);
    }  
  }
}
/*******************************************************************/
void allON_LC75823()
{
unsigned char group=0;
//send total of 56 bits (7Bytes), the 4 last 14 bits belongs to controls    
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      // Position of bit(..76543210)
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);   
          send_char_without(0B11111111);  send_char_without(0B11111111); //   1:8     -9:16// 
          send_char_without(0B11111111);  send_char_without(0B11111111); //  17:24    -25:32// 
          send_char_without(0B11111111);  send_char_without(0B11111111); //  33:40    -41:48//
          send_char_without(0B11111111);  send_char_without(0B11111111); //  49:56    -57:64//
          send_char_without(0B11111111);  send_char_without(0B11111111); //  65:72    -73:80//
          send_char_without(0B11111111);  send_char_without(0B11111111); //  81:88    -89:96//
          send_char_without(0B11111111);  send_char_without(0B11111111); //  97:104   -105:112//
          send_char_without(0B11111111);  send_char_without(0B11111111); // 113:120   -121:128// 
          send_char_without(0B11111111);  send_char_without(0B11111111); // 120:136   -137:144// 
          send_char_without(0B11111111);  send_char_without(0B00011111); // 145:152   -153:160//      
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
/**************************************************************************/
void allOFF_LC75823()
{
unsigned char group=0;
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_char_without(0B00000000);  send_char_without(0B00000000); //   1:8     -9:16// 
          send_char_without(0B00000000);  send_char_without(0B00000000); //  17:24    -25:32// 
          send_char_without(0B00000000);  send_char_without(0B00000000); //  33:40    -41:48//
          send_char_without(0B00000000);  send_char_without(0B00000000); //  49:56    -57:64//
          send_char_without(0B00000000);  send_char_without(0B00000000); //  65:72    -73:80//
          send_char_without(0B00000000);  send_char_without(0B00000000); //  81:88    -89:96//
          send_char_without(0B00000000);  send_char_without(0B00000000); //  97:104   -105:112//
          send_char_without(0B00000000);  send_char_without(0B00000000); // 113:120   -121:128// 
          send_char_without(0B00000000);  send_char_without(0B00000000); // 120:136   -137:144// 
          send_char_without(0B00000000);  send_char_without(0B00010000); // 145:152   -153:160//
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}

void HiFolks()
{
//send total of 160 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care.
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_char_without(0b00100110);  send_char_without(0b01101000);  //   8:1     -16:9//    //H 0x26, 0x68
          send_char_without(0b11100000);  send_char_without(0b00000000);  //  24:17    -32:25//   //I 0xE0, 0x00
          send_char_without(0b00000000);  send_char_without(0b11000000);  //  40:33    -48:41//   //  0x00, 0x00
          send_char_without(0b00010100);  send_char_without(0b01100001);  //  56:49    -64:57//   //F 0x14, 0x61
          send_char_without(0b00001100);  send_char_without(0b00110110);  //  72:65    -80:73//   //O 0x0C, 0x36
          send_char_without(0b00000010);  send_char_without(0b10011000);  //  88:81    -96:89//   //L 0x02, 0x98
          send_char_without(0b00011000);  send_char_without(0b11000100);  //  104:97   -112:105// //K 0x18, 0xC4
          send_char_without(0b10010001);  send_char_without(0b00000000);  //  120:113  -128:121// //S 0x91, 0x00
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  136:129  -144:137//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime136(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_char_without(0b00000000);  send_char_without(0b10000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b01000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00010000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b11111110);  send_char_without(0b11111110);  //  136:129  -144:137//  
          send_char_without(0b11111110);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime135(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_char_without(0b00000000);  send_char_without(0b10000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00100000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00010000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b01000000);  send_char_without(0b00000010);  //  104:97   -112:105//  
          send_char_without(0b00100000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b01111110);  send_char_without(0b01111110);  //  136:129  -144:137//  
          send_char_without(0b01111110);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime134(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_char_without(0b00000000);  send_char_without(0b10000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00100000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00010000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b01000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00100000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00111110);  send_char_without(0b00111110);  //  136:129  -144:137//  
          send_char_without(0b00111110);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime133(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);   
          send_char_without(0b00000000);  send_char_without(0b00000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b01000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00100000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00010000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00100000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00011110);  send_char_without(0b00011110);  //  136:129  -144:137//  
          send_char_without(0b00011110);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime132(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);     
          send_char_without(0b00000000);  send_char_without(0b10000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b01000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00100000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00010000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b01000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00001110);  send_char_without(0b00001110);  //  136:129  -144:137//  
          send_char_without(0b00001110);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime131(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);      
          send_char_without(0b00000000);  send_char_without(0b10000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b01000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00100000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b01000000);  send_char_without(0b00000010);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00000110);  send_char_without(0b00000110);  //  136:129  -144:137//  
          send_char_without(0b00000110);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime130(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);      
          send_char_without(0b00000000);  send_char_without(0b00000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b01000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00010000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00000010);  send_char_without(0b00000010);  //  136:129  -144:137//  
          send_char_without(0b00000010);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
//
void anime144(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);   
          send_char_without(0b00000000);  send_char_without(0b00000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00000000);  send_char_without(0b10000000);  //  136:129  -144:137//  
          send_char_without(0b10000000);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime143(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_char_without(0b00000000);  send_char_without(0b00000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00000000);  send_char_without(0b11000000);  //  136:129  -144:137//  
          send_char_without(0b11000000);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime142(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1); 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00000000);  send_char_without(0b11100000);  //  136:129  -144:137//  
          send_char_without(0b11100000);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime141(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b0000000);  send_char_without(0b11110000);  //  136:129  -144:137//  
          send_char_without(0b11110000);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime140(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1); 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00000000);  send_char_without(0b11111000);  //  136:129  -144:137//  
          send_char_without(0b11111000);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime139(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_char_without(0b00000000);  send_char_without(0b00000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00000000);  send_char_without(0b11111100);  //  136:129  -144:137//  
          send_char_without(0b11111100);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime138(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);       
          send_char_without(0b00000000);  send_char_without(0b00000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00000000);  send_char_without(0b11111110);  //  136:129  -144:137//  
          send_char_without(0b11111110);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
//
void anime152(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);    
          send_char_without(0b00000000);  send_char_without(0b00000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  136:129  -144:137//  
          send_char_without(0b10000000);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime151(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_char_without(0b00000000);  send_char_without(0b00000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  136:129  -144:137//  
          send_char_without(0b11000000);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime150(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_char_without(0b00000000);  send_char_without(0b00000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  136:129  -144:137//  
          send_char_without(0b11100000);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime149(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_char_without(0b00000000);  send_char_without(0b00000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  136:129  -144:137//  
          send_char_without(0b11110000);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime148(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_char_without(0b00000000);  send_char_without(0b00000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  136:129  -144:137//  
          send_char_without(0b11111000);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime147(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  136:129  -144:137//  
          send_char_without(0b11111100);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void anime146(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_char_without(0b00000000);  send_char_without(0b00000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  136:129  -144:137//  
          send_char_without(0b11111110);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
//
void animeOFF(){
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_char_without(0b00000000);  send_char_without(0b00000000);  //   8:1     -16:9// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  24:17    -32:25//
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  40:33    -48:41// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  56:49    -64:57// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  72:65    -80:73// 
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  88:81    -96:89//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  104:97   -112:105//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  120:113  -128:121//   
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  136:129  -144:137//  
          send_char_without(0b00000000);  send_char_without(0b00000000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}

void asciiTesMsgHiFolks(unsigned int s)
{
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
uint16_t letter = 0x0000;

letter = (asciiMsg[s]);
letter = (letter << 1);
Serial.println(letter, BIN);
Serial.println(s, DEC);
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_ascii_without(asciiMsg[s]);       //   8:1     -16:9//
          send_ascii_without(asciiMsg[s+1]);     //  24:17    -32:25//
          send_ascii_without(asciiMsg[s+2]);     //  40:33    -48:41// 
          send_ascii_without(asciiMsg[s+3]);     //  56:49    -64:57// 
          send_ascii_without(asciiMsg[s+4]);     //  72:65    -80:73// 
          send_ascii_without(asciiMsg[s+5]);    //  88:81    -96:89//  
          send_ascii_without(asciiMsg[s+6]);    //  104:97   -112:105//  
          send_ascii_without(asciiMsg[s+7]);    //  120:113  -128:121//   
          send_ascii_without(asciiMsg[s+8]);    //  136:129  -144:137//  
          send_ascii_without(0x0000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void asciiMsgHiFolks(unsigned int s)
{
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
uint16_t letter = 0x0000;

letter = (asciiMsg[s]);
letter = (letter << 1);
Serial.println(letter, BIN);
Serial.println(s, DEC);
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_char_without(ascii8Msg[s+0]); 
          send_char_without(ascii8Msg[s+1]);       //   8:1     -16:9//
          
          send_char_without(ascii8Msg[s+2]); 
          send_char_without(ascii8Msg[s+3]);     //  24:17    -32:25//
          
          send_char_without(ascii8Msg[s+4]); 
          send_char_without(ascii8Msg[s+5]);     //  40:33    -48:41//
           
          send_char_without(ascii8Msg[s+6]); 
          send_char_without(ascii8Msg[s+7]);     //  56:49    -64:57//
           
          send_char_without(ascii8Msg[s+8]); 
          send_char_without(ascii8Msg[s+9]);     //  72:65    -80:73// 
          send_char_without(ascii8Msg[s+10]); 
          send_char_without(ascii8Msg[s+11]);    //  88:81    -96:89//  
          send_char_without(ascii8Msg[s+12]); 
          send_char_without(ascii8Msg[s+13]);   //  104:97   -112:105//  
          send_char_without(ascii8Msg[s+14]); 
          send_char_without(ascii8Msg[s+15]);   //  120:113  -128:121//   
          send_char_without(ascii8Msg[s+16]); 
          send_char_without(ascii8Msg[s+17]);   //  136:129  -144:137//  
          send_char_without(ascii8Msg[s+18]);  
          send_char_without(0x00);//  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void asciiShift(uint8_t s)
{
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
uint16_t letter = 0x00;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_ascii_without(asciiChar[s]);       //   8:1     -16:9//
          //
          letter = (asciiChar[s]); letter = (letter >> 1);
          send_ascii_without(letter);//  24:17    -32:25//
          letter = (asciiChar[s]); letter = (letter >> 2);
          send_ascii_without(letter);//  40:33    -48:41// 
          letter = (asciiChar[s]); letter = (letter >> 3);
          send_ascii_without(letter);//  56:49    -64:57// 
          letter = (asciiChar[s]); letter = (letter >> 4);
          send_ascii_without(letter);//  72:65    -80:73// 
          letter = (asciiChar[s]); letter = (letter >> 5);
          send_ascii_without(letter);//  88:81    -96:89//
          letter = (asciiChar[s]); letter = (letter >> 6);
          send_ascii_without(letter);//  104:97   -112:105//
          letter = (asciiChar[s]); letter = (letter >> 7);
          send_ascii_without(letter);//  120:113  -128:121//   
          letter = (asciiChar[s]); letter = (letter >> 8);
          send_ascii_without(letter);//  136:129  -144:137// 
          //    
          send_ascii_without(0x0000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void asciiTestDigit0(uint8_t s)
{
//send total of 160 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
      //Note: The ASCII table working only at first digit, is necessary do a shift to the other's
      //But because the skip is not allways the same, it becames a difficulty
          send_ascii_without(asciiChar[s]);   //   8:1     -16:9//
          send_ascii_without(asciiChar[0]);   //  24:17    -32:25//
          send_ascii_without(asciiChar[0]);   //  40:33    -48:41// 
          send_ascii_without(asciiChar[0]);   //  56:49    -64:57// 
          send_ascii_without(asciiChar[0]);   //  72:65    -80:73// 
          send_ascii_without(asciiChar[0]);   //  88:81    -96:89//  
          send_ascii_without(asciiChar[0]);   //  104:97   -112:105//  
          send_ascii_without(asciiChar[0]);   //  120:113  -128:121//   
          send_ascii_without(asciiChar[0]);   //  136:129  -144:137//  
          send_ascii_without(0x0000);         //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void asciiTextFix(uint8_t s)
{
//send total of 160 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_ascii_without(asciiMsg[s+0]);  //   8:1     -16:9// 
          send_ascii_without(asciiMsg[s+1]);  //  24:17    -32:25//
          send_ascii_without(asciiMsg[s+2]);  //  40:33    -48:41// 
          send_ascii_without(asciiMsg[s+3]);  //  56:49    -64:57// 
          send_ascii_without(asciiMsg[s+4]);  //  72:65    -80:73// 
          send_ascii_without(asciiMsg[s+5]);  //  88:81    -96:89//  
          send_ascii_without(asciiMsg[s+6]);  //  104:97   -112:105//  
          send_ascii_without(asciiMsg[s+7]);  //  120:113  -128:121//   
          send_ascii_without(asciiMsg[s+7]);  //  136:129  -144:137//  
          send_ascii_without(0x0000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void asciiNumbersLetters(uint8_t s)
{
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_ascii_without(asciiShort[s]);  //   8:1     -16:9// 
          send_ascii_without(asciiShort[s]);  //  24:17    -32:25//
          send_ascii_without(asciiShort[s]);  //  40:33    -48:41// 
          send_ascii_without(asciiShort[0]);  //  56:49    -64:57// 
          send_ascii_without(asciiShort[0]);  //  72:65    -80:73// 
          send_ascii_without(asciiShort[0]);  //  88:81    -96:89//  
          send_ascii_without(asciiShort[0]);  //  104:97   -112:105//  
          send_ascii_without(asciiShort[0]);  //  120:113  -128:121//   
          send_ascii_without(asciiShort[0]);  //  136:129  -144:137//  
          send_ascii_without(0x0000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void asciiBinary(uint8_t s)
{
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_ascii_without(binarySeg[s]);  //   8:1     -16:9// 
          send_ascii_without(binarySeg[s]);  //  24:17    -32:25//
          send_ascii_without(binarySeg[s]);  //  40:33    -48:41// 
          send_ascii_without(binarySeg[s]);  //  56:49    -64:57// 
          send_ascii_without(binarySeg[s]);  //  72:65    -80:73// 
          send_ascii_without(binarySeg[s]);  //  88:81    -96:89//  
          send_ascii_without(binarySeg[s]);  //  104:97   -112:105//  
          send_ascii_without(binarySeg[s]);  //  120:113  -128:121//   
          send_ascii_without(binarySeg[s]);  //  136:129  -144:137//  
          send_ascii_without(0x0000);  //  152:145  -160:153//  
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); // 
      delayMicroseconds(1);
}
void animation1(){
  unsigned int t=175;
  for (int i = 0; i<4; i++){
  anime130();
  delay(t);
  anime131();
  delay(t);
  anime132();
  delay(t);
  anime133();
  delay(t);
  anime134();
  delay(t);
  anime135();
  delay(t);
  anime136();
  delay(t);
  animeOFF();
  delay(t);
}
}
void animation2(){
  for (int i = 0; i<4; i++){
  anime138();
  delay(100);
  anime139();
  delay(100);
  anime140();
  delay(100);
  anime141();
  delay(100);
  anime142();
  delay(100);
  anime143();
  delay(100);
  anime144();
  delay(100);
  animeOFF();
  delay(100);
}
}
void animation3(){
for (int i = 0; i<4; i++){
  anime146();
  delay(100);
  anime147();
  delay(100);
  anime148();
  delay(100);
  anime149();
  delay(100);
  anime150();
  delay(100);
  anime151();
  delay(100);
  anime152();
  delay(100);
  animeOFF();
  delay(100);
}

}
/*******************************************************************/
void searchOfSegments(){
// put your main code here, to run repeatedly:
  int group = 0x00;
  byte nBit =0x00;
  byte nMask = 0b00000001;
  unsigned int block =0;
  unsigned int nSeg=0x000;  // This variable need support more of 255 (600 segments)
  Serial.println();
  Serial.println("We start the test of segments!");
for( group=0; group<=19; group++){   // Do until n bits 15*8 bits
       
          for (nMask = 0b00000001; nMask>0; nMask <<= 1){
            Aa=0x00; Ab=0x00; Ac=0x00; Ad=0x00; Ae=0x00; Af=0x00; Ag=0x00; Ah=0x00; Ai=0x00; Aj=0x00;
            Ak=0x00; Al=0x00; Am=0x00; An=0x00; Ao=0x00; Ap=0x00; Aq=0x00; Ar=0x00; As=0x00; At=0x00;
                  switch (group){
                    case 0: Aa=nMask; break;
                    case 1: Ab=nMask; break;
                    case 2: Ac=nMask; break;
                    case 3: Ad=nMask; break;
                    case 4: Ae=nMask; break;
                    case 5: Af=nMask; break;
                    case 6: Ag=nMask; break;
                    case 7: Ah=nMask; break;
                    case 8: Ai=nMask; break;
                    case 9: Aj=nMask; break;
                    case 10: Ak=nMask; break;
                    case 11: Al=nMask; break;
                    case 12: Am=nMask; break;
                    case 13: An=nMask; break;
                    case 14: Ao=nMask; break;
                    case 15: Ap=nMask; break;
                    case 16: Aq=nMask; break;
                    case 17: Ar=nMask; break;
                    case 18: As=nMask; break;
                    case 19: At=nMask; break;
                  }
            
           nSeg++;
          
      //This start the control of button to allow continue teste! 
                      while(1){
                            if(!buttonReleased){
                              delay(200);
                            }
                            else{
                              delay(15);
                               buttonReleased = false;
                               break;
                               }
                         }
               delay(50);
                     segments();
            Serial.print(nSeg, DEC); Serial.print(", group: "); Serial.print(group, DEC);Serial.print(", BlockBit: "); Serial.print(blockBit, HEX);Serial.print(", nMask: "); Serial.print(nMask, BIN);Serial.print("   \t");
            Serial.print(At, HEX);Serial.print(", ");Serial.print(As, HEX);Serial.print(", ");Serial.print(Ar, HEX);Serial.print(", ");Serial.print(Aq, HEX);Serial.print(", ");Serial.print(Ap, HEX); Serial.print("; ");
            Serial.print(Ao, HEX);Serial.print(", ");Serial.print(An, HEX);Serial.print(", ");Serial.print(Am, HEX);Serial.print(", ");Serial.print(Al, HEX);Serial.print(", ");Serial.print(Ak, HEX); Serial.print("; ");
            Serial.print(Aj, HEX);Serial.print(", ");Serial.print(Ai, HEX);Serial.print(", ");Serial.print(Ah, HEX);Serial.print(", ");Serial.print(Ag, HEX);Serial.print(", ");Serial.print(Af, HEX); Serial.print("; ");
            Serial.print(Ae, HEX);Serial.print(", ");Serial.print(Ad, HEX);Serial.print(", ");Serial.print(Ac, HEX);Serial.print(", ");Serial.print(Ab, HEX);Serial.print(", ");Serial.print(Aa, HEX); Serial.print("; ");
            
            Serial.println();
            delay (250);           
           }        
      }
  }

void segments(){
//Bit function: 
      digitalWrite(LCD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x4B) firts 8 bits is address, every fixed as (0B01000010), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
      // 
          send_char_without(~Aa);  send_char_without(~Ab);  //   8:1     -16:9// 
          send_char_without(~Ac);  send_char_without(~Ad);  //  24:17    -32:25//
          send_char_without(~Ae);  send_char_without(~Af);  //  40:33    -48:41// 
          send_char_without(~Ag);  send_char_without(~Ah);  //  56:49    -64:57// 
          send_char_without(~Ai);  send_char_without(~Aj);  //  72:65    -80:73// 
          send_char_without(~Ak);  send_char_without(~Al);  //  88:81    -96:89//  
          send_char_without(~Am);  send_char_without(~An);  //  104:97   -112:105//  
          send_char_without(~Ao);  send_char_without(~Ap);  //  120:113  -128:121//   
          send_char_without(~Aq);  send_char_without(~Ar);  //  136:129  -144:137//  
          send_char_without(~As);  send_char_without(At);  //  152:145  -160:153// //Please is very important you don't invert the last 4 bits!!!
      //   
      delayMicroseconds(1);
      digitalWrite(LCD_ce, LOW); //                   
}

void loop() {
   for(uint8_t s = 0; s<4; s++){
    allOFF_LC75823(); // All off
    delay(500);
    allON_LC75823(); // All on
    delay(1000);
  }
//Here we write directley at the table of segments.    
HiFolks(); 
delay(3000);
//Here is the sequence of animations
animation1();
animation2();
animation3();
//Here we run the array of "short", is one way to write the message.
asciiMsgHiFolks(0);  
delay(1000);
// All off
allOFF_LC75823(); 
delay(500);
//
  for (unsigned int v = 0; v < 65; v++){
     asciiTestDigit0(v);
     delay(200); 
  }
//
//Here only some digits is write correctley, optimize the shift Please!  
  for (uint8_t v = 0; v< 65; v++){
    asciiShift(v); 
   delay(200); 
  }
//
//Here we write the text present at table: asciiMsg.
asciiTextFix(0);
delay(2000);
//
allOFF_LC75823(); // All off
//searchOfSegments(); //Uncomment this line if you want run the find segments
}

void buttonReleasedInterrupt() {
  buttonReleased = true; // This is the line of interrupt button to advance one step on the search of segments!
}
