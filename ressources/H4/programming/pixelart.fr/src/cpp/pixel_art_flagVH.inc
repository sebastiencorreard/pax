\text{lii=\pays[\x1;3]}
\text{nomi=Drapeau \pays[\x1;2]}

\integer{rh=randint(0..255)}
\integer{gh=randint(0..255)}
\integer{bh=randint(0..255)}

\text{enonce=Le but de cette exercice est de créer un programme Python afin de concevoir
 le drapeau proposé. Pour réaliser ce drapeau, il faut récupérer les couleurs
 RGB de chaque zone du drapeau. On doit donc télécharger l'image du drapeau et utiliser
 l'outil pipette de votre logiciel de traitement d'images préféré.
 <br/>
 Par exemple le rouge du drapeau Français donne le code RGB suivant : 206,17,38.
 Pour affecter cette valeur aux cellules de votre matrice, il suffit d'écrire le code suivant: 
 <code>mat[i][j]=[206,17,38]</code>
 <div class="wims_instruction">
Modifier la position des 3 curseurs afin de vérifier les couleurs obtenues. Par exemple
 essayer d'obtenir le rouge RGB : 206,17,38.
</div>
<table class="wimscenter wimsborder">
  <tr><td>Red</td>
      <td><input type="range" min="0" max="255" value="\rh" id="rouge"></td>
      <td id="rv">\rh</td>
  </tr>
  <tr>
      <td>Green</td>
      <td><input type="range" min="0" max="255" value="\bh" id="vert"></td>
      <td id="gv">\gh</td>
  </tr>
  <tr>
      <td>Blue</td>
      <td><input type="range" min="0" max="255" value="\gh" id="bleu"></td>
      <td id="bv">\bh</td>
   </tr>
</table>
<div id="boule"></div>

}

\text{encop=[[1] * nombre_colonne for _ in range(nombre_ligne)]}

\text{keytest=for&if&or}
\text{instruction_code=instruction=[if, 2<=k<=3:]}

\integer{alt=randint(0..3)}
\integer{pp=randint(0..1)}
\integer{ppp=randint(0..2)}
\text{cond1=randitem(j%2==\pp,j%3==\ppp,true)}
\text{cond2=randitem(i<=j+\alt,j<=i+\alt)}

\text{DDV=pari(print(m);)}
text{DD=wims(declosing \DDV)}
text{DD=wims(declosing \DD)}
text{DD=wims(replace internal &#93;,&#91; by , in \DDV )} <= Bon affichage matrice
text{DD=wims(replace internal ; by , in \DD)}
text{DD=wims(declosing \DD)}
text{DD=[\DD]}<= Bon affichage matrice

\text{DD=}
\text{mjsx=}
\for{kj=1 to \nl}{
\for{kk=1 to \nc}{
\text{s=\DDV[\kj;\kk]}
\text{ss=wims(declosing \s)}
\text{DD=wims(append word \ss, to \DD)}
\text{mjsx=wims(append line board.create('point', [\kk-0.5,\kj-0.5],{color:"rgb(\ss)"}); to \mjsx)}
}}

\text{DD=wims(nospace \DD)}
\text{DD=wims(char 1 to -2 of \DD)}

\text{inst=Modifier cet algorithme afin qu'il réalise le drapeau \pays[\x1;1].
 La représentation donnée à droite ou ci-dessous est à effectuer.}
