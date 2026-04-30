target=volumecoeff1,volumecoeff2,volumecoeff3,volumecoeff4
#define TITRE Agrandissement réduction et volume
\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}

\text{C=randitem(C,D,E,R)}
\matrix{don=cône,un
  cube,un
  parallélépipède,un
  boule,une
  pyramide,une}
\text{don=randrow(\don)}
\text{figure=item(1,\don)}
\text{art=item(2,\don)}
\text{obtenu=\art=un?obtenu:obtenue}
\text{note=\ârt=un?noté:notée}
\real{aire1=randint(10..100)/10}
\real{coef=randitem(randint(1..9)/10,randint(11..99)/10)}
\real{aire2=\aire1*\coef^3}

#if defined TARGET_volumecoeff1
 \title{TITRE 1}
 \text{inconnue=\mathcal{\C}}
 \text{connue=\mathcal{\C}'}
 \text{caire=\aire1}
 \text{repaire=\aire2}
 \text{transfo=\coef<1?une réduction:un agrandissement}
 \text{enonce=\(\mathcal{\C}) est \art \figure \obtenu à partir d'\art \figure \(\mathcal{\C}') par \transfo de coefficient \(\coef)}
#endif

#if defined TARGET_volumecoeff2
 \title{TITRE 2}
 \text{inconnue=\mathcal{\C}'}
 \text{connue=\mathcal{\C}}
 \text{caire=\aire2}
 \text{repaire=\aire1}
 \text{transfo=\coef<1?une réduction:un agrandissement}
 \text{enonce=\(\mathcal{\C}) est \art \figure \obtenu à partir d'\art \figure \(\mathcal{\C}') par \transfo de coefficient \(\coef)}
#endif

#if defined TARGET_volumecoeff3
 \title{TITRE 3}
 \matrix{don=\mathcal{\C},\mathcal{\C}',\aire1,\aire2
\mathcal{\C}',\mathcal{\C},\aire2,\aire1}
 \text{don=randrow(\don)}
 \text{inconnue=item(1,\don)}
 \text{connue=item(2,\don)}
 \text{caire=item(3,\don)}
 \text{repaire=item(4,\don)}
 \text{enonce=\(\mathcal{\C}') est \art \figure. On multiplie les longueurs de \(\mathcal{\C}') par \(\coef) afin d'obtenir \art autre \figure \note \(\mathcal{\C})}
#endif

#if defined TARGET_volumecoeff4
 \title{TITRE 4}
 \matrix{don=\mathcal{\C},\mathcal{\C}',\aire2,\aire1
\mathcal{\C}',\mathcal{\C},\aire1,\aire2}
 \text{don=randrow(\don)}
 \text{inconnue=item(1,\don)}
 \text{connue=item(2,\don)}
 \text{caire=item(3,\don)}
 \text{repaire=item(4,\don)}
 \text{enonce=\(\mathcal{\C}') est \art \figure. On divise les longueurs de \(\mathcal{\C}') par \(\coef) afin d'obtenir \art autre \figure \note \(\mathcal{\C})}
#endif

\statement{
\enonce.
<br>
  Quelle est la mesure du volume de \(\inconnue) sachant que le volume de \(\connue) mesure \(\caire cm^3) ?
<p>
<strong>Votre réponse :</strong></p>
  Le volume de \(\inconnue) mesure \embed{r1,12} \(cm^3).
}

\answer{réponse}{\repaire}{type=litexp}
