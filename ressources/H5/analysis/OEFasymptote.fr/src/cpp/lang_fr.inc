#if defined TARGET_posasympt || defined TARGET_chxasympt1 || defined TARGET_assocfct || defined TARGET_assocfct2 || defined TARGET_assocfct3
\text{name_textsol=On fait apparaître l'expression de l'asymptote
  dans chacune des expressions algébriques&nbsp;}
#endif
#if defined TARGET_extremum1 || defined TARGET_extremum2
\text{lstsigne=positif ou nul, strictement positif, négatif ou nul,
  strictement négatif}
\text{lstextr=maximum,majorant,minimum,minorant}
\text{name_enonce=On considère la fonction \(f\) définie sur \(\,\RR\) par &nbsp;,
  On veut démontrer que, est ou n'est pas un extremum pour}
\text{name_question=Calculer, et écrire le résultat sous la forme d'une fraction }
\text{name_question2=Quel est le signe du numérateur&nbsp;,
  Quel est le signe du dénominateur&nbsp;,
  En déduire le signe de,
  On peut donc conclure que, est un , de}
\text{name_answer=numérateur,dénominateur,signe du numérateur,signe du dénominateur,
  signe de,nature de l'extremum}
\text{name_feed=Donc, est un , de}
\text{name_suitesol=atteint en,jamais atteint}
#endif
#if defined TARGET_assocfct || defined TARGET_assocfct2 || defined TARGET_assocfct3
\text{name_question=Associer à chacune des fonctions ci-dessous son graphe
  dans le plan muni d'un repère orthonormé \((O,i,j)\).}
\text{name_answer=Correspondance graphe/fonction}
#endif
#if defined TARGET_calcullim
\text{as1=Cf possède une asymptote horizontale}
\text{as2=Cf possède une asymptote verticale}
\text{as3=cette limite ne correspond pas à une asymptote}
\text{name_inst=On écrira, pour}
\text{name_answer=limite}
\text{name_question=Déterminer la limite de la fonction \(f\) définie par,
  lorsque \(x\) tend vers}
\text{name_question2= On note \(C_f\) la représentation graphique de \(f\).
  On a vu que, De cette égalité, on peut déduire que}
\text{name_points=par valeurs inférieures,par valeurs supérieures}
\text{name_posneg=positif,négatif}
\text{name_textsol=La limite en XXXX s'obtient par le rapport des termes de plus haut degré.
  Comme le numérateur est de degré YYYY au dénominateur, cette limite est ZZZZ.}
\text{name_textsola=De plus le numérateur tend vers XXXX et le dénominateur vers UUUU,
  Donc la limite est}
\text{name_textsolb=La limite en XXXX s'obtient par le rapport des termes de plus haut degré,
  soit le rapport}
\text{name_textsolc=Le dénominateur et le numérateur s'annulent en XXXX.<br>
  Pour calculer la limite, il faut d'abord simplifier la fraction. On obtient}
\text{name_textsold=Le dénominateur s'annule en XXXX alors que le numérateur ne s'annule pas.
  La limite est donc infinie.<br>
  Reste à déterminer le signe. Le numérateur est YYYY et
  le dénominateur est ZZZZ en UUUU.<br> Donc la limite est }
#endif
#if defined TARGET_calcullim || defined TARGET_limfrac
\text{non=non}
\text{name_inst=On écrira, pour,s'il n'y a pas de limite}
#endif
#if defined TARGET_limfrac || defined TARGET_calcullim
\text{name_supinf=supérieur,inférieur}
\text{name_infzero=infinie, nulle}
#endif
#if defined TARGET_limfrac
\text{name_posneg=positif,négatif}
\text{name_posneg2=positive,négative}
\text{inf=inf}
\text{name_answer=Votre réponse,La limite est,La réponse est donc }
\text{name_evenodd=paire,impaire}
\text{name_at=En}
\text{name_textsol=Pour déterminer la limite en,
  on s'intéresse aux termes de plus haut degré.,
  on s'intéresse aux termes de plus bas degré.,
  Comme on obtient une puissance XXXX YYYY de \(x\),
  la limite est infinie.,
   Comme on obtient une constante,
   la limite est cette constante c'est-à-dire ,
   la limite est,
   On s'intéresse alors au signe de ce terme qui est,
   la limite à droite et à gauche de 0 est donc infinie et de sens opposé.}
\text{name_enonce=Soit \(b) un entier,
  Quelle est la limite de,
  lorsque \(x\) tend vers}
#endif
#if defined TARGET_posasympt || defined TARGET_chxasympt1
\text{position=au dessus,en dessous}
#endif
#if defined TARGET_posasympt
\text{name_enonce=On sait que la courbe représentative
  \(\displaystyle{\mathcal{C}}\) d'une fonction \(f\) se situe&nbsp;}
\text{name_pos=de son asymptote en}
\text{name_question=Choisir la fonction pouvant correspondre à}
\text{name_answer=Votre réponse&nbsp;,Choix de la fonction&nbsp;}
\text{name_choix=est au dessus de son asymptote en,
  est en dessous de son asymptote en,
  est en dessous de son asymptote en \(-\infty\) et au dessus en \(+\infty\),
  est au dessus de son asymptote en \(-\infty\) et en dessous en \(+\infty\)}
#endif
#if defined TARGET_eqasympt
\text{name_enonce=On considère une fonction \(f\) définie par&nbsp;}
\text{name_question=Cocher la ou les bonnes réponses&nbsp;,
  La courbe représentative de \(f\) admet&nbsp;}
\text{listrep=des branches paraboliques de direction (Oy),
  une branche parabolique de direction (Ox),
  une asymptote verticale,
  une asymptote horizontale,
  une asymptote oblique}
\text{name_answer=Types de branches infinies}
\text{name_equpos=Équation de l'asymptote verticale,
  Équation de l'asymptote horizontale,
  Équation de l'asymptote oblique}
\text{position=au dessus,au dessous}
\text{name_textsol0=La partie entière de}
\text{name_textsol=\(f\) est une fonction polynôme de degré supérieur ou égal à 2.
  Elle a donc des branches infinies paraboliques de direction (Oy).}
\text{name_textsol1=Le dénominateur de la partie rationnelle de \(f\) ne s'annule pas,
  \(f\) est donc définie sur \(\!\RR\) et ne possède pas d'asymptote verticale.}
\text{name_textsol2=Le dénominateur de la partie rationnelle de \(f\) s'annule pour,
  \(f\) est donc définie sur, et son asymptote verticale a pour équation}
\text{name_textsol3=Le terme en \(\sqrt{x}\) indique que \(f\) possède une branche parabolique de direction (Ox).}
\text{name_textsol4= En décomposant la fonction \(f\) en partie entière et en partie rationnelle,
  on obtient une partie entière constante,
  ce qui indique la présence d'une asymptote horizontale d'équation}
\text{name_textsol5=En décomposant la fonction \(f\) en partie entière et en partie rationnelle,
  on obtient une partie entière affine,
  ce qui indique la présence d'une asymptote oblique d'équation}
#endif
#if defined TARGET_chxasympt1
\text{name_enonce=La courbe bleue représente une fonction
  \(f\), ses asymptotes sont représentées en pointillés rouge.}
\text{name_question=Choisir l'expression algébrique pouvant correspondre à \(f\).}
\text{name_textsol1=Les deux dernières expressions ont des points de discontinuité et ne
  peuvent pas correspondre à \(f\).<br>La courbe se situant XXXX
  de son asymptote}
\text{name_textsol2=La troisième expression est donc la seule à présenter
  une seule asymptote verticale}
\text{name_textsol3=La dernière expression est donc la seule à présenter
  deux asymptotes verticales }
\text{name_goodexpr=la bonne expression pour \(f\) est}
#endif
