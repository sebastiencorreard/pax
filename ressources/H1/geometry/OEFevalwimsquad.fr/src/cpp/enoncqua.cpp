target=oefenoncqua1 oefenoncqua2 oefenoncqua3 oefenoncqua4 oefenoncqua5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\langage{fr}
\format{html}
\text{let=shuffle(A,B,C,E,F,G,H,R,S,T)}

#if defined TARGET_oefenoncqua1
\text{enonc1=\name_enonc1[1] \let[1]\let[2]\let[3]\let[4] \name_enonc1[2]}
\real{l1=randint(40..80)/10}
\real{l2=randint(\l1*10+10..120)/10}
\integer{rep=sqrt(\l1^2+\l2^2)*10}
\real{rep1=(\rep-1)/10}
\real{rep2=(\rep+1)/10}
\text{l=shuffle(\l1,\l2)}
\text{enonc2=\let[1]\let[2] = \l[1] cm \name_enonc2 \let[1]\let[4] = \l[2] cm.}
\text{enonc3=\name_enonc3}
#endif
#if defined TARGET_oefenoncqua2
\text{enonc1=\name_enonc1[1] \let[1]\let[2]\let[3]\let[4] \name_enonc1[2]}
\real{l1=randint(40..80)/10}
\real{l2=randint(\l1*10+10..120)/10}
\integer{rep=sqrt(\l2^2-\l1^2)*10}
\real{rep1=(\rep-1)/10}
\real{rep2=(\rep+1)/10}
\text{l=\l1,\l2}
\text{enonc2=\name_enonc2[1] [\let[1]\let[2]] \name_enonc2[2] \l[1] cm
  \name_enonc2[3] \l[2] cm.}
\text{enonc3= \let[1]\let[4]}
#endif
#if defined TARGET_oefenoncqua3
\text{enonc1=\name_enonc1[1] \let[1]\let[2]\let[3]\let[4] \name_enonc1[2]}
\real{l1=randint(40..90)/10}
\text{enonc2=\name_enonc2 \l1 cm}
\text{enonc3=\let[1]\let[2]}
\integer{rep=\l1/sqrt(2)*10}
\real{rep1=(\rep-1)/10}
\real{rep2=(\rep+1)/10}
#endif
#if defined TARGET_oefenoncqua4
\text{enonc1=\name_enonc1[1] \let[1]\let[2]\let[3]\let[4] \name_enonc1[2]}
\real{l1=randint(40..80)/10}
\real{l2=randint(\l1*10+10..120)/10}
\integer{rep=sqrt(\l2^2+\l1^2)*10/2}
\real{rep1=(\rep-1)/10}
\real{rep2=(\rep+1)/10}
\text{enonc2=\name_enonc2[1] \l1 cm \name_enonc2[2] \l2 cm.}
\text{enonc3= \let[1]\let[2]}
#endif
#if defined TARGET_oefenoncqua5
\text{enonc1=\name_enonc1[1] \let[1]\let[2]\let[3]\let[4] \name_enonc1[2]}
\real{l1=randint(40..80)/10}
\real{l2=randint(40..(\l1*10-10)*2)/10}
\integer{rep=sqrt(\l1^2-\l2^2/4)*20}
\real{rep1=(\rep-1)/10}
\real{rep2=(\rep+1)/10}
\text{enonc2=\name_enonc2[1] \l1 cm \name_enonc2[2] \l2 cm.}
\text{enonc3= \name_enonc3}
#endif
\statement{
\enonc1
\enonc2
<p>\name_question \enonc3.</p>
<div class="spacer"><label for="reply1">\name_mesure \enonc3 =</label> \embed{r1,4} cm.
</div>
}

\answer{}{\rep1,\rep2}{type=range}

\latex{
\begin{statement}
\enonc1
\enonc2
\par
\name_question \enonc3.
\par
\name_mesure \enonc3= \(\cdots \) cm.
\end{statement}
}
