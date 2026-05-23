target=optrou1 optrou2 optrou3 optrou4 optrou5 optrou6

#include "lang_titles.inc"
#include "lang.inc"
#include "author.inc"
\precision{10000}

\integer{sizef=4}
\integer{confparm1=\confparm1=?1}

#include "valeurs.inc"

\text{a=item(1,\valeurs)}
\text{b=item(2,\valeurs)}

#if defined TARGET_optrou3
\real{d=\b*\a }
\real{r=\b}
\text{enonce1=\a \(\times\)}
\text{enonce2= = \d}
#endif
#if defined TARGET_optrou4
\if{\confparm1=1 or \confparm1=3 or \confparm1=5}{
  \if{\b<\a}{
    \real{\t=\a}
    \real{\a=\b}
    \real{\b=\t}
  }
}
\real{r=\b-\a}
\text{enonce1=\a +}
\text{enonce2= = \b}
#endif
#if defined TARGET_optrou5
\if{\confparm1=1 or \confparm1=3 or \confparm1=5}{
  \if{\a<\b}{
    \real{\t=\a}
    \real{\a=\b}
    \real{\b=\t}
  }
}
\real{r=\a-\b}
\text{enonce1=\a -}
\text{enonce2= = \b}
#endif
#if defined TARGET_optrou6
\real{r=\a*\b}
\text{enonce1=}
\if{\a>0}{\text{enonce2= \(\div\) \a = \b}}{\text{enonce2= \(\div\) (\a) = \b}}
#endif
#if defined TARGET_optrou1
\real{r=\a+\b}
\text{enonce1=}
\if{\a>0}{\text{enonce2= - \a = \b}}{\text{enonce2= - (\a) = \b}}
#endif
#if defined TARGET_optrou2
\real{r=\b}
\real{d=\a*\b}
\text{enonce1=\d \(\div\)}
\text{enonce2= = \a}
#endif
\statement{\name_enonce
<div class="wimscenter larger">
<label for="reply1">\enonce1</label> \embed{r1,\sizef} \enonce2.
</div>}

\answer{}{\r}{type=numeric}

\latex{
\begin{statement}
\name_enonce \enonce1 \(\cdots\) \enonce2.
\end{statement}
}
