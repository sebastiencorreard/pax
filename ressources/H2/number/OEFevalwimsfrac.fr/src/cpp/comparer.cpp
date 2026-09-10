target=comparer1 comparer2 comparer3 comparer4 comparer5
#define TITRE Comparer avec une fraction à l'unité
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}

#if defined TARGET_comparer1 
 \title{TITRE 1}
 \text{v=wims(values v for v=2 to 15)}
 \text{v=shuffle(\v)}
 \text{fr=\v[1]/\v[2]}
#endif

#if defined TARGET_comparer2 
 \title{TITRE 2}
 \text{d=randint(2..9)}
 \text{n=randint(10..20)}
 \text{fr=-\n/\d}
#endif

#if defined TARGET_comparer3 
 \title{TITRE 3}
 \text{v=randint(5..15)}
 \text{fr=1/\v}
#endif

#if defined TARGET_comparer4 
 \title{TITRE 4}
 \integer{ch=randint(1..2)}
 \if{\ch=1}{
  \real{d=randint(35..99)+randint(1..9)*0.1+randint(1..9)*0.01}
  \real{n=randint(1..2)+randint(1..9)*.1}
 }{
  \real{n=randint(35..99)+randint(1..9)*0.1+randint(1..9)*0.01}
  \real{d=randint(1..2)+randint(1..9)*.1}
 }
 \text{fr=\n/\d}
#endif

#if defined TARGET_comparer5 
 \title{TITRE 5}
 \real{v=randint(3..9)*0.1}
 \text{fr=\v}
 \integer{ch=randint(1..2)}
 \text{type=item(\ch,plus grand,plus petit)}
 \text{rep=(\ch=1 and \fr>1) or (\ch=2 and \fr<1)?Vrai:Faux}
 \statement{
Répondre par Vrai ou Faux :
<div class="wimscenter">
\(\frac{\v}{1}) est \type que 1.
</div>}
 \choice{}{\rep}{Vrai,Faux}
#else
 \integer{ch=randint(1..2)}
 \text{type=item(\ch,plus grand,plus petit)}
 \text{rep=(\ch=1 and \fr>1) or (\ch=2 and \fr<1)?Vrai:Faux}
 \text{fr=texmath(\fr)}
 \statement{
Répondre par Vrai ou Faux :
<div class="wimscenter">
\(\fr) est \type que 1.
</div>}
 \choice{}{\rep}{Vrai,Faux}
#endif

