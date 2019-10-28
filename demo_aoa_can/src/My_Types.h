#ifndef TYPE_H_
#define TYPE_H_

#include "lpc_types.h"

#define GET_BIT(data,bit)	((data >> bit ) & 0x1)

#define LB(word)	((uint8_t)(word & 0x00FF))
#define HB(word)	((uint8_t)((word >> 8) & 0x00FF))

#define LLB(dword)	((uint8_t)(dword & 0x000000FF))
#define LHB(dword)	((uint8_t)((dword >> 8) & 0x000000FF))
#define HLB(dword)	((uint8_t)((dword >> 16) & 0x000000FF))
#define HHB(dword)	((uint8_t)((dword >> 24) & 0x000000FF))


#define BIT0	0
#define BIT1	1
#define BIT2	2
#define BIT3	3
#define BIT4	4
#define BIT5	5
#define BIT6	6
#define BIT7	7
#define BIT8	8
#define BIT9	9
#define BIT10	10
#define BIT11	11
#define BIT12	12
#define BIT13	13
#define BIT14	14
#define BIT15	15
#define BIT16	16
#define BIT17	17
#define BIT18	18
#define BIT19	19
#define BIT20	20
#define BIT21	21
#define BIT22	22
#define BIT23	23
#define BIT24	24
#define BIT25	25
#define BIT26	26
#define BIT27	27
#define BIT28	28
#define BIT29	29
#define BIT30	30
#define BIT31	31

#define NO		0
#define YES		1

#define STATE_OFF	0
#define STATE_ON	1

typedef enum {OFF = STATE_OFF, ON = STATE_ON} DIGITAL_STATE;

typedef enum {DISCONNECTED = 0, CONNECTED = !DISCONNECTED} CONNECTIVITY_STATE;

typedef enum {DISABLED = 0, ENABLED = !DISABLED} FUNCTIONAL_STATE;

typedef enum {EMPTY, NOTeMPTY_NOTfULL, FULL} BUFFER_STATE;


// Macro para verificar una condición en tiempo de compilación
#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))

#endif /* TYPE_H_ */
