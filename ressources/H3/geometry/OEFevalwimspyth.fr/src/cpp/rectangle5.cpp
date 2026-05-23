target=rectangle5
\title{Rectangle ou non 5}
#include "author.inc"
\integer{ch=randint(1..2)}
\integer{a=randint(100..250)}
\integer{b=randint(300..500)}
\integer{c=\ch=1?\a+\b:\a+\b+randint(100..200)}
\text{bad=Non,Oui}
\text{good=item(\ch,\bad)}
\text{namecolor=bleu,rouge,vert,jaune,violet}
\text{color=blue,red,green,yellow,purple}
\text{randcol=shuffle(1,2,3,4,5)}

\text{dessin=draw(190,210
fpoly \color[\randcol[1]],10,80,60,80,60,130,10,130
fpoly \color[\randcol[2]],60,130,60,200,130,200,130,130
fpoly \color[\randcol[3]],130,130,180,60,110,10,60,80
fpoly \color[\randcol[4]],60,80,60,130,130,130)}

\text{bad=Oui,Non}
\text{good=item(\ch,\bad)}


\statement{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\dessin" alt="">
 <div class="wims_instruction">La figure n'est pas à l'échelle.</div></div>
 <div class="medium_size text_col">
  Les surfaces \namecolor[\randcol[1]], \namecolor[\randcol[2]], \namecolor[\randcol[3]]
  sont des carrés.
  Les mesures de leur aire respective sont données ci-dessous :
  <ul>
   <li>Le carré \namecolor[\randcol[1]] : \a \(cm^2).</li>
   <li>Le carré \namecolor[\randcol[2]] : \b \(cm^2).</li>
   <li>Le carré \namecolor[\randcol[3]] : \c \(cm^2).</li>
  </ul>
   Le triangle \namecolor[\randcol[4]] est-il rectangle ?
    </div>
  </div>
}
\choice{}{\good}{\bad}
