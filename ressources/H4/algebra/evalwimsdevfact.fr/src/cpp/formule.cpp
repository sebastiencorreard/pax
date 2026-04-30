target=formule1,formule2,formule3,formule4,formule5

\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}
#define TITRE Connaissance des formules
#if defined TARGET_formule1
 \title{TITRE 1}
 \text{sg=randitem(+,-)}
 \text{enonce=k(a\sg b)}
 \text{good=\(k a\sg k b)}
 \text{lettres=\(a\), \(b\) et \(k\)}
 \text{bad=\(k a\sg b),\(k a b),\(a\sg k b)}
#endif

#if defined TARGET_formule2
 \title{TITRE 2}
 \text{enonce=(a+b)(c+d)}
 \text{good=\(a c+a d+b c+b d)}
 \text{lettres=a, b, c et d}
 \text{bad=\(a c+b d),\(a+b c+d),\(a+b+c+d)}
#endif

#if defined TARGET_formule3
 \title{TITRE 3}
 \text{enonce=(a+b)^2}
 \text{lettres=\(a\) et \(b\)}
 \text{good=\(a^2+2a b+b^2)}
 \text{bad=\(a^2+b^2),\(a^2+a b+b^2),\(a^2+2a+2b+b^2)}
#endif

#if defined TARGET_formule4
 \title{TITRE 4}
 \text{enonce=(a-b)^2}
 \text{lettres=\(a\) et \(b\)}
 \text{good=\(a^2-2a b+b^2)}
 \text{bad=\(a^2-b^2),\(a^2-a b+b^2),\(a^2-2a b-b^2)}
#endif

#if defined TARGET_formule5
 \title{TITRE 5}
 \text{enonce=(a+b)(a-b)}
 \text{lettres=\(a\) et \(b\)}
 \text{good=\(a^2-b^2)}
 \text{bad=\(a^2+b^2),\(a+a b-b),\(a^2-2a b-b^2),\(a^2-2a b+b^2)}
#endif

\text{size=150x30x1}

\statement{
  Parmi les expressions suivantes, laquelle est l'expression développée égale à \(\enonce)
  pour toutes les valeurs possibles de \lettres ?
<p>
<b>Votre réponse :</b>
</p>
<div class="wimscenter">
\(\enonce =) \embed{r1,\size}.
</div>
}
\reply{réponse}{\good;\bad}{type=clickfill}
