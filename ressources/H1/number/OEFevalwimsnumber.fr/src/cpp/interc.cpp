target=oefinterc1 oefinterc2 oefinterc3 oefinterc4 oefinterc5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
text{inf=draw(32,32
linewidth 3
segment 8,16,24,8,black
segment 8,16,24,24,black)}
text{sup=draw(32,32
linewidth 3
segment 8,8,24,16,black
segment 8,24,24,16,black)}
text{ego=draw(32,32
linewidth 3
segment 8,12,24,12,black
segment 8,20,24,20,black)}
text{sign=<img src="\inf" alt="">,<img src="\sup" alt="">,<img src="\ego" alt="">}
\text{sign=\(\Large{<}\),\(\Large{>}\),\(\Large{=}\)}
#if defined TARGET_oefinterc1
\integer{nb1=randint(10..999)}
\integer{d=randint(2..10)}
\integer{nb2=\nb1+\d}
\text{enonc1= \name_enonc}
\text{\enonc2= \sign[\1] \nb2}
\text{size=6}
#endif
#if defined TARGET_oefinterc2
\integer{nb1=randint(10..999)}
\integer{d=1}
\integer{nb2=\nb1+\d}
\text{\enonc1= \name_enonc}
\text{\enonc2= \sign[\1] \nb2}
\text{size=6}
#endif
#if defined TARGET_oefinterc3
\integer{nb1=randint(100..999)}
\integer{d=randint(2..10)}
\integer{nb2=\nb1+\d}
\real{nb1=\nb1/10}
\real{nb2=\nb2/10}
\text{\enonc1= \name_enonc}
\text{\enonc2= \sign[\1] \nb2}
\text{size=6}
#endif
#if defined TARGET_oefinterc4
\integer{nb1=randint(100..999)}
\integer{d=1}
\integer{nb2=\nb1+\d}
\real{nb1=\nb1/10}
\real{nb2=\nb2/10}
\text{\enonc1= \name_enonc}
\text{\enonc2= \sign[\1] \nb2}
\text{size=6}
#endif
#if defined TARGET_oefinterc5
\integer{d=random(-1,1)}
\integer{nb1=randint(1..99)}
\integer{nb2=\nb1*10 + \d}
\real{nb1=\nb1/10}
\real{nb2=\nb2/100}
\if{\d=-1}{
  \real{a=\nb1}
  \real{nb1=\nb2}
  \real{nb2=\a}}
\text{\enonc1= \name_enonc}
\text{\enonc2= \sign[\1] \nb2}
\text{size=6}
#endif

\statement{\enonc1&nbsp;:
  <div class="wimscenter">
  <label for="reply1">\nb1 \sign[1]</label> \embed{r1,\size} \enonc2
  </div>}

\answer{}{\rep1}{type=numeric}
\condition{}{\rep1>\nb1 and \rep1<\nb2}
\latex{
\begin{statement}
\enonc1
  \begin{center}
  \nb1 \sign[1] \(\dots\dots\) \enonc2
  \end{center}
\end{statement}
}
