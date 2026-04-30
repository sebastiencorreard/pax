\integer{goodrep=3}
\text{facedest= wims(listintersect \faces[\indpt1;] and \faces[\indpt2;])}
\if{ \face isitemof \facedest}{ \integer{goodrep=2}}{
  calcul de la pente de la droite choisie
  \text{cpt1=\PT[\indpt1;]}
  \text{cpt2=\PT[\indpt2;]}
  \rational{vecx=\cpt1[1] - (\cpt2[1])}
  \rational{vecy=\cpt1[2] - (\cpt2[2])}
  \rational{vecz=\cpt1[3] - (\cpt2[3])}
  calcul du ecteur normal au plan
  \text{cpt3=\PT[\indpl1;]}
  \text{cpt4=\PT[\indpl2;]}
  \text{cpt5=\PT[\indpl3;]}
  \rational{vec1x=\cpt3[1] - (\cpt4[1])}
  \rational{vec1y=\cpt3[2] - (\cpt4[2])}
  \rational{vec1z=\cpt3[3] - (\cpt4[3])}
  \rational{vec2x=\cpt3[1] - (\cpt5[1])}
  \rational{vec2y=\cpt3[2] - (\cpt5[2])}
  \rational{vec2z=\cpt3[3] - (\cpt5[3])}
  \rational{nvecx=\vec1y*\vec2z-\vec1z*\vec2y}
  \rational{nvecy=\vec1z*\vec2x-\vec1x*\vec2z}
  \rational{nvecz=\vec1x*\vec2y-\vec1y*\vec2x}
  \rational{pdtscal=\nvecx*\vecx+\nvecy*\vecy+\nvecz*\vecz}
  \if{ \pdtscal<0.001 and \pdtscal>-0.001}{\integer{goodrep=1}}
}
