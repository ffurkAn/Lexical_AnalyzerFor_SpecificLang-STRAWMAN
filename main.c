#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

#define ASSIGN 1
#define TRIM 2
#define CONCAT 3
#define REPLACE 4
#define IDENT 5
#define STRING 6
#define EOL 9
#define LETTER 10
#define DIGIT 11
#define BLANK 12
#define TRUNCAT 13
#define SEMICOLON 14
#define READ 15
#define WRITE 16
#define LEFTPH 17
#define RIGHTPH 18
#define FROM 19
#define TO 20
#define COMMENT 35
#define UNKNOWN 99
#define typeMAX 20
#define nameMAX 100
#define EOF -1

struct Terminal {
      char name [nameMAX];
      char type [typeMAX];
      char value [nameMAX];
      int charClass;
      int row;
      int col;
      struct Terminal *sonraki;

} typedef TERMINAL;

void getChar();
void skipBlank();
void addToList(TERMINAL **, TERMINAL *);
void printList(TERMINAL *);
void printVariables(TERMINAL *);
void lex();
void assignment();
void interpret();
void concat();
void trim();
void read();
void write();
void strCopy(char [], char []);
void arrayShifter(int);
void updateVariables(TERMINAL *, TERMINAL *);
TERMINAL* getNext(TERMINAL *);

int charClass ;
int glRow = 1;
int glCol = 0;
char nextChar ;
char prevChar;
int identLen = 0;
int errorCounter = 0;
char string[nameMAX];

FILE *file, *fopen();
TERMINAL *linkedList = NULL;
TERMINAL *onceki;
TERMINAL *sonraki;
TERMINAL *variable;

int main()
{
    if ((file = fopen("sourcecode.stw", "r")) == NULL)
      printf("(ERROR !) File <sourcecode.stw> could not be opened properly.\n");
    else
    {
      getChar();

      do
      {
         lex();
      }while (charClass!= EOF);

      fclose(file);

      if (errorCounter == 0)
      {
            printList(linkedList);
            sonraki = linkedList;
            onceki = sonraki;
            while(sonraki != NULL)
            {
                  interpret();
                  if (sonraki->charClass == EOL && sonraki->sonraki != NULL)
                  {
                      if (sonraki->sonraki->charClass != IDENT && sonraki->sonraki->charClass != READ && sonraki->sonraki->charClass != WRITE)
                      {
                          printf("#ERROR! expected identifier or command on %d line, %d column \n", sonraki->row, sonraki->col);
                          errorCounter++;
                          break;
                      }
                  }
                  sonraki = getNext(sonraki);
            }

            if (errorCounter == 0)
                  printVariables(linkedList);
            else
                  printf("\n\n\t%d error(s) found\n", errorCounter);
      }
      else
            printf("\n\n\t%d error(s) found\n", errorCounter);

    }
    system("pause");
    return 0;
}

