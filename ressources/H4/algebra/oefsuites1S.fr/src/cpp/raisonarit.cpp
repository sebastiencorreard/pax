target=raisonarit
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\integer{nat=randint(1..3)}
\integer{dif=randint(1..2)}
 nat = 1 formule explicite, 2 avec deux termes

\integer{a=random(2..10)*random(-1,1)}
\integer{b=random(-1,1)*random(2..10)}
\integer{c=random(2..11)}
\integer{d=random(-1,1)*random(2..100)}
\real{d=\d/10}
\integer{e=random(2..3)}
\integer{f=random(-1,1)*random(3,5,9,15)}
\integer{g=random(-1,1)*random(2,7,4,8,14)}
\if{\nat == 1}{
  \if{\dif == 1}{
   \text{s=texmath(\b* n + (\a))}
   \text{t=(\b) * n + (\a)}
   \rational{rep1=\a}
   \rational{rep2=\b}
   }{
   \text{s=texmath(\c * ((\b)*n + (\a)))}
   \text{t=(\c) * ((\b) * n + (\a))}
   \rational{rep1=(\c)*(\a)}
   \text{rep2=(\b)*(\c)}
  }
}
\if{\nat == 2}{
   \integer{ind1=random(1..40)}
   \integer{ind2=random(41..100)}
   \text{ut1=u_{\ind1}}
   \text{ut2=u_{\ind2}}
  \if{\dif == 1}{
   \text{t=(\b) * n + (\a)}
   \rational{rep1=\a}
   \rational{rep2=\b}
   }{
   \text{t=(\b)/(\c) * n + (\a)/(\e)}
   \rational{rep1=(\a)/(\e)}
   \rational{rep2=(\b)/(\c)}
   }
   \rational{v1=evalue(\t,n=\ind1)}
   \rational{v2=evalue(\t,n=\ind2)}
   \text{tv1=\v1}
   \text{tv1=wims(replace internal / by , in \tv1)}
   \text{tv1=items(\tv1)=1?\tv1:\frac{\tv1[1]}{\tv1[2]}}
   \text{tv2=\v2}
   \text{tv2=wims(replace internal / by , in \tv2)}
   \text{tv2=items(\tv2)=1?\tv2:\frac{\tv2[1]}{\tv2[2]}}
}
\if{\nat==3}{
  \if{\dif == 1}{
   \text{s=texmath(\b* (n + \e) + (\a))}
   \rational{rep1=\a+(\b)*\e}
   \rational{rep2=\b}
   }{
   \text{s=texmath(\b*(\e*n + (\c)) + (\a))}
   \rational{rep1=(\b)*(\c)+(\a)}
   \text{rep2=(\b)*(\e)}
  }
}
\text{size=\confparm1=1 ? :x-large}
\statement{
\if{\nat != 2}{
\name_enonce[1]
<div class="wimscenter">\( u_n = \s \).</div>
}{
\name_enonce[2]
<div class="wimscenter">\(\ut1 = \tv1\), \(\ut2 = \tv2\).</div>
}
<p>\name_question</p>
<ul><li>
<label for="reply1">\name_answer[1]:</label> \embed{r1,5}
</li><li>
<label for="reply2">\name_answer[2]:</label> \embed{r2,5}
</li></ul>
}

\reply{u_0}{\rep1}{type=algexp}
\reply{raison}{\rep2}{type=algexp}
