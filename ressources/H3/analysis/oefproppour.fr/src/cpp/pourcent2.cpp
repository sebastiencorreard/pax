target=pourcent2

#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\precision{10000}

\integer{size=6}

\text{donnees=randint(1..9)/10,randint(12..99)/100,randint(12..99)/10000,randint(12..99)/1000,randint(101..999)/1000}
\text{donnees=shuffle(\donnees)}

\text{enonce=}
\text{rep=}
\for{i=1 to 6}{
 \integer{ent=randitem(0,1,2)}
 \real{nombre=item(\i,\donnees)+\ent}
 \real{sol=\nombre*100}
 \text{enonce=wims(append item \nombre to \enonce)}
 \text{rep=wims(append item \sol to \rep)}
}

\statement{
\name_enonce:
<div class="wimscenter">
\special{mathmlinput [\begin{matrix}
\enonce[1] &=& \frac{reply1}{100}&\enonce[2] &=& \frac{reply2}{100}\\\
  \enonce[3] &=&\frac{reply3}{100}&\enonce[4] &=& \frac{reply4}{100}\\\
  \enonce[5] &=& \frac{reply5}{100}&\enonce[6] &=& \frac{reply6}{100}
\end{matrix}
], \size
reply1
reply2
reply3
reply4
reply5
reply6}
</div>
}

\answer{\enonce[1]}{\rep[1]}{type=numexp}
\answer{\enonce[2]}{\rep[2]}{type=numexp}
\answer{\enonce[3]}{\rep[3]}{type=numexp}
\answer{\enonce[4]}{\rep[4]}{type=numexp}
\answer{\enonce[5]}{\rep[5]}{type=numexp}
\answer{\enonce[6]}{\rep[6]}{type=numexp}

\latex{
\begin{statement}
\name_enonce:
\begin{enumerate}
\item \enonce[1] = \(\frac{\phantom{-------}}{100}\)
\item \enonce[2] = \(\frac{\phantom{-------}}{100}\)
\item \enonce[3] = \(\frac{\phantom{-------}}{100}\)
\item \enonce[4] = \(\frac{\phantom{-------}}{100}\)
\item \enonce[5] = \(\frac{\phantom{-------}}{100}\)
\item \enonce[6] = \(\frac{\phantom{-------}}{100}\)
\end{enumerate}
\end{statement}
}
