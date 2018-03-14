//---------------------------------------------------------------------------------------
// HEADER DE FICHIER
// Description
//---------------------------------------------------------------------------------------

#include "humiditySensor.h"   //variables and modules initialisation

#include <stdio.h>
#include <unistd.h>

DHT::DHT(uint8_t pin, uint8_t type, uint8_t count) {
  // _pin = pin;
  // _type = type;
  // _count = count;
  // firstreading = true;
}

void DHT::begin(void) {
  // // set up the pins!
  // pinMode(_pin, INPUT);
  // digitalWrite(_pin, HIGH);
  // _lastreadtime = 0;
}

//boolean S == Scale.  True == Farenheit; False == Celcius
float DHT::readTemperature(bool S) {
//   float f;
//
//   if (read()) {
//     switch (_type) {
//     case DHT11:
//       f = data[2];
//       if(S)
//       	f = convertCtoF(f);
//
//       return f;
//     case DHT22:
//     case DHT21:
//       f = data[2] & 0x7F;
//       f *= 256;
//       f += data[3];
//       f /= 10;
//       if (data[2] & 0x80)
// 	f *= -1;
//       if(S)
// 	f = convertCtoF(f);
//
//       return f;
//     }
//   }
//   Serial.print("Read fail");
//   return NAN;
// }
//
// float DHT::convertCtoF(float c) {
// 	return c * 9 / 5 + 32;
// }
//
// float DHT::readHumidity(void) {
//   float f;
//   if (read()) {
//     switch (_type) {
//     case DHT11:
//       f = data[0];
//       return f;
//     case DHT22:
//     case DHT21:
//       f = data[0];
//       f *= 256;
//       f += data[1];
//       f /= 10;
//       return f;
//     }
//   }
//   Serial.print("Read fail");
//   return NAN;
}


bool humiditySensor::getData(void) {
  // uint8_t laststate = HIGH;
  // uint8_t counter = 0;
  // uint8_t j = 0, i;
  // unsigned long currenttime;
  //
  // // pull the pin high and wait 250 milliseconds
  // digitalWrite(_pin, HIGH);
  // delay(250);
  //
  // currenttime = millis();
  // if (currenttime < _lastreadtime) {
  //   // ie there was a rollover
  //   _lastreadtime = 0;
  // }
  // if (!firstreading && ((currenttime - _lastreadtime) < 2000)) {
  //   return true; // return last correct measurement
  //   //delay(2000 - (currenttime - _lastreadtime));
  // }
  // firstreading = false;
  // /*
  //   Serial.print("Currtime: "); Serial.print(currenttime);
  //   Serial.print(" Lasttime: "); Serial.print(_lastreadtime);
  // */
  // _lastreadtime = millis();
  //
  // data[0] = data[1] = data[2] = data[3] = data[4] = 0;
  //
  // // now pull it low for ~20 milliseconds
  // pinMode(_pin, OUTPUT);
  // digitalWrite(_pin, LOW);
  // delay(20);
  // cli();
  // digitalWrite(_pin, HIGH);
  // delayMicroseconds(40);
  // pinMode(_pin, INPUT);
  //
  // // read in timings
  // for ( i=0; i< MAXTIMINGS; i++) {
  //   counter = 0;
  //   while (digitalRead(_pin) == laststate) {
  //     counter++;
  //     delayMicroseconds(1);
  //     if (counter == 255) {
  //       break;
  //     }
  //   }
  //   laststate = digitalRead(_pin);
  //
  //   if (counter == 255) break;
  //
  //   // ignore first 3 transitions
  //   if ((i >= 4) && (i%2 == 0)) {
  //     // shove each bit into the storage bytes
  //     data[j/8] <<= 1;
  //     if (counter > _count)
  //       data[j/8] |= 1;
  //     j++;
  //   }
  //
  // }
  //
  // sei();

  /*
  Serial.println(j, DEC);
  Serial.print(data[0], HEX); Serial.print(", ");
  Serial.print(data[1], HEX); Serial.print(", ");
  Serial.print(data[2], HEX); Serial.print(", ");
  Serial.print(data[3], HEX); Serial.print(", ");
  Serial.print(data[4], HEX); Serial.print(" =? ");
  Serial.println(data[0] + data[1] + data[2] + data[3], HEX);
  */

  // check we read 40 bits and that the checksum matches
  // if ((j >= 40) &&
  //     (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) ) {
  //   return true;
  }


  return false;

}

void read_dht11_dat()
{
  // // Example program for bcm2835 library
  // // Blinks a pin on an off every 0.5 secs
  // // Author: Mike McCauley (mikem@open.com.au)
  // // Copyright (C) 2011 Mike McCauley
  // // $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $
  //
  // #include <bcm2835.h>
  //
  // // Blinks on RPi pin GPIO 11
  // #define PIN RPI_GPIO_P1_11
  //
  //   if (!bcm2835_init())
  // 	return 1;
  //   // Set the pin to be an output
  //   bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
  //   // Blink
  //   while (1)
  //   {
  //   	// Turn it on
  //   	bcm2835_gpio_write(PIN, HIGH);
  //   	// wait a bit
  //   	delay(500);
  //   	// turn it off
  //   	bcm2835_gpio_write(PIN, LOW);
  //   	// wait a bit
  //   	delay(500);
  //   }
  //     return 0;
  // }

//Reference : http://www.circuitbasics.com/how-to-set-up-the-dht11-humidity-sensor-on-the-raspberry-pi/
//   #include <wiringPi.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>
// #define MAXTIMINGS	85
// #define DHTPIN		7
// int dht11_dat[5] = { 0, 0, 0, 0, 0 };
  //
	// uint8_t laststate	= HIGH;
	// uint8_t counter		= 0;
	// uint8_t j		= 0, i;
	// float	f;
  //
	// dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;
  //
	// pinMode( DHTPIN, OUTPUT );
	// digitalWrite( DHTPIN, LOW );
	// delay( 18 );
	// digitalWrite( DHTPIN, HIGH );
	// delayMicroseconds( 40 );
	// pinMode( DHTPIN, INPUT );
  //
	// for ( i = 0; i < MAXTIMINGS; i++ )
	// {
	// 	counter = 0;
	// 	while ( digitalRead( DHTPIN ) == laststate )
	// 	{
	// 		counter++;
	// 		delayMicroseconds( 1 );
	// 		if ( counter == 255 )
	// 		{
	// 			break;
	// 		}
	// 	}
	// 	laststate = digitalRead( DHTPIN );
  //
	// 	if ( counter == 255 )
	// 		break;
  //
	// 	if ( (i >= 4) && (i % 2 == 0) )
	// 	{
	// 		dht11_dat[j / 8] <<= 1;
	// 		if ( counter > 16 )
	// 			dht11_dat[j / 8] |= 1;
	// 		j++;
	// 	}
	// }
  //
	// if ( (j >= 40) &&
	//      (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) )
	// {
	// 	f = dht11_dat[2] * 9. / 5. + 32;
	// 	printf( "Humidity = %d.%d %% Temperature = %d.%d C (%.1f F)\n",
	// 		dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3], f );
	// }else  {
	// 	printf( "Data not good, skip\n" );
	// }
}
