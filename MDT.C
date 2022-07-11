#include <io.h>
#include <stdio.h>
#include "menufil.h"
#include "tabela.h"

extern char mat[400][13],
            tabmdt[63],
            tabband[29],
            tabdband1[29];
extern int  posi,
	    tab,
	    px,
            arq1;
FILE *fopen(), *arq2;
mdt(int pos)
{
extern char mat1[70];

/*union REGS regs;*/
char *buf,letra='';

 file(pos);

/* regs.h.ah=0;
 regs.h.al=231;
 regs.x.dx=1;
 int86(0x14,&regs,&regs);*/

 if((arq2=fopen("8600","wb"))==NULL) { gotoxy(3,2); printf("Disco com problema /O");
                                       exit();
                                     }

 while(eof(arq1)!=1) {
		      tab=0;
		      read(arq1,buf,1);
                      letra=*buf;
                      if (letra=='\r') {letra='\x10'; pcom(letra); lseek(arq1,1,SEEK_CUR);}
                      if (letra==';')  {tab=band();}
                      if (isla(letra) && tab==0) {letra=recl(letra-'A'); tab=2;}
                      if (islb(letra) && tab==0) {letra=recl(letra-'G'); tab=2;}
                      if (isnu(letra) && tab==0) {letra=recl(letra+'\4'); tab=2;}
                      if (letra==';' && tab==0)  {tab=band1();}
                      if (tab==0) tab=lt(letra);
                      if (tab==0) {printf("Caractere Nao Reconhecido: %c-%d",letra,letra); }
		     }
 pcom('\x57');
 close(arq1);
 fclose(arq2);
}

band()
{
 char *prox;
 int x;

 read(arq1,prox,1);
 if (*prox=='\r') { pcom('\x09'); pcom('\x20');
                    pcom('\x14'); pcom('\x09');
                    lseek(arq1,1,SEEK_CUR);
                  }

 for(x=0;x<28;x++) if(*prox==tabband[x]) {pcom(tabband1[x]); break;}

 if(x==28) {lseek(arq1,-1,SEEK_CUR); return(0);} else return(2);
}

recl(letra)
{
 letra=tabmdt[letra];
 pcom(letra);
}

lt(char let)
{
 switch(let) { case ' ': pcom('\x8');  return(2);
               case '-': pcom('\x13'); return(2);
               case '$': pcom('\x6f'); return(2);
               case '!': pcom('\x2f'); return(2);
               case '?': pcom('\x33'); return(2);
               case ':': pcom('\x75'); return(2);
               case ';': pcom('\x35'); return(2);
               case '.': pcom('\x39'); return(2);
               case ',': pcom('\x19'); return(2);
               case '+': pcom('\x67'); return(2);
               case '=': pcom('\x61'); return(2);
               case '(': pcom('\x63'); return(2);
               case ')': pcom('\x23'); return(2);
               case '&': pcom('\x73'); return(2);
               case '[': pcom('\x6b'); return(2);
               case ']': pcom('\x4f'); return(2);
               case '*': pcom('\x3d'); return(2);
               case '<': pcom('\x09'); return(2);
               case '>': pcom('\x09'); return(2);
               case '#': pcom('\x3f'); return(2);
               case '"': pcom('\x51'); pcom('\x51'); return(2);
               case '_': pcom('\x65'); pcom('\x6d'); return(2);
               case '/': pcom('\x25'); pcom('\x71'); return(2);
               case '%': pcom('\x65'); pcom('\x4d'); return(2);
             }
}

band1()
{
 char *prox;

 read(arq1,prox,1);
 switch(*prox)  { case 'C': pcom('\x65'); pcom('\x7b'); return(2);
                  case 'c': pcom('\x25'); pcom('\x3b'); return(2);
                  case 'O': pcom('\x09'); pcom('\x30');
                            pcom('\x1a'); pcom('\x09');
                            pcom('\x25'); pcom('\x2b');
                            pcom('\x69'); return(2);
                  case 'A': pcom('\x09'); pcom('\x30');
                            pcom('\x1a'); pcom('\x09');
                            pcom('\x25'); pcom('\x2b');
                            pcom('\x29'); return(2);
                  case '"': pcom('\x11'); pcom('\x11'); return(2);
                  case '>': pcom('\x09'); pcom('\x2e');
                            pcom('\x14'); pcom('\x09'); return(2);
                  case '=': pcom('\x09'); pcom('\x2e');
                            pcom('\x1c'); pcom('\x09'); return(2);
                  case 'r': pcom('\x09'); pcom('\x0c');
                            pcom('\x1c'); pcom('\x09'); return(2);
                  case 'f': pcom('\x10'); pcom('\x09');
                            pcom('\x14'); pcom('\x0a');
                            pcom('\x09'); return(2);
                  case 'v': pcom('\x25'); pcom('\x0f'); return(2);
                  case 'x': pcom('\x25'); pcom('\x27'); return(2);
                  case 'd': pcom('\x25'); pcom('\x03'); return(2);
                  case 'w': pcom('\x25'); pcom('\x15'); return(2);
                  case 'E': pcom('\x65'); pcom('\x4f'); return(2);
                  case '.': pcom('\x25'); pcom('\x2b'); return(2);
                  case '(': pcom('\x25'); pcom('\x31'); return(2);
                  case ')': pcom('\x25'); pcom('\x2d'); return(2);
                  case 'b': pcom('\x25'); pcom('\x0b'); return(2);
                  case '1': pcom('\x65'); pcom('\x67'); return(2);
                  case '2': pcom('\x65'); pcom('\x43'); return(2);
                  case '3': pcom('\x65'); pcom('\x61'); return(2);
                  case '$': pcom('\x65'); pcom('\x55'); return(2);
                  case 's': pcom('\x25'); pcom('\x21'); return(2);
                  case 'q': pcom('\x65'); pcom('\x6b'); return(2);
                  case 'p': pcom('\x09'); pcom('\x02');
                            pcom('\x24'); pcom('\x09'); return(2);
                  case '0': pcom('\x09'); pcom('\x1c');
                            pcom('\x14'); pcom('\x09'); return(2);
                  case '#': pcom('\x3f'); pcom('\x30');
                            pcom('\x0e'); pcom('\x7f'); return(2);
                }
}

/*pcom(letra)
{
 putc(letra,arq2);
}*/

pcom(letra)
{
 union REGS regs;

 regs.h.ah=3;
 regs.x.dx=1;
 int86(0x14,&regs,&regs);

 while(((regs.h.al>>7)&1)==0 || ((regs.h.al>>5)&1)==0)
 { gotoxy(1,1);
   if(((regs.h.al>>7)&1)==0) printf("Falta Portadora"); else printf("               ");
   gotoxy(1,2);
   if(((regs.h.al>>5)&1)==0) printf("TY fora de Linha"); else printf("                ");
   regs.h.ah=3;
   regs.x.dx=1;
   int86(0x14,&regs,&regs);
 }

 regs.h.ah=1;
 regs.h.al=letra;
 regs.x.dx=1;
 int86(0x14,&regs,&regs);

}
