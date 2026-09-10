target=oefaxesym5
#define NUM 5
#include "lang_titles.inc"
#include "lang.inc"
#include "author.inc"
\keywords{symmetry}
\matrix{fig=\name_list[1],0
\name_list[2],0
\name_list[3],1
\name_list[4],1
\name_list[5],3
\name_list[6],4
\name_list[7],2
\name_list[8],2
\name_list[9],1
\name_list[10],0}

\integer{n=randint(1..10)}
\text{choix=row(\n,\fig)}
\integer{rep=\choix[2]+1}

\statement{
\name_stat[1] \choix[1] \name_stat[2] \embed{r1} \name_stat[3]
}
\answer{}{\rep;0,1,2,3,4,5,6,7,8,9,\name_beaucoup}{type=menu}