void lex ()
{
      int row = 0;
      int col = 0;

      TERMINAL *terminal;

      int index = 0;
      terminal = malloc(sizeof(TERMINAL));
      skipBlank();


      switch (charClass)
      {

            case DIGIT :
                  charClass = UNKNOWN;
                  break;

            case LETTER :

                  row = glRow;
                  col = glCol-1;
                  terminal->name[index]=nextChar;
                  index++;
                  getChar();

                        while (charClass == LETTER || charClass == DIGIT)
                        {
                              if (index > (19))
                              {
                                    printf("\n(ERROR !) IDENTIFIER cannot be longer than 20 characters , on %d line , %d column ! ", row,col);
                                    errorCounter++;
                                    break;
                              }
                              terminal->name[index]=nextChar;
                              index++;
                              getChar();

                              if(index==4)
                              {
                                    if(terminal->name[0] == 'R' && terminal->name[1] == 'E' && terminal->name[2] == 'A' && terminal->name[3] == 'D' && nextChar == ' ' )
                                    {
                                          charClass=READ;
                                          terminal->name[0] = 'R';
                                          terminal->name[1] = 'E';
                                          terminal->name[2] = 'A';
                                          terminal->name[3] = 'D';
                                          terminal->name[4] = '\0';
                                          terminal->type[0] = 'R';
                                          terminal->type[1] = 'E';
                                          terminal->type[2] = 'A';
                                          terminal->type[3] = 'D';
                                          terminal->type[4] = 'C';
                                          terminal->type[5] = 'O';
                                          terminal->type[6] = 'M';
                                          terminal->type[7] = 'D';
                                          terminal->type[8] = '\0';
                                          terminal->row=glRow;
                                          terminal->col=glCol;
                                          terminal->charClass=READ;
                                          addToList(&linkedList, terminal);

                                          break;
                                     }
                              }

                              if(terminal->name[0] == 'W' && terminal->name[1] == 'R' && terminal->name[2] == 'I' && terminal->name[3] == 'T' && terminal->name[4]=='E' && nextChar == ' ' )
                              {
                                          charClass=WRITE;

                                          terminal->name[0] = 'W';
                                          terminal->name[1] = 'R';
                                          terminal->name[2] = 'I';
                                          terminal->name[3] = 'T';
                                          terminal->name[4] = 'E';
                                          terminal->name[5] = '\0';
                                          terminal->type[0] = 'W';
                                          terminal->type[1] = 'R';
                                          terminal->type[2] = 'I';
                                          terminal->type[3] = 'T';
                                          terminal->type[4] = 'E';
                                          terminal->type[5] = 'C';
                                          terminal->type[6] = 'M';
                                          terminal->type[7] = 'D';
                                          terminal->type[8] = '\0';
                                          terminal->row=glRow;
                                          terminal->col=glCol;
                                          terminal->charClass=WRITE;
                                          addToList(&linkedList, terminal);

                                          break;
                        }

                        if(terminal->name[0] == 'F' && terminal->name[1] == 'R' && terminal->name[2] == 'O' && terminal->name[3] == 'M' && nextChar == ' ' )
                        {
                                          charClass=READ;

                                          terminal->name[0] = 'F';
                                          terminal->name[1] = 'R';
                                          terminal->name[2] = 'O';
                                          terminal->name[3] = 'M';
                                          terminal->name[4] = '\0';
                                          terminal->type[0] = 'r';
                                          terminal->type[1] = 'e';
                                          terminal->type[2] = 'a';
                                          terminal->type[3] = 'd';
                                          terminal->type[4] = 'K';
                                          terminal->type[5] = 'E';
                                          terminal->type[6] = 'Y';
                                          terminal->type[7] = 'W';
                                          terminal->type[8] = '\0';
                                          terminal->row=glRow;
                                          terminal->col=glCol;
                                          terminal->charClass=FROM;
                                          addToList(&linkedList, terminal);

                                          break;
                        }

                        if(terminal->name[0] == 'T' && terminal->name[1] == 'O' && nextChar == ' ' )
                        {
                                          charClass=WRITE;

                                          terminal->name[0] = 'T';
                                          terminal->name[1] = 'O';
                                          terminal->name[2] = '\0';
                                          terminal->type[0] = 'w';
                                          terminal->type[1] = 'r';
                                          terminal->type[2] = 'i';
                                          terminal->type[3] = 't';
                                          terminal->type[4] = 'e';
                                          terminal->type[5] = 'K';
                                          terminal->type[6] = 'E';
                                          terminal->type[7] = 'Y';
                                          terminal->type[8] = 'W';
                                          terminal->type[9] = '\0';
                                          terminal->row=glRow;
                                          terminal->col=glCol;
                                          terminal->charClass=TO;
                                          addToList(&linkedList, terminal);

                                          break;
                        }
                  }

                  if(charClass != READ && charClass != WRITE)
                  {
                        terminal->name[index] = '\0';

                        terminal->type[0] = 'I';
                        terminal->type[1] = 'D';
                        terminal->type[2] = 'E';
                        terminal->type[3] = 'N';
                        terminal->type[4] = 'T';
                        terminal->type[5] = 'I';
                        terminal->type[6] = 'F';
                        terminal->type[7] = 'I';
                        terminal->type[8] = 'E';
                        terminal->type[9] = 'R';
                        terminal->type[10] = '\0';
                        terminal->row=glRow;
                        terminal->col=glCol;
                        terminal->charClass=IDENT;

                        addToList(&linkedList, terminal);
                  }

                  break;

            case ASSIGN :

                  terminal->name[0] = ':';
                  terminal->name[1] = '=';
                  terminal->name[2] = '\0';
                  terminal->type[0] = 'A';
                  terminal->type[1] = 'S';
                  terminal->type[2] = 'S';
                  terminal->type[3] = 'I';
                  terminal->type[4] = 'G';
                  terminal->type[5] = 'N';
                  terminal->type[6] = 'M';
                  terminal->type[7] = 'E';
                  terminal->type[8] = 'N';
                  terminal->type[9] = 'T';
                  terminal->type[10] = '\0';
                  terminal->row=glRow;
                  terminal->col=glCol;
                  terminal->charClass=ASSIGN;
                  addToList(&linkedList, terminal);

                  getChar();
                  break;

            case STRING :

                  terminal->row=glRow;
                  terminal->col=glCol;

                   getChar();

                   while (nextChar != '"' && nextChar != EOF)
                   {
                         if(nextChar== '\n')
                         {
                              glCol=1;
                              glRow++;
                         }
                         terminal->name[index]=nextChar;
                         terminal->value[index]=nextChar;
                         index++;
                         glCol++;

                         nextChar = getc(file);
                   }

                         if (nextChar == EOF)
                         {
                              printf("\n(ERROR !) non-terminated string constant '%c' , on %d line , %d column ! ",'"',terminal->row,terminal->col);
                              errorCounter++;
                         }

                         else
                         {
                               terminal->name[index]= '\0';
                               terminal->value[index] = '\0';
                               terminal->type[0]='S';
                               terminal->type[1]='T';
                               terminal->type[2]='R';
                               terminal->type[3]='I';
                               terminal->type[4]='N';
                               terminal->type[5]='G';
                               terminal->type[6]='\0';
                               terminal->charClass=STRING;

                               addToList(&linkedList, terminal);

                         }

                   getChar();
                   break;

            case SEMICOLON :

                  getChar();
                  if (nextChar=='=')
                  {
                        charClass=ASSIGN;
                        break;
                  }
                  else if (nextChar=='/')
                  {
                        charClass=TRUNCAT;
                        break;
                  }
                  else
                  {
                        skipBlank();

                        terminal->name[0] = ':';
                        terminal->name[1] = '\0';
                        terminal->type[0] = 'R';
                        terminal->type[1] = 'E';
                        terminal->type[2] = 'P';
                        terminal->type[3] = 'O';
                        terminal->type[4] = 'P';
                        terminal->type[5] = 'C';
                        terminal->type[6] = 'O';
                        terminal->type[7] = 'L';
                        terminal->type[8] = '\0';
                        terminal->row=glRow;
                        terminal->col=glCol;
                        terminal->charClass=REPLACE;
                        addToList(&linkedList, terminal);

                        break;
                  }

                  getChar();
                  break;

            case REPLACE :

                  getChar();
                  if(nextChar=='"')
                        charClass=STRING;

                  terminal->name[0] = '<';
                  terminal->name[1] = '\0';
                  terminal->type[0] = 'R';
                  terminal->type[1] = 'E';
                  terminal->type[2] = 'P';
                  terminal->type[3] = 'L';
                  terminal->type[4] = 'A';
                  terminal->type[5] = 'C';
                  terminal->type[6] = 'E';
                  terminal->type[7] = 'M';
                  terminal->type[8] = 'E';
                  terminal->type[9] = 'N';
                  terminal->type[10] = 'T';
                  terminal->type[11] = '\0';

                  terminal->row=glRow;
                  terminal->col=glCol;
                  terminal->charClass=REPLACE;
                  addToList(&linkedList, terminal);

                  break;

            case CONCAT :

                  getChar();
                  if(nextChar=='"')
                        charClass=STRING;
                  if(isalpha(nextChar))
                         charClass=LETTER;

                  terminal->name[0] = '+';
                  terminal->name[1] = '\0';
                  terminal->type[0] = 'C';
                  terminal->type[1] = 'O';
                  terminal->type[2] = 'N';
                  terminal->type[3] = 'C';
                  terminal->type[4] = 'A';
                  terminal->type[5] = 'T';
                  terminal->type[6] = 'E';
                  terminal->type[7] = 'N';
                  terminal->type[8] = 'A';
                  terminal->type[9] = 'T';
                  terminal->type[10] = 'I';
                  terminal->type[11] = 'O';
                  terminal->type[12] = 'N';
                  terminal->type[13] = '\0';
                  terminal->row=glRow;
                  terminal->col=glCol;
                  terminal->charClass=CONCAT;

                  addToList(&linkedList, terminal);

                  break;

            case TRIM :

                  getChar();
                  if(nextChar=='"')
                  {
                        charClass=STRING;

                  }
                  else if (nextChar=='*')
                  {
                        charClass=COMMENT;
                        break;
                  }

                  terminal->name[0] = '/';
                  terminal->name[1] = '\0';
                  terminal->type[0] = 'T';
                  terminal->type[1] = 'R';
                  terminal->type[2] = 'I';
                  terminal->type[3] = 'M';
                  terminal->type[4] = 'M';
                  terminal->type[5] = 'I';
                  terminal->type[6] = 'N';
                  terminal->type[7] = 'G';
                  terminal->type[8] = '\0';
                  terminal->row=glRow;
                  terminal->col=glCol;
                  terminal->charClass=TRIM;
                  addToList(&linkedList, terminal);

                  break;

            case COMMENT :

                  row=glRow;
                  col=glCol;
                  while (nextChar != EOF)
                  {
                        if(nextChar== '\n')
                        {
                              glCol=1;
                              glRow++;
                        }
                        nextChar=getc(file);
                        if ( nextChar== '*'  )
                        {
                              nextChar=getc(file);
                              if(nextChar == '/' )
                              {
                                    getChar();
                                    break;
                              }
                        }

                  }
                  if (nextChar == EOF)
                  {
                        printf("\n(ERROR !) non-terminated comment , on %d line; %d column ! ", row,col);
                        errorCounter++;
                        charClass = EOF;
                  }

                  break;

            case LEFTPH :

                  getChar();
                  if(nextChar=='"')
                        charClass=STRING;
                  else if(isalpha(nextChar))
                        charClass=LETTER;

                  terminal->name[0] = '(';
                  terminal->name[1] = '\0';
                  terminal->type[0] = 'l';
                  terminal->type[1] = 'e';
                  terminal->type[2] = 'f';
                  terminal->type[3] = 't';
                  terminal->type[4] = 'P';
                  terminal->type[5] = 'A';
                  terminal->type[6] = 'R';
                  terminal->type[7] = 'A';
                  terminal->type[8] = 'N';
                  terminal->type[9] = 'T';
                  terminal->type[10] = '\0';
                  terminal->row=glRow;
                  terminal->col=glCol;
                  terminal->charClass=LEFTPH;
                  addToList(&linkedList, terminal);

                  break;

            case RIGHTPH :

                  getChar();
                  if(nextChar=='"')
                        charClass=STRING;
                  else if(isalpha(nextChar))
                        charClass=LETTER;

                  terminal->name[0] = ')';
                  terminal->name[1] = '\0';
                  terminal->type[0] = 'r';
                  terminal->type[1] = 'i';
                  terminal->type[2] = 'g';
                  terminal->type[3] = 'h';
                  terminal->type[4] = 't';
                  terminal->type[5] = 'P';
                  terminal->type[6] = 'A';
                  terminal->type[7] = 'R';
                  terminal->type[8] = 'A';
                  terminal->type[9] = 'N';
                  terminal->type[10] = 'T';
                  terminal->type[11] = '\0';
                  terminal->row=glRow;
                  terminal->col=glCol;
                  terminal->charClass=RIGHTPH;
                  addToList(&linkedList, terminal);

                  break;

            case TRUNCAT :

                  getChar();
                  if(nextChar=='"')
                        charClass=STRING;

                  terminal->name[0] = ':';
                  terminal->name[1] = '/';
                  terminal->name[2] = '\0';
                  terminal->type[0] = 'T';
                  terminal->type[1] = 'R';
                  terminal->type[2] = 'U';
                  terminal->type[3] = 'N';
                  terminal->type[4] = 'C';
                  terminal->type[5] = 'A';
                  terminal->type[6] = 'T';
                  terminal->type[7] = 'I';
                  terminal->type[8] = 'O';
                  terminal->type[9] = 'N';
                  terminal->type[10] = '\0';

                  terminal->row=glRow;
                  terminal->col=glCol;
                  terminal->charClass=TRUNCAT;

                  addToList(&linkedList, terminal);

                  break;

            case UNKNOWN :

                  printf("\n(ERROR !) unknown character '%c' , on %d line; %d column ! ", nextChar,glRow,glCol);
                  errorCounter++;

                  getChar();
                  break;

            case EOL :

                  terminal->name[0]=';';
                  terminal->name[1]='\0';
                  terminal->type[0]='E';
                  terminal->type[1]='O';
                  terminal->type[2]='L';
                  terminal->type[3]='\0';

                  terminal->row=glRow;
                  terminal->col=glCol;
                  terminal->charClass=EOL;

                  addToList(&linkedList, terminal);

                  getChar();
                  break;

            case EOF :

                  terminal->name[0]='E';
                  terminal->name[1]='O';
                  terminal->name[2]='F';
                  terminal->name[3]='\0';

                  terminal->row=glRow;
                  terminal->col=glCol;
                  terminal->charClass=EOF;

                  break;

      }

}

