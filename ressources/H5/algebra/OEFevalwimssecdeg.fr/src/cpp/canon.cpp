target=canon1 canon2 canon3 canon4 canon5 canon6
\author{Régine, Mangeard;Maguy, Bruno}
\keywords{trinomial}
\email{regine@mangeard.fr}
\format{html}
\precision{100}
#if defined TARGET_canon1
# define NUM 1
#endif
#if defined TARGET_canon2
# define NUM 2
#endif
#if defined TARGET_canon3
# define NUM 3
#endif
#if defined TARGET_canon4
# define NUM 4
#endif
#if defined TARGET_canon5
# define NUM 5
#endif
#if defined TARGET_canon6
# define NUM 6
#endif
#include "lang_titles.inc"
#if defined TARGET_canon1
\integer{a=1}
\integer{b=2*randint(1..9)}
\integer{c=randint(1..9)*randint(1,-1)}
#endif
#if defined TARGET_canon2
\integer{a=1}
\integer{b=-2*randint(1..9)+1}
\integer{c=randint(1..9)*randint(1,-1)}
#endif
#if defined TARGET_canon3
\integer{a=1}
\integer{b=randint(1..9)*randint(1,-1)}
\integer{c=0}
#endif
#if defined TARGET_canon4
\integer{a=randint(2..9)}
\integer{b=randint(1..9)*randint(1,-1)}
\integer{c=randint(1..9)*randint(1,-1)}
#endif
#if defined TARGET_canon5
\integer{a=-randint(1..9)}
\integer{b=randint(1..9)*randint(1,-1)}
\integer{c=randint(1..9)*randint(1,-1)}
#endif
#if defined TARGET_canon6
%% exercice rajouté par bpr
\integer{a=randint(2..9)*randint(1,-1)}
\integer{b=randint(1..9)*randint(1,-1)}
\integer{c=randint(1..9)*randint(1,-1)}
#endif

\text{eqx=texmath(maxima(\a*x^2+\b*x+\c))}
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

#if defined TARGET_canon6
\rational{cc=\sc \cc * \a}
\text{sc=\cc>0?+:-}
\text{ic=\cc>0?1:2}
\rational{cc=abs(\cc)}
#endif

\text{instruction=Mettre sous forme canonique le polynôme \(P(x)=\eqx \):}

\statement{
\instruction
#if (defined TARGET_canon4 || defined TARGET_canon5)
<div class="wimscenter">\(P(x)=\)\embed{reply1,2}\leftpar2
  (\(x)\embed{reply2}\embed{reply3,2})<sup>2</sup>\embed{reply4}\embed{reply5,3}\rightpar2</div>
#endif
#if defined TARGET_canon6
<div class="wimscenter">\(P(x)=\)\embed{reply1,2}(\(x)\embed{reply2}\embed{reply3,2})<sup>2</sup>\embed{reply4}\embed{reply5,3}</div>
#endif
#if defined TARGET_canon1 || defined TARGET_canon2 || defined TARGET_canon3
<div class="wimscenter">\(P(x)= \)(\(x\)\embed{reply1}\embed{reply2,2})<sup>2</sup>\embed{reply3}\embed{reply4,3}</div>
#endif
}
#if defined TARGET_canon4 || defined TARGET_canon5 || defined TARGET_canon6
\answer{coef 1}{\ca}{type=numeric}
#endif
\answer{signe 1}{\ib;+,-}{type=menu}
\answer{coef 2}{\cb}{type=numexp}
\answer{signe 2}{\ic;+,-}{type=menu}
\answer{coef 3}{\cc}{type=numexp}
