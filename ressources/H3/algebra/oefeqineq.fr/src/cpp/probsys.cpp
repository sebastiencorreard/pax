target=probsys probsys2
#include "author.inc"
#if defined TARGET_probsys
# define NUM 1
#endif
#if defined TARGET_probsys2
# define NUM 2
#endif
#include "lang_titles.inc"

\precision{10000}

\text{genre=randitem(boy,girl)}
\text{noms=slib(lang/fname fr,\genre,2)}
\text{prenom1=item(1,\noms)}
\text{prenom2=item(2,\noms)}
#if defined TARGET_probsys
\integer{prixA=randint(7..30)}
\integer{prixB=randint(7..30)}
#endif
#if defined TARGET_probsys2
\integer{prixA=randint(15..30)}
\integer{prixB=randint(15..30)}
#endif
\if{\prixA=\prixB}{
#if defined TARGET_probsys
  \integer{prixA=7}
  \integer{prixB=12}
#endif
#if defined TARGET_probsys2
\integer{prixA=17}
\integer{prixB=22}
#endif
}
#if defined TARGET_probsys
\text{t=shuffle(7)}
#endif
#if defined TARGET_probsys2
\real{prixA=\prixA/10}
\real{prixB=\prixB/10}
\text{t=shuffle(2,3,4,5,6,7)}
#endif
\integer{nbA1=\t[1]}
\integer{nbA2=\t[2]}
\integer{nbB1=\t[3]}
\integer{nbB2=\t[4]}
\integer{nbB2=\nbA1*\nbB2-\nbA2*\nbB1=0?\nbB2+1}

\real{total1=\nbA1*\prixA+\nbB1*\prixB}
\real{total2=\nbA2*\prixA+\nbB2*\prixB}
w
#include "lang.inc"
\statement{<div>\enonce
<p>\enonce2</p>
</div>
<ul>
<li><label for="reply1">\name_prix[1] \listnoms[1]</label> : \embed{r1,10} euros</li>
<li><label for="reply2">\name_prix[2] \listnoms[2]</label> : \embed{r2,10} euros</li>
</ul>}

\reply{\name_prix[1] \listnoms[1]}{\prixA}{type=auto}
\reply{\name_prix[2] \listnoms[2]}{\prixB}{type=auto}
