target=difference difference2
\language{fr}
\range{-5..5}
#if defined TARGET_difference
\author{Noémie,Cochi; Olivier,Dupuy}
#endif
#if defined TARGET_difference2
\author{Noémie,Cochi; Olivier,Dupuy; Gérard,Lauton}
#endif
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{yes}
\format{html}
\precision{10000}
\real{a=randint(0..9)*random(-1,1)}
\real{b=randint(\a+1..10)}
\real{c=randint(0..9)*random(-1,1)}
\real{d=randint(\c+1..10)}
\real{res3=\a-\d}
\real{res4=\b-\c}
#if defined TARGET_difference2
\real{ac=\a+\c}
\real{bd=\b+\d}
\real{absc=abs(\c)}
\real{absd=abs(\d)}
\text{s=\c>0?-:+}
\text{t=\d>0?-:+}
\text{s=\c=0? }
\text{t=\d=0? }
\rational{oppc = -\c}
\rational{oppd = -\d}
\integer{r=pari(vecmin([\res3,0,\a,\b,\c,\d])-2)}
\integer{R=pari(vecmax([\res4,0,\a,\b,\c,\d])+2)}
\text{eq=x-\res3,x-\res4}
# include "graphdiffsum.inc"
#endif
\statement{
#if defined TARGET_difference
\name_enonce
  \(\a \;< \; x \; < \; \b \) et \( \c \; < \; y \;< \; \d \).
#endif
#if defined TARGET_difference2
<p>\name_graph</p>
  <p class="wimscenter">\draw{900,100}{\dessin}</p>
#endif
<label for="reply1">\name_bestappr \(x - y\)&nbsp;:</label>
<div class="wimscenter">
  \embed{r1,3}<label for="reply2">\(\;\leq \; x \;- \;y \; \leq \;\)</label> \embed{r2,3}.
</div>
}

\answer{}{\res3}{type=numexp}
\answer{}{\res4}{type=numexp}

\help{\name_help}
\hint{\name_hint}
#if defined TARGET_difference2
# include "soldiff.inc"
#endif
\feedback{\reply1>\reply2}{\name_feed1 \(\reply1 > \reply2\).}
\feedback{\reply1=\a-\c and \reply2=\b-\d}{\name_feed2}
\feedback{\reply1=\a+\c and \reply2=\b+\d}{\name_feed3}
\feedback{\reply1<\res3 and \reply2>\res4}{\name_feed4}
