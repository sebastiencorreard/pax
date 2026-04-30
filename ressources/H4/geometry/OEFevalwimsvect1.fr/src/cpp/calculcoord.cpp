target=calculcoord1 calculcoord2 calculcoord3 calculcoord4 calculcoord5
\language{fr}
\range{-5..5}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}
#define TITLE Calculs avec des coordonnées
\integer{mid=8}
\integer{range=\mid*2}
\integer{a1=2*random(-\mid..\mid-2)+1}
\integer{b1=2*random(-\mid..\mid)}
\integer{a2=random(-\range..\range)}
\integer{b2=2*random(-\mid..\mid-2)+1}
\integer{a=random(2..\range)*random(-1,1)}
\integer{b=random(2..\range)*random(-1,1)}
\integer{xa=random(-\range..\range)}
\integer{ya=random(-\range..\range)}
\integer{xb=random(-\range..\range)}
\integer{yb=random(-\range..\range)}
\if{\xa=\xb and \ya=\yb}
 {
 \integer{xa=\xa+1}
 \integer{ya=\ya-2}
 }
 #if defined TARGET_calculcoord1
 \title{TITLE I}
 \integer{k=random(1..4)}
 \text{lstquest=les coordonnées du vecteur \(\overrightarrow{A B}),
  les coordonnées du vecteur \(\overrightarrow{B A}),
  les coordonnées du milieu \(I\) du segment &#91;A B&#93;,
  les coordonnées du point \(C\) symétrique de \(A\) par rapport à \(B\)}
 \text{quest=\lstquest[\k]}
 \if{\k=1}
 {
 \integer{x=\xb - (\xa)}
 \integer{y=\yb - (\ya)}
 }
 \if{\k=2}
 {
 \integer{x=\xa - (\xb)}
 \integer{y=\ya - (\yb)}
 }
 \if{\k=3}
 {
 \rational{x=(\xb + (\xa))/2}
 \rational{y=(\yb + (\ya))/2}
 }
 \if{\k=4}
 {
 \integer{x=2*\xb - (\xa)}
 \integer{y=2*\yb - (\ya)}
 }
 \text{rep=\x,\y}
\statement{
  Dans un repère \((O,\vec{i},\vec{j})) du plan, on considère les points
  \(A\) (\xa,\ya) et \(B\) (\xb,\yb).
<p>
  Déterminer \quest.
</p><div>
<label for="reply1">\quest sont:</label> \embed{reply1,7}
</div>
<div class="wims_instruction">Séparer l'ordonnée de l'abscisse par une virgule.</div>
}
\answer{Votre réponse}{\rep}{type=vector}
#endif
#if defined TARGET_calculcoord2
 \title{TITLE II}
 \integer{k=random(1..4)}
 \text{lstquest=\(\overrightarrow{O C}= \a \overrightarrow{A B}),
\(\overrightarrow{C O}= \a \overrightarrow{A B}),
\(\overrightarrow{A C}= \a \overrightarrow{A B}),
\(\overrightarrow{C B}= \a \overrightarrow{A B})}
 \text{quest=\lstquest[\k]}
 \if{\k=1}
 {
 \integer{x=\a*(\xb - (\xa))}
 \integer{y=\a*(\yb - (\ya))}
 }
 \if{\k=2}
 {
 \integer{x=\a*(\xa - (\xb))}
 \integer{y=\a*(\ya - (\yb))}
 }
 \if{\k=3}
 {
 \integer{x=\a*(\xb - (\xa))+(\xa)}
 \integer{y=\a*(\yb - (\ya))+(\ya)}
 }
 \if{\k=4}
 {
 \integer{x=\a*(\xa - (\xb))+(\xb)}
 \integer{y=\a*(\ya - (\yb))+(\yb)}
 }
 \text{rep=\x,\y}
\statement{
  Dans un repère \((O,\vec{i},\vec{j})) du plan, on considère les points \(A\) (\xa,\ya) et \(B\) (\xb,\yb).
<p>
  Calculer les coordonnées du point \(C\) tel que:
</p><div class="wimscenter">\quest.</div>
<div>
  <label for="reply1">Les coordonnées de \(C\) sont:</label> \embed{reply1,7}.
</div>
<div class="wims_instruction">
  Séparer l'ordonnée de l'abscisse par une virgule.</div>
}
\answer{Votre réponse}{\rep}{type=vector}
#endif
#if defined TARGET_calculcoord3
 \title{TITLE III}
 \integer{xc=random(-\range..\range)}
 \integer{yc=random(-\range..\range)}
 \integer{k=random(1..3)}
 \text{lstquest= \(A B C D) est un parallélogramme,
\(\overrightarrow{C D}= \a \overrightarrow{A B}),
\(\overrightarrow{D C}= \a \overrightarrow{A B})}
 \text{quest=\lstquest[\k]}
 \if{\k=1}
 {
 \integer{x=\xa - (\xb)+(\xc)}
 \integer{y=\ya - (\yb)+(\yc)}
 }
 \if{\k=2}
 {
 \integer{x=\a*(\xb - (\xa))+(\xc)}
 \integer{y=\a*(\yb - (\ya))+(\yc)}
 }
 \if{\k=3}{
 \integer{x=-\a*(\xb - (\xa))+(\xc)}
 \integer{y=-\a*(\yb - (\ya))+(\yc)}
 }
 \text{rep=\x,\y}
