int ledsgn = 10;    //led di segnalazione, si accende quando si muore o quando si e` senza colpi
int ledfiam = 9;   //led di fiammata si accende quando si spara per simulare la luce rossa che esce dalla canna di un fucile quando si spara
int buzsp = 12;     //buzzer di sparo si accende quando si spara
int buzsgn = 11;     //buzzer di segnalazione, si accende quando si e` colpiti o a ricarica avvenuta
int IR555 = 4;      //segnale che va a pilotare il reset di un 555 la cui uscita e` collegata ad un led ir
int pulssp = 3;     //pulsante di sparo
int pulsric = 2;     //pulsante di ricarica
int sensIR = 8;     //sensori infrarosso che ricevono il colpo

//ingressi impostazione arma e codice
int s0 = 0;         //i bit s impostano la squadra
int s1 = 1;
int a0 = 2;         //i bit a impostano l'arma
int a1 = 3;
int a2 = 4;
//variabili impostazione arma e codice
int DATO[5] = {0,0,0,0,0};    //variabile che contiene il codice

int data[5]; //i 5 impulsi che arrivano all'IR vengono inseriti nell'array data[ ] contengono il codice dell'arma avversaria

//variabili che inpostano l'arma
int vita = 0;          //variabile che indica i punti vita, si decrementa ogni volta che si viene colpiti, aumenta se si viene curati
int colpi = 0;         //variabile che indica il numero di colpi per caricatore, decrementa ogni volta che si spara un colpo
int caricatori = 0;    //variabile che indica il numero di caricatori, decrementa ogni volta che si ricarica
int SQUADRA = 0;       //variabile che indica la squadra della propria arma
int ARMA = 0;          //variabile che indica il tipo della propria arma

int squadranem = 0;
int armanem = 0;

int base2 = 1;         //variabili di supporto per la conversione in binario del codice arma squadra
int BASE2 =1;

volatile int iric = 0;          //variabili di supporto usate nella ISR ricarica
volatile int iledsgn = 0;
volatile int flagledsgn = 0;

//variabili per codice in uscita
int BitStart = 1000;    //variabile che indica il valore del bit di start 
int bin_1 = 800;       //variabile che indica quando voglio spedire un bit 1
int bin_0 = 600;       //variabile che indica quando voglio spedire un bit 0
int basso = 600;       //variabile che indica il valore di stacco tra un bit e l'altro

int BitStartRic = 950;    //variabile che indica il valore che devo avere per iniziare la ricezione del codice
int bin_1Ric = 750;       //variabile che indica il valore che devo avere per avere un bit a 1
int Statoh = LOW;         //variabile che mi indica se ho un bit a 1 con stato basso o stato alto
int timeoutstart = 5000;  //10000 funziona
int timeoutbit = 4000;    //9000 funziona

int i = 0;
int flagtimer0 = 0;

int k = 0;
int flagbuzin = 0;
int flaggiriin = 0;

int FUNZIONESPARO();
int funzioneaggiornamentovita();
int sparo=0;


void setup( ) 
{
  pinMode(ledsgn, OUTPUT);  
  pinMode(ledfiam, OUTPUT);
  pinMode(buzsp, OUTPUT);
  pinMode(buzsgn, OUTPUT); 
  pinMode(IR555, OUTPUT);   
  pinMode(pulssp, INPUT); 
  pinMode(pulsric, INPUT); 
  pinMode(sensIR, INPUT); 
  
  Serial.begin(9600); 

  cli();//stop interrupts

  //set timer2 interrupt at 2kHz                                     //timer usato per la ricarica
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;// initialize counter value to 0
  // set compare match register for 2khz increments
  OCR2A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR2B |= (1 << CS21) | (1 << CS20);   
  
  TIMSK2 &= (0 << OCIE2A);


  
                                                                   //  timer usato per lo sparo
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  //OCR1A viene scelto nel case arma
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  
  TIMSK1 &= (0 << OCIE1A);



  //set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR2A register to 0
  TCCR0B = 0;// same for TCCR2B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  
  TIMSK0 &= (0 << OCIE0A);
  
  sei();//allow interrupts
  
  DATO[0]=analogRead(s0);
  DATO[1]=analogRead(s1);
  DATO[2]=analogRead(a0);
  DATO[3]=analogRead(a1);
  DATO[4]=analogRead(a2);
  for(i=0;i<5;i++)
  {
    Serial.print("dato: ");
    Serial.println(DATO[i]);
    if(DATO[i]>= 800)
    {
      DATO[i]=1;
    }
    else
    {
      DATO[i]=0;
    }
    Serial.print("DATO: ");
    Serial.println(DATO[i]);
  }

  for(int i=0;i<5;i++) 
   {
      if(i<2)
      {
        if(DATO[i] == 1) 
        {
          SQUADRA=SQUADRA+base2;
        }
        base2 = base2 * 2; // questa istruzione permette il calcolo del peso in base 2 necessario per la conversione
      }
      else
      {
         if(DATO[i] == 1) 
        {
          ARMA=ARMA+BASE2;
        }
        BASE2 = BASE2 * 2; // questa istruzione permette il calcolo del peso in base 2 necessario per la conversione
      }
   }
   Serial.print("Squadra: ");
   Serial.println(SQUADRA);
   Serial.print("Arma: ");
   Serial.println(ARMA);
   
   switch (ARMA)
   {
     case 1:  vita = 100;        //m4
                colpi = 30;
                caricatori = 5;
                OCR1A = 2232;    // = (16*10^6) / (1*1024) - 1 (must be <65536)  //spara a 7 hz       //400 colpi al minuto
                //danno 25
                //tempo di ricarica 4s
                Serial.println("arma 1");
                break;
                
     case 2:  vita = 100;        //uzzi
                colpi = 15;
                caricatori = 15;
                OCR1A = 1953; //500 colpi al minuto
                //danno 25
                //tempo di ricarica 3s
                Serial.println("arma 2");
                break;
                
     case 3:  vita = 100;        //cecchino
                colpi = 1;
                caricatori = 15;
                OCR1A = 2232;
                //danno 100
                //tempo di ricarica 7s
                Serial.println("arma 3");
                break;

     case 4:  vita = 400;        //minigun
                colpi = 200;
                caricatori = 3;
                OCR1A = 1563;     //600 colpi minuto
                //danno 10
                //tempo di ricarica 10s
                Serial.println("arma 4");
                break;
                
     case 5:  vita = 400;        //bazooka
                colpi = 1;
                caricatori = 7;
                OCR1A = 2232;
                //danno 100
                //tempo di ricarica 10s
                Serial.println("arma 3");
                break;

     case 6:  vita = 200;        //pompa
                colpi = 7;
                caricatori = 5;
                OCR1A = 5200;
                //danno 50
                //tempo di ricarica 5s
                Serial.println("arma 2");
                break;
                
   /*  case 7:  vita = 100;        //libero
                colpi = 1;
                caricatori = 15;
                OCR1A = 2232;
                //danno 100
                //tempo di ricarica 7s
                Serial.println("arma 3");
                break;*/
                 
    default:  vita = 0;        
                 colpi = 0;
                 caricatori = 0;
                 Serial.println("errore arma");
                 break;
   } 
   digitalWrite(ledsgn, LOW);
   digitalWrite(ledfiam, LOW);
   digitalWrite(buzsp, LOW);
   TIMSK0 |= (1 << OCIE0A);
}



