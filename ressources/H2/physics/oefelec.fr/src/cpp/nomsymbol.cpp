target= nomsymbol nomsymbolcorr
#include "lang_titles.inc"
#include "lang.inc"
\author{Marie-joëlle, Ramage}
\email{marie-joelle.ramage@u-psud.fr}

*** définition taille de l'image en sortie **********************
\integer{drawsize=80}

*** création des dessins des composants - renvoie une url ****
\text{moteur=draw(200,200
slib(circuits/draw 1/comph,\drawsize,black,motor))}

\text{generateur=draw(200,200
slib(circuits/draw 1/comph,\drawsize,black,gen))}

\text{resistance=draw(200,200
slib(circuits/draw 1/comph,\drawsize,black,res))}

\text{amperemetre=draw(200,200
slib(circuits/draw 1/comph,\drawsize,black,ammeter))}

\text{voltmetre=draw(200,200
slib(circuits/draw 1/comph,\drawsize,black,voltmeter))}

\text{close=draw(200,200
slib(circuits/draw 1/comph,\drawsize,black,close2))}

\text{open=draw(200,200
slib(circuits/draw 1/comph,\drawsize,black,open2))}

\text{lampe=draw(200,200
slib(circuits/draw 1/comph,\drawsize,black,lamp))}

\text{del=draw(200,200
slib(circuits/draw 1/comph,\drawsize,black,del))}

*** constitution de la matrice de données *****

\matrix{donnees=<img src="\moteur" alt="">,\name_data[1;]
<img src="\generateur" alt="">,\name_data[2;]
<img src="\resistance" alt="">,\name_data[3;]
<img src="\amperemetre" alt="">,\name_data[4;]
<img src="\voltmetre" alt="">,\name_data[5;]
<img src="\close" alt="">,\name_data[6;]
<img src="\open" alt="">,\name_data[7;]
<img src="\lampe" alt="">,\name_data[8;]
<img src="\del" alt="">,\name_data[9;]}

*** calcul du nombre d'enregistrements (un par ligne) **************
\integer{nb=wims( rowcnt of \donnees)}

*** constitution de la liste de tirage de 5 images(sans remise)  *****

**** mélange des enregistrements ********************
\text{tirage=shuffle(\nb)}
\text{cnt=5}
**** constitution de la liste : tirage des 5 premiers éléments de la liste mélangée *************
#if defined TARGET_nomsymbol
\integer{choix=\tirage[1]}
\text{schemas=\donnees[\choix;1]}
\text{nom=\donnees[\choix;2]}
\text{article=\donnees[\choix;3]}
\for{i=2 to \cnt}{
  \text{schemas=wims(append item \donnees[\tirage[\i];1] to \schemas)}
}

\statement{<div class="instruction">
 \name_instruction
 \article \nom.
</div>
<div class="wimscenter">\embed{r1}</div>
}
\answer{}{1;\schemas}{type=click}{option=shuffle}
#endif
#if defined TARGET_nomsymbolcorr
\text{schemas=}
\text{definitions=}
\text{solution=}
\for{i=1 to \cnt}
  {\integer{choix=\tirage[\i]}
  \text{schemas=wims(append item \donnees[\choix;1] to \schemas)}
   \text{definitions=wims(append item \donnees[\choix;2] to \definitions)}
  }
\statement{<div class="instruction">
 \name_instruction
</div>
<div class="wimscenter">\embed{reply1,80x80x300}</div>
}
\answer{}{\schemas;\definitions}{type=correspond}{option=split}
#endif

\solution{<p>\name_feed.</p>
<table class="wimscenter wimsborder">
\for{j=1 to \cnt}{
<tr><td>\donnees[\j;1]</td><td>\donnees[\j;2]</td></tr>
}
</table>
}
