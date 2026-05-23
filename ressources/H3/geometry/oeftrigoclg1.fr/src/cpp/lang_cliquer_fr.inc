%%%%%%%%%%%%%%%%%%%% ENONCES %%%%%%%%%%%%%%%%%%%%

\text{phrase1=\A\B\C est un triangle rectangle en <span class="nowrap">\Sommet.</span>}
#if defined TARGET_01CliquerHypotenuse
\text{phrase2=Sélectionner son hypoténuse.}
\text{phrase3=Identifier son hypoténuse.}
#endif
#if defined TARGET_02CliquerAdjacent || defined TARGET_03CliquerOppose
\text{NomAngle=randitem(1,2)=1?\Sommet\Hyp[1]\Hyp[2]:\Hyp[2]\Hyp[1]\Sommet}
# if defined TARGET_02CliquerAdjacent
 \text{phrase2=Sélectionner le côté adjacent à l'angle aigu <span class="nowrap">\(\widehat{\NomAngle}\).</span>}
 \text{phrase3=Identifier le côté adjacent à l'angle aigu <span class="nowrap">\(\widehat{\NomAngle}\).</span>}
# else
 \text{phrase2=Sélectionner le côté opposé à l'angle aigu <span class="nowrap">\(\widehat{\NomAngle}\).</span>}
 \text{phrase3=Identifier le côté opposé à l'angle aigu <span class="nowrap">\(\widehat{\NomAngle}\).</span>}
# endif
#endif


%%%%%%%%%%%%%%%%% MODE EMPLOI CLIC %%%%%%%%%%%%%%%%%%%%%


\text{title_accord=Comment sélectionner un objet ?}
\text{procedure=
Un clic sur un objet sélectionne l'objet&nbsp;; un nouveau clic sur le même objet annule la sélection.
<p>Une fois la sélection voulue effectuée, cliquer sur "Envoyer la réponse".</p>}


%%%%%%%%%%%%%%%%% BLOC SOLUTION %%%%%%%%%%%%%%%%%%%%%%%%

\text{SolDetails=
#if defined TARGET_01CliquerHypotenuse
<p>Par définition, l'hypoténuse d'un triangle rectangle est le côté opposé à l'angle droit.</p>
<p>Ici, \A\B\C est un triangle rectangle en \Sommet&nbsp;: le sommet de l'angle droit du
triangle est le point \Sommet.</p>
<p>Son côté opposé, appelé hypoténuse,  est le segment
 <span class="nowrap"><span class="oef_indgood">[\Hyp[1]\Hyp[2]]</span>.</span>
</p>
#endif
#if defined TARGET_02CliquerAdjacent || defined TARGET_03CliquerOppose
<p>Dans un triangle rectangle, un angle aigu a deux côtés&nbsp;:</p>
<ul class="euler_ul">
 <li> l'un est l'hypoténuse du triangle rectangle (c'est le côté opposé à l'angle droit)&nbsp;;</li>
 <li>l'autre côté de l'angle aigu est son côté adjacent.</li>
</ul>
# if  defined TARGET_03CliquerOppose
<p>Le troisième côté du triangle est le côté opposé à cet angle aigu.</p>
<p>Dans le triangle \A\B\C rectangle en \Sommet, les deux côtés de l'angle aigu
\(\widehat{\NomAngle}\) sont [\Hyp[1]\Hyp[2]] et [\Hyp[1]\Sommet].
<br>Le troisième côté <span class="oef_indgood">[\Hyp[2]\Sommet]</span> est le côté
opposé à l'angle aigu <span class="nowrap">\(\widehat{\NomAngle}\).</span>
</p>
# endif
# if  defined TARGET_02CliquerAdjacent
<p>Dans le triangle \A\B\C rectangle en \Sommet, les deux côtés de l'angle aigu
\(\widehat{\NomAngle}\) sont&nbsp;:
  <ul class="euler_ul">
   <li>d'une part l'hypoténuse <span class="nowrap">[\Hyp[1]\Hyp[2]] ;</span></li>
   <li>d'autre part le segment <span class="oef_indgood nowrap">[\Hyp[1]\Sommet]</span>,
   côté adjacent à l'angle aigu <span class="nowrap">\(\widehat{\NomAngle}\).</span></li>
  </ul>
# endif
#endif
}

%%%%%%%%%%%%%%%%%%%% FEEDBACK %%%%%%%%%%%%%%%%%%%%

\text{feed_good=Vous avez sélectionné le côté <span class="oef_indgood">\segt1</span>. C'est bien
#if defined TARGET_01CliquerHypotenuse
l'hypoténuse du triangle <span class="nowrap">\A\B\C</span> rectangle en <span class="nowrap">\Sommet.</span>
#endif
#if defined TARGET_02CliquerAdjacent || defined TARGET_03CliquerOppose
le côté
# if defined TARGET_02CliquerAdjacent
adjacent
# else
opposé
# endif
à l'angle aigu <span class="nowrap">\(\widehat{\NomAngle}\).</span>
#endif
}

\text{feed_bad_1=Vous avez sélectionné le côté <span class="oef_indbad">\segt2</span>. C'est
#if defined TARGET_01CliquerHypotenuse
un côté de l'angle droit&nbsp;!
#endif
#if defined TARGET_02CliquerAdjacent || defined TARGET_03CliquerOppose
 l'hypoténuse&nbsp;!
#endif
}

\text{feed_bad_2=Vous avez sélectionné le côté <span class="oef_indbad">\segt3</span>. C'est
#if defined TARGET_01CliquerHypotenuse
un côté de l'angle droit&nbsp;!
#endif
#if defined TARGET_02CliquerAdjacent || defined TARGET_03CliquerOppose
 le côté
# if defined TARGET_02CliquerAdjacent
opposé
# else
adjacent
# endif
à l'angle aigu <span class="nowrap">\(\widehat{\NomAngle}\)&nbsp;!</span>
#endif
}

\text{feed_multi_clic=Vous avez sélectionné plusieurs segments&nbsp;!}

\text{feed_sol=
#if defined TARGET_01CliquerHypotenuse
L'hypoténuse
#endif
#if defined TARGET_02CliquerAdjacent || defined TARGET_03CliquerOppose
Le côté
# if defined TARGET_02CliquerAdjacent
adjacent
# else
opposé
# endif
à l'angle aigu <span class="nowrap">\(\widehat{\NomAngle}\)</span>
#endif
du triangle <span class="nowrap">\A\B\C</span> rectangle en \Sommet est le côté
<span class="nowrap oef_indgood">\segt1</span>.}
