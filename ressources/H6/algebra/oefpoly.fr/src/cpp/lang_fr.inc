#if defined TARGET_mindeggcd2 || defined TARGET_rootcomp || defined TARGET_rerootdeg2 || defined TARGET_rootcnt
\text{comma=&#44;}
#endif

#if defined TARGET_relrtdeg2
\text{name_statement1=Soient \(r_1), \(r_2) les deux racines du polynôme}
\text{name_statement2=où \(a) est un coefficient réel. Quelle est la valeur de}
\text{name_hint1=Nous avons}
\text{name_hint2=Maintenant utilisez la relation entre les racines et les coefficients du polynôme}
#endif

#if defined TARGET_relrtdeg3
\text{name_statement1=Soient \(r_1\), \(r_2\), \(r_3\) les trois racines du polynôme}
\text{name_statement2=où \(a) est un coefficient réel non nul. Quelle est la valeur de}
#endif

#if defined TARGET_relrtdeg2 || defined TARGET_relrtdeg3
\text{name_instruction=Cette valeur est une fonction de}
#endif

#if defined TARGET_mindeggcd2 || defined TARGET_deggcd || defined TARGET_mindeggcdn
note for translators: in the following keep commas
\text{name_statement=Soit,un polynôme de degré,et à coefficients,ayant,racines réelles et,racines complexes différentes (non comptées avec multiplicités),Soit}
#endif

#if defined TARGET_mindeggcd2 || defined TARGET_deggcd || defined TARGET_mindeggcdn || defined TARGET_rootcnt || defined TARGET_givderiv
\text{name_gcd=pgcd}
#endif

#if defined TARGET_deggcd
\text{name_derivative=la dérivée de}
\text{name_question=Quel est le degré de}
\text{name_answer=Degré du}
\text{name_hint=Les racines du pgcd(\(P(x),P'(x))) sont exactement
les racines multiples de \(P).}
#endif

#if defined TARGET_mindeggcd2
\text{name_derivative=la dérivée seconde de}
\text{name_question=Quel est le minimum du degré de}
\text{name_answer=Minimum de}
\text{name_hint=Les racines multiples de \(P\) avec multiplicité \( >2 \) sont parmi les racines de \(pgcd(P(x),P''(x))\).}
#endif

#if defined TARGET_mindeggcdn
note for translators: in the following keep commas
\text{name_derivative=la dérivée d'ordre,de}
\text{name_question=Quel est le minimum du degré de}
\text{name_answer=Minimum de}
#endif

#if defined TARGET_stadouble
\text{name_statement=Quel est le type de racines du polynôme de degré 2 suivant&nbsp;}
\text{name_choice=Type de racines}
\text{name_type_list=une racine réelle et une racine complexe non réelle,une racine double réelle,une racine double non réelle,deux racine simples réelles,deux racines complexes conjuguées}
#endif

#if defined TARGET_parmdeg2
\text{name_type_list=deux racines simples réelles,
  deux racines complexes conjuguées,
  une racine double}
note for translators: in the following keep commas
\text{name_statement=Pour quelles valeurs réelles du paramètre,le polynôme,a}
\text{name_choice=La condition}
\text{name_answer=Où}
#endif

#if defined TARGET_parmdeg2b
note for translators: in the following keep commas
\text{name_statement=Pour quelles valeurs réelles du paramètre,le polynôme,a-t-il une racine égale à,sous condition que}
#endif


#if defined TARGET_givderiv
note for translators: in the following keep commas
\text{name_statement=Trouver le polynôme,tel que&nbsp;,où,est le polynôme dérivé de,le degré de,est le plus petit possible}
note for translators: in the following keep commas
\text{name_instruction=Vous pouvez entrer le polynôme sous forme développée ou factorisée,Tapez,pour}
\text{name_andsoon=etc}
#endif

#if defined TARGET_diffeqn
note for translators: in the following keep commas
\text{name_statement=Trouver le polynôme,tel que,et que}
note for translators: in the following keep commas
\text{name_instruction=Tapez,pour}
\text{name_andsoon=etc}
#endif

#if defined TARGET_givrtdeg3
note for translators: in the following keep commas
\text{name_statement=Déterminez le polynôme,sachant que,sont réels et que,en est une racine}
\text{name_answer=La racine réelle}
#endif

#if defined TARGET_rootcomp
\text{name_item_list=est une racine de,est une racine de,est aussi une racine de}
note for translators: in the following keep commas
\text{name_statement=Soient,un polynôme,un autre polynôme,Considérons les polynômes composés,Complétez&nbsp;}
note for translators: in the following keep commas
\text{name_question=Si,est une racine de,alors}
\text{name_answer=Le nombre à compléter}
#endif


#if defined TARGET_rootmultsum || defined TARGET_rootcnt
\text{name_of=de}
#endif

#if defined TARGET_rootmultsum || defined TARGET_degsum
\text{name_statement1=Soient \(P(X)\) et \(Q(X)\) deux polynômes. Complétez&nbsp;}
#endif

#if defined TARGET_rootmultsum
\text{name_sup=supérieure ou égale à m}
\text{name_inf=inférieure ou égale à m}
\text{name_equ=égale à m}
note for translators: in the following keep commas
\text{name_statement2=Si,est une racine de multiplicité,et une racine de multiplicité,alors,est une racine de multiplicité}
\text{name_choice=La multiplicité est}
\text{name_answer=Où}
#endif

#if defined TARGET_degsum
\text{\name_sup=supérieure ou égale à un nombre d}
\text{\name_inf=inférieure ou égale à un nombre d}
\text{\name_equ=égale à un nombre d}
note for translators: in the following keep commas
\text{name_statement2=Si,alors,est un polynôme de degré}
\text{name_choice=Le degré est}
\text{name_answer=Où}
#endif

#if defined TARGET_tripledeg3 || defined TARGET_tripledeg3b || defined TARGET_rootcomp || defined TARGET_quadpoly || defined TARGET_givrtdeg3 || defined TARGET_degsum
\text{name_and=et}
#endif

#if defined TARGET_tripledeg3 || defined TARGET_tripledeg3b
note for translators: in the following keep commas
\text{name_statement=Pour quelles valeurs réelles des paramètres,le polynôme,a-t-il une racine triple}
\text{name_answer=La racine triple}
\text{name_condition=est une racine triple}
#endif

#if defined TARGET_tripledeg3
\text{name_hint1=Si \(r\) est une racine triple de \(P\), alors}
\text{name_hint2=est donc une racine (réelle) du polynôme}
\text{name_where=ou}
#endif

#if defined TARGET_tripledeg3b
\text{name_instruction=La solution n'est pas forcément unique.}
#endif

#if defined TARGET_trinomefact
\text{name_step=Etape}
\text{name_statement1=Factoriser}
\text{name_statement2=Mettons les termes de \(x\) en un carré complet}
\text{name_statement3=Nous avons}
\text{name_statement4=Donc}
\text{name_statement5=Maintenant on applique la formule}
\text{name_result=Résultat&nbsp;}
\text{name_instruction=Il faut entrer les expressions simplifiées.}
\text{name_answer1=Terme constant du développement du carré}
\text{name_answer2=Terme constant dans le carré}
\text{name_answer3=Terme compensateur}
#endif

#if defined TARGET_quadpoly
\text{name_statement=Calculer les deux racines du polynôme}
\text{name_instruction=Vous pouvez entrer les deux racines \(\r1\) \name_and \(\r2\) dans n'importe quel ordre.}
\text{name_condition1=est une racine}
\text{name_condition2=est l'autre racine}
#endif

#if defined TARGET_rootdeg2
\text{name_statement1=Trouver les deux racines}
\text{name_statement2=du polynôme}
\text{name_instruction=Les racines sont réelles, et l'ordre des racines est sans importance.}
\text{name_condition1=est une racine}
\text{name_condition2=Il n'y a pas d'autres racines}
#endif

#if defined TARGET_rootcnt
note for translators: in the following keep commas
\text{name_statement=Soit,un polynôme de degré,et à coefficients,et soit,le polynôme dérivé de,On sait que,est un polynôme de degré}
note for translators: in the following keep commas
\text{name_question=Quel est le nombre de racines,distinctes,}
\text{name_note=racines réelles et complexes confondues}
\text{name_answer=Nombre de racines distinctes}
\text{name_hint=Les racines de \(pgcd(P(x),P'(x))\) sont exactement
les racines multiples de \(P(x)).}
#endif

#if defined TARGET_rerootdeg2
note for translators: in the following keep commas
\text{name_statement=Soit,un polynôme à coefficients réels,ayant deux racines complexes conjuguées,Quelle est la partie réelle d'une racine}
#endif

#if defined TARGET_degmult || defined TARGET_mindeggcd2 || defined TARGET_deggcd || defined TARGET_mindeggcdn || defined TARGET_rootcnt
\text{name_type_list=réels,complexes}
#endif

#if defined TARGET_degmult
note for translators: in the following keep commas
\text{name_statement=Quel est le degré minimum d'un polynôme,à coefficients,admettant &nbsp;}
\text{name_request1=comme racine de multiplicité}
\text{name_request2=comme  racine de multiplicité}
note for translators: in the following keep commas
\text{name_instruction=Répondez,si vous pensez qu'un tel polynôme n'existe pas}
\text{name_answer=Minimum du degré}
#endif

#if defined TARGET_findmult3 || defined TARGET_findmult4 || defined TARGET_findmult5 || defined TARGET_findmult6
\text{name_statement=Le polynôme suivant a une racine multiple. Trouver cette racine}
\text{name_answer=La racine multiple}
#endif

#if defined TARGET_multiplicity3 || defined TARGET_multiplicity4 || defined TARGET_multiplicity5 || defined TARGET_multiplicity6
note for translators: in the following keep commas
\text{name_statement=Le nombre,est une racine du polynôme suivant}
\text{name_statement2=Calculer sa multiplicité}
\text{name_answer=La multiplicité de}
#endif

#if defined TARGET_multparm3 || defined TARGET_multparm4
\text{name_statement=Trouver une valeur de \(m) pour que le polynôme suivant ait une racine multiple, et trouver cette racine multiple.}
\text{name_warning=ATTENTION}
\text{name_instruction=Cet exercice n'accepte pas les réponses approximatives ! Il y a toujours une solution entière. Trouvez-la.}
\text{name_answer=La racine multiple}
\text{name_condition=est une racine multiple de}
\text{name_feedback1=n'est même pas une racine de}
\text{name_feedback2=Calcul égaré.}
\text{name_feedback3=est en effet une racine de}
\text{name_feedback4=Pour que ce soit une racine multiple, il faut que}
\text{name_feedback5=soit aussi une racine de la dérivée de}
\text{name_feedback6=ce qui n'est malheureusement pas le cas. Vérifiez votre calcul.}
#endif
