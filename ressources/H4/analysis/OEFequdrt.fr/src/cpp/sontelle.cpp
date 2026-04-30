target=sontelles1 sontelles2 sontelles3 sontelles4 sontelles5 sontelles6

#include "author.inc"
#include "lang_titles.inc"

\text{d=randitem(D,d,m,p,q)}
\text{l=wims(values v for v=-10 to 10)}
\text{l=shuffle(\l)}
\integer{ch=randint(1..2)}
#include "lang.inc"
#if defined TARGET_sontelles1
 \integer{a2=\ch=1?\l[1]:\l[2]}
 text{equation= y = maxima(expand(\l[1]*x +\l[3]);),y = maxima(expand(\a2*x + \l[4]);)}
 \text{equation= y = pari(\l[1]*x +\l[3]),y = pari(\a2*x + \l[4])}
#endif
#if defined TARGET_sontelles2
 \integer{s=randitem(-1,-2,1,2)}
 \integer{b1=\ch=1?\l[1]*(\s):\l[4]}
 \integer{b2=\ch=1?\l[2]*(\s):\l[5]}
 \integer{ch=\l[1]*(\l[5])-(\l[2])*(\l[4])=0?1}
 \if{\l[1]!=0 and \l[2]!=0}{
  \text{t1=randitem(texmath(\l[1]*x + \l[2]*y),texmath(\l[2]*y + \l[1]*x))}
 }{
  \text{t1=\l[1]=0?simplify(\l[2]*y):simplify(\l[1]*x)}
 }
 \if{\b1!=0 and \b2!=0}{
  \text{t2=randitem(texmath(\b1*x + \b2*y),texmath(\b2*y+\b1*x))}
 }{
  \text{t2=\b1=0?simplify(\b2*y):simplify(\b1*x)}
 }
 \text{equation= shuffle(\t1= \l[3] , \t2 = \l[6] )}
#endif
#if defined TARGET_sontelles3
 \integer{a2=\ch=1?\l[1]:\l[2]}
 text{equation=y = maxima(expand(\l[1]*x +\l[3]);),y = maxima(expand(\a2*x + \l[4]);)}
 \text{equation=y = pari(\l[1]*x +\l[3]),y = pari(\a2*x + \l[4])}
 \integer{ch=\ch=1?2:1}
#endif
#if defined TARGET_sontelles4
 \integer{s=randitem(-1,-2,1,2)}
 \integer{b1=\ch=1?\l[1]*(\s):\l[4]}
 \integer{b2=\ch=1?\l[2]*(\s):\l[5]}
 \integer{ch=\l[1]*(\l[5])-(\l[2])*(\l[4])=0?1}
 \if{\l[1]!=0 and \l[2]!=0}{
  \text{t1=randitem(texmath(\l[1]*x + \l[2]*y),texmath(\l[2]*y + \l[1]*x))}
 }{
  \text{t1=\l[1]=0?simplify(\l[2]*y):simplify(\l[1]*x)}
 }
 \if{\b1!=0 and \b2!=0}{
  \text{t2=randitem(texmath(\b1*x + \b2*y),texmath(\b2*y+\b1*x))}
 }{
  \text{t2=\b1=0?simplify(\b2*y):simplify(\b1*x)}
 }
 \text{equation= shuffle(\t1= \l[3] , \t2 = \l[6] )}
 \integer{ch=\ch=1?2:1}
#endif
#if defined TARGET_sontelles5
 \text{l=wims(listcomplement 0 in \l)}
 \text{a1=simplify(\l[1]/\l[2])}
 \text{a2=\ch=1?simplify(-1/(\a1)):simplify(\l[3]/\l[4])}
 \integer{ch=\a1*\a2=-1?1}
 \text{b1=simplify(\l[5]/\l[6])}
 \text{b2=simplify(\l[7]/\l[8])}
 \text{equation=texmath(y = \a1 * x + \b2)\;,texmath(y = \a2 * x + \b1)\;}
#endif
#if defined TARGET_sontelles6
 \text{l=wims(listcomplement 0 in \l)}
 \integer{s=randitem(-1,-2,1,2)}
 \integer{b1=\ch=1?-1*(\l[2])*(\s):\l[4]}
 \integer{b2=\ch=1?\l[1]*(\s):\l[5]}
 \integer{ch=\l[1]*(\l[5])-(\l[2])*(\l[4])=0?1}
 \text{t1=randitem(texmath(\l[1]*x + \l[2]*y),texmath(\l[2]*y + \l[1]*x ))}
 \text{t2=randitem(texmath(\b1*x + \b2*y),texmath(\b2*y+\b1*x))}
 \text{equation= shuffle(\t1= \l[3] , \t2 = \l[6] )}
#endif
\text{rep=item(\ch,\name_yesno)}
\statement{\name_enonce[1] \((\d _1)\) \name_enonce[2] \((\d _2)\) \name_enonce[3]:
<ul>
 <li>\((\d _1)\) : \(\equation[1]\) </li>
 <li>\((\d _2)\) : \(\equation[2]\) </li>
</ul>
  \name_question[1] \((\d _1)\) \name_question[2] \((\d _2)\) \name_question[3] \propriete ?}

\choice{}{\rep}{\name_yesno}
