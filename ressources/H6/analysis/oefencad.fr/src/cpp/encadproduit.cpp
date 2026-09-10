target=encadproduit encadproduit2 encadproduit3

\language{fr}
\range{-5..5}
\computeanswer{yes}
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_encadproduit2
\integer{a = randint(1..8)}
\integer{b = randint(\a+2..10)}
\integer{absc = randint(1..8)}
\integer{absd = randint(\absc+2..10)}
\integer{s = -1}
\integer{sgn=randint(1..2)}
\integer{t = \sgn=1? -1:1}
\integer{c = \s * \absc}
\integer{d = \t * \absd}
\integer{e = min(\c,\d)}
\integer{f = max(\c,\d)}
\integer{c = \e}
\integer{d = \f}
\integer{absc = abs(\c)}
\integer{absd = abs(\d)}
\integer{oppc=-\c}
\integer{oppd=-\d}
#else
\real{a=randint(1..8)*random(-1,-1,1)}
\real{b=randint(\a+2..10)}
\real{c=randint(1..8)*random(-1,-1,1)}
\real{d=randint(\c+2..10)}
#endif
\integer{ac=\a*\c}
\integer{ad=\a*\d}
\integer{bc=\b*\c}
\integer{bd=\b*\d}

\real{res1=min(min(\ac,\bc),min(\ad,\bd))}
\real{res2=max(max(\ac,\bc),max(\ad,\bd))}
\integer{r=pari(vecmin([0,\a,\b,\c,\d])-4)}
\integer{R=pari(vecmax([\a,\b,\c,\d,0])+4)}
\text{eq=\res1 / x,\res2 / x}

#if defined TARGET_encadproduit3
#include "solprodprel.inc"
#include "graphprod.inc"
#endif
#if defined TARGET_encadproduit2
#include "solprodprel0.inc"
#include "graphprod.inc"
#endif
\statement{
\name_enonce
  <div class="wimscenter">
#if defined TARGET_encadproduit
  \( \a \;< \; x \; < \; \b \) et \(\c \; < \; y \;< \; \d).
#endif
#if defined TARGET_encadproduit2 || defined TARGET_encadproduit3
\({\a < x < \b}\) et \({\c < y < \d}\).
#endif
</div>
#if defined TARGET_encadproduit2 || defined TARGET_encadproduit3
<p>\name_graph</p><p class="wimscenter">\draw{900,100}{\dessin}</p>
#endif
<label for="reply1">Trouver le meilleur encadrement de \(x y):</label>
#if defined TARGET_encadproduit
<div class="wims_instruction"> ici, \(P_1\leq P_2\)</div>
#endif
 <div class="wimscenter">
#if defined TARGET_encadproduit1
  \embed{r1, 3} <label for="reply2">\(\;<\; x y \;< \;\)</label> \embed{r2,3 }.
#endif
#if defined TARGET_encadproduit2 || defined TARGET_encadproduit3
  \embed{r1, 3} <label for="reply2">\(\;\leq x y \;\leq\)</label> \embed{r2,3 }.
#endif
</div>
}
\answer{\(P_1\)}{\res1}{type=numexp}
\answer{\(P_2\)}{\res2}{type=numexp}

#if defined TARGET_encadproduit2 || defined TARGET_encadproduit3
#include "solprod.inc"
#endif
#if defined TARGET_encadproduit2 || defined TARGET_encadproduit3
\hint{\name_hint}
#endif
#if defined TARGET_encadproduit || defined TARGET_encadproduit2
\help{\name_help}
#endif

\feedback{\reply1>\reply2}{\name_feed1 \(\reply1 > \reply2\).}
\feedback{(\reply1<>\res1 and \reply1=\ac) or (\reply2<>\res2 and \reply2=\bd)}{
  \name_feed2
}
\feedback{\reply1<\res1 and \reply2>\res2}{\name_feed3}
