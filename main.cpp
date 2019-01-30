/*
*  Copyright (c) 2012 Neal Horman - http://www.wanlink.com
*
*  License: MIT open source (http://opensource.org/licenses/MIT)
*      Summary;
*      Use / modify / distribute / publish it how you want and
*      if you use it, or don't, you can't hold me liable for how
*      it does or doesn't work.
*      If it doesn't work how you want, don't use it, or change
*      it so that it does work.
*/

#include "mbed.h"
#include "Adafruit_SSD1306.h"
#include "TSISensor.h"
#include <iostream>   // std::cout
#include <string>

Serial bt(PTE0,PTE1,9600);
PwmOut led1(LED_GREEN);
PwmOut led2(LED_RED);
PwmOut led3(LED_BLUE);
AnalogIn Ain(PTB0);
// an SPI sub-class that provides a constructed default


class SPIPreInit : public SPI
{
public:
   SPIPreInit(PinName mosi, PinName miso, PinName clk) : SPI(mosi,miso,clk)
   {
       format(8,3);
       frequency(1300000);
   };
};


SPIPreInit gSpi(PTD2,NC,PTD1);
Adafruit_SSD1306_Spi gOled1(gSpi,PTA13,PTD5,PTD0);
TSISensor tsi;
double a = tsi.readPercentage();
bool blt = 1;
bool connected = 1;
bool suc_pass = 0;
bool account = 1;
bool withd = 0;
bool deposit = 0;
int balance = 100;
bool final = 0;
bool dummy = 1;
bool dummy3 = 1;
void hi() {

       char *a;
       gOled1.display();
       if (connected)
           {
               connected = 0;
               gOled1.printf("Cnnctd\r\n");
               gOled1.printf("Enter PSWRD\r\n");
               //gOled1.display();
           }
       while(bt.readable() != 0){
           //gOled1.printf("hey\r\n");
           *a= bt.getc();
           //gOled1.printf(a);
           gOled1.display();
           //blt = 1;
           if (*a == '1')
           {
               suc_pass = 1;
               blt = 0;
               gOled1.display();
           }
           else if (*a == '0')
           {
               gOled1.printf("Wrong!");
               led1 = 1;
               gOled1.display();
           }
           gOled1.display();
       }
}

void hi2() {

   led1 = 1;
   led2 = 1;
   led3 = 1;
       if (tsi.readPercentage() == 0)
       {
       led1 = 1;
       led2 = 1;
       led3 = 1;
       gOled1.display();
       //wait(0.1);
       }
       else if (tsi.readPercentage() < 0.3)
       {
       gOled1.clearDisplay();
       gOled1.setTextCursor(0,0);
       gOled1.printf("Withdrawal Menu\r\n");
       led1 = 0;
       led2 = 1;
       led3 = 1;
       gOled1.display();
       account = 0;
       withd = 1;
       wait_ms(500);
       //wait(0.1);
       }
       else if (tsi.readPercentage() > 0.3 && tsi.readPercentage() < 0.7)
       {
       led1 = 1;
       led2 = 0;
       led3 = 1;
       gOled1.display();
       //wait(0.1);
       }
       else if (tsi.readPercentage() > 0.7)
       {
       gOled1.clearDisplay();
       gOled1.setTextCursor(0,0);
       gOled1.printf("Deposit Menu\r\n");
       led1 = 1;
       led2 = 1;
       led3 = 0;
       gOled1.display();
       account = 0;
       deposit = 1;
       //wait(0.1);
       }

}

