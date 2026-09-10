#if defined TARGET_oefaxesym1 || defined TARGET_oefaxesym2
\text{name_stat=La droite rouge est un axe de symétrie du}
\text{name_choice=oui,non,je ne sais pas}
#endif
#if defined TARGET_oefaxesym3 || defined TARGET_oefaxesym4 || defined TARGET_oefaxesym5
# if defined TARGET_oefaxesym3
\text{name_stat=Cliquer sur le dessin où sont tracés tous les axes de symétrie du}
#endif
# if defined TARGET_oefaxesym4 || defined TARGET_oefaxesym5
\text{name_stat=Le,a,axe(s) de symétrie.}
\text{name_beaucoup=beaucoup}
# endif
\text{name_list=triangle quelconque,triangle rectangle,triangle rectangle et isocèle,
  triangle isocèle,triangle équilatéral,carré,rectangle,losange,cerf volant,quadrilatère quelconque}
#endif

# if defined TARGET_oefbissect1
\matrix{enonc=La bissectrice,d'un angle,est
l'axe,de symétrie,de cet angle.
La bissectrice,d'un angle,est la demi-droite,qui partage
cet angle,en deux angles,de même mesure.
La bissectrice,d'un angle,est une demi-droite,qui partage
en deux parties, superposables.}
\text{name_stat=Placer les mots dans l'ordre pour faire une phrase correcte&nbsp;}
#endif
#if defined TARGET_oefbissect2
\text{name_stat=La demi-droite,est la bissectrice de l'angle}
\text{name_choice=oui,non,je ne sais pas}
#endif
#if defined TARGET_oefbissect3
\text{enonc=Cliquer sur le dessin où est tracée la bissectrice de l'angle}
#endif
#if defined TARGET_oefbissect4
\matrix{enonc=La demi-droite, est la bissectrice de l'angle
  L'angle, mesure}
\text{question=Donner la mesure de l'angle}
#endif
#if defined TARGET_oefbissect5
\matrix{name_stat=Tous les angles représentés ont la même mesure.
  La bissectrice de l'angle,est la demi-droite}
#endif
#if defined TARGET_oefmediat1
\matrix{enonc=La médiatrice,d'un segment,est la droite
  passant par,le milieu du segment,et perpendiculaire,à ce segment.
  Si un point,est sur la médiatrice,d'un segment
  alors il est à égale,distance (équidistant),des extrémités,du segment.
  Si un point,est à égale,distance (équidistant),des extrémités,d'un segment
  alors il est,sur la médiatrice,de ce segment.
  On appelle,médiatrice,d'un segment
  la droite,perpendiculaire,à ce segment,en son milieu.
  La médiatrice,d'un segment,est
  un axe,de symétrie,de ce segment.
  Si un point,appartient,à la médiatrice,d'un segment
  alors il est situé,à égale distance,des extrémités,de ce segment.}
\text{name_stat=Placer les mots dans l'ordre pour faire une phrase correcte}
#endif
#if defined TARGET_oefmediat2
\text{name_stat=La droite (d) est la médiatrice du segment}
\text{name_choice=oui,non,je ne sais pas}
#endif
#if defined TARGET_oefmediat3
\text{enonc=Cliquer sur le dessin avec la médiatrice du segment}
#endif
#if defined TARGET_oefmediat4
\text{reps=Je ne sais pas.,
  La droite (d) est mal tracée.,
  La droite (d) n'est pas parallèle à la droite (AB).,
  La droite (d) n'est pas perpendiculaire à la droite (AB).,
  La droite (d) ne passe pas par le milieu du segment [AB].,
  La droite (d) n'est pas sécante à la droite (AB).}
\text{name_stat=La droite (d) n'est pas la médiatrice du segment [AB]. Pourquoi ?}
#endif
#if defined TARGET_oefmediat5
\text{name_stat=Cliquer sur un point de la médiatrice du segment [AB]
  autre que le milieu du segment [AB].}
#endif
#if defined TARGET_oefcoder1 || defined TARGET_oefcoder2 || defined TARGET_oefcoder3 || defined TARGET_oefcoder4 || defined TARGET_oefcoder5
\text{name_stat=Coder la figure avec les symboles.}
# if defined TARGET_oefcoder1
\matrix{enonc=Le point A est le symétrique du point B par rapport à la droite D1.}
# endif
# if defined TARGET_oefcoder2
\matrix{enonc=Le point F est le symétrique du point B par rapport à la droite D1.
Le point E est le symétrique du point A par rapport à la droite D1.
Le point G est le symétrique du point C par rapport à la droite D1.}
# endif
# if defined TARGET_oefcoder3
\matrix{enonc=Le point D est le symétrique du point B par rapport à la droite (AC).}
# endif
# if defined TARGET_oefcoder4
\matrix{enonc=Le point B est le symétrique du point A par rapport à la droite D1.
Le point E est le symétrique du point C par rapport à la droite (AB).
Le point F est le symétrique du point C par rapport à la droite D2.}
# endif
# if defined TARGET_oefcoder5
\matrix{enonc=Le point B est le symétrique du point A par rapport à la droite D1.
Le point F est le symétrique du point E par rapport à la droite (AC).}
# endif
#endif
#if defined TARGET_oefsymfig1 || defined TARGET_oefsymfig2 || defined TARGET_oefsymfig3 || defined TARGET_oefsymfig4 || defined TARGET_oefsymfig5
\text{name_step=Étape}
\text{name_enonce=Voici les différentes étapes de construction.
  Placer les explications pour chaque étape.}
# if defined TARGET_oefsymfig1
\text{rep=Je lis la consigne : "Tracer le symétrique du segment [AB] par rapport à la droite (d).",
  Je fais glisser l'équerre sur la droite (d) jusqu'au point A.,
  Je trace la perpendiculaire à la droite (d) passant par le point A.,
  Avec le compas&#44; je reporte la longueur entre le point A et le point d'intersection avec la perpendiculaire.,
  Je fais glisser l'équerre sur la droite (d) jusqu'au point B.,
  Je trace la perpendiculaire à la droite (d) passant par le point B.,
  Avec le compas&#44; je reporte la longueur entre le point B et le point d'intersection avec la perpendiculaire.,
  Je nomme le point A'&#44; le symétrique du point A et le point B'&#44; le symétrique du point B.,
  Je trace le segment [A'B']&#44; symétrique du segement [AB] par rapport à la droite (d).}
# endif
# if defined TARGET_oefsymfig2
\text{rep=Je lis la consigne : "Tracer le symétrique du segment [AB] par rapport à la droite (d).",
  Je trace deux arcs de cercle sécants passant par le point A&#44; dont les centres appartiennent à la droite (d).,
  Je trace deux arcs de cercle sécants passant par le point B&#44; dont les centres appartiennent à la droite (d).,
  Je nomme le point A'&#44; le symétrique du point A et le point B'&#44; le symétrique du point B.,
  Je trace le segment [A'B']&#44; symétrique du segment [AB] par rapport à la droite (d).,
  Le segment [A'B'] est le symétrique du segment [AB] par rapport à la droite (d).}
# endif
# if defined TARGET_oefsymfig3
\text{rep=Je lis la consigne : "Tracer le symétrique du cercle de centre A par rapport à la droite (d).",
  Je fais glisser l'équerre sur la droite (d) jusqu'au point A.,
  Je trace la perpendiculaire à la droite (d) passant par le point A.,
  Avec le compas&#44; je reporte la longueur entre le point A et le point d'intersection avec la perpendiculaire.,
  J'obtiens un point d'intersection qui est le symétrique du centre.,
  Je nomme le point A'&#44; le symétrique du point A par rapport à la droite (d).,
  Je trace un cercle de centre A' et de même rayon que le cercle de centre A.,
  Le cercle de centre A' est le symétrique du cercle de centre A par rapport à la droite (d).}
# endif
# if defined TARGET_oefsymfig4
\text{rep=Je lis la consigne : "Tracer le symétrique du cercle de centre A par rapport à la droite (d).",
  Je trace un premier arc de cercle passant par le point A&#44; dont le centre appartient à la droite (d).,
  Je trace un deuxième arc de cercle sécant au premier&#44; passant par le point A&#44; dont le centre appartient à la droite (d).,
  J'obtiens un point d'intersection que je nomme A' et qui est le symétrique du centre A par rapport à la droite (d).,
  Je trace un cercle de centre A' et de même rayon que le cercle de centre A.,
  Le cercle de centre A' est le symétrique du cercle de centre A par rapport à la droite (d).}
# endif
# if defined TARGET_oefsymfig5
\text{rep=Je lis la consigne : "Tracer le symétrique de la droite (d2) par rapport à la droite (d1).",
  Je choisis un premier point sur le droite (d2) et je construis son symétrique.,
  Je choisis un deuxième point sur le droite (d2) et je construis son symétrique.,
  J'obtiens deux points qui appartiennent au symétrique de la droite (d2) par rapport à la droite (d1).,
  Je trace le droite (d3) qui passe par les deux points obtenus.,
  La droite (d3) est le symétrique de la droite (d2) par rapport à la droite (d1).}
# endif
#endif
#if defined TARGET_oefsyminst1 || defined TARGET_oefsyminst2 || defined TARGET_oefsyminst3 || defined TARGET_oefsyminst4 || defined TARGET_oefsyminst5
\text{enonc1=Un élève a construit le symétrique d'une figure
  par rapport à la droite (d).}
\text{l1=Oui,Non,Je ne sais pas}
\text{l2=L'équerre a été mal utilisée car les perpendiculaires ne sont pas respectées.,
  Le compas a été mal utilisé car les reports de longueurs ne sont pas corrects.,
  L'élève ne connaît pas les propriétés de la symétrie qui conserve la longueur des segments et la mesure des angles.,
  Non il n'y a pas d'erreur.}
\matrix{name_construction=La construction de l'élève est correcte&nbsp;
  La construction n'est pas correcte car&nbsp;,choisir la (ou les) erreur(s)}
#endif

#if defined TARGET_oefsymconst1
\text{enonc0=Avec l'équerre et la règle graduée&nbsp;}
\text{enonc1= Pour tracer le point C', symétrique du point C par rapport à la droite (AB),
 j'utilise l'équerre pour tracer une droite }
\text{enonc2= à la droite }
\text{enonc3= et passant par le point}
\text{enonc4= Cette droite coupe la droite (AB) au point M.
 Avec la règle graduée, je mesure la longueur du segment }
\text{enonc5= et je reporte cette longueur pour que le point M soit le milieu du segment }
\text{name_mot=perpendiculaire,parallèle,sécante}
#endif
#if defined TARGET_oefsymconst2
\text{enonc0=Avec l'équerre et la règle graduée&nbsp;}
\text{enonc1=
Pour tracer le point C', symétrique du point C par rapport à la droite (AB),
 j'utilise }
\text{enonc2= pour tracer une droite }
\text{enonc3= à la droite (AB) et passant par le point C. Cette droite coupe la droite (AB) au point M.
 Avec}
\text{enonc4= , je mesure }
\text{enonc5= du segment [MC] et je reporte cette longueur pour que le point M soit }
\text{enonc6=du segment [CC']}
#endif
#if defined TARGET_oefsymconst2 || defined TARGET_oefsymconst3
\text{name_mot1=l'équerre,le compas,la règle graduée}
\text{name_mot2=perpendiculaire,parallèle,sécante}
\text{name_mot3=l'équerre,le compas,la règle graduée,le crayon}
\text{name_mot4=la longueur,le rayon,l'angle}
\text{name_mot5=le milieu,l'intersection,l'axe}
#endif
#if defined TARGET_oefsymconst3
\text{enonc0=Avec l'équerre et le compas&nbsp;}
\text{enonc1=
 Pour tracer le point C', symétrique du point C par rapport à la droite (AB),
 j'utilise l'équerre pour tracer une droite }
\text{enonc2= à la droite }
\text{enonc3= et passant par le point}
\text{enonc4=. Cette droite coupe la droite (AB) au point M.
 Avec le compas, je trace un cercle qui a pour centre le point }
\text{enonc5= et qui passe par le point }
\text{enonc6=. Ce cercle coupe la droite (CM) au point C et au point C'}
\text{name_mot=perpendiculaire,parallèle,sécante}
#endif
#if defined TARGET_oefsymconst4
\text{enonc0=Avec l'équerre et le compas&nbsp;}
\text{enonc1=
 Pour tracer le point C', symétrique du point C par rapport à la droite (AB),
 j'utilise }
\text{enonc2= pour tracer une droite }
\text{enonc3= à la droite (AB) et passant par le point C.
 Cette droite coupe la droite (AB) au point M.
 Avec }
\text{enonc4=, je trace}
\text{enonc5= qui a pour }
\text{enonc6=le point M et qui passe par le point C.
Ce cercle coupe la droite (CM) au point C et au point C'}
\text{name_mot1=l'équerre,le compas,la règle graduée,le crayon}
\text{name_mot2=perpendiculaire,parallèle,sécante}
\text{name_mot4=un cercle,une perpendiculaire,une parallèle,un segment}
\text{name_mot5=centre,intersection,axe,mesure}
#endif
#if defined TARGET_oefsymconst5
\text{enonc0=Avec le compas uniquement&nbsp;}
\text{enonc1= Pour tracer le point C', symétrique du point C par rapport à la droite (AB),
 j'utilise le compas pour tracer }
\text{enonc2= de centre A et qui passe par le point }
\text{enonc3=. Ensuite, je trace un deuxième cercle de centre}
\text{enonc4= et qui passe par le point }
\text{enonc5=. Les deux cercles se coupent au point C et au point }
\text{name_mot=un cercle,une perpendiculaire,une parallèle,un segment}
#endif
#if defined TARGET_oefsymconst1 || defined TARGET_oefsymconst2 || defined TARGET_oefsymconst3 || defined TARGET_oefsymconst4 || defined TARGET_oefsymconst5
\text{name_youranswer=Votre réponse}
#endif
