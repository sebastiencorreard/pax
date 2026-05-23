target=graphant

\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{nom=random(f,g,h)}
\integer{nb1=random(1,-1)*random(1..50)}
\integer{nb2=random(1,-1)*random(1..50)}
\real{nb1=\nb1/10}
\real{nb2=\nb2/10}
\if{abs(\nb1-\nb2)<.5}{
  \real{nb1=-2.5}
  \real{nb2=3.4}
}

\real{a=10/(\nb2-(\nb1))}
\real{b=5-\nb2*(\a)}
\integer{pt1=\nb1*50+250}
\integer{pt2=\nb2*50+250}

\text{dessin=wims(record 1 of src/graph.don)}
\text{dessin=\dessin
segment \pt2,0,\pt1,500,red}

\integer{ord=random(1,-1)*random(1..45)}
\real{ord=\ord/10}
\real{abs=(\ord-\b)/(\a)}
\integer{abs2=\abs*10}
\real{abs2=\abs2/10}

\integer{tmp=-(\ord)*50+250}
\integer{tmp2=250+(\abs)*50}
\if{\abs>0}{\text{texte1=text green,220,\tmp-10,medium,\ord}}
{\text{texte1=text green,255,\tmp-10,medium,\ord}}

\if{\ord>0}{\text{texte2=text green,\tmp2-10,260,medium,\abs2}}
{\text{texte2=text green,\tmp2-10,230,medium,\abs2}}

\text{dessin2=\dessin
arrow \tmp2,\tmp,\tmp2,250,10,green
\texte2
arrow 250,\tmp,\tmp2,\tmp,10,green
\texte1}
\statement{
\name_enonce[1] \(\nom\) \name_enonce[2]:
<div class="wimscenter">\draw{500,500}{\dessin}</div>
\name_question[1] \(\ord) \name_question[2] \(\nom\) ?
<div class="spacer">
<b>\name_answer:</b>
<label for="reply1">
\name_ans[1] \(\ord\) \name_ans[2] \(\nom\) \name_ans[3] </label>
\embed{r1,5}.
</div>}

\answer{\(\nom^{-1}(\ord))}{\rep}{type=auto}

\condition{\name_cond}{abs(\abs-(\rep))<0.1}

\solution{\name_sol1[1] \ord \name_sol1[2] \nom \name_sol1[3] \ord.
<p>\name_sol2[1] \ord \name_sol2[2]</p>
<div class="wimscenter">
\draw{500,500}{\dessin2}
</div>}
