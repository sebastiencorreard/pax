target=oefaxesym3
#include "lang.inc"
#define NUM 3
#include "lang_titles.inc"
#include "author.inc"
\keywords{symmetry}
#include "dessin3.inc"

\matrix{fig=<img src="\triaa" alt="">,<img src="\triab" alt="">,<img src="\triac" alt="">,\name_list[1],2
<img src="\triarecta" alt="">,<img src="\triarectb" alt="">,<img src="\triarectc" alt="">,\name_list[2],2
<img src="\triarectisoa" alt="">,<img src="\triarectisob" alt="">,<img src="\triarectisoc" alt="">,\name_list[3],1
<img src="\triaisoa" alt="">,<img src="\triaisob" alt="">,<img src="\triaisoc" alt="">,\name_list[4],1
<img src="\triaequia" alt="">,<img src="\triaequib" alt="">,<img src="\triaequic" alt="">,\name_list[5],2
<img src="\carrea" alt="">,<img src="\carreb" alt="">,<img src="\carrec" alt="">,\name_list[6],3
<img src="\recta" alt="">,<img src="\rectb" alt="">,<img src="\rectc" alt="">,\name_list[7],1
<img src="\losangea" alt="">,<img src="\losangeb" alt="">,<img src="\losangec" alt="">,\name_list[8],1
<img src="\cerfa" alt="">,<img src="\cerfb" alt="">,<img src="\cerfc" alt="">,\name_list[9],1
<img src="\quelca" alt="">,<img src="\quelcb" alt="">,<img src="\quelcc" alt="">,\name_list[10],2}

\integer{n=randint(1..10)}
\text{choix=row(\n,\fig)}
\text{des=\choix[1],\choix[2],\choix[3]}
\text{des=shuffle(\des)}
\text{rep=\choix[\choix[5]]}
\text{p=positionof(\rep,\des)}

\statement{
<div class="wimscenter">\embed{r1}</div>
  \name_stat \choix[4].
}
\answer{}{\p;\des}{type=click}
