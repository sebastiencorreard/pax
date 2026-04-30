target=factorisat1 factorisat2

\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\keywords{literal_calculation,factorization}
\precision{100}
\keywords{literal_calculation,factorization}

#include "style.inc"
\text{list=wims(values v,-v for v=1 to 13)}
\text{list=shuffle(\list)}
\integer{a=item(1,\list)}
\integer{b=item(2,\list)}
\integer{c=item(3,\list)}
\integer{d=item(4,\list)}
\integer{f=randint(2..5)}
\integer{e=randint(2..5)}
\integer{aa=(\a)^2}
\integer{bb=(\b)^2}
\integer{a2=\e*\a}
\integer{b2=\e*\b}

\text{s1=random(-,+)}
\text{s2=random(-,+)}
\text{s3=random(-,+)}
\text{s4=random(-,+)}
\text{signe=\s1,\s2,\s3,\s4}
\integer{choix=random(1,2)}

\text{tt1=choix=1?(\a*x+\b)*(\c*x+\d):(\c*x+\d)*(\a*x+\b)}
\text{tt2=(\a*x+\b)^2}
\text{tt3=(\aa*x^2-\bb)}
\text{tt4=(\a2*x+\b2)}
\text{tt5=\f*x*(\a*x+\b)}
\text{termes=\tt1,\tt2,\tt3,\tt4,\tt5}
\text{stermes=shuffle(\termes)}
\integer{it1=position(\stermes[1],\termes)}
\integer{it2=position(\stermes[2],\termes)}
\text{itermes=\it1,\it2}
#if defined TARGET_factorisat2
\integer{it3=position(\stermes[3],\termes)}
\integer{it4=position(\stermes[4],\termes)}
\integer{it5=position(\stermes[5],\termes)}
\text{itermes=\itermes,\it3,\it4,\it5}
#endif
\text{alist=\c,\a,\a,0,\f}
\text{blist=\d,\b,-\b,\e,0}
\text{aaa1=item(\itermes[1],\alist)}
\text{aaa2=item(\itermes[2],\alist)}
#if defined TARGET_factorisat2
\text{aaa3=item(\itermes[3],\alist)}
\text{aaa4=item(\itermes[4],\alist)}
\text{aaa5=item(\itermes[5],\alist)}
#endif
\text{bbb1=item(\itermes[1],\blist)}
\text{bbb2=item(\itermes[2],\blist)}
#if defined TARGET_factorisat2
\text{bbb3=item(\itermes[3],\blist)}
\text{bbb4=item(\itermes[4],\blist)}
\text{bbb5=item(\itermes[5],\blist)}
#endif

