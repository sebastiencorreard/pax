target=majmin1 majmin2 majmin3 majmin4 majmin5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_majmin1
\integer{a=randint(1..5)*randint(1,-1)}
\integer{b=randint(1..5)*randint(1,-1)}
\integer{c=randint(1..5)*randint(1,-1)}
\integer{d=randint(1..5)*randint(1,-1)}
\integer{b=\a=\c?\d+randint(1..5)*randint(1,-1)}
\rational{r=-\d/\c}
\rational{si=\a/\c}
\text{sing=texmath(\si)}
\text{tr=texmath(\r)}
\integer{i=randint(1,2)}
\text{defdom=\i=1?\(\rbrack \tr; +\infty \lbrack):\(\rbrack -\infty; \tr \lbrack)}
\function{f=maxima((\a*x+\b)/(\c*x+\d))}
\text{ft=texmath(\f)}
\function{fcan=maxima(\f - \a/\c)}
\integer{signeden=(\c>0 and \i=1) or (\c<0 and \i=2)?1:-1}
\integer{sd=\signeden=1?1:2}
\rational{num=\b-\a*\d/\c}
\text{fden=texmath(maxima(\c*x+\d))}
\rational{s=\signeden*\num}
\integer{rep=\s>0?4:3}
\statement{
  On considère la fonction \(f) définie sur \defdom par:
<div class="wimscenter">\(f(x)=\ft) </div>
  On veut déterminer si \(\sing) est un extremum, un minorant ou un majorant de \(f).
<ol>
<li>Calculer
  \special{mathmlinput [f(x)- (\sing)=\frac{reply1}{\fden}],12
reply 1}
</li>
<li> Sur \defdom, quel est le signe du dénominateur ?
  \embed{reply2} </li>
<li> Que peut-on conclure alors&nbsp;? \(\sing) est \embed{reply3} de \(f).</li>
</ol>
}
\answer{calcul}{\num}{\type=numexp}
\answer{signe du dénominateur}{\sd;Positif,Négatif,Variable}{type=radio}
\answer{nature de \(\sing)}{\rep;\listerep}{type=menu}
#endif

#if defined TARGET_majmin2
\integer{a=randint(1..5)*randint(1,-1)}
\integer{b=randint(1..5)*randint(1,-1)}
\integer{c=randint(1..5)*randint(1,-1)}
\integer{d=randint(1..5)*randint(1,-1)}
\function{f=maxima(expand(\d*(x+\b)^2+\c))}
\function{g=\d*(x+\b)^2}
\integer{sd=\d>0?1:2}
\integer{rep=\d>0?2:1}
\text{ft=texmath(\f)}
\statement{
  On considère la fonction \(f) définie sur \(\RR) par:
<div class="wimscenter">\(f(x)=\ft). </div>
  On veut déterminer si \(\c) est un extremum, un minorant ou un majorant de \(f).
<ol>
<li> Calculer <label for="reply1">\(f(x)-(\c))=</label>\embed{reply1}</li>
<li> Sur \(\,\RR), quel est le signe de cette expression ? \embed{reply2} </li>
<li> Que peut-on conclure alors ?
\(\c) est \embed{reply3} de \(f).</li>
</ol>
}
\answer{calcul}{\g}{\type=numexp}
\answer{signe du dénominateur}{\sd;Positif,Négatif,Variable}{type=radio}
\answer{nature de \(\c)}{\rep;\listerep}{type=menu}
#endif

#if defined TARGET_majmin3
\integer{a=randint(1..5)*randint(1,-1)}
\integer{b=randint(1..5)*randint(1,-1)}
\integer{c=randint(1..5)}
\integer{d=randint(0,randint(1..5)*randint(1,-1))}
\function{f=maxima((\a*x^2+\d*x+\b)/(x^2+\c))}
\function{fden=maxima(x^2+\c)}
\function{g=maxima(\d*x+\b-\a*\c)}
\integer{n=\b-\a*\c}
\if{\d=0}
 {
 \integer{rep=\n>0?4:3}
 \integer{sd=\n>0?1:2}
 }
 {
 \integer{rep=5}
 \integer{sd=3}
 }
\text{ft=texmath(\f)}
\statement{
  On considère la fonction \(f) définie sur \(\,\RR) par:
<div class="wimscenter">\(f(x)=\ft) </div>
  On veut déterminer si \(\a) est un extremum, un minorant ou un majorant de \(f).
<ol>
<li> Calculer
\special{mathmlinput [f(x)- (\a) = \frac{reply1}{\fden} ], 12
reply1
}
</li>
<li> Sur \(\,\RR), quel est le signe de cette expression ? \embed{reply2} </li>
<li> Que peut-on conclure alors ?<br>
\(\a) est \embed{reply3} de \(f).</li>
</ol>
}
\answer{calcul}{\g}{\type=numexp}
\answer{signe du dénominateur}{\sd;Positif,Négatif,Variable}{type=radio}
\answer{nature de \(\c)}{\rep;\listerep}{type=menu}
#endif

#if defined TARGET_majmin4
\integer{a=randint(1..5)*randint(1,-1)}
\integer{b=randint(1..5)*randint(1,-1)}
\integer{c=randint(1..5)*randint(1,-1)}
\integer{d=randint(1..5)*randint(1,-1)}
\function{f=maxima(\d*(\a*x+\b)^2+\c)}
\text{extr=\d>0?minimum:maximum}
\rational{x0=-\b/\a}
\text{ft=texmath(\f)}
\statement{
  On considère la fonction \(f) définie sur \(\ \RR) par:
<div class="wimscenter">\(f(x)=\ft) </div>
  Cette fonction possède un \extr noté \(m) atteint en \(x_0).<p>
  Déterminer les valeurs de \(m) et de \(x_0).</p>
<div class="wimscenter"> \(m)=\embed{reply1,4}</div>
<div class="wimscenter"> \(x_0)=\embed{reply2,4}</div>
}
\answer{m}{\c}{type=numeric}
\answer{\(x_0)}{\x0}{type=numexp}
#endif

#if defined TARGET_majmin5
\integer{a=randint(1..5)*randint(1,-1)}
\integer{b=randint(1..5)*randint(1,-1)}
\integer{c=randint(1..5)}
\integer{d=randint(1..5)}
\function{f=maxima((\a*x^2+\b)/(\c*x^2+\d))}
\function{fden=maxima(\c*x^2+\d)}
\text{ft=texmath(\f)}
\rational{n=\b-\a*\d/\c}
\rational{m=\a/\c}
 \text{verbe=\n>0?minorée:majorée}
 \text{extr=\n>0?plus grand minorant:plus petit majorant}
\statement{
  On considère la fonction \(f) définie sur \(\RR) par:
<div class="wimscenter">\(f(x)=\ft).</div>
  Cette fonction est \verbe.<p>
  Déterminer son \extr noté \(m).
  </p>
<div class="wimscenter"> <label for="reply1">\(m)=</label>\embed{reply1,4}</div>
}
\answer{m}{\m}{type=numexp}
#endif
