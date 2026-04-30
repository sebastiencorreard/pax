target=critcolin1 critcolin2 critcolin3 critcolin4 critcolin5
\language{fr}
\range{-5..5}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}
#define TITLE Critère de colinéarité
\integer{mid=8}
\integer{range=\mid*2}
#if defined TARGET_critcolin2 || defined TARGET_critcolin4
\integer{x0=random(1..\mid)*randint(1,-1)}
\integer{y0=random(1..\mid)*randint(1,-1)}
#else
\integer{x0=random(-\mid..\mid)}
\integer{y0=random(-\mid..\mid)}
#endif
\if{\x0=0 and \y0=0}
 {
 \integer{x0=random(1..\range)*random(1,-1)}

 }

#if (defined TARGET_critcolin2 || defined TARGET_critcolin3)
\integer{d1=1}
#else
\integer{d1=random(1,1,1,1,2,3,4,5)}
#endif
\rational{x0=\x0 / random(\d1,1)}
\rational{y0=\y0 / random(\d1,1)}

\integer{a=random(2..6)*random(-1,1)}
\integer{b=random(2..6)*random(-1,1)}
\integer{b=\a=\b?-\b}
\rational{xa=\a*\x0}
\rational{ya=\a*\y0}
\rational{xb=\b*\x0}
\rational{yb=\b*\y0}


#if (defined TARGET_critcolin1 || defined TARGET_critcolin2)
 \title{TITLE II}

 \integer{k=random(1,2)}
 \integer{k2=random(1,2)}
#if defined TARGET_critcolin1
 \title{TITLE I}
 \integer{k2=1}
#endif
#if defined TARGET_critcolin2
\integer{d=random(2,3,5,7,11)}
\integer{e=random(1..\range)*random(1,-1)}

\rational{xc=\e*(\xa)}
\rational{yc=\e*(\ya)}
#endif
\if{\k=2 and \k2=1}
 {
 \rational{ya=\ya+randint(1..\range)*randint(1,-1)}
 \rational{colin=\ya*(\xb) -(\yb)*(\xa)}
 \rational{xa=\colin=0?\xa+randint(1..\range)*random(1,-1)}
 }
\if{\k=2 and \k2=2}
 {
 \rational{yc=\yc+randint(1..\range)*randint(1,-1)}
 \rational{colin=\yc*(\xb) -(\yb)*(\xc)}
 \rational{xc=\colin=0?\xc+randint(1..\range)*random(1,-1)}
 }
#if defined TARGET_critcolin2
 \text{sa=random(+,-)}
 \text{xa=\xa*sqrt(\d)\sa \xc}
 \text{ya=\ya*sqrt(\d)\sa \yc}
#endif
\integer{rep=\k}
\text{txa=texmath(\xa)}
\integer{i=random(1,2)}
\if{\i=1}
 {
\text{txb=texmath(\ya)}
\text{tya=texmath(\xb)}
 }
 {
\text{txb=texmath(\xb)}
\text{tya=texmath(\ya)}
 }
\text{tyb=texmath(\yb)}
\statement{
  Dans un repère \((O,\vec{i},\vec{j})\) du plan, on considère les vecteurs
\(\vec{u})\(\left(\begin{array}{c} \txa \\ \tya \end{array}\right)\) et
\(\vec{v})\(\left(\begin{array}{c} \txb \\ \tyb \end{array}\right)\).
<div>
  Les vecteurs \(\vec{u}\) et \(\vec{v}\) sont-ils colinéaires? \embed{reply1}
</div>
}
\answer{Votre réponse}{\rep;Oui,Non}{type=radio}
#endif



#if defined TARGET_critcolin3
 \title{TITLE III}
 \integer{xb=\xa+randint(2,4,5)*randint(1,-1)}
%% choix de la réponse: 1 alignés/parallèles, 2 non
 \integer{rep=random(1,2)}
