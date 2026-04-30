target=airecoeff1,airecoeff2,airecoeff3,airecoeff4
#define TITRE Agrandissement réduction et aire
\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}

\text{C=randitem(C,D,E,R)}
\text{figure=randitem(disque,triangle,carré,losange,parallélogramme,pentagone)}
\real{aire1=randint(10..100)/10}
\real{coef=randitem(randint(1..9)/10,randint(11..99)/10)}
\real{aire2=\aire1*\coef^2}

#if defined TARGET_airecoeff1
 \title{TITRE 1}
 \text{inconnue=\mathcal{\C}}
 \text{connue=\mathcal{\C}'}
 \text{caire=\aire1}
 \text{repaire=\aire2}
 \text{transfo=\coef<1?une réduction:un agrandissement}
 \text{enonce=\(\mathcal{\C}) est un \figure obtenu à partir d'un \figure \(\mathcal{\C}') par \transfo de coefficient \(\coef)}
#endif

#if defined TARGET_airecoeff2
 \title{TITRE 2}
 \text{inconnue=\mathcal{\C}'}
 \text{connue=\mathcal{\C}}
 \text{caire=\aire2}
 \text{repaire=\aire1}
 \text{transfo=\coef<1?une réduction:un agrandissement}
 \text{enonce=\(\mathcal{\C}) est un \figure obtenu à partir d'un \figure \(\mathcal{\C}') par \transfo de coefficient \(\coef)}
#endif

#if defined TARGET_airecoeff3
 \title{TITRE 3}
 \matrix{don=\mathcal{\C},\mathcal{\C}',\aire1,\aire2
\mathcal{\C}',\mathcal{\C},\aire2,\aire1}
 \text{don=randrow(\don)}
 \text{inconnue=item(1,\don)}
 \text{connue=item(2,\don)}
 \text{caire=item(3,\don)}
 \text{repaire=item(4,\don)}
 \text{enonce=\(\mathcal{\C}') est un \figure. On multiplie les longueurs de tous les côtés de \(\mathcal{\C}') par \(\coef) afin d'obtenir un nouveau \figure noté \(\mathcal{\C})}
#endif

#if defined TARGET_airecoeff4
 \title{TITRE 4}
 \matrix{don=\mathcal{\C},\mathcal{\C}',\aire2,\aire1
\mathcal{\C}',\mathcal{\C},\aire1,\aire2}
 \text{don=randrow(\don)}
 \text{inconnue=item(1,\don)}
 \text{connue=item(2,\don)}
 \text{caire=item(3,\don)}
 \text{repaire=item(4,\don)}
 \text{enonce=\(\mathcal{\C}') est un \figure. On divise les longueurs de tous les côtés de \(\mathcal{\C}') par \(\coef) afin d'obtenir un nouveau \figure noté \(\mathcal{\C})}
#endif

\statement{
\enonce.<br>
  Quelle est la mesure de l'aire de \(\inconnue) sachant que l'aire de \(\connue) mesure \(\caire cm^2) ?
<p>
<strong>Votre réponse :</strong>
</p>
  L'aire de \(\inconnue) mesure \embed{r1,12} \(cm^2).
}

\answer{réponse}{\repaire}{type=litexp}
