target=Equation10 Equation11 Equation12 Equation13 Equation14

#if defined TARGET_Equation10
# define NUM ax+b&#61;c
#endif
#if defined TARGET_Equation11
# define NUM a(x+b)&#61;c
#endif
#if defined TARGET_Equation12
# define NUM ax+b&#61;cx+d
#endif
#if defined TARGET_Equation13
# define NUM ax+b&#61;c DEC
#endif
#if defined TARGET_Equation14
# define NUM ax+b&#61;cx+d DEC
#endif
#if defined TARGET_correquat1
# define TITRE Correspondance d'équations
#endif

#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

\integer{sizef=4}
\integer{confparm1=\confparm1=?1}

\text{champ=wims(record \confparm1 of src/generateur)}
\text{A=row(2,\champ)}
\text{B=row(3,\champ)}
\text{c=item(3,\A)}
\if{\B=}{
  \text{a=item(1,\A)}
  \text{b=item(2,\A)}
  \text{valeurs=wims(values \c*v for v=\a to \b)}
}{
  \text{valeurs=\B}
  \if{\c<0}{
    \text{valeurs=wims(replace internal , by ,- in \valeurs)}
  }
}
\text{valeurs=wims(listuniq \valeurs)}
\text{valeurs=shuffle(\valeurs)}

\text{m=item(1,\valeurs)}

#if defined TARGET_Equation10
\text{a=randint(2..9)}
\text{b=randint(2..99)}
\real{c=\m*\a+\b}
\real{d=\m}
\text{enonc1=\a}
\if{\b<0}{\text{enonc2= \b = \c}}{\text{enonc2= + \b = \c}}
#endif
#if defined TARGET_Equation11
\text{a=randint(2..9)}
\real{c=\m*\a}
\text{b=randint(1..abs(\m))}
\real{d=\m-\b}
\text{par=()}
\text{par1=wims(char 1 of \par)}
\text{par2=wims(char 2 of \par)}
\text{enonc1=\a \par1}
\if{\b<0}{\text{enonc2= \b \par2 = \c}}{\text{enonc2= + \b \par2= \c}}
#endif
#if defined TARGET_Equation12
\text{a=randint(5..19)}
\text{c=randint(2..\a-1)}
\real{e=\m*(\a-\c)}
\text{b=randint(1..29)}
\real{d=\e+\b}
\real{f=(\d-\b)/(\a-\c)}
\text{enonc1=\a}
\if{\b<0}{\text{enonc2= \b = \c}}{\text{enonc2= + \b = \c}}
\if{\d<0}{\text{enonc3= \d }}{\text{enonc3= + \d}}
#endif
#if defined TARGET_Equation13
\real{a=randint(20..90)/10}
\real{b=randint(20..199)/10}
\real{c=\m*\a+\b}
\real{d=\m}
\text{enonc1=\a}
\if{\b<0}{\text{enonc2= \b = \c}}{\text{enonc2= + \b = \c}}
#endif
#if defined TARGET_Equation14
\real{a=randint(50..190)/10}
\text{c=randint(2..\a-1)}
\real{b=randint(20..199)/10}
\real{e=\m*(\a-\c)}
\real{d=\e+\b}
\real{f=(\d-\b)/(\a-\c)}

\text{enonc1=\a}
\if{\b<0}{\text{enonc2= \b = \c}}{\text{enonc2= + \b = \c}}
\if{\d<0}{\text{enonc3= \d }}{\text{enonc3= + \d}}
#endif
\statement{
  \name_enonce
<span class="larger">
#if defined TARGET_Equation10 || defined TARGET_Equation11 || defined TARGET_Equation13
\(\enonc1 x \enonc2\).
#endif
#if defined TARGET_Equation12 || defined TARGET_Equation14
  \(\enonc1 x \enonc2 x \enonc3\).
#endif
</span>
<div class="wims_question"><label for="reply1">\name_then:</label> <span class="larger">
  \embed{r1,\sizef}.</span>
</div>
<div class="wims_instruction">\name_instruction</div>
}
#if defined TARGET_Equation10 || defined TARGET_Equation11 || defined TARGET_Equation13
\answer{}{\d}{type=numeric}
#endif
#if defined TARGET_Equation12 || defined TARGET_Equation14
\answer{}{\f}{type=numeric}
#endif
\latex{
  \begin{statement}
  \name_enonce
#if defined TARGET_Equation10 || defined TARGET_Equation11 || defined TARGET_Equation13
  \(\enonc1 x \enonc2.\)
#endif
#if defined TARGET_Equation12 || defined TARGET_Equation14
  \(\enonc1 x \enonc2 x \enonc3.\)
#endif
\par
\(x = \cdots\)
\end{statement}
}
