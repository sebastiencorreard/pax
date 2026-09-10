le premier doit être la lune vide

signe(8/2-i+0.2) dans la liste
qu'est-ce que ls ?

\text{listinit=pari([[1,1],[sqrt(2)/2,1],[0,1],[-sqrt(2)/2,1],
  [-1,-1],[-sqrt(2)/2,-1],[0,-1],[sqrt(2)/2,-1]])}
\if{\direct2=0}{
  \text{angle=0,180,360}
  \if{\direct1=0}{
    soleil en haut
    \text{ls=1,0,0,-1}
    \text{list0=3,4,5,6,7,8,1,2}
    \text{signe=-1}
  }
  \if{\direct1=1}{
    soleil en bas
    \text{ls=-1,0,0,1}
    \text{list0=7,8,1,2,3,4,5,6}
    \text{signe=1}
  }
  \text{soleil=linewidth 10
  parallel 0,-(\signe)*\range,0,-(\signe)*(\range-1),1,0,10,yellow
  parallel 0,-(\signe)*\range,0,-(\signe)*(\range-1),-1,0,10,yellow
  linewidth 1}
}
\if{\direct2=1}{
  \text{angle=-90,90,270}
  \if{\direct1=0}{
    soleil à gauche
    \text{ls=0,-1,1,0}
    \text{list0=1,2,3,4,5,6,7,8}
    \text{signe=1}
  }
  \if{\direct1=1}{
    soleil à droite
    \text{ls=0,1,-1,0}
    \text{list0=5,6,7,8,1,2,3,4}
    \text{signe=-1}
  }
  \text{soleil=linewidth 10
parallel -(\signe)*\range,0,-(\signe)*(\range-1),0,0,1,10,yellow
parallel -(\signe)*\range,0,-(\signe)*(\range-1),0,0,-1,10,yellow
linewidth 1}
}
\text{list=\listinit[\list0]}

\text{terre=linewidth 10
fcircle 0,0,\t,black
linewidth 1
text black,0,1,,Terre}
