target=intinj

#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
#include "values.inc"
#include "tablegen.inc"
#include "common.inc"
\text{size=70x40x1}
\integer{sh=random(1,2,3,4)}
\text{xint=\xmiddles[;1],\xmiddles[\sh;2]}
\text{xint=wims(makelist \(x) for x in \xint)}
\text{yint=1,2,3,4,\sh}
\text{gooddir=\arrows[\sh] issametext ne?\name_creasing[1]:\name_creasing[2]}
\text{baddir=\arrows[\sh] issametext se?\name_creasing[1]:\name_creasing[2]}

\text{test1=0}
\text{nstep=r1,r2}
\nextstep{\nstep}

\statement{\intro

#include "table.inc"

\if{\step=1}{
  \name_question1
  <div class="wimscenter">
     \(I) = \rightbrack \embed{reply 1,\size} ,
     \embed{reply 2,\size} \leftbrack
</div>
\exit{}
}
\if{\step=2 and \test1<1}{
  Vous avez répondu : la restriction de \(f) sur l'intervalle
  \(I) = \rightbrack\reply1 , \reply2\leftbrack est injective.
  \exit{}
}
  Soit \(f_I) la restriction de \(f) sur l'intervalle \(I) =
  \rightbrack\reply1 , \reply2\leftbrack.
  <br>
  Justifiez : \(f_I\) est injective parce qu'elle est
  <div class="center">\embed{reply 3,120x30x5}.</div>
}

\answer{\name_answer[1] \(I\)}{\rep1;\xint}{type=dragfill}
\answer{\name_answer[2] \(I\)}{\rep2}{type=dragfill}

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
      \Rleft=\Rright?1:0}

\text{nstep=\test1>0 and \step=2?r3}
\condition{L'intervalle est bon}{\test1>0}

\feedback{\rr1 > \rr2}{Vous avez écrit l'intervalle à l'envers.
Il faut placer le plus petit nombre à gauche.}

\feedback{\Rleft<\Rright}{
 D'après le tableau de variation, \(f_I\) n'est pas monotone. Et une
 fonction continue et non monotone ne peut pas être injective.
}

\answer{Raison pour l'injectivité}
{strictement,\gooddir;\baddir,continue,et,dérivable}{type=clickfill}

\feedback{\test1>0 and \gooddir isitemof \reply3 and
	(continue isitemof \reply3 or dérivable isitemof \reply3)}{
 Pour qu'une fonction soit injective, il suffit qu'elle soit
 strictement monotone. Ni la continuité ni la dérivabilité n'est
 nécessaire pour assurer l'injectivité.
}

\feedback{\test1>0 and \reply3 issametext \gooddir}{
 Une fonction \gooddir mais pas strictement \gooddir n'est pas
 injective. Pensez à une fonction constante. Elle
 est à la fois croissante et décroissante, mais évidemment pas
 injective.
}
