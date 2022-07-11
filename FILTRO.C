#include "menufil.h"
#include <fcntl.h>
#include <io.h>

char *varg[5],
     video[200]="",
     mat1[70]="";
int  posi=0,
     tab=0,
     pos=0,
     narg,
     arq1;

main(argc, argv)
char *argv[];
int argc;
{
 extern int marca[400],
            arq;
 narg=argc;
 varg[1]=argv[1];
 menu();
 gettext(24, 10, 55, 12, video);
 for (pos=1;pos<=arq;pos++) if(marca[pos]==1) foto(pos);
 fim();
}

foto(int pos)
{
 extern char mat[400][13];
 char label[2]=" o";
 int loc=0;
 char mold1[]="ÕoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍo¸o",
      mold2[]="³o oFoiolotoroaonodooo:o o o o o o o o o o o o o o o o o o o o³o",
      mold3[]="ÔoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍo¾o";
 window(24, 10, 56, 12);
 puttext(24, 10, 55, 10, mold1);
 puttext(24, 11, 55, 11, mold2);
 puttext(24, 12, 55, 12, mold3);
 while(mat[pos][loc]!='\0') { label[0]=mat[pos][loc];
			      puttext(37+loc,11,37+loc,11,label);
			      loc++;
                            }
 mdt(pos);
}

fim()
{
 union REGS regs;
 regs.h.ah=1;
 regs.h.ch=5;
 regs.h.cl=6;
 int86(0x10, &regs, &regs);
 window(1, 1, 80, 24);
 puttext(24, 10, 55, 12, video);
 gotoxy(1, 24);
}

file(int pos)
{
 extern char mat[400][13];
 int x;

 for(x=0;x<13;x++) mat1[x]=mat[pos][x];

 if((arq1=open(mat1,O_BINARY,0))==-1) { gotoxy(3,2); printf("Disco com problema");
				        exit();
				      }
}

