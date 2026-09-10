target=intminmax

#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
#include "values.inc"
#include "tablegen.inc"
#include "common.inc"
\text{name_minmax=minimum,maximum}
\matrix{name_answer=Début de \(I\) vaut
  Fin de \(I\) vaut
  Le \minimax de \(f_I\) est
  \(f_I\) atteint son,en
}

\text{size=70x40x1}
\integer{sh=random(0,1)}
\text{xint=\xmiddles[1+\sh..3+\sh;]}
\text{xint=wims(translate internal ; to , in \xint)}
\text{xint=wims(makelist \(x\) for x in \xint)}
\text{yint=item(\sh*2+1..\sh*2+6,1,1,2,2,3,3,4,4)}
\integer{o=random(1,2)}
\text{minmax=item(\o,\name_minmax)}
\text{infsup=item(\o,inf,sup)}

\integer{oo=(\o+\orient)%2}
\text{osign=item(\orient,+,-)}
\integer{ptest=\oo=1 and \sh=0?2}
\integer{ptest=\oo=1 and \sh=1?4}
\integer{ptest=\oo=0?3}
\text{mval=\ys[\ptest]}
\text{ambig=(\ptest=2 and \osign(\YY[4])>\osign(\mval)) or
   (\ptest=3 and \sh=0 and \osign(\YY[1])<\osign(\mval)) or
   (\ptest=3 and \sh=1 and \osign(\YY[5])<\osign(\mval)) or
   (\ptest=4 and \osign(\YY[2])>\osign(\mval))?yes:no}

\text{yy0=\ys[\sh[1]+1]}
\text{yys=\ymiddles[1+\sh..3+\sh;]}

\text{test1=0}
\text{nstep=r1,r2}
\nextstep{\nstep}

\statement{\intro

#include "table.inc"

\if{\step=1}{
Utilisez les valeurs proposées ci-dessous pour construire un intervalle
ouvert \(I\) tel que la restriction de \(f\) sur \(I\) atteigne son \minmax.
<div class="wimscenter">
     \(I\) = \rightbrack \embed{reply 1,\size} ,
     \embed{reply 2,\size} \leftbrack
</div>
\exit{}
}
\if{\step=2 and \test1<1}{
  Vous avez répondu : la restriction de \(f\) sur l'intervalle
  \(I\) = \rightbrack\reply1 , \reply2\leftbrack atteint son \minmax.
  \exit{}
}
Soit \(f_I\) la restriction de \(f\) sur l'intervalle \(I\) =
  \rightbrack\reply1 , \reply2\leftbrack.
  <p>
  \(f_I\) atteint son \minmax \embed{reply 3,12} en
  \embed{reply 4,12}.
  </p>
}

\answer{\name_answer[1;]}{\rep1;\xint}{type=dragfill}
\answer{\name_answer[2;]}{\rep2}{type=dragfill}

\text{rr1=wims(replace internal \ by in \rep1)}
\text{rr2=wims(replace internal \ by in \rep2)}

\text{nstep=}
\text{rleft=position(\rep1,\xint)}
\text{rright=position(\rep2,\xint)}
\if{\rr1<\rr2}{
 \text{rl=\rleft}\text{rr=\rright}
}{
 \text{rl=\rright}\text{rr=\rleft}
}
\text{Rleft=\yint[\rl]}\text{Rright=\yint[\rr]}
\text{test1=items(\rleft)=1 and items(\rright)=1 and \rr1<\rr2 and
      \Rleft<\ptest and \Rright>=\ptest?1:0}
\if{\test1>0 and (\Rleft<\ptest-1 or \Rright>\ptest) and \ambig issametext yes}{
 \text{test1=-1}
 \text{badx=\Rleft<\ptest-1?\xint[\rl]:\xint[\rr]}
}

\text{nstep=\test1>0 and \step=2?r3,r4}
\condition{L'intervalle est bon}{\test1>0}

\feedback{\rr1 > \rr2}{Vous avez écrit l'intervalle à l'envers.
Il faut placer le plus petit nombre à gauche.}

\feedback{\test1<0}{
 <strong>Attention</strong>. Votre intervalle n'est pas correct car l'existence du \minmax
 dépend de la valeur inconnue \(f_I\)(\badx)
 qui pourrait dépasser \(f_I\)(\(\xs[\ptest]\)) = \(\mval\)&nbsp;!
}

\feedback{\Rleft=\Rright}{
 D'après le tableau de variation, la fonction \(f\) est strictement
 monotone sur l'intervalle \(I\). Puisque \(I\) est ouvert,
 la restriction \(f_I\) n'a ni maximum ni minimum.
}

\feedback{\rr1 > \rr2 and \Rleft != \Rright and \test=0}{
 La restriction \(f_I\) admet un \infsup mais pas de \minmax.
}

\answer{\name_answer[3;]}{\ys[\ptest]}{type=default}
\answer{\name_answer[4;1] \minmax \name_answer[4;2]}{\xs[\ptest]}{type=default}
