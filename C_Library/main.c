/* put this code in your main.c!

#define _XTAL_FREQ 80000000
#define ALL //CAN ID = 1 (put your module define here (see pic18f458_badgerloop.c))

volatile uint8_t receivedData[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    //receivedData[0-7] = data
volatile uint8_t sendData[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    //sendData[0-7] = data


void CAN_Transmit(void)
{
    uint16_t canId = CAN_IDENTIFIER;
    canId = (canId<<5);

    //  wait till transmission
    while(TXB0CON & (1<<3));
    //  load CAN ID
    TXB0SIDL = (uint8_t)(canId & 0x00E0); // standard 11bit Identifier
    TXB0SIDH = (uint8_t)((canId>>8)& 0x00FF);

    //  Data length = 1byte == 8 bits or a unsigned 8 bit integer (uint8_t) ;)
    //TXB0DLC = 0x01;
    TXB0DLC = 0x08;

    //  load data
    TXB0D0 = sendData[0];
    TXB0D1 = sendData[1];
    TXB0D2 = sendData[2];
    TXB0D3 = sendData[3];
    TXB0D4 = sendData[4];
    TXB0D5 = sendData[5];
    TXB0D6 = sendData[6];
    TXB0D7 = sendData[7];

    //  start transmission
    TXB0CON = (1<<3);

}

uint16_t CAN_Receive(void)
{
    //receivedData[0-7] = data

    uint8_t canIdH=0;
    uint8_t canIdL=0;
    uint16_t canId=0;

    //  wait till reception
    while(!(RXB0CON & (1<<7)));

    // copy CAN ID
    canIdL = RXB0SIDL;
    canIdH = RXB0SIDH;

    //  copy data
    receivedData[0] = RXB0D0;
    receivedData[1] = RXB0D1;
    receivedData[2] = RXB0D2;
    receivedData[3] = RXB0D3;
    receivedData[4] = RXB0D4;
    receivedData[5] = RXB0D5;
    receivedData[6] = RXB0D6;
    receivedData[7] = RXB0D7;
    
    // clear receive flag
    RXB0CON &= ~(1<<7);

    canId = canIdH<<3;
    canId |= canIdL>>5;
	
    return canId;
}

//OPTIONAL but helpful for debugging

#define LED_PIN LATBbits.LATB0

void flashLED(void) {
    int count;
    count = 10;
    while(1) {
        LED_PIN = 1;   // RB-0 to High  
        delayzz();
        LED_PIN = 0;    // RB-0 to LOW
        delayzz();
        count--;
        if (count == 0)
        {
            break;
        }
    }
}

*/