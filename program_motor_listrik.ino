#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
#include "call.h"
#define led 10
CallGSM call;
SMSGSM sms;
int poin=0;
char number[20];
int numdata;
byte stat=0;
boolean started = false;
char smsbuffer[160];
char n[20];

void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  if (gsm.begin(2400)) {
    started = true;
  }
  delsms();
}

void loop()
{
  stat=call.CallStatusWithAuth(number,0,0);
   if(stat==CALL_INCOM_VOICE_AUTH)
   {
      digitalWrite(led,HIGH);
      delay(200);
      digitalWrite(led,LOW);
      delay(200);
      poin=1;
   }
   else if((!stat==CALL_INCOM_VOICE_AUTH)&&(poin==1)){
      digitalWrite(led,LOW);
      delay(10);
      poin=0;
    }
  int pos = 0;
  if (started) {
    pos = sms.IsSMSPresent(SMS_ALL);
    if (pos) {
      sms.GetSMS(pos, n, 20, smsbuffer, 160);
      delay(50);
      if (!strcmp(smsbuffer, "on")) {
        digitalWrite(led,HIGH);
      }
      if (!strcmp(smsbuffer, "off")) {
        digitalWrite(led,LOW);
      }
      delsms();
    }
  }
}


void delsms() {
  for (int i = 0; i < 10; i++) {
    int pos = sms.IsSMSPresent(SMS_ALL);
    if (pos != 0){
      if (sms.DeleteSMS(pos) == 1) {} else {}
    }
  }
}
