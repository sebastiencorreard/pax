target=Imagerciproque2 Imagerciproque Imagedelimager
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\range{-2..2}
\author{Bernadette, Perrin-Riou}
\email{bernadette.m.riou@orange.fr}
\computeanswer{yes}
\format{html}
\precision{100000}

\matrix{name_instruction=Soit la fonction \(f\) définie sur \(\displaystyle{\RR}\) par
  Soit, Que peut-on dire de}
\matrix{name_question=est-il égal à l'intervalle
  est-il strictement contenu dans
  contient-il strictement
  aucune de ces possibilités}
\text{name_feed= est toujours contenu dans \(I\). Votre réponse est donc impossible.}
#if defined TARGET_Imagerciproque2 || defined TARGET_Imagedelimager
\text{eg = est égal à \(I\)}
\text{cont=contient strictement \(I\)}
\text{contenu=est strictement contenu dans \(I\)}
\text{autre=aucune de ces possibilités}
#endif
#if defined TARGET_Imagerciproque || defined TARGET_Imagerciproque2
\text{vi =l'ensemble vide}
\text{int=un intervalle non vide}
\text{deuxint=la réunion de deux intervalles disjoints et maximaux}
#endif

\integer{a=random(1,-1)}
\integer{b=random(1..15)*random(-1,1)}
\integer{B=\b*2}
\real{cent=-(\b)/(\a)}
\integer{c=random(1..50)*random(-1,1)}
\function{f=\a*x^2 + \B*x + \c}
\real{base=evalue(\f,x=\cent)}

#if defined TARGET_Imagerciproque
\integer{zone=random(1,2,3)}
\integer{A1=item(\zone,random(\base-20..\base-9),
  random(\base-6..\base-2),
  random(\base+2..\base+8))}
\integer{B1=item(\zone,random(\base-8..\base-2),
	random(\base+7..\base+16),
	random(\base+9..\base+20))}
#endif
#if defined TARGET_Imagedelimager
\integer{zone=random(1,2,3)}
\integer{A1=item(\zone,random(\base-20..\base-9),
		random(\base-6..\base-2),
		random(\base+2..\base+8))}
\integer{B1=item(\zone,random(\base-8..\base-2),
		random(\base+7..\base+16),
		random(\base+9..\base+20))}
#endif
#if defined TARGET_Imagerciproque2
\integer{zone=random(1,2,3,4,4)}
\integer{a1=item(\zone,random(\cent-20..\cent-9),
		 random(\cent-6..\cent-2),
		 random(\cent+2..\cent+8),
		 random(\cent-6..\cent-2))}
\integer{b1=item(\zone,random(\cent-8..\cent-2),
		 random(\cent+7..\cent+16),
		 random(\cent+9..\cent+20),
		 2*\cent-\a1)}
#endif
#if defined TARGET_Imagerciproque
\text{liste=\a=1? \vi,\int,\deuxint :\deuxint,\int,\vi}
\text{bat=shuffle(3)}
\text{liste=\liste[\bat]}
\text{rep=position(\zone,\bat)}
#endif
#if defined TARGET_Imagerciproque2
\text{bad=shuffle(\eg,\cont,\contenu,\autre)}
\text{liste1=\cont,\cont,\cont,\eg}
\text{good=item(\zone,\liste1)}
#endif
#if defined TARGET_Imagedelimager
\text{bad=shuffle(\eg,\cont,\contenu,\autre)}
\text{liste1=\contenu,\contenu,\eg}
\text{liste2=\eg,\contenu,\contenu}
\text{good=\a=1? item(\zone,\liste1): item(\zone,\liste2)}
#endif
#if defined TARGET_Imagerciproque2
\statement{\name_instruction[1;]
  <div class="wimscenter">\(f(x) = \f\).</div>
  \name_instruction[2;1] \(I\) = [\a1, \b1].
  \name_instruction[2;2] \(f^{-1}(f( I ))\):
  \name_question[1;] \(I\)?
  \name_question[2;] \(I\)?
  \name_question[3;] \(I\)?
  \name_question[4;]?
}

\choice{Il}{\good}{\bad}
\hint{Chercher l'extremum de la parabole et faites un dessin.}
\feedback{\choice1= \autre or \choice1= \contenu}{
  \(f^{ -1} \circ f (I)\) contient toujours \(I\). Votre réponse est donc impossible. }
\feedback{\choice1!= \good and \good=\eg}{
  Faites un dessin : vous verrez que l'intervalle \(I\) est symétrique par rapport
  à la \(x\)-coordonnée de l'extremum de la parabole qui est \cent.
}
#endif
#if defined TARGET_Imagerciproque
\statement{
  \name_instruction[1;]
  <div class="wimscenter">\(f(x) = \f\).</div>
 \name_instruction[2;1] \(I\) = [\A1 , \B1]. \name_instruction[2;2] \(f^{-1}( I )\) ? C'est
  <ul>
  <li>\embed{reply1,1}</li>
  <li>\embed{reply1,2}</li>
  <li>\embed{reply1,3}</li>
  </ul>
}
\answer{Il est }{ \rep;\liste}{type=radio}
#endif
#if defined TARGET_Imagedelimager
\statement{\name_instruction[1;]
  <div class="wimscenter">\(f(x) = \f\).</div>
 \name_instruction[2;1] \(I\) = [\A1 , \B1]. \name_instruction[2;2] \(f (f^{ -1}(I))\) :
  \name_question[1;] \(I\)?
  \name_question[2;] \(I\)?
  \name_question[3;] \(I\)?
  \name_question[4;]?
}

\choice{Il}{\good}{\bad}

\feedback{\choice1= \autre or \choice1= \cont}{\(f (f^{-1}( I))\) \name_feed }
#endif
