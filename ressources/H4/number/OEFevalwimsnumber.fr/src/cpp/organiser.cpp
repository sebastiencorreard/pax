target=organiser1 organiser2 organiser3 organiser4 organiser5

#if defined TARGET_organiser1
\title{Organiser un calcul 1}
\integer{a=randint(2..4)}
\text{ul=shuffle(4)}
\integer{u=\ul[1]}
\integer{v=\ul[2]}
\integer{b=2*\u*\v}
\integer{c=\u^2-\v^2}
\integer{c=\c<0?-\c}
\real{sol=\a*sqrt(\b^2+\c^2)}
\text{form=\a \sqrt{\b^2+\c^2}}
\statement{
  Calculer à la main:
<div class="wimscenter"> <label for="reply1">\(\form)</label>=\embed{reply1}</div>
}
\answer{}{\sol}{type=numeric}
#endif

#if defined TARGET_organiser2
\title{Organiser un calcul 2}
\integer{a=randint(2..8)}
\integer{b=randint(2..8)}
\integer{c=randint(2..8)}
\text{listexp=(\a+\b)/(\c-pi),\a+\b/(\c-pi),(\a+\b)/\c - pi,\a+\b/\c-pi}
\text{listsol=}
\text{listsol2=}
\for{i=1 to 4}
 {
 \real{y=\listexp[\i]}
 \real{x=\y*100}
 \text{tx=\x}
 \text{tx=wims(replace internal . by , in \tx)}
 \rational{x=\tx[1]/100}
 \text{listsol=wims(append item \x to \listsol)}
 \text{listsol2=wims(append item \y to \listsol2)}
 }
\text{listform=\frac{\a+\b}{\c-\pi},\a+\frac{\b}{\c-\pi},\frac{\a+\b}{\c}-\pi,\a+\frac{\b}{\c}-\pi}
\integer{k=randint(1..3)}
\statement{
  A l'aide de la calculatrice, donner la <label for="reply1">troncature à deux décimales
  de \(\listform[\k])</label>:
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{\listsol[\k]}{type=numeric}
\feedback{\reply1=\listsol[1] and \k<>1}{La valeur donnée correspond à \(\listform[1]) au lieu de \(\listform[\k])}
\feedback{\reply1=\listsol[2] and \k<>2}{La valeur donnée correspond à \(\listform[2]) au lieu de \(\listform[\k])}
\feedback{\reply1=\listsol[3] and \k<>3}{La valeur donnée correspond à \(\listform[3]) au lieu de \(\listform[\k])}
\feedback{\reply1=\listsol[4] and \k<>4}{La valeur donnée correspond à \(\listform[4]) au lieu de \(\listform[\k])}
#endif

#if defined TARGET_organiser3
\title{Organiser un calcul 3}
\integer{a=randint(2..8)}
\integer{b=randint(2..8)}
\text{listexp=sqrt((\a+pi)^2+\b),sqrt(\a)+pi^2+\b,sqrt(\a+pi)^2+\b}
\text{listsol=}
\text{listsol2=}
\for{i=1 to 3}
 {
 \real{y=\listexp[\i]}
 \real{x=\y*100}
 \text{tx=\x}
 \text{tx=wims(replace internal . by , in \tx)}
 \rational{x=\tx[1]/100}
 \text{listsol=wims(append item \x to \listsol)}
 \text{listsol2=wims(append item \y to \listsol2)}
 }
\text{listform=\sqrt{(\a+\pi)^2+\b},\sqrt{\a}+\pi^2+\b,\sqrt{\a+\pi}^2+\b}
\integer{k=1}
\statement{
  A l'aide de la calculatrice, donner <label for="reply1">
  la troncature à deux décimales de \(\listform[\k])</label>:
<div class="wimscenter"> \embed{reply1}</div>
}
\answer{}{\listsol[\k]}{type=numeric}
\feedback{\reply1=\listsol[1] and \k<>1}{La valeur donnée correspond à \(\listform[1]) au lieu de \(\listform[\k])}
\feedback{\reply1=\listsol[2] and \k<>2}{La valeur donnée correspond à \(\listform[2]) au lieu de \(\listform[\k])}
\feedback{\reply1=\listsol[3] and \k<>3}{La valeur donnée correspond à \(\listform[3]) au lieu de \(\listform[\k])}
#endif

#if (defined TARGET_organiser4 || defined TARGET_organiser5 )
#if defined TARGET_organiser4
\title{Organiser un calcul 4}
 \integer{n=2}
 \text{typeval=à \(10^{-2}) par défaut}
 \integer{k=randint(2..9)}
 \integer{m=randint(2..9)}
 \integer{p=randint(2..9)}
 \integer{b=randint(3..9)}
 \real{a=\k/10}
 \real{b=\m/10}
 \real{c=\p/10}
 \text{x=\(\frac{\a \times 10^3 - \b \times 10^4}{\c \times 10^5} )}
 \real{u=(\a*10^3-\b*10^4)/(\c*10^5)}
 \real{u=\u*100}
 \text{tu=\u}
 \text{tu=wims(replace internal . by , in \tu)}
 \real{u=\tu[1]}
 \real{sol=\u/100}
 \integer{ndec=2}
\text{infocalc=Sans}
#endif

#if defined TARGET_organiser5
\title{Organiser un calcul 5}
 \integer{n=4}
 \text{typeval=par défaut}
 \integer{a=randint(2..9)}
 \integer{b=randint(2..9)}
 \integer{c=randint(2..9)}
 \text{x=\(\frac{\pi}{\a}+\frac{\pi^2}{\b}+\frac{\pi^3}{\c})}
 \real{u=pi/\a+ (pi)^2/\b+ (pi)^3/\c}
 \real{u=\u*10000}
 \text{tu=\u}
 \text{tu=wims(replace internal . by , in \tu)}
 \real{u=\tu[1]}
 \real{sol=\u/10000}
 \integer{ndec=4}
\text{infocalc=A}
#endif

\statement{
\infocalc l'aide de la calculatrice, donner <label for="reply1">la troncature à \ndec décimales</label>
de:
<div class="wimscenter">\x</div>
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{\sol}{type=numeric}
#endif
