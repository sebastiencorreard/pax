target= resoudre1 resoudre2 resoudre3

\language{nl}
\range{-5..5}
\author{Guerimand Fabrice}
\email{fwguerima@free.fr}
\translator{Reinie Erne}
\computeanswer{no}
\format{html}
\precision{10000}

\integer{confparm1=\confparm1=?1}
\integer{confparm2=\confparm2=?1}

#include "valeurs.inc"

\text{a=item(1,\valeurs)}
\text{b=item(2,\valeurs)}
\text{c=item(3,\valeurs)}
\text{d=item(4,\valeurs)}
\text{e=item(5,\valeurs)}
\text{f=item(6,\valeurs)}
\text{var=randitem(x,y,a,b)}

#if #TARGET (resoudre1)
\title{Vergelijking met product 1}

\text{tmp1=\a*\var+(\b)}
\text{tmp2=\c*\var+(\d)}
\text{tmp3=\e*\var+(\f)}
\if{\c+(\e)=0 or  \c-(\e)=0}{\text{e=2}\text{c=3}}

\matrix{donnees=(\tmp1)*(\tmp2)=0,simplify(-(\b)/(\a)),simplify(-(\d)/(\c))
(\tmp1)*(\tmp2)+(\tmp3)*(\tmp1)=0,simplify(-(\b)/(\a)),simplify(-(\d+(\f))/(\c+(\e)))
(\tmp1)*(\tmp2)-(\tmp3)*(\tmp1)=0,simplify(-(\b)/(\a)),simplify(-(\d-(\f))/(\c-(\e)))}
#endif

#if #TARGET (resoudre2)
\title{x^2-b^2&#61;0}
\text{A=simplify((\a)^2)}
\text{B=simplify((\b)^2)}
\matrix{donnees=\A*\var^2-(\B)=0,simplify(-(\b)/(\a)),simplify((\b)/(\a))
\var^2-(\B)=0,simplify(-\b),simplify(\b)
\B-(\A)*\var^2=0,simplify(-(\b)/(\a)),simplify((\b)/(\a))
\B-\var^2=0,simplify(-\b),simplify(\b)}
#endif

#if #TARGET (resoudre3)
\title{x^2-b&#61;0}
\text{A=simplify((\a)^2)}
\text{b=simplify(abs(\b))}
\matrix{donnees=\A*\var^2-\b=0,simplify(-sqrt(\b)/(\a)),simplify(sqrt(\b)/(\a))
\var^2-\b=0,simplify(-sqrt(\b)),simplify(sqrt(\b))
\a*\var^2-\b=0,simplify(-sqrt((\b)/(\a))),simplify(sqrt((\b)/(\a)))
\b-\A*\var^2=0,simplify(-sqrt(\b)/(\a)),simplify(sqrt(\b)/(\a))
\b-\var^2=0,simplify(-sqrt(\b)),simplify(sqrt(\b))
\b-\a*\var^2=0,simplify(-sqrt((\b)/(\a))),simplify(sqrt((\b)/(\a)))}
#endif

\text{don=randrow(\donnees)}
\text{enonce=texmath(item(1,\don))}
\text{rep=wims(item 2 to -1 of \don)}

\statement{Los de volgende vergelijking op :
<center>\(\enonce)</center>
(als er meerdere oplossingen zijn, scheid ze dan van elkaar met  komma's; 
als je een vierkantwortel nodig hebt, schrijf die dan als sqrt(...))}

\answer{\var}{\rep}{type=fset}
