#include <driverlib.h>
#include "hal_LCD.h"
#include <msp430.h>
#include <time.h>
#include "string.h"
#include <stdlib.h>
#include <stdio.h>

// Initializes the LCD_C module
// *** Source : Function obtained from MSP430FR6989 Sample Code ***
void Initialize_LCD() {
    PJSEL0 = BIT4 | BIT5 ; // For LFXT
    // Initialize LCD segments 0 - 21; 26 - 43
    LCDCPCTL0 = 0xFFFF ;
    LCDCPCTL1 = 0xFC3F ;
    LCDCPCTL2 = 0x0FFF ;
    // Configure LFXT 32 kHz crystal
    CSCTL0_H = CSKEY >> 8; // Unlock CS registers
    CSCTL4 &= ~ LFXTOFF ; // Enable LFXT
    do {
        CSCTL5 &= ~ LFXTOFFG ; // Clear LFXT fault flag
        SFRIFG1 &= ~ OFIFG ;
    } while ( SFRIFG1 & OFIFG ) ; // Test oscillator fault flag
    CSCTL0_H = 0; // Lock CS registers
    // Initialize LCD_C
    // ACLK , Divider = 1 , Pre - divider = 16; 4 - pin MUX
    LCDCCTL0 = LCDDIV__1 | LCDPRE__16 | LCD4MUX | LCDLP ;
    // VLCD generated internally ,
    // V2 -V4 generated internally , v5 to ground
    // Set VLCD voltage to 2.60 v
    // Enable charge pump and select internal reference for it
    LCDCVCTL = VLCD_1 | VLCDREF_0 | LCDCPEN ;
    LCDCCPCTL = LCDCPCLKSYNC ; // Clock synchronization enabled
    LCDCMEMCTL = LCDCLRM ; // Clear LCD memory
    // Turn LCD on
    LCDCCTL0 |= LCDON ;
    return ;
}

// Función para mostrar las letras mayúsculas del alfabeto contenidas en un vector de 6 elementos en el LCD de la placa:
void ShowBuffer(int buffer[]) {
    LCDMEM[9] = alphabetBig[(buffer[0])-65][0];
    LCDMEM[10] = alphabetBig[(buffer[0])-65][1];
    LCDMEM[5] = alphabetBig[(buffer[1])-65][0];
    LCDMEM[6] = alphabetBig[(buffer[1])-65][1];
    LCDMEM[3] = alphabetBig[(buffer[2])-65][0];
    LCDMEM[4] = alphabetBig[(buffer[2])-65][1];
    LCDMEM[18] = alphabetBig[(buffer[3])-65][0];
    LCDMEM[19] = alphabetBig[(buffer[3])-65][1];
    LCDMEM[14] = alphabetBig[(buffer[4])-65][0];
    LCDMEM[15] = alphabetBig[(buffer[4])-65][1];
    LCDMEM[7] = alphabetBig[(buffer[5])-65][0];
    LCDMEM[8] = alphabetBig[(buffer[5])-65][1];
}

const unsigned char LCD_Num [10] = {0xFC , 0x60 , 0xDB , 0xF3 , 0x67 , 0xB7 , 0xBF , 0xE0 , 0xFF ,0xE7 };
// *************** function that displays any 16 - bit unsigned integer ************
inline void display_num_lcd ( unsigned int n ) {
    int i = 0;
    do {
        unsigned int digit = n % 10;
        switch ( i ) {
            case 0: LCDM8 = LCD_Num [ digit ]; break ; // first digit
            case 1: LCDM15 = LCD_Num [ digit ]; break ; // second digit
            case 2: LCDM19 = LCD_Num [ digit ]; break ; // third digit
            case 3: LCDM4 = LCD_Num [ digit ]; break ; // fourth digit
            case 4: LCDM6 = LCD_Num [ digit ]; break ; // fifth digit
        }
        n /= 10;
        i ++;
    } while ( i < 5) ;
}

