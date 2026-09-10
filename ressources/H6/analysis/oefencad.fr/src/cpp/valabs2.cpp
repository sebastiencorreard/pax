target=valeurabsolue2 valeurabsolue3

\language{fr}
\range{-5..5}
\author{Michel, Gosse}
\email{michel.gosse@ac-poitiers.fr}
\computeanswer{no}
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\integer{a=random(-10..10)}
\integer{r=random(1..10)}
\integer{c=\a+\r}
\integer{b=\a-\r}
#if defined TARGET_valeurabsolue2
\statement{\name_enonce[1] [\b,\c] \name_enonce[2] \(|x-a| \leq r\).}
#endif
#if defined TARGET_valeurabsolue3
\statement{\name_enonce[1] \(|x-a|\ge r) \name_enonce[2]
  \(\rbrack - \infty,\b\rbrack \cup \lbrack \c,+\infty \lbrack).}
#endif
#if defined TARGET_valeurabsolue2
\hint{\name_hint}
#endif
#if defined TARGET_valeurabsolue3
\hint{\name_hint [\b,\c].}
#endif
\answer{Valeur de \(a\)}{\a}{type=default}
\answer{Valeur de \(r\)}{\r}{type=default}
