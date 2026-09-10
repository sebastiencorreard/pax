%%%%%%%%%%%%%%%%%% TEXTES DE L EXERCICE %%%%%%%%%%%
#if defined TARGET_01a || defined TARGET_01b
\text{enonce0=Cliquer, dans la liste ci-dessous, sur l'hypoténuse du triangle \A\B\C&nbsp;:}
#endif
#if defined TARGET_02a || defined TARGET_02b || defined TARGET_03a || defined TARGET_03b || defined TARGET_04a || defined TARGET_04b ||  defined TARGET_05a || defined TARGET_05b 
\text{enonce0=Compléter la zone de saisie avec un nombre écrit en chiffres ou avec une expression numérique.}
#endif
\text{enonce0_sol=Compléter.}

\text{reprise_rep=Vous avez répondu&nbsp;:<br class="spacer">}
\text{rep_exacte=Cette réponse est exacte.}
\text{rep_fausse=Cette réponse est fausse.}

#if defined TARGET_01a || defined TARGET_01b || defined TARGET_02a || defined TARGET_02b || defined TARGET_03a || defined TARGET_03b  || defined TARGET_04a || defined TARGET_04b || defined TARGET_05a || defined TARGET_05b || defined TARGET_09 
\text{credits_JSX=<span class="euler_credit">Figure réalisée avec JSXGraph</span>}
#endif

#if defined TARGET_01a || defined TARGET_01b 
\text{enonce1=Soit \A\B\C un triangle rectangle en <span class="nowrap">\Sommet.</span><br class="spacer">}
\text{enonce1_sol=\enonce1}
\text{enonce_saisie=Son hypoténuse est le côté}
\text{enonce_saisie_sol=Son hypoténuse est le côté ..........}
\text{sol_sol1=Le point \Sommet est le sommet de l'angle droit&nbsp;; <br>
les côtés de l'angle droit sont les segments [\Sommet\Hyp[1]] et [\Sommet\Hyp[2]]&nbsp;; <br>
le troisième côté du triangle, côté opposé à l'angle droit, est l'hypoténuse.
<p> Ici l'hypoténuse est le côté <span class="oef_indgood">[\Hyp[1]\Hyp[2]]</span>,
  nommé aussi <span class="oef_indgood">[\Hyp[2]\Hyp[1]]</span>.</p>
}

\text{cond1=Hypoténuse identifiée&nbsp;}
\text{cond2=Hypoténuse correctement écrite&nbsp;}

#endif




#if defined TARGET_02a || defined TARGET_02b || defined TARGET_03a || defined TARGET_03b || defined TARGET_04a || defined TARGET_04b || defined TARGET_05a || defined TARGET_05b

\text{enonce1=Une unité de longueur est donnée.<br>
Soit \A\B\C un triangle rectangle en \Sommet tel que&nbsp;:<br>}
  
\text{enonce1=\enonce1
  #if defined TARGET_02a || defined TARGET_02b || defined TARGET_04a || defined TARGET_04b
  - l'aire du carré construit sur le côté [\Sommet\Hyp[1]] de l'angle droit est égale à \(\A_B\) unités d'aire&nbsp;;<br>
  - l'aire du carré construit sur le côté [\Sommet\Hyp[2]] de l'angle droit est égale à \(\A_C\) unités d'aire.<br class="spacer">
    #if defined TARGET_04a || defined TARGET_04b
      Calculer la longueur de l'hypoténuse [\Hyp[1]\Hyp[2]], en unités de longueur.
    #endif
  #else
  - l'aire du carré construit sur l'hypoténuse [\Hyp[1]\Hyp[2]] est égale à \(\A_Hyp\) unités d'aire&nbsp;;<br>
  - l'aire du carré construit sur le côté [\Sommet\Hyp[1]] de l'angle droit est égale à \(\A_B\) unités d'aire.<br class="spacer">
    #if defined TARGET_05a || defined TARGET_05b
      Calculer la longueur du côté [\Sommet\Hyp[2]] de l'angle droit, en  unités de longueur.
    #endif
  #endif
}
\text{enonce1_sol=\enonce1}

  #if defined TARGET_02a || defined TARGET_02b || defined TARGET_03a || defined TARGET_03b
  \text{enonce_saisie=L'aire du carré construit sur 
    #if defined TARGET_02a || defined TARGET_02b
      l'hypoténuse [\Hyp[1]\Hyp[2]]
    #else
      le côté [\Sommet\Hyp[2]] de l'angle droit
    #endif
    est, en unités d'aire, égale à }
  #endif

  #if defined TARGET_04a || defined TARGET_04b
  \text{enonce_saisie=\Hyp[1]\Hyp[2] = }
  #endif
  
  #if defined TARGET_05a || defined TARGET_05b
  \text{enonce_saisie=\Sommet\Hyp[2] = }
  #endif

\text{enonce_saisie_sol=\enonce_saisie ..........}


  #if defined TARGET_02a || defined TARGET_02b || defined TARGET_04a || defined TARGET_04b
    \text{sol_sol1=L'aire du carré construit sur l'hypoténuse [\Hyp[1]\Hyp[2]] est la somme des aires des carrés
    construits sur les côtés de l'angle droit [\Sommet\Hyp[1]] et [\Sommet\Hyp[2]]&nbsp;; c'est le
     <span class="oef_indgood">théorème de Pythagore</span>.<br>
    On calcule ici <span class="nowrap">\(\A_B + \A_C = \A_Hyp\).</span><br class="spacer">
    L'aire du carré construit sur l'hypoténuse [\Hyp[1]\Hyp[2]] est égale à <span class="oef_indgood">\(\A_Hyp\)</span> unités d'aire.
    #if  defined TARGET_04a || defined TARGET_04b
      <br>Il existe deux nombres dont le carré est égal à <span class="nowrap">\(\A_Hyp\)&nbsp;:</span> les nombres opposés \(\Opp_Hyp\) et <span class="nowrap">\(\Hypo\).</span><br>
      La longueur de l'hypoténuse étant un nombre positif, on a <span class="nowrap oef_indgood"> \Hyp[1]\Hyp[2]=\(\Hypo\)</span> unités de longueur.
    #endif
    }
  #endif
  #if defined TARGET_03a || defined TARGET_03b || defined TARGET_05a || defined TARGET_05b
    \text{sol_sol1=
    L'aire du carré construit sur le côté [\Sommet\Hyp[2]] de l'angle droit est égale
     à la différence entre l'aire du carré construit sur l'hypoténuse [\Hyp[1]\Hyp[2]]
     et l'aire du carré construit sur l'autre côté de l'angle droit [\Sommet\Hyp[1]]&nbsp;; c'est le <strong>théorème de Pythagore</strong>.<br>
    On calcule ici <span class="nowrap">\(\A_Hyp - \A_B = \A_C\).</span><br class="spacer">
    L'aire du carré construit sur le côté [\Sommet\Hyp[2]] de l'angle droit est égale à <span class="oef_indgood">\(\A_C\)</span> unités d'aire.
    #if  defined TARGET_05a || defined TARGET_05b
    Il existe deux nombres dont le carré est égal à <span class="nowrap">\(\A_C\)&nbsp;:</span> les nombres opposés \(\OppL_C\) et <span class="nowrap">\(\L_C\).</span><br>
    La longueur d'un côté étant un nombre positif, on a <span class="nowrap oef_indgood"> \Sommet\Hyp[2]=\(\L_C\)</span> unités de longueur.
    <p>Remarque&nbsp;:  On a bien <span class="nowrap">\(\solution1 \times \solution1 = \A_Hyp - \A_B\).</span></p> 
    #endif
    }
  #endif
  
#endif




#if defined TARGET_06 || defined TARGET_07 || defined TARGET_08 || defined TARGET_09

\text{def_triangle=Le triangle \(\A\B\C\) est rectangle en }
\text{def_triangle2=Dans le triangle \(\A\B\C\) rectangle en }

 #if defined TARGET_09
\text{enonce0=\def_triangle <span class="nowrap">\liste_sommets[\config].</span>
<div class="spacer quest">Parmi les affirmations suivantes, cocher celles qui sont vraies.</div>}
 #endif
 
\text{sol1=d'après le théorème de Pythagore}
\text{sol2= on a successivement&nbsp;:}

 #if defined TARGET_09
\text{sol3=La proposition}
\text{sol4= est donc <span class="oef_indgood">vraie</span>}
\text{sol5=est <span class="oef_indbad">fausse</span>}
\text{sol6=En effet, c'est dans le triangle \A\B\C <span class="oef_indbad">rectangle en }
\text{sol7=</span> que l'on obtient}
\text{sol8=cette égalité de Pythagore.}
\text{sol9=successivement d'après le théorème de Pythagore&nbsp;:}
 #endif

 #if defined TARGET_06 || defined TARGET_07 || defined TARGET_08
\text{enonce0=On donne trois descriptions de triangle \(\A\B\C\) et trois égalités.
<div class="spacer quest">Pour chacun des cas suivants, sélectionner le sommet qui permet d'associer à l'égalité de Pythagore donnée le triangle rectangle correspondant.</div>
}

%%%%% TABLE SOLUTION %%%%
\text{th1=Triangle}
\text{th2=&#201;galité}
\text{sol_liaison=Des indications ci-dessus nous déduisons les associations suivantes&nbsp;:
}
 #endif
#endif

#if defined TARGET_01a || defined TARGET_01b || defined TARGET_06 || defined TARGET_07 || defined TARGET_08 || defined TARGET_09
%%% Sigle Title %%%%
\text{title_good=Réponse correcte}
\text{title_bad=Réponse fausse}
\text{title_forget=Réponse correcte oubliée}
#endif