int palabras[100][6] = {
{'A', 'I', 'S', 'L', 'A', 'R'}, // 1
{'A', 'T', 'A', 'Q', 'U', 'E'}, // 2
{'A', 'N', 'H', 'E', 'L', 'O'}, // 3
{'A', 'S', 'T', 'R', 'A', 'L'}, // 4
{'B', 'I', 'B', 'L', 'I', 'A'}, // 5
{'B', 'I', 'S', 'T', 'E', 'C'}, // 6
{'B', 'E', 'L', 'I', 'C', 'O'}, // 7
{'B', 'O', 'D', 'E', 'G', 'A'}, // 8
{'B', 'A', 'R', 'N', 'I', 'Z'}, // 9
{'C', 'R', 'I', 'M', 'E', 'N'}, // 10
{'C', 'O', 'L', 'E', 'R', 'A'}, // 11
{'C', 'O', 'M', 'I', 'T', 'E'}, // 12
{'C', 'U', 'P', 'U', 'L', 'A'}, // 13
{'C', 'I', 'B', 'O', 'R', 'G'}, // 14
{'D', 'E', 'B', 'I', 'T', 'O'}, // 15
{'D', 'E', 'N', 'T', 'A', 'R'}, // 16
{'D', 'E', 'S', 'L', 'I', 'Z'}, // 17
{'D', 'E', 'L', 'I', 'T', 'O'}, // 18
{'E', 'N', 'I', 'G', 'M', 'A'}, // 19
{'E', 'O', 'L', 'I', 'C', 'O'}, // 20
{'E', 'X', 'I', 'M', 'I', 'R'}, // 21
{'E', 'X', 'I', 'L', 'I', 'O'}, // 22
{'E', 'T', 'E', 'R', 'E', 'O'}, // 23
{'F', 'R', 'A', 'G', 'I', 'L'}, // 24
{'F', 'R', 'A', 'U', 'D', 'E'}, // 25
{'F', 'A', 'B', 'U', 'L', 'A'}, // 26
{'F', 'E', 'R', 'U', 'L', 'A'}, // 27
{'G', 'A', 'N', 'D', 'U', 'L'}, // 28
{'G', 'E', 'R', 'M', 'E', 'N'}, // 29
{'G', 'E', 'S', 'T', 'A', 'R'}, // 30
{'G', 'A', 'N', 'Z', 'U', 'A'}, // 31
{'G', 'R', 'A', 'G', 'E', 'A'}, // 32
{'H', 'U', 'R', 'T', 'A', 'R'}, // 33
{'H', 'A', 'S', 'T', 'I', 'O'}, // 34
{'H', 'U', 'E', 'L', 'L', 'A'}, // 35
{'H', 'I', 'N', 'C', 'A', 'R'}, // 36
{'I', 'N', 'N', 'A', 'T', 'O'}, // 37
{'I', 'N', 'F', 'A', 'M', 'E'}, // 38
{'I', 'N', 'C', 'O', 'A', 'R'}, // 39
{'I', 'N', 'O', 'C', 'U', 'O'}, // 40
{'I', 'M', 'P', 'E', 'T', 'U'}, // 41
{'J', 'O', 'V', 'I', 'A', 'L'}, // 42
{'J', 'U', 'B', 'I', 'L', 'O'}, // 43
{'J', 'A', 'R', 'A', 'N', 'A'}, // 44
{'K', 'I', 'M', 'O', 'N', 'O'}, // 45
{'L', 'U', 'D', 'I', 'C', 'O'}, // 46
{'L', 'O', 'C', 'U', 'A', 'Z'}, // 47
{'L', 'I', 'N', 'A', 'J', 'E'}, // 48
{'M', 'A', 'C', 'I', 'Z', 'O'}, // 49
{'M', 'E', 'R', 'C', 'E', 'D'}, // 50
{'M', 'O', 'H', 'O', 'S', 'O'}, // 51
{'M', 'A', 'R', 'C', 'H', 'A'}, // 52
{'N', 'O', 'M', 'A', 'D', 'A'}, // 53
{'N', 'E', 'U', 'T', 'R', 'O'}, // 54
{'N', 'O', 'C', 'I', 'V', 'O'}, // 55
{'N', 'A', 'I', 'L', 'O', 'N'}, // 56
{'O', 'S', 'A', 'D', 'I', 'A'}, // 57
{'O', 'Y', 'E', 'N', 'T', 'E'}, // 58
{'O', 'D', 'I', 'S', 'E', 'A'}, // 59
{'O', 'O', 'L', 'I', 'T', 'O'}, // 60
{'O', 'C', 'T', 'E', 'T', 'O'}, // 61
{'P', 'E', 'R', 'I', 'T', 'O'}, // 62
{'P', 'R', 'I', 'M', 'O', 'R'}, // 63
{'P', 'U', 'L', 'C', 'R', 'O'}, // 64
{'P', 'U', 'E', 'R', 'I', 'L'}, // 65
{'P', 'I', 'E', 'D', 'A', 'D'}, // 66
{'P', 'R', 'A', 'X', 'I', 'S'}, // 67
{'Q', 'U', 'I', 'E', 'T', 'O'}, // 68
{'Q', 'U', 'E', 'M', 'A', 'R'}, // 69
{'R', 'E', 'A', 'C', 'I', 'O'}, // 70
{'R', 'U', 'M', 'I', 'A', 'R'}, // 71
{'R', 'A', 'B', 'I', 'N', 'O'}, // 72
{'R', 'E', 'H', 'U', 'I', 'R'}, // 73
{'R', 'I', 'S', 'T', 'R', 'A'}, // 74
{'R', 'E', 'T', 'A', 'C', 'O'}, // 75
{'S', 'E', 'V', 'E', 'R', 'O'}, // 76
{'S', 'O', 'N', 'D', 'E', 'O'}, // 77
{'S', 'A', 'N', 'D', 'I', 'A'}, // 78
{'S', 'U', 'B', 'I', 'T', 'O'}, // 79
{'S', 'O', 'L', 'F', 'E', 'O'}, // 80
{'S', 'U', 'M', 'M', 'U', 'M'}, // 81
{'T', 'U', 'T', 'E', 'L', 'A'}, // 82
{'T', 'I', 'T', 'E', 'R', 'E'}, // 83
{'T', 'R', 'E', 'C', 'H', 'O'}, // 84
{'T', 'A', 'N', 'D', 'E', 'M'}, // 85
{'U', 'T', 'O', 'P', 'I', 'A'}, // 86
{'U', 'F', 'A', 'N', 'I', 'A'}, // 87
{'U', 'M', 'B', 'R', 'I', 'O'}, // 88
{'U', 'M', 'B', 'R', 'A', 'L'}, // 89
{'V', 'I', 'L', 'E', 'Z', 'A'}, // 90
{'V', 'A', 'I', 'V', 'E', 'N'}, // 91
{'V', 'E', 'N', 'A', 'D', 'O'}, // 92
{'V', 'U', 'L', 'G', 'A', 'R'}, // 93
{'V', 'I', 'V', 'E', 'R', 'O'}, // 94
{'W', 'H', 'I', 'S', 'K', 'Y'}, // 95
{'X', 'E', 'R', 'I', 'C', 'O'}, // 96
{'Y', 'U', 'N', 'Q', 'U', 'E'}, // 97
{'Z', 'O', 'C', 'A', 'L', 'O'}, // 98
{'Z', 'A', 'H', 'O', 'R', 'I'}, // 99
{'Z', 'U', 'R', 'R', 'O', 'N'}, // 100
};

