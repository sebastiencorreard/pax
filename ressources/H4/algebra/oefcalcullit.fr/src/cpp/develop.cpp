target=dev1exp dev2exp dev2fact1 dev2fact2
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
\keywords{literal_calculation}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_dev1exp
\text{s1=random(+,-)}
\text{s2=random(+,-)}
\text{s3=random( ,-)}

\integer{x1=random(2..10)}
\integer{x2=random(2..10)}
\integer{x3=random(1..10)}
\integer{x4=random(1..10)}
\integer{x5=random(1..10)}
\integer{x6=random(1..10)}

\text{v1=random(x,x,x,y,y,y,z,z,m,n,t,k)}
\text{v2=random(x,y,z,m,n,t,k)}

\text{et1=\s3 (\v2 \s2 \x2)*(\v2 \s1 \x4)}
\text{er1=maxima(expand((\et1));)}
\text{eq1=texmath(\er1)}
\text{ea1=maxima(factor((\er1));)}
\text{ea1=texmath(\ea1)}

\text{t1=\s3 (\v1 \s1 \x4)*(\v1 \s2 \x3)}
\text{r1=maxima(expand((\t1));)}
\text{q1=texmath(\r1)}
\text{a1=maxima(factor((\r1));)}
\text{a1=texmath(\a1)}

