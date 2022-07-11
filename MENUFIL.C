#include <errno.h>
#include "menufil.h"

extern int narg;
extern char *varg[];
char mat[400][13],
     dest[2700]="",
     *ext;
int  arq=0, max_x=0, max_y=0, cpage, marca[400], narq, erro=0;

menu()
{
 if (narg<2) ext="*."; else ext=varg[1];
 j_ini();
 dir();
 if(erro==0) { mos_arq();
	       def_max();
	     }
 inverte(0);
 letesp();
 puttext(1, 5, 80, 20, dest);
}

j_ini()
{
 int  linha;
 char linsup[] ="ÕOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍO¸O",
      linmei[] ="³O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O³O",
      lininf[] ="ÃOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄOÄO´O",
      linin1[] ="ÔOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍO¾O";

 gettext(1, 5, 80, 20, dest);
 window(1, 19, 80, 20);
 clrscr();
 puttext(1, 17, 80, 17, linmei);
 puttext(1, 18, 80, 18, linin1);
 window(1, 5, 80, 19);
 puttext(1, 5, 80, 5, linsup);
 for (linha=6;linha<16;linha++) puttext(1, linha, 80, linha, linmei);
 puttext(1, 16, 80, 16, lininf);
 gotoxy(2, 2);
 textbackground(MAGENTA);
 cprintf("            Fotografia de MDT para 8600            Vers„o: Junho 90           ");
 textbackground(CYAN);
 puttext(5 ,17,13,17,"AOrOqOuOiOvOoO:O O");
 puttext(30,17,39,17,"TOoOtOaOlO:O O0O O O");
 puttext(50,17,62,17,"MOaOrOcOaOdOoOsO:O O0O O O");
 puttext(69,17,77,17,"[OFO1O]O OHOeOlOpO");
}

dir()
{
 union REGS regs;
 struct ffblk ffblk;
 int nome=0;
 arq=0; errno=0;
 findfirst(ext, &ffblk, 1);
 if (errno != 0) { arq_naoexiste(); erro=1; return; }
 arq+=1;
 for (nome=0;nome<14;nome++) mat[arq][nome]=ffblk.ff_name[nome];
 do { findnext(&ffblk);
      if (errno != 0) { break; }
      arq+=1;
      for (nome=0;nome<14;nome++) mat[arq][nome]=ffblk.ff_name[nome];
    } while(errno == 0);
 gotoxy(37, 13); cprintf("%d  ",arq);
 gotoxy(4, 8);
 regs.h.ah=1;
 regs.h.ch=9;
 regs.h.cl=0;
 int86(0x10, &regs, &regs);
 cpage=1; erro=0;
}

letesp()
{
 union scan { int c;
              char ch[2];
            } sc;

 int x=4, y=8, page, fim=0;

 if(arq%40 != 0) page=arq/40+1; else page=arq/40;
 inverte(0);
 do  {
      sc.c=getch();
      if((sc.ch[0]==0x20) || (sc.ch[0]==0x0D)) { inverte(1); sc.ch[1]=0; sc.ch[0]=77; }
      if((sc.ch[1]==0 && sc.ch[0]==72) && y==8) if (x > max_x) y=max_y; else y=max_y+1;
      if(sc.ch[1]==0 && sc.ch[0]==72) { inverte(0); y-=1;  gotoxy(x, y); inverte(0); } /*sobe*/
      if((sc.ch[1]==0 && sc.ch[0]==80) && y==max_y) y=7;
      if((sc.ch[1]==0 && sc.ch[0]==80) && y+1==max_y) if (x > max_x) y=7;
      if(sc.ch[1]==0 && sc.ch[0]==80) { inverte(0); y+=1;  gotoxy(x, y); inverte(0); } /*desce*/
      if((sc.ch[1]==0 && sc.ch[0]==77) && x==64) if (y!=max_y) { inverte(0); x=4; y++; gotoxy(x, y); inverte(0); sc.ch[0]=0; }
      if((sc.ch[1]==0 && sc.ch[0]==77) && y==max_y && x==max_x) sc.ch[0]=0;
      if(sc.ch[1]==0 && sc.ch[0]==77) { inverte(0); x+=15; gotoxy(x, y); inverte(0); } /*direita*/
      if((sc.ch[1]==0 && sc.ch[0]==75) && x==4 && y==8) sc.ch[0]=0;
      if((sc.ch[1]==0 && sc.ch[0]==75) && x==4) {y--; if (y==max_y) x=max_x+15; else x=79;}
      if(sc.ch[1]==0 && sc.ch[0]==75) {inverte(0); x-=15; gotoxy(x, y); inverte(0);} /*esquerda*/
      if(sc.ch[1]==0 && sc.ch[0]==71) {inverte(0); x=4; y=8; gotoxy(x, y); inverte(0);} /*home*/
      if(sc.ch[1]==0 && sc.ch[0]==79) {inverte(0); x=max_x; y=max_y; gotoxy(x, y); inverte(0);} /*end*/
      if(sc.ch[1]==0 && sc.ch[0]==73) if (cpage>1) { cpage--; l_tela(); mos_arq(); def_max(); x=4; y=8;} /*PgUp*/
      if(sc.ch[1]==0 && sc.ch[0]==81) if (cpage<page) { cpage++; l_tela(); mos_arq(); def_max(); x=4; y=8;} /*PgDn*/
      if(sc.ch[1]==0 && sc.ch[0]==0x3b) help();
      if(sc.ch[1]==0 && sc.ch[0]==0x3c) fim=1; else fim=0;
      if(sc.ch[1]==0 && sc.ch[0]==0x3f) if(narq!=arq) {marca_tudo(1); x=4; y=8;}
      if(sc.ch[1]==0 && sc.ch[0]==0x40) if(narq!=0) {marca_tudo(0); x=4; y=8;}
      if(sc.ch[1]==0 && sc.ch[0]==0x21) {page=redir(); x=4; y=8;}
      if(sc.ch[0]==0x1B) cancela();
      } while (fim==0);
}

