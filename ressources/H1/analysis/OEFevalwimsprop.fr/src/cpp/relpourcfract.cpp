target=oefrelpourcfract1 oefrelpourcfract2 oefrelpourcfract3

#include "author.inc"
\precision{100000}

#if defined TARGET_oefrelpourcfract1
# define NUM 1
#endif
#if defined TARGET_oefrelpourcfract2
# define NUM 2
#endif
#if defined TARGET_oefrelpourcfract3
# define NUM 3
#endif
#include "lang_titles.inc"
#include "lang.inc"
\keywords{percents, fraction}

#if defined TARGET_oefrelpourcfract1
\integer{num=randint(5..99)}
\integer{den=100}
\real{rep=\num/\den}
\integer{pgcd=gcd(\num,\den)}
\if{\pgcd<>1}{\integer{newnum=\num/\pgcd}
\integer{newden=\den/\pgcd}}
\statement{
\name_instruction
<div class="wimscenter">
\special{mathmlinput [\num \% = \frac{reply1}{reply2}],4 noanswer
reply1
reply2
}
</div>
}
\answer{}{\rn}{type=numeric}
\answer{}{\rd}{type=numeric}
\condition{\rep=\rn/\rd}
\solution{\(\num \% = \frac{\num}{\den}\).
\if{\pgcd<>1}{<p>On peut simplifier la fraction.</p>
\(\num \% = \frac{\num}{\den}=\frac{\pgcd \times \newnum}{\pgcd \times \newden}=\frac{\newnum}{\newden}\).</p>}}
\latex{
\begin{statement}
\name_instruction\par
\[ \num \% =\dfrac{\ldots}{\ldots} \]
\end{statement}

\begin{solution}
\[ \num \%= \dfrac{\num}{100}\]
\end{solution}
}
#endif
#if defined TARGET_oefrelpourcfract2 || defined TARGET_oefrelpourcfract3
# if defined TARGET_oefrelpourcfract2
\integer{den=random(10,20,50)}
# else
\integer{den=random(2,4,5,25)}
# endif
\integer{num=randint(1..\den-1)}
\integer{p=100/\den}
\integer{rep=\num*\p}
\statement{
\name_instruction
<div class="wimscenter"><label for="reply1">\(\Large{\frac{\num}{\den}}\)=</label> \embed{r1,5} %</div>
}
\answer{}{\rep}{type=numeric}
\solution{On transforme la fraction donnée en une fraction égale de dénominateur 100.
<p>\(\frac{\num}{\den}=\frac{\num \times \p}{\den \times \p}=\frac{\rep}{100}=\rep \%\).</p>}
\latex{
\begin{statement}
\name_instruction\par
\[ \dfrac{\num}{\den}=\ldots \% \]
\end{statement}

\begin{solution}
\[ \dfrac{\num}{\den}=\rep \%\]
\end{solution}
}
#endif
