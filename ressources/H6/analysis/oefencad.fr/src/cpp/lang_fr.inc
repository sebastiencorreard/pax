\text{name_and=et}
\text{name_hint=Le type d'inégalités est imposé, on ne cherche pas à savoir si les bornes
  sont atteintes.}
#if defined TARGET_carre || defined TARGET_difference || defined TARGET_difference2 || defined TARGET_valabs || defined TARGET_oefencad1
\text{name_bestappr=Trouvez le meilleur encadrement de}
#endif
#if defined TARGET_carre || defined TARGET_valabs
\text{name_enonce=Soit \(x\) un réel vérifiant}
#endif
#if defined TARGET_carre
\text{name_feed1=Votre encadrement n'a pas de sens car}
\text{name_feed2= Votre encadrement n'est pas bon car \(0), par exemple, n'est
  pas compris entre}
\text{name_feed3=Regardez la représentation graphique de la fonction carré.}
#endif
#if defined TARGET_oefencad1
\text{name_of=de}
\text{name_carre=et de la racine carrée de}
\text{name_supinf=est supérieur à,est inférieur à,est supérieure à,est inférieure à}
\text{name_carre2=La racine carrée de}
\text{name_answer=La racine carrée de \(x^2\) est}
#endif
#if defined TARGET_difference || defined TARGET_difference2
\text{name_help=Pour encadrer la différence \(x -y\), commencez par encadrer \(-y\).}
\text{name_feed1=Votre réponse n'a pas de sens car}
\text{name_feed2= Vous avez soustrait les inégalités membre à membre.
  Ce n'est pas la règle pour encadrer une différence.}
\text{name_feed3=Vous avez encadré la somme, et non la différence.}
\text{name_feed4=Votre encadrement est juste, mais n'est pas le meilleur possible.}
#endif
#if defined TARGET_sum || defined TARGET_difference || defined TARGET_encadproduit || defined TARGET_encadproduit2 || defined TARGET_encadproduit3 || defined TARGET_oefencad1 || defined TARGET_oefencad2
\text{name_enonce=Soient \(x\) et \(y\) deux réels vérifiant}
#endif
#if defined TARGET_sum || defined TARGET_encadproduit2 || defined TARGET_encadproduit3 || defined TARGET_difference || defined TARGET_difference2
\text{name_graph=Les valeurs possibles de \(x\) et \(y\) sont figurées ci-dessous
  en <span style="color:red">rouge</span> pour \(x\) et
  <span style="color:green">en vert</span> pour \(y\).}
#endif
#if defined TARGET_sum
\text{name_question=Trouvez le meilleur encadrement de la somme de \(x\) et de \(y\)}
\text{name_feed1=La réponse n'a pas de sens car}
\text{name_feed2=Votre encadrement est juste, mais n'est pas le meilleur possible.}
#endif
#if defined TARGET_valeurabsolue1
\text{name_enonce=L'ensemble des réels \(x\) qui vérifient l'équation, est égal à}
#endif
#if defined TARGET_inequation
\text{name_enonce=Donnez l'ensemble des solutions de l'inéquation}
\text{name_inst=Construire l'ensemble (de gauche à droite) en cliquant sur
  les éléments en dessous.}
\text{name_hint=Dressez un tableau de la valeur des expressions avec valeur absolue selon \(x\).}
#endif
#if defined TARGET_valeurabsolue2
\text{name_enonce=Déterminer les entiers \(a\) et \(r\) tels que
  l'intervalle, soit égal à l'ensemble des réels \(x\) qui vérifient l'équation }
\text{name_hint=On rappelle que \(a\) est le milieu de l'intervalle,
  tandis que \(r\) en est le rayon.}
#endif
#if defined TARGET_valeurabsolue3
\text{name_enonce=Déterminer les entiers \(a\) et \(r\) tels que les réels \(x\)
qui vérifient l'inéquation ,soient les réels appartenant à}
\text{name_hint=Les réels \(x\) tels que \(|x-a| \ge r) sont tels que
  la distance à \(a\) est supérieure ou égale à \(r\).
  Il faut donc commencer par chercher le milieu de l'intervalle}
#endif
#if defined TARGET_oefencad2
\text{name_hint=On demande ici le meilleur encadrement possible. Pensez à faire
  apparaître des carrés.}
\text{name_question=Le meilleur encadrement de,est le suivant }
#endif
#if defined TARGET_encadproduit || defined TARGET_encadproduit2
\text{name_help=Lorsque \(x\) ou \(y\) ne sont pas de signe constant, c'est-à-dire encadrés par
  des nombres de signes différents,
  séparez votre encadrement de \(x\) (ou de \(y\)) en deux autres encadrements
  de façon à ne travailler que sur des inégalités entre nombres de même signe.}
#endif
#if defined TARGET_encadproduit || defined TARGET_encadproduit2 || defined TARGET_encadproduit3
\text{name_feed1=Votre encadrement n'a pas de sens puisqu'on a :}
\text{name_feed2=Faites attention aux signes.}
\text{name_feed3=Votre encadrement est juste mais n'est pas le meilleur possible.}
#endif
#if defined TARGET_valabs
\text{name_feed1=Votre encadrement n'a pas de sens car}
\text{name_feed2=Votre encadrement n'est pas correct :
  par exemple \(0) n'est pas compris entre}
\text{name_feed3=La valeur absolue d'un nombre est toujours positive.}
\text{name_feed4=Quelles sont les variations de la fonction valeur absolue sur
  les nombres positifs}
\text{name_feed5=Quelles sont les variations de la fonction valeur absolue
  sur les nombres négatifs}
\text{name_feed6= Regardez la représentation graphique de la fonction valeur absolue.
  Est-elle monotone sur}
#endif
