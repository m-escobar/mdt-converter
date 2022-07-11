#if __STDC__
#define _Cdecl
#else
#define _Cdecl  cdecl
#endif

#define MAGENTA 6
#define CYAN    4

#define isla(c) ((c)>=65 && (c)<=90)
#define islb(c) ((c)>=97 && (c)<=122)
#define isnu(c) ((c)>=48 && (c)<=57)

struct WORDREGS { unsigned int  ax, bx, cx, dx, si, di, cflag, flags; };
struct BYTEREGS { unsigned char al, ah, bl, bh, cl, ch, dl, dh; };
union  REGS { struct WORDREGS x;
              struct BYTEREGS h; };

struct ffblk { char       ff_reserved[21];
               char       ff_attrib;
               unsigned   ff_ftime;
               unsigned   ff_fdate;
               long       ff_fsize;
               char       ff_name[13]; };

int  _Cdecl findfirst (const char *path, struct ffblk *ffblk, int attrib);
int  _Cdecl findnext (struct ffblk *ffblk);
