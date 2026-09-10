target=terminologie2 terminologie3
%% des intervalles et ensembles de nombres
\language{fr}
\computeanswer{yes}
\precision{1000}
\format{html}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_terminologie2
\text{alltraductions=\(x \in I\),
  \(x \notin I\),
  \(E=\emptyset\),
  \(I \cap J = \emptyset\),
  \(x \in I\cap J\),
  \(I \subseteq J\),
  \(I \subset J\),
  \(x \in I \cup J\),
  \(I\) &nsub; \(J\),
  \(I = &#91; a ; b &#93;\),
  \(x < a\),
  \(x \leq a \),
  \(x \in &#93; a ; +\infty &#91;\),
  \(x \in &#91; a ; +\infty &#91;\),
  \(x \in &#91; a ; b &#93;\),
  \(a \leq x \leq b\),
  \(I = &#93;  a ; b &#91; \) ,
  \(x \geq 0\),
  \(x > 0\),
  \(f(a) = 0\),
  \(f(x) = 0 \Longleftrightarrow x = a \; ou \; x = b\)}
#endif
#if defined TARGET_terminologie3
\text{alltraductions= \(f = u*v\),
\(f = k*u*v\),
\(f = u + v\),
\(f = k*(u+v)\),
\(f = u - v\),
\(f = (u)/(v)\),
\(f = u^2\),
\(f = u^3\),
\(f = sqrt(u) \),
\(f = 2 u + v\),
\(f = 3 v + u\),
\(f = u^2 + v/3\),
\(f = k/(v)\),
\(f = (u+ v)^2\),
\(f = 1/(u+ v)\),
\(f = k*u/(v)^2\),
\(f = k*u/(sqrt(v))\),
\(f = (u+v)^2\),
\(f = (u/v)^2\),
\(f = (u-v)^3\)}
#endif
\text{cnt=items(\alltraductions)}
\text{ind=shuffle(\cnt)}
\text{enonces=\allenonces[\ind[1]]}
\for{i = 2 to 8}{\text{enonces=\enonces,\allenonces[\ind[\i]] }}
\text{traductions=\alltraductions[\ind[1]]}
\for{i = 2 to 8}{\text{traductions=\traductions,\alltraductions[\ind[\i]] }}
#if defined TARGET_terminologie2
\text{enonce0=}
#endif
#if defined TARGET_terminologie3
\text{enonce0=\(f\), \(u\) \name_and \(v\) \name_enonce0 \(I\).}
#endif
\statement{
<div class="monenonce">
\enonce0 \name_enonce
</div>
<div class="wims_instruction">\name_instruction</div>
<div class="wimscenter">
\embed{reply1,80 x 300 x 300}
</div>
}

\answer{}{\enonces;\traductions}{type=correspond}{option=split,shuffle}
