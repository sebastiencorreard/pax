target=mediane5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{eff=19+2*randint(1..4)}
\integer{maxscore=randitem(1,2)}
\integer{nb=5}

\text{E=slib(generator \nb,\eff)}
\integer{maxscore=10*\maxscore}
\text{min=wims(values \maxscore/5*v for v=0 to 6)}

\integer{ch=randint(1..2)}
\integer{toc=\ch=1?0:\eff}
\text{sg=\ch=1?+:-}
\text{coord=\min[1],\toc}
\text{valeurs=}
\real{lar=\maxscore/5}
\integer{init=\ch=1?0:-1}
\for{k=1 to \nb}{
 \integer{toc=\toc\sg\E[\k]}
 \text{tmp=wims(values \min[\k]+\lar/\E[\k]*(v+\init) for v=1 to \E[\k])}
 \text{valeurs=wims(append item \tmp to \valeurs)}
 \text{coord=\coord,\min[\k+1],\toc}
}
\integer{med=slib(stat/median [\valeurs])}

\text{dessin=slib(lgbrisee \name_head[1],\nameclass,\coord)}
\text{figure=draw(400,400
\dessin)}
\text{sens=\ch=1?\name_sens[1]:\name_sens[2]}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\figure" alt=""></div>
  <div class="medium_size text_col">
  \name_enonce[1] \maxscore.<br>\name_enonce[2] \eff \name_enonce[3]
  <table class="wimscenter wimsborder">
   <tr>
    <th>\nameclass</th>
    <th>\name_head[2]</th>
   </tr>
   \for{l=1 to \nb}{<tr>
    <td>\(\min[\l] \leq N < \min[\l+1])</td>
    <td>\E[\l]</td>
   </tr>}
  </table>
\name_enonce[4] \sens \name_enonce[5]<br>
\name_question ?
<div class="wims_instruction">\name_inst</div>
 </div>
</div>
}

\answer{\name_head[2]}{\med}{type=numexp}
