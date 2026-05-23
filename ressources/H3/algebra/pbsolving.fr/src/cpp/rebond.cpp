target=rebond

\language{fr}
\author{Jean-Baptiste, Frondas}
\email{jbfrondas@gmail.com}
\format{html}
\precision{10000}
\computeanswer{no}

\text{genre=random(girl,boy)}
% Genre dans le fichier de traduction
\text{prenom=slib(lang/fname, \genre )}

% Mélange des expressions
\text{mix=shuffle(rows(\nombres))}
\text{nombresmix=\expression[\mix;]}

\integer{rebond=random(70..90)}

\integer{hauteurini=random(70..150)}
\integer{nombrerebond=random(2..6)}

\real{hauteurfinale=\hauteurini*((\rebond/100)^(\nombrerebond))}
\integer{hf=\hauteurfinale}

# define NUM 3
#include "lang_titles.inc"
#include "lang.inc"

\statement{\enonce}

\answer { \hauteur}{ \hf }

\solution{\solution}

\latex{
\begin{statement}
\enonce
\end{statement}

\begin{solution}
\solution
\end{solution}
}