help()
{
 int x, y;
 char help[4001], e='';
 x=wherex(); y=wherey();
 window(1, 1, 80, 25);
 gettext(1, 1, 80, 25, help);
 puttext(1,1,80,1,"ÉOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOËOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍO»O");
 puttext(1,2,80,2,"ºO O O O O O O O O O OCOoOnOtOrOoOlOeO OdOoO OCOuOrOsOoOrO O O O O O O O O O O O OºO O O O O O O O O O O O OTOeOcOlOaOsO OCOoOmOuOnOsO O O O O O O O O O O O OºO");
 puttext(1,3,80,3,"ºO O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,4,80,4,"ºO O\x1aO O O O O O-O OMOoOvOeO OoO OcOuOrOsOoOrO OpOaOrOaO OdOiOrOeOiOtOaO O O O O OºO OEOsOpOaO‡OoO O O-O OMOaOrOcOaO/ODOeOsOmOaOrOcOaO OuOmO OaOrOqOuOiOvOoO OºO");
 puttext(1,5,80,5,"ºO O\x1bO O O O O O-O OMOoOvOeO OoO OcOuOrOsOoOrO OpOaOrOaO OeOsOqOuOeOrOdOaO O O O OºO OROeOtOoOrOnOoO O-O OMOaOrOcOaO/ODOeOsOmOaOrOcOaO OuOmO OaOrOqOuOiOvOoO OºO");
 puttext(1,6,80,6,"ºO O\x18O O O O O O-O OMOoOvOeO OoO OcOuOrOsOoOrO OpOaOrOaO OcOiOmOaO O O O O O O O OºO OEOsOcO O O O O O-O OCOaOnOcOeOlOaO OfOuOnO‡O„OoO O O O O O O O O O O O OºO");
 puttext(1,7,80,7,"ºO O\x19O O O O O O-O OMOoOvOeO OoO OcOuOrOsOoOrO OpOaOrOaO ObOaOiOxOoO O O O O O O OºO O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,8,80,8,"ºO OHOoOmOeO O O-O OPOoOsOiOcOiOoOnOaO OnOoO OpOrOiOmOeOiOrOoO OaOrOqOuOiOvOoO O OÌOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍO¹O");
 puttext(1,9,80,9,"ºO OEOnOdO O O O-O OPOoOsOiOcOiOoOnOaO OnOoO O£OlOtOiOmOoO OaOrOqOuOiOvOoO O O O OºO O O O O O O O OEOdOiOtOoOrOeOsO ODOiOsOpOoOnO¡OvOeOiOsO O O O O O O O O OºO");
 puttext(1,10,80,10,"ºO OPOgO OUOpO O-O OAOvOaOnO‡OaO OpO OgOiOnOaO O O O O O O O O O O O O O O O O O OºO O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,11,80,11,"ºO OPOgO ODOnO O-O OROeOtOrOoOcOeOdOeO OpO OgOiOnOaO O O O O O O O O O O O O O O OºO O O_O OCOaOrOtOaO OCOeOrOtOaO O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,12,80,12,"ºO O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO O O_O OFO OcOiOlO O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,13,80,13,"ÌOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍO¹O O O_O OMOSO OWOoOrOdO O O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,14,80,14,"ºO O O O O O O O O O O OTOeOcOlOaOsO OdOeO OFOuOnO‡O”OeOsO O O O O O O O O O O O OºO O O_O OOOpOeOnO OAOcOeOsOsO O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,15,80,15,"ºO O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO O O_O OPO OgOiOnOaO OCOeOrOtOaO O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,16,80,16,"ºO OFO1O O O O O-O OMOoOsOtOrOaO OeOsOtOeO OHOeOlOpO O O O O O O O O O O O O O O OºO O O_O OROeOdOaOtOoOrO OIO-O7O0O0O0O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,17,80,17,"ºO OFO2O O O O O-O OFOiOlOtOrOaO OoOsO OaOrOqOuOiOvOoOsO OmOaOrOcOaOdOoOsO O O O OºO O O_O OROeOdOaOtOoOrO OIOBOMO OPOCO O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,18,80,18,"ºO OFO3O O O O O-O OMOuOdOaO OoO OEOdOiOtOoOrO OOOrOiOgOeOmO O O O O O O O O O O OºO O O_O OWOoOrOdO OPOeOrOfOeOcOtO O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,19,80,19,"ºO OFO4O O O O O-O OMOuOdOaO OoO OEOdOiOtOoOrO ODOeOsOtOiOnOoO O O O O O O O O O OºO O O_O OWOoOrOdO OSOtOaOrO O(OaOtO‚O OvOeOrOsO„OoO O3O.O3O)O O O O O O O OºO");
 puttext(1,20,80,20,"ºO OFO5O O O O O-O OMOaOrOcOaO OtOoOdOoOsO OoOsO OaOrOqOuOiOvOoOsO O O O O O O O OºO O O_O OWOoOrOdO OSOtOaOrO O(OaOpO¢OsO OvOeOrOsO„OoO O3O.O4O)O O O O O O OºO");
 puttext(1,21,80,21,"ºO OFO6O O O O O-O ODOeOsOmOaOrOcOaO OtOoOdOoOsO OoOsO OaOrOqOuOiOvOoOsO O O O O OºO O O_O OWOoOrOdO OSOtOaOrO O2O0O0O0O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,22,80,22,"ºO OAOLOTO OFO O-O OMOuOdOaO OaO OmO OsOcOaOrOaO OdOoOsO OaOrOqOuOiOvOoOsO O O O OÌOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍO¹O");
 puttext(1,23,80,23,"ºO O O O O O O O O O OmOoOsOtOrOaOdOoOsO O O O O O O O O O O O O O O O O O O O O OºO OPOrOoOgOrOaOmOaOdOoOrO:O OMOaOrOcOeOlOoO OEOsOcOoObOaOrO O O O O O O O OºO");
 puttext(1,24,80,24,"ÈOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÊOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍO¼O");
 while(e=='') e=getch();
 puttext(1, 1, 80, 25, help);
 window(1, 5, 80, 19);
 gotoxy(x,y);
}
