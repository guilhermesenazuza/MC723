#include <stdio.h>
#define START_ADRESS (0x6410000)

#define OP1_ADRESS (0x6420000)
#define OP2_ADRESS (0x6430000)
#define RESULT_ADRESS (0x7410000)



volatile int *lock = (volatile int *) START_ADRESS;
volatile int *operand1 = (volatile int *) OP1_ADRESS;
volatile int *operand2 = (volatile int *) OP2_ADRESS;
volatile int *wresult = (volatile int *) RESULT_ADRESS;

static int procCounter = 0;
static double result= 0;

void AcquireLock(){
  while(*lock);
}

void ReleaseLock(){
  *lock = 0;
}

void send_operands(){
  *operand1 = 555;
  *operand2 = 555;
}

void read_result(){
  // result = *wresult;
  printf("Result from Mips %d:%u\n ",procCounter,*wresult);
}

// int  multiply(int procvalue){
//     int value;
//     value = procvalue*2;
//     return value;
// }

int main(int ac, char *av[]){
  int procNumber;
  // int doublevalue;

  AcquireLock();
  procNumber = procCounter;
  printf("Hello from Mips %d:\n ",procNumber);
  procCounter++;
  // if (procNumber==0){
    send_operands();
    read_result();
  // }
  ReleaseLock();

  // AcquireLock();
  // doublevalue = multiply(procNumber);
  // printf("Times x2 %d:\n ", doublevalue);
  // ReleaseLock();

  return 0;
  }
