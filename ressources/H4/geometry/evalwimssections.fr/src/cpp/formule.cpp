target=formule1,formule2,formule3,formule4,formule5
#define TITRE Formule d'aire et volume
\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}

#if defined TARGET_formule1 
 \title{TITRE 1}
 \integer{c=randint(2..15)}
 \integer{h=randint(10..50)}
 \text{rep=\c^2*\h/3}
 \text{enonce=Quelle est la mesure du volume d'une pyramide dont la base est un carré dont les côtés mesurent \(\c cm) et dont la hauteur mesure \(\h cm)}
 \text{question1=Son volume est de}
 \text{question2=\(cm^3)}
#endif

#if defined TARGET_formule2 
 \title{TITRE 2}
 \integer{r=randint(2..15)}
 \integer{h=randint(500..200)}
 \text{rep=pi*\r^2*\h/3}
 \text{enonce=Quelle est la mesure du volume d'un cône de révolution dont la base est un disque de rayon \(\r cm) et dont la hauteur mesure \(\h cm)}
 \text{question1=Son volume est de}
 \text{question2=\(cm^3)}
#endif

#if defined TARGET_formule3 
 \title{TITRE 3}
 \integer{r=randint(2..15)}
 \integer{h=randint(500..200)}
 \text{rep=pi*\r^2*\h}
 \text{enonce=Quelle est la mesure du volume d'un cylindre de révolution dont la base est un disque de rayon \(\r cm) et dont la hauteur mesure \(\h cm)}
 \text{question1=Son volume est de}
 \text{question2=\(cm^3)}
#endif


#if defined TARGET_formule4 
 \title{TITRE 4}
 \integer{r=randint(2..20)}
 \text{rep=4/3*pi*\r^3}
 \text{enonce=Quelle est la mesure du volume d'une boule de rayon \(\r cm)}
 \text{question1=Son volume est de}
 \text{question2=\(cm^3)}
#endif

#if defined TARGET_formule5 
 \title{TITRE 5}
 \integer{r=randint(2..20)}
 \text{rep=4*pi*\r^2}
 \text{enonce=Quelle est la mesure de l'aire de la surface d'une sphère de rayon \(\r cm)}
 \text{question1=Son volume est de}
 \text{question2=\(cm^2)}
#endif

\integer{prec=random(1..3)}
\matrix{don=au dixième,1
  au centième,2
  au milième,3
  à 0.1 près,1
  à 0.01 près,2
  à 0.001 près,3}
\text{don=randrow(\don)}
\text{precision=item(1,\don)}
\integer{prec=item(2,\don)}
\integer{tmp=\rep*10^(\prec)}
\real{rep=\tmp/10^(\prec)}

\statement{
\enonce ?
<div>
<strong>Votre réponse :</strong>
\question1  \embed{r1,12} \question2.
</div>
<div class="wims_instruction">
  Vous arrondirez, si nécessaire, votre résultat \precision.
</div>
}

\reply{Réponse}{\rep}{type=numexp}
