target=sysequi1 sysequi2 sysequi3 sysequi4 sysequi5
#include "author.inc"
#include "lang_titles.inc"

\text{v=wims(values v for v=2 to 9)}
\text{v=shuffle(\v)}
\text{name_enonce= Parmi les deux systèmes d'équations ci-dessous,
  lequel a la même solution que le système suivant.}
#if defined TARGET_sysequi1
 \integer{r1=\v[1]*\v[4]}
 \integer{r2=\v[2]*\v[4]}
 \integer{r3=\v[3]*\v[4]}
 \integer{r4=\v[4]*\v[1]}
 \integer{r5=\v[5]*\v[1]}
 \integer{r6=\v[6]*\v[1]}
 \text{don=\r1,\v[2],\v[3],\r4,\v[5],\v[6]
\v[1],\v[2],\v[3],\v[4],\v[5],\v[6]
\r1,\r2,\r3,\r4,\r5,\r6}
#endif
#if defined TARGET_sysequi2
 \integer{r1=\v[5]-\v[2]}
 \integer{r2=\v[6]-\v[3]}
 \text{don=\v[1],\v[2],\v[3],0,\r1,\v[6]
\v[1],\v[2],\v[3],\v[1],\v[5],\v[6]
\v[1],\v[2],\v[3],0,\r1,\r2}
#endif
#if defined TARGET_sysequi3
 \integer{r1=\v[5]-\v[2]}
 \integer{r2=\v[6]-\v[3]}
 \text{don=\v[1],\v[2],\v[3],-\v[1],\v[5],\v[6]
\v[1],\v[2],\v[3],\v[1],\v[5],\v[6]
\v[1],\v[2],\v[3],0,\r1,\r2}
#endif
#if defined TARGET_sysequi4
 \integer{r1=\v[5]+\v[2]}
 \integer{r2=\v[6]+\v[3]}
 \text{don=\v[1],\v[2],\v[3],\v[1],\v[5],\v[6]
\v[1],\v[2],\v[3],-\v[1],\v[5],\v[6]
\v[1],\v[2],\v[3],0,\r1,\r2}
#endif
#if defined TARGET_sysequi5
 \text{v=wims(values v,-v for v=2 to 9)}
 \text{v=shuffle(\v)}
 \integer{r1=\v[1]*\v[4]}
 \integer{r2=\v[2]*\v[4]}
 \integer{r3=\v[3]*\v[4]}
 \integer{r4=\v[4]*\v[1]}
 \integer{r5=\v[5]*\v[1]}
 \integer{r6=\v[6]*\v[1]}
 \text{don=\r1,\v[2],\v[3],\r4,\v[5],\v[6]
\v[1],\v[2],\v[3],\v[4],\v[5],\v[6]
\r1,\r2,\r3,\r4,\r5,\r6}
#endif

\text{para=}
\text{inc=randrow(x,y
u,v
a,b)}
\text{x=\inc[1]}
\text{y=\inc[2]}
\text{choix=}
\for{k=1 to 3}{
 \text{c=row(\k,\don)}
 \text{t1=\c[1]*\c[2]=0?maxima(\c[1]*\y+\c[2]*\x;):\c[1]*\y+\c[2]*\x}
 \text{t1=texmath(\t1)}
 \text{t2=\c[4]*\c[5]=0?maxima(\c[4]*\y+\c[5]*\x;):\c[4]*\y+\c[5]*\x}
 \text{t2=texmath(\t2)}
 \text{sys=\left\lbrace\begin{array}{ccc}\t1&=&\c[3]\\ \t2&=&\c[6]\end{array}\right.}
 \text{choix=wims(append item \para \(\sys) to \choix)}
}

\statement{
  \name_enonce
  <div class="wimscenter">\choix[2]</div>}

\choice{Votre choix}{\choix[3]}{\choix[1]}