void getChar()
{
      glCol++;
      if(!isspace(nextChar))
            prevChar=nextChar;

      if ((nextChar=getc(file)) != EOF)
      {
            if (isalpha(nextChar))
            {
                  charClass = LETTER ;
            }
            else if (isdigit(nextChar))
            {
                  charClass = DIGIT ;
            }
            else if(nextChar == ':')
            {
                  charClass = SEMICOLON;
            }
            else if(nextChar == '"')
            {
                   charClass = STRING ;
            }
            else if(nextChar == '+')
            {
                   charClass = CONCAT ;
            }
            else if(nextChar == '/')
            {
                   charClass = TRIM ;
            }
            else if(nextChar == '<')
            {
                   charClass = REPLACE ;
            }
            else if(nextChar == ' ')
            {
                   charClass = BLANK ;
            }
            else if(nextChar == ';')
            {
                  charClass = EOL;
            }
            else if(nextChar == '(')
            {
                  charClass=LEFTPH;
            }
            else if(nextChar == ' ')
            {
                  charClass = BLANK;
            }
            else if(nextChar == ')')
            {
                  charClass=RIGHTPH;
            }
            else if(nextChar=='\n')
            {
                  glCol=1;
                  glRow++;
            }

            else
            {
                charClass = UNKNOWN;
            }

      }
      else
      {
            charClass = EOF ;
      }
}

