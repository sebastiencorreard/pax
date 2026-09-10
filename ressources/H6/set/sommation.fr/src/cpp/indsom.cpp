target=indsom
#include "lang_titles.inc"
#include "author.inc"
\computeanswer{no}
\description{Travail sur l'indice de sommation}
\text{R=2}
\integer{a=randint(1..3)*random(-1,1)}
\integer{b=randint(7..12)}
\integer{t=randint(1..4)*random(-1,1)}
\text{n=randitem(i,j,k,m,n,r)}
\integer{R=random(1,2)}
\integer{at=simplify(\a+\t)}
\integer{bt=simplify(\b+\t)}
\integer{rep1= \R=1? \at : \bt}
\text{rep2=simplify(\n-\t)}
\text{presentgood=}
\statement{
On désigne par \(f\) une fonction définie sur les entiers et on pose :
\(\displaystyle{ S = \sum_{\n = \a}^{\b} f ( \n )}\).
<div class="wims_question">Donner une autre expression de \(S\) en faisant une translation sur la variable :
\if{\R=1}{
<div class="wimscenter">
\special{mathmlinput [S=\displaystyle{\sum_{\n=reply1}^{\bt}f(reply2)}],4,noanswer
reply1,3
reply2}
</div>
}{
<div class="wimscenter">
\special{mathmlinput [S=\displaystyle{\sum_{\n=\at}^{reply1}f(reply2)}],4,noanswer
reply1,3
reply2}
</div>
}
</div>
\if{\presentgood=1 and (\sc_reply1 <1 or \sc_reply2 <1)}{<span class="oef_indbad">Expression incorrecte,</span>
 <p class="wimscenter">
\(\displaystyle{\sum_{\n = \a}^{\b}f(\n) = \sum_{\n = \at}^{\bt}f(\rep2)}.\)
</p>
}

}
\text{presentgood=slib(oef/env presentgood)}
\answer{}{\rep1}{type=formal}
\answer{}{\rep2}{type=formal}
