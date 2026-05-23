target=touche1 touche2 touche3 touche4 touche5
#define TITRE Touches de la calculette
#include "author.inc"
\text{bad=<img src="\imagedir/sqrt.gif" alt="">,<img src="\imagedir/square.gif" alt="">,<img src="\imagedir/inv1.gif" alt="">,<img src="\imagedir/inv2.gif" alt="">,Aucune  de ces touches}

#if defined TARGET_touche1
 \title{TITRE 1}
 \integer{a=randint(31..99)}
 \integer{a=0 isin \a?\a+1}
 \text{enonce=\(\a^2)}
 \text{good=2}
#endif
#if defined TARGET_touche2
 \title{TITRE 2}
 \integer{a=randint(31..99)}
 \integer{a=0 isin \a?\a+1}
 \text{enonce=\(\sqrt{\a})}
 \text{good=1}
#endif
#if defined TARGET_touche3
 \title{TITRE 3}
 \integer{a=randint(31..99)}
 \integer{a=0 isin \a?\a+1}
 \text{enonce=la racine carrée de \a}
 \text{good=1}
#endif
#if defined TARGET_touche4
 \title{TITRE 4}
 \integer{a=randint(31..99)}
 \integer{a=0 isin \a?\a+1}
 \text{enonce=le carré de \a}
 \text{good=2}
#endif
#if defined TARGET_touche5
 \title{TITRE 5}
 \integer{a=randint(31..99)}
 \integer{a=0 isin \a?\a+1}
 \text{enonce=le double de \a}
 \text{good=5}
#endif

\statement{
  Pour calculer <span class="wims_emph">\enonce</span>,
  quelle touche de la calculette doit-on utiliser ?
  <div class="wimscenter">
<ul class="inline"><li>\embed{r1,1}</li><li>\embed{r1,2}</li><li>\embed{r1,3}</li><li>
\embed{r1,4}</li><li>\embed{r1,5}</li></ul>
</div>}

\answer{}{\good;\bad}{type=click}
