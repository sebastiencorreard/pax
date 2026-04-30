target=31 32
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

#include "level.inc"
\text{polycnt=rows(\poly)}
\text{choix=shuffle(\polycnt)}
\text{poly=row(\choix[1],\poly)}

\text{patroncode=slib(geo2D/polynet \poly[1;1],raw)}

\text{codesommet=wims(declosing \patroncode[1])}
\text{somcnt=\poly[2]}
\text{list=}
\text{codesommet0=}
\for{j=0 to \somcnt-1}{
  \text{somcoord=wims(select \codesommet where column 3 = \j)}
  \text{tmp=items(\somcoord[;1])}
  \if{\tmp>=3}{\text{list=wims(append item \j to \list)}}
  \text{codesommet0=\tmp>1? \codesommet0;\somcoord[;1,2]}
}
\if{\list=}{
  \for{j=0 to \somcnt-1}{
    \text{somcoord=wims(select \codesommet where column 3 = \j)}
    \text{tmp=items(\somcoord[;1])}
    \if{\tmp>=2}{\text{list=wims(append item \j to \list)}}
  }
}

\text{som=randitem(\list)}
\text{somcoord0=wims(select \codesommet where column 3 = \som)}
\text{position=}
\text{somcoord_=}
\for{j=1 to \somcnt}{
  \text{position=\position,wims(positionof row \somcoord0[\j;] in \codesommet)}
  \if{\j>=2}{\text{somcoord_=\somcoord_,\somcoord0[\j;1,2]}}
}
\text{position=wims(nonempty items \position)}
\text{somcoord=wims(nonempty items \somcoord_)}
\text{codesommet0=wims(replace internal \somcoord0[\position[1];1,2] by in \codesommet0)}
\text{codesommet0=\codesommet0;\somcoord}
\text{codesommet0=wims(replace internal ; by , in \codesommet0)}
\text{codesommet0=wims(nonempty items \codesommet0)}

\text{patron_=slib(geo2D/offdraw \patroncode, size=400 vertex_legend=[\position[1],X])}
\text{patron2=slib(geo2D/offdraw \patroncode, html size=400 vertex_legend)}
\text{patron=\patron_[2..-1;];snaptopoints \codesommet0}

\text{size=wims(word 2 to -1 of \patron_[1;])}
\text{pol=slib(geo3D/polyhedra \poly[1;1],300,300,show=[S,A,F] scale=0.8 color=[black,green,yellow,blue] width=[6,2] id=0)}
#if defined TARGET_31
\text{nom=wims(lookup \poly[1;1] in data/polyedre_off/index.\lang)}
\text{nom=\nom[1]}
#endif
\statement{
\name_instruction
#if defined TARGET_32
<div class="wimscenter">
#endif
#if defined TARGET_31
<div class="wims_columns">
 <div class="medium_size img_col">
  \pol
  <div class="wimscenter">\nom</div>
 </div><div class="medium_size text_col">
#endif
\embed{r1,\size[1]x\size[2]}
</div>
#if defined TARGET_31
</div>
#endif
}
\answer{}{[\patron];crosshairs,\somcoord}{type=draw}{option=split precision=10}
#if defined TARGET_32
# include "feedback.inc"
#endif
