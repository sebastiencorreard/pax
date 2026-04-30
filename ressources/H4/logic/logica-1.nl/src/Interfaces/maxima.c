/*    Copyright (C) 1998-2003 XIAO, Gang of Universite de Nice - Sophia Antipolis
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* Interface maxima to wims */

/*************** Customization: change values hereafter ****************/
#include "common.h"
/* limit of input/output file sizes */
int fsizelim=131072;
/* This string tells maxima to exit. */
char *quitstring="\nquit();\n";
char *aboutquitstring="build_info();" "\nquit();\n";
/* The way to print a string in the program. */
char *stringprinter="\"%s\";\n";
/* This is maxima home page. To be kept up to date. */
#define homepage "http://maxima.sourceforge.net/"

char *nameofcmd="maxima";
int precision=20;
char header[]="\n\
display2d:false;\n\
letrat:true;\n\
keepfloat:true;\n\
rombergmin:5;\n\
rombergtol:1.E-6;\n\
rombergit:13;\n\
simpsum:true;\n\
triginverses:true; logabs:true;\n\
e:%e;pi:%pi;Pi:%pi;PI:%pi;I:%i;i:%i;\n\
ln:log;sh:sinh;ch:cosh;th:tanh;\n\
arctan:atan;arcsin:asin;arccos:acos;\n\
tg:tan;arctg:atan;\n\
argsh:asinh;argch:acosh;argth:atanh;\n\
Argsh:asinh;Argch:acosh;Argth:atanh;\n\
cotan:cot;ctg:cot;\n\
log10(x):=block([],return(log(x)/log(10.0)));\n\
log2(x):=block([],return(log(x)/log(2.0)));\n\
lg(x):=log10(x);\n\
sgn:sign;\n\
nolabels:true; kill(labels);\n\
load \"logic.lisp\";\n\
";

struct {
    char *wname; char *defaultval; char *setname;
} setups[]={
      {"w_maxima_precision", "20", "fpprec"}
};

/* names which are not allowed */
char *illegal[]={
      "system","describe","example",
      "save","fassave","stringout","batcon",
      "batcount","cursordisp",
      "direc","readonly","with_stdout","pscom",
      "demo","ttyintfun","bug"

};

int illegal_no=(sizeof(illegal)/sizeof(illegal[0]));

/* name parts which are not allowed */

#ifdef CHROOT_PRESENT
 char *illpart[]={"file", "debug", "plot", "store", "batch"};
#else
char *illpart[]={"file", "debug", "plot", "load", "store", "batch"};
#endif

int illpart_no=(sizeof(illpart)/sizeof(illpart[0]));

/***************** Nothing should need change hereafter *****************/

#define linebyline "\n(%i"
char *progname="maxima";

/* check for security violations in command string */
void check_parm(char *pm)
{
    char *s, *pp;
    int l;
/* Underscore replacement */
#ifndef CHROOT_PRESENT
    for(pp=strchr(pm,'_'); pp!=NULL; pp=strchr(pp+1,'_')) *pp='K';
#endif

/* '?' escapes to Lisp commands. */
    if(strchr(pm,'?')!=NULL) {
        fprintf(stderr,"Illegal under WIMS.\n"); exit(1);
    }
    for(s=pm;*s;s++) *s=tolower(*s);
    strip_trailing_spaces2(pm); l=strlen(pm);
    if(l>0 && pm[l-1]!=';') strcat(pm,";");
    find_illegal(pm);
}

char *find_prompt(char *p, char t)
{
    char *pp=p-1, *pt;
    char c;
    int add;
    redo:
    if(*p==0 || (pp>=p && *pp==0)) return NULL;
    add=3;
    do {
      pp=strstr(pp+1,"\n(");
      if(!pp) break;
      c=pp[2]; add=3;
      if(c=='\%') { /* backward compatibility */
          add++; c=pp[3];
          if(c=='i') c='C';
          if(c=='o') c='D';
      }
    }
    while(c!=t);
    pt=pp;
    if(pp!=NULL) {
      pp+=add; while(isdigit(*pp)) pp++;
      if(*pp!=')') goto redo;
      pp++;
    }
    if(pt!=NULL && t=='D') pt=pp;
    return pt;
}

