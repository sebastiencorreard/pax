target=produit
#include "author.inc"
\precision{10000}
#define NUM
#include "lang_titles.inc"
#include "lang.inc"

\integer{confparm1=\confparm1=?1}
\integer{confparm2=\confparm2=?1}

\integer{confparm1=\confparm1=?1}
\text{champ=wims(record \confparm1 of src/generateur)}
\text{A=row(2,\champ)}
\text{B=row(3,\champ)}
\text{c=item(3,\A)}
\if{\B=}{
\text{a=item(1,\A)}
\text{b=item(2,\A)}
\if{\c<0}{
\text{valeurs=wims(values \c*v,-(\c)*v for v=\a to \b)}
}{
\text{valeurs=wims(values \c*v for v=\a to \b)}
}
}{
\text{valeurs=\B}
\if{\c<0}
{\text{tmp=wims(replace internal , by ,- in \valeurs)}
\text{valeurs=wims(listunion \valeurs and \tmp)}
}
}
\text{valeurs=wims(listuniq \valeurs)}
\text{valeurs=shuffle(\valeurs)}
\text{b=item(2,\valeurs)}
\text{c=item(3,\valeurs)}
\text{d=item(4,\valeurs)}
\text{f=item(6,\valeurs)}
\text{a=random(-1,1)*(\b)}
\text{a=simplify(\a)}
\text{e=random(-1,1)*(\c)}
\text{e=simplify(\e)}

\text{x=randitem(x,y,z,a,b)}
\text{A=randitem(A,B,F,E,C)}

\text{BB=simplify((\b)^2)}
\text{CC=simplify((\c)^2)}
\text{terme=texmath(\BB*\x^2-(\CC))}
\text{rds=randitem(+1,-1)}
\text{cal=(\BB)*\x^2-(\CC)+(\rds)*((\a)*\x+(\e))*((\d)*\x+(\f))}
\text{enonce=texmath(\cal)}

\text{rep1=maxima(expand(\cal);)}
\text{rep2=maxima(factor( (\BB)*\x^2-(\CC) );)}
\text{rep3=maxima(factor(\cal);)}

\text{ea=simplify((\a)/(\b))}
\text{ee=simplify((\e)/(\c))}
\text{ft1=simplify(-(\ee)*(\ea)*(\c)/(\b))}
\text{ft2=simplify(((\ea)*(\ee)*(\c)-(\ea)*(\rds)*(\f))/((\b)+(\ea)*(\rds)*(\d)))}

\statement{<div class="wimscenter">\(\A=\enonce\)</div>
<ul><li>
\name_Question 1 : \name_question[1] \(\A\).
</li><li>
\name_Question 2 : \name_question[2] \(\terme\).
</li><li>
\name_Question 3 : \name_question[3] \(\A\).
</li><li>
\name_Question 4 : \name_question[4] \(\A=0\) ?
</li></ul>
<div class="wims_instruction">\name_instruction</div>}

\answer{Réponse 1}{\rep1}{type=algexp}
\answer{Réponse 2}{\rep2}{type=algexp}
\answer{Réponse 3}{\rep3}{type=algexp}
\answer{Réponse 4}{\ft1,\ft2}{type=set}
