/* 
	This is the lex.c file for the UCF Fall 2021 Systems Software Prolex_indexect.
	For HW2, you must implement the function lexeme *lexanalyzer(char *input).
	You may add as many constants, global variables, and support functions
	as you desire.
	
	If you choose to alter the printing functions or delete list or lex_index, 
	you MUST make a note of that in you readme file, otherwise you will lose 
	5 points.
*/


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "compiler.h"
#define MAX_NUMBER_TOKENS 500
#define MAX_IDENT_LEN 11
#define MAX_NUMBER_LEN 5

lexeme *list;
int lex_index;

void printlexerror(int type);
void printtokens();


lexeme *lexanalyzer(char *input)
{
  //variables
  int i;
  int codeLength = 500;
  int error;

  //temp word and word len for identifiers
  char temp_word[MAX_IDENT_LEN];
  int word_len;

  //temp num and num len for numbers
  char temp_num[MAX_NUMBER_LEN];
  int num_len;

  //set lex index to 0
  lex_index = 0;

  //create the list and allocate the memory
  lexeme *list = malloc(MAX_NUMBER_TOKENS * sizeof(list));


  //Cleans code to get rid of comments and newlines to make code easier to analyze
  for (i = 0; i < codeLength; i++) {
    if (input[i] == '/') {
      if (input[i + 1] == '/') {
        input[i] = ' ';
        input[i + 1] = ' ';
        i++;
        for (i = i; i < codeLength; i++) {
          if (input[i] != '\n') {
            input[i] = ' ';
          }
          else {
            input[i] = ' ';
            break;
          }
        }
      }
    }
  }

  //Run through cleaned code and do all the cool stuff
  for (i = 0; i < codeLength; i++) {

    //Set temp word and num to 0 and empty
    word_len = 0;
    num_len = 0;
    memset(temp_word, 0, strlen(temp_word));
    memset(temp_num, 0, strlen(temp_num));

    // space check
    if (input[i] == ' ') {
      continue;
    }

    // word check
    else if (isalpha(input[i])) {

      // const check
      if (input[i] == 'c' && input[i + 1] == 'o' && input[i + 2] == 'n' && input[i + 3] == 's' && input[i + 4] == 't' && isalpha(input[i + 5]) == 0) {
        i += 5;
        list[lex_index].type = constsym;
        list[lex_index].value = 1;
        lex_index++;
        i -= 1;
        continue;
      }

      // var check
      else if (input[i] == 'v' && input[i + 1] == 'a' && input[i + 2] == 'r' && isalpha(input[i + 3]) == 0) {
        i += 3;
        list[lex_index].type = varsym;
        list[lex_index].value = 2;
        lex_index++;
        i -= 1;
        continue;
      }

      // procedure check
      else if (input[i] == 'p' && input[i + 1] == 'r' && input[i + 2] == 'o'
      && input[i + 3] == 'c' && input[i + 4] == 'e' && input[i + 5] == 'd' && 
      input[i + 6] == 'u' && input[i + 7] == 'r' && input[i + 8] == 'e' && isalpha(input[i + 9]) == 0) {
        i += 9;
        list[lex_index].type = procsym;
        list[lex_index].value = 3;
        lex_index++;
        i -= 1;
        continue;
      }

      // begin check
      else if (input[i] == 'b' && input[i + 1] == 'e' && input[i + 2] == 'g' && input[i + 3] == 'i' && input[i + 4] == 'n' && isalpha(input[i + 5]) == 0) {
        i += 5;
        list[lex_index].type = beginsym;
        list[lex_index].value = 4;
        lex_index++;
        i -= 1;
        continue;
      }

      // end check
      else if (input[i] == 'e' && input[i + 1] == 'n' && input[i + 2] == 'd' && isalpha(input[i + 3]) == 0) {
        i += 3;
        list[lex_index].type = endsym;
        list[lex_index].value = 5;
        lex_index++;
        i -= 1;
        continue;
      }

      // while check
      else if (input[i] == 'w' && input[i + 1] == 'h' && input[i + 2] == 'i' && input[i + 3] == 'l' && input[i + 4] == 'e' && isalpha(input[i + 5]) == 0) {
        i += 5;
        list[lex_index].type = whilesym;
        list[lex_index].value = 6;
        lex_index++;
        i -= 1;
        continue;
      }

      // do check
      else if (input[i] == 'd' && input[i + 1] == 'o' && isalpha(input[i + 2]) == 0) {
        i += 2;
        list[lex_index].type = dosym;
        list[lex_index].value = 7;
        lex_index++;
        i -= 1;
        continue;
      }

      // if check
      else if (input[i] == 'i' && input[i + 1] == 'f' && isalpha(input[i + 2]) == 0) {
        i += 2;
        list[lex_index].type = ifsym;
        list[lex_index].value = 8;
        lex_index++;
        i -= 1;
        continue;
      }

      // then check
      else if (input[i] == 't' && input[i + 1] == 'h' && input[i + 2] == 'e' && input[i + 3] == 'n' && isalpha(input[i + 4]) == 0) {
        i += 4;
        list[lex_index].type = thensym;
        list[lex_index].value = 9;
        lex_index++;
        i -= 1;
        continue;
      }

      // else check
      else if (input[i] == 'e' && input[i + 1] == 'l' && input[i + 2] == 's' && input[i + 3] == 'e' && isalpha(input[i + 4]) == 0) {
        i += 4;
        list[lex_index].type = elsesym;
        list[lex_index].value = 10;
        lex_index++;
        i -= 1;
        continue;
      }

      // call check
      else if (input[i] == 'c' && input[i + 1] == 'a' && input[i + 2] == 'l' && input[i + 3] == 'l' && isalpha(input[i + 4]) == 0) {
        i += 4;
        list[lex_index].type = callsym;
        list[lex_index].value = 11;
        lex_index++;
        i -= 1;
        continue;
      }

      // write check
      else if (input[i] == 'w' && input[i + 1] == 'r' && input[i + 2] == 'i' && input[i + 3] == 't' && input[i + 4] == 'e' && isalpha(input[i + 5]) == 0) {
        i += 5;
        list[lex_index].type = writesym;
        list[lex_index].value = 12;
        lex_index++;
        i -= 1;
        continue;
      }

      // read check
      else if (input[i] == 'r' && input[i + 1] == 'e' && input[i + 2] == 'a' && input[i + 3] == 'd' && isalpha(input[i + 4]) == 0) {
        i += 4;
        list[lex_index].type = readsym;
        list[lex_index].value = 13;
        lex_index++;
        i -= 1;
        continue;
      }

      // odd check
      else if (input[i] == 'o' && input[i + 1] == 'd' && input[i + 2] == 'd' && isalpha(input[i + 3]) == 0) {
        i += 3;
        list[lex_index].type = oddsym;
        list[lex_index].value = 28;
        lex_index++;
        i -= 1;
        continue;
      }

      // identifier check
      else {
        temp_word[word_len] = input[i];
        i++;
        while (isalpha(input[i]) || (input[i] >= '0' && input[i] <= '9')) {
          word_len++;
          //if word goes over the max length, print appropriate error and exit
          if (word_len > MAX_IDENT_LEN) {
            error = 4;
            printlexerror(error);
            exit(0);
          }
          temp_word[word_len] = input[i];
          i++;
        }
        list[lex_index].type = identsym;
        list[lex_index].value = 14;
        strcpy(list[lex_index].name, temp_word);
        memset(temp_word, 0, strlen(temp_word));
        lex_index++;
        i -= 1;
        continue;
      }
    }

    // := symbol check
    if (input[i] == ':') {
      i++;
      if (input[i] == '=') {
        list[lex_index].type = assignsym;
        list[lex_index].value = 16;
        lex_index++;
        continue;
      }
      //if incorrect symbol, print appropriate erorr and exit
      else {
        error = 1;
        printlexerror(error);
        return NULL;
      }
    }

    // + symbol check
    if (input[i] == '+') {
        list[lex_index].type = addsym;
        list[lex_index].value = 17;
        lex_index++;
        continue;
    }

    // - symbol check
    if (input[i] == '-') {
        list[lex_index].type = subsym;
        list[lex_index].value = 18;
        lex_index++;
        continue;
    }

    // * symbol check
    if (input[i] == '*') {
        list[lex_index].type = multsym;
        list[lex_index].value = 19;
        lex_index++;
        continue;
    }

    // / symbol check
    if (input[i] == '/') {
        list[lex_index].type = divsym;
        list[lex_index].value = 20;
        lex_index++;
        continue;
    }

    // % symbol check
    if (input[i] == '%') {
        list[lex_index].type = modsym;
        list[lex_index].value = 21;
        lex_index++;
        continue;
    }

    // == symbol check
    if (input[i] == '=') {
      if (input[i + 1] == '=') {
        i++;
        list[lex_index].type = eqlsym;
        list[lex_index].value = 22;
        lex_index++;
        continue;
      }
      else {
        error = 1;
        printlexerror(error);
        return NULL;
      }
    }

    // != symbol check
    if (input[i] == '!') {
      i++;
      if (input[i] == '=') {
        list[lex_index].type = neqsym;
        list[lex_index].value = 23;
        lex_index++;
        continue;
      }
      //if incorrect symbol, print appropriate error and exit
      else {
        error = 1;
        printlexerror(error);
        return NULL;
      }
    }

    // < and <= symbol check
    if (input[i] == '<') {
      i++;
      if (input[i] == '=') {
        list[lex_index].type = leqsym;
        list[lex_index].value = 25;
        lex_index++;
        continue;
      }
      else {
        list[lex_index].type = lsssym;
        list[lex_index].value = 24;
        lex_index++;
        continue;
      }
    }

    // > and >= symbol check
    if (input[i] == '>') {
      i++;
      if (input[i] == '=') {
        list[lex_index].type = geqsym;
        list[lex_index].value = 27;
        lex_index++;
        continue;
      }
      else {
        list[lex_index].type = gtrsym;
        list[lex_index].value = 26;
        lex_index++;
        continue;
      }
    }

    // ( symbol check
    if (input[i] == '(') {
        list[lex_index].type = lparensym;
        list[lex_index].value = 29;
        lex_index++;
        continue;
    }

    // ) symbol check
    if (input[i] == ')') {
        list[lex_index].type = rparensym;
        list[lex_index].value = 30;
        lex_index++;
        continue;
    }

    // , symbol check
    if (input[i] == ',') {
        list[lex_index].type = commasym;
        list[lex_index].value = 31;
        lex_index++;
        continue;
    }

    // . symbol check
    if (input[i] == '.') {
        list[lex_index].type = periodsym;
        list[lex_index].value = 32;
        lex_index++;
        continue;
    }

    // ; symbol check
    if (input[i] == ';') {
        list[lex_index].type = semicolonsym;
        list[lex_index].value = 33;
        lex_index++;
        continue;
    }

    // number check
    if (input[i] >= '0' && input[i] <= '9') {
      temp_num[num_len] = input[i];
      i++;
      while (input[i] >= '0' && input[i] <= '9') {
        num_len++;
        //if number is longer than max length, print appropraite error and exit
        if (num_len > MAX_NUMBER_LEN) {
          error = 3;
          printlexerror(error);
          return NULL;
        }
        if (isalpha(input[i + 1])) {
          error = 2;
          printlexerror(error);
          return NULL;
        }
        temp_num[num_len] = input[i];
        i++;
      }
      list[lex_index].type = numbersym;
      list[lex_index].value = atoi(temp_num);
      strcpy(list[lex_index].name, temp_num);
      memset(temp_num, 0, strlen(temp_num));
      lex_index++;
      i -= 1;
      continue;
    }

    
  }

  //Won't work when I pass printtokens(); for some reason
  //It segfaults, but this is the exact same code in the print function?
  //***************************************************

  printf("Lexeme Table:\n");
	printf("lexeme\t\ttoken type\n");
	for (i = 0; i < lex_index; i++)
	{
		switch (list[i].type)
		{
			case oddsym:
				printf("%11s\t%d", "odd", oddsym);
				break;
			case eqlsym:
				printf("%11s\t%d", "==", eqlsym);
				break;
			case neqsym:
				printf("%11s\t%d", "!=", neqsym);
				break;
			case lsssym:
				printf("%11s\t%d", "<", lsssym);
				break;
			case leqsym:
				printf("%11s\t%d", "<=", leqsym);
				break;
			case gtrsym:
				printf("%11s\t%d", ">", gtrsym);
				break;
			case geqsym:
				printf("%11s\t%d", ">=", geqsym);
				break;
			case modsym:
				printf("%11s\t%d", "%", modsym);
				break;
			case multsym:
				printf("%11s\t%d", "*", multsym);
				break;
			case divsym:
				printf("%11s\t%d", "/", divsym);
				break;
			case addsym:
				printf("%11s\t%d", "+", addsym);
				break;
			case subsym:
				printf("%11s\t%d", "-", subsym);
				break;
			case lparensym:
				printf("%11s\t%d", "(", lparensym);
				break;
			case rparensym:
				printf("%11s\t%d", ")", rparensym);
				break;
			case commasym:
				printf("%11s\t%d", ",", commasym);
				break;
			case periodsym:
				printf("%11s\t%d", ".", periodsym);
				break;
			case semicolonsym:
				printf("%11s\t%d", ";", semicolonsym);
				break;
			case assignsym:
				printf("%11s\t%d", ":=", assignsym);
				break;
			case beginsym:
				printf("%11s\t%d", "begin", beginsym);
				break;
			case endsym:
				printf("%11s\t%d", "end", endsym);
				break;
			case ifsym:
				printf("%11s\t%d", "if", ifsym);
				break;
			case thensym:
				printf("%11s\t%d", "then", thensym);
				break;
			case elsesym:
				printf("%11s\t%d", "else", elsesym);
				break;
			case whilesym:
				printf("%11s\t%d", "while", whilesym);
				break;
			case dosym:
				printf("%11s\t%d", "do", dosym);
				break;
			case callsym:
				printf("%11s\t%d", "call", callsym);
				break;
			case writesym:
				printf("%11s\t%d", "write", writesym);
				break;
			case readsym:
				printf("%11s\t%d", "read", readsym);
				break;
			case constsym:
				printf("%11s\t%d", "const", constsym);
				break;
			case varsym:
				printf("%11s\t%d", "var", varsym);
				break;
			case procsym:
				printf("%11s\t%d", "procedure", procsym);
				break;
			case identsym:
				printf("%11s\t%d", list[i].name, identsym);
				break;
			case numbersym:
				printf("%11d\t%d", list[i].value, numbersym);
				break;
		}
		printf("\n");
	}
  
	printf("\n");
	printf("Token List:\n");

	for (i = 0; i < lex_index; i++)
	{
		if (list[i].type == numbersym)
			printf("%d %d ", numbersym, list[i].value);
		else if (list[i].type == identsym)
			printf("%d %s ", identsym, list[i].name);
		else
			printf("%d ", list[i].type);
	}
	printf("\n");
	list[lex_index++].type = -1;

  //***************************************************
  
  //Segfaults
  //printtokens();

	return NULL;
}


