target=oefsimpfract1 oefsimpfract2 oefsimpfract3 oefsimpfract4 oefsimpfract5
#define TITRE Simplification d'une fraction
\langage{fr}
\author{Jean-Luc,Donadoni}
\email{jluc.donadoni@laposte.net}
\format{html}

\integer{n1=randint(1..9)}
\integer{n2=randint(2..9)}
\if{\n1=2}{\integer{n2=random(3,5,7,9)}}
\if{\n1=3}{\integer{n2=random(2,4,5,7,8)}}
\if{\n1=4}{\integer{n2=random(3,5,7,9)}}
\if{\n1=6}{\integer{n2=random(5,7,11)}}
\if{\n1=8}{\integer{n2=random(3,5,7,9)}}
\if{\n1=9}{\integer{n2=random(2,4,5,7,8)}}
\if{\n1=\n2}{\integer{n2=\n1+1}}

#if defined TARGET_oefsimpfract1
\title{TITRE 1}
\integer{a=2}
\integer{d1=\n1*\a}
\integer{d2=\n2*\a}
\text{rep1=\n1}
\text{rep2=\n2}
\integer{large=3}
#endif

#if defined TARGET_oefsimpfract2
\title{TITRE 2}
\integer{a=random(3,5,10)}
\integer{d1=\n1*\a}
\integer{d2=\n2*\a}
\text{rep1=\n1}
\text{rep2=\n2}
\integer{large=3}
#endif

#if defined TARGET_oefsimpfract3
\title{TITRE 3}
\integer{a=random(2,3,5,7)}
\integer{d1=\n1*\a}
\integer{d2=\n2*\a}
\text{rep1=\n1}
\text{rep2=\n2}
\integer{large=3}
#endif

#if defined TARGET_oefsimpfract4
\title{TITRE 4}
\integer{a=random(4,6,8,9)}
\integer{d1=\n1*\a}
\integer{d2=\n2*\a}
\text{rep1=\n1}
\text{rep2=\n2}
\integer{large=3}
#endif

#if defined TARGET_oefsimpfract5
\title{TITRE 5}
\integer{a=randint(2..10)}
\integer{d1=\n1*\a}
\integer{d2=\n2*\a}
\text{rep1=\n1}
\text{rep2=\n2}
\integer{large=3}
#endif

\statement{
Simplifier la fraction le mieux possible :
<div class="wimscenter">
\special{mathmlinput [\frac{\d1}{\d2} = \frac{reply1}{reply2}],\large
reply1
reply2}
</div>
}


\answer{}{\rep1}
\answer{}{\rep2}
