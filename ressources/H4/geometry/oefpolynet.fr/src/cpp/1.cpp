target=11 12
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{N=3}
#include "level.inc"
\text{poly=row(\choix[1..\N],\poly)}
\text{rep=randint(1..\N)}
\text{list=wims(makelist x for x=1 to \N)}
\text{tt=}
#if defined TARGET_11
\for{j=1 to \N}{
  \text{tt=\tt, slib(geo2D/polynet \poly[\j;1],size=200 html)}
  \text{tm=\j=\rep?slib(geo3D/polyhedra \poly[\j;1],300,300,scale=0.8 show=[S,A,F] color=[black,green,yellow,blue] width=[6,2] id=\j)}
}
#endif
#if defined TARGET_12
\for{j=1 to \N}{
  \text{tm=\j=\rep?slib(geo2D/polynet \poly[\j;1],size=200 html)}
  \text{tt=\tt,slib(geo3D/polyhedra \poly[\j;1],300,300,scale=0.8 show=[S,A,F] color=[black,green,yellow,blue] width=[6,2] id=\j)}
}
#endif
\text{tt=wims(nonempty items \tt)}
\text{pol1=slib(geo3D/polyhedra \poly[1;1],300,300,show=[S,A,F] color=[black,green,yellow,blue] width=[6,2] id=11)}
\text{pol2=slib(geo3D/polyhedra \poly[2;1],300,300,show=[S,A,F] color=[black,green,yellow,blue] width=[6,2] id=12)}
\text{pol3=slib(geo3D/polyhedra \poly[3;1],300,300,show=[S,A,F] color=[black,green,yellow,blue] width=[6,2] id=13)}

\statement{
  \name_instruction
 <div class="wimscenter">\tm</div>
    <ul class="inline">
\for{k=1 to \N}{<li>\embed{r1,\k} \tt[\k]</li>}
    </ul>
  </div>
}
\answer{}{\rep;\list}{type=radio}
\text{nom=wims(lookup \poly[\rep;1] in data/polyedre_off/index.\lang)}
\feedback{1=1}{\name_nom <span class="wims_emph">\nom</span>.}
