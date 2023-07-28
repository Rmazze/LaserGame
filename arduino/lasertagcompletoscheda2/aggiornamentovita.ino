
int funzioneaggiornamentovita()
{
  if(squadranem != SQUADRA && squadranem != 0)
  {
    switch (armanem)
    {
      case 1:    flagtimer0 = 1;
                 vita=vita-25;             //m4
                 TIMSK0 |= (1 << OCIE0A);
                 break;

      case 2:    flagtimer0 = 1;
                 vita=vita-25;             //uzzi
                 TIMSK0 |= (1 << OCIE0A);
                 break;

      case 3:    flagtimer0 = 1;
                 vita=vita-100;          //cecchino
                 TIMSK0 |= (1 << OCIE0A);
                 break;

      case 4:    flagtimer0 = 1;
                 vita=vita-10;             //minigun
                 TIMSK0 |= (1 << OCIE0A);
                 break;

      case 5:    flagtimer0 = 1;
                 vita=vita-100;             //bazooka
                 TIMSK0 |= (1 << OCIE0A);
                 break;

      case 6:    flagtimer0 = 1;
                 vita=vita-50;          //pompa
                 TIMSK0 |= (1 << OCIE0A);
                 break;

     /* case 7:    flagtimer0 = 1;
                 vita=vita-100;          //cecchino
                 TIMSK0 |= (1 << OCIE0A);
                 break;*/
                 
    default:      flagtimer0 = 2;
                  TIMSK0 |= (1 << OCIE0A);  //colpo di striscio
                  break;
    } 
  }
  //Serial.print("Vita: ");
  //Serial.println(vita);
}




ISR(TIMER0_COMPA_vect)
{
  k++;
  if(flagtimer0 == 0)
  {
    if(k >= 200 && flaggiriin < 4)
    {
      flagbuzin = 1-flagbuzin;
      digitalWrite(buzsgn, flagbuzin);
      k=0;
      flaggiriin++;
    }
    else if(flaggiriin >=4)
    {
      flagtimer0 = 1;
      digitalWrite(buzsgn, LOW);
      k=0;
      TIMSK0 &= (0 << OCIE0A);
    }
  }
  else if (flagtimer0 == 1)
  {
    digitalWrite(buzsgn, HIGH);
    digitalWrite(ledsgn, HIGH);
    if(k >= 50)
    {
      digitalWrite(buzsgn, LOW);
      digitalWrite(ledsgn, LOW);
      k=0;
      TIMSK0 &= (0 << OCIE0A);
    }
  }
  else if (flagtimer0 == 2)
  {
    if(k >= 25 && flaggiriin < 4)
    {
      flagbuzin = 1-flagbuzin;
      digitalWrite(buzsgn, flagbuzin);
      k=0;
      flaggiriin++;
    }
    else if(flaggiriin >= 4)
    {
      digitalWrite(buzsgn, LOW);
      k=0;
      TIMSK0 &= (0 << OCIE0A);
    }
  }
}

