/* 
 * File:   main.c
 * Author: Alan Cruz
 *
 * Created on 20 de septiembre de 2021, 12:26 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "LCD_lib.h"
#include "conf.h"

    char buffer1[23];
    char buffer[20];
   int vel = 500;
   int k = 1;
   unsigned char f = 0;
   int i = 0;
   int l = 15;

int a,b,s;//DECLARAMOS VARIABLES DE TIPO ENTERO
    void P1(){    
    LCD_Comando(1);
    LCD_Comando(0b01000000);//pagina 27  HD44780    
    LCD_Data(0b00011111);
    LCD_Data(0b00010101);
    LCD_Data(0b00011111);
    LCD_Data(0b00001110);
    LCD_Data(0b00010101);
    LCD_Data(0b00001110);
    LCD_Data(0b00011011);
    LCD_Data(0b00000000);
    LCD_Data(0b00000111);
    LCD_Data(0b00000010);
    LCD_Data(0b00011111);
    LCD_Data(0b00000111);
    LCD_Data(0b00000111);
    LCD_Data(0b00000101);
    LCD_Data(0b00011011);
    LCD_Data(0b00000000);
    LCD_Data(0b00011100);
    LCD_Data(0b00001000);
    LCD_Data(0b00011111);
    LCD_Data(0b00011100);
    LCD_Data(0b00011100);
    LCD_Data(0b00010100);
    LCD_Data(0b00011011);
    LCD_Data(0b00000000);
    }


 void tocar_nota(int duracion, float tfrec){  //funcion generadora de notas, periodo de la nota y duracion de esta
 
     int duracion2;
     duracion2 = (int)duracion/tfrec;
     tfrec = 255-((tfrec/2)/(.0002*128));

       for(b=0;b<duracion2;b++){
           
            PORTAbits.RA0 = 1;
           TMR0 = tfrec;
           while(INTCONbits.TMR0IF==0);
           INTCONbits.TMR0IF=0;
  
        PORTAbits.RA0=0;
         TMR0 = tfrec;
         while(INTCONbits.TMR0IF==0);
         INTCONbits.TMR0IF=0;
}
  
 }
 void silencio(int duracion, float tfrec){  //funcion generadora de notas, periodo de la nota y duracion de esta
     
     duracion = duracion/tfrec;
     tfrec = 255-((tfrec/2)/(.0002*128));

       for(b=0;b<duracion;b++){
            PORTAbits.RA0 = 0;
           TMR0 = tfrec;
           while(INTCONbits.TMR0IF==0);
           INTCONbits.TMR0IF=0;
  
        PORTAbits.RA0=0;
         TMR0 = tfrec;
         while(INTCONbits.TMR0IF==0);
         INTCONbits.TMR0IF=0;
}
 }


 void confT0(){
     //11000010
    T0CONbits.TMR0ON = 1; //encendido
      T0CONbits.T08BIT = 1;  //modo 8 bits
      T0CONbits.T0CS = 0; //modo temporizador tcy
      T0CONbits.T0SE = 0; //leer bajadas
      T0CONbits.PSA = 0;  //con preescalador
      T0CONbits.T0PS = 0b110; 
     
      INTCONbits.TMR0IE = 1;      // Habilitamos las interrupción por desborde de TIMER0


 }


 
 
      
  float cancion[44][3] =     
  {
 { 1, 3.034,1},{ 1, 3.034,1},{ 1,3.034,1},{( .75),3.82,1},{( .25),2.55,1},{ 1,3.034,1},{( .75),3.82,1},{( .25),2.551,1},{( 2),3.034,1},{(1),2.028,1},
 { 1,2.028,1},{ 1,2.028,1},{ (0.75),1.911,1},{ (0.25),2.551,1},{ 1,3.61,1},{ (0.75),3.82,1},{ (0.25),2.551,1},{ 2,3.034,1},{ 1,1.517,1},{ (0.75),3.034,1},
 { (0.25),3.034,1},{ 1,1.517,1},{ (0.75),1.607,1},{ (0.25),1.703,1},{ (0.25),1.804,1},{ (0.25),1.911,1},{ (0.60),1.804,1},{ (0.20),1,0},{ (0.60),2.863,1},{ 1,2.145,1},
 { (0.75),2.273,1},{ (0.25),2.408,1},{ (0.25),2.551,1},{ (0.25),2.703,1},{ (0.60),2.551,1},{ (0.20),1,0},{ (0.60),3.822,1},{ 1,3.608,1},{ (0.75),3.822,1},{ (0.25),2.551,1},
 { 1,3.034,1},{ (0.75),3.822,1},{ (0.25),2.551,1},{ 5,3.034,1}
 };
 
void cancion1(){ 

for( int j = 0; j < 44; j ++){
        
if(i < 15 && l > 0){
     // 0 - 14--15 & 15 - 1--0
      
                        if(cancion[j][2] == 1){
                                  if(PORTBbits.RB0 == 1){
                                    k = 0;
                                }
                                else{
                                    k = 1;
                                }
                                LCD_XY(1,15);
                            sprintf(buffer1,"%i",l);  //Texto alineado a la izquierda
                             LCD_Cadena(buffer1);
                                LCD_XY(k,i);
                                LCD_Data(0);
                                LCD_XY(1,l);
                                LCD_Data(1);
                         tocar_nota(vel*cancion[j][0],cancion[j][1]);


                     }

                     else if(cancion[j][2] == 0){
                         
                                                       if(PORTBbits.RB0 == 1){
                                    k = 0;
                                }
                                else{
                                    k = 1;
                                }
                                LCD_XY(1,15);
                            sprintf(buffer1,"%i",l);  //Texto alineado a la izquierda
                             LCD_Cadena(buffer1);
                                LCD_XY(k,i);
                                LCD_Data(0);
                                LCD_XY(1,l);
                                LCD_Data(1);
                         silencio(vel*cancion[j][0],cancion[j][1]);



                     } 
            LCD_Comando(1);
            i++;
            l--;
         //   f = 0;
        } 

       //     f = 1;
else if(i > 0 && l < 15 ){
       // 14-0 &  1-15
                      if(cancion[j][2] == 1){
                                   if(PORTBbits.RB0 == 1){
                                    k = 0;
                                }
                                else{
                                    k = 1;
                                }
                                LCD_XY(1,15);
                            sprintf(buffer1,"%i",l);  //Texto alineado a la izquierda
                             LCD_Cadena(buffer1);
                                LCD_XY(k,i);
                                LCD_Data(0);
                                LCD_XY(1,l);
                                LCD_Data(2);
                         tocar_nota(vel*cancion[j][0],cancion[j][1]);


                     }

                     else if(cancion[j][2] == 0){
                             if(PORTBbits.RB0 == 1){
                                    k = 0;
                                }
                                else{
                                    k = 1;
                                }
                               LCD_XY(1,15);
                            sprintf(buffer1,"%i",l);  //Texto alineado a la izquierda
                             LCD_Cadena(buffer1);
                                LCD_XY(k,i);
                                LCD_Data(0);
                                LCD_XY(1,l);
                                LCD_Data(2);
                         silencio(vel*cancion[j][0],cancion[j][1]);



                     }
            LCD_Comando(1);
            i--;
            l++;
      //      f = 1;
        } 

        
    }


return;
 }


 
int main(int argc, char** argv) {
 
     ADCON1= 15;
    
             LCD_Init();
             P1();
       confT0();
           
             
    TRISA =  0b00010000;
    TRISB = 0b11111111;

             
           
    while(1){


    cancion1();
   /*   while(i < 14 && l > 0){
           
            if(PORTBbits.RB0 == 1){
                puntaje++;
                k = 0;
            }
            else{
                k = 1;
            }
                    LCD_XY(1,15);
       sprintf(buffer1,"%i",puntaje);  //Texto alineado a la izquierda
        LCD_Cadena(buffer1);
            LCD_XY(k,i);
            LCD_Data(0);
            LCD_XY(1,l);
            LCD_Data(1);
            __delay_ms(100); 
            LCD_Comando(1);
            i++;
            l--;
        } 
        

      while(i > 0 && l < 14){

           if(PORTBbits.RB0 == 1){
              puntaje++;
                k = 0;
            }
            else{
                k = 1;
            }
                   LCD_XY(1,15);
       sprintf(buffer1,"%i",puntaje);  //Texto alineado a la izquierda
        LCD_Cadena(buffer1);
            LCD_XY(k,i);
            LCD_Data(0);
            LCD_XY(1,l);
            LCD_Data(2);
            __delay_ms(100); 
            LCD_Comando(1);
            i--;
            l++;
        }
      
        */
     
    }
 	
 
 
     

    return (EXIT_SUCCESS);
    
    
    
    
}
