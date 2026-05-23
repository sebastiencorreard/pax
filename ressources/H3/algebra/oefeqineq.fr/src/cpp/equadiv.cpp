target=equadiv

\language{fr}
\author{Paul,Byache}
\email{paul-marcel-rog.byache@ac-aix-marseille.fr}
maintainer: WIMS EDU
\format{html}
#define NUM
#include "lang_titles.inc"
#include "lang.inc"

\integer{sizef=4}
\integer{confparm1=\confparm1=?1}
\integer{confparm2=\confparm2=?1}

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
  \if{\c<0}{
    \text{tmp=wims(replace internal , by ,- in \valeurs)}
    \text{valeurs=wims(listunion \valeurs and \tmp)}
  }
}
\text{valeurs=wims(listuniq \valeurs)}
\text{valeurs=shuffle(\valeurs)}
\text{a=item(1,\valeurs)}
\text{b=item(2,\valeurs)}

\text{x=random(x,y,z,a,b)}

!!on aura une equation du type : c/b=a

\if{\confparm1>4}{
!! correctif de bug d'affichage en cas d'usage des décimaux (FG)
  \integer{ta=(\a)*100}
  \integer{tb=(\b)*100}
  \integer{t=\ta*\tb}
  \text{c=slib(decimal \t,4)}
}{
  \text{c=simplify((\a)*(\b))}
}

!!definition de l'inconnue et de la solution \par
\matrix{A=\a,\b,\c}
\integer{choix=random(3)}
\text{sol=\A[\choix]}
\matrix{B = pari (A = Mat([\A]); A[1,\choix]=\x; print(A))}
\text{enonce = \frac{texmath(\B[3])}{texmath(\B[2])} = texmath(\B[1])}
\statement{\name_question[1] \(\enonce\). \name_question[2] \(\x\)
<label for="reply1">\name_question[3]</label> ? \embed{r1,5}.
}

\answer{}{\sol}{type=numexp}
