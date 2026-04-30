target=enchainrange1 enchainrange2 enchainrange3 enchainrange4 enchainrange5
\language{fr}
\range{-5..5}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}

#if defined TARGET_enchainrange1
#define NUM 1
#endif
#if defined TARGET_enchainrange2
#define NUM 2
#endif
#if defined TARGET_enchainrange3
#define NUM 3
#endif
#if defined TARGET_enchainrange4
#define NUM 4
#endif
#if defined TARGET_enchainrange5
#define NUM 5
#endif
#include "lang_titles.inc"
%%%% la liste des objets que l'on peut cliquer pour résoudre l'exercice ###
\text{sgt=>}
\text{sge=\(\ge )}
\text{slt=<}
\text{sle=\(\le )}
\text{size=50x30x1}

\text{symboles=\slt,\sle,\sgt,\sge}
\text{swapsymb=2,1}
\integer{symbx1=randint(1..2)}
\integer{symbx2=randint(1..2)}

%%%% inégalité sur x ######
%%%%
\integer{a3=randint(1..10)}
\integer{a4=randint(1..10)}
\integer{a4=\a3=\a4?\a4+10:\a4}
\integer{a1=\a3>\a4?\a4:\a3}
\integer{a2=\a3>\a4?\a3:\a4}
\text{eqx=\a1 \symboles[\symbx1] \(x) \symboles[\symbx2] \a2}

\integer{a=randint(2..10)}

\text{clicList=
\slt,\sle
}

\integer{k=randint(1,2)}
\function{faff=\k=1?\a*x:x+\a}
\text{taff=\k=1?\a x:\a+x}

#if defined TARGET_enchainrange5
\function{fref1=texmath(maxima(x^2))}
\function{fref2=texmath(maxima(1/x))}
 \function{f1=\k=1?\a/(x^2):1/x^2+\a}
 \function{f2=\k=1?1/(\a*x^2):1/(x^2+\a)}
 \function{f3=\k=1?1/(\a*x)^2:1/(x+\a)^2}

 \text{e1=\(\begin{array}{ccccccc}& \fref1&&\fref2&&\taff&\\ x & \longmapsto &\cdots &\longmapsto & \cdots & \longmapsto & \cdots\end{array})}
 \text{e2=\(\begin{array}{ccccccc}& \fref1&&\taff&&\fref2&\\ x & \longmapsto &\cdots &\longmapsto & \cdots & \longmapsto & \cdots\end{array})}
 \text{e3=\(\begin{array}{ccccccc}& \taff&&\fref1&&\fref2&\\ x & \longmapsto &\cdots &\longmapsto & \cdots & \longmapsto & \cdots\end{array})}
 \text{lstench=\e1,\e2,\e3}
 \integer{chench=randint(1..3)}
 \text{ench=\lstench[\chench]}
\if{\chench=1}
  {
   \rational{val1min=evalue(\f1,x=\a1)}
   \rational{val1max=evalue(\f1,x=\a2)}
  }
\if{\chench=2}
  {
   \rational{val1min=evalue(\f2,x=\a1)}
   \rational{val1max=evalue(\f2,x=\a2)}
  }
\if{\chench=3}
  {
   \rational{val1min=evalue(\f3,x=\a1)}
   \rational{val1max=evalue(\f3,x=\a2)}
  }
   \rational{v1min=\val1min < \val1max?\val1min:\val1max}
   \rational{v1max=\val1min < \val1max?\val1max:\val1min}
   \text{s1g=\val1min < \val1max?\symbx1:\symbx2}
   \text{s1d=\val1min < \val1max?\symbx2:\symbx1}
   \rational{rep1=\v1min}
   \text{rep2=\symboles[\s1g]}
   \text{rep3=\symboles[\s1d]}
   \rational{rep4=\v1max}

#else
#if (defined TARGET_enchainrange1  || defined TARGET_enchainrange3 )
\function{fref=texmath(maxima(x^2))}
 \function{f1=\k=1?\a*x^2:x^2+\a}
 \function{f2=\k=1?(\a*x)^2:(x+\a)^2}
#endif
#if (defined TARGET_enchainrange2  || defined TARGET_enchainrange4 )
\function{fref=texmath(maxima(1/x))}
 \function{f1=\k=1?\a/x:1/x+\a}
 \function{f2=\k=1?1/(\a*x):1/(x+\a)}
#endif
 \text{e1=\(\begin{array}{ccccc}& \fref&&\taff&\\ x & \longmapsto &\cdots &\longmapsto & \cdots\end{array})}
 \text{e2=\(\begin{array}{ccccc}& \taff&&\fref&\\ x & \longmapsto &\cdots &\longmapsto & \cdots\end{array})}
 \text{lstench=\e1,\e2}
 \integer{chench=randint(1..2)}
 \text{ench=\lstench[\chench]}
   \rational{val1min=evalue(\f1,x=\a1)}
   \rational{val1max=evalue(\f1,x=\a2)}
   \rational{v1min=\val1min < \val1max?\val1min:\val1max}
   \rational{v1max=\val1min < \val1max?\val1max:\val1min}
   \text{s1g=\val1min < \val1max?\symbx1:\symbx2}
   \text{s1d=\val1min < \val1max?\symbx2:\symbx1}
   \rational{val2min=evalue(\f2,x=\a1)}
   \rational{val2max=evalue(\f2,x=\a2)}
   \rational{v2min=\val2min < \val2max?\val2min:\val2max}
   \rational{v2max=\val2min < \val2max?\val2max:\val2min}
   \text{s2g=\val2min < \val2max?\symbx1:\symbx2}
   \text{s2d=\val2min < \val2max?\symbx2:\symbx1}
 \if{\chench=1}
   {
   \text{grep=\v1min \symboles[\s1g] f(x) \symboles[\s1d] \v1max}
   \text{brep=\v2min \symboles[\s2g] f(x) \symboles[\s2d] \v2max}
   \rational{rep1=\v1min}
   \text{rep2=\symboles[\s1g]}
   \text{rep3=\symboles[\s1d]}
   \rational{rep4=\v1max}
   }
   {
   \text{brep=\v1min \symboles[\s1g] f(x) \symboles[\s1d] \v1max}
   \text{grep=\v2min \symboles[\s2g] f(x) \symboles[\s2d] \v2max}
   \rational{rep1=\v2min}
   \text{rep2=\symboles[\s2g]}
   \text{rep3=\symboles[\s2d]}
   \rational{rep4=\v2max}
   }
#endif
\statement{
  On considère une fonction \(f) définie par l'enchainement suivant&nbsp;:
<div class="wimscenter"> \ench.</div>
#if (defined TARGET_enchainrange1  || defined TARGET_enchainrange2 )
  Cocher l'encadrement de \(f(x)) correspondant à \eqx.
      <ul><li>\embed{r1,1}</li><li>\embed{r1,2}</li></ul>
}
\answer{Encadrement}{1;\grep,\brep}{type=checkbox}{option=shuffle}
#else
  Donner l'encadrement de \(f(x)) correspondant à \eqx.
<div class="wimscenter">\embed{reply1,5} \embed{reply2,\size} \(f(x)) \embed{reply3,\size} \embed{reply4,5} </div>
}
\answer{borne gauche}{\rep1}{type=numeric}
\answer{symbole gauche}{\rep2;\clicList}{type=clickfill}
\answer{symbole droite}{\rep3;\clicList}{type=clickfill}
\answer{borne droite}{\rep4}{type=numeric}
#endif