void loop()
{
  if(vita > 0)
  {
     BASE2 = 1;
     base2 = 1;
     squadranem = 0;
     armanem = 0;
     while(pulseIn(sensIR, LOW, timeoutstart) < BitStartRic)
     {
            if(colpi != 0)
            {
               digitalWrite(ledsgn, LOW); //togliere se ci son problemi con il led di segnalazione
             // Serial.println("ho colpi da sparare");
              if(digitalRead(pulssp) == HIGH)
              {
               // Serial.println("pulsante sparo ON");
                TIMSK1 |= (1 << OCIE1A);
                if(sparo == 1)
                {
                  FUNZIONESPARO();
                }
              }
              else
              {
              //  Serial.println("pulsante sparo OFF");
                TIMSK1 &= (0 << OCIE1A);
                digitalWrite(IR555, LOW);
              }
            }
            else
            {
              TIMSK1 &= (0 << OCIE1A);
              //Serial.println("NON ho colpi da sparare");
              if(iric == 0)
              {
                digitalWrite(ledsgn, HIGH);
              }
            }
            if((digitalRead(pulsric) == HIGH)  && caricatori != 0)
            {
              //Serial.println("Ricarica");
              colpi=0;
              TIMSK2 |= (1 << OCIE2A);
            }
         /*   Serial.print("Colpi: ");
            Serial.println(colpi);
            Serial.print("Caricatori: ");
            Serial.println(caricatori);*/
     }
     data[0] = pulseIn(sensIR, Statoh, timeoutbit); // inizia la misura della durata
     data[1] = pulseIn(sensIR, Statoh, timeoutbit); // degli impulsi alti a partire
     data[2] = pulseIn(sensIR, Statoh, timeoutbit); // dal trigger alto-basso
     data[3] = pulseIn(sensIR, Statoh, timeoutbit);
     data[4] = pulseIn(sensIR, Statoh, timeoutbit);
     for(i=0;i<5;i++) 
     { // verifica tutti i dati
       if(data[i] > bin_1Ric) 
       { 
         data[i] = 1 ; 
       }
       else 
       {
         data[i] = 0;
       }
      // Serial.println(data[i]);
     }
     // come fare la conversione binario decimale
     for(int i=0;i<5;i++) 
     {
        if(i<2)
        {
          if(data[i] == 1) 
          {
            squadranem=squadranem+base2;
          }
          base2 = base2 * 2; // questa istruzione permette il calcolo del peso in base 2 necessario per la conversione
        }
        else
        {
           if(data[i] == 1) 
          {
            armanem=armanem+BASE2;
          }
          BASE2 = BASE2 * 2; // questa istruzione permette il calcolo del peso in base 2 necessario per la conversione
        }
      /*  Serial.print("squadra nemica: ");
        Serial.println(squadranem);
        Serial.print("arma nemica: ");
        Serial.println(armanem);*/
     }
     funzioneaggiornamentovita();
  }
  else
  {
    colpi = 0;
    caricatori = 0;
    digitalWrite(buzsgn, HIGH);
    digitalWrite(ledsgn, HIGH);
    digitalWrite(ledsgn, HIGH);
 }
}










//ISR azione sparo
ISR(TIMER1_COMPA_vect)
{
    //Serial.println("ISR SPARO");
    sparo=1;
}