marca_tudo(int tipo)
{
 int x;
 if (tipo==0) { for(x=0;x<=400;x++) marca[x]=0;
                l_tela();
                mos_arq();
                def_max();
                gotoxy(4,8);
                narq=0;
              } else { for(x=0;x<=400;x++) marca[x]=1;
                       l_tela();
                       mos_arq();
                       def_max();
                       gotoxy(4,8);
                       narq=arq;
                     }
 gotoxy(60, 13); cprintf("%d   ",narq);
 gotoxy(4,8);
}

redir()
{
 union REGS regs;
 char alet[2]=" o", let='',
      mold1[]="ÕoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍo¸o",
      mold2[]="³o oNooovoao oMo osocoaoroao:o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o³o",
      mold3[]="ÔoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍo¾o";
 int x=0, c=0;
 *ext='\0';
 window(9, 10, 71, 12);
 puttext(9, 10, 71, 10, mold1);
 puttext(9, 11, 71, 11, mold2);
 puttext(9, 12, 71, 12, mold3);
 gotoxy(17,2);
 regs.h.ah=1;
 regs.h.ch=5;
 regs.h.cl=6;
 int86(0x10, &regs, &regs);
 for(c=0;c<45;c++) { x=0;
                     let=getch();
                     if(let=='\x0D') { *(ext+c)='\0'; break; }
		     if(let=='\b' && c==0) { c--; puttext(25,11,25,11," o"); gotoxy(17,2); x=1;
					   } else if(let=='\b' && x==0) { x=wherex(); gotoxy(x-1,2);
									  puttext(x+7,11,x+7,11," o");
									  x=1; c-=2;
									}
		     if(let=='\x1B') cancela();
		      else if(x==0 && let=='\0') {let=getch(); c--;}
			      else if(x==0) {x=wherex();
					     alet[0]=let;
					     puttext(x+8,11,x+8,11,alet);
					     *(ext+c)=let;
					     gotoxy(x+1,2);
					     x=0;
					    }
		     if(c==44) { c=-1; gotoxy(17,2);
				 puttext(25,11,69,11," o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o");
			       }
		  }
 regs.h.ah=1;
 regs.h.ch=9;
 regs.h.cl=0;
 int86(0x10, &regs, &regs);
 for(x=0;x<400;x++) marca[x]=0;
 narq=0; cpage=1;
 l_tela();
 dir();
 mos_arq();
 def_max();
 gotoxy(60,13); cprintf("%d   ",narq);
 gotoxy(4,8);
 if(arq%40!=0) return(arq/40+1); else return(arq/40);
}

matriz(int tag)
{
 int posy=0, posx=0, x;
 posx = wherex();
 posy = wherey();
 switch (posx) { case  4: x=((cpage-1)*40)+1+((posy-8)*5); break;
		 case 19: x=((cpage-1)*40)+2+((posy-8)*5); break;
		 case 34: x=((cpage-1)*40)+3+((posy-8)*5); break;
		 case 49: x=((cpage-1)*40)+4+((posy-8)*5); break;
		 case 64: x=((cpage-1)*40)+5+((posy-8)*5); break;
               };
 if (tag==0) { marca[x]=0; narq--; } else { marca[x]=1; narq++; }
 gotoxy(60,13); cprintf("%d   ",narq); gotoxy(posx, posy);
}

