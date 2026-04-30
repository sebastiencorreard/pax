target=ineqequi1 ineqequi2 ineqequi3 ineqequi4 ineqequi5

#include "author.inc"
#include "lang_titles.inc"
\text{x=randitem(x,y,z,u,v,a,b)}
\integer{ch=randint(1..4)}
\text{sy=item(\ch,<,>,<=,>=)}
\text{csy=item(\ch,>,<,>=,<=)}
\text{sy2=item(\ch,<=,>=,<,>)}
\text{v=wims(values v for v=2 to 9)}
\text{v=shuffle(\v)}

#if defined TARGET_ineqequi1
 \text{don=\v[1]*\x+\v[2]-\v[4] \sy2 \v[3]*\x
\v[1]*\x+\v[2] \sy \v[3]*\x+\v[4]
\v[1]*\x+\v[2]-\v[4] \sy \v[3]*\x}
#endif
#if defined TARGET_ineqequi2
 \integer{r1=\v[1]-\v[3]}
 \integer{r2=\v[1]+\v[3]}
 \text{don=\r2*\x+\v[2] \sy \v[4]
\v[1]*\x+\v[2] \sy \v[3]*\x+\v[4]
\r1*\x+\v[2] \sy \v[4]}
#endif
#if defined TARGET_ineqequi3
 \integer{r1=\v[2]+\v[4]}
 \text{don=\v[1]*\x+\r1 \csy \v[3]*\x
\v[1]*\x+\v[2] \sy \v[3]*\x-\v[4]
\v[1]*\x+\r1 \sy \v[3]*\x}
#endif
#if defined TARGET_ineqequi4
 \text{r1=\v[2]/\v[1]}
 \text{don=\x \csy \r1
\v[1]*\x \sy \v[2]
\x \sy \r1}
#endif
#if defined TARGET_ineqequi5
 \text{r1=-\v[2]/\v[1]}
 \text{don=\x \sy \r1
-\v[1]*\x \sy \v[2]
\x \csy \r1}
#endif

\text{choix=}
\for{k=1 to 3}{
 \text{c=row(\k,\don)}
 \text{t=texmath(\c)}
 \text{choix=wims(append item \(\t) to \choix)}
}
\text{name_enonce=Trouver l'intrus parmi les trois inéquations suivantes&nbsp;}
\statement{
  \name_enonce:}

\choice{Intru}{\choix[1]}{\choix[2],\choix[3]}
