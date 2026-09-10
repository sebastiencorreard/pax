target=oefapproch5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\format{html}
\precision{10000}

\integer{ch=randint(1..6)}
\integer{a=randint(1..9)*10000+randint(1..8)*1000+randint(0..9)*100+randint(0..9)*10+randint(1..9)}
\integer{b=randint(0..99)}

\text{sg=+,-}
\real{v=\b+\a/100000}

\integer{nb1=floor(\v)}
\integer{nb4=ceil(\v)}

\real{nb2=floor(\v*10)/10}
\real{nb5=ceil(\v*10)/10}

\real{nb3=floor(\v*100)/100}
\real{nb6=ceil(\v*100)/100}

\if{\nb4=\nb5}{\text{nb5=\nb5.0}}

\text{nb=\nb1,\nb2,\nb3,\nb4,\nb5,\nb6}
\text{rep=wims(replace internal . by , in \nb[\ch])}
\text{v=slib(numeration/ecriturenombre \v)}
\text{v=wims(replace internal . by , in \v)}
\statement{\name_statement[1] \v. \name_statement[2] \mot[\ch] :
 \embed{r1,8}
<div class="wims_instruction">\name_inst</div>
}

\answer{}{\rep}{type=raw}

\latex{
\begin{statement}
\name_statement:
  \name_statement[1] \v. \name_statement[2] \mot[\ch]
\end{statement}
}