void skipBlank ()
{
      while (isspace(nextChar))
      {
            getChar();
      }
}

void addToList(TERMINAL **bas, TERMINAL *yeni)
{
    TERMINAL *gecici, *onceki;

    if(*bas==NULL) //kuyruk bossa
    {
        yeni->sonraki=NULL;
        *bas=yeni;
    }
    else
    {
            onceki=*bas;
            gecici=(*bas)->sonraki;
            while((gecici!=NULL)) //eklenecek uygun yer araniyor
            {
                onceki=gecici;
                gecici=gecici->sonraki;
            }
            yeni->sonraki=gecici; //gecici NULL ise en sona, degilse onceki dugumu ile gecici dugumu arasina ekleniyor
            onceki->sonraki=yeni;
    }
}

void printList(TERMINAL *bas)
{
      TERMINAL *gecici;

      gecici=bas;
      printf("\n");
      while(gecici!=NULL)
      {
            printf("\t%s \t %s\n", gecici->name, gecici->type);

            gecici=gecici->sonraki;
      }
}

void printVariables(TERMINAL *bas)
{
      TERMINAL *gecici;

      gecici=bas;
      printf("\n");
      while(gecici!=NULL)
      {
            if (gecici->charClass == IDENT)
                  printf("\t%s \t %s\n", gecici->name, gecici->value);

            gecici=gecici->sonraki;
      }
}

