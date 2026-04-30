target=coefficientA1,coefficientA2,coefficientA3,coefficientA4,coefficientA5,coefficientV1,coefficientV2,coefficientV3,coefficientV4,coefficientV5
#define TITRE Aire et coefficient
\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}

#if defined TARGET_coefficientA1
 \title{TITRE 1}
\text{objet=randitem(carré,rectangle,losange,parallélogramme,triangle)}
 \integer{rep=randint(2..13)}
 \integer{coef=\rep^2}
 \text{enonce=Par quel coefficient faut-il multiplier les longueurs des côtés d'un \objet pour obtenir un \objet dont l'aire est \coef fois plus grande}
 \text{reponse=Il faut les multiplier par}
#endif

#if defined TARGET_coefficientA2
 \title{TITRE 2}
\text{objet=randitem(carré,rectangle,losange,parallélogramme,triangle)}
 \integer{rep=randitem(2,4,5,8,10)}
 \integer{coef=\rep^2}
 \text{rep=1/\rep}
 \text{enonce=Par quel coefficient faut-il multiplier les longueurs des côtés d'un \objet pour obtenir un \objet dont l'aire est \coef fois plus petite}
 \text{reponse=Il faut les multiplier par}
#endif

#if defined TARGET_coefficientA3
 \title{TITRE 3}
 \integer{rep=randint(2..15)}
 \real{aire1=randint(1000..10000)/10}
 \real{aire2=\rep^2*\aire1}
 \text{lettre=randitem(S,T,C,D,M)}
 \text{enonce=\(\mathcal{S}) est une surface dont l'aire mesure \(\aire1 cm^2). \(\mathcal{S}') est une deuxième surface dont l'aire mesure \(\aire2 cm^2). Sachant que \(\mathcal{S}') est obtenue par agrandissement de \(\mathcal{S}), quel est le coefficient d'agrandissement}
 \text{reponse=Le coefficient est}
#endif

#if defined TARGET_coefficientA4
 \title{TITRE 4}
 \integer{rep=randint(2..15)}
 \real{aire1=randint(1000..10000)/10}
 \real{aire2=\rep^2*\aire1}
 \text{rep=1/\rep}
 \text{lettre=randitem(S,T,C,D,M)}
 \text{enonce=\(\mathcal{S}) est une surface dont l'aire mesure \(\aire2 cm^2). \(\mathcal{S}') est une deuxième surface dont l'aire mesure \(\aire1 cm^2). Sachant que \(\mathcal{S}') est obtenue par réduction de \(\mathcal{S}), quel est le coefficient de réduction}
 \text{reponse=Le coefficient est}
#endif

#if defined TARGET_coefficientA5
 \title{TITRE 5}
 \text{list=wims(values v for v=2 to 15)}
 \text{list=shuffle(\list)}
 \integer{coef1=item(1,\list)}
 \integer{coef2=item(2,\list)}
 \integer{rep=\coef1*\coef2}
 \text{let=randint(S,T,C,D,M,V)}
 \text{enonce=\(\mathcal{S}_1) est une surface.<br>On obtient une deuxième surface \(\mathcal{S}_2) en effectuant un agrandissement de coefficient \(\coef1) de \(\mathcal{S}_1).<br> Enfin, on obtient une troisième surface \(\mathcal{S}_3) en effectuant un agrandissement de coefficient \(\coef2) de \(\mathcal{S}_2).<br> Quel est le coefficient de l'agrandissement qui permet de passer directement de \(\mathcal{S}_1) à \(\mathcal{S}_3)}
 \text{reponse=Le coefficient est}
#endif


#if defined TARGET_coefficientV1
 \title{Volume et coefficient 1}
 \matrix{objet=cube,un
  parallélépipède,un
  cylindre,un
  sphère,une
  pyramide,une}
 \text{objet=randrow(\objet)}
 \text{art=item(2,\objet)}
 \text{objet=item(1,\objet)}
 \integer{rep=randint(2..7)}
 \integer{coef=\rep^3}
 \text{enonce=Par quel coefficient faut-il multiplier les longueurs  d'\art \objet pour obtenir \art \objet dont le volume est \coef fois plus grand}
 \text{reponse=Il faut les multiplier par}
#endif

#if defined TARGET_coefficientV2
 \title{Volume et coefficient 2}
 \matrix{objet=cube,un
  parallélépipède,un
  cylindre,un
  boule,une
  pyramide,une}
 \text{objet=randrow(\objet)}
 \text{art=item(2,\objet)}
 \text{objet=item(1,\objet)}
 \integer{rep=randint(2,4,5,8,10)}
 \integer{coef=\rep^3}
 \text{rep=1/\rep}
 \text{enonce=Par quel coefficient faut-il multiplier les longueurs  d'\art \objet pour obtenir \art \objet dont le volume est \coef fois plus petit}
 \text{reponse=Il faut les multiplier par}
#endif

#if defined TARGET_coefficientV3
 \title{Volume et coefficient 3}
 \integer{rep=randint(2..15)}
 \real{aire1=randint(1000..10000)/10}
 \real{aire2=\rep^3*\aire1}
 \text{lettre=randitem(S,T,C,D,M)}
 \text{enonce=\(\mathcal{S}) est un solide dont le volume mesure \(\aire1 cm^3). \(\mathcal{S}') est un deuxième solide dont le volume mesure \(\aire2 cm^3). Sachant que \(\mathcal{S}') est obtenu par agrandissement de \(\mathcal{S}), quel est le coefficient d'agrandissement}
 \text{reponse=Le coefficient est}
#endif

#if defined TARGET_coefficientV4
 \title{Volume et coefficient 4}
 \integer{rep=randint(2..15)}
 \real{aire1=randint(1000..10000)/10}
 \real{aire2=\rep^3*\aire1}
 \text{lettre=randitem(S,T,C,D,M)}
 \text{rep=1/\rep}
 \text{enonce=\(\mathcal{S}) est un solide dont le volume mesure \(\aire2 cm^3). \(\mathcal{S}') est un deuxième solide dont le volume mesure \(\aire1 cm^3). Sachant que \(\mathcal{S}') est obtenu par réduction de \(\mathcal{S}), quel est le coefficient de réduction}
 \text{reponse=Le coefficient est}
#endif

#if defined TARGET_coefficientV5
 \title{Volume et coefficient 5}
 \text{list=wims(values v for v=2 to 15)}
 \text{list=shuffle(\list)}
 \integer{coef1=item(1,\list)}
 \integer{coef2=item(2,\list)}
 \integer{rep=\coef1*\coef2}
 \text{let=randint(S,T,C,D,M,V)}
 \text{enonce=\(\mathcal{S}_1) est un solide.<br>On obtient un deuxième solide \(\mathcal{S}_2) en effectuant un agrandissement de coefficient \(\coef1) de \(\mathcal{S}_1).<br> Enfin, on obtient un troisième solide \(\mathcal{S}_3) en effectuant un agrandissement de coefficient \(\coef2) de \(\mathcal{S}_2).<br>Quel est le coefficient de l'agrandissement qui permet de passer directement de \(\mathcal{S}_1) à \(\mathcal{S}_3)}
 \text{reponse=Le coefficient est}
#endif

\statement{
\enonce ?
<p>
<strong>Votre réponse :</strong>
</p>
\reponse \embed{r1,10}.
}

\reply{Réponse}{\rep}{type=numexp}
