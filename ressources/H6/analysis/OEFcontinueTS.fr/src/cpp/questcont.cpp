target=questcont1 questcont2 questcont3 questcont4
#include "author.inc"
\keywords{real_function,continuity}
#include "lang_titles.inc"
#include "lang.inc"

#if (defined TARGET_questcont1 || defined TARGET_questcont3 || defined TARGET_questcont4)
# if defined TARGET_questcont1
\integer{j=1}
# endif
# if defined TARGET_questcont3
\integer{j=2}
# endif
# if defined TARGET_questcont4
\integer{j=3}
# endif
\text{rappel=}
\if{\j=1}{
  \integer{a=randint(1..9)*randint(1,-1)}
  \integer{ap=randint(1..9)}
  \integer{b=randint(1..9)*randint(1,-1)}
  \integer{c=randint(1..9)}
  \integer{bg=randint(-10..10)}
  \integer{bgp=randint(1..10)}
  \integer{bgp2=\bgp+1}
  \integer{bgn=randint(-10..-2)}
  \integer{bgn2=\bgn+1}
  \integer{bd=\bg+randint(20..30)}
  \text{data=|\a*x+\b|,\(\lbrack \bg;\bd \rbrack),1
\a*x^2+\b*x+\c,\(\lbrack \bg;\bd \rbrack),1
\a*x^2+\b/(x^2+\c),\(\lbrack \bg;\bd \rbrack),1
sqrt(abs(\a*x+\b)),\(\lbrack \bg;\bd \rbrack),1
E(\a*x+\b),\(\displaystyle{\RR}\),2
E(\ap*x+\b),\(\lbrack \bgn;\bd \rbrack),2
E((\ap*x+\b)/1000),\(\lbrack \bgn;\bd \rbrack),2
E((\ap*x+\b)/1000),\(\lbrack \bgp;\bd \rbrack),1}
  \integer{i=randint(1..rows(\data))}
  \text{cedata=row(\i,\data)}
  \text{defdom=\cedata[2]}
  \text{defin=texmath(f(x)=\cedata[1])}
  \text{defin=\(\defin)}
  \integer{rep=\cedata[3]}
  \text{rappel=\i>4? \name_rappel}
}
\if{\j=2}{
  \text{defdom=\(\displaystyle{\RR})}
  \integer{a=randint(1..10)*randint(1,-1)}
  \integer{b=randint(1..10)*randint(1,-1)}
  \integer{c=randint(1..10)*randint(1,-1)}
  \integer{c=\c=\a? \c randitem(+,-) 1}
  \integer{x0=randint(1..10)*randint(1,-1)}
  \integer{x1=\x0-1}
  \integer{d=\a*\x0+\b-\c*\x0}
  \integer{d2=\d+randint(1..3)*randint(1,-1)}
  \integer{e=\a*\x0+\b-\c*(\x0)^2}
  \integer{e2=\e+randint(1..3)*randint(1,-1)}
  \integer{f=\a*\x0+\b-\c}
  \integer{f2=\f+randint(1..3)*randint(1,-1)}
  \text{data=\a*x,\(x \leq 0),-sin(\a*x),\(x > 0),1
\a*x-\b,\(x \leq 0),\b-sin(\a*x),\(x > 0),2
\a*x+\b,\(x \leq \x0),\c*x+\d,\(x > \x0),1
\a*x+\b,\(x \leq \x0),\c*x+\d2,\(x > \x0),2
\a*x+\b,\(x \leq \x0),\c*x^2+\e,\(x > \x0),1
\a*x+\b,\(x \leq \x0),\c*x^2+\e2,\(x > \x0),2
\a*x+\b,\(x \leq \x0),\c/(x-\x1)+\f,\(x > \x0),1
\a*x+\b,\(x \leq \x0),\c/(x-\x1)+\f2,\(x > \x0),2}
\integer{i=randint(1..rows(\data))}
\text{cedata=row(\i,\data)}
\text{def1=texmath(maxima(\cedata[1]))}
\text{def2=texmath(maxima(\cedata[3]))}
\text{defin=\(f(x)=\def1\) si \cedata[2] et \(f(x)=\def2\) si \cedata[4]}
\integer{rep=\cedata[5]}
}
\if{\j=3}{
  \integer{a=randint(1..10)*randint(1,-1)}
  \integer{b=randint(1..10)*randint(1,-1)}
  \integer{c=randint(1..10)*randint(1,-1)}
  \integer{x0=randint(1..3)*randint(1,-1)}
  \integer{d=-\x0*\c}
  \rational{x1=simplify(-\b/\a)}
  \rational{e=\a*\x0+\b=0?simplify(\a/\c):\a*\x0+\b}
  \integer{f=\a*\x0+\b}
  \integer{f2=\f+randint(1..3)*randint(1,-1)}
  \text{data=(\a*x+\b)/(\c*x+\d),\(x \not = \x0),\e,\(\displaystyle{\RR}\),2
  expand((\a*x+\b)*(\c*x+\d))/(\c*x+\d),\(x \not = \x0),\f,\(\displaystyle{\RR}\),1
  expand((\a*x+\b)*(\c*x+\d))/(\c*x+\d),\(x \not = \x0),\f2,\(\displaystyle{\RR}\),2
  (\c*x+\d)/(expand((\a*x+\b)*(\c*x+\d))),\(x \not = \x0),1/\f,\(\RR- \lbrace \x1 \rbrace\),1
  (\c*x+\d)/(expand((\a*x+\b)*(\c*x+\d))),\(x \not = \x0),1/\f2,\(\RR- \lbrace \x1 \rbrace\),2}
  \integer{i=randint(1..rows(\data))}
  \text{cedata=row(\i,\data)}
  \text{defdom=\cedata[4]}
  \text{def1=texmath(maxima(\cedata[1]))}
  \text{def2=texmath(maxima(\cedata[3]))}
  \text{defin=\(f(x)=\def1) si \cedata[2] et \(f(\x0)=\def2)}
  \integer{rep=\i!=4 or \f!=0? \cedata[5]:2}
}