void interpret()
{
      switch (sonraki->charClass)
      {
            case IDENT :
                  variable = sonraki;
                  sonraki=getNext(sonraki);
                  if (sonraki->charClass != ASSIGN && sonraki->charClass != EOL)
                  {
                        printf("#ERROR! expected assignment operator on %d line, %d column \n", sonraki->row, sonraki->col);
                        errorCounter++;
                        return;
                  }
                  else if (sonraki->sonraki->charClass != STRING && sonraki->sonraki->charClass != IDENT && sonraki->sonraki->charClass != LEFTPH)
                  {
                        printf("#ERROR! expected identifier or string constant on %d line, %d column \n", sonraki->row, sonraki->col);
                        errorCounter++;
                        return;
                  }
                  else
                  {
                        while (sonraki->charClass != EOL)
                        {
                              assignment();
                        }

                  }

                  updateVariables(linkedList, variable);

                  break;

            case READ :
                  read();
                  break;

            case WRITE :
                  write();
                  break;

      }

}

void assignment()
{
            sonraki=getNext(sonraki);
            //printf("sonraki->charClass = %d\n", sonraki->charClass);

            if (onceki->charClass == sonraki->charClass)
            {
                printf("#ERROR! expected operator on %d line, %d column \n", sonraki->row, sonraki->col);
                errorCounter++;
                return;
            }

            switch (sonraki->charClass)
            {
                  case IDENT :
                        //printf("case IDENT\n");
                        strCopy(string, sonraki->value);
                        break;

                  case STRING :
                        //printf("case STRING\n");
                        strCopy(string, sonraki->value);
                        break;

                  case TRIM :
                        //printf("case TRIM\n");
                        trim();
                        break;

                  case CONCAT :
                        //printf("case CONCAT\n");
                        concat();
                        break ;

                  case EOL :
                        //printf("case EOL\n");
                        strCopy(variable->value, string);
                        break;
            }
}