%% choix de la question 1:3 pts alignés, 2: 2 droites paralleles
 \integer{k=random(1,2)}
 \text{lstquest= Les points \(A) &#44;\(B) et \(C) sont-ils alignés,
  Les droites \((A B)) et \((C D)) sont-elles parallèles}
 \text{quest=\lstquest[\k]}
%% choix des points en fonction de la réponse souhaitée
 \if{\k=1}
 {
 \rational{xd=\xa}
 \rational{yd=\ya}
 }
 {
 \integer{xd=random(-\range..\range)}
 \integer{yd=random(-\range..\range)}
 }
 \integer{xc=random(-\range..\range)}
 \integer{yc=random(-\range..\range)}
 \rational{xx=(\xb - (\xa))*(\xc-(\xd))}
  \if{\xx<>0}{ \rational{yc=\yd+(\xc-(\xd))*(\yb-(\ya))/(\xb-(\xa))}}
    {\rational{xa=\xb}
     \rational{xc=\xd}
     \rational{yb=\ya+randint(1..\range)*randint(1,-1)}
     \rational{yc=\yd+randint(1..\range)*randint(1,-1)}
   }
  \if{\rep=2}{
    \rational{yb=\yb+randint(1..\range)*randint(1,-1)}
    \rational{colin=(\yb-(\ya))*(\xc-(\xd)) -(\yc-(\yd))*(\xb-(\xa))}
    \rational{xa=\colin=0?\xa+randint(1..\range)*random(1,-1)}
  }

\text{lstpt=\(A\) (\xa&#44;\ya)&#44; \(B\) (\xb&#44;\yb) et \(C\) (\xc&#44;\yc),
  \(A\) (\xa&#44;\ya)&#44; \(B\) (\xb&#44;\yb)&#44; \(C\) (\xc&#44;\yc) et \(D\) (\xd&#44;\yd)}
\text{pts=\lstpt[\k]}
\statement{
  Dans un repère \((O,\vec{i},\vec{j})) du plan, on considère les points
\pts.

<div class="wimscenter">\quest? \embed{reply1}</div>
}
\answer{Votre réponse}{\rep;Oui,Non}{type=radio}
#endif
#if (defined TARGET_critcolin4 || defined TARGET_critcolin5)
#if defined TARGET_critcolin5
 \title{TITLE V}
#else
 \title{TITLE IV}
#endif
\text{lst=texmath(\xa),texmath(\xb),texmath(\ya),texmath(\yb)}
\text{lstval=\xa,\xb,\ya,\yb}
\integer{i=randint(1..4)}
\rational{rep=\lstval[\i]}
#if defined TARGET_critcolin5
 \text{subst=texmath(\a*t+\b)}
 \rational{rep=(\rep-(\b))/(\a)}
 \text{lst=wims(replace item number \i by \subst in \lst)}
#else
 \text{lst=wims(replace item number \i by t in \lst)}
#endif
\text{txa=\lst[1]}
\text{txb=\lst[2]}
\text{tya=\lst[3]}
\text{tyb=\lst[4]}
\integer{test=\xa*\yb-\ya*\xb}
\statement{
  Dans un repère \((O,\vec{i},\vec{j})) du plan, on considère les vecteurs
\(\vec{u})\(\left(\begin{array}{c} \txa \\ \tya \end{array}\right)) et
\(\vec{v})\(\left(\begin{array}{c} \txb \\ \tyb \end{array}\right)).
<p>
  Déterminer la valeur de \(t) telle que les vecteurs \(\vec{u}) et \(\vec{v}) soient colinéaires.
</p>
<div class="wimscenter"><label for="reply1">Valeur de \(t):</label> \embed{reply1,7}
</div>
<div class="wims_instruction">
  Donner \(t) sous forme fractionnaire ou décimale avec deux décimales.
</div>
}
\answer{Votre réponse}{\rep}{type=numeric}
#endif