\statement{
  Dans un repère \((O,\vec{i},\vec{j})) du plan, on considère les points
\(A\) (\xa,\ya), \(B\) (\xb,\yb) et \(C\)(\xc,\yc).
<p>
  Calculer les coordonnées du point \(D\) tel que:
</p><div class="wimscenter">\quest.</div>
<div>
  <label for="reply1">Les coordonnées de \(D\) sont:</label> \embed{reply1,7}.
</div>
<div class="wims_instruction">Séparer l'ordonnée de l'abscisse par une virgule.</div>
}
\answer{Votre réponse}{\rep}{type=vector}
#endif
#if defined TARGET_calculcoord4
 \title{TITLE IV}
 \integer{xi=random(-\range..\range)}
 \integer{yi=random(-\range..\range)}
 \integer{x=2*(\xi)-(\xa)}
 \integer{y=2*(\yi)-(\ya)}
 \integer{x2=2*(\xi)-(\xb)}
 \integer{y2=2*(\yi)-(\yb)}
 \text{rep=\x,\y}
 \text{rep2=\x2,\y2}
\statement{
  Dans un repère \((O,\vec{i},\vec{j})) du plan, on considère les points
\(A\) (\xa,\ya), \(B\) (\xb,\yb) et \(I\) (\xi,\yi).
<p>
  Calculer les coordonnées des points \(C\) et \(D\) tels que:
</p>
<div class="wimscenter">\(A B C D) est un parallélogramme de centre \(I).</div>
<div>
  <label for="reply1">Les coordonnées de \(C\) sont:</label> \embed{reply1,7}<br>
  <label for="reply2">Les coordonnées de \(D\) sont:</label> \embed{reply2,7}.
</div>
<div class="wims_instruction">Séparer l'ordonnée de l'abscisse par une virgule.</div>
}
\answer{Votre réponse}{\rep}{type=vector}
\answer{Votre réponse}{\rep2}{type=vector}
#endif
#if defined TARGET_calculcoord5
 \title{TITLE V}
\text{lstnat=rectangle, rectangle isocèle, isocèle, équilatéral, quelconque}
\integer{k=random(1..5)}
\integer{n=random(1..5)}
\text{txb=\xb}
\text{tyb=\yb}
\if{\k=1 or \k=2}
 {
 \integer{xc=\xa+((\k-2)*\n+1)*(\ya-(\yb))}
 \integer{yc=\ya+((\k-2)*\n+1)*(\xb-(\xa))}
 \integer{goodrep=\k}
 }
\if{\k=3}
  {
%% calcul de la pente perpendiculaire à (AB)
  \rational{a=(\xa-(\xb))/(\yb-(\ya))}
  \rational{b=((\yb)^2+(\xb)^2-(\xa)^2-(\ya)^2)/(2*(\yb-(\ya)))}
  \integer{xc=random(-\range..\range)}
  \rational{yc=\a*(\xc)+(\b)}
  \rational{pdtscal=(\xb-(\xa))*(\xc-(\xa))+(\yb-(\ya))*(\yc-(\ya))}
  \if{\pdtscal=0}
    {\integer{goodrep=2}}
    {\integer{goodrep=3}}
  }
