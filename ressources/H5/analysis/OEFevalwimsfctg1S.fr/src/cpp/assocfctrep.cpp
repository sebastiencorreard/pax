target=assocfctrep1 assocfctrep2 assocfctrep3 assocfctrep4 assocfctrep5
#include "author.inc"
#include "lang.inc"
#include "lang_titles.inc"
\text{calcindic=<div class="wims_warning">\name_warning</div>}
#if (defined TARGET_assocfctrep1 || defined TARGET_assocfctrep2 || defined TARGET_assocfctrep4 )
\text{lstrep=}
#if defined TARGET_assocfctrep1
\text{al=shuffle(-4,-3,-2,-1,-0.5,-0.25,0.25,0.5,1,2,3,4)}
\real{a1=\al[1]}
\real{a2=\al[2]}
\for{ a in \al}{
 \text{f=\(y=texmath(\a*x^2))}
 \text{lstrep=wims(append item \f to \lstrep)}
}
\text{rep1=\(y=texmath(\a1*x^2))}
\text{rep2=\(y=texmath(\a2*x^2))}
\text{typef=texmath(k*x^2)}
\text{f1=\a1 * x^2}
\text{f2=\a2 * x^2}
# endif
#if defined TARGET_assocfctrep2
\text{al=shuffle(-4,-3,-2,-1,-0.5,0.5,1,2,3,4)}
\real{a1=\al[1]}
\real{a2=\al[2]}
\for{ a in \al}{
 \text{f=\(y=texmath(\a/x))}
 \text{lstrep=wims(append item \f to \lstrep)}
 }
\text{rep1=\(y=texmath(\a1/x))}
\text{rep2=\(y=texmath(\a2/x))}
\text{typef=texmath(k / x)}
\text{f1=\a1 / x}
\text{f2=\a2 / x}
#endif
#if defined TARGET_assocfctrep4
\text{calcindic=}
\text{al=shuffle(-4,-3,-2,-1,0,1,2,3,4)}
\integer{a1=\al[1]}
\integer{a2=\al[2]}
\integer{b1=\a1=0?randint(1..5)*randint(1,-1):randint(-5..5)}
\integer{b2=\a2=0?randint(1..5)*randint(1,-1):randint(-5..5)}
\text{typef=texmath((x-a)^2+b)}
\text{f1=(x-\a1)^2+\b1}
\text{f2=(x-\a2)^2+\b2}
#endif
\text{grep=\rep1,\rep2}
\text{size=100x50x1}
\text{lstrep=wims(listcomplement \grep in \lstrep)}
\text{dessin=
 xrange -10,10
 yrange -10,10
 parallel -10,-9,10,-9,0,1,19,gray
 parallel -9,-10,-9,10,1,0,19,gray
 arrow 0,-10,0,10,10,black
 arrow -10,0,10,0,10,black
 segment -0.2,1,0.2,1,black
 segment 1,-0.2,1,0.2,black
 text black,-0.7,1.5,small,1
 text black,0.7,-0.5,small,1
 }
\text{dessin1=\dessin
 plot red,\f1
}
\text{dessin2=\dessin
 plot red,\f2
 }
\statement{\calcindic
  \name_instruction \(y=\typef).
<table class="wimscenter wimsnoborder"><tr>
 <td>\draw{200,200}{\dessin1}</td><td>\draw{200,200}{\dessin2}</td></tr>
# if defined TARGET_assocfctrep4
  <tr><td><label for="reply1">\(y=\)</label>\embed{reply1,8}</td>
    <td><label for="reply2">\(y=\)</label>\embed{reply2,8}</td>
    </tr></table>
}
\answer{courbe 1}{\f1}{type=function}
\answer{Courbe 2}{\f2}{type=function}
# else
  <tr><td>\embed{reply1,\size}</td><td>\embed{reply2,\size}</td></tr></table>
}
\answer{courbe 1}{\rep1;\lstrep}{type=dragfill}
\answer{Courbe 2}{\rep2}{type=dragfill}
# endif
#endif
#if (defined TARGET_assocfctrep3 || defined TARGET_assocfctrep5 )
# if defined TARGET_assocfctrep3
\integer{a=randint(1..10)*randint(1,-1)}
\integer{b=randint(1..10)*randint(1,-1)}
\integer{ma=-\a}
\integer{mb=-\b}
\text{eq1=texmath(x^2+\a)}
\text{eq2=texmath((x-\b)^2)}
\text{lstrep1= C \lsttxt \(\a\vec{i}), C \lsttxt \(\a\vec{j}), C \lsttxt \(\ma\vec{i}), C \lsttxt \(\ma\vec{j})}
\text{lstrep2= \(\Gamma) \lsttxt \(\b\vec{i}), \(\Gamma) \lsttxt \(\b\vec{j}), \(\Gamma) \lsttxt \(\mb\vec{i}), \(\Gamma) \lsttxt \(\mb\vec{j})}
\statement{\calcindic
  \name_instruction \(y=\eq1) \name_and \(y=\eq2).
<p>
  \name_question[1]?
</p>
<ol><li>
 <ul>
  <li>\embed{reply1,1}</li>
  <li>\embed{reply1,2}</li>
  <li>\embed{reply1,3}</li>
  <li>\embed{reply1,4}</li></ul>
</li><li>
  <ul><li>\embed{reply2,1}</li>
  <li>\embed{reply2,2}</li>
  <li>\embed{reply2,3}</li>
  <li>\embed{reply2,4}</li>
  </ul>
</li></ol>
}
\answer{Courbe C}{2;\lstrep1}{type=radio}{option=shuffle}
\answer{Courbe \(Gamma)}{1;\lstrep2}{type=radio}{option=shuffle}
# endif
# if defined TARGET_assocfctrep5
\integer{a=randint(1..10)*randint(1,-1)}
\integer{b=randint(1..10)*randint(1,-1)}
\integer{ma=\a>0?-\a:\a}
\integer{mb=\b>0?-\b:\b}
\integer{pa=\a>0?\a:-\a}
\integer{pb=\b>0?\b:-\b}
\integer{rep1=\b>0?1:3}
\integer{rep1=\a<0?\rep1+1}
\integer{rep2=\rep1}

\text{eq1=texmath(1/(x-\a)+\b)}
\text{lstrep1= C \lsttxt \(\pa\vec{i}+\pb\vec{j}), C \lsttxt \(\ma\vec{i}+\pb\vec{j}), C \lsttxt \(\pa\vec{i}\mb\vec{j}), C \lsttxt \(\ma\vec{i}\mb\vec{j})}
\text{lstrep2= \lsttxt2 \(S(\pa;\pb)), \lsttxt2 \(S(\ma;\pb)), \lsttxt2 \(S(\pa;\mb)), \lsttxt2 \(S(\ma;\mb))}
\statement{\calcindic
  \name_instruction \(y=\eq1).
<ol><li>
  \name_question[1]?
<ul>
 <li>\embed{reply1,1}</li>
 <li>\embed{reply1,2}</li>
 <li>\embed{reply1,3}</li>
 <li>\embed{reply1,4}</li>
 </ul>
</li><li>
  \name_question[1] \(C)?
 <ul>
 <li>\embed{reply2,1}</li>
 <li>\embed{reply2,2}</li>
 <li>\embed{reply2,3}</li>
 <li>\embed{reply2,4}</li>
 </ul>
</li></ol>
}
\answer{Courbe C}{\rep1;\lstrep1}{type=radio}{option=shuffle}
\answer{Symétrie}{\rep2;\lstrep2}{type=radio}{option=shuffle}
# endif
#endif