unsigned int holdCount = 0;
int adivinado[6] = {91,91,91,91,91,91};
int solucion[6] = {91,91,91,91,91,91};
unsigned int vidas = 5;
unsigned int bloqueo = 1;
unsigned int parar = 0;
unsigned int num_letras = 0;
unsigned int i;
unsigned int letrasUsadas[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int juego;
int inicio = 1;
unsigned int contador = 0;
int puntuacion[2] = {0,0};
int jugAct = 0;
unsigned int valor = 30;
unsigned int rondas = 0;
unsigned int limpiarTerminal = 0;
unsigned int contadorLimpieza = 0;
unsigned int letrasPrint = 0;

int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    PM5CTL0 &= ~ LOCKLPM5; // Activar periféricos

    /*******************************************************************************
     * CONFIGURAMOS LA UART
     ******************************************************************************/

    // Para la utilización de los pines 4 y 5 del puerto 3 por la UART, seleccionamos la función del módulo primario (es decir, 01) en los bits de selección
    P3SEL0 |= BIT4 | BIT5;
    P3SEL1 &= ~BIT4 & ~BIT5;

    CSCTL0_H = CSKEY >> 8; // Unlock clock registers
    CSCTL1 = DCOFSEL_3 | DCORSEL; // Set DCO to 8MHz
    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1; // Set all dividers
    CSCTL0_H = 0; // Lock CS registers

    // Configure USCI_A1 for UART mode
    UCA1CTLW0 = UCSWRST; // Put eUSCI in reset
    UCA1CTLW0 |= UCSSEL__SMCLK; // CLK = SMCLK

    // Baud Rate calculation
    // 8000000/(16*9600) = 52.083
    // Fractional portion = 0.083
    // User's Guide Table 21-4: UCBRSx = 0x04
    // UCBRFx = int ( (52.083-52)*16) = 1
    UCA1BR0 = 52; // 8000000/16/9600
    UCA1BR1 = 0x00;
    UCA1MCTLW |= UCOS16 | UCBRF_1 | 0x4900;
    UCA1CTLW0 &= ~UCSWRST; // Initialize eUSCI

    // Configure interruptions to receive and transmit data in register UCA1IE (Completar)
    UCA1IE |= BIT0; // Activamos las interrupciones de recepcion
    UCA1IE |= BIT1; // Activamos las interrupciones de transmision

    /*******************************************************************************
     * CONFIGURAMOS EL RELOJ
     ******************************************************************************/

    //Escoge la señal de reloj a utilizar: ACLK
    //Establece el divisor de frecuencia: /1
    //Establece el modo de control a subida: Up
    //Resetea el contador antes de empezar (hace un clear)
    TA0CTL = TASSEL__ACLK | ID__1 | MC__UP | TACLR;

    TA0CCR0 = 10000; //Establece el numero que alcanza el contador
    TA0CCTL0 = CCIE;

    TA1CTL = TASSEL__ACLK | ID__1 | MC__UP | TACLR;

    TA1CCR0 = 10000; //Establece el numero que alcanza el contador
    TA1CCTL0 = CCIE;
    Initialize_LCD();

    /*******************************************************************************
     * CONFIGURAMOS LOS LEDS
     ******************************************************************************/

    P1SEL0 &= ~BIT0;
    P1SEL1 &= ~BIT0;
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    P9SEL0 &= ~BIT7;
    P9SEL1 &= ~BIT7;
    P9DIR |= BIT7;
    P9OUT &= ~BIT7;

    /*******************************************************************************
     * CONFIGURAMOS EL BOTON
     ******************************************************************************/

    P1SEL0 &= ~BIT1;
    P1SEL1 &= ~BIT1;
    P1DIR &= ~BIT1;
    P1REN |= BIT1;
    P1OUT |= BIT1;

    P1IE |= BIT1; //Habilita interrupciones
    P1IES |= BIT1;
    P1IFG &= ~BIT1;


    P1SEL0 &= ~BIT2;
    P1SEL1 &= ~BIT2;
    P1DIR &= ~BIT2;
    P1REN |= BIT2;
    P1OUT |= BIT2;

    P1IE |= BIT2; //Habilita interrupciones
    P1IES |= BIT2;
    P1IFG &= ~BIT2;


    //Creamos una semilla aleatoria
    srand(time(NULL));

    /*******************************************************************************
     * COMIENZA EL JUEGO
     ******************************************************************************/
    introGlobal();
    __bis_SR_register ( LPM4_bits + GIE ) ;

}

