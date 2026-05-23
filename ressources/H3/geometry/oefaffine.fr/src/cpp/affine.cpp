target=affine
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

translation: liste, instruction

\integer{a=randint(1..8)*random(1,-1)}
\integer{b=randint(-8..8)}
\integer{c=randint(-10..10)}
\integer{c1=randint(1..10)}
\rational{c=\c/\c1}
\rational{d=\a*\c+\b}
\function{f=simplify(\a*x + (\b))}
\text{choix=random(1,2)}
\text{im=item(\choix,\liste)}

(permet de choisir antécédent ou image dans l'énoncé)
\rational{P=\choix=1? \d: \c}
syntaxe signifiant \d si \choix=1, \c sinon
\rational{rep=\choix=1 ? \c:\d}

\text{instruction=\name_enonce[1]
\(f(x) = \f\). \name_enonce[2]
\im \name_enonce[3] \P \name_enonce[4] \(f\).}

\statement{\instruction }
\answer{\im \name_enonce[3] \P}{\rep}{type=formal}
