target=convduree1 convduree2 convduree3 convduree4 convduree5
\keywords{conversion}
#include "author.inc"
#if defined TARGET_convduree1
# define NUM 1
#endif
#if defined TARGET_convduree2
# define NUM 2
#endif
#if defined TARGET_convduree3
# define NUM 3
#endif
#if defined TARGET_convduree4
# define NUM 4
#endif
#if defined TARGET_convduree5
# define NUM 5
#endif
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_convduree1
 \matrix{ltype=HMS,S}
# define TYP 1
#endif
#if defined TARGET_convduree2
 \matrix{ltype=HM,H}
# define TYP 1
#endif
#if defined TARGET_convduree3
 \matrix{ltype=HMS,M}
# define TYP 1
#endif
#if defined TARGET_convduree4
 \matrix{ltype=HMS,S}
# define TYP 2
#endif
#if defined TARGET_convduree5
 \matrix{ltype=HMS,H}
# define TYP 2
#endif


\integer{typ=TYP}
\text{textenonce=\name_enonce[\typ]}
\integer{confparm1=1}

\text{don=randrow(\ltype)}
\text{questo=item(1,\don)}
\text{repo=item(2,\don)}
\text{don2=slib(convheure \questo,\repo)}
\if{\typ=1}{
\text{quest=row(1,\don2)}
\text{rep=row(2,\don2)}
}{
\text{quest=row(2,\don2)}
\text{rep=row(1,\don2)}
\text{questo=item(2,\don)}
\text{repo=item(1,\don)}
}
\text{lname=h,min,s}
\text{lsymb=H,M,S}
\integer{nb=items(\quest)}
\text{enonce=}
\for{i=1 to \nb}{
 \text{l=wims(char \i of \questo)}
 \integer{po=position(\l,\lsymb)}
 \text{en=item(\po,\lname)}
 \text{enonce=\enonce \quest[\i] \en}
}

\integer{nb=items(\rep)}
\text{tt=}
\for{i=1 to \nb}{
 \text{l=wims(char \i of \repo)}
 \integer{po=position(\l,\lsymb)}
 \text{en=item(\po,\lname)}
 \text{tt=wims(append item \en to \tt)}
}
\steps{wims(item 1 to \nb of r1,r2,r3)}

\statement{
\textenonce.
<div class="wimscenter"><label for="reply1">\enonce =</label>
\for{j=1 to \nb}{\embed{r\j,10} \tt[\j]} </div>}

\answer{\tt[1]}{\rep[1]}{type=numexp}
\answer{\tt[2]}{\rep[2]}{type=numexp}
\answer{\tt[3]}{\rep[3]}{type=numexp}