void introGlobal(){
    inicio = 1;
    P1IFG &= ~BIT1;
    P1IFG &= ~BIT2;
    displayScrollText("BIENVENIDO A CONSOLA MSP     PULSE EL BOTON IZQUIERDO PARA AHORCADO     PULSE EL BOTON DERECHO PARA CONTADOR");
    //displayScrollText("BIENVENIDO");
}

void introContador(){
    displayScrollText("BIENVENIDO A CONTADOR MSP     SE EMPEZARA UNA CUENTA QUE LUEGO DESAPARECERA    DEBES PULSAR EL BOTON DERECHO CUANDO CONSIDERES QUE LA CUENTA HA ALCANZADO 30     OS IREIS TURNANDO ENTRE DOS JUGADORES CON 5 RONDAS CADA UNO     EL QUE MENOR PUNTUACION OBTENGA GANA     SI MANTIENES EL BOTON IZQUIERDO RESETEARAS LA CONSOLA     SUERTE");
    //displayScrollText("CONTADOR");
    __delay_cycles(1000000);
    iniContador();
}

void iniContador(){
    if(jugAct == 0){
        switch(rondas/2){
        case 0:
            displayScrollText("RONDA 1");
            break;
        case 1:
            displayScrollText("RONDA 2");
            break;
        case 2:
            displayScrollText("RONDA 3");
            break;
        case 3:
            displayScrollText("RONDA 4");
            break;
        case 4:
            displayScrollText("RONDA 5");
            break;
        }
        displayScrollText("TURNO DEL JUGADOR 1");
    }
    else displayScrollText("TURNO DEL JUGADOR 2");
    int frec = rand()%4;
    switch(frec){
        case 0:
                TA1CCR0 = 3000;
                break;
            case 1:
                TA1CCR0 = 5000;
                break;
            case 2:
                TA1CCR0 = 8000;
                break;
            case 3:
                TA1CCR0 = 10000;
                break;
    }
    TA1CTL |= TACLR;
    contador = 0;
    parar = 0;
    bloqueo = 0;
}

