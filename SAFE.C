#include "skeleton.c"
#include "safe_fcns.h"
#include "takutil.c"

char temps[81],scramble[6],code[6];
int tempi,done;

void main(int argc, char *argv[])
{

  FILE *fptr;
  char s[81],safe_name[30];

  if (argc<2)
    strcpy(s,"chain.txt");
  else
    strcpy(s,argv[1]);

  if (read_in_data(s)==-1) {
    printf("\nUnable to find CHAIN.TXT\n\n");
    exit(0);
  }

  outchr(12);
  pl("Safecracker v1.0 ALPHA");
  pl("By The Archaic Knight");

  outstr("Instructions [y/N]? ");
  if (yn()) {
    printfile("safe.doc");
    pausescr();
  }

  fptr=fopen("SAFE.DAT","r");
  fgets(safe_name,30,fptr);
  fgets(code,5,fptr);
  fgets(scramble,5,fptr);
  fclose(fptr);
  nl();
  safe_name[(strlen(safe_name)-1)] = '\0';
  code[(strlen(safe_name)-1)] = '\0';
  scramble[(strlen(safe_name)-1)] = '\0';
  sprintf(temps,"The current Safe Cracker Champion is %s!",safe_name);
  pl(temps);
  tempi = 1;
  done = 0;
  do {
    sprintf(temps,"Unscramble This: %s",scramble);
    pl(temps);
    sprintf(temps,"Try #%d        : ",tempi);
    outstr(temps);
    input(temps,4);
    if(strcmp(temps,code) == 0)
      done = 1;
    ++tempi;
  } while ((tempi < 4) && (!done));
  if (done) {
    nl();
    pl("Congratulations!  You cracked the safe!");
    nl();
    pl("You get 2,500 gold!");
    gold += 2500;
    nl();
    outstr("Enter new combination: ");
    input(code,4);
    scramble_code();
    nl();
    sprintf(temps,"Scramble code is: %s",scramble);
    pl(temps);
    fptr=fopen("SAFE.DAT","w");
    fputs(name,fptr);
    fputs(code,fptr);
    fputs(scramble,fptr);
    fclose(fptr);
  }
  else {
    nl();
    pl("Sorry, the safe remains closed...");
  }
}

void scramble_code()
{
  int count,used[4] = {0,0,0,0};

  randomize();
  count = 1;
  tempi = (random(4)+1);
  strcpy(temps,&code[tempi]);
  used[tempi] = 1;
  do {
    do {
      tempi = (random(4)+1);
    } while (used[tempi] != 1);
    strcat(temps,&code[tempi]);
    used[tempi] = 1;
    ++count;
  } while (count < 3);
  strcpy(scramble, temps);
}
