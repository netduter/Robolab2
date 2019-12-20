SoftwareSerial mySerial(2, 3); // RX, TX

int previousNote = 0;

void setup() {

  Serial.begin(9600);

}

String msg="";

void loop() {

  char c;  
  
  do{
    while(Serial.available()==0);
    

    c=Serial.read();
  
    msg+=c;
    
  }while(c!='\n' && c!='\r');

  if(msg.toInt()==-1){

    noTone(6);
  }else{

    if(msg.length()>1){


        previousNote = msg.toInt();

        tone(6,msg.toInt());

    }
    
    
  }
  
  msg="";
  
}