void write()
{
      variable = sonraki;
      if (sonraki->sonraki->charClass != STRING && sonraki->sonraki->charClass != IDENT && sonraki->sonraki->charClass != LEFTPH)
      {
            printf("#ERROR! expected identifier or string constant on %d line, %d column \n", sonraki->row, sonraki->col);
            errorCounter++;
            return;
      }
      else
      {
            while (sonraki->charClass != TO)
            {
                  if (sonraki->charClass == EOL)
                        break;
                  assignment();
            }

            if (sonraki->charClass == TO)
            {
                  if ((file = fopen((sonraki=getNext(sonraki))->value, "w")) == NULL)
                  {
                        printf("(ERROR !) File could not be opened properly.\n");
                        errorCounter++;
                        return;
                  }
                  else
                  {
                        printf("\nDosyaya yazma\n");
                        fprintf(file, "%s\n", string);
                        fclose(file);
                  }
            }
            else
            {
                  printf("String value: %s", string);
            }

      }

}

void read()
{
      int i = 0;
      char fileChar;
      sonraki=getNext(sonraki);
      variable = sonraki;
      if (sonraki->charClass != IDENT)
      {
            printf("#ERROR! expected identifier on %d line, %d column", sonraki->row, sonraki->col);
            errorCounter++;
            return;
      }
      else if ((sonraki=getNext(sonraki))->charClass == FROM)
      {
            if ((sonraki=getNext(sonraki))->charClass != STRING)
            {
                  printf("#ERROR! expected file name on %d line, %d column", sonraki->row, sonraki->col);
                  errorCounter++;
                  return;
            }
            else
            {
                  if ((file = fopen(sonraki->name, "r")) == NULL)
                  {
                        printf("(ERROR !) File could not be opened properly.\n");
                        errorCounter++;
                        return;
                  }
                  else
                  {
                        fileChar = getc(file);
                        while (fileChar != EOF)
                        {
                            variable->value[i] = fileChar;
                            fileChar = getc(file);
                            i++;
                        }
                  }
            }
      }
      else
      {
            printf("Enter a string value: ");
            scanf("%s", string);
            strCopy(variable->value, string);
      }
}

