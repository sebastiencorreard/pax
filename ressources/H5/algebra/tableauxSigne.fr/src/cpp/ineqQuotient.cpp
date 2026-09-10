target=ineqQuotient

\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{cas=random(1..2)}
\integer{a = (-1)^random(0,1)*random(1..10)}
\integer{b = (-1)^random(0,1)*random(1..10)}
\integer{c = (-1)^random(0,1)*random(1..10)}
\integer{d = (-1)^random(0,1)*random(1..10)}
\integer{k1=(-1)^random(0,1)*random(1..10)}
\integer{k2=(-1)^random(0,1)*random(1..10)}
\integer{cas=random(1..2)}
\function{f=\a *x + \b}
\function{f=\a==1?x + \b}
\function{f=\a==-1?-x + \b}
\function{g=\c *x + \d}
\function{g=\c==1?x + \d}
\function{g=\c==-1?-x + \d}
\text{lsymb=<,>,\leq,\geq}
\text{symb=item(1,shuffle(\lsymb))}
\function{q1=\k2/(\g)}
\function{q2=\k1/(\f)}
\text{lineq=\(\k1 \symb) \(\q1), \(\q2) \(\symb \k2)}
\function{ineq=item(\cas,\lineq)}
\text{uu=(\k1*(\g)-\k2),(\k1-\k2*(\f))}
\text{vv=\g,\f}
\function{u=maxima(expand(item(\cas,\uu)))}
\function{v=item(\cas,\vv)}
\function{q=(\u)/(\v)}
\integer{ua=pari(polcoeff(\u,1))}
\integer{ub=pari(polcoeff(\u,0))}
\rational{racu=-\ub/\ua}
\rational{racv=\cas==1?-\d/\c}
\rational{racv=\cas==2?-\b/\a}
/** ordonner les racines ; preparer les tests de signe **/
\integer{test=\racu<\racv?1:2}
\rational{x1=\test==1?\racu:\racv}
\rational{x2=\test==1?\racv:\racu}
/** placer le terme ayant la plus petite racine en premier **/
/** cas = 1 : u avant v ; cas = 2 : v avant u **/
\rational{xm=(\x1+\x2)/2}
\rational{ug = evaluate(\u,x=\x1-1)}
\rational{um = evaluate(\u,x=\xm)}
\rational{ud = evaluate(\u,x=\x2+1)}
\rational{vg = evaluate(\v,x=\x1-1)}
\rational{vm = evaluate(\v,x=\xm)}
\rational{vd = evaluate(\v,x=\x2+1)}
/** elements du tableau **/
\rational{rep1=\x1}
\rational{rep2=\x2}
\text{rep3=\ug>0?+:-}
\text{rep4=\x1==\racu?0:}
\text{rep5=\um>0?+:-}
\text{rep6=\x2==\racu?0:}
\text{rep7=\ud>0?+:-}
\text{rep8=\vg>0?+:-}
\text{rep9=\x1==\racv?0:}
\text{rep10=\vm>0?+:-}
\text{rep11=\x2==\racv?0:}
\text{rep12=\vd>0?+:-}
\text{rep13=\rep3 issametext \rep8?+:-}
\text{rep14=\x1==\racv?db:0}
\text{rep15=\rep5 issametext \rep10?+:-}
\text{rep16=\x2==\racv?db:0}
\text{rep17=\rep7 issametext \rep12?+:-}
\text{tableau1=slib(function/tabsignes [x,-Inf,,\x1,,\x2,,+Inf;\u,,\rep3,\rep4,\rep5,\rep6,\rep7; \v,,\rep8,\rep9,\rep10,\rep11,\rep12;f(x),,\rep13,\rep14,\rep15,\rep16,\rep17])}
\text{tableau=<table class="wimsborder">
<tr>
<th style="width:15%">\(x)</th>
<td style="width:25%;text-align:left">\(-\infty)</td>
<td style="width:5%">\x1</td>
<td style="width:25%;text-align:right"></td>
<td style="width:5%">\x2</td>
<td style="width:25%;text-align:right">\(+\infty)</td>
</tr><tr>
<th>\(\u)</th>
<td>\rep3</td>
<td>\rep4</td>
<td>\rep5</td>
<td>\rep6</td>
<td>\rep7</td>
</tr><tr>
<th>\(\v)</th>
<td>\rep8</td>
<td>\rep9</td>
<td>\rep10</td>
<td>\rep11</td>
<td>\rep12</td>
</tr><tr>
<th>\(f(x))</th>
<td>\rep13</td>
<td>\rep14</td>
<td>\rep15</td>
<td>\rep16</td>
<td>\rep17</td>
</tr>
</table>}
/** choix des intervalles **/
\text{int1= &#93; -&#8734; &#44;\x1 &#91; }
\text{int2=&#93; -&#8734; &#44;\x1 &#93; }
\text{int3=&#91; \x2 &#44; +&#8734; &#91; }
\text{int4=&#93; \x2 &#44; +&#8734; &#91; }
\text{S1=\int1 \(\cup) \int3}
\text{S2=\int1 \(\cup) \int4 }
\text{S3=\int2 \(\cup) \int3}
\text{S4=\int2 \(\cup) \int4 }
\text{S5=&#91; \x1 &#44; \x2 &#91; }
\text{S6=&#91; \x1 &#44; \x2 &#93; }
\text{S7=&#93; \x1 &#44; \x2 &#91; }
\text{S8=&#93; \x1 &#44; \x2 &#93; }
\text{choix=<i>S</i><sub>1</sub>,<i>S</i><sub>2</sub>,
<i>S</i><sub>3</sub>,<i>S</i><sub>4</sub>, <i>S</i><sub>5</sub>,<i>S</i><sub>6</sub>,
<i>S</i><sub>7</sub>,<i>S</i><sub>8</sub>}
\text{sol=(\symb issametext < and \rep15 issametext -) or
(\symb issametext > and \rep15 issametext +)?7}
\text{sol=(\symb issametext > and \rep13 issametext +) or
(\symb issametext < and \rep13 issametext -)?2}
\text{sol=(\symb issametext \leq and \rep13 issametext - and \x1==\racv)? 1}
\text{sol=(\symb issametext \leq and \rep13 issametext - and \x1!=\racv)? 4}
\text{sol=(\symb issametext \leq and \rep15 issametext - and \x1==\racv)? 8}
\text{sol=(\symb issametext \leq and \rep15 issametext - and \x1!=\racv)? 5}
\text{sol=(\symb issametext \geq and \rep13 issametext + and \x1==\racv)? 1}
\text{sol=(\symb issametext \geq and \rep13 issametext + and \x1!=\racv)? 4}
\text{sol=(\symb issametext \geq and \rep15 issametext + and \x1==\racv)? 8}
\text{sol=(\symb issametext \geq and \rep15 issametext + and \x1!=\racv)? 5}

\text{question3=wims(replace internal XXXX by  \(f(x) = \q \) in \name_question3)}
\steps{reply1
reply2}

\statement{
<div class="wims_question">
\name_question: \ineq.
</div>
<ol><li>
\if{\step==1}{
\name_question2 \(\frac{u(x)}{v(x)} \symb 0\) \name_with \(u(x)\) \name_and \(v(x)\)
\name_binome:
<div class="wimscenter">\(u(x)\) = \embed{reply1, 12} \name_and \( v(x)\) = \(\v\).</div>}
{\name_enonce1 : \(\q\)\(\symb 0 \).}
</li>
\if{\step==2}
{<li>\question3
<div class="wimscenter">\tableau</div>
</li>
}
\if{\step==2}{<li> \name_def:
<ul class="wims_nopuce">
<li>\(S_1\) = \S1</li>
<li>\(S_2\) = \S2</li>
<li>\(S_3\) = \S3</li>
<li>\(S_4\) = \S4</li>
<li>\(S_5\) = \S5</li>
<li>\(S_6\) = \S6</li>
<li>\(S_7\) = \S7</li>
<li>\(S_8\) = \S8</li></ul>
\name_question4:
<div class="wimscenter">\embed{reply2}.</div>
</li>
}
</ol>
}
\answer{\sujquest1}{\u}{type=algexp}{option=nonstop}
\answer{}{\sol ; \choix}{type=radio}{option=nonstop}
\function{testrep1 = simplify(\reply1-(\u))}
\feedback{\testrep1 != 0 }{
  <div><span class="oef_indbad">\name_feed1</span> \name_feed2?</div>}
