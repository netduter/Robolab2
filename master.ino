#include <math.h>
 
#define sizeOfIntervals (sizeof(interval)/sizeof(long))
#define sizeOfIntervalsBass (sizeof(intervalBass)/sizeof(long))
 
 
long interval[] = {0,96,192,384,480,576,768,864,960,1104,1152,1536,1632,1728,1872,1920,2016,2112,2208,2256,2304,2400,2496,2592,2688,2880,3072,3168,3264,3456,3552,3648,3840,3936,4032,4176,4224,4608,4704,4800,4944,4992,5088,5184,5280,5328,5376,5472,5568,5664,5760,6048,6144,6240,6336,6432,6528,6816,6864,6912,7008,7104,7200,7296,7584,7680,7776,7872,7968,8064,8352,8448,8544,8640,8736,8832,9120,9216,9312,9408,9504,9600,9888,9936,9984,10080,10176,10272,10368,10656,10752,10848,10944,11040,11136,11232,11328,11424,11520,11616,11712,11808,11904,12096,12288,12384,12480,12672,12768,12864,13056,13152,13248,13392,13440,13824,13920,14016,14160,14208,14304,14400,14496,14544,14592,14688,14784,14880,14976,15168,15360,15456,15552,15744,15840,15936,16128,16224,16320,16464,16512,16896,16992,17088,17232,17280,17376,17472,17568,17616,17664,17760,17856,17952,18048,18431};
int notes[] = {71,71,71,71,71,71,71,74,67,69,71,72,72,72,72,72,71,71,71,71,71,69,69,71,69,74,71,71,71,71,71,71,71,74,67,69,71,72,72,72,72,72,71,71,71,71,74,74,72,69,67,62,62,71,69,67,62,62,62,62,71,69,67,64,64,64,72,71,69,66,74,76,74,72,69,71,62,62,71,69,67,62,62,62,62,71,69,67,64,64,64,72,71,69,74,74,74,74,76,74,72,69,67,74,71,71,71,71,71,71,71,74,67,69,71,72,72,72,72,72,71,71,71,71,71,69,69,71,69,74,71,71,71,71,71,71,71,74,67,69,71,72,72,72,72,72,71,71,71,71,74,74,72,69,67};
 
long intervalBass[] = {0,384,768,1152,1536,1920,2304,2688,2880,3072,3456,3840,4224,4608,4992,5376,5760,6144,6528,6912,7296,7680,8064,8448,8832,9216,9600,9984,10368,10752,11136,11520,11904,12288,12672,13056,13440,13824,14208,14592,14976,15168,15360,15744,16128,16512,16896,17280,17664,18048,18431};
int notesBass[] = {55,55,55,47,48,47,49,50,54,55,55,55,47,48,47,54,55,50,50,50,48,48,54,54,55,50,50,50,48,48,54,54,55,55,55,55,47,48,47,49,50,54,55,55,55,47,48,47,54,55};
 
float BPM = 190;
double del = 60000/BPM / 100; //Converting BPM to milliseconds delay, reference http://www.sengpielaudio.com/calculator-bpmtempotime.htm
 
unsigned long time;
 
int noteToHz(int note){ //69 is C5
  float relativeNote = note-69;
  float freq = pow(2,(relativeNote/12))*440; //Convert note to frequency, reference https://newt.phys.unsw.edu.au/jw/notes.html
  return (int)freq;
}
 
void timedActionLoop(){
  static unsigned long previousTime = 0;
  unsigned long now = millis();
 
  bool play = false;
  int noteToPlay = 0;
 
  for(int i = 0; i<sizeOfIntervals-1; i++){
    if(now - previousTime >= interval[i]*del && now - previousTime < interval[i+1]*del - 20){ //20 milliseconds delay between notes
      noteToPlay = noteToHz(notes[i]);
      play = true;
    }
  }
 
  if(now - previousTime >= interval[sizeOfIntervals-1]*del){
    play = false;
  }
 
  if(play){
    tone(6, noteToPlay);
  }
  else{
    noTone(6);
  }
}
void timedActionBassLoop(){
  static unsigned long previousTimeBass = 0;
  unsigned long now = millis();
 
  bool play = false;
  int noteToPlay = 0;
 
  for(int i = 0; i<sizeOfIntervalsBass-1; i++){
    if(now - previousTimeBass >= intervalBass[i]*del && now - previousTimeBass < intervalBass[i+1]*del - 20){ //20 milliseconds delay between notes
      noteToPlay = noteToHz(notesBass[i]);
      play = true;
    }
  }
 
  if(now - previousTimeBass >= intervalBass[sizeOfIntervalsBass-1]*del){
    play = false;
  }
 
  if(play){
    Serial.println(noteToPlay);
  }
  else{
    Serial.println("-1"); //when slave reads -1, it will execute noTone();
  }
}
 
void setup() {
  Serial.begin(9600);
  while (! Serial);
}
void loop() {
  timedActionLoop(); //Primary
  timedActionBassLoop(); //Secondary
}
