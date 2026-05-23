\title{Question 205 Calculer le périmètre d'un losange}
\keywords{quizz,perimeter}
\observation{Question du sujet zéro sujet-zero-dnb-serie-generale-a-mathematiques.pdf du DNB publié sur éduscol en décembre 2025  }

%%%%%%%%%%%%%%%%%%%%%%%
l'unité (cm) n'apparait pas après le embed
MB : il faut le mettre dans \enonceb et pas dans enonce2. C'est corrigé
%%%%%%%%%%%%%%%%%%%%%%%


%% Losange ABCD, avec les côtés AB et CD sur les lignes du quadrillage

\integer{cote=randint(3..8)}
\integer{xA=0}
\integer{yA=0}
\integer{xB=\cote}
\integer{yB=0}
\integer{yD=randint(2..\cote)}
\real{xD=randint(1,-1)*sqrt(\cote*\cote-\yD*\yD)}
\real{xC=\xB+\xD}
\integer{yC=\yD}

\real{xmin=min(min(min(\xA,\xB),\xC),\xD)-1.5}
\real{xmax=max(max(max(\xA,\xB),\xC),\xD)+0.8}
\real{ymin=min(min(min(\yA,\yB),\yC),\yD)-1.6}
\real{ymax=max(max(max(\yA,\yB),\yC),\yD)+0.8}

\if{\cote<4 or \yD<3}{
  \integer{size=randint(40..50)}
}
\if{\cote>=4 and \cote<=6}{
  \integer{size=randint(30..40)}
}
\if{\cote>=7}{
  \integer{size=randint(25..35)}
}

\integer{size_x=(\xmax-\xmin)*\size}
\integer{size_y=(\ymax-\ymin)*\size}

\text{quadrillage=}
\for{k=ceil(\xmin) to floor(\xmax)}{
  \text{quadrillage=\quadrillage
    segment \k,\ymin,\k,\ymax,grey
  }
}
\for{k=ceil(\ymin) to floor(\ymax)}{
  \text{quadrillage=\quadrillage
    segment \xmin,\k,\xmax,\k,grey
  }
}

\text{dessin=draw(\size_x,\size_y
  xrange \xmin,\xmax
  yrange \ymin,\ymax
  \quadrillage
  segment -1,-1,0,-1,red
  segment -1,-1.2,-1,-0.8,red
  segment 0,-1.2,0,-0.8,red
  text red, -0.9,-0.4,medium,1 cm
  linewidth 2
  polygon blue, \xA,\yA,\xB,\yB,\xC,\yC,\xD,\yD
)}


\text{dessin_feedback=draw(\size_x,\size_y
  xrange \xmin,\xmax
  yrange \ymin,\ymax
  \quadrillage
  segment -1,-1,0,-1,red
  segment -1,-1.2,-1,-0.8,red
  segment 0,-1.2,0,-0.8,red
  text red, -0.9,-0.4,medium,1 cm
  linewidth 2
  polygon blue, \xA,\yA,\xB,\yB,\xC,\yC,\xD,\yD
  dsegment \xA,\yA,\xB,\yB,red
  text red, \xB/2-0.5, -0.1,giant,\cote cm
)}


\text{enonce=Quel est le périmètre de ce losange&nbsp;&#63;
<br><img src="\dessin" alt="">
}

\integer{rep=\cote*4}

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
\text{enonceb=cm}

\text{typerep=formal}

\text{feedback=Comme tous les losanges&#44; il a ses 4 côtés qui sont de la même mesure.
<br>On trouve la mesure de ses côtés grace aux carreaux &#58; <span style="color:red">\cote cm</span>.
<br><img src="\dessin_feedback" alt="">
<br>On calcule le périmètre &#58; \cote cm &#215; 4 = \rep cm
<br>
<br><u>Ce losange a un périmètre de <b>\rep centimètres</b></u>.
}
