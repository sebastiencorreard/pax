target=ordphase1 ordphase2 date1 date2 date1P date2P ordphase1P
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_ordphase1 || defined TARGET_ordphase2 || defined TARGET_date1 || defined TARGET_date2

#endif
#if defined TARGET_date1P || defined TARGET_date2P || defined TARGET_ordphase1P
# define PHOTO
#endif
\text{r=2}
\text{list=pari([[1,1],[sqrt(2)/2,1],[0,1],[-sqrt(2)/2,1],[-1,-1],[-sqrt(2)/2,-1],[0,-1],[sqrt(2)/2,-1]])}
#include "color.inc"
\text{centre=0,0}
\text{range=2}
\text{angle=-90,90,270}
\text{direct=3}
\integer{direct1=\direct%2} 1
\integer{direct2=(\direct-\direct1)/2} 1
\text{ls=0,-1,1,0}
\text{s=}
\text{s1=}
\text{signe=1}
\text{width=80}
#ifdef PHOTO
\text{Images=wims(makelist <img src="\imagedir/moon/x.gif" width="\width" alt=""> for x=1 to 8)}
\text{Dessin=\Images}
#else
\text{Dessin=}
\text{head=xrange -\range,\range
yrange -\range,\range}
\for{je=1 to 8}{
# include "lune.inc"
  \text{dessinimg=draw(\width,\width
\head
\phase)}
  \text{Dessin=\Dessin <img src="\dessinimg" alt="">,}
}
\text{Dessin=wims(nonempty items \Dessin)}
#endif
#if defined TARGET_ordphase2
hemisphere SUD
\text{hemi=\name_nordsouth[2]}
\text{Dessin=\Dessin[1,8,7,6,5,4,3,2]}
#endif
#if defined TARGET_ordphase1 || defined TARGET_ordphase1P
hemisphere NORD
\text{hemi=\name_nordsouth[1]}
#endif
#if defined TARGET_ordphase1 || defined TARGET_ordphase2 || defined TARGET_ordphase1P
\text{transl=randint(1..8)}
\text{transl=pari(vector(8,j,lift(Mod(j+\transl,8))+1))}
\text{Dessin=\Dessin[\transl]}
\statement{
  <div class="wims_question">\name_enonce \hemi.</div>
  <div class="wimscenter">\Dessin[1]</div>
  \embed{r1,8x120}
}
\answer{\Dessin[1]}{\Dessin[2..-1];}{type=reorder}
#endif
#if defined TARGET_date1 || defined TARGET_date1P || defined TARGET_date2 || defined TARGET_date2P
# if defined TARGET_date1P || defined TARGET_date2P
\text{hemi=1}
# else
\text{hemi=\confparm1}
\text{hemi=\hemi=?1}
\text{hemi=\hemi=3?randitem(1,2)}
# endif
\text{n_hemi=\name_nordsouth[\hemi]}
\text{Dessin=\hemi=2?\Dessin[1,8,7,6,5,4,3,2]}
\text{size=\width x\width}
\text{choix=shuffle(8)}
\text{choix=\choix[1,2]}
\text{rep=\choix[2]}
\integer{shift=\choix[1]<\choix[2] ? \choix[2]-\choix[1]:8+\choix[2]-\choix[1]}
\real{jour=28/8*\shift}
\text{vv=wims(values x for x=1 to 8)}

\statement{
  <div class="wims_question">
  \name_where \n_hemi. \name_enonce[1;]:
  <div class="wimscenter">
  \Dessin[\choix[1]].
</div>
  \name_enonce[2;1] \jour \name_enonce[2;2]?
  \embed{r1,\size}
  </div>
# ifdef PHOTO
# include "credits.inc"
# endif
}
# if defined TARGET_date1 || defined TARGET_date1P
\answer{}{\Dessin[\rep];\Dessin}{type=clickfill}{option=keeporder}
# endif
# if defined TARGET_date2 || defined TARGET_date2P
\answer{}{\Dessin[\rep];\Dessin}{type=clickfill}{option=shuffle}
# endif
#endif
