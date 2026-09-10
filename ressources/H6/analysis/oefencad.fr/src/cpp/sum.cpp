target=sum
\language{fr}
\range{-5..5}
\author{Gérard, Lauton}
\computeanswer{yes}
\format{html}
\precision{10000}

#include "lang_titles.inc"
#include "lang.inc"

\real{a=randint(1..8)*random(-1,1)}
\real{b=randint(\a+2..10)}
\real{c=randint(1..8)*random(-1,1)}
\while{\c=\a}{
  \real{c=randint(0..8)*random(-1,1)}
}
\real{d=randint(\c+2..10)}

\integer{res1=\a+\c}
\integer{res2=\b+\d}
\integer{res3=\res1} (pour le graphe)
\integer{res4=\res2}
\integer{r=pari(vecmin([\res3,0,\a,\c])-2)}
\integer{R=pari(vecmax([\res4,0,\b,\d])+2)}
\text{eq=-x+\res3,-x+\res4}

#include "graphdiffsum.inc"
#include "solsumprel.inc"
\statement{
  \name_enonce:
  \({\a < x < \b}\) \name_and \({\c < y < \d}\).
  <p>\name_graph</p>
  <p class="wimscenter">\draw{900,100}{\dessin}</p>
  <label for="reply1">\name_question:</label>
  <div class="wimscenter">\embed{r1,3}
  <label for="reply2">\({< x + y <}\)</label> \embed{r2,3}.
  </div>}

\answer{}{\res1}{type=numexp}
\answer{}{\res2}{type=numexp}
\hint{\name_hint}
\solution{<p>En additionnant terme à terme les bornes de l'encadrement
\({\a < x < \b}\) de \(x\) et de celui \({\c < y < \d}\) de \(y\), on obtient :
</p>
<p class="wimscenter">\({\res1 < x + y < \res2}\).</p>
<p><em>On peut visualiser cet encadrement de la somme \(x + y\)
par la figure ci-dessous.</em>
\Explication</p>
<p class="wimscenter">\draw{400,400 }{\Encadrement}</p>
}

\feedback{\reply1>\reply2}{\name_feed1 \reply1 > \reply2.}
\feedback{\reply1<\res1 and \reply22\res2}{\name_feed1}
