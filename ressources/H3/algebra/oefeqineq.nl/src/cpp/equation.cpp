target=Equation3,Equation4,optrou3,optrou4,optrou5

\language{fr}
\range{-5..5}
\author{Guerimand Fabrice}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}

\integer{sizef=4}

\integer{confparm1=\confparm1=?1}
\integer{confparm2=\confparm2=?1}


#include "valeurs.inc"

\text{a=item(1,\valeurs)}
\text{b=item(2,\valeurs)}
\text{x=randitem(x,y,z,a,b)}

#if #TARGET (Equation3)
   \title{ax&#61;b}
   \text{tmp=simplify(\a*\b)}
   \text{d=\b}
   \text{enonce=\a*\x = \tmp}
   \integer{test=1}
#endif

#if #TARGET (Equation4)
   \title{x+a&#61;b}
   \text{d=simplify((\b)-(\a))}
   \text{enonce=\x+(\a)=\b}
   \integer{test=1}
#endif

#if #TARGET (optrou3)
   \title{Vermenigvuldiging met gaten}
   \text{tmp=simplify((\b)*(\a))}
   \text{d=\b}
   \text{enonce1=\textmath(\a)\times}
   \text{enonce2=texmath(=\tmp)}
   \integer{test=0}
#endif

#if #TARGET (optrou4)
   \title{Optelling met gaten}
   \text{d=simplify(\b-\a)}
   \text{enonce1=texmath(\a)+}
   \text{enonce2=texmath(=\b)}
   \integer{test=0}
#endif

#if #TARGET (optrou5)
   \title{Verschil met gaten}
   \text{d=simplify(\a-(\b))}
   \text{enonce1=texmath(\a)-}
   \text{enonce2=texmath(=\b)}
   \integer{test=0}
#endif

\text{enonce=texmath(\enonce)}

\statement{\if{\test=1}
{Los vergelijking \(\enonce) op. <p>Geef je antwoord in de vorm van een vereenvoudigde breuk.<br>\(\x =) \embed{reply 1,\sizef}}
{Vul het ontbrekend getal in : \(\enonce1) \embed{reply 1,\sizef } \(\enonce2)}}

\answer{Antwoord }{\d}{type=algexp}
