%%%%%%%%%%%%%%%%%%%% ENONCES %%%%%%%%%%%%%%%%%%%%%%%%%%

\text{phrase1=\A\B\C est un triangle rectangle en <span class="nowrap">\Sommet.</span>}
\text{phrase2=Compléter les phrases
#if defined TARGET_04ReconTrRect1
 en utilisant les étiquettes.
#endif

#if defined TARGET_04ReconTrRect2
 en indiquant les extrémités des segments.
#endif
} 

\text{quest1=Son hypoténuse est le côté&nbsp;}
\text{quest2=Le côté adjacent à l'angle \(\widehat{\NomAngle}\) est le côté&nbsp;}
\text{quest3=Le côté opposé à l'angle \(\widehat{\NomAngle}\) est le côté&nbsp;}

%%%%%%%%%%%%%%%%% BLOC SOLUTION %%%%%%%%%%%%%%%%%%%%%%%%

\text{SolDetails=
<p>Par définition, l'hypoténuse d'un triangle rectangle est le côté opposé à son angle droit. 
Ici, l'angle droit est \(\widehat{\Hyp[1]\Sommet\Hyp[2]}\), et <strong>l'hypoténuse</strong> est le côté 
 <span class="oef_indgood nowrap">[\Hyp[1]\Hyp[2]]</span>, appelé aussi 
 <span class="oef_indgood nowrap">[\Hyp[2]\Hyp[1]]</span>.
</p>
<p>Dans le triangle \A\B\C, l'angle \(\widehat{\NomAngle}\) est déterminé par deux côtés du triangle&nbsp;:</p>
<p>d'une part <strong>l'hypoténuse</strong>&nbsp;: le côté 
 <span class="nowrap oef_indgood">[\Hyp[1]\Hyp[2]]</span>&nbsp;;
</p>
<p>d'autre part <strong> le côté adjacent à l'angle <span class="nowrap">\(\widehat{\NomAngle}\)</strong>&nbsp;:</span> 
 le côté <span class="oef_indgood nowrap">[\Hyp[1]\Sommet]</span>, appelé aussi 
 <span class="oef_indgood nowrap">[\Sommet\Hyp[1]]</span>.
</p>
<p>Le troisième côté du triangle est <strong>le côté opposé à l'angle 
<span class="nowrap">\(\widehat{\NomAngle}\)</strong>&nbsp;:</span>
 le côté <span class="oef_indgood nowrap">[\Sommet\Hyp[2]]</span>, appelé aussi 
 <span class="oef_indgood nowrap">[\Hyp[2]\Sommet]</span>.
</p>
}


%%%%%%%%%%%%%%%%%%%%% CONDITIONS %%%%%%%%%%%%%%%%%%%%%%%%%

\text{cond1=Hypoténuse&nbsp;}
\text{cond2=Côté adjacent à \(\widehat{\NomAngle}\)&nbsp;}
\text{cond3=Côté opposé à \(\widehat{\NomAngle}\)&nbsp;}

%%%%%%%%%%%%%%%%%%%%% FEEDBACK %%%%%%%%%%%%%%%%%%%%%%%%%%%

\text{feed1=
Le point \Sommet est le sommet de l'angle droit&nbsp;; par définition, l'hypoténuse est le côté <em>opposé</em> 
à l'angle droit&nbsp;!}

\text{feed2=
Vous semblez confondre le côté adjacent à l'angle \(\widehat{\NomAngle}\) avec le côté opposé à ce même angle.}


#if defined TARGET_04ReconTrRect2
\text{feed3=
Vous avez reconnu l'hypoténuse, mais au moins une des extrémités du segment n'a pas été écrite en MAJUSCULE.
}
\text{feed4=
Vous avez reconnu le côté adjacent à l'angle \(\widehat{\NomAngle}\), mais au moins une des extrémités du segment 
n'a pas été écrite en MAJUSCULE.
}
\text{feed5=
Vous avez reconnu le côté opposé à l'angle \(\widehat{\NomAngle}\), mais au moins une des extrémités du segment 
n'a pas été écrite en MAJUSCULE.
}
\text{feed6=
Vérifiez que vos segments sont écrits correctement ou que leurs extrémités sont bien des sommets du triangle \A\B\C.
}
\text{feed7=
 réponses identiques ont été données&nbsp;!
}
#endif
