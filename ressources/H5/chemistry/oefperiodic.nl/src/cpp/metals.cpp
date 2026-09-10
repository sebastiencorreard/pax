target=metals4 metals6 metals8 metals10

#include "header.inc"
#include "confparm.inc"

#if defined TARGET_metals4
# define NUM 4
#endif
#if defined TARGET_metals6
# define NUM 6
#endif
#if defined TARGET_metals8
# define NUM 8
#endif
#if defined TARGET_metals10
# define NUM 10
#endif
#include "lang_titles.inc"
#include "lang.inc"
#include "position.inc"

\integer{tot=NUM}
\integer{beg=item(\tot,1,1,1,1,2,2,2,2,3,3,3,3,4,4)}
\integer{cut=random(\beg..\tot-\beg)}
\integer{length=\tot-\beg+1}
\text{given=\given notitemof 2,3?randitem(2,3)}
\integer{xsize=item(\given-1,50,100)}
\text{metals=column(1,wims(select \pdata where column 5 isitemof 2,3,7))}
\text{nonmetals=column(1,wims(select \pdata where column 5 notitemof 2,3,7))}
\text{metals=\data[\metals;\given]}
\text{nonmetals=\data[\nonmetals;\given]}
\text{metals=item(1..\cut,shuffle(\metals))}
\text{nonmetals=item(1..\tot-\cut,shuffle(\nonmetals))}
\text{size=\xsize[]x30x\length}

\statement{\name_instruction
<div>
\name_metal[1] : \embed{reply 1,\size}
</div><div>
\name_metal[2] : \embed{reply 2,\size}
</div>
}

\answer{\name_metal[1]}{\rmet;\metals}{type=dragfill}
\answer{name_metal[2]}{\rnon;\nonmetals}{type=dragfill}

\text{totans=\rmet,\rnon}
\text{noans=wims(listcomplement \totans in \metals,\nonmetals)}
\text{totans=\totans,\noans}
\text{clean=}
\text{check=}
\for{t=1 to \tot}{
  \text{ans=\totans[\t]}
  \if{\ans isitemof \rmet}{
   \text{clean=\clean \name_ismetal[1],}
   \text{check=\ans isitemof \metals?\check 1,:\check 0,}
  }{
  \if{\ans isitemof \rnon}{
   \text{clean=\clean \name_ismetal[2],}
   \text{check=\ans isitemof \nonmetals?\check 1,:\check 0,}
  }{
   \text{clean=\clean \name_ismetal[3],}
   \text{check=\check 0,}
  }
 }
}

\condition{\totans[1] \clean[1]}{\check[1]=1}
\condition{\totans[2] \clean[2]}{\check[2]=1}
\condition{\totans[3] \clean[3]}{\check[3]=1}
\condition{\totans[4] \clean[4]}{\check[4]=1}
#if NUM > 4
\condition{\totans[5] \clean[5]}{\check[5]=1}
\condition{\totans[6] \clean[6]}{\check[6]=1}
#endif
#if NUM > 6
\condition{\totans[7] \clean[7]}{\check[7]=1}
\condition{\totans[8] \clean[8]}{\check[8]=1}
#endif
#if NUM > 8
\condition{\totans[9] \clean[9]}{\check[9]=1}
\condition{\totans[10] \clean[10]}{\check[10]=1}
#endif