\text{q=(\a*x+\b)*(\c*x+\d)\signe[1](\a*x+\b)^2\signe[2](\aa*x^2-\bb)\signe[3](\a2*x+\b2)\signe[4]\f*x*(\a*x+\b)}
\text{ch11=texmath(\a*x+\b)}
\text{ch12=texmath(\c*x+\d)}
\text{ch13=texmath(\aa*x^2-\bb)}
\text{ch14=texmath(\a2*x+\b2)}
\text{ch15=texmath(\a*x-\b)}
\text{ch16=texmath(\f*x)}
#if defined TARGET_factorisat1
\integer{aaa=\c\signe[1]\a\signe[2](\a)\signe[4]\f}
\integer{aaa=\aaa1\signe[1]\aaa2}
\integer{bbb=\d\signe[1]\b\signe[2](-\b)\signe[3]\e}
\integer{bbb=\bbb1\signe[1]\bbb2}
#endif
#if defined TARGET_factorisat2
\integer{aaa=(\aaa1)\signe[1](\aaa2)\signe[2](\aaa3)\signe[3](\aaa4)\signe[4](\aaa5)}
\integer{bbb=(\bbb1)\signe[1](\bbb2)\signe[2](\bbb3)\signe[3](\bbb4)\signe[4](\bbb5)}
#endif
\text{bad1=\ch11,\ch12,\ch13,\ch14,\ch15,\ch16}
\text{good1=\ch11}
\text{rep=texmath(\aaa*x+\bbb)}
\text{lgood=\ch12,\ch11,\ch15,\e,\ch16}
\text{sgood=\good1,\lgood[\itermes]}
#if defined TARGET_factorisat1
\text{mstep=r1
r2
r3
r4}
#endif
#if defined TARGET_factorisat2
\text{mstep=r1
r2
r3
r4
r5
r6
r7}
#endif
\nextstep{\mstep}
#if defined TARGET_factorisat1
\text{cnt=4}
#endif
#if defined TARGET_factorisat2
\text{cnt=7}
#endif
\text{alletape=rien}
\for{s=1 to \cnt-2}{
  \matrix{alletape=\alletape
  \name_tetape[1] <span class="blue">\(\stermes[\s]\)</span>, \name_tetape[2] <span class="red">\(\sgood[1]\)</span> \name_tetape[3]}
}
\text{expression=<span class="blue">\(\stermes[1]\)</span>}
\for{k=2 to \cnt-2}{
  \text{expression=\expression <span class="purple">\(\signe[\k-1]\phantom{ }\) </span>
  <span class="blue">\(\stermes[\k]\)</span> }
}
\statement{\tintro
<div class="wimscenter">\expression</div>
<h2>\name_tetape1[1]: \name_tetape1[2].</h2>
<div class="wimscenter">
\if{\step=1}{\embed{r1,6}.</div>}{
  <span class="red">\(\sgood[1]\)</span>.</div>
  \if{\step>=2}{
  <h2>\name_tetape2[1]: \name_tetape2[2]</h2>
    <ul><li>\alletape[2;]}
    \if{\step=2}{\embed{r2,6}.</li></ul>}{
    <span class="green">\(\sgood[2]\)</span>.</li>
    \if{\step=3}{<li>\alletape[3;] \embed{r3,6}.</li></ul>}{
      <li>\alletape[3;] <span class="green">\(\sgood[3]\)</span>.</li>
#if defined TARGET_factorisat2
      \if{\step=4}{
        <li>\alletape[4;] \embed{r4,6}.</li></ul>}{
        <li>\alletape[4;] <span class="green">\(\sgood[4]\)</span>.</li>
        \if{\step=5}{
          <li>\alletape[5;] \embed{r5,6}.</li></ul>}{
          <li>\alletape[5;] <span class="green">\(\sgood[5]\)</span>.</li>
        \if{\step=6}{
          <li>\alletape[6;] \embed{r6,6}.</li></ul>}{
          <li>\alletape[6;] <span class="green">\(\sgood[6]\)</span>.</li>
          </ul>}}}
#endif
}}}
  \if{\step>=\cnt}{
</ul><h2>\name_regroup.</h2>
  \name_reduction:
   <div class="wimscenter">
    \expression=
    (<span class="red">\(\sgood[1]\)</span>) (
    \for{j=2 to \cnt-2}{
     <span class="green">(\(\sgood[\j]\))</span>
      <span class="purple">\(\signe[\j-1]\phantom{ }\)</span>
    }
    <span class="green">(\(\sgood[\cnt-1]\))</span>).
    </div>
    \name_hence
  <div class="wimscenter">
    \expression=
    (<span class="red">\(\sgood[1]\)</span>)
  \if{\step=\cnt}{(\embed{r\step,6}).}{(\(\rep\)).}
  </div>
  }
}
\answer{\name_answer[1]}{1;\bad1}{type=menu}{option=shuffle nonstop}
#if defined TARGET_factorisat1
\answer{\name_answer[2] 1}{\sgood[2]}{type=algexp}{option=nonstop}
\answer{\name_answer[2] 2}{\sgood[3]}{type=algexp}{option=nonstop}
#endif
#if defined TARGET_factorisat2
\answer{\name_answer[2] 1}{\sgood[2]}{type=algexp}
\answer{\name_answer[2] 2}{\sgood[3]}{type=algexp}
\answer{\name_answer[2] 3}{\sgood[4]}{type=algexp}
\answer{\name_answer[2] 4}{\sgood[5]}{type=algexp}
\answer{\name_answer[2] 5}{\sgood[6]}{type=algexp}
#endif
\answer{\name_answer[3]}{\rep}{type=algexp}
\if{step=\cnt}\text{mstep=}

