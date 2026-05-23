target=approchee1 approchee2 approchee3 approchee4 approchee5
#define TITRE Valeur approchée
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}

#if defined TARGET_approchee1
 \title{TITRE 1}
 \text{don=randrow(petit,supérieur,1
grand,inférieur,2)}
 \real{N=randint(11..99)+randint(111..999)/1000}
 \text{enonce=Quel est le plus \don[1] nombre entier \don[2] au nombre \N &#63;}
 \integer{rep=floor(\N)}
 \integer{rep=\don[3]=1?\rep+1}
#endif

#if defined TARGET_approchee2
 \title{TITRE 2}
 \text{don=randrow(petit,supérieur,1
grand,inférieur,2)}
 \real{N=randint(11..99)+randint(111..999)/1000}
 \real{N=-\N}
 \text{enonce=Quel est le plus \don[1] nombre entier \don[2] au nombre \N &#63;}
 \integer{rep=floor(\N)}
 \integer{rep=\don[3]=1?\rep+1}
#endif

#if defined TARGET_approchee3
 \title{TITRE 3}
 \text{a=randitem(A,B,C,D,E)}
 \text{don=randrow(petit,supérieur,1
grand,inférieur,2)}
 \integer{b=randint(11..99)}
 \integer{rep=randint(1..8)}
 \text{exp=\b+\frac{\a}{10}}
 \real{N=\b+\rep*0.1+randint(11..99)*0.001}
 \text{enonce=Quel est le plus \don[1] nombre entier \a tel que \(\exp) soit \don[2] au nombre \N &#63;}
 \integer{rep=\don[3]=1?\rep+1}
#endif

#if defined TARGET_approchee4
 \title{TITRE 4}
 \text{a=randitem(A,B,C,D,E)}
 \text{don=randrow(petit,supérieur,1
grand,inférieur,2)}
 \integer{b=randint(11..99)}
 \integer{rep=randint(11..98)}
 \text{exp=\b+\frac{\a}{100}}
 \real{N=\b+\rep*0.01+randint(1..9)*0.001}
 \text{enonce=Quel est le plus \don[1] nombre entier \a tel que \(\exp) soit \don[2] au nombre \N &#63;}
 \integer{rep=\don[3]=1?\rep+1}
#endif

#if defined TARGET_approchee5
 \title{TITRE 5}
 \real{N=randint(11..99)+randint(1..9)*0.1+randint(1..9)*0.01+randint(1..9)*0.001}
 \integer{ch=randint(0..2)}
 \text{arr=item(\ch+1,à l'unité,au dixième,au centième)}
 \real{rep=rint((\N)*10^\ch)/10^\ch}
 \text{enonce=Quel est l'arrondi \arr du nombre \N &#63;}
#endif

\statement{
\enonce<p>
<b>Votre réponse</b>: \embed{r1,5}
</p>}

\answer{}{\rep}{type=numexp}