void hi3() {
   led1 = 1;
   led2 = 1;
   led3 = 1;
       if (tsi.readPercentage() == 0)
       {
       led1 = 1;
       led2 = 1;
       led3 = 1;
       gOled1.display();
       //wait(0.1);
       }
       else if (tsi.readPercentage() < 0.3) // 20 going to be withdrawn
       {
       led1 = 0;
       led2 = 1;
       led3 = 1;
       gOled1.display();
       withd = 0;
       final = 1;
       deposit = 0;
       balance = balance - 20;
       //wait(0.1);
       }
       else if (tsi.readPercentage() > 0.3 && tsi.readPercentage() < 0.7) // 50 going to be withdrawn
       {
       led1 = 1;
       led2 = 0;
       led3 = 1;
       gOled1.display();
       withd = 0;
       final = 1;
       deposit = 0;
       balance = balance - 50;
       //wait(0.1);
       }
       else if (tsi.readPercentage() > 0.7) // 100 going to be withdrawn
       {
       led1 = 1;
       led2 = 1;
       led3 = 0;
       gOled1.display();
       withd = 0;
       final = 1;
       deposit = 0;
       balance = balance - 100;
       //wait(0.1);
       }
   gOled1.display();
}

void hi4() {
  gOled1.display();
  led1 = 1;
  led2 = 1;
  led3 = 1;
   if (Ain < 0.1)
       {
       gOled1.display();
           if (tsi.readPercentage() > 0.3 && tsi.readPercentage() < 0.7)
           {
               balance = balance + 20;
               deposit = 0;
               final = 1;
           }
       led1 = 0;

       //myled2 = 1;
       //myled3 = 1;
       }
       else if (Ain > 0.1 && Ain< 0.9)
       {
       //myled1 = 1;
       gOled1.display();
           if (tsi.readPercentage() > 0.3 && tsi.readPercentage() < 0.7)
           {
               balance = balance + 50;
               deposit = 0;
               final = 1;
           }
       led2 = 0;
       //myled3 = 1;
       }
       else if (Ain > 0.9)
       {
       //myled1 = 1;
       //myled2 = 1;
       gOled1.display();
           if (tsi.readPercentage() > 0.3 && tsi.readPercentage() < 0.7)
           {
               balance = balance + 100;
               deposit = 0;
               final = 1;
           }
       led3 = 0;
       }
   gOled1.display();
}

int main(){
   bt.attach(&hi,Serial::RxIrq);

   gOled1.printf("Welcome to the Bank!\r\n");
   gOled1.printf("Connect Blt! \r\n");
   while(blt){ // make this blt
      hi();
   }
   while(account){ // make this account
      if (suc_pass)
      {
         gOled1.clearDisplay();
         gOled1.setTextCursor(0,0);
         gOled1.printf("PSWRD Correct\r\n");
         gOled1.printf("Account Menu\r\n");
         gOled1.printf("W / D ?\r\n");
         suc_pass = 0;
         gOled1.display();
      }
      hi2();
   }
   while(withd){ // make this withd
       gOled1.clearDisplay();
       gOled1.setTextCursor(0,0);

       gOled1.printf("Withdrawal Menu\r\n");
       char buf[10];
       sprintf(buf, "%d", balance);
       gOled1.printf("Account Balance: ");
       gOled1.printf(buf);
       gOled1.printf("\r\n Amount to Withdraw?\r\n");
       gOled1.printf("20      50      100 \r\n");
       gOled1.display();

       hi3();
   }
   while(deposit){ // make this deposit
       gOled1.clearDisplay();
       gOled1.setTextCursor(0,0);
       gOled1.printf("Deposit Menu\r\n");
       char buf2[10];
       sprintf(buf2, "%d", balance);
       gOled1.printf("Account Balance: ");
       gOled1.printf(buf2);
       gOled1.display();
      hi4();
   }
   while (final)
   {
       if (dummy)
       {
       gOled1.clearDisplay();
       gOled1.setTextCursor(0,0);
       dummy = 0;

       char buf3[10];
       sprintf(buf3, "%d", balance);
       gOled1.printf("Current Balance: ");
       gOled1.printf(buf3);
       gOled1.printf("\r\n");
       gOled1.printf("Thanks for using ATM\r\n");

       }
  gOled1.display();
   }

}
