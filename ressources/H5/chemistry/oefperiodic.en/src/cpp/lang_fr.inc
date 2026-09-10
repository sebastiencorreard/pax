#if defined TARGET_click1
\text{namelist=le numéro atomique, le symbole, le nom, la masse atomique en \(u\)}
\text{name_instruction=Dans le tableau périodique des éléments qui n'est pas rempli,
  cliquez sur la case pour l'élément dont }
\text{name_is=est}
\text{name_answer=La position}
\text{name_feed=Vous avez cliqué sur la case,au lieu de}
#endif
#if defined TARGET_blackbox|| defined TARGET_blackbox2
\text{namelist=le numéro atomique, le symbole, le nom, la masse atomique en \(u\)}
\text{quel=Quel,Quel,Quel,Quelle}
\text{name_instruction=Dans le tableau périodique des éléments ci-dessous,
  une case est noircie.}
\text{name_is=est}
\text{name_instruction2=de l'élément dans cette case&nbsp;}
\text{name_answer=Le numéro atomique,Le symbole est,Le nom de l'élément est,La masse atomique en \(u\)}
#endif
#if defined TARGET_corr3|| defined TARGET_corr4 || defined TARGET_corr5 || defined TARGET_corr6 || defined TARGET_corr7
\text{namelist=numéros atomiques,symboles,noms,masses atomiques en \(u\)}
\text{name_instruction=Établissez la correspondance correcte entre les,
  et les,des atomes suivants.}
\text{name_answer=La correspondance}
#endif
#if defined TARGET_fill3 || defined TARGET_fill4 || defined TARGET_fill5 || defined TARGET_fill6 || defined TARGET_fill8 || defined TARGET_fill10 || defined TARGET_fill14 || defined TARGET_fill20 || defined TARGET_fill33 || defined TARGET_fill54 || defined TARGET_fill62 || defined TARGET_fill103 || defined TARGET_fill108
\text{name_instruction=Placer les symboles donnés dans le tableau suivant.}
\text{name_case=Case}
#endif
#if defined TARGET_metals4 || defined TARGET_metals6 || defined TARGET_metals8 || defined TARGET_metals10
\text{name_instruction=Classifiez les éléments ci-dessous en métaux et non-métaux.}
\text{name_metal=Métaux,Non-métaux}
\text{name_ismetal=est un métal,est un non-métal,est ni métal ni non-métal}
#endif
#if defined TARGET_one || defined TARGET_prec || defined TARGET_next
\text{name_connector=précédant immédiatement celui,suivant immédiatement celui}
\text{namelist=le numéro atomique, le symbole, le nom, la masse atomique en \(u\)}
\text{quel=Quel,Quel,Quel,Quelle}
\text{name_is= est}
\text{name_instruction2=de l'élément, dont}
\text{name_answer=Le numéro atomique est,Le symbole est,Le nom de l'élément est,La masse atomique en \(u\) est}
#endif
#if defined TARGET_order3 || defined TARGET_order4 || defined TARGET_order5 || defined TARGET_order6
\text{namelist=numéros atomiques,symboles,noms,masses atomiques en \(u\)}
\text{name_instruction=Rangez les atomes suivants dans l'ordre croissant des numéros atomiques, en les tirant
  dans les cases vides.}
\text{name_answer=Élément}
#endif
