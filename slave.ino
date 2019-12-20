SoftwareSerial mySerial(2, 3); // RX, TX

int previousNote = 0;

void setup() {

  Serial.begin(9600);

}

String msg="";

void loop() {

  char c;  
  
  do{
    while(Serial.available()==0);// Ο slave περιμένει μέχρι ο master να στείλει μήνυμα προκειμένου να παίξει κάποια νότα.
    

    c=Serial.read();
  
    msg+=c;
    
  }while(c!='\n' && c!='\r');

  if(msg.toInt()==-1){ // Ο master στέλνει "-1" αν θελει ο slave να σταματήσει την αναπαραγωγή κάποιας νότας.
    noTone(6);
  }else{

    if(msg.length()>1){//Εξασφαλίζει ότι θα αγνοηθούν πιθανά σκουπίδια.


        previousNote = msg.toInt();

        tone(6,msg.toInt());

    }
    
    
  }
  
  msg="";
  
}
