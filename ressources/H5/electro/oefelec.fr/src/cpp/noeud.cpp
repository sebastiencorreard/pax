target=noeud

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{n=random(4..8)}
\integer{m=randint(1..\n)}
\text{somme=0}
\text{dessin= xrange -2,2.2
 yrange -2,2.2}
\text{Intensite=}
\for{i=1 to \n}{
  \text{signe=randitem(1,-1)}
  \integer{I=\i<\n? randint(-10..10): -(\signe)*(\somme)}
  \real{somme=\somme+(\I)*(\signe)}
  \text{Intensite=\Intensite,\I}
  \text{dessin=\dessin
segment 0,0,cos(2*pi*\i/\n),sin(2*pi*\i/\n), black}
  \if{\signe=1}{
    \text{dessin=\dessin
    arrow  cos(2*pi*\i/\n)*0.75,sin(2*pi*\i/\n)*.75,cos(2*pi*\i/\n)*0.5,sin(2*pi*\i/\n)*.5, 10,black}
    }
    {\text{dessin=\dessin
    arrow  cos(2*pi*\i/\n)*0.5,sin(2*pi*\i/\n)*.5,cos(2*pi*\i/\n)*0.75,sin(2*pi*\i/\n)*.75, 10,black}
    }
  \if{\i <>\m}{
  \text{dessin= \i>\n/4 and \i<3*\n/4? \dessin
  text blue, cos(2*pi*\i/\n)*1.6,sin(2*pi*\i/\n)*1.6,medium, \I A
  :
  \dessin
  text blue, cos(2*pi*\i/\n)*1.4,sin(2*pi*\i/\n)*1.4,medium, \I A}
  }
  {\text{dessin=\dessin
    text red, cos(2*pi*\i/\n)*1.5,sin(2*pi*\i/\n)*1.5,medium, I}
  }
}
\text{Intensite=wims(nonempty items \Intensite)}
\text{rep=item(\m,\Intensite)}

\statement{\name_statement[1;]:
<div class="wimscenter">\draw{200,200}{\dessin}</div>
\name_statement[2;]?
<div class="wims_instruction">\name_instruction</div>}

\answer{\(I)}{\rep A}{type =units}

\hint{\name_hint}
