//ISR per la ricarica
ISR(TIMER2_COMPA_vect)
{
  iric++;
  iledsgn++;
  if(iledsgn >= 1000)
  {
    flagledsgn=1-flagledsgn;
    digitalWrite(ledsgn, flagledsgn);
    digitalWrite(buzsgn, flagledsgn);
    iledsgn=0;
   // Serial.println("ISR RICARICA");
  }
  switch (ARMA)
    {
      case 1:  if(iric >= 8000)             // m4
               {
                  colpi = 30;
                  caricatori--;
                  TIMSK2 &= (0 << OCIE2A);
                  iric=0;
                  digitalWrite(ledsgn, LOW);
                  digitalWrite(buzsgn, LOW);
                 /* Serial.print("Colpi ricaricati: ");
                  Serial.println(colpi);
                  Serial.print("Caricatori rimasti: ");
                  Serial.println(caricatori);*/
               }
                 break;

      case 2:    if(iric >= 6000)             // uzzi
               {
                  colpi = 15;
                  caricatori--;
                  TIMSK2 &= (0 << OCIE2A);
                  iric=0;
                  digitalWrite(ledsgn, LOW);
                  digitalWrite(buzsgn, LOW);
                /*  Serial.print("Colpi ricaricati: ");
                  Serial.println(colpi);
                  Serial.print("Caricatori rimasti: ");
                  Serial.println(caricatori);*/
               }
                 break;

      case 3:     if(iric >= 14000)             // cecchino
               {
                  colpi = 1;
                  caricatori--;
                  TIMSK2 &= (0 << OCIE2A);
                  iric=0;
                  digitalWrite(ledsgn, LOW);
                  digitalWrite(buzsgn, LOW);
                /*  Serial.print("Colpi ricaricati: ");
                  Serial.println(colpi);
                  Serial.print("Caricatori rimasti: ");
                  Serial.println(caricatori);*/
               }
                 
                 break;

      case 4:  if(iric >= 20000)             // minigun
               {
                  colpi = 200;
                  caricatori--;
                  TIMSK2 &= (0 << OCIE2A);
                  iric=0;
                  digitalWrite(ledsgn, LOW);
                  digitalWrite(buzsgn, LOW);
                 /* Serial.print("Colpi ricaricati: ");
                  Serial.println(colpi);
                  Serial.print("Caricatori rimasti: ");
                  Serial.println(caricatori);*/
               }
                 break;

      case 5:    if(iric >= 20000)             // bazooka
               {
                  colpi = 1;
                  caricatori--;
                  TIMSK2 &= (0 << OCIE2A);
                  iric=0;
                  digitalWrite(ledsgn, LOW);
                  digitalWrite(buzsgn, LOW);
                /*  Serial.print("Colpi ricaricati: ");
                  Serial.println(colpi);
                  Serial.print("Caricatori rimasti: ");
                  Serial.println(caricatori);*/
               }
                 break;

      case 6:     if(iric >= 10000)             // pompa
               {
                  colpi = 7;
                  caricatori--;
                  TIMSK2 &= (0 << OCIE2A);
                  iric=0;
                  digitalWrite(ledsgn, LOW);
                  digitalWrite(buzsgn, LOW);
                /*  Serial.print("Colpi ricaricati: ");
                  Serial.println(colpi);
                  Serial.print("Caricatori rimasti: ");
                  Serial.println(caricatori);*/
               }
                 
                 break;

     /* case 7:     if(iric >= 14000)             // libero
               {
                  colpi = 1;
                  caricatori--;
                  TIMSK2 &= (0 << OCIE2A);
                  iric=0;
                  digitalWrite(ledsgn, LOW);
                  digitalWrite(buzsgn, LOW);
                 // Serial.print("Colpi ricaricati: ");
                 // Serial.println(colpi);
                 // Serial.print("Caricatori rimasti: ");
                 // Serial.println(caricatori);
               }
                 
                 break;*/
                 
    default:     if(iric >= 10)            
               {
                  colpi = 0;
                  caricatori = 0;
                  TIMSK2 &= (0 << OCIE2A);
                  iric=0;
                  digitalWrite(ledsgn, LOW);
                  digitalWrite(buzsgn, LOW);
                 /* Serial.println("Errore ricarica");
                  Serial.print("Colpi ricaricati: ");
                  Serial.println(colpi);
                  Serial.print("Caricatori rimasti: ");
                  Serial.println(caricatori);*/
               } 
                  break;
    }
}
