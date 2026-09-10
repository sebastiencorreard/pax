target=majbase

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}

\text{ba=randint(4..10)}
\integer{t=0}
\while{\t=0}{
\text{a=randint(200..500)}
\text{b=randint(200..500)}
\integer{c=\a*\b}
\text{h=wims(exec float_calc ibase=10; obase=\ba ;
\a;\b;\a*\b)}
\matrix{h=\h}
\text{A=\h[1;]}
\text{B=\h[2;]}
\text{C=\h[3;]}
\integer{na=wims(charcnt \A)-1}
\integer{nb=wims(charcnt \B)-1}
\integer{nc=wims(charcnt \C)-1}
\text{a1=wims(char 1 of \A)}
\text{b1=wims(char 1 of \B)}
\text{c1=wims(char 1 of \C)}
\text{a2=wims(char 2 of \A)}
\text{b2=wims(char 2 of \B)}
\text{c2=wims(char 2 of \C)}
\text{lim=wims(sort numeric item \a1,\b1,\c1,\a2,\b2,\c2)}
\integer{lim=\lim[-1]+1}

\integer{\t= \a1*\b1!=\c1 ? 1}
}
\text{max=pari(vecmax([\a1,\a2,\b1,\b2,\c1,\c2])+1)}

\text{AA1=\a1,\a2,wims(makelist \bullet for x=1 to \na-1)}
\text{BB1=\b1,\b2,wims(makelist \bullet for x=1 to \nb-1)}
\text{CC1=\c1,\c2,wims(makelist \bullet for x=1 to \nc-1)}
\text{AA1=wims(items2words \AA1)}
\text{AA1=wims(nospace \AA1)}
\text{BB1=wims(items2words \BB1)}
\text{BB1=wims(nospace \BB1)}
\text{CC1=wims(items2words \CC1)}
\text{CC1=wims(nospace \CC1)}
\integer{v=\nc-\na-\nb+1}
\function{m1=(\a1 * x + \a2)*(\b1 * x + \b2)}
\function{M1=(\a1 * x + \a2+1)*(\b1 * x + \b2+1)}
\function{m2=(\c1 * x + \c2)}
\function{M2=\c1 * x + \c2 +1}

\function{eq1 = simplify(((\m1) - (\M2)*x^\v))} négative
\function{eq2 = simplify((\M1) - (\m2)*x^\v)} positive

\text{S=}
\if{\v=2}{
  \integer{BM=max(\max,floor((\a1+1)*(\b1+1)/\c1))}
  \integer{Bm=ceil(\a1*\b1/(\c1+1))}
  \for{u=\Bm to \BM}{
    \real{test1=evalue(\eq1,x=\u)}
    \real{test2=evalue(\eq2,x=\u)}
    \if{\test1 <0 and \test2 >0 and \u >}{
      \text{S=wims(append item \u to \S)}
    }
  }
}

\if{\v=1}{
  \text{U=pari(g=real(polroots(\eq1*1.)) ; g[#g])}
  \text{V=pari(g=real(polroots(\eq2*1.)) ; g[#g])}
  \text{UV=wims(sort numeric items \U,\V)}
  \integer{BM=ceil(\UV[2])}
  \integer{Bm=floor(\UV[1])}
  \for{u=\Bm to \BM}{
    \real{test1=evalue(\eq1,x=\u)}
    \real{test2=evalue(\eq2,x=\u)}
    \if{\test1 <0 and \test2 >0 and \u >= \lim}{
      \text{S=wims(append item \u to \S)}
     }
  }
}

#include "lang.inc"

\statement{\name_statement1
<div class="wimscenter">
\(\CC1 = \AA1  \times \BB1 \)
</div>
\name_statement2
<div class="wimscenter">
   \embed{r1, 10}
</div>
}

\answer{xx}{\S}{type=set}

\hint{\name_hint}

feedback{1=1}{S=\S}
