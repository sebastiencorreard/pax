target=2nddegre operation fonctionaff periaire comparaison tarif decompte divisibilite somme sommec sommecpi fact listm

\integer{nbtheme=(\confparm1==)?1:\confparm1}
\matrix{theme=ambiance,neat;rubyblue,eclipse;the-matrix,3024-day}

#define MF Modifier une fonction
#define MLFI Modifier la fonction Python intitulée
#define E Écrire une fonction
#define EE Écrire une fonction qui effectue la somme
#define PPP Le programme Python ci-dessous permet
#define IFI Il utilise une fonction intitulée

\text{list_var=a,b,c,d,f,g,h,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,}
\text{nomvar1=randitem(\list_var)}
\text{nomvar11=randitem(\list_var)}
\text{nomvar111=randitem(\list_var)}
\text{eva1=\nomvar1 \nomvar11 \nomvar111 _test1}
\text{eva1=wims(nospace \eva1)}
\text{list_var2=wims(listcomplement \nomvar1 in \list_var)}
\text{nomvar2=randitem(\list_var2)}
\text{eva2=\nomvar2 \nomvar11 \nomvar111 _test2}
\text{eva2=wims(nospace \eva2)}
\text{list_var3=wims(listcomplement \nomvar2 in \list_var2)}
\text{nomvar3=randitem(\list_var3)}
\text{eva3=\nomvar3 \nomvar11 \nomvar111 _test3}
\text{eva3=wims(nospace \eva3)}
\text{list_var4=wims(listcomplement \nomvar3 in \list_var3)}
\text{nomvar4=randitem(\list_var4)}
\text{eva4=\nomvar4 \nomvar11 \nomvar111 _test4}
\text{eva4=wims(nospace \eva4)}

\integer{preci=1000}

#if defined TARGET_2nddegre
# include "2nddegre.inc"
#endif

#if defined TARGET_operation
#include "operation.inc"
#endif

#if defined TARGET_fonctionaff
#include "fonctionaff.inc"
#endif

#if defined TARGET_periaire
#include "periaire.inc"
\integer{preci=1}
#endif

#if defined TARGET_comparaison
#include "comparaison.inc"
#endif

#if defined TARGET_tarif
#include "tarif.inc"
#endif

#if defined TARGET_decompte
#include "decompte.inc"
#endif

#if defined TARGET_divisibilite
#include "divisibilite.inc"
#endif

#if defined TARGET_somme
\title{EE des nombres entiers de 0 à N}
\text{des=des \(N+1\) premiers nombres entiers de 0 à \(N\)}
\text{exx=0+1+2+3+4=\displaystyle \sum_{i=0}^{N=4} i=10}
\integer{NN=randint(100..1000)}
\integer{xO=\NN*(\NN+1)/2}
#include "somme.inc"
#endif

#if defined TARGET_sommec
\title{EE des carrés des entiers de 0 à N}
\text{des=des carrés des \(N+1\) premiers nombres entiers de 0 à \(N\)}
\text{exx=0^2+1^2+2^2+3^2+4^2=\displaystyle \sum_{i=0}^{N=4} i^2=0+1+4+9+16=30}
\integer{NN=randint(100..900)}
\integer{RP=randint(50..100)}
\integer{xO=\NN*(\NN+1)*(2*\NN+1)/6}
\integer{nbi=\RP*(\RP+1)*(2*\RP+1)/6+(randint(1..\RP-1))^2}
#include "somme.inc"
#endif

#if defined TARGET_sommecpi
\title{EE de carrés des nombres pairs ou impairs}
\integer{alea=randint(1..2)}
\text{des=(\alea==1)?des carrés des \(N+1\) premiers nombres pairs:des carrés des \(N+1\) premiers nombres impairs}
\text{exx=(\alea==1)?\begin{array}{lcl} 0^2+2^2+4^2+6^2+8^2 & = & (2\times 0)^2+(2\times 1)^2+(2\times 2)^2+(2\times 3)^2+(2\times 4)^2 \\ & = & \displaystyle \sum_{i=0}^{N=4} (2i)^2=0+4+16+36+64=120\end{array}:\begin{array}{lcl}1^2+3^2+5^2+7^2+9^2 & = & (2\times 0+1)^2+(2\times 1+1)^2+(2\times 2+1)^2+(2\times 3+1)^2+(2\times 4+1)^2 \\ & = &\displaystyle \sum_{i=0}^{N=4} (2i+1)^2=1+9+25+49+81=165\end{array}}
\integer{NN=randint(20..100)}
\integer{xO=(\alea==1)?\NN*2*(\NN+1)*(2*\NN+1)/3:(\NN+1)*(2*\NN+1)*(2*\NN+3)/3}
#include "somme.inc"
#endif

#if defined TARGET_fact
\title{E Factorielle avec la méthode itérative}
#include "fact.inc"
#endif
#if defined TARGET_listm
\title{E qui effectue la liste des multiples de 0 à N}
#include "listm.inc"
#endif

\text{consigne=Tester votre fonction à l'aide de ce type
  d'instruction <code>\inst</code> pour vérifier qu'elle
 fonctionne dans chacun des cas.}

#include "prog.inc"
