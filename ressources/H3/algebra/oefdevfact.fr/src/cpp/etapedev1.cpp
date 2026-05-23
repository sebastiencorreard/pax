target=etapedev1
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{10000}

\integer{confparm1=\confparm1=?1}
\integer{confparm1=\confparm1<1 or \confparm1>6?1}
\text{x=randitem(x,y,z,t,u,v,a,b)}
\text{c=wims(values v,-v for v=1 to 9)}
\text{c=shuffle(\c)}
\text{lt=wims(values v for v=0 to \confparm1)}
\text{lt=shuffle(\lt)}
\text{p1=item(1,\lt)}
\text{p2=item(2,\lt)}
\text{p3=\p1}
\text{p4=\p2}
\text{calcul=(simplify(\c[1]*\x^\p1)+simplify(\c[2]*\x^\p2))*(simplify(\c[3]*\x^\p3)+simplify(\c[4]*\x^\p4))}
\text{enonce=texmath(\calcul)}
\text{rep3=maxima(expand(\calcul);)}
\text{tmp=texmath(simplify(\c[3]*\x^\p1))}
\text{tmp=\c[3]<0?(\tmp)}
\text{tmp1=texmath(simplify(\c[1]*\x^\p1))}
\text{enonce1=\tmp1\times \tmp}
\text{sol1=simplify(\c[1]*\c[3]*\x^(\p1+\p3))}
\text{tmp1=texmath(simplify(\c[4]*\x^\p4))}
\text{tmp1=\c[4]<0?(\tmp1)}
\text{tmp2=texmath(simplify(\c[3]*\x^\p3))}
\text{tmp2=\c[3]>=0?+\tmp2}
\text{tmp=texmath(simplify(\c[2]*\x^\p2))}
\text{tmp=\c[2]<0?(\tmp)}
\text{enonce2=texmath(simplify(\c[1]*\x^\p1))\times \tmp1 \tmp2\times \tmp}
\text{sol2=maxima(expand(\c[1]*\c[4]*\x^(\p1+\p4)+\c[2]*\c[3]*\x^(\p2+\p3));)}

\steps{r1,r2
r3}
\statement{
  <ol>
  \if{\step=1}{
    <li>\name_enonce:
     <ul>
      <li><label for="reply1">\(A = \enonce1 =)</label> \embed{r1}</li>
      <li><label for="reply2">\(B = \enonce2 =)</label> \embed{r2}</li>
     </ul>
    </li>
  }
  \if{\step=2}{
    <li>\name_enonce:
      <ul>
       <li>\(A = \enonce1 =) <span class="oef_indgood">\(\sol1) &nbsp; \goodanswer</span></li>
       <li>\(B = \enonce2 =) <span class="oef_indgood">\(\sol2) &nbsp; \goodanswer</span></li>
      </ul>
     </li>
     <li>\name_enonce2:
      <blockquote>
       <label for="reply3">\(C = \enonce = \)</label> \embed{r3}.
      </blockquote>
     </li>
  }
  </ol>
}

\answer{A}{\sol1}{type=litexp}{option=polexpand}
\answer{B}{\sol2}{type=litexp}{option=polexpand}
\answer{C}{\rep3}{type=algexp}{option=polexpand}