/*void printtokens()
{
	int i;
	printf("Lexeme Table:\n");
	printf("lexeme\t\ttoken type\n");
  printf("%d", lex_index);
	for (i = 0; i < lex_index; i++)
	{
		switch (list[i].type)
		{
			case oddsym:
				printf("%11s\t%d", "odd", oddsym);
				break;
			case eqlsym:
				printf("%11s\t%d", "==", eqlsym);
				break;
			case neqsym:
				printf("%11s\t%d", "!=", neqsym);
				break;
			case lsssym:
				printf("%11s\t%d", "<", lsssym);
				break;
			case leqsym:
				printf("%11s\t%d", "<=", leqsym);
				break;
			case gtrsym:
				printf("%11s\t%d", ">", gtrsym);
				break;
			case geqsym:
				printf("%11s\t%d", ">=", geqsym);
				break;
			case modsym:
				printf("%11s\t%d", "%", modsym);
				break;
			case multsym:
				printf("%11s\t%d", "*", multsym);
				break;
			case divsym:
				printf("%11s\t%d", "/", divsym);
				break;
			case addsym:
				printf("%11s\t%d", "+", addsym);
				break;
			case subsym:
				printf("%11s\t%d", "-", subsym);
				break;
			case lparensym:
				printf("%11s\t%d", "(", lparensym);
				break;
			case rparensym:
				printf("%11s\t%d", ")", rparensym);
				break;
			case commasym:
				printf("%11s\t%d", ",", commasym);
				break;
			case periodsym:
				printf("%11s\t%d", ".", periodsym);
				break;
			case semicolonsym:
				printf("%11s\t%d", ";", semicolonsym);
				break;
			case assignsym:
				printf("%11s\t%d", ":=", assignsym);
				break;
			case beginsym:
				printf("%11s\t%d", "begin", beginsym);
				break;
			case endsym:
				printf("%11s\t%d", "end", endsym);
				break;
			case ifsym:
				printf("%11s\t%d", "if", ifsym);
				break;
			case thensym:
				printf("%11s\t%d", "then", thensym);
				break;
			case elsesym:
				printf("%11s\t%d", "else", elsesym);
				break;
			case whilesym:
				printf("%11s\t%d", "while", whilesym);
				break;
			case dosym:
				printf("%11s\t%d", "do", dosym);
				break;
			case callsym:
				printf("%11s\t%d", "call", callsym);
				break;
			case writesym:
				printf("%11s\t%d", "write", writesym);
				break;
			case readsym:
				printf("%11s\t%d", "read", readsym);
				break;
			case constsym:
				printf("%11s\t%d", "const", constsym);
				break;
			case varsym:
				printf("%11s\t%d", "var", varsym);
				break;
			case procsym:
				printf("%11s\t%d", "procedure", procsym);
				break;
			case identsym:
				printf("%11s\t%d", list[i].name, identsym);
				break;
			case numbersym:
				printf("%11d\t%d", list[i].value, numbersym);
				break;
		}
		printf("\n");
	}
  
	printf("\n");
	printf("Token List:\n");

	for (i = 0; i < lex_index; i++)
	{
		if (list[i].type == numbersym)
			printf("%d %d ", numbersym, list[i].value);
		else if (list[i].type == identsym)
			printf("%d %s ", identsym, list[i].name);
		else
			printf("%d ", list[i].type);
	}
	printf("\n");
	list[lex_index++].type = -1;
}*/

void printlexerror(int type)
{
	if (type == 1)
		printf("Lexical Analyzer Error: Invalid Symbol\n");
	else if (type == 2)
		printf("Lexical Analyzer Error: Invalid Identifier\n");
	else if (type == 3)
		printf("Lexical Analyzer Error: Excessive Number Length\n");
	else if (type == 4)
		printf("Lexical Analyzer Error: Excessive Identifier Length\n");
	else
		printf("Implementation Error: Unrecognized Error Type\n");
	
	free(list);
	return;
}