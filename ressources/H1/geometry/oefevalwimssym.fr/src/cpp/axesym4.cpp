target=oefaxesym4
#define NUM 4
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\keywords{symmetry}
#include "dessin4.inc"
\matrix{fig=<img src="\tria" alt="">,\name_list[1],0
<img src="\triarect" alt="">,\name_list[2],0
<img src="\triarectiso" alt="">,\name_list[3],1
<img src="\triaiso" alt="">,\name_list[4],1
<img src="\triaequi" alt="">,\name_list[5],3
<img src="\carre" alt="">,\name_list[6],4
<img src="\rect" alt="">,\name_list[7],2
<img src="\losange" alt="">,\name_list[8],2
<img src="\cerf" alt="">,\name_list[9],1
<img src="\quelc" alt="">,\name_list[10],0}

\integer{n=randint(1..10)}
\text{choix=row(\n,\fig)}
\text{des=\choix[1]}
\integer{rep=\choix[3]+1}
\statement{
<div class="wims_columns">
  <div class="medium_size">
    \des
  </div>
  <div class="medium_size">
  \name_stat[1] \choix[2] \name_stat[2] \embed{r1} \name_stat[3]
  </div>
</div>
}
\answer{}{\rep;0,1,2,3,4,5,6,7,8,9,\name_beaucoup}{type=menu}
