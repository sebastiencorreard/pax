target=Equation1 Equation2 Equation3 Equation4 Equation5 Equation6

#include "author.inc"
\precision{10000}
#if defined TARGET_Equation1
# define NUM a - x &#61; b
#endif
#if defined TARGET_Equation2
# define NUM a / x &#61; b
#endif
#if defined TARGET_Equation3
# define NUM x * a &#61; b
#endif
#if defined TARGET_Equation4
# define NUM a + x &#61; b
#endif
#if defined TARGET_Equation5
# define NUM x / a &#61; b
#endif
#if defined TARGET_Equation6
# define NUM x - a &#61; b
#endif
#include "lang_titles.inc"
#include "lang.inc"
\integer{sizef=4}
\integer{confparm1=\confparm1=?1}
#include "valeurs.inc"
\text{a=item(1,\valeurs)}
\text{b=item(2,\valeurs)}
#if defined TARGET_Equation1
\if{\confparm1=1 or \confparm1=3 or \confparm1=5}{\if{\a<\b}{
  \real{\t=\a}
  \real{\a=\b}
  \real{\b=\t}}
}
\real{r=\a-\b}
\text{enonce1=\a -}
\text{enonce2= = \b}
#endif
#if defined TARGET_Equation2
\real{r=\b}
\real{d=\a*\b}
\text{enonce1=\d \div }
\text{enonce2= = \a}
#endif
#if defined TARGET_Equation3
\real{d=\b*\a }
\real{r=\b}
\text{enonce1=\a \times}
\text{enonce2= = \d}
#endif
#if defined TARGET_Equation4
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
#if defined TARGET_Equation5
\real{r=\a*\b}
\text{enonce1=}
\if{\a>0}{\text{enonce2= \div \a = \b}}{\text{enonce2= \div (\a) = \b}}
#endif
#if defined TARGET_Equation6
\real{r=\a+\b}
\text{enonce1=}
\if{\a>0}{\text{enonce2= - \a = \b}}{\text{enonce2= - (\a) = \b}}
#endif
\statement{\name_enonce
<span class="larger"> \(\enonce1 x \enonce2 \).</span>
<div class="wims_question">\name_then
<span class="larger">\embed{r1,\sizef}</span>.
</div>}
\answer{}{\r}{type=numeric}
\latex{
  \begin{statement}
  \name_enonce
  \(\enonce1\ x\ \enonce2 .\)
  \par
  \(x= \cdots\)
\end{statement}
}