\statement{
  \name_enonce[1] \defdom \name_enonce[2]:
  <div class="wimscenter">\defin.</div>
  \name_enonce[3]? \embed{reply1}.
  \if{\rappel!=}{<div class="wims_instruction">\rappel</div>}
}
\answer{}{\rep;\lstrep}{type=radio}
#endif
#if defined TARGET_questcont2
\integer{a=randint(1..9)*randint(1,-1)}
\integer{ap=randint(1..9)}
\integer{b=randint(1..9)*randint(1,-1)}
\integer{c=randint(1..9)}
\integer{bg=randint(-10..10)}
\integer{bgp=randint(1..10)}
\integer{bgp2=\bgp+1}
\integer{bgn=randint(-10..-2)}
\integer{bgn2=\bgn+1}
\integer{bd=\bg+randint(20..30)}
\text{data=E(x),\(\lbrack \bgp;\bgp2 \rbrack\),2
E(x),\(\rbrack \bgp;\bgp2 \rbrack\),2
E(x),\(\lbrack \bgp;\bgp2 \lbrack\),1
E(x),\(\lbrack \bgn;\bgn2 \rbrack\),2
E(x),\(\rbrack \bgn;\bgn2 \rbrack\),2
E(x),\(\lbrack \bgn;\bgn2 \lbrack\),1
E(x),\(\rbrack \frac{-1}{\ap}; \frac{1}{\ap} \lbrack\),2}
\integer{i=randint(1..rows(\data))}
\text{cedata=row(\i,\data)}
\text{defdom=\cedata[2]}
\text{defin=texmath(f(x)=\cedata[1])}
\text{defin=\(\defin\)}
\integer{rep=\cedata[3]}
\text{rappel=\name_rappel}
\statement{
<p>\name_enonce[1] \defdom \name_enonce[2]:</p>
<div class="wimscenter"> \defin.</div>
\name_enonce[3]? \embed{reply1}
<div class="wims_instruction">\rappel</div>
}
\answer{}{\rep;\lstrep}{type=radio}
#endif
