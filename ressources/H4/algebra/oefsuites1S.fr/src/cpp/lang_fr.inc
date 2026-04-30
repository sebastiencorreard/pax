#if defined TARGET_raisongeo
\text{name_question=Pour une telle suite,
  donner une raison possible et le terme initial de rang 0 correspondant.}
\text{name_enonce=Soit \( (u_n) \) la suite de terme général,
   Soit \( (u_n) \) une suite géométrique vérifiant}
\text{name_and=et}
\text{name_or=ou}
\text{name_answer=raison&nbsp;,terme initial de rang 0&nbsp;}
\text{name_feed=Il y a deux possibilités, La solution est}
#endif
#if defined TARGET_raisonarit
\text{name_enonce=Soit \( (u_n) \) la suite arithmétique de terme général,
   \( (u_n) \) une suite arithmétique vérifiant}
\text{name_question=Indiquer le terme initial de rang 0 et la raison de cette suite.}
\text{name_answer=Le terme initial  de rang 0 est,La raison est}
#endif
#if defined TARGET_sensvarsuite
\text{variation= croissante, décroissante, non monotone }
\text{signeraison=positive,négative}
\text{compareraison=positive et supérieure à 1, positive et inférieure à 1, négative}
\text{name_enonce=Soit, la suite définie par, La fonction, est,sur}
\text{name_mots=On a,avec,mais}
\text{name_question=Trouver le sens de variation de cette suite., Sens de variation&nbsp;}
\text{name_feed1=C'est une suite arithmétique de raison, La suite est donc}
\text{name_feed2=C'est une suite géométrique de terme initial,
  C'est une suite géométrique de raison}
\text{name_posneg=positif,négatif}
\text{name_feed3=positive et supérieure à,  positive et inférieure à, de raison}
#endif
#if defined TARGET_classersuitesA || defined TARGET_classersuitesB
\text{name_question=Classer les suites suivantes suivant leur nature&nbsp;}
\text{name_type=Suites arithmétiques&nbsp;,Suites géométriques:&nbsp;,
  Suites ni arithmétique ni géométrique}
\text{name_affine=ni arithmétique, ni géométrique}
#endif
#if defined TARGET_aritm1 || defined TARGET_aritm2 || defined TARGET_geom1
\text{name_answer=Votre réponse&nbsp;}
\text{name_yesno=Oui,Non}
\text{name_enonce=Le tableau suivant donne 3 termes d'une suite&nbsp; }
# if defined TARGET_aritm1 || defined TARGET_aritm2
\text{name_question=La suite \( u \) peut-elle être arithmétique&nbsp;}
# endif
# if defined TARGET_geom1
\text{name_question=La suite \( u \) peut-elle être géométrique&nbsp;}
# endif
#endif
