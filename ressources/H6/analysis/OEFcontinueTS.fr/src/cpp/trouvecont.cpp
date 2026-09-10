target=trouvecont1 trouvecont2 trouvecont3 trouvecont4
#include "author.inc"
\keywords{real_function,continuity}
#include "lang_titles.inc"
#include "lang.inc"
#if (defined TARGET_trouvecont1 || defined TARGET_trouvecont2)
\text{defdom=\(\displaystyle{\RR}\)}
\integer{a=randint(1..10)*randint(1,-1)}
\integer{b=randint(1..10)*randint(1,-1)}
\integer{c=randint(1..10)*randint(1,-1)}
\integer{c=\c=\a ? \c randitem(+,-) 1}
\integer{x0=randint(1..10)*randint(1,-1)}
\integer{x1=\x0-1}
\integer{d=\a*\x0+\b-\c*\x0}
\integer{e=\a*\x0+\b-\c*(\x0)^2}
\integer{f=\a*\x0+\b-\c}
\rational{x00=-\x0+\a/\c}
\rational{x01=-(\c-\a*\x1)/\a}
# if defined TARGET_trouvecont1
\text{data=\a*x,\(x \leq x_0),-sin(\a*x),\(x > x_0),0
\a*x+\b,\(x \leq x_0),\c*x+\d,\(x > x_0),\x0
\a*x+\b,\(x \leq x_0),\c*x^2+\e,\(x > x_0),\x0,\x00
\a*x+\b,\(x \leq x_0),\c/(x-(\x1))+\f,\(x > x_0),\x0,\x01
}

\integer{i=randint(1..rows(\data))}
\text{cedata=row(\i,\data)}
\text{def1=texmath(maxima(\cedata[1]))}
\text{def2=texmath(maxima(\cedata[3]))}

\text{defin=\(f(x)=\def1\) \name_ifand[1] \cedata[2] \name_ifand[2]
  \(f(x)=\def2\) \name_ifand[1] \cedata[4]}
text{test=\cedata[1]-(\cedata[3])}
text{test=pari(factor(\test))}
\rational{x0=\cedata[5]}
\rational{x1=\cedata[6]}
\statement{
\name_enonce[1] \(x_0\) \name_enonce[2]
<div class="wimscenter">\defin</div>
\name_enonce[3] \defdom.
<div class="wimscenter">
<label for="reply1">\name_value \(x_0\)&nbsp;:</label> \embed{reply1,7}</div>
}
answer{\(x_0\)}{\x0}{type=numexp}
\answer{}{\x0,\x1}{type=fset}
# endif
# if defined TARGET_trouvecont2
\text{data=\a*x+k,\(x \leq 0),-sin(\a*x),\(x > 0),0
\a*x+\b,\(x \leq \x0),\c*x+k,\(x > \x0),\d
\a*x+k,\(x \leq \x0),\c*x^2+\e,\(x > \x0),\b
\a*x+\b,\(x \leq \x0),\c/(x-\x1)+k,\(x > \x0),\f
}
\integer{i=randint(1..rows(\data))}
\text{cedata=row(\i,\data)}
\text{def1=texmath(maxima(\cedata[1]))}
\text{def2=texmath(maxima(\cedata[3]))}
\text{defin=\(f(x)=\def1\) \name_ifand[1] \cedata[2] \name_ifand[2] \(f(x)=\def2\) \name_ifand[1] \cedata[4]}
\integer{k=\cedata[5]}

\statement{
\name_enonce[1] \(k\) \name_enonce[2]
<div class="wimscenter">\defin</div>
\name_enonce[3] \defdom.
<div class="wimscenter">
<label for="reply1">\name_value \(k\) :</label> \embed{reply1,7}.
</div>
}
\answer{\(k\)}{\k}{type=numexp}
# endif
#endif
#if defined TARGET_trouvecont3
\integer{a=randint(1..10)*randint(1,-1)}
\integer{b=randint(1..10)*randint(1,-1)}
\integer{c=randint(1..10)*randint(1,-1)}
\integer{x0=randint(1..3)*randint(1,-1)}
\integer{d=-\x0*\c}
\rational{x1=simplify(-\b/\a)}
\rational{e=\a*\x0+\b=0?simplify(\a/\c):\a*\x0+\b}
\integer{f=\a*\x0+\b}
\integer{f2=\f+randint(1..3)*randint(1,-1)}

\text{data=k/(\c*x+\d),\(x \not = \x0\),\e,\(\displaystyle{\RR}\),2,\b
expand((\a*x+\b)*(\c*x+\d))/(\c*x+\d),\(x \not = \x0\),k,\(\displaystyle{\RR}\),1,\f
(\c*x+\d)/(expand((\a*x+\b)*(\c*x+\d))),\(x \not = \x0\),k,\(\RR- \lbrace \x1 \rbrace\),1,1/\f}
\integer{i=randint(1..rows(\data))}
\text{cedata=row(\i,\data)}
\text{defdom=\cedata[4]}
\text{def1=texmath(maxima(\cedata[1]))}
\text{def2=texmath(maxima(\cedata[3]))}
\text{defin=\(f(x)=\def1) \name_ifand[1] \cedata[2] \name_ifand[2] \(f(\x0)=\def2)}
\integer{rep=\i!=3 or \f!= 0? \cedata[5]:2}
\rational{k=\cedata[6]}

\text{mstep=\rep=2?r1:r1
r2}
\steps{\mstep}
\statement{
  \name_enonce[1] \defdom \name_enonce[2]
  <div class="wimscenter"> \defin </div>
  \name_enonce[3]?
  \if{\step=1}{
    <div class="wimscenter">\embed{reply1}</div>
  }
  {<span class="oef_indgood">\lstrep[\rep]</span><p>\rappel</p>
    <div><label for="reply2">\name_answer:</label> \embed{reply2,7}.</div>
    <div class="wims_instruction">\instruct</div>
  }
}
\answer{}{\rep;\lstrep}{type=radio}
\answer{k}{\k}{type=numexp}
#endif
#if defined TARGET_trouvecont4
\rational{a=simplify(randint(1..9)*randint(1,-1)/randint(2,3,5))}
\rational{b=simplify(randint(1..9)*randint(1,-1)/randint(2,3,5))}
\integer{x0=randint(-5..5)}
\integer{c=floor(\a*\x0+\b)}
\rational{b1=simplify((\c-\b)/(\a))}
\rational{b2=simplify((\c+1-\b)/(\a))}
\rational{bg=\b1<\b2?\b1:\b2}
\rational{bd=\b1<\b2?\b2:\b1}

\text{ft=texmath(\a*x+\b)}
\text{ft=\(f(x)=E(\ft))}

\text{crocg=&#91;}
\text{crocd=&#93;}
\text{lstcroc=\crocg,\crocd}
\text{size=50x20x1}

\text{crg=\b1<\b2?\crocg:\crocd}
\text{crd=\b1<\b2?\crocg:\crocd}
\statement{
  <div class="wims_instruction">\name_rappel</div>
  <p>\name_enonce[1]</p>
  <div class="wimscenter"> \ft. </div>
  <p>\name_enonce[2] \(\x0\) \name_enonce[3]</p>
  <div class="wimscenter"> \embed{reply1,\size} \embed{reply2,5} ;
    \embed{reply3,5} \embed{reply4,\size} </div>
  <div class="wims_instruction">\instruct</div>
}
\answer{}{\crg;\lstcroc}{type=clickfill}
\answer{\name_answer[1]}{\bg}{type=numexp}
\answer{\name_answer[2]}{\bd}{type=numexp}
\answer{}{\crd;\lstcroc}{type=clickfill}
#endif
