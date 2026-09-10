target=valeurabsolue1

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
\text{eq=maxima(x-\a;)}
\integer{b=\a+\r}
\integer{c=\a-\r}
\integer{b1=\r+\a}
\integer{c1=\r-\a}
\integer{n=random(1..2)}
\text{sens=item(\n,\le,=)}
\text{s1=[\c,\b]}
\text{s2={\c,\b}}
\text{rep=item(\n,\s1,\s2)}
\text{s4=[\c1,\b1]}
\text{s5={\c1,\b1}}

\statement{\name_enonce[1]
  <div class="wimscenter">\(|\eq| \sens \r)</div>
  \name_enonce[2]:
}

\choice{S=}{\rep}{\s1,\s2,\s4,\s5}
