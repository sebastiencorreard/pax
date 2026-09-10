target=transfmult
#define NUM
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\precision{10000}

\integer{n=randint(2..4)}
\integer{a=random(1,-1)*randint(2,3,5,7)}
\integer{b=random(1,-1)*randint(2,6,4,11)}
\integer{c=random(1,-1)*randint(2,3,5,7)}
\integer{d=random(1,-1)*randint(3,4,8)}

\text{choix1=random(1,2)}
\text{choix2=random(1,2)}
\text{choix3=random(1,2)}
\text{sol=\choix1=1 and \choix2=1 and \choix3=1 ? pari(\a*(\c)/((\b)*(\d)))}
\text{sol=\choix1=1 and \choix2=2 and \choix3=1 ? pari(\a*(\d)/((\b)*(\c)))}
\text{sol=\choix1=1 and \choix2=1 and \choix3=2 ? pari((\a*(\c)/((\b)*(\d)))^(-1))}
\text{sol=\choix1=1 and \choix2=2 and \choix3=2 ? pari((\a*(\d)/((\b)*(\c)))^(-1))}
\text{sol=\choix1=2 and \choix2=1 and \choix3=1 ? pari(\b*(\c)/((\a)*(\d)))}
\text{sol=\choix1=2 and \choix2=1 and \choix3=2 ? pari((\b*(\c)/((\a)*(\d)))^(-1))}
\text{sol=\choix1=2 and \choix2=2 and \choix3=1 ? pari(\b*(\d)/((\a)*(\c)))}
\text{sol=\choix1=2 and \choix2=2 and \choix3=2 ? pari((\b*(\d)/((\a)*(\c)))^(-1))}
\text{den=pari(denominator(\sol))}
\text{num=pari(numerator(\sol))}

\text{multiplie=item(\choix1,\multdiv)}
\text{divise=item(\choix2,\multdiv)}
\text{multip=item(\choix3,\multidivi)}

\statement{\name_statement[1] \multiplie \name_statement[2]
\(\frac{\a}{\b}\) \name_statement[3] \divise \name_statement[4] \(\frac{\c}{\d}\)&nbsp;?
 <p>\name_statement[5] \multip \name_statement[6]</p> <table class="wimscenter"><tr><td>\embed{reply 1, 4}</td></tr>
<tr><td><hr></td></tr>
<tr><td>\embed{reply 2, 4}</td></tr></table>.
}
\answer{\name_num}{\num1}{type=numeric}
\answer{\name_den}{\den1}{type=numeric}
\text{reponse=pari(if(\den1!=0,\num1/\den1-(\sol),1000))}
\condition{\name_statement[5] \multip \name_statement[6] \num1/\den1 ?}{\reponse=0}
\text{pgc=pari(gcd(\num1,\den1))}
\feedback{\reponse=0 and \pgc <>1}{<div class="wimscenter">\name_feed</div>}

\latex{
\begin{statement}
\name_statement[1] \multiplie \name_statement[2]
\(\frac{\a}{\b}\) \name_statement[3] \divise \name_statement[4] \(\frac{\c}{\d}\)&nbsp;?
 \par \name_statement[5] \multip \name_statement[6] \(\dots\dots\)
\end{statement}
\begin{solution}
\(\frac{\num1}{\den1}\)
\end{solution}
}
