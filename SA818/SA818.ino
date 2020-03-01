void setup() 
{
  Serial.begin( 9600 );
  Serial.println( "Starting..." );
  
  Serial1.begin( 9600, SERIAL_8N1 );
  Serial1.print("AT\r\n");

  delay(500);

  for(uint8_t r = 0; r<5; r++)
  {
    Serial1.print("AT+DMOCONNECT\r\n");
    if(readSerialTimeout())
    {
      Serial.print("Got response" );
      break;
    }
  }

    Serial1.print("AT+VERSION\r\n");
    if(readSerialTimeout())
    {
      Serial.print("Got response" );
    }


    
    Serial1.print("AT+DMOSETVOLUME=5\r\n");
    if(readSerialTimeout())
    {
      Serial.print("Got response" );
    }

    Serial1.print("RSSI?\r\n");
    if(readSerialTimeout())
    {
      Serial.print("Got response" );
    }

    char buf[20];

/*
    for ( int j = 146 ; j < 148 ; j++ )
    for ( int i = 0 ; i < 9999 ; i += 50 )
    {
      sprintf( buf, "%03d.%04d", j, i );
      Serial.print( buf );
      setConfig( 1, buf, buf, "0000", "0000", 0 );
      delay( 200 ); 
    }
    */

    setConfig( 1, "146.9200", "146.9200", "0000", "0000", 2 );

   /*
    for ( ;; )
    {
      
    Serial1.print("RSSI?\r\n");
    if(readSerialTimeout())
    {
      Serial.print("Got response" );
    }
    delay( 500 );
    }
    */
}


uint8_t setConfig(uint8_t bw, char* tx_f, char* rx_f, char* tx_ctcss, char* rx_ctcss, uint8_t squelch)
{

  for(uint8_t r=0; r<5; r++){
    Serial1.print("AT+DMOSETGROUP=");
    Serial1.print(bw); // 0/1
    Serial1.print(",");
    Serial1.print(tx_f);//134-174/400-480, format to 415.1250
    Serial1.print(",");
    Serial1.print(rx_f);//format to 415.1250
    Serial1.print(",");
    Serial1.print(tx_ctcss);//format to 0000
    Serial1.print(",");
    Serial1.print(squelch); // <= 8
    Serial1.print(",");
    Serial1.print(rx_ctcss);
    Serial1.print("\r\n");

    if(readSerialTimeout()){
      return true;
    }
  }

  return false;
}


uint8_t readSerialTimeout()
{
  uint8_t readed = false;
  unsigned long timeout = millis();
  
  while (millis() - timeout < 500) 
  {
    delay(100);
    while (Serial1.available() > 0) 
    {
      Serial.write(Serial1.read());
      readed = true;
    }
    if (readed == true)break;
  }

  if(!readed)
    Serial.println("Read timeout");

  return readed;
}

void loop() 
{
 
}
