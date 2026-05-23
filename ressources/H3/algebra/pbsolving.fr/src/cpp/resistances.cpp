target=resistances

\language{fr}
\author{Jean-Baptiste, Frondas}
\email{jbfrondas@gmail.com}
\format{html}
\precision{10000}
\computeanswer{no}

\integer{R1=random(1..99)}
\integer{R2=random(1..99)}
\rational{R=(\R1+\R2)/(\R1*\R2)}

#define NUM 2
#include "lang_titles.inc"
#include "lang.inc"

\statement{\enonce}
\hint{\monaide}

\answer { R  \( (\Omega) \)}{ \R }
\solution{}

\latex{
\begin{statement}
\enonce \monaide
\end{statement}

\begin{solution}
\(R= \R \Omega\)
\end{solution}
}
