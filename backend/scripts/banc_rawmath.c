/* Banc de `rawmath()` : la vraie routine de WIMS, arbitre du port Python
 * (`core/oef/def_engine/rawmath.py`).
 *
 * Compiler depuis la racine du dépôt :
 *   gcc -w -Iwims/src -Iwims/src/Lib -o /tmp/banc_rawmath \
 *       backend/scripts/banc_rawmath.c wims/src/rawmath.c wims/src/Lib/libwims.a -lm
 *
 * Une expression par ligne sur l'entrée (octets latin-1, `\x01` pour un saut
 * de ligne) ; en sortie, `résultat \x03 avertissement`. Les variables de
 * session que lit `rawmath()` restent vides — `wims_rawmath_variables` et
 * `wims_rawmath_functions` comprises : à poser ici pour éprouver `litexp`.
 */
#include "wims.h"
/* Bouchons : rawmath() ne lit que ces variables de session. */
static char warn[4096];
char *getvar(char *name) {
  if(strcmp(name,"wims_warn_rawmath")==0) return warn;
  return NULL;
}
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
    warn[0]=0;
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