/* process and print maxima output */
void output(char *p)
{
    int i,n;
    char *pp, *pe, *pt;

    pp=find_prompt(p,'C');
    while(pp!=NULL) {
      pe=find_prompt(pp+1,'C'); pp=find_prompt(pp,'D');
      if(pp==NULL) return;
      if(pe!=NULL && pp>=pe) goto emptyline;
      if(pe==NULL) pe=pp+strlen(pp); else *pe++=0;
      if(pp>=pe) {
          emptyline:
          puts(""); pp=pe; continue;
      }
      n=strlen(pp); if(n==0) goto emptyline;
/* make every output one-line */
      for(i=0;i<n;i++) {
          if(*(pp+i)=='\n' || *(pp+i)=='\%') *(pp+i)=' ';
          else *(pp+i)=tolower(*(pp+i));
      }
/* strip leading and trailing spaces */
      while(isspace(*pp) && pp<pe) pp++;
      pt=pp+strlen(pp)-1;
      while(isspace(*pt) && pt>pp) *pt--=0;
      if(*pp=='[' && *pt==']' && find_matching2(pp+1,']')==pt) {
          *(pt--)=0; pp++;
      }
      for(pt=strchr(pp,'b');pt!=NULL; pt=strchr(pt+1,'b')) {
          if(pt>pp && isdigit(*(pt-1)) &&
             (*(pt+1)=='-' || isdigit(*(pt+1)))) {
            if(*(pt+1)=='0' && !isdigit(*(pt+2))) ovlstrcpy(pt,pt+2);
            else *pt='E';
          }
      }
      puts(pp); pp=pe;
    }
}

void about(void)
{
    char *p, *p2, *pp;
    int i;

/*    printf("<a href=\"%s\">Maxima</a>",homepage); return; */
    prepabout(aboutquitstring,outputfname,NULL);
    if(readabout()>0) {
      for(p=aboutbuf; *p; p=find_word_start(find_word_end(p))) {
          if(strncasecmp(p,"Maxima",strlen("Maxima"))==0) {
            p2=find_word_start(find_word_end(p));
            if(strncmp(p2,"restarted",9)!=0) break;
          }
      }
      for(p2=p;*p2 && *p2!='\n' && !isdigit(*p2);p2++);
      if(isdigit(*p2)) pp=find_word_end(p2);
      else for(i=0, pp=p;i<2;i++) pp=find_word_end(find_word_start(pp));
      *pp=0;
      if(*p!=0) printf("<a target=\"wims_external\" href=\"%s\">%s</a>",homepage,p);
    }
}

char *dynsetup(char *ptr, char *end)
{
    int i;
    char *p, *pp;
    if(wseed!= NULL) {
      snprintf(ptr,end-ptr,"\nwimsseed:make_random_state(%u);\nset_random_state(wimsseed);\n",atoi(wseed)&(0x7FFFFFFF));
      ptr+=strlen(ptr);
    }
    for(i=0;i<SETUP_NO;i++) {
      p=getenv(setups[i].wname);
      if(p!=NULL) for(pp=p;*pp;pp++) if(!isspace(*pp) && !isalnum(*pp)) p="";
      if(p==NULL || *p==0) p=setups[i].defaultval;
      snprintf(ptr,end-ptr,"%s:%s;\n",setups[i].setname,p);
      ptr+=strlen(ptr);
      if(strstr(setups[i].wname,"maxima_precision")!=NULL)
        precision=atoi(p);
      if(precision<0) precision=-precision;
    }
    return ptr;
}

int main(int argc,char *argv[])
{
    prepare1();
    run();
    return 0;
}

