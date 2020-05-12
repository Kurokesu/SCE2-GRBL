#ifndef TMC2300_H
#define TMC2300_H

unsigned char reverseBits(unsigned char num);
void swuart_calcCRC(unsigned char * datagram, unsigned char datagramLength);
void set_pwr(unsigned char motor, unsigned char run_pwr, unsigned char idle_pwr);
void tmc_test(unsigned char motor);
void tmc_set(unsigned char motor, unsigned char d3, unsigned char d2, unsigned char d1, unsigned char d0);
void tmc_read(unsigned char motor, unsigned char reg);

#endif