\text{ans=\r1}
%%%%% MB feedback %%%%%
\function{feedans=pari(\ans)}
%%%%%%
\statement{ \name_enonce
<div class="wimscenter">
\(\a1\).
</div>
<label for="reply1">\name_answer</label>: \embed{reply1,15}
}
\answer{\name_answer}{\ans}{type=default}{option=noanalyzeprint}
%%% MB %%%%
%%%%% affichage de la bonne réponse bien écrite %%%%
\feedback{\sc_reply1 <1}{<div class="feedback">La bonne réponse était &#58;  \(\feedans\)}
#endif
#if defined TARGET_dev2exp
\integer{a1=randint(1..15)}
\integer{b1=randint(-15..15)}
\if{\b1=0}{\integer{b1=\b1+1}}

\integer{c1=randint(1..15)}
\integer{d1=randint(-15..15)}
\if{\d1=0}{\integer{d1=\d1+1}}

\integer{a2=randint(1..15)}
\integer{b2=randint(-15..15)}
\if{\b2=0}{\integer{b2=\b2+1}}
\integer{c2=randint(1..15)}
\integer{d2=randint(-15..15)}
\if{\d2=0}{\integer{d2=\d2+1}}

\text{alea=+,-}
\text{\alea=shuffle(\alea)}
\text{\alea=item(1,\alea)}

\text{exp=(\a1*x+\b1)*(\c1*x+\d1)\alea(\a2*x+\b2)*(\c2*x+\d2)}
\text{exp1=(\a1*x+\b1)*(\c1*x+\d1)}
\text{exp2=(\a2*x+\b2)*(\c2*x+\d2)}
\text{exp_html=texmath(\exp)}
\text{exp_dev=maxima(expand(\exp))}
\text{exp_dev1=maxima(expand(\exp1))}
\text{exp_dev2=maxima(expand(\exp2))}

\statement{
<p>\name_enonce:</p>
<ul class="wims_nopuce">
<li><label for="reply1">\(\exp_html\)</label>
</li>\({}={}\)\embed{reply1, 20}\({}\alea({}\)\embed{reply2, 20}\({}))</li>
</li><li>
<label for="reply3">\(\exp_html\)</label>=\embed{reply3, 20}.
</li></ul>
<div class="wims_instruction">\name_instruction</div>
}

\answer{}{\exp_dev1}{type=function}
\answer{}{\exp_dev2}{type=function}
\answer{}{\exp_dev}{type=algexp}

#endif
#if (defined TARGET_dev2fact1 || defined TARGET_dev2fact2 )
\text{s3=random( ,-)}
\text{s1=+,-}
\text{s1=shuffle(\s1)}
\text{fs1=item(2,\s1)}
\text{s1=item(1,\s1)}
\text{s2=+,-}
\text{s2=shuffle(\s2)}
\text{fs2=item(2,\s2)}
\text{s2=item(1,\s2)}

\integer{x1=random(2..10)}
\integer{x2=random(2..10)}
\integer{x3=random(1..10)}
\integer{x4=random(1..10)}
\integer{x5=random(2..10)}
\integer{x6=random(1..10)}
///// on veut éviter x3=x4=2
\integer{x4=(\x3=\x4 and \x4=2)?\x4+1}

\text{v1=random(x,x,x,y,y,y,z,z,m,n,t,k)}
\text{v2=random(x,y,z,m,n,t,k)}

#if defined TARGET_dev2fact1
\text{et1=\s3 (\v2 \s2 \x2)*(\v2 \s1 \x4)}
\text{er1=maxima(expand((\et1));)}
\text{eq1=texmath(\er1)}
\text{ea1=maxima(factor((\er1));)}
\text{ea1=texmath(\ea1)}

\text{t1=\s3 (\v1 \s1 \x4)*(\v1 \s2 \x3)}
\text{r1=maxima(expand((\t1));)}
\text{q1=texmath(\r1)}
\text{a1=maxima(factor((\r1));)}
\text{a1=texmath(\a1)}

\text{tx1=\x1*\x2}
\text{t21=simplify(\s3(\s1\x4\s2\x3))}
\text{t22=simplify(\s3(\s1\x4)*(\s2\x3))}
\text{t2=\s3\v1^2+\t22\v1+\t21}
\text{q2=texmath(\t2)}
\text{a2=maxima(factor((\r2));)}
\text{a2=texmath(\a2)}

\text{tx2=\x4*\x6}
\text{t31=simplify(\s3(\fs1\x4\s2\x3))}
\text{t32=simplify(\s3(\s1\x4)*(\fs2\x3))}
\text{t3=\s3\v1^2+\t32\v1+\t31}
\text{q3=texmath(\t3)}
\text{a3=maxima(factor((\r3));)}
\text{a3=texmath(\a3)}

\text{t4=(\v1 \s1 \x4)*(\v1 \fs2 \x3)}
\text{r4=maxima(expand((\t4));)}
\text{q4=texmath(\r4)}
\text{a4=maxima(factor((\r4));)}
\text{a4=texmath(\a4)}
#endif
#if defined TARGET_dev2fact2
\text{et1=\s3 (\v2 \s2 \x2)*(\v2 \s1 \x4)}
\text{er1=maxima(expand((\et1));)}
\text{eq1=texmath(\er1)}
\text{ea1=maxima(factor((\er1));)}
\text{ea1=texmath(\ea1)}

\text{t1=\s3 \x5*(\v1 \s1 \x4)*(\v1 \s2 \x3)}
\text{r1=maxima(expand((\t1));)}
\text{q1=texmath(\r1)}
\text{a1=maxima(factor((\r1));)}
\text{a1=texmath(\a1)}

\text{t21=simplify(\s3\x5*(\s1\x4\s2\x3))}
\text{t22=simplify(\s3\x5*(\s1\x4)*(\s2\x3))}
\text{t2=\s3\x5*\v1^2+\t22\v1+\t21}
\text{q2=texmath(\t2)}
\text{a2=maxima(factor((\r2));)}
\text{a2=texmath(\a2)}

\text{t31=simplify(\s3(\s1\x4\s2\x3))}
\text{t32=simplify(\s3(\s1\x4)*(\s2\x3))}
\text{t3=\s3\x5*\v1^2+\t31\v1+\t32}
\text{q3=texmath(\t3)}
\text{a3=maxima(factor((\r3));)}
\text{a3=texmath(\a3)}

\text{t4=(\x5*\v1 \s1 \x4)*(\v1 \s2 \x3)}
\text{r4=maxima(expand((\t4));)}
\text{q4=texmath(\r4)}
\text{a4=maxima(factor((\r4));)}
\text{a4=texmath(\a4)}
#endif

\text{l=a,b,c,d}
\text{n=shuffle(4)}
\text{as=\q1,\q2,\q3,\q4}
\text{an1=position(1,\n)}
\text{ans=item(\an1,\l)}

\text{p1=item(1,\n)}
\text{p2=item(2,\n)}
\text{p3=item(3,\n)}
\text{p4=item(4,\n)}
\text{aa1=item(\p1,\as)}
\text{bb1=item(\p2,\as)}
\text{cc1=item(\p3,\as)}
\text{dd1=item(\p4,\as)}
\text{vide=}
\statement{\name_enonce
<div class="wimscenter">\(\a1\).</div>
<ul class="wims_nopuce"><li> a. \(\aa1\)
</li><li>
b. \(\bb1\)
</li><li>
c. \(\cc1\)
</li><li>
d. \(\dd1\)
</li></ul>
<label for="reply1">\name_instruction</label> \embed{reply1,3}
<div class="wimscenter"><label for="reply2">\name_brou</label></div>
<div class="wimscenter">
\embed{reply2,10x30}</div>
}

\hint{
<h3>\name_hint[1]</h3>
  \name_hint[2]
<div class="wimscenter">
\((x + p)(x + q)\)
</div>
 \name_hint[3]
<div class="wimscenter"> \(x^2 - (p+q)x + p q\)
</div>
<h3>\name_hint[4]</h3>
<div class="wimscenter">
\(\ea1\)
<br>
\(\eq1\)
</div>
}
\answer{a,b,c,d}{\ans}{type=text}
\answer{}{\reptext}{type=matrix}{option=default=vide}
#endif
