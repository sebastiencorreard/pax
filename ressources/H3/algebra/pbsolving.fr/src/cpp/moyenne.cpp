target=moyenne
\language{fr}
\author{Jean-Baptiste, Frondas}
\email{jbfrondas@gmail.com}
\format{html}
\precision{10000}
\computeanswer{no}

\text{genre=random(girl,boy)}
% genre dans le fichier de traduction

\text{prenom=slib(lang/fname, \genre )}

\integer{n=random(4..7)}
\text{notes=}
\real{somme=0}
\for{u=1 to \n}{
  \integer{s=randint(0..40)}
  \real{note=\s/2}
  \text{notes=wims(append item \note to \notes)}
  \real{somme=\somme+\note}
}
\real{moyenne=(\somme)/\n}

\integer{m=\n-1}
\text{liste=wims(replace item number \n by in \notes)}
\text{liste=wims(nonempty items \liste)}
#define NUM 3
#include "lang_titles.inc"
#include "lang.inc"

\statement{\enonce
}

\answer { \lastnote }{ \notes[\n] }


\latex{
\begin{statement}
\enonce
\end{statement}

\begin{solution}
\solution
\end{solution}
}
