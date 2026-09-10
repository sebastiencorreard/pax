target=pourcentage2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}
\integer{n=randint(10..90)}
\text{u=randint(1..5)}
\text{longueur=item(\u,\name_longueur)}
\text{genre=\name_genre[\u]}
\text{l=item(\u,l,v,h,m,p)}
\text{choix=random(1,-1)}
\text{rep0=\choix=1 ? 1:2}
\text{augmen=\name_augmen}
\text{augmente=\choix=1 ? item(1,\augmen):item(2,\augmen)}
\text{augmen2=\choix=1 ? \name_augmen2[1]: \name_augmen2[2]}
\text{multiplie=\name_multiplie[\genre]}
\real{rep=(100+(\choix)*\n)/100}
\steps{reply1
reply2}
\statement{
\name_enonce[1] \longueur \name_enonce[2]
  \multiplie
 \name_enonce[3] \rep.
\if{\step<=1}{
  \name_question1[1] \embed{reply 1,1} \name_question1[2] \embed{reply 1,2} ?
}
\if{\step=2}{<p>\name_question[1] \augmen2 \name_question[2]</p>}
}
\answer{\name_answer[1]}{\rep0;\augmen}{type=radio}
\answer{\name_augmen3[\rep0] %}{\n}{type=numeric}
