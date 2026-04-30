%%%%% ENONCES EN FRANCAIS %%%%%

\text{exp_vect=vecteurs \(\overrightarrow{\A\B}\) et \(\overrightarrow{\C\D}\)}
\text{inyourcase=Dans votre cas}
%%% STATEMENT %%%
#if !defined TARGET_06memenorme 
\if{\conf2=1}
  {\text{coli=de même direction}}
  {\text{coli=colinéaires}}
#endif

\text{ElemSol=Solution}

\text{explication0=Après avoir consulté l'analyse de votre réponse en bas de page, vous pouvez visualiser} 
#if defined TARGET_01colineaire || defined TARGET_02memesens || defined TARGET_03sensoppose || defined TARGET_06memenorme || defined TARGET_07memenormenoncoli 
# if defined TARGET_01colineaire || defined TARGET_02memesens || defined TARGET_03sensoppose
\text{explication1a=d'autres}
\text{explication1b=quelques}
# endif
# if defined TARGET_06memenorme || defined TARGET_07memenormenoncoli
\text{explication1a=toutes les autres}
\text{explication1b=toutes les}
# endif
\text{explication1c=solutions à l'aide d'un curseur,}
#else
\text{explication1=la solution,}
#endif
\text{explication2=en cliquant sur le bouton <span class="wims_button disabled">\ElemSol</span> situé au-dessus de l'applet GeoGebra.}


# if defined TARGET_01colineaire
\if{\conf2=1}
  {\text{enonce1bis= \coli}}
  {\text{enonce1bis= \coli et que \(\overrightarrow{\C\D}\) ne soit pas le vecteur nul}}
# endif

\text{enonce1=
#if defined TARGET_04egaux || defined TARGET_05oppose || defined TARGET_06memenorme || defined TARGET_07memenormenoncoli
Le plan est rapporté à une grille constituée de carrés de côté de longueur 1 unité.<br/>
#endif
Les points \(\mathrm{\A}\), \(\mathrm{\B}\) et \(\mathrm{\C}\) étant donnés, déplacer le point \(\mathrm{\D}\) 
sur la grille de telle façon que les \exp_vect soient 
#if defined TARGET_04egaux
 égaux.
#endif
#if defined TARGET_05oppose
 opposés.
#endif
#if defined TARGET_06memenorme
 de même norme.
#endif
#if defined TARGET_07memenormenoncoli
 de même norme et ne soient pas \coli.
#endif
#if defined TARGET_01colineaire || defined TARGET_02memesens || defined TARGET_03sensoppose
# if defined TARGET_01colineaire
\enonce1bis.
# endif
# if defined TARGET_02memesens
de même sens.
# endif
# if defined TARGET_03sensoppose
de sens opposé.
# endif
#endif
}

#if defined TARGET_04egaux || defined TARGET_05oppose
\text{para= est un parallélogramme}
#endif

%%% FEEDBACK %%%

#if defined TARGET_01colineaire || defined TARGET_02memesens || defined TARGET_03sensoppose
\if{\conf2=1}
  {\text{feed1=Vos points \C et \D étant confondus, <strong>le vecteur \(\overrightarrow{\C\D}\) est égal au vecteur nul et n'a donc pas de direction</strong>.}}
  {\text{feed1=Le vecteur \(\overrightarrow{\C\D}\) ne devant  pas être égal au vecteur nul, <strong>les points \(\mathrm{\C}\) et 
\(\mathrm{\D}\) doivent être distincts</strong>.}
  }
#endif

#if defined TARGET_06memenorme || defined TARGET_07memenormenoncoli
\text{feed1=Les longueurs \(\mathrm{\A\B}\) et \(\mathrm{\C\D}\) ne sont pas égales, <strong>les \exp_vect n'ont pas la même norme</strong>. }
#endif



#if defined TARGET_01colineaire
\text{feed2=<strong>Les droites \((\mathrm{\A\B})\) et \((\mathrm{\C\D})\) ne sont pas parallèles</strong>, les \exp_vect ne sont donc pas \coli. 
Utilisez correctement le quadrillage pour déplacer le point 
\(\mathrm{\D}\) de façon à ce que les droites \((\mathrm{\A\B})\) et \((\mathrm{\C\D})\) soient parallèles.}
#endif

#if defined TARGET_02memesens || defined TARGET_03sensoppose
\text{feed2=<strong>Les \exp_vect ne sont pas \coli</strong>, ils ne peuvent donc pas
# if defined TARGET_02memesens
avoir le même sens.
# endif
# if defined TARGET_03sensoppose
être de sens opposé.
# endif 
}
#endif

#if defined TARGET_07memenormenoncoli
\text{feed2=Les \exp_vect ont effectivement la même norme, <strong>mais ils ne doivent pas être \coli</strong>.}
#endif


#if defined TARGET_02memesens || defined TARGET_03sensoppose
\text{feed3=Les \exp_vect sont bien \coli <strong>mais ils ne sont pas de
# if defined TARGET_02memesens
même sens</strong>.
# else
sens opposé</strong>.
# endif
}
\if{\conf1=1}
  {\text{feed3=\feed3 \inyourcase }}
#endif

#if defined TARGET_04egaux || defined TARGET_05oppose
\text{feed1=Les \exp_vect sont bien de même norme <strong>mais ils ne sont pas \coli</strong>.}
\text{feed2=Les \exp_vect
# if defined TARGET_04egaux 
ne sont pas égaux mais <strong>opposés</strong>.
# else
ne sont pas opposés mais <strong>égaux</strong>.
# endif
}
\if{\conf1=1}
  {\text{feed2=\feed2 \inyourcase }}

\text{feed3=Les \exp_vect <strong>n'ont pas la même norme et ne sont pas \coli</strong>.}
\text{feed4=Les \exp_vect sont bien \coli <strong>mais ils ne sont pas de
# if defined TARGET_04egaux 
même sens</strong>
# else
sens opposé</strong>
# endif
<strong>et n'ont pas la même norme</strong>.
}
\if{\conf1=1}
  {\text{feed4=\feed4 \inyourcase }}
  
\text{feed5=Les \exp_vect sont bien \coli et de
# if defined TARGET_04egaux 
même sens
# else
sens opposé
# endif
<strong>mais n'ont pas la même norme</strong>.
}
\if{\conf1=1}
  {\text{feed5=\feed5 \inyourcase }}
#endif


\text{display=Montrer votre réponse}
\text{notdisplay=Cacher votre réponse}

%%% IN CASE OF GOOD REP %%%
#if defined TARGET_01colineaire || defined TARGET_02memesens || defined TARGET_03sensoppose
\text{feed_good=Les \exp_vect sont bien 
# if defined TARGET_01colineaire
\coli.}
# endif
# if defined TARGET_02memesens
de même sens.}
# endif
# if defined TARGET_03sensoppose
de sens opposé.}
# endif
\if{\conf1=1}
  {\text{feed_good=\feed_good \inyourcase }}
#endif

#if defined TARGET_04egaux || defined TARGET_05oppose
\text{feed_good=Les \exp_vect sont bien \coli,
# if defined TARGET_04egaux
de même sens 
# else
de sens opposé
#endif
et de même norme  
# if defined TARGET_04egaux
(\(\mathrm{\A\B\D\C}\) est un parallélogramme). Les \exp_vect sont  égaux. 
# else
(\(\mathrm{\A\B\C\D}\) est un parallélogramme). Les \exp_vect sont opposés.
#endif
}
#endif

#if defined TARGET_06memenorme || defined TARGET_07memenormenoncoli
\text{feed_good=Les longueurs \(\mathrm{\A\B}\) et \(\mathrm{\C\D}\) sont bien égales. Les \exp_vect sont de même norme
# if defined TARGET_06memenorme
.
# else
et il ne sont effectivement pas \coli.
# endif
}
#endif

%%%% HELP %%%%
\text{help_caption=Outils GeoGebra utilisés}
\text{ico=Outils}
\text{signif=Rôles}
\text{signif1=Déplacer / Sélectionner un objet}
\text{signif2=Déplacer / Déplacer le graphique}
\text{signif3=Agrandir}
\text{signif4=Réduire}
\text{signif5=Annuler / Refaire}
\text{signif6=Vous pouvez déplacer le curseur à la souris ou avec les flèches du clavier en faisant au préalable un clic gauche sur le curseur.}

%%%%  HINT %%%%
#if !defined TARGET_04egaux && !defined TARGET_05oppose 
\text{definition1=Soit \(\mathrm{A}\) et \(\mathrm{B}\) deux points distincts. Le vecteur \(\overrightarrow{AB}\) 
est caractérisé par&nbsp;:}
\text{li1=sa direction&nbsp;: celle de la droite (AB)&nbsp;;}
\text{li2=son sens&nbsp;: celui de A vers B&nbsp;;}
\text{li3=sa norme&nbsp;: la longueur AB.}
\text{definition2=Si \(\mathrm{A}\) et \(\mathrm{B}\) sont confondus alors le vecteur \(\overrightarrow{AB}\) 
est le vecteur nul noté \(\overrightarrow{0}\). Il n'a ni direction, ni sens et sa norme est nulle.}
#endif
#if defined TARGET_04egaux
\text{definition1=Deux vecteurs non nuls \(\overrightarrow{AB}\) et \(\overrightarrow{CD}\) sont égaux si et seulement si 
ils ont la même direction, le même sens et la même norme.}
\text{definition2=Deux vecteurs \(\overrightarrow{AB}\) et \(\overrightarrow{CD}\) sont égaux si et seulement si le 
quadrilatère \(\mathrm{ABDC}\) est un parallélogramme (éventuellement aplati).}
#endif
#if defined TARGET_05oppose
\text{definition1=Deux vecteurs non nuls \(\overrightarrow{AB}\) et \(\overrightarrow{CD}\) sont opposés si et seulement si 
ils ont la même direction, des sens opposés et la même norme.}
\text{definition2=Deux vecteurs \(\overrightarrow{AB}\) et \(\overrightarrow{CD}\) sont opposés si et seulement si le 
quadrilatère \(\mathrm{ABCD}\) est un parallélogramme (éventuellement aplati).}
#endif
