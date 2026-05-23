target=vocabulaire1 vocabulaire2

\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}

#if defined TARGET_vocabulaire1
 \title{Vocabulaire multiplication}
 \matrix{donnees=double,2*x,le
  triple,3*x,le
  moitié,x/2,la
  tiers,x/3,le
  quart,x/4,le
  deux-tiers,2*x/3,les
  trois-quarts,3*x/4,les}
 \integer{nombre=4*3*randint(3..25)}
#endif

#if defined TARGET_vocabulaire2
 \title{Vocabulaire puissance}
 \matrix{donnees=carré,x^2,le
  cube,x^3,le}
 \integer{nombre=randint(4..9)}
#endif

\text{don=randrow(\donnees)}

\text{mot=item(1,\don)}
\function{calcul=item(2,\don)}
\text{article=item(3,\don)}
\text{enonce=les isin \article?Quels sont:Quel est}
\text{enonce=la isin \article?Quelle est}
\integer{res=evalue(\calcul,x=\nombre)}

\statement{
\enonce \article \mot de \nombre ?
<div>
<b><label for="reply1">Votre réponse :</label></b> \embed{r1,6}.
</div>
}

\answer{réponse}{\res}{type=numexp}
