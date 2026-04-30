\statement{
<div class="encadre">
<p class="problematique">\prob</p>
<div id="boited">
<img src="\imagedir/python.png" alt="Logo de Python">
</div>
<div class="enonce">
\enonce
<div class="question">
\question
<div class="wims_instruction">\consigne</div>
\embed{reply1,[python,[\code]];[id1,theme=[\theme[\nbtheme;]] init fullscreen post=[\post] ,Jouer le code !]}
</div>
#if defined TARGET_periaire
<div class="question">
<div id="boiteg">
<img src="\imagedir/\plan[\ale;3]" width=100 alt="\plan[1]">
</div>
Sachant que le rayon \plan[\ale;1] a environ pour valeur \plan[\ale;2] \(km\), déterminer son \nff[\alea]
 arrondi à l'unité :
<div class="wimscenter">\embed{reply2,15} \(\unite[\alea]\)</div>
</div>
#endif
#if defined TARGET_sommec
<div class="question">
<div id="boiteg">
<img src="\imagedir/Square_pyramidal_number.svg.png" width=400 alt="Pyramide à base carré">
</div>
\oef_firstname dispose de \nbi billes pour construire une pyramide de base carré. Déterminer
 le nombre d'étages maximum qu'il peut effectuer : \embed{reply2,10}.
</div>
#endif
</div>
</div>
}
<script>
function graph(){alert(prog);}
execid1.addEventListener('click',graph);
</script>

\answer{}{\rtest}{type=runcode}{precision=\preci}
#if defined TARGET_periaire || defined TARGET_sommec
\answer{}{\RP}{type=numeric}
#endif
#if defined TARGET_comparaison
\text{code2=
def comparaison(a,b):
    return \ab[\alea] if a>b else \ba[\alea]
#Test#
print(comparaison(5,8))
}
\text{BB=slib(coding/runcode [python,[\code2]],id2,fullscreen  theme=[\theme[\nbtheme;]],Jouer le code !)}
\feedback{1=1}{<div class="solution"><p>Une manière plus efficace d'écrire le code est de
 l'écrire par compréhension :</p>
<div>
\BB
</div>
</div>}
#endif
