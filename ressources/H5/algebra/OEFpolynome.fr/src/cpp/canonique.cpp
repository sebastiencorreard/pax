target=canon1 canon2 canon3
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\precision{100}
#define TITRE Mise sous forme canonique
#if defined TARGET_canon1 
\title{TITRE 1}
\integer{a=1}
\integer{b=2*randint(1..9)*randint(1,-1)}
\integer{c=randint(1..9)}
#endif
#if defined TARGET_canon2 
\title{TITRE 2}
\integer{a=1}
\integer{b=2*randint(1..9)*randint(1,-1)+1}
\integer{c=randint(1..9)}
#endif
#if defined TARGET_canon3 
\title{TITRE 3}
\integer{a=randint(2..9)*randint(1,-1)}
\integer{b=2*randint(1..9)*randint(1,-1)}
\integer{c=randint(1..9)}
#endif
\text{eqx=texmath(\a*x^2+\b*x+\c)}
\integer{ca=\a}
\rational{cb=\b / (2 * \a)}
\text{sb=\cb<0?-:+}
\text{ib=\cb<0?2:1}
\rational{cb=\cb<0?-\cb}
\integer{d=(\b)^2-4*\a*\c}
\rational{cc=\d / (4*(\a)^2)}
\text{sc=\cc>0?-:+}
\text{ic=\cc>0?2:1}
\rational{cc=abs(\cc)}

\statement{
Mettre sous forme canonique le polynôme \(P(x)=\eqx):
#if defined TARGET_canon3 
<div class="wimscenter">\(P(x)=)\embed{reply1,2}((\(x)\embed{reply2}\embed{reply3,2})<sup>2</sup>\embed{reply4}\embed{reply5,3})</div>
}
\answer{coef 1}{\ca}{type=numeric}
#else
<div class="wimscenter">\(P(x)=)(\(x)\embed{reply1}\embed{reply2,2})<sup>2</sup>\embed{reply3}\embed{reply4,3}</div>
}
#endif
\answer{signe 1}{\ib;+,-}{type=menu}
\answer{coef 2}{\cb}{type=numeric}
\answer{signe 2}{\ic;+,-}{type=menu}
\answer{coef 3}{\cc}{type=numeric}
