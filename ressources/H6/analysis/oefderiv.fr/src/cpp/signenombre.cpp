target=signenombre
#include "xiao.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{data1=randomrow(
ln(x+1),+
1/(x+1),-
sin(x),+
e^x,+
),1}
\text{data2=randomrow(
1/(x+1)^2,-
(x+1)^2,+
),2}
\text{data3=randomrow(
(x+1)^3,+
1/(x+1)^3,-
),3}
\text{datah=randomrow(
sqrt(x+1),+
1/sqrt(x+1),-
),0.5}
\text{data=\data1;\data2;\data3;\datah}
\integer{cnt=rows(\data)}
\text{take=shuffle(\cnt)}
\text{data1=row(\take[1],\data)}
\text{data2=row(\take[2],\data)}
\text{f1=\data1[1]}
\text{f2=\data2[1]}
\text{sign1=\data1[2]}
\text{sign2=\data2[2]}
\text{c1=\data1[3]}
\text{c2=\data2[3]}
\text{add=\sign1 1 = \sign2 1?+:-}

\real{epsilon=randitem(0.001,0.002,0.003,0.005,0.006,0.008,0.01,0.015,0.02,0.03,0.05)*random(1,-1)}
\real{minus=-(\epsilon)}
\real{plus1=1+\epsilon}
\real{minus1=1-\epsilon}
\real{plus2=2+\epsilon}
\real{minus2=2-\epsilon}
\text{interval=\epsilon>0?[0,\epsilon]:[\epsilon,0]}
\text{v1=wims(replace internal x+1 by \plus1 in \f1)}
\text{v1=wims(replace internal x+2 by \plus2 in \v1)}
\text{v1=wims(mathsubst x=\epsilon in \v1)}
\text{v2=wims(replace internal x+1 by \minus1 in \f2)}
\text{v2=wims(replace internal x+2 by \minus2 in \v2)}
\text{v2=wims(mathsubst x=\minus in \v2)}
\text{f2=wims(mathsubst x=-x in \f2)}
\text{t=randint(1,2)}
\function{f=item(\t,\f1 \add \f2,\f2 \add \f1)}
\function{value=item(\t,\v1 \add \v2,\v2 \add \v1)}
\real{const=evalue(\f,x=0)}
\if{\const != 0} {
 \function{f=\f - \const}
 \function{value=\value - \const}
}

\function{badf=wims(mathsubst x=-x in \f)}
\function{deriv=diff(\f,x)}
\function{badderiv=diff(\badf,x)}
\real{deriv0=evalue(\deriv,x=0)}
\text{sens=\deriv0>0?>:<}
\text{rev=\deriv0<0?>:<}
\text{sens2=\deriv0*\epsilon>0?>:<}
\text{rev2=\deriv0*\epsilon<0?>:<}
\text{posneg=\deriv0*\epsilon>0?\name_posneg[1]:\name_posneg[2]}
\text{negpos=\deriv0*\epsilon<0?\name_posneg[1]:\name_posneg[2]}

\text{step1=wims(embraced randitem {\name_step1[1;]} \name_step1[2;]
\(f : x\) \(\mapsto\) \(\f\).)}
\text{step2=wims(embraced randitem {\name_step2[1;]} \name_step2[2;] :
\(f\prime(x)\) = \(\deriv\).)}
\text{step3=\name_step3[1] \(f '(x) \sens 0\) \name_step3[2] \(x \in \interval\).}
\text{step4=wims(embraced randitem \(a = f(\epsilon) \sens2 f(0) = 0\)&#44;
{\name_step4[1;]} \(a\) \name_step4[2;] \posneg.)}
\text{bad1=wims(embraced randitem {\name_bad1[1;]} \name_bad1[2;]
\(f : x\) \(\mapsto\) \(\badf\).)}
\text{bad2=wims(embraced randitem {\name_bad2[1;]} \name_bad2[2;] :
\(f\prime(x)\) = \(\badderiv).)}
\text{bad3=\name_bad3[1] \(f '(x) \rev 0\) \name_bad3[2] \(x \in \interval\).}
\text{bad4=wims(embraced randitem \(a = f(\epsilon) \rev2 f(0) = 0\)&#44;
{\name_bad4[1;]} \(a\) \name_bad4[2;] \negpos.)}
\text{good=wims(singlespace \step1,\step2,\step3,\step4)}
\text{bad=wims(singlespace \bad1,\bad2,\bad3,\bad4)}

\text{p1=randitem(\name_p1)}
\text{p2=randitem(\name_p23)}
\text{p3=randitem(\name_p23)}
\text{p4=randitem(\name_p4)}

\text{feed6=wims(replace internal XXXX by \sens in \name_feed6)}
\text{size=400x70x1}

\statement{\feed3
\name_enonce[1] \(a = \value\) \name_enonce[2]
<ul> <li>\p1, <div class="center">\embed{r1,\size}</div>
</li><li>\p2, <div class="center">\embed{r2,\size}</div>
</li><li>\p3, <div class="center">\embed{r3,\size}</div>
</li><li>\p4, <div class="center">\embed{r4,\size}</div>
</li></ul>
}

\answer{\name_answer 1}{\t1;\good,\bad}{type=dragfill}
\answer{\name_answer 2}{\t2}{type=dragfill}
\answer{\name_answer 3}{\t3}{type=dragfill}
\answer{\name_answer 4}{\t4}{type=dragfill}

\text{r1=\t1 issametext \step1?1:0}
\text{r2=\t2 issametext \step2?1:0}
\text{r3=\t3 issametext \step3?1:0}
\text{r4=\t4 issametext \step4?1:0}
\text{b1=\t1 issametext \bad1?1:0}
\text{b2=\t2 issametext \bad2?1:0}
\text{b3=\t3 issametext \bad3?1:0}
\text{b4=\t4 issametext \bad4?1:0}
\condition{\name_cond}{\r1*\r2*\r3*\r4=1}

\feedback{\r1+\b1=0 and \t1 isitemof \good[2,3],\bad[2,3]}{
 \name_feed1 \(f\)&nbsp;?
}
\feedback{\b1*(\r4+\b4)=1}{
 \name_feed2[1] \(f(\epsilon) = a\), \name_feed2[2]
 \(f(x) = \f\), \name_feed2[3] \(f(x) = \badf\).
}

\feedback{\r1*\b2=1 or \b1*\r2=1}{ \name_feed3 \(f\)&nbsp;?}
\feedback{\r1+\b1=1 and \r2+\b2=0}{\name_feed4}
\feedback{\r2*\b3=1}{\name_feed5[1] \(f'(x)\). \name_feed5[2].}
\feedback{\r3*\b4=1 or \b3*\r4=1}{\feed6?}
\feedback{\r4+\b4=0}{\name_feed7 \(a\).}
