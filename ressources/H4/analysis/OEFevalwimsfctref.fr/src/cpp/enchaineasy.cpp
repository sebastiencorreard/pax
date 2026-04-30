target=enchaineasy1 enchaineasy2 enchaineasy3 enchaineasy4 enchaineasy5
#define TITRE Enchainement simple de fonctions
\language{fr}
\range{-5..5}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}
#if defined TARGET_enchaineasy1
# define NUM 1
#endif
#if defined TARGET_enchaineasy2
# define NUM 2
#endif
#if defined TARGET_enchaineasy3
# define NUM 3
#endif
#if defined TARGET_enchaineasy4
# define NUM 4
#endif
#if defined TARGET_enchaineasy5
# define NUM 5
#endif
#include "lang_titles.inc"
 \integer{a=randint(2..8)*randint(1,-1)}
 \integer{b=randint(1..8)*randint(1,-1)}
#if defined TARGET_enchaineasy5
 \function{fref1=texmath(x^2)}
 \function{fref2=texmath(1/x)}
 \text{aff1=\a x}

 \function{f1=\a/(x^2)}
 \function{f2=1/(\a*x^2)}
 \function{f3=1/(\a*x)^2}

 \text{e1=\(\begin{array}{ccccccc}& \fref1&&\fref2&&\aff1&\\ x & \longmapsto &\cdots &\longmapsto & \cdots & \longmapsto & \cdots\end{array})}
 \text{e2=\(\begin{array}{ccccccc}& \fref1&&\aff1&&\fref2&\\ x & \longmapsto &\cdots &\longmapsto & \cdots & \longmapsto & \cdots\end{array})}
 \text{e3=\(\begin{array}{ccccccc}& \aff1&&\fref1&&\fref2&\\ x & \longmapsto &\cdots &\longmapsto & \cdots & \longmapsto & \cdots\end{array})}
#else

#if (defined TARGET_enchaineasy1  || defined TARGET_enchaineasy2 )
 \function{fref=texmath(x^2)}
 \text{aff1=\a x}
 \function{aff2=texmath(x+\b)}

 \function{f1=texmath(maxima(\a*x^2+\b))}
 \function{f2=texmath(maxima((\a*x)^2+\b))}
 \function{f3=texmath(maxima((\a*x+\b)^2))}
#endif
#if (defined TARGET_enchaineasy3  || defined TARGET_enchaineasy4 )
 \function{fref=texmath(1/x)}
 \text{aff1=\a x}
 \function{aff2=texmath(x+\b)}

 \function{f1=texmath(maxima(\a/x+\b))}
 \function{f2=texmath(maxima(1/(\a*x)+\b))}
 \function{f3=texmath(maxima(1/(\a*x+\b)))}
#endif

 \text{e1=\(\begin{array}{ccccccc}& \fref&&\aff1&&\aff2&\\ x & \longmapsto &\cdots &\longmapsto & \cdots & \longmapsto & \cdots\end{array})}
 \text{e2=\(\begin{array}{ccccccc}& \aff1&&\fref&&\aff2&\\ x & \longmapsto &\cdots &\longmapsto & \cdots & \longmapsto & \cdots\end{array})}
 \text{e3=\(\begin{array}{ccccccc}& \aff1&&\aff2&&\fref&\\ x & \longmapsto &\cdots &\longmapsto & \cdots & \longmapsto & \cdots\end{array})}
#endif

 \integer{rep=randint(1..3)}
#if (defined TARGET_enchaineasy1 || defined TARGET_enchaineasy3  || defined TARGET_enchaineasy5 )
 \text{lstquest=\(\f1),\(\f2),\(\f3)}
 \text{lstrep=\e1,\e2,\e3}
 \text{quest=\lstquest[\rep]}
\statement{
  On considère une fonction \(f) définie par
<div class="wimscenter">\(f(x)=)\quest.</div>
  Cocher l'enchainement de fonctions de référence correspondant à \(f).
<ol>
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
</ol>
}
\answer{Enchainement ?}{\rep;\lstrep}{type=radio}
#else
 \text{lstrep=\(\f1),\(\f2),\(\f3)}
 \text{lstquest=\e1,\e2,\e3}
 \text{quest=\lstquest[\rep]}
\statement{
  On considère l'enchainement de fonctions ci-dessous&nbsp;:
<div class="wimscenter">\quest.</div>
  Cocher l'expression algébrique correspondant à cet enchainement.
<ol>
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
</ol>
}
\answer{Expression algébrique ?}{\rep;\lstrep}{type=radio}
#endif
