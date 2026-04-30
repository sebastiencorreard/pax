#if defined TARGET_thmpte5
\title{TITRE 5}
\integer{k=randint(1..3)}
integer{k=3}
\if{\k=1}
{
\text{lstrep=Le quadrilatère \(FACB) est un parallélogramme&#44; car ses côtés sont parallèles deux à deux.,
   Le quadrilatère \(AECB) est un parallélogramme&#44; car ses côtés sont parallèles deux à deux.,
\(FA=BC=AE),
   La médiatrice de \([FE]) passe par \(A). De même&#44; la médiatrice de \([ED]) passe par \(C) et celle de \([DF]) par \(B).,
   Comme les côtés de FED sont parallèles aux côtés de ABC&#44; les médiatrices de FED sont les hauteurs de ABC.,
   Comme les médiatrices d'un triangle sont concourantes&#44; les hauteurs de ABC sont concourantes.
}
\text{rep=\lstrep}
\text{size=250x100x1}
\text{dessin=
 xrange -6,6
 yrange -3,9
 linewidth 2
 poly black,-5,8,5,8,2,-2
 poly blue,0,8,-1.5,3,3.5,3
 segment 0,3,0,8,red
 segment -1.09,4.38,3.5,3,red
 segment 1.86,5.35,-1.5,3,red
 text black,0,8.5,medium,A
 text black,-2,3,medium,B
 text black,4,3,medium,C
 text black,2,-2.5,medium,D
 text black,5,8.5,medium,E
 text black,-5,8.5,medium,F
}

}
\if{\k=2}
{
\text{lstrep=La médiatrice d'un segment est l'ensemble des points du plan qui sont équidistants des extrémités du segment.,
   On trace les médiatrices de \([AB]) et de \([AC]) et on note O leur point commun.,
   Du fait que O est un point de la médiatrice de [AB]&#44; on a \(OA = OB).,
   Du fait que O est un point de la médiatrice de [AC]&#44; on a \(OA = OC).,
   On a donc l'égalité \(OB = OC).,
   Le point O appartient donc à la médiatrice de \([BC]).}
\text{rep=\lstrep}
\text{size=250x100x1}
\text{dessin=
 xrange -5,10
 yrange -5,10
 linewidth 2
 poly black,0,8,-4,-2,8,-2
 segment -2,3,2,1.4,red
 segment 4,3,2,1.4,red
 segment -4,-2,2,1.4,blue
 segment 0,8,2,1.4,blue
 segment 8,-2,2,1.4,blue
 text black,0,8.5,medium,A
 text black,-4,-2.8,medium,B
 text black,8,-2.8,medium,C
 text black,2,1,medium,O
}
}
\if{\k=3}
{
\text{lstrep=\(I) étant le milieu de \([HB]) et \(J) le milieu de \([AH])&#44; un théorème de la "droite des milieux"&#44; dans le triangle \(ABH)&#44; implique que \((IJ) \parallel (BA)).,
   Comme \((BA)) est perpendiculaire à \((AC))&#44; \((IJ)) est également perpendiculaire à \((AC)).,
   Donc le point \(J) appartient à la hauteur issue de \(I) du triangle \(AIC).,
   Le point \(J) appartient à la hauteur issue de \(A) du triangle \(AIC).,
   La droite \((CJ)) est une hauteur du triangle \(AIC)&#44; car les trois hauteurs d'un triangle sont concourantes.,
   Les droites \((CJ)) et \((AI)) sont perpendiculaires.
}
\text{rep=\lstrep}
\text{size=350x100x1}
\text{dessin=
 xrange -0.5,8.5
 yrange -2,7
 linewidth 2
 poly black,0,5,0,0,8,0
 segment 0,0,2.25,3.6,red
 linewidth 5
 points black,1.12,4.3,1.12,1.8,blue
 text black,0,-0.5,medium,A
 text black,0,5.5,medium,B
 text black,8,-0.8,medium,C
 text black,1,5,medium,I
 text black,1,2.5,medium,J
 text black,2,4.4,medium,H
}
}
\statement{
<div class="float_right">\draw{250,250}{\dessin}</div>

\if{\k=1}
{Soit un triangle ABC. Par A on mène la parallèle à (BC), par B la parallèle à (AC) et par C la parallèle à (AB). Ces trois droites définissent un triangle DEF.
   Montrons que les trois hauteurs d'un triangle sont concourantes.
}
\if{\k=2}{
   On rappelle que la médiatrice d'un segment est la droite perpendiculaire à ce segment qui passe par son milieu.<p>
   Soit un triangle \(ABC). Montrons que les médiatrices de ses côtés ont un point commun, qui est le centre d'un cercle passant par les trois sommets.
}
\if{\k=3}{
   Soit un triangle \(ABC) rectangle en \(A).
   La hauteur issue de \(A) coupe \((BC)) en \(H).
   On note \(I) le milieu du segment \([BH]) et \(J) le milieu du segment \([AH]).
<p>
   On souhaite prouver que les droites \((CJ)) et \((AI)) sont perpendiculaires.
</p>
}
   Il s'agit d'ordonner le raisonnement ci-dessous.
<ul class="wims_nopuce"><li>
\embed{reply1,\size} \embed{reply2,\size}</li>
<li>\embed{reply3,\size} \embed{reply4,\size}</li>
<li>\embed{reply5,\size} \embed{reply6,\size}</li>
</ul>
}
\answer{}{\rep1;\lstrep}{type=clickfill}
\answer{}{\rep2;\lstrep}{type=clickfill}
\answer{}{\rep3;\lstrep}{type=clickfill}
\answer{}{\rep4;\lstrep}{type=clickfill}
\answer{}{\rep[5];\lstrep}{type=clickfill}
\answer{}{\rep[6];\lstrep}{type=clickfill}
\if{\k=3}
{
\text{larep=\rep1,\rep2,\rep3,\rep4}
\integer{i1=position(\rep[1],\larep)}
\integer{i2=position(\rep[2],\larep)}
\integer{i3=position(\rep[3],\larep)}
\integer{good=\i1 <\i2 and \i2 < \i3?1:0}
}
\condition{}{(\k=1 and \rep3 issametext \rep[3] and \rep4 issametext \rep[4] and ((\rep1 issametext \rep[1] and \rep2 issametext \rep[2]) or (\rep1 issametext \rep[2] and \rep2 issametext \rep[1])))
or (\k=2 and \rep1 issametext \rep[1] and \rep2 issametext \rep[2] and ((\rep3 issametext \rep[3] and \rep4 issametext \rep[4]) or (\rep3 issametext \rep[4] and \rep4 issametext \rep[3])))
or (\k=3 and \good=1)
}
#endif
