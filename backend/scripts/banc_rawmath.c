/* Banc de `rawmath()` : la vraie routine de WIMS, arbitre du port Python
 * (`core/oef/def_engine/rawmath.py`).
 *
 * Compiler depuis la racine du dépôt :
 *   gcc -w -Iwims/src -Iwims/src/Lib -o /tmp/banc_rawmath \
 *       backend/scripts/banc_rawmath.c wims/src/rawmath.c wims/src/Lib/libwims.a -lm
 *
 * Une expression par ligne sur l'entrée (octets latin-1, `\x01` pour un saut
 * de ligne) ; en sortie, `résultat \x03 avertissement`. Deux formes
 * préfixées, champs séparés par `\x02` :
 *   R<x02>variables<x02>fonctions<x02>expr  — `rawmath()` sous
 *       `wims_rawmath_variables` / `wims_rawmath_functions` (`anstype/litexp`) ;
 *   V<x02>expr                              — `!varlist nofn expr`.
 */
#include "wims.h"
/* Bouchons : rawmath() ne lit que ces variables de session. */
static char warn[4096], uvars[MAX_LINELEN+1], ufns[MAX_LINELEN+1];
char *getvar(char *name) {
  if(strcmp(name,"wims_warn_rawmath")==0) return warn;
  if(strcmp(name,"wims_rawmath_variables")==0) return uvars;
  if(strcmp(name,"wims_rawmath_functions")==0) return ufns;
  return NULL;
}
void mathvarlist(char *p);
int force_setvar(char *name, char *value) {
  if(strcmp(name,"wims_warn_rawmath")==0) snprintf(warn,sizeof(warn),"%s",value);
  return 0;
}
void rawmath(char *p);
int main(void) {
  static char buf[MAX_LINELEN+1];
  while(fgets(buf,sizeof(buf),stdin)) {
    size_t n=strlen(buf); if(n && buf[n-1]=='\n') buf[--n]=0;
    for(char *q=buf;*q;q++) if(*q=='\x01') *q='\n';
    warn[0]=0; uvars[0]=0; ufns[0]=0;
    if(buf[0]=='V' && buf[1]=='\x02') {
      static char tmp[MAX_LINELEN+1];
      snprintf(tmp,sizeof(tmp),"nofn %s",buf+2);
      mathvarlist(tmp);
      printf("%s\x03\n",tmp);
      continue;
    }
    if(buf[0]=='R' && buf[1]=='\x02') {
      char *a=buf+2, *b=strchr(a,'\x02'), *c=b?strchr(b+1,'\x02'):NULL;
      if(b && c) {
        *b=0; *c=0;
        snprintf(uvars,sizeof(uvars),"%s",a);
        snprintf(ufns,sizeof(ufns),"%s",b+1);
        memmove(buf,c+1,strlen(c+1)+1);
      }
    }
    rawmath(buf);
    for(char *q=buf;*q;q++) if(*q=='\n') *q='\x01';
    printf("%s\x03%s\n",buf,warn);
  }
  return 0;
}
/* Symboles de htmlmath/mathml, non appelés par rawmath(). */
int mathalign_base=0;
char *substit(char *p) {return p;}
int mathml(char *p, int option) {return 0;}
