target=lceb1b

#define NUM Ib
#include "lang_titles.inc"

#include "author.inc"
#include "style.inc"

\if{\confparm1=1}{
 \text{nt=4}
  \integer{M1=randint(21..24)}
  \integer{M2=randint(38..43)}
 \text{tablettes=shuffle(3,3,4,5,6,2,2,6,4,6,1)}
 \text{tablettes=\tablettes[1..4],0,0}
 \text{nt=4}
 }
 {
\text{nt=6}
\integer{M1=randint(101..240)}
\integer{M2=randint(800..999)}
\text{tablettes=shuffle(1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,25,50,75,100)}
}

#include "lang.inc"

\text{data=\tablettes[1..6]}
\text{dataw=wims(items2words \data)}
\text{data=wims(nospace \data)}
\text{data=wims(replace internal ,0 by in \data)}
\text{data=wims(nonempty items \data)}
\text{Data=\data}
\text{N=}
\integer{R=}
\text{lceb=}
\text{lceb1=}
\text{goal=}
\text{test0=}

\text{rep=}
\text{test1=}
\text{test3=}
\text{nn=\nt}
\text{nstep=r1}
\nextstep{\nstep}
\text{d=}
\text{d1=}
\text{t=}
\text{test0=}
\text{Feed=}

\statement{
\if{\step=1}{<p>\instruction0[1;] \embed{r1}</p>}

\if{\step>=2}{<p>
\if{\test0=0}{\instruction0[2;] } \instruction1 <span class="tt">\Data[1] + \Data[2] = \R</span>.
\instruction2</p>
<table class="wimscenter lceb">
<tr>\for{u=1 to \nt}{<th>\Data[\u]</th>}</tr>
</table>

<table class="wimscenter lceb">
<tr>\for{u=1 to \nn}{<th>\data[\u]</th>}
</tr>
<tr><td class="goal" colspan="\nt">\N</td></tr>
<tr><td class="answer" colspan="\nt">
\if{\nstep=}{\d1[3]}{\embed{r \step,150
default}
}
</td></tr>
</table>
}
}

\answer{}{\rep1}{type=numeric}{option=nonstop}
\answer{}{\Rep1}{type=raw}{option=nonstop}
\answer{}{\Rep2}{type=raw}{option=nonstop}
\answer{}{\Rep3}{type=raw}{option=nonstop}
\answer{}{\Rep4}{type=raw}{option=nonstop}
\answer{}{\Rep5}{type=raw}{option=nonstop}
\answer{}{\Rep6}{type=raw}{option=nonstop}
\text{N=\step=2?\rep1}
\text{nstep=r2}
\integer{test0=\rep1>=\M1 and \rep1<=\M2 ? 1 : 0}
\text{N=\test0=0 and \step=2? randint(\M1..\M2)}

#include "lang.inc"

\text{lceb=wims(exec lceb \N \dataw)}
\text{lceb1=\lceb}
\text{lceb=wims(line 3 to -1 of \lceb)}
\text{goal=NOTFOUND isin \lceb1? wims(word 2 of wims(line 2 of \lceb1)) : \N}
\integer{R=\Data[1] + \Data[2]}

\text{data1=\data}
\integer{repcnt=rows(\reply2)}
\matrix{rep=\Rep1
\Rep2
\Rep3
\Rep4
\Rep5
\Rep6}
\text{rep=wims(replace internal <pre> by in \rep)}
\text{rep=wims(replace internal </pre> by in \rep)}
\if{\step>=3}{
\text{d=\rep[\step-2;]}
\text{t=wims(replace internal = by == in \d)}
\text{t=pari(\t)}
\text{test3=wims(append item \t to \test3)}
\text{d1=wims(replace internal = by , in \d)}
\text{data=wims(append item \d1[2] to \data)}
\text{d1=wims(translate internal +=-*/ to ,,,,, in \d)}
\text{d1=wims(nonempty items \d1)}
\text{h1=position(\d1[1],\data)}
\text{h2=position(\d1[2],\data)}
\integer{h1=\h1[1]}
\integer{h2=\d1[1] notsametext \d1[2]? \h2[1]:\h2[2]}
\text{test1=\h1 notwordof 1 2 3 4 5 6 or \h2 notwordof 1 2 3 4 5 6 ? wims(append item 0 to \test1):wims(append item 1 to \test1)}
 \if{0 notin \test1}{
    \text{data=wims(replace internal item number \h1 by in \data)}
    \text{data=wims(replace internal item number \h2 by in \data)}
    \text{data=wims(nonempty items \data)}
    \integer{nn=\nn-1}
  }
 \text{nstep=}
 \text{nstep=\step<\nt+1 and \N notitemof \data and abs(\goal - \N) < abs(\N - \d1[3]) and 0 notin \test1 and 0 notin \test3 ? r \step}
 \text{Feed=\t=1?\Feed
\d:\Feed
<span class="oef_indbad">\d</span>}

 \text{test2=\N isitemof \data1 ? 1:0}
 \text{test2=\test2=0 and abs(\goal - \N) >= abs(\N - \d1[3]) ? 1}
}
 \condition{\conditiontext[4;]}{\test0=1}
 \condition{\conditiontext[1;]}{0 notin \test1}{weight=1}
 \condition{\conditiontext[2;]}{0 notin \test3}{weight=3}
 \condition{\conditiontext[3;]}{0 notin \test3,\test1 and \test2=1}{weight=8}

\feedback{1=1}{
\feedtext[1;]

<div class="wimscenter">
\special{expandlines
\Feed
}
</div>
}
\feedback{0 isin \test3,\test1 or \test2!=1}{
\feedtext[2;]
<div class="wimscenter">
\special{expandlines
\lceb
}
</div>
}