\if{\k=4}{
  \integer{goodrep=4}
  \integer{i=random(1,2)}
  \if{\i=1}{
     \integer{a=\yb-(\ya)}
     \integer{a=\a<0?\a*(-1)}
     \text{sa=random(+,-)}
     \text{txb=\(\xa \sa \a \sqrt{3})}
     \real{xb=\xa \sa \a* sqrt(3)}
     \integer{xc=\xa}
     \integer{yc=2*(\yb)-(\ya)}
    }{
     \integer{a=\xb-(\xa)}
     \integer{a=\a<0?\a*(-1)}
     \text{sa=random(+,-)}
     \text{tyb=\(\ya \sa \a \sqrt{3})}
     \real{yb=\ya \sa \a *sqrt(3)}
     \integer{yc=\ya}
     \integer{xc=2*\xb-(\xa)}
    }
  }
 \if{\k=5}{
  \integer{goodrep=5}
  \integer{xc=random(-\range..\range)}
  \integer{yc=random(-\range..\range)}
  \integer{n1=(\xa - (\xb))^2+(\ya - (\yb))^2}
  \integer{n2=(\xc - (\xb))^2+(\yc - (\yb))^2}
  \integer{n3=(\xc - (\xa))^2+(\yc - (\ya))^2}
  \integer{pdtscal=(\xb-(\xa))*(\xc-(\xa))+(\yb-(\ya))*(\yc-(\ya))}
  \if{\n1=\n2 or \n1=\n3 or \n2=\n3}{
    \if{\n1=\n2 and \n1=\n3}{
       \integer{goodrep=4}
       }{
       \if{\pdtscal=0}
         {\integer{goodrep=2}}
         {\integer{goodrep=3}}
       }
     }{
       \if{\pdtscal=0}{\integer{goodrep=1}}{\integer{goodrep5}}
     }
  }
\text{xtlist=\xa,\txb,\xc}
\text{xlist=\xa,\xb,\xc}
\text{ylist=\ya,\yb,\yc}
\text{ytlist=\ya,\tyb,\yc}
\text{ind=shuffle(3)}
\text{xa=\xlist[\ind[1]]}
\text{txa=\xtlist[\ind[1]]}
\text{xb=\xlist[\ind[2]]}
\text{txb=\xtlist[\ind[2]]}
\text{xc=\xlist[\ind[3]]}
\text{txc=\xtlist[\ind[3]]}
\text{ya=\ylist[\ind[1]]}
\text{yb=\ylist[\ind[2]]}
\text{yc=\ylist[\ind[3]]}
\text{tya=\ytlist[\ind[1]]}
\text{tyb=\ytlist[\ind[2]]}
\text{tyc=\ytlist[\ind[3]]}
\real{xab=\xb-\xa}
\real{xbc=\xc-\xb}
\real{xac=\xc-\xa}
\real{yab=\yb-\ya}
\real{ybc=\yc-\yb}
\real{yac=\yc-\ya}
\text{vab=\xab,\yab}
\text{vbc=\xbc,\ybc}
\text{vac=\xac,\yac}
  \integer{nab=(\xa - (\xb))^2+(\ya - (\yb))^2}
  \integer{nbc=(\xc - (\xb))^2+(\yc - (\yb))^2}
  \integer{nac=(\xc - (\xa))^2+(\yc - (\ya))^2}
\statement{
  Dans un repère \((O,\vec{i},\vec{j})) du plan, on considère les points
  \(A\) (\txa,\tya), \(B\) (\txb,\tyb) et \(C\) (\txc,\tyc).
<p>
  Pour déterminer la nature du triangle \(A B C), calculer les coordonnées des vecteurs
  \(\overrightarrow{A B}), \(\overrightarrow{A C}) et \(\overrightarrow{B C}):
</p>
<ul>
<li><label for="reply2">\(\overrightarrow{A B})=</label>\embed{reply2}</li>
<li><label for="reply3">\(\overrightarrow{A C})=</label>\embed{reply3}</li>
<li><label for="reply4">\(\overrightarrow{B C})=</label>\embed{reply4}</li>
</ul>
<div class="wims_instruction">Taper <span class="tt">sqrt(3)</span> pour \(\sqrt{3}).</div>
<p>
  Puis déterminer la norme au carré de ces vecteurs.
</p>
<ul>
<li><label for="reply5">\(\|\overrightarrow{A B}\|^2)=</label>\embed{reply5}</li>
<li><label for="reply6">\(\|\overrightarrow{A C}\|^2)=</label>\embed{reply6}</li>
<li><label for="reply7">\(\|\overrightarrow{B C}\|^2)=</label>\embed{reply7}</li>
</ul>
  En déduire la nature du triangle:
<p>
  Le triangle \(A B C) est: </p>
<ul><li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
<li>\embed{reply1,5}</li>
</ul>
}
\answer{nature du triangle}{\goodrep;\lstnat}{type=radio}
\answer{\(\overrightarrow{A B})}{\vab}{type=vector}
\answer{\(\overrightarrow{A C})}{\vac}{type=vector}
\answer{\(\overrightarrow{B C})}{\vbc}{type=vector}
\answer{\(\|\overrightarrow{A B}\|^2)}{\nab}{type=vector}
\answer{\(\|\overrightarrow{A C}\|^2)}{\nac}{type=vector}
\answer{\(\|\overrightarrow{B C}\|^2)}{\nbc}{type=vector}
#endif