inverte(int cond)
{
 int posy=0, posx=0,
     cont, local, fim,
     cor1=0x47, cor2=0x2f, cor3=0x30, cor4=0x70;
 char ch='',
      d_inv[30] = "",
      chr[3]="",
      name[3]="";

 posx = wherex();
 posy = wherey();
 if (cond!=1)
  { gettext(posx, posy, posx+11, posy, d_inv);
    if ( d_inv[1] == cor1) ch = cor2;
    if ( d_inv[1] == cor2) ch = cor1;
    if ( d_inv[1] == cor3) ch = cor4;
    if ( d_inv[1] == cor4) ch = cor3;
    cont=0; name[0]='';
    while (name[0]!='.') { name[0]=d_inv[cont];
                           if (name[0]=='.') { cont+=2; break; }
                           name[1]=cor1;
                           puttext(14+(cont/2), 17, 14+(cont/2), 17, name);
                           if (cont<18) cont+=2; else break;
                         }
    local=cont-2;
    if (local<21) { name[0]=''; name[1]=cor1;
                   for(;local<21;local+=2) puttext(14+(local/2), 17, 14+(local/2), 17, name);
                  }
    name[0]='.';
    puttext(22, 17, 22, 17, name);
    local=0; fim=cont+6;
    for(;cont<fim;cont+=2) { name[0]=d_inv[cont];
                            name[1]=cor1;
                            puttext(23+local, 17, 23+local, 17, name);
                            local++;
                          }

    for (cont=1;cont<24;cont+=2) d_inv[cont] = ch;
    puttext(posx, posy, posx+11, posy, d_inv);
  } else {  gettext(posx-1, posy, posx-1, posy, d_inv);
            if (d_inv[0]=='\x7') { chr[0]=' ';   chr[1]= cor1; matriz(0); }
                            else { chr[0]='\x7'; chr[1]= cor3; matriz(1); }
            puttext(posx-1, posy, posx-1, posy, chr);
            gettext(posx, posy, posx+11, posy, d_inv);
            if ( d_inv[1] == cor2) ch = cor4; else ch = cor2;
            for (cont=1;cont<24;cont+=2) d_inv[cont] = ch;
            puttext(posx, posy, posx+11, posy, d_inv);
         }
}

def_max()
{
 int pos, page;
 if(arq%40 != 0) page=arq/40+1; else page=arq/40;
 if (arq<=40) pos=arq; else if (cpage!=page) pos=40;
                       else pos=arq%40;
 if (pos%5 == 0) max_y= 7 + (pos/5);
  else max_y= 8 + (pos/5);
 if (pos%5 == 0) max_x= 64;
  else max_x= 4 + ((arq%5-1)*15);
}

arq_naoexiste()
{
 unsigned char e='',
               mold1[]="ÕoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍo¸o",
               mold2[]="³o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o³o",
               mold3[]="ÔoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍo¾o";

 puttext(24, 10, 55, 10, mold1);
 puttext(24, 11, 55, 11, mold2);
 puttext(24, 12, 55, 12, mold3);
 gotoxy(26, 7);
 cprintf("Arquivo nao existe tecle ESC");
 while(e != '\x1B') e = getch();
 redir();
}

mos_arq()
{
 char marc[3]={'\x7','0','\0'},
      video[25]="";
 int page, x=4, y=4, ini=0, fim=0, loc=0;
 if(arq%40 != 0) page=arq/40+1; else page=arq/40;
 ini=((cpage-1)*40)+1;
 if (cpage<page) fim=40*cpage; else fim=arq;
 if (marca[ini]==1) { while(mat[ini][loc]!='\0') { video[loc*2]=mat[ini][loc];
						   video[loc*2+1]='0';
                                                   loc++;
                                                 }
		      while(loc<=11) { video[loc*2]=' ';
				       video[loc*2+1]='0';
                                       loc++;
                                     }
                      gotoxy(x, y);
                      puttext(x-1, y+4, x-1, y+4, marc);
                      puttext(x, y+4, x+11, y+4, video);
                      ini++; x+=15;
                    }
 while(ini <= fim)
  {
   loc=0;
   gotoxy(x, y);
   if (marca[ini]==1) { while(mat[ini][loc]!='\0') { video[loc*2]=mat[ini][loc];
						     video[loc*2+1]='0';
                                                     loc++;
                                                   }
                        while(loc<=11) { video[loc*2]=' ';
					 video[loc*2+1]='0';
                                         loc++;
                                       }
                        video[loc*2]='\0';
                        puttext(x-1, y+4, x-1, y+4, marc);
                        puttext(x, y+4, x+11, y+4, video);
		      } else cprintf("%s",mat[ini]);
   ini++;
   if (x == 64) { x=4; y++; } else { x+=15; }
  }
 gotoxy(4, 8);
 inverte(0);
}

l_tela()
{
 window(3, 8, 75, 15);
 clrscr();
 window(1, 5, 80, 19);
}

cancela()
{
 union REGS regs;
 puttext(1, 5, 80, 20, dest);
 regs.h.ah=1;
 regs.h.ch=5;
 regs.h.cl=6;
 int86(0x10, &regs, &regs);
 window(1, 1, 80, 24);
 gotoxy(1, 24);
 exit();
}
