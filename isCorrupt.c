#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct pkt {
	int seqnum;
	int acknum;
	int checksum;
	char payload[20];
};

void isCorruptTester();
int computeChecksum(char[], int);
void testNoBitCorruption();
void testBitCorruption();
int isCorrupt(struct pkt);

int main()
{
    isCorruptTester();
}

/*Converts 32 bit integer into C str*/
char* toBinary (int x)
{
    char* msg = (char*) malloc(33* sizeof(char));
    msg[32] = '\0';
    int i;
    for (i = 0; i < 32; i++){
        msg[31-i] = '0' + ((x >> i) & 1);
    }
     return msg;
}

void isCorruptTester()
{
    testNoBitCorruption(); 
    testBitCorruption();    
}

void testBitCorruption()
{
    int i;
    char msg[] = "TestMessage!";

    struct pkt sndPkt;

    i = 0;
    while(msg[i] != '\0')
        sndPkt.payload[i++] = msg[i];

    sndPkt.checksum = computeChecksum(sndPkt.payload,20);
    //Simulate bit corruption.
    sndPkt.payload[0] = 'H';
    
    assert(isCorrupt(sndPkt));
    printf("testBitCorruption() test passed!\n");
}

void testNoBitCorruption()
{
     int i;
     char msg [20]; 
     for (i = 0; i < 19; i++)
	     msg[i] = 'c';
     msg[19] = '\0'; //Null terminated string

        
     struct pkt packet1;
     for (i = 0; i < 20; ++i)
         packet1.payload[i] = msg[i];
     packet1.checksum = computeChecksum(msg, 20);

     assert(!isCorrupt(packet1));
     printf("testNoBitCorruption Test passed!\n");
}


int computeChecksum(char msg[], int len)
{
    int sum = 0;
    int i;
    for (i = 0; i < len && msg[i] != '\0'; i++)
	    sum += msg[i];
    return ~sum;
}

int isCorrupt(struct pkt packet)
{
    int expectedChecksum = packet.checksum;
    int calculatedChecksum = 0;
    int msgLen = 20;

    int i;
    for (i = 0; i < msgLen; i++)
        calculatedChecksum += (packet.payload)[i];
        
    char* calculated = toBinary(calculatedChecksum);
    char* expected = toBinary(expectedChecksum);
    char* sum = toBinary(calculatedChecksum + expectedChecksum);

    printf("calculated sum: %s\n", calculated);
    printf("packet checksum: %s\n", expected);
    printf("sum: %s\n", sum);

    free(calculated);
    free(expected);
    free(sum);

    return ((expectedChecksum + calculatedChecksum) != (0xFFFFFFFF));
}
