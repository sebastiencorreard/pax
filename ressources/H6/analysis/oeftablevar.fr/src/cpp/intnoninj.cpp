target=intnoninj

#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
#include "values.inc"
#include "tablegen.inc"
#include "common.inc"

\text{size=70x40x1}
\integer{sh=random(1,2,3)}
\text{sh=\sh,\sh+1}
\text{int=\sh[1],\sh[1],\sh[2],\sh[2]}
\text{xint=\xmiddles[\sh[1];],\xmiddles[\sh[2];]}
\text{xint=wims(makelist \(x) for x in \xint)}
\text{yy0=\ys[\sh[1]+1]}
\text{yy1=\ymiddles[\sh[1];random(1,2)]}
\text{yy2=\ymiddles[\sh[2];random(1,2)]}

\text{reasons=\name_reasons}
\integer{reasoncnt=items(\reasons)}
\text{sh=shuffle(\reasoncnt)}
\text{reasons=\reasons[\sh]}
\text{goodreason=position(1,\sh)}
\text{test1=0}
\text{test2=0}

\text{nstep=r1,r2}
\nextstep{\nstep}

\statement{\intro

#include "table.inc"

\if{\step=1}{
  Utilisez les valeurs proposées ci-dessous pour construire un intervalle
  ouvert \(I\) tel que la restriction de \(f\) sur \(I\) soit non injective.
  <div class="wimscenter">
       \(I\) = \rightbrack \embed{reply 1,\size} ,
       \embed{reply 2,\size} \leftbrack
  </div>
  \exit{}
}
\if{\step=2 and \test1<1}{
  Vous avez répondu : la restriction de \(f\) sur l'intervalle
  \(I\) = \rightbrack\reply1 , \reply2\leftbrack n'est pas injective.
  \exit{}
}
Soit \(f_I\) la restriction de \(f\) sur l'intervalle \(I\) =
  \rightbrack\reply1 , \reply2\leftbrack.
\if{\step>2}{<p>Nous avons \(f\)(\reply1) = \(\yy1\), \(f\)(\reply2) = \(\yy2\).}
 </p>
\if{\step=2}{
  \if{\reply3 notsametext \empty and \reply3 != \goodreason}{
    Mauvaise raison de non injectivité.
  }{
   Pourquoi \(f_I\) n'est-elle pas injective&nbsp;?
   <ul>
   \for{t=1 to \reasoncnt}{
    <li>\embed{reply 3,\t}
   }
   </ul>
  }
  \exit{}
}
  \if{\step=3}{
    Pour justifier que \(f_I\) n'est pas injective,
    donnez une valeur dans l'image de \(f_I\)
    qui a plusieurs antécédents&nbsp;:
    \embed{reply 4,6}
    \exit{}
  }
}

\answer{\name_answer[1]}{\rep1;\xint}{type=dragfill}
\answer{\name_answer[2]}{\rep2}{type=dragfill}

\text{rr1=wims(replace internal \ by in \rep1)}
\text{rr2=wims(replace internal \ by in \rep2)}

\text{nstep=}
\text{Rleft=position(\rep1,\xint)}
\text{Rright=position(\rep2,\xint)}
\text{test1=items(\Rleft)=1 and items(\Rright)=1 and \Rleft<=2 and \Rright>=3?1:0}
\if{\rr1 > \rr2}{
 \text{R1=\rep2}
 \text{R2=\rep1}
}{
 \text{R1=\rep1}
 \text{R2=\rep2}
}

\text{nstep=\test1>0 and \step=2?r3:}
\condition{L'intervalle est bon}{\test1>0}
\feedback{\rr1 > \rr2}{Vous avez écrit l'intervalle à l'envers !
Il faut placer le plus petit nombre à gauche.}
\feedback{\Rleft<=2 and \Rright<=2 or \Rleft>=3 and \Rright>=3}{
 D'après le tableau de variation,
 \(f\) est strictement monotone dans \rightbrack\R1 , \R2\leftbrack. Elle est donc
 injective dans cet intervalle !
}

\answer{\name_answer[3]}{\goodreason;\reasons}
{type=radio}

\answer{\name_answer[4]}{\rep4}{type=number}

\text{nstep=\step=3?r4}

\if{\test1>0}{
 \if{\yy1<\yy0 and \rep4 < \yy0 and \rep4 > \yy1 and \rep4 > \yy2 or
     \yy1>\yy0 and \rep4 > \yy0 and \rep4 < \yy1 and \rep4 < \yy2} {
  \text{test2=1}
 }{
  \if{\yy1<\yy0 and (\rep4 > \yy0 or \rep4 <= min(\yy1,\yy2)) or
      \yy1>\yy0 and (\rep4 < \yy0 or \rep4 >= min(\yy1,\yy2))}{
    \text{test2=-2}
   }{
    \text{test2=-1}
   }
 }
}

\condition{\(\rep4\) a plusieurs antécédents}{\test2>0}

\feedback{\test2=-2}{La valeur \(\rep4\) n'est même pas dans l'image
 de \(f_I\). Vous avez probablement confondu le domaine de définition
 de \(f_I\) et son image.
}

