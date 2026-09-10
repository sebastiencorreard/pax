target=quatrprop1 quatrprop2 quatrprop5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_quatrprop1
\integer{a=randint(2..10)}
\integer{b=\a*randint(2..5)}
\integer{c=\b*randint(2..10)}
\integer{r=(\a * \c)/\b}
#endif
#if defined TARGET_quatrprop2 || defined TARGET_quatrprop5
\real{a=randint(2..10)+randint(1..9)/10}
\real{b=\a*randint(2..5)}
\real{c=\b*randint(2..10)}
\real{r=(\a * \c)/\b}
#endif
#if defined TARGET_quatrprop5
\text{un=\a,\b,\c,XX}
\text{deux=\b,\c,XX,\a}
\text{trois=\c,XX,\a,\b}
\text{quatre=XX,\a,\b,\c}
\integer{n=randint(1..4)}
#endif

\statement{
\name_enonce
<table class="wimscenter wimsborder"><tr><td>
#if defined TARGET_quatrprop5
  \if{\n==4}{\embed{r1,4}}{\un[\n]}</td> <td> \if{\n==1}{\embed{r1,4}}{\quatre[\n]} </td>
  </tr><tr>
  <td> \if{\n==3}{\embed{r1,4}}{\deux[\n]} </td> <td> \if{\n==2}{\embed{r1,4}}{\trois[\n]} </td>
#else
  \a</td><td>\embed{r1,4}</td>
  </tr><tr>
  <td>\b</td><td>\c
#endif
  </td></tr></table>
}

\answer{\name_answer}{\r}
