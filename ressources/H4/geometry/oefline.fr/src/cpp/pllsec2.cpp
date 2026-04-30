target=pllsec2

#include "header.inc"
#include "lang_titles.inc"

\keywords{lines}
\integer{n=randint(1..3)}

#include "lang.inc"

cas sécantes
\integer{p1 = randint(-5..5) }
\integer{b1= randint(-5..5)}
\integer{p2 = randint(-5..5)}
on évite le cas parallèle
\integer{p2=\p1=\p2 ? \p2+1:\p2}
on choisit l'abscisse du point M d'intersection
\integer{x0= randint(-3..3)}
on calcule son ordonnée sur la première droite
\integer{y0=\p1*\x0 + \b1}
on calcule l'ordonnée à l'origine de la deuxième droite pour que M soit aussi sur la deuxième droite
\integer{b2=\y0-\p2*\x0}
équations de droites
\text{y1=maxima(\p1*x+\b1)}
\text{y2=maxima(\p2*x+\b2)}
\text{y1=texmath(\y1)}
\text{y2=texmath(\y2)}
\integer{\rep1=2}
\text{etape2=reply2,reply3}
\text{enonce=\name_statement2}
\text{w=3}
cas parallèles
\integer{ k = random(-1,1)* randint(1..3)}
\text{y3=simplify(\p1*x+\k*\b1)}
\if{\n=1}{
\text{y2=\y3}
\integer{\rep1=1}
\text{enonce=\name_statement1 ?}
\text{etape2=reply4}
\if{\k=1 or \b1=0}{\text{rep4=1}}{\text{rep4=2}}
\text{w=5}}
Définition des étapes
\steps{reply1
\etape2}


\statement{<div class="wims_difficultylevel">\name_difflevel</div>
<p>\name_statement[1;] \(( \math_droite )\)
\name_statement[2;] \(y=\y1\) \name_and \((\math_droite')\) \name_statement[2;] \(y=\y2\).</p>
    \if{\step=1}
        {<div>\step. \name_statement[3;] \embed{reply1}.</div>
        }
    \if{\step=2}
        {<div>\step. \enonce</div>
        }
}

\answer{ }{\rep1;\name_options_list }{type=menu }{option= }{weight= \w}
\answer{\(x\) }{\x0 }{type=numeric }{option= }{weight= 3.5}
\answer{\(y\) }{\y0 }{type=numeric }{option= }{weight= 3.5 }
\answer{\name_answer?}{\rep4;\name_yesno}{type=radio }{option= }{weight= 5}
