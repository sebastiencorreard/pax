#if defined TARGET_equ_dr5 || defined TARGET_equ_dr4 || defined TARGET_equ_dr_mcd || defined TARGET_parallele || defined TARGET_equ_dr1 || defined TARGET_syst1 || defined TARGET_syst2 || defined TARGET_pllsec2 || defined TARGET_secnico || defined TARGET_ordonnee || defined TARGET_sys3_app || defined TARGET_abscisse
\text{name_and=et}
#endif
#if defined TARGET_equ_dr5 || defined TARGET_equ_dr_mcd || defined TARGET_eqgeqr || defined TARGET_equ_dr1 || defined TARGET_equ_dr0 || defined TARGET_equ_dr2 || defined TARGET_equ_dr4 || defined TARGET_ordonnee || defined TARGET_abscisse
\text{name_is=est}
#endif
#if defined TARGET_equ_dr_mcd
\text{name_or=ou}
#endif
#if defined TARGET_pllsec2 || defined TARGET_equ_dr2 || defined TARGET_equ_dr5 || defined TARGET_equ_dr4 || defined TARGET_equ_dr0
\text{name_solution=L'équation réduite de la droite}
#endif
#if defined TARGET_equ_dr0 || defined TARGET_equ_dr2 || defined TARGET_equ_dr5 || defined TARGET_equ_dr4
\text{name_answer1=Coefficient directeur}
\text{name_answer2=Ordonnée à l'origine}
#endif

#if defined TARGET_pllsec2
\text{name_options_list=parallèles,sécantes}
\text{name_yesno=oui,non}
\text{name_statement1=Oui, les droites sont parallèles. Sont-elles confondues}
\text{name_statement2=Oui, les droites sont sécantes. Déterminer les coordonnées \( (x ; y) \) de leur point d'intersection.}
# note for translators: semicolons are line separators
\matrix{name_statement=Dans le plan muni d'un repère, on considère les droites ; d'équation ; Les droites sont }
\text{name_answer=Confondues}
#endif

#if defined TARGET_equ_dr0
# note for translators: semicolons are line separators
\matrix{name_statement=Dans le plan muni d'un repère, on considère la droite ; d'équation ; Donner le coefficient directeur ainsi que l'ordonnée à l'origine de la droite}
#endif

#if defined TARGET_secnico
# note for translators: commas are separators
\text{name_statement=Le plan est rapporté à un repère orthonormal,Soient,les droites d'équations respectives,On admet que les droites,sont sécantes en un point,Déterminer les coordonnées du point}
\text{name_answer1=Abscisse de}
\text{name_answer2=Ordonnée de}
#endif

#if defined TARGET_equ_dr2
\text{name_statement1=Dans le plan muni d'un repère, on considère la droite \(\math_droite\) représentée ci-contre.
Déterminer graphiquement l'ordonnée à l'origine et le coefficient directeur de cette droite.}
#endif

#if defined TARGET_equ_dr4
\text{name_statement1=Dans le plan muni d'un repère, on considère la droite \(\math_droite\) passant par les points }
#endif

#if defined TARGET_equ_dr2 || defined TARGET_equ_dr4
\text{name_statement2=L'équation réduite de}
#endif


#if defined TARGET_ordonnee
# note for translators: commas are separators
\text{name_statement=Le plan est rapporté à un repère orthonormal,Soient,la droite d'équation,le point d'abscisse}
\text{name_question=Déterminer l'ordonnée \( y_A \) du point \( A \) dans le repère.}
\text{name_answer=L'ordonnée de}
#endif

#if defined TARGET_abscisse
# note for translators: commas are separators
\text{name_statement=Le plan est rapporté à un repère orthonormal,Soient,la droite d'équation,le point d'ordonnée}
\text{name_question=Déterminer l'abscisse \( x_A \) du point \( A \) dans le repère.}
\text{name_answer=L'abscisse de}
#endif

#if defined TARGET_para2
# note for translators: commas are separators
\text{name_statement=Le plan est rapporté à un repère orthonormal,Soit,la droite d'équation,Déterminer l'équation réduite de la droite,parallèle à la droite,passant par le point}
\text{name_answer=Equation de la droite}
\text{name_feedback1=L'équation de la droite est}
\text{name_feedback2=L'équation donnée n'est pas l'équation d'une parallèle à}
#endif

#if defined TARGET_sys3
\text{name_statement=Résoudre le système}
\text{name_instruction=<b>Indication:</b> Les solutions sont entières.}
#endif

#if defined TARGET_sys3_app
\text{name_option_list=malabars,carambars,fraiser}
\text{name_anoption_list=Un malabar,Un carambar,Une fraise}
\text{name_statement=Trois élèves vont acheter des bonbons}
# note for translators: commas are separators
\text{name_question=achète,et paye,euros,Déterminer le prix de chaque type de bonbons,coûte}
#endif

#if defined TARGET_equdroitevoc
\text{name_statement1=Le plan est rapporté à un repère orthonormal}
\text{name_statement2=Soit \((\math_droite) \) la droite d'équation&nbsp;}
\text{name_statement3=Déterminer le coefficient directeur de la droite \( (\math_droite)\) et son ordonnée à l'origine}
\text{name_answer1=Coefficient directeur de}
\text{name_answer2=Ordonnée à l'origine  de}
\text{name_feedback=Attention, vous confondez le coefficient directeur et l'ordonnée à l'origine&nbsp;}
#endif

#if defined TARGET_equ_dr1
# note for translators: semicolons are line separators
\matrix{name_statement=Dans le plan muni d'un repère, on considère la droite ; passant par le point ; de coordonnées ; et dirigée par le vecteur ; de coordonnées ; Déterminer une équation de la droite ; Une équation de ; son équation réduite est&nbsp;}
\text{name_answer1=Le petit}
\text{name_answer2=Le coefficient directeur de}
\text{name_answer3=L'ordonnée à l'origine de}
\text{name_condition1=est un vecteur directeur de cette droite}
# note for translators: commas are separators
\text{name_condition2=Le point,est situé sur cette droite}
# note for translators: commas are separators
\text{name_solution=Une équation de la droite,son équation réduite est}
#endif

#if defined TARGET_eqgeqr
\text{name_question_list=le coefficient directeur,l'ordonnée à l'origine}
\text{name_Question_list=Le coefficient directeur,L'ordonnée à l'origine}
# note for translators: semicolons are line separators
\matrix{name_statement=On considère la droite ; d'équation ; Déterminer ; de la droite }
\text{name_reponse=Réponse}
#endif

#if defined TARGET_equa_red
\text{name_statement=Mettez en relation les équations de droites se correspondant}
#endif

#if defined TARGET_parallele
# note for translators: commas are separators
\text{name_statement=Déterminer,pour que les droites,d'équations respectives,soient parallèles,Une valeur de}
#endif

#if defined TARGET_syst1 || defined TARGET_syst2
\text{name_statement=Résoudre le système suivant&nbsp;}
\text{name_answer=Valeur de}
\text{name_solution=Les solutions sont}
#endif

#if defined TARGET_equ_dr5
\text{name_options_list=abscisses,ordonnées}
# note for translators: semicolons are line separators
\matrix{name_statement=Dans le plan muni d'un repère, on considère la droite ; d'équation ; la droite ; parallèle à ; passant par}
# note for translators: semicolons are line separators
\matrix{name_question=Déterminer les coordonnées du point d'intersection ; de la droite ; avec l'axe des}
#endif

#if defined TARGET_pointdroite
# note for translators: semicolons are line separators
\matrix{name_statement=Dans le plan rapporté à un repère, on considère la droite \(\math_droite\) d'équation ; Pour quelle valeur de \(b\), le point \(M\) de coordonnées ; appartient-il à \(\math_droite\)&nbsp;}
#endif

#if defined TARGET_equ_dr_mcd || defined TARGET_pllsec2
\text{name_difflevel=Cet exercice comporte deux étapes.}
#endif
#if defined TARGET_equ_dr_mcd
\text{name_options_list=parallèle à l'axe des ordonnées , parallèle à l'axe des abscisses, non parallèle aux axes de coordonnées}
# note for translators: semicolons are line separators
\matrix{name_statement=Dans le plan rapporté à un repère, on considère les points ; La droite ; est-elle ; Oui, la droite ; Donner son équation ; }
text{name_instruction=L'équation réduite de la droite.}
\text{name_instruction=Cliquer sur la bonne réponse.}
#endif

#if defined TARGET_pointsentiers
# note for translators: semicolons are line separators
\matrix{name_statement=Déterminer un point \(M\) situé sur la droite \(\math_droite\) d'équation ; dont les coordonnées sont <b>entières</b> ; Le point ; convient }
\text{name_condition1=Le point \(M\) est sur \(\math_droite\)}
\text{name_condition2=L'abscisse de \(M\) est entière}
\text{name_condition3=L'ordonnée de \(M\) est entière}
#endif

