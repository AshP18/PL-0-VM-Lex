//Ashley Peters

//Global Variables
int MAX_PAS_LENGTH = 500;
int GP = 0;
int IC = 0;
int DP = 0;
int FREE = 0;
int BP = 0;
int PC = 0;
int SP = 0;

//Struct for IR
typedef struct{

  //IR Values
  int OP;
  int L;
  int M;

}IR;

//Function Prototypes:
//***** Base Function
//******** Print Execution Function
int base(int L, int BP, int *PAS);
void print_execution(int line, char *opname, IR * Ir, int PC, int BP, int SP, int DP, int *PAS, int GP);

//Libraries
#include <stdio.h>
#include <string.h>

//Main
int main(int argc, char *argv[]) {

  //Open file from command line
  FILE * fp = fopen(argv[1], "r");

  //PAS declaration
  int PAS[MAX_PAS_LENGTH];

  //Integer declaration:
  //**** int i for loops
  //****** Do not hault flag (changes to 0 for program termination)
  //******** line value (PC / 3)
  //********** Op name string
  int i;
  int DoNotHault = 1;
  int line;
  char opname[4];

  //PAS set to 0 initialization 
  for (i = 0; i < MAX_PAS_LENGTH; i++) {
    PAS[i] = 0;
  }

  //Scan in instruction values from file,
  //Increment i and Instruction Counter (IC) by 3 to read in next instruction
  for (i = 0; i < MAX_PAS_LENGTH; i += 3) {
    fscanf(fp, "%d%d%d", &PAS[i], &PAS[i+1], &PAS[i+2]);
    IC = i + 3;
    
    //If end of program line is read, terminate instruction reading
    if (PAS[i] == 9 && PAS[i+1] == 0 && PAS[i+2] == 3) {
      break;
    }
  }

  //Close the file
  fclose(fp);

  //Change the default values appropriately after reading in instructions
  GP = IC;
  DP = IC - 1;
  FREE = IC + 10;
  BP = IC;
  PC = 0;
  SP = MAX_PAS_LENGTH;

  //Print initial headers
  printf("%25s", "PC");
  printf("%7s", "BP");
  printf("%7s", "SP");
  printf("%7s", "DP");
  printf("%7s", "Data\n");

  //Print out initial values
  printf("Initial Values:");
  printf("%*d", 10, PC);
  printf("%*d", 7, BP);
  printf("%*d", 7, SP);
  printf("%*d\n", 7, DP);

  //Make IR Struct
  IR Ir;

  //While loop to terminate if the DoNotHault flag is set to 0
  while (DoNotHault == 1) {
    //Get the current line:
    //Divided PC by 3 for each 3 parts of an instruction
    line = (PC / 3);

    //Fetch Cycle:
    //***** Read in instructions to IR struct
    Ir.OP = PAS[PC];
    Ir.L = PAS[PC + 1];
    Ir.M = PAS[PC + 2];

    //Increment PC
    PC += 3;
    
    //Execute Cycle:
    //**** Switch cases to appropriate OP code values
    //******* Print execution function added appropriately to each switch case
    switch(Ir.OP) {
      
      //Switch case 1 LIT Op code
      case 1: 
        strcpy(opname, "LIT");
        if (BP == GP) {
          DP = DP + 1;
          PAS[DP] = Ir.M;
        }
        else {
          SP = SP - 1;
          PAS[SP] = Ir.M;
        }
        print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
        break;
      //Switch case 2 RTN Op code
      case 2:
        //Secondary Switch cases for M code
        switch(Ir.M) {
          //Switch case 0 RTN M code
          case 0:
            strcpy(opname, "RTN");
            SP = BP + 1;
            BP = PAS[SP - 2];
            PC = PAS[SP - 3];
            printf("%d\n", PAS[SP -3]);
            print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
            break;
          
          //Switch case 1 NEG M code
          case 1:
            strcpy(opname, "NEG");
            if (BP == GP) {
              PAS[DP] = -1 * PAS[DP];
            }
            else {
              PAS[SP] = -1 * PAS[SP];
            }
            print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
            break;

          //Switch case 2 ADD M code
          case 2:
            strcpy(opname, "ADD");
            if (BP == GP) {
              DP = DP - 1;
              PAS[DP] = PAS[DP] + PAS[DP + 1];
            }
            else {
              SP = SP + 1;
              PAS[SP] = PAS[SP] + PAS[SP - 1];
            }
            print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
            break;

          //Switch case 3 SUB M code
          case 3:
            strcpy(opname, "SUB");
            if (BP == GP) {
              DP = DP - 1;
              PAS[DP] = PAS[DP] - PAS[DP + 1];
            }
            else {
              SP = SP + 1;
              PAS[SP] = PAS[SP] - PAS[SP - 1];
            }
            print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
            break;

          //Switch case 4 MUL M code
          case 4:
            strcpy(opname, "MUL");
            if (BP == GP) {
              DP = DP - 1;
              PAS[DP] = PAS[DP] * PAS[DP + 1];
            }
            else {
              SP = SP + 1;
              PAS[SP] = PAS[SP] * PAS[SP - 1];
            }
            print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
            break;
          
          //Switch case 5 DIV M code
          case 5:
            strcpy(opname, "DIV");
            if (BP == GP) {
              DP = DP - 1;
              PAS[DP] = PAS[DP] / PAS[DP + 1];
            }
            else {
              SP = SP + 1;
              PAS[SP] = PAS[SP] / PAS[SP - 1];
            }
            print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
            break;

          //Switch case 6 ODD M code
          case 6:
            strcpy(opname, "ODD");
            if (BP == GP) {
              PAS[DP] = PAS[DP] % 2;
            }
            else {
              PAS[SP] = PAS[SP] % 2;
            }
            print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
            break;

          //Switch case 7 MOD M code
          case 7:
            strcpy(opname, "MOD");
            if (BP == GP) {
              DP = DP - 1;
              PAS[DP] = PAS[DP] % PAS[DP + 1];
            }
            else {
              SP = SP + 1;
              PAS[SP] = PAS[SP] % PAS[SP - 1];
            }
            print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
            break;

          //Switch case 8 EQL M code
          case 8:
            strcpy(opname, "EQL");
            if (BP == GP) {
              DP = DP - 1;
              PAS[DP] = PAS[DP] == PAS[DP + 1];
            }
            else {
              SP = SP + 1;
              PAS[SP] = PAS[SP] == PAS[SP - 1];
            }
            print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
            break;

          //Switch case 9 NEQ M code
          case 9:
            strcpy(opname, "NEQ");
            if (BP == GP) {
              DP = DP - 1;
              PAS[DP] = PAS[DP] != PAS[DP + 1];
            }
            else {
              SP = SP + 1;
              PAS[SP] = PAS[SP] != PAS[SP - 1];
            }
            print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
            break;

          //Switch case 10 LSS M Code
          case 10:
            strcpy(opname, "LSS");
            if (BP == GP) {
              DP = DP - 1;
              PAS[DP] = PAS[DP] < PAS[DP + 1];
            }
            else {
              SP = SP + 1;
              PAS[SP] = PAS[SP] < PAS[SP - 1];
            }
            print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
            break;

          //Switch case 11 LEQ M code
          case 11:
            strcpy(opname, "LEQ");
            if (BP == GP) {
              DP = DP - 1;
              PAS[DP] = PAS[DP] <= PAS[DP + 1];
            }
            else {
              SP = SP + 1;
              PAS[SP] = PAS[SP] <= PAS[SP - 1];
            }
            print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
            break;

          //Switch case 12 GTR M code
          case 12:
            strcpy(opname, "GTR");
            if (BP == GP) {
              DP = DP - 1;
              PAS[DP] = PAS[DP] > PAS[DP + 1];
            }
            else {
              SP = SP + 1;
              PAS[SP] = PAS[SP] > PAS[SP - 1];
            }
            print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
            break;

          //Switch case 13 GEQ M code
          case 13:
            strcpy(opname, "GEQ");
            if (BP == GP) {
              DP = DP - 1;
              PAS[DP] = PAS[DP] >= PAS[DP + 1];
            }
            else {
              SP = SP + 1;
              PAS[SP] = PAS[SP] >= PAS[SP - 1];
            }
            print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
            break;
        }
        break;
      
      //Switch case 3 LOD Op code:
      //***** Base function called appropriately
      case 3:
        strcpy(opname, "LOD");
        if (BP == GP) {
          DP = DP + 1;
          PAS[DP] = PAS[GP + Ir.M];
        }
        else {
          if (base(Ir.L, BP, PAS) == GP) {
            SP = SP - 1;
            PAS[SP] = PAS[GP + Ir.M];
          }
          else
            SP = SP - 1;
            PAS[SP] = PAS[base(Ir.L, BP, PAS) - Ir.M];
        }
        print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
        break;

      //Switch case 4 STO Op code:
      //***** Base function called appropriately
      case 4:
        strcpy(opname, "STO");
        if (BP == GP) {
          PAS[GP + Ir.M] = PAS[DP];
          DP = DP - 1;
        }
        else {
          if (base(Ir.L, BP, PAS) == GP) {
            PAS[GP + Ir.M] = PAS[SP];
            SP = SP + 1;
          }
          else {
            PAS[base(Ir.L, BP, PAS) - Ir.M] = PAS[SP];
            SP = SP + 1;
          }
        }
        print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
        break;

      //Switch case 5 CAL Op code:
      //***** Base function called appropriately
      case 5:
        strcpy(opname, "CAL");
        PAS[SP - 1] = base(Ir.L, BP, PAS);
        PAS[SP - 2] = BP;
        PAS[SP - 3] = PC;
        BP = SP - 1;
        PC = Ir.M;
        print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
        break;

      //Switch case 6 INC Op code
      case 6:
        strcpy(opname, "INC");
        if (BP == GP) {
          DP = DP + Ir.M;
        }
        else {
          SP = SP - Ir.M;
        }
        print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
        break;

      //Switch case 7 JMP Op code
      case 7:
        strcpy(opname, "JMP");
        PC = Ir.M;
        print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
        break;

      //Switch case 8 JPC Op code
      case 8:
        strcpy(opname, "JPC");
        if (BP == GP) {
          if (PAS[DP] == 0) {
            PC = Ir.M;
          }
          DP = DP - 1;
        }
        else {
          if (PAS[SP] == 0) {
            PC = Ir.M;
          }
          SP = SP + 1;
        }
        print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
        break;

      //Switch case 9 SYS Op code
      case 9:
        strcpy(opname, "SYS");
        //Secondary switch cases for M code values
        switch(Ir.M) {
          //Switch case 1 Top Stack Value print M code
          case 1:
            if (BP == GP) {
              printf("Top of Stack Value: ");
              printf("%d\n", PAS[DP]);
              DP = DP - 1;
            }
            else {
              printf("Top of Stack Value: ");
              printf("%d\n", PAS[SP]);
              SP = SP + 1;
            }
            print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
            break;

          //Switch case 2 Integer read M code
          case 2:
            if (BP == GP) {
              DP = DP + 1;
              printf("Please Enter an Integer: ");
              scanf("%d", &PAS[DP]);
            }
            else {
              SP = SP - 1;
              printf("Please Enter an Integer: ");
              scanf("%d", &PAS[SP]);
            }
            print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
            break;

          //Switch case 3 Hault Program M code
          case 3:
            DoNotHault = 0;
            print_execution(line, opname, &Ir, PC, BP, SP, DP, PAS, GP);
            break;
        }
        break;
    }
  }
  //End main
  return 0;
}


/**********************************************/
  /*      Find base L levels down           */
  /*                                        */
/**********************************************/

int base(int L, int BP, int *PAS){
  int arb = BP; // arb = activation record base
  while ( L > 0) {    //find base L levels down
  arb = PAS[arb];
  L--;
  }
  return arb;
  }

  void print_execution(int line, char *opname, IR * Ir, int PC, int BP, int SP, int DP, int *PAS, int GP) {
    int i;
    // print out instruction and registers
    printf("%d", line);
    printf("%*s", 5, opname);
    printf("%*d", 5, Ir->L);
    printf("%*d", 5, Ir->M);
    printf("%*d", 8, PC);
    printf("%*d", 7, BP);
    printf("%*d", 7, SP);
    printf("%*d", 7, DP);
    printf("   ");
    // print data section
    for (i = GP; i <= DP; i++)
      printf("%d ", PAS[i]);
    printf("\n");
    // print stack
    printf("\tstack : ");
    for (i = MAX_PAS_LENGTH - 1; i >= SP; i--)
      printf("%d ", PAS[i]);printf("\n");
  }