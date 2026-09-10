\text{name_answer=Nombre de façons}
#if defined TARGET_tablediner1 || defined TARGET_tablediner2 || defined TARGET_tablediner3 || defined TARGET_tablediner4
\text{name_enonce=couples dînent ensemble. Combien de façons différentes y a-t-il pour ces,
  personnes de s'asseoir autour de la table de manière que}
# if defined TARGET_tablediner1 || defined TARGET_tablediner2 || defined TARGET_tablediner4
\text{name_question=chaque monsieur soit assis à côté de deux dames}
#   if defined TARGET_tablediner2
\text{name_question2= et que tous les maris et femmes soient assis ensemble}
#   endif
#   if defined TARGET_tablediner4
\text{name_question2=et qu'aucun mari soit assis à côté de sa femme}
#   endif
# endif
# if defined TARGET_tablediner3
\text{name_question2=chaque couple soit assis ensemble}
# endif
#endif
#if defined TARGET_Regtriangle
\text{name_enonce=Soit \(P\) un polygône régulier de,côtés}
\text{name_question=Combien de triangles distincts dont les trois sommets
  sont des sommets de \(P\) y a-t-il}
\text{name_answer=Nombre de triangles}
#endif
#if defined TARGET_boiteslettres
\text{name_question=Combien de façons différentes y a-t-il de mettre,
  lettres dans ,boîtes à lettres&nbsp;}
#endif
#if defined TARGET_bonbon
\text{name_method=chaque fille en reçoive au moins un,
	chaque garçon en reçoive au moins un,
	chaque enfant en reçoive au moins un,
	chaque fille en reçoive au moins 1 et chaque garçon en recoive au moins 2,
	chaque fille en reçoive au moins 2 et chaque garçon en recoive au moins 1,
	chaque enfant en reçoive au moins 2,
	chaque fille en reçoive au moins 2 et chaque garçon en recoive au moins 3,
	chaque fille en reçoive au moins 3 et chaque garçon en recoive au moins 2}
\text{name_question=De combien de façons distinctes peut-on distribuer,
  bonbons à, filles et ,garçons de manière que}
#endif
#if defined TARGET_Doublelangue
\text{name_enonce=Parmi, élèves d'une classe, parlent anglais,
  parlent allemand. Tout élève parle soit anglais soit allemand.}
\text{name_question=Maintenant il faut en choisir deux, dont l'un
  parle anglais et l'autre parle allemand. Combien de choix possibles y
  a-t-il&nbsp;}
\text{name_answer=Nombre de choix}
#endif
#if defined TARGET_Hotellampe
\text{name_enonce=Un long couloir dans un hôtel est éclairé par, lampes alignées.}
\text{name_enonce2=Pour économiser de l'énergie, l'hôtel éteint, de ces lampes
  pendant la nuit.}
\text{name_question=Pour avoir un minimum d'éclairage, on ne peut pas éteindre des lampes
  adjacentes, ni les lampes aux extrémités du couloir. Dans ce cas,
  combien de façons différentes y a-t-il d'éteindre}
\text{name_lampe=lampes&nbsp;}
#endif
#if defined TARGET_triangline
\text{name_enonce=Nous avons deux droites parallèles dans le plan. Sur la première
  droite il y a LLLL points, et sur la deuxième, MMMM points.}
\text{name_question=Combien de triangles peut-on former avec ces TTTT points&nbsp;}
\text{name_answer=Nombre de triangles}
#endif
#if defined TARGET_triangle
\text{name_enonce=Nous avons LLLL droites dans le plan, dont XXXX passent par
  l'origine du plan. Il n'y a aucun autre point placé sur plus de deux
  droites, ni aucune droite parallèle à une autre.}
\text{name_question=Combien de triangles peut-on former avec ces,droites&nbsp;}
\text{name_answer=Nombre de triangles}
#endif
#if defined TARGET_subsets
\text{name_enonce=Un ensemble fini \(S\) a,sous-ensembles ,éléments.
  Combien d'éléments \(S\) a-t-il&nbsp;}
#endif
#if defined TARGET_rectangle
\text{name_enonce=Soient XXXX droites dans le plan, dont YYYY horizontales et
  ZZZZ verticales.}
\text{name_question=Combien de rectangles peut-on former avec ces,droites&nbsp;}
#endif
#if defined TARGET_Ordinat1 || defined TARGET_Ordinat2
\text{name_enonce=Une école a une salle informatique avec XXXX ordinateurs numérotés.
  Un groupe de YYYY élèves suit un cours dans cette salle.}
# if defined TARGET_Ordinat1
\text{name_question=Combien de façons différentes y a-t-il d'attribuer chaque élève
  à un ordinateur (distinct)&nbsp;}
# endif
# if defined TARGET_Ordinat2
\text{name_question=Combien de façons différentes y a-t-il
  pour répartir les élèves sur les ordinateurs pour que chaque ordinateur reçoive ZZZZ
  élèves&nbsp;}
# endif
#endif
#if defined TARGET_quadriline
\text{name_enonce=Nous avons 2 droites parallèles dans le plan. Sur la première
  droite il y a XXXX points, et sur la deuxième, YYYY points.}
\text{name_question=Combien de quadrilatères peut-on former avec ces, points&nbsp;?}
\text{name_answer=Nombre de quadrilatères}
#endif
#if defined TARGET_partfix
\matrix{name_question=De combien de façons distinctes peut-on écrire
  où les \(n_i\) sont des entiers supérieurs ou égaux à,rangés dans l'ordre}
\text{name_order=croissant,décroissant}
#endif
#if defined TARGET_n || defined TARGET_nn
\text{name_enonce=Soit \(n\) un entier positif tel que}
\text{name_question=Quelle est la valeur de}
\text{name_answer=Votre réponse}
#endif
#if defined TARGET_busetconducteu
\text{name_enonce=Il y a, bus,conducteurs et,contrôleurs}
\text{name_question=Combien de façons y a-t-il d'attribuer les conducteurs et contrôleurs
  aux bus de manière à ce que chaque bus ait un conducteur et un contrôleur&nbsp;}
#endif
#if defined TARGET_committee
\text{name_question=Dans une classe de XXXX garçons et de YYYY filles,
  combien de possibilités y a-t-il pour composer un comité de classe de
  CCCC élèves, sachant qu'il doit y avoir au moins BBBB et
  GGGG dans le comité&nbsp;}
\text{name_answer=Nombre de possibilités}
\text{name_gb=garcon,fille}
\text{name_gbs=garcons,filles}
#endif
#if defined TARGET_intersection || defined TARGET_intersection2 || defined TARGET_intersection3
\text{name_enonce=Dans le plan, deux droites ont au plus un point d'intersection.}
\text{name_question=Combien de points d'intersection y a-t-il au plus entre,droites}
\text{name_answer=Nombre de points}
# if defined TARGET_intersection2
\text{name_question1=dont,sont,(donc parallèles entre elles)&nbsp;}
\text{name_dir=horizontales,verticales}
# endif
# if defined TARGET_intersection3
\text{name_question1=dont, passent par l'origine du plan&nbsp;}
# endif
#endif
#if defined TARGET_posneg
\text{name_enonce=Soit \(S\) un ensemble contenant, entiers positifs et,
  entiers négatifs. Les valeurs absolues de ces, entiers sont des
  nombres premiers distincts.}
\text{name_question=Quel est le nombre, de deux nombres différents dans \(S\)&nbsp;}
\text{qlist=d'entiers négatifs qui sont des produits,
  d'entiers positifs qui sont des produits,
  de nombres rationnels négatifs qui sont des rapports,
  de nombres rationnels positifs qui sont des rapports}
\text{name_answer=Le nombre}
#endif
#if defined TARGET_party
\text{name_enonce=XXXX couples et YYYY personnes non mariées
  se rencontrent pendant une soirée. Au début de la soirée, chaque
  participant se serre la main avec chaque autre participant une fois,
  sauf qu'il n'y a pas de poignée de main entre mari et femme.}
\text{name_question=Combien de poignées de main ont eu lieu au total&nbsp;}
\text{name_answer=Poignées de main}
#endif
#if defined TARGET_couples
\text{name_question=Combien de possibilités y a-t-il pour former,
  couples à partir de , hommes et , femmes&nbsp;}
#endif
#if defined TARGET_groupement
\text{name_question=De combien de façons distinctes peut-on diviser
  une classe de, élèves en, groupes de , élèves chacun&nbsp;}
#endif
#if defined TARGET_helico
\text{name_enonce=On a,hélicoptères de tourisme, pilotes et, hôtesses de l'air.}
\text{name_question=Combien de façons différentes y a-t-il d'attribuer
  les pilotes et hôtesses de l'air aux hélicoptères de manière que chaque
  hélicoptère ait un pilote et deux hôtesses de l'air&nbsp;}
#endif
#if defined TARGET_mots
\text{name_question=Combien de mots distincts peut-on former avec les TTTT premières
  lettres de l'alphabet, sachant que chaque lettre est utilisée exactement une fois
  dans chaque mot et que les AAAA premiers lettres {BBBB} doivent être groupées dans
  chaque mot&nbsp;}
\text{name_hint=Considérez d'abord les , premières lettres comme un seul élément.}
\text{name_answer=Nombre de mots}
#endif
#if defined TARGET_monom3 || defined TARGET_monom4
\text{name_question=Combien y a-t-il d'entiers de la forme,
  où les exposants,
  sont des entiers non négatifs avec}
\text{name_answer=Nombre d'entiers}
\text{name_hint=Les bases XXXX étant premières entre elles,
  ces entiers sont différents pour tous choix différents de XXXX.
  Il suffit donc d'évaluer le nombre de possibilités d'écriture YYYY}
#endif
