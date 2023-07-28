int FUNZIONESPARO()
{
    //Serial.println("funzione sparo");
    digitalWrite(ledfiam, HIGH);
    digitalWrite(buzsp, HIGH);
    digitalWrite(IR555, HIGH);
    delayMicroseconds(BitStart);
    digitalWrite(IR555, LOW);
    delayMicroseconds(basso);
    switch (SQUADRA)
    {
      case 0: digitalWrite(IR555, HIGH);
                delayMicroseconds(bin_0);
                digitalWrite(IR555, LOW);
                delayMicroseconds(basso);
                digitalWrite(IR555, HIGH);
                delayMicroseconds(bin_0);
                digitalWrite(IR555, LOW);
                delayMicroseconds(basso);
                break;
                
      case 1: digitalWrite(IR555, HIGH);
                delayMicroseconds(bin_1);
                digitalWrite(IR555, LOW);
                delayMicroseconds(basso);
                digitalWrite(IR555, HIGH);
                delayMicroseconds(bin_0);
                digitalWrite(IR555, LOW);
                delayMicroseconds(basso);
                break;
                
      case 2: digitalWrite(IR555, HIGH);
                delayMicroseconds(bin_0);
                digitalWrite(IR555, LOW);
                delayMicroseconds(basso);
                digitalWrite(IR555, HIGH);
                delayMicroseconds(bin_1);
                digitalWrite(IR555, LOW);
                delayMicroseconds(basso);
                break;
                
      case 3: digitalWrite(IR555, HIGH);
                delayMicroseconds(bin_1);
                digitalWrite(IR555, LOW);
                delayMicroseconds(basso);
                digitalWrite(IR555, HIGH);
                delayMicroseconds(bin_1);
                digitalWrite(IR555, LOW);
                delayMicroseconds(basso);
                break;
    }
    switch (ARMA)
    {
      case 1:  digitalWrite(IR555, HIGH);  // m4
                 delayMicroseconds(bin_1);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 digitalWrite(IR555, HIGH);
                 delayMicroseconds(bin_0);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 digitalWrite(IR555, HIGH);
                 delayMicroseconds(bin_0);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 break;

      case 2:  digitalWrite(IR555, HIGH);  // uzzi
                 delayMicroseconds(bin_0);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 digitalWrite(IR555, HIGH);
                 delayMicroseconds(bin_1);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 digitalWrite(IR555, HIGH);
                 delayMicroseconds(bin_0);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 break;

      case 3:  digitalWrite(IR555, HIGH);  // cecchino
                 delayMicroseconds(bin_1);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 digitalWrite(IR555, HIGH);
                 delayMicroseconds(bin_1);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 digitalWrite(IR555, HIGH);
                 delayMicroseconds(bin_0);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 break;

      case 4:  digitalWrite(IR555, HIGH);  // minigun
                 delayMicroseconds(bin_0);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 digitalWrite(IR555, HIGH);
                 delayMicroseconds(bin_0);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 digitalWrite(IR555, HIGH);
                 delayMicroseconds(bin_1);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 break;

      case 5:  digitalWrite(IR555, HIGH);  // bazooka
                 delayMicroseconds(bin_1);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 digitalWrite(IR555, HIGH);
                 delayMicroseconds(bin_0);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 digitalWrite(IR555, HIGH);
                 delayMicroseconds(bin_1);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 break;

      case 6:  digitalWrite(IR555, HIGH);  // pompa
                 delayMicroseconds(bin_0);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 digitalWrite(IR555, HIGH);
                 delayMicroseconds(bin_1);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 digitalWrite(IR555, HIGH);
                 delayMicroseconds(bin_1);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 break;

      case 7:  digitalWrite(IR555, HIGH);  // libero
                 delayMicroseconds(bin_1);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 digitalWrite(IR555, HIGH);
                 delayMicroseconds(bin_1);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 digitalWrite(IR555, HIGH);
                 delayMicroseconds(bin_1);
                 digitalWrite(IR555, LOW);
                 delayMicroseconds(basso);
                 break;
                 
    default:  digitalWrite(IR555, HIGH); //colpo di striscio
                  delayMicroseconds(bin_0);
                  digitalWrite(IR555, LOW);
                  delayMicroseconds(basso);
                  digitalWrite(IR555, HIGH);
                  delayMicroseconds(bin_0);
                  digitalWrite(IR555, LOW);
                  delayMicroseconds(basso);
                  digitalWrite(IR555, HIGH);
                  delayMicroseconds(bin_0);
                  digitalWrite(IR555, LOW);
                  delayMicroseconds(basso);
                  break;
    }
    colpi--;
    digitalWrite(ledfiam, LOW);
    digitalWrite(buzsp, LOW);
    sparo=0;
}

