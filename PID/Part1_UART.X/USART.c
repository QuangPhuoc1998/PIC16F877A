#include "main.h"
#include "USART.h"


void UART_Init(int baudRate)
{    
    // ngat
    GIE = 1; // ngat toan cuc
    PEIE = 1; // ngat ngoai vi
    RCIE = 1; 
    TXIE = 1;
    // cau hinh port
    TRISC7 = 1; // RX la input
    TRISC6 = 0; // TX la output
    // cau hinh thanh ghi TXSTA
    CSRC = 0;
    TX9 = 0; // cho phep gui 8 bit
    TXEN = 1; // cho phep truyen du lieu
    SYNC = 0; // che do khong dong bo
    BRGH = 1; // toc do cao
    TRMT = 0; // TSR full
    TX9D = 0; // bit thu 9
    // cau hinh thanh ghi RCSTA
    SPEN = 1; // cho phep nhan cong noi tiep
    RX9 = 0; // cho phep nhan 8 bit
    SREN = 0; // khong quan tam
    CREN = 1; // cho phep nhan du lieu lien tuc
    ADDEN = 0; // Không cho phép phát hi?n ??a ch? , t?t c? byte ???c nh?n và bit th? 9 dùng làm bit parity.- 
    FERR = 0; // bit bao loi frame
    OERR = 0; // khong loi
    RX9D = 0; // bit thu 9 neu nhan 9 bit
    // cai dat toc do baud rate
    SPBRG = (20000000/(long)(16*(baudRate+1)));      // baud rate @20Mhz Clock
}
void UART_TxChar(char ch)
{
    while(TXIF==0);    // Wait till the transmitter register becomes empty
    TXIF=0;            // Clear transmitter flag
    TXREG=ch;          // load the char to be transmitted into transmit reg
}
char UART_RxChar()
{
    while(RCIF==0);    // Wait till the data is received 
    RCIF=0;            // Clear receiver flag
    return(RCREG);     // Return the received data to calling function
}