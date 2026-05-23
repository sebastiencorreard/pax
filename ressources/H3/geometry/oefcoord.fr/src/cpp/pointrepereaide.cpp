target=pointrepereaide

\title{Point dans un repère (aidé)}
\author{Marie-Claude, David}
\email{mcld@math.u-psud.fr}

	étapes
\steps{reply1
reply2}
	grille de base
\integer{taille=300}
\text{ grille =
   xrange -7.2,7.2
   yrange -7.2,7.2
   parallel -7,-7,7,-7,0,1,16, grey
   parallel -7,-7,-7,7,1,0,16, grey
   hline 0,0,black
   arrow 6,0,7,0,8, black
  text black, 0.8,-0.1, normal, 1
   arrow 0,6,0,7,8, black
   text black, -0.5,1, normal, 1
   vline 0,0,black }
 \text{nomgrille = draw(\taille,\taille
 \grille)}

	donnée du point A
\integer{a=random(-6..6)}
\integer{b=random(-1,1)*random(1..6)}
\real{s=7.2}
\text{ XX = slib(draw/convpixel \a,0,\taille,\taille,-\s,\s,-\s,\s,0,pixels) }
\real{ X = \XX[1] }
\real{ Y = \XX[2] }
\text{ PP = slib(draw/convpixel \a,\b,\taille,\taille,-\s,\s,-\s,\s,0,pixels) }
\real{ Px = \PP[1] }
\real{ Py = \PP[2] }
première question :
\text{reponse1=\grille
 vline \a,0,green
 circle \a,0,10,green}
\text{nomreponse1 = draw(\taille,\taille
 \reponse1)}

deuxième question :
 \text{reponse2=\reponse1
 hline 0,\b,orange
  disk \a,\b,10,blue}
\text{nomreponse2 = draw(\taille,\taille
 \reponse2)}


\statement{<span style="color:blue;">Cet exercice propose deux étapes pour placer
  le point \(A) de coordonnées \((\a,\b)) dans le repère.</span><br>
\if{\step=1}{<b>Première étape :</b> Cliquez sur le point de coordonnées \((\a,0)).
        <div class="wimscenter">\embed{ reply1 } </div>
}
\if{\step=2}{<i>Bravo ! Vous avez cliqué sur le point  de coordonnées \((\a,0)).</i><br>
<span style="color:green;">On a dessiné la droite verte qui porte tous les points d'abcisse \(\a).</span> <br>
<b>Deuxième étape : </b> Maintenant, cliquez sur le point \(A).
        <div class="wimscenter">\embed{ reply2 } </div>
}
}

\answer{}{\nomgrille ; point, \X,\Y}{type=coord}{option=noanalyzeprint}
\answer{}{\nomreponse1 ; point, \Px,\Py}{type=coord}
\feedback{ \result1 = -1 }{Le point de coordonnées \((\a,0)) est sur l'axe horizontal. <br>
<span style="color:green;">La droite verte porte tous les points d'abscisse \(\a).</sapn>}
\feedback{1=1 }{<span style="color:orange;">La droite orange porte tous les points d'ordonnée \(\b).</span>
<br><span style="color:blue;">Le point bleu est le point \(A) :</span>
    <div class="wimscenter">
    <img src="\nomreponse2" alt=""></div> }