void trim()
{
        int trimStrLen, strIndex = 0, trimIndex = 0, isFound = 0, isDone = 0;
        sonraki=getNext(sonraki);
        trimStrLen=strlen(sonraki->value);

        while(string[strIndex] == ' ')
        {
            strIndex++;
        }
        if (strIndex > 0)
            arrayShifter(strIndex-1);

        for (strIndex=0; string[strIndex] != '\0'; strIndex++)
        {
            if (string[strIndex] == sonraki->value[trimIndex] && isDone == 0)
            {
                isFound++;
                trimIndex++;
                if (sonraki->value[trimIndex] == '\0')
                {
                    trimIndex = 0;
                    if (isFound == trimStrLen)
                    {
                        arrayShifter(strIndex);
                        strIndex = -1;
                        isFound = 0;
                    }
                }
            }
            else
            {
                isDone = 1;
                if (string[strIndex] == ' ')
                    continue;
                else
                {
                    if (strIndex > 0)
                        arrayShifter(strIndex-1);
                    break;
                }
            }
        }

        isDone = 0;
        strIndex = strlen(string) - 1;
        trimIndex = strlen(sonraki->value) - 1;
        while(string[strIndex] == ' ')
        {
            strIndex--;
        }
        if (strIndex < (strlen(string) - 1))
            string[strIndex+1] = '\0';

        for (strIndex; strIndex > 0; strIndex--)
        {
            if (string[strIndex] == sonraki->value[trimIndex] && isDone == 0)
            {
                isFound++;
                trimIndex--;
                if (trimIndex == -1)
                {
                    trimIndex = strlen(sonraki->value) - 1;
                    if (isFound == trimStrLen)
                    {
                        string[strIndex] = '\0';
                        strIndex = strlen(string);
                        isFound = 0;
                    }
                }
            }
            else
            {
                isDone = 1;
                if (string[strIndex] == ' ')
                    continue;
                else
                {
                    string[strIndex+1] = '\0';
                    break;
                }
            }
        }

}

void concat()
{
      int i, j;
      sonraki=getNext(sonraki);
      for (i=0; i<nameMAX; i++)
      {
            if (string[i] == '\0')
            {
                  for (j=0; sonraki->value[j] != '\0'; string[i] = sonraki->value[j], i++, j++);
                        break;
            }
      }

      for (i=i+j; i<nameMAX; i++)
            string[i] = '\0';
}

void arrayShifter(int strIndex)
{
    int i;

    for (i=0; string[strIndex] != '\0'; i++)
    {
        string[i] = string[strIndex+1];
        strIndex++;
    }
    for (i=strIndex; i<nameMAX; i++)
    {
        string[i] = '\0';
    }
}

void updateVariables(TERMINAL *bas, TERMINAL *t)
{
      TERMINAL *gecici;

      gecici=bas;
      while(gecici!=NULL)
      {
            if (gecici->charClass == IDENT)
            {
                  if (strcmp(gecici->name, t->name) == 0)
                  {
                        strCopy(gecici->value, t->value);
                  }
            }

            gecici=gecici->sonraki;
      }
}

TERMINAL* getNext(TERMINAL *simdiki)
{
      onceki = simdiki;
      return simdiki->sonraki;
}

void strCopy(char degisicek [], char kopyalancak[])
{
      int i,j;
      for (i=0; kopyalancak[i] != '\0'; degisicek[i] = kopyalancak[i], i++);
      for (j=i; j<nameMAX; degisicek[j]='\0', j++);
}