void introAhorcado(){
    resetAhorcado();
    displayScrollText("BIENVENIDO A AHORCADO MSP     TIENES 5 VIDAS PARA ADIVINAR LA PALABRA     DEBE INTRODUCIR UNA LETRA POR TURNO     CADA FALLO RESTA UNA VIDA     DEBES ADIVINAR UNA PALABRA ALEATORIA DE 6 LETRAS    SI MANTIENES EL BOTON IZQUIERDO RESETEARAS LA CONSOLA     SUERTE");
    //displayScrollText("AHORCADO");
    ShowBuffer(adivinado);
}

/*******************************************************************************
 * FUNCIONES DE RESET
 ******************************************************************************/

void resetGlobal(){
    resetAhorcado();
    resetContador();
    introGlobal();
}

void resetContador(){
    puntuacion[0] = 0;
    puntuacion[1] = 0;
    rondas = 0;
    jugAct = 0;
    contador = 0;
    bloqueo = 0;
}

void resetAhorcado(){

    //Limpia el hyperterminal
    limpiarTerminal = 1;
    UCA1IFG |= BIT1;

    //Genera numero aleatorio
    int random = rand() % 100;
    for(i = 0; i < 6; i++){
        solucion[i] = palabras[random][i];
    }
    for(i = 0; i < 6; i++){
        adivinado[i] = 91;
    }
    vidas = 5;
    num_letras = 0;
    holdCount = 0;
    bloqueo = 0;
    for(i = 0; i < 26; i++) letrasUsadas[i] = 0;
}

/*******************************************************************************
 * CONFIGURAMOS LA RTI DE LA UART
 ******************************************************************************/

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void) {
    if(UCA1IFG & BIT0 & juego == 0 & bloqueo == 0) {
        unsigned int letra = UCA1RXBUF;
        if(letra >= 65 & letra <= 90 & letrasUsadas[letra - 65] == 0){
            unsigned int acertado = 0;
            for(i = 0; i < 6; i++){
                if(letra == solucion[i]) {
                    adivinado[i] = letra;
                    num_letras++;
                    acertado = 1;
                }
            }
            letrasUsadas[letra - 65] = 1;
            if(acertado == 0){
                //Mostramos por hyperterminal la letra errada
                UCA1TXBUF = letra;
                letrasPrint++;
                vidas--;
                P1OUT ^= BIT0;
                __delay_cycles(1000000);
                P1OUT ^= BIT0;
                if(vidas == 0){
                    bloqueo = 1;
                    __delay_cycles(1000000);
                    //P1OUT |= BIT0;
                    for (i = 0; i < 20; i++){
                        P1OUT ^= BIT0;
                        __delay_cycles(1000000);
                    }
                    displayScrollText("HAS PERDIDO     LA PALABRA ERA");
                    ShowBuffer(solucion);
                    __delay_cycles(4000000);
                    displayScrollText("RESETEA PULSANDO EL BOTON IZQUIERDO PARA UNA NUEVA PARTIDA");
                }
            }
            else{
                ShowBuffer(adivinado);
                P9OUT ^= BIT7;
                __delay_cycles(1000000);
                P9OUT ^= BIT7;
                if(num_letras == 6){
                    bloqueo = 1;
                    __delay_cycles(1000000);
                    //P9OUT |= BIT7;
                    for (i = 0; i < 20; i++){
                        P9OUT ^= BIT7;
                        __delay_cycles(1000000);
                    }
                    displayScrollText("HAS GANADO     RESETEA PULSANDO EL BOTON IZQUIERDO PARA UNA NUEVA PARTIDA");

                }
            }
        }
    }
    else if(UCA1IFG & BIT1){
        if(limpiarTerminal == 1){
            UCA1TXBUF = ' ';
            contadorLimpieza++;
            if(contadorLimpieza == (8*103-letrasPrint)){
                contadorLimpieza = 0;
                limpiarTerminal = 0;
                letrasPrint = 0;
            }
        }
        else
            UCA1IFG &= ~BIT1;
    }
    else {
        unsigned int letra = UCA1RXBUF;
    }

}

