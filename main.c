#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ASSIGN 1
#define TRIM 2
#define CONCAT 3
#define REPLACE 4
#define IDENT 5
#define STRING 6
#define LEFTP 7
#define RIGHTP 8
#define EOL 9
#define LETTER 10
#define DIGIT 11
#define BLANK 12
#define TRUNCAT 13
#define SEMICOLON 14
#define READ 15
#define WRITE 16
#define UNKNOWN 99
#define MAX 50
#define EOF -1

struct Terminal {
      char name [MAX];
      char type [MAX];
      int row ;
      int col ;
      int level ;
      struct Terminal *sonraki;

} typedef TERMINAL;

void getChar();
void skipBlank();
void addToList(TERMINAL **, TERMINAL *);
void printList(TERMINAL *);
void lex();

int charClass ;
int glRow =1;
int glCol =0;
char nextChar ;
char prevChar;
char tempChar;
int nextToken ;
FILE *file, *fopen() ;
TERMINAL *linkedList = NULL;

int main()
{

    if ((file = fopen("sourcecode.txt", "r")) == NULL)
      printf("Dosya acilamadi..");
    else
    {
      getChar();
      do
      {
         lex();
      }while (charClass!= EOF);

      printList(linkedList);
    }
    return 0;
}

void lex ()
{

      TERMINAL *terminal;

      int index = 0;
      terminal = malloc(sizeof(TERMINAL));
      skipBlank();


      switch (charClass)
      {
            case LETTER :

                  terminal->name[index]=nextChar;
                  index++;
                  getChar();
                  while (charClass == LETTER || charClass == DIGIT)
                  {

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
                                    addToList(&linkedList, terminal);

                                       break;
                  }

                  if(terminal->name[0] == 'F' && terminal->name[1] == 'R' && terminal->name[2] == 'O' && terminal->name[3] == 'M' && nextChar == ' ' )
                               {
                                   charClass=WRITE;

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
                  addToList(&linkedList, terminal);

                  getChar();
                  break;

            case STRING :

                   getChar();
                   while (nextChar != '"' && nextChar != EOF)
                   {
                         terminal->name[index]=nextChar;
                         index++;
                         //getChar();
                         nextChar = getc(file);
                   }
                   if (nextChar == EOF)
                    printf("tirnagi kapatmadin");


                   else
                   {
                         terminal->name[index] = '\0';
                         terminal->type[0]='S';
                         terminal->type[1]='T';
                         terminal->type[2]='R';
                         terminal->type[3]='I';
                         terminal->type[4]='N';
                         terminal->type[5]='G';
                         terminal->type[6]='\0';
                         terminal->row=glRow;
                         terminal->col=glCol;

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
                        charClass=STRING;

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
                        addToList(&linkedList, terminal);

                        break;
                  }
                  if (nextChar != '"')
                        printf("(ERROR !) expected character '%c' , on %d line; %d column ! ",'"',glRow,glCol);

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

                  addToList(&linkedList, terminal);

                  break;

            case TRIM :

                  getChar();
                  if(nextChar=='"')
                        charClass=STRING;

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

                  addToList(&linkedList, terminal);

                  break;

                  /*case READ :

                  terminal->name[0] = 's';
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
                  addToList(&linkedList, terminal);

                  break;*/

            case EOL :

                  terminal->name[0]=';';
                  terminal->name[1]='\0';
                  terminal->type[0]='E';
                  terminal->type[1]='O';
                  terminal->type[2]='L';
                  terminal->type[3]='\0';
                  addToList(&linkedList, terminal);

                  getChar();
                  break;

            case EOF :

                  terminal->name[0]='E';
                  terminal->name[1]='O';
                  terminal->name[2]='F';
                  terminal->name[3]='\0';

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
            else if(nextChar=='\n')
                  {
                        glCol=1;
                        glRow++;
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

void addToList(TERMINAL **bas,TERMINAL *yeni)
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
      while((gecici!=NULL))
      {
            printf("\t%s \t %s\n", gecici->name, gecici->type);

            gecici=gecici->sonraki;
      }
}
