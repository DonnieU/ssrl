/**
frame HEADER        = 0x7e
frame END           = 0x7e
ESC character        = 0x7d
ESC HEADER/END(0x7e)= 0x7d 0x5e
ESC ESC (0x7d)		= 0x7d 0x5d
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FRAME_SIZE 258     //	indicates total frame size (in bytes)
#define DATA_SIZE 256	//	indicates size of data message (in bytes)
#define FLAG 0x7e		//	indicates flag for frame start or end


int OS_Delay(int i)
{
	return (1);
}

int csk_uart1_count(void)
{
	return (1);
}

char csk_uart1_getchar(void)
{
	char temp[258];
	int i = 0;
	
	return ('c');
}

int recv_frame(char *msg, int frame_size)
{
	int check = 0;
    
	//de-stuffed message
	char dmsg[DATA_SIZE];
		
	// byte stuffed character signature
	char ESC_FLAG[]={0x7d, 0x5e};
	char ESC_ESC[]={0x7d, 0x5d};
		
	while(1)
	{
		while(!csk_uart1_count() > 0) OS_Delay(1);
		check = 0;
		while(csk_uart1_count() > 0 && !check)
		{
			
			/**
			//msg[0] = csk_uart1_getchar();
			
			// check for header
			if(msg[0] == FLAG)
			{
				check = 1;
				int i = 0;	// int counter for 'for' loop below -->
				for (i = 1; i < FRAME_SIZE; i++)
				{
					
					//msg[i] = csk_uart1_getchar();
				}
				
				check = 0;
			}
			**/

			// discards frame if not correct size or header/end aren't in the right places
			if ((frame_size != FRAME_SIZE) || (msg[0] != FLAG) || (msg[FRAME_SIZE-1] != FLAG))
			{
				printf("Discarded message\n");
        			printf("%x\n", msg[0]);
                		printf("%x\n", msg[FRAME_SIZE-1]);
				msg[0] = '\0';
				return (-1);
			}
			else
			{
				// looks for byte stuffed characters in msg
				int j = 0;	//	int counter for 'for' loop below -->
				for (j = 0; j < FRAME_SIZE; j++)
				{
					// byte stuffed character check for ESC_FLAG
					if ((msg[j] == ESC_FLAG[0]) && (msg[j+1] == ESC_FLAG[1]))
					{
						// writes escaped character to de-stuffed message
						dmsg[j] = 0x7e;
                        			printf("De-stuffed ESC_FLAG\n");
					}
					// byte stuffed character check for ESC_ESC
					else if ((msg[j] == ESC_ESC[0]) && (msg[j+1] == ESC_ESC[1]))
					{
						// writes escaped character to de-stuffed message
						dmsg[j] = 0x7d;
                        			printf("De-stuffed ESC_ESC\n");
					}
					// drops start flag from de-stuffed message
					else if (msg[j] == FLAG)
					{
						continue;
					}
					// drops start flag from de-stuffed message
					else if (msg[j] == FLAG)
					{
						continue;
					}
					else
					{
						dmsg[j] = msg[j];
					}
				}
    
				return (0);
			}
		}		
    }// end while(1)
}// end recv_frame

int main(void)
{	
	char frame[258];
    
    int i = 0;
    for (i = 0; i < FRAME_SIZE; i++)
	{
		frame[i] = i;
	}
     
	frame[0] = FLAG;
	frame[FRAME_SIZE-1] = FLAG;
	
	frame[30] = 0x7d;
	frame[31] = 0x5e;
	
	frame[90] = 0x7d;
	frame[91] = 0x5d;
    
    recv_frame(frame, sizeof(frame));
	return 0;
}
