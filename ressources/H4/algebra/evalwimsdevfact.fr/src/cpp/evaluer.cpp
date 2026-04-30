target=evalA1,evalA2,evalA3,evalA4,evalA5,evalB1,evalB2,evalB3,evalB4,evalB5

\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}
#define TITRE Evaluer premier degré
\text{list=wims(values v for v=2 to 12)}
\text{list=shuffle(\list)}
\integer{a=item(1,\list)}
\integer{b=item(2,\list)}
\integer{e=item(3,\list)}
\integer{g=gcd(\a,\b)}
\integer{c=randint(2..5)}
\integer{d=randint(2..5)}
\integer{g=gcd(\c,\d)}
\if{\g!=1}{
 \integer{c=4}
 \integer{d=9}
}

\text{x=randitem(x,y,z,t,u,v)}
\text{A=randitem(A,B,C,D,V)}
\text{sg=randitem(-,+)}
\text{sg1=shuffle(-,+)}
\text{sg2=item(1,\sg1)}
\text{sg1=item(2,\sg1)}

#if defined TARGET_evalA1
 \title{TITRE 1}
 \text{enonce=\a*\x\sg\b}
 \text{val=\c}
#endif

#if defined TARGET_evalA2
 \title{TITRE 2}
 \text{enonce=-\a*\x\sg\b}
 \text{val=\c}
#endif

#if defined TARGET_evalA3
 \title{TITRE 3}
 \text{enonce=-\a*\x\sg\b}
 \text{val=-\c}
#endif

#if defined TARGET_evalA4
 \title{TITRE 4}
 \text{enonce=-\a*\x\sg\b}
 \text{val=\c/\d}
#endif

#if defined TARGET_evalA5
 \title{TITRE 5}
 \text{enonce=-\a*\x\sg\b}
 \text{val=-\c/\d}
#endif

#if defined TARGET_evalB1
 \title{Evaluer second degré 1}
 \text{enonce=\a*\x^2\sg1\b*\x+\e}
 \text{val=0}
#endif

#if defined TARGET_evalB2
 \title{Evaluer second degré 2}
 \text{enonce=\a*\x^2\sg1\b*\x+\e}
 \text{val=\c}
#endif

#if defined TARGET_evalB3
 \title{Evaluer second degré 3}
 \text{enonce=\a*\x^2\sg1\b*\x+\e}
 \text{val=-\c}
#endif

#if defined TARGET_evalB4
 \title{Evaluer second degré 4}
 \text{enonce=\a*\x^2\sg1\b*\x+\e}
 \text{val=1/\c}
#endif

#if defined TARGET_evalB5
 \title{Evaluer second degré 5}
 \text{enonce=\a*\x^2\sg1\d*\x+\e}
 \text{val=-\c/\d}
#endif

\text{affichage=texmath(\enonce)}
\text{affval=texmath(\val)}
\text{rep=wims(replace internal \x by (\val) in \enonce)}
\text{rep=simplify(\rep)}

\statement{
  Quelle est la valeur de l'expression \(\A = \affichage) pour \(\x = \affval) ?
<p>
<b>Votre réponse :</b>
</p>
<div class="wimscenter">
\(\A =) \embed{r1,20}.
</div>}

\reply{réponse}{\rep}{type=numexp}