/*******************************************************************************
 * CONFIGURAMOS LA RTI DEL TIMER (si se mantiene pulsado el boton, reinicia)
 ******************************************************************************/

# pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR ( void ) {
    if(~P1IN & BIT1){
        holdCount++;
        if(holdCount == 3){
            displayScrollText("CONSOLA RESETEADA");
            resetGlobal();
            holdCount = 0;
        }
    }
    else {
        holdCount = 0;
    }
}

# pragma vector = TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR ( void ) {
    if(inicio == 0){
        if(juego == 1 & parar == 0 & bloqueo == 0){
            contador++;
            if(contador <= 10) display_num_lcd(contador);
            else ShowBuffer(adivinado);
        }
        else if(juego == 1 & parar == 1 & bloqueo == 0){
            display_num_lcd(contador);

            __delay_cycles(4000000);
            //meter extra

            if(contador > valor)
                puntuacion[jugAct] += contador - valor;
            else
                puntuacion[jugAct] += valor - contador;

            if(contador == valor) {
                P1OUT ^= BIT0;
                __delay_cycles(1000000);
                for (i = 0; i < 20; i++){
                    P1OUT ^= BIT0;
                    P9OUT ^= BIT7;
                    __delay_cycles(1000000);
                }
                P1OUT ^= BIT0;
            }

            if(jugAct == 0) displayScrollText("PUNTUACION JUGADOR 1");
            else displayScrollText("PUNTUACION JUGADOR 2");
            display_num_lcd(puntuacion[jugAct]);

            __delay_cycles(4000000);
            //meter extra

            jugAct = (jugAct + 1) % 2;
            rondas++;

            if(rondas == 10){
                if(puntuacion[0] > puntuacion[1]) {
                    for (i = 0; i < 20; i++){
                        P9OUT ^= BIT7;
                        __delay_cycles(1000000);
                    }
                    displayScrollText("HA GANADO EL JUGADOR 2     ENHORABUENA     PULSE EL BOTON IZQUIERDO PARA REINICIAR");
                }
                else if (puntuacion[0] < puntuacion[1]) {
                    for (i = 0; i < 20; i++){
                        P1OUT ^= BIT0;
                        __delay_cycles(1000000);
                    }
                    displayScrollText("HA GANADO EL JUGADOR 1     ENHORABUENA     PULSE EL BOTON IZQUIERDO PARA REINICIAR");
                }
                else {
                    for (i = 0; i < 20; i++){
                        P1OUT ^= BIT0;
                        P9OUT ^= BIT7;
                        __delay_cycles(1000000);
                    }
                    displayScrollText("HA HABIDO UN EMPATE     ENHORABUENA A LOS DOS     PULSE EL BOTON IZQUIERDO PARA REINICIAR");
                }
                bloqueo = 1;
            } else{
                iniContador();
            }
        }
    }
}

/*******************************************************************************
 * CONFIGURAMOS LA RTI DEL BOTON (inicia la partida)
 ******************************************************************************/

# pragma vector = PORT1_VECTOR
__interrupt void Port_1 ( void ) {
    if(P1IFG & BIT1){
        if(bloqueo == 1 & juego == 0 & inicio == 0){
            resetAhorcado();
            displayScrollText("DEBES ADIVINAR UNA PALABRA ALEATORIA DE 6 LETRAS    SI MANTIENES EL BOTON IZQUIERDO RESETEARAS LA CONSOLA     SUERTE");
        }
        else if (bloqueo == 1 & juego == 1 & inicio == 0){
            resetContador();
            displayScrollText("DEBES PULSAR EL BOTON DERECHO CUANDO CONSIDERES QUE LA CUENTA HA ALCANZADO 20     OS IREIS TURNANDO ENTRE DOS JUGADORES CON 5 RONDAS CADA UNO     EL QUE MENOR PUNTUACION OBTENGA GANA     SI MANTIENES EL BOTON IZQUIERDO RESETEARAS LA CONSOLA     SUERTE");
            iniContador();
        }
        else if(inicio == 1){
            juego = 0;
            inicio = 0;
            introAhorcado();
        }
        P1IFG &= ~BIT1;
    }
    else{
        if(parar == 0 & juego == 1 & inicio == 0){
            parar = 1;
        }
        else if(inicio == 1){
            juego = 1;
            inicio = 0;
            introContador();
        }
        P1IFG &= ~BIT2;
    }
}

