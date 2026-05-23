\text{name_hkm=h,km,km/h}
#if defined TARGET_arret
\matrix{name_enonce=Le temps de réaction d'un conducteur est de
  Sur route mouillée, les distances de freinage sont augmentées de
  Remplir le tableau (on peut consulter l'aide).
  Les distances seront données avec une décimale par excès.}
\text{name_header=vitesse du véhicule en km/h,
  distance parcourue pendant le temps de réaction,
  distance de freinage sur route sèche en m,
  distance d'arrêt sur route sèche en m,
  distance de freinage sur route mouillée en m,
  distance d'arrêt sur route mouillée en m}
\text{name_seconde=seconde,secondes}
\text{name_help1=Entre le moment où un conducteur voit un obstacle et celui
  où il commence à freiner,
  s'écoule un temps appelé <span class="bold">temps de réaction</span>.
  C'est la durée de transmission de l'influx nerveux entre l'oeil (organe récepteur)
  et la main qui serre le frein ou le pied qui appuie sur la pédale de frein (organe effectueur).}
\text{name_help2=La distance parcourue pendant le temps de réaction est fonction de la vitesse du véhicule.
  Le temps de réaction est plus ou moins long suivant les individus, leur état de fatigue.
  Sa durée moyenne est de 1 à 3 secondes.}
\text{name_help3=Entre le moment où le conducteur actionne le frein et celui où le véhicule s'arrête,
  la distance parcourue est appelée <span class="bold">distance de freinage</span>.
  La distance de freinage dépend du véhicule (état du système de freinage),
  de la vitesse, de l'adhérence du véhicule sur la chaussée
  (chaussée glissante, mouillée, verglacée, sèche).}
\text{name_help4=La <span class="defn">distance d'arrêt</span>
  est la somme de la distance parcourue pendant le temps de réaction
  et de la distance de freinage.}
#endif
#if defined TARGET_impot
\text{name_enonce=Vous êtes, sans enfant,avec, enfants, à charge, vous avez donc droit à,
  part,parts}
\text{name_question=Calculez l'impôt pour un revenu,en,
  en utilisant le graphique de la fonction impôt qui est formé de segments,
  et d'une demi-droite à partir du point,Les coordonnées sont les suivantes}
\text{name_hint=Il faut calculer le coefficient directeur \(coeff\) de la droite}
\text{name_answer=impôt arrondi à 0.01 près}
\text{name_etat=célibataire,marié}
#endif
#if defined TARGET_trajet
\text{name_heuv=Heure,Vitesse}
\text{name_enonce=Anne doit parcourir la distance de, km selon le graphique suivant}
\matrix{name_question1=Lire le diagramme
  Combien de temps s'arrête-t-elle en cours de route
  Combien de temps après son départ fait-elle la,pause
  Quelle distance a-t-elle alors parcourue}
\matrix{name_question2=Elle a parcouru la fin du trajet (après la deuxième pause) à la vitesse moyenne horaire de
  A quelle heure arrive-t-elle, Elle arrive à
  A quelle vitesse moyenne horaire a-t-elle parcouru la fin du trajet (après la deuxième pause)}
\text{name_question3=Elle arrive donc à,
  avec une vitesse moyenne horaire sur le dernier tronçon de,
  Quelle est sa vitesse moyenne horaire sur l'ensemble du parcours}
\text{name_instruction=Arrondir les vitesses à 1 par excès (en km/h).
  Écrire les unités (les temps sont écrits en heures et en minutes
  par exemple 150 min ou 2 h 30 min en laissant un espace entre les heures et les minutes)}
\text{name_answer=Temps de pause ,pause,Nombre de km}
#endif
#if defined TARGET_vitesse
\text{name_enonce=Un motocycliste roule pendant,à la vitesse de,
  et pendant,à la vitesse de}
\text{name_question1=Quelle est sa vitesse moyenne}
\text{name_enonce2=Il roule ensuite pendant, Sa vitesse moyenne totale est de,
  Quelle est sa vitesse moyenne dans la dernière partie&nbsp;}
\text{name_instruction=Les résultats seront donnés avec un chiffre au plus après la virgule et
  en}
\text{name_answer=Vitesse moyenne,
  Vitesse dans la dernière partie}
#endif
#if defined TARGET_vitesse2
\text{name_enonce=Un automobiliste part de son domicile à XXXX \name_hkm[1] 00,
  son compteur indique YYYY \name_hkm[2].
 Il revient à ZZZZ \name_hkm[1] 00, son compteur marque TTTT \name_hkm[2].}
\text{name_question=Quelle distance a-t-il parcourue,
  Pendant combien de temps a-t-il roulé}
\matrix{name_question2=En effet, il a parcouru
  et a roulé pendant
  Quelle a été sa vitesse moyenne horaire}
\text{name_instruction=Consigne : les unités sont demandées.}
\text{name_answer=La distance parcourue est de,
  Il a roulé pendant,
  Sa vitesse moyenne horaire est de}
\text{name_hint1=La distance parcourue est la différence entre ce
  qu'indique son compteur à l'arrivée et ce qu'il indique  au départ.}
\text{name_hint2=Le temps de parcours est la différence entre l'heure
  d'arrivée et l'heure de départ.}
\text{name_hint3=La vitesse moyenne horaire est égale à la distance parcourue
  divisée par le temps pendant lequel il a roulé.}
#endif
#if defined TARGET_vitesse12
\text{liste= oui,non}
\text{name_list=pendant, à une vitesse de,durant}
\text{name_enonce=Monsieur Rapide part de Paris à , et roule d'abord, puis, et enfin}
\text{name_question=Combien de kilomètres a-t-il parcouru (par excès à 0.01 près),
  Il a parcouru XXXX \name_hkm[2],
  Combien de temps son trajet a-t-il duré,
  Son trajet a duré YYYY,
  Quelle est sa vitesse moyenne sur la totalité du parcours,
  Sa vitesse moyenne sur la totalité du parcours est,
  Il a rendez-vous à ZZZZ h. Sera-t-il à l'heure}
\text{name_instruction1=Consigne : mettre les unités, par exemple}
\text{name_instruction2=laisser des espaces}
\text{name_hint1=On calcule la distance à partir du temps de parcours
(en heures) et de la vitesse par la relation suivante}
\text{name_hint2=Le fait qu'il soit ou non à l'heure dépend de son heure d'arrivée
  et donc de son temps de trajet}
\text{name_answer=Distance parcourue,Temps de parcours,Vitesse moyenne}
\text{name_feed=Son temps de trajet est de,
  Il arrive donc à,
  ce qui est bien,avant, après,son heure de rendez-vous}
#endif

