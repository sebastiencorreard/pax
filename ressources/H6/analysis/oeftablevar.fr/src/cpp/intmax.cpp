target=intmax intmax2

#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_intmax
 \steps{r1,r2,r3,r4
 r5,r6,r7,r8
 }
#endif
#if defined TARGET_intmax2
 \steps{r1,r2,r3,r4
 r5,r6,r7,r8
 r9
 r10,r11
 r12,r13,r14,r15, r16,r17,r18,r19
 r20,r21,r22,r23
 }
#endif

#include "values.inc"
#include "tablegen.inc"
#include "common.inc"

\text{bsize=20x30x1}
\text{size2=100x30x4}
\text{fsize=10}
\integer{midterm=random(1..4)}
\text{xint=\xmiddles[\midterm;random(1,2)]}
\text{yint=\ymiddles[\midterm;random(1,2)]}

\text{bracks=\leftbrack,\rightbrack}
\text{lbrind=\midterm=1?2:1}
\text{rbrind=\midterm=4?2:1}
\text{lbr=\bracks[\lbrind]}
\text{rbr=\bracks[3-\rbrind]}
\text{leftx=\xshow[\midterm]}
\text{rightx=\xshow[\midterm+1]}
\text{Leftx=\midterm=1?-inf:\xs[\midterm]}
\text{Rightx=\midterm=4?inf:\xs[\midterm+1]}
\text{lefty=\arrows[\midterm] issametext ne?\ys[\midterm]:\ys[\midterm+1]}
\text{righty=\arrows[\midterm] issametext ne?\ys[\midterm+1]:\ys[\midterm]}
\text{Lefty=wims(replace internal \infty by inf in \lefty)}
\text{Righty=wims(replace internal \infty by inf in \righty)}
\text{lbr2=\arrows[\midterm] issametext ne?\lbr:\bracks[\rbrind]}
\text{rbr2=\arrows[\midterm] issametext ne?\rbr:\bracks[3-\lbrind]}
\text{croiss=\arrows[\midterm] issametext ne?croissante:décroissante}
\text{badcroiss=wims(listcomplement \croiss in croissante,décroissante)}
\text{jective=injective mais pas surjective,
surjective mais pas injective,injective et surjective
donc bijective,ni injective ni surjective}
\text{yesno=Oui. Toujours, Non. Jamais, Cela dépend de \(f)}

\statement{\intro
#include "table.inc"

  Déterminez l'intervalle maximal \(I\) contenant le nombre \(\xint\),
sur lequel la restriction de \(f\) est injective.

\if{\step=1}{
<div class="wimscenter">
 \(I\) = \embed{r1,\bsize}\embed{r2,\fsize} , \embed{r3,\fsize}\embed{r4,\bsize}
</div>
<div class="wims_instruction">
Tapez <span class="tt">inf</span> pour \infty.
</div>
\exit{}
}
<div class="wimscenter">
 \(I\) = \lbr\leftx , \rightx\rbr
</div>
\if{\step<=3}{
Soit \(f_I\) la restriction de \(f\) sur \(I\). Quelle est l'image de
\(f_I\)&nbsp;?
\if{\step=2}{
<div class="wimscenter">
 image(\(f_I\)) = \embed{r5,\bsize}\embed{r6,\fsize} , \embed{r7,\fsize}\embed{r8,\bsize}
</div>
<div class="wims_instruction">
Tapez <span class="tt">inf</span> pour \infty.
</div>
\exit{}
}
<div class="wimscenter">
 image(\(f_I\)) = \lbr2\(\lefty) , \(\righty)\rbr2
</div>
\if{\step=3}{
Quelle est la nature de la restriction \(f_I\): \(I -> f(I)\)&nbsp;?
<p>
Elle est \embed{r9}.
</p>
\exit{}
}}
Soit \(f_I\): \(I ->\) \lbr2\(\lefty\) , \(\righty\)\rbr2 la restriction de
\(f\).
\if{\step=4}{
<ul>
<li>Pourquoi \(f_I\) est-elle injective ? Parce qu'elle est
\embed{r10,\size2}. </li>
<li>Pourquoi \(f_I\) est-elle surjective ? Parce qu'elle est
\embed{r11,\size2}.</li>
</ul>
\exit{}
}
<p>
\(f_I\) est bijective, donc elle admet une fonction réciproque
</p> <div class="wimscenter">
\if{\step=5}{
 \(f_I^{-1}\): \embed{r12,\bsize}\embed{r13,\fsize} ,
 \embed{r14,\fsize}\embed{r15,\bsize}
 \(->\)
 \embed{r16,\bsize}\embed{r17,\fsize} , \embed{r18,\fsize}\embed{r19,\bsize} .
 </div>
<div class="wims_instruction">
 Tapez <span class="tt">inf</span> pour \infty.
 </div>
 \exit{}
}
<div>
 \(f_I^{-1}\): \lbr2\(\lefty\) , \(\righty\)\rbr2 \(-> I\).
</div class="wimscenter">
\(f_I^{-1}\) est \embed{r20} et
\embed{r21,100x30x2}.
<ul><li>
Est-elle partout continue ? \embed{r22}
</li><li>
Est-elle partout dérivable ? \embed{r23}
</li></ul>
}

\answer{Crochet à gauche de I}{\lbr;\bracks}{type=clickfill}
\answer{Début de I}{\Leftx,inf}{type=function}
\answer{Fin de I}{\Rightx,inf}{type=function}
\answer{Crochet à droite de I}{\rbr;\bracks}{type=clickfill}
\answer{Crochet à gauche de f(I)}{\lbr2;\bracks}{type=clickfill}
\answer{Début de f(I)}{\Lefty,inf}{type=function}
\answer{Fin de f(I)}{\Righty,inf}{type=function}
\answer{Crochet à droite de f(I)}{\rbr2;\bracks}{type=clickfill}
\answer{Nature de \(f_I\)}{3;\jective}{type=menu}
\answer{\(f_I\) est injective car elle est}{strictement,\croiss;\badcroiss,dérivable,et}{type=clickfill}
\answer{\(f_I\) est surjective car elle est}{continue}{type=clickfill}
\answer{Domaine de \(f_I^{-1}\), crochet 1}{\lbr2;\bracks}{type=clickfill}
\answer{Domaine de \(f_I^{-1}\) gauche}{\Lefty,inf}{type=function}
\answer{Domaine de \(f_I^{-1}\) droite}{\Righty,inf}{type=function}
\answer{Domaine de \(f_I^{-1}\), crochet 2}{\rbr2;\bracks}{type=clickfill}
\answer{Image \(f_I^{-1}\), crochet 1}{\lbr}{type=clickfill}
\answer{Image de \(f_I^{-1}\) gauche}{\Leftx,inf}{type=function}
\answer{Image de \(f_I^{-1}\) droite}{\Rightx,inf}{type=function}
\answer{Image \(f_I^{-1}\), crochet 2}{\rbr}{type=clickfill}
\answer{Nature de \(f_I^{-1}\)}{3;\jective}{type=menu}
\answer{Croissance de \(f_I^{-1}\)}{strictement,\croiss;
\badcroiss}{type=clickfill}
\answer{Continuité de \(f_I^{-1}\)}{1;\yesno}{type=menu}
\answer{Dérivabilité de \(f_I^{-1}\)}{2;\yesno}{type=menu}

