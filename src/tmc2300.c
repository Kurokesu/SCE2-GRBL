#include "grbl.h"


unsigned char reverseBits(unsigned char num)
{
	// https://www.geeksforgeeks.org/write-an-efficient-c-program-to-reverse-bits-of-a-number/
    unsigned char count = sizeof(num) * 8 - 1;
    unsigned char reverse_num = num;

    num >>= 1;
    while(num)
    {
       reverse_num <<= 1;
       reverse_num |= num & 1;
       num >>= 1;
       count--;
    }
    reverse_num <<= count;
    return reverse_num;
}


void swuart_calcCRC(unsigned char * datagram, unsigned char datagramLength)
{
	int i, j;
	unsigned char* crc = datagram + (datagramLength-1); // CRC located in last byte of message
	unsigned char currentByte;
	*crc = 0;
	for (i=0; i<(datagramLength-1); i++)
	{    // Execute for all bytes of a message
		currentByte = datagram[i];  // Retrieve a byte to be sent from Array
		for (j=0; j<8; j++)
		{
			if ((*crc >> 7) ^ (currentByte&0x01))   // update CRC based result of XOR operation
			{
				*crc = (*crc << 1) ^ 0x07;
			}
			else
			{
				*crc = (*crc << 1);
			}
		currentByte = currentByte >> 1;
		} // for CRC bit
	} // for message byte
}

/*
void set_pwr(unsigned char motor, unsigned char run_pwr, unsigned char idle_pwr)
{
	unsigned char cmd1[] = {0x05, motor, 0x90, 0x00, 0x00, run_pwr, idle_pwr, 0xFF}; // set CRC to FF and calculate in next step
	swuart_calcCRC(cmd1, 8);

	for(int i=0; i<8; i++)
	{
		USART_SendData(USART3, cmd1[i]);
		while (!(USART3->SR & USART_FLAG_TXE));
	}
}
*/

void tmc_set(unsigned char motor, unsigned char reg, unsigned char d3, unsigned char d2, unsigned char d1, unsigned char d0)
{
	unsigned char cmd1[] = {0x05, motor, reg, d3, d2, d1, d0, 0xFF}; // set CRC to FF and calculate in next step
	swuart_calcCRC(cmd1, 8);

	for(int i=0; i<8; i++)
	{
		USART_SendData(USART3, cmd1[i]);
		while (!(USART3->SR & USART_FLAG_TXE));
	}
}

/*
void tmc_test(unsigned char motor)
{
	unsigned char cmd1[] = {0x05, motor, 0x22, 0x00, 0x00, 0x25, 0x00, 0xFF}; // set CRC to FF and calculate in next step
	// data = make_w_command(slave=0, register=TMC2300_register.VACTUAL, d0=00, d1=0x01, d2=0x25, d3=0xff) # rotate

	swuart_calcCRC(cmd1, 8);

	for(int i=0; i<8; i++)
	{
		USART_SendData(USART3, cmd1[i]);
		//USART_SendData(USART3, reverseBits(cmd1[i]));
		while (!(USART3->SR & USART_FLAG_TXE));
	}
}
*/


void tmc_read(unsigned char motor, unsigned char reg)
{
	  char buffer[30];

	  serial3_reset_read_buffer();

	  unsigned char cmd1[] = {0x05, motor, reg, 0xFF}; // set CRC to FF and calculate in next step
	  swuart_calcCRC(cmd1, 4);

	  for(int i=0; i<4; i++)
	  {
		  USART_SendData(USART3, cmd1[i]);
		  while (!(USART3->SR & USART_FLAG_TXE));
	  }

	  _delay_ms(10);

	  int c1 = 0;
	  c1 = serial3_get_rx_buffer_count();

	  printString("[TMC:");
	  for(int i=0; i < c1; i++)
	  {
		  uint8_t d = serial3_read();
		  itoa (d, buffer, 10);
		  printString(buffer);
		  if(i<(c1-1))
			  printString(",");
	  }
	  printString("]\r\n");

	  serial3_reset_read_buffer();

}
