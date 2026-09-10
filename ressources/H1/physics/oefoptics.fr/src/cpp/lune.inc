utilise dans lune.cpp (qui est un fichier de test), phaseorder.cpp et phase.cpp
dessin de la lune avec rectangle noir et lune grise
\text{phase=}
list (angle terre lune+signe)
  \text{j1=\list[\je]}
  \text{j1=wims(declosing \j1)}
  \text{si=\j1[2]}
  \text{ang=\si>0?\angle[1,2]:\angle[2,3]}
  \text{j=\j1[1]}
  \text{phase=\phase
  frect \centre[1]-1.5*\r,\centre[2]-1.5*\r,\centre[1]+1.5*\r,\centre[2]+1.5*\r,\color4}
  \if{\j!=1 or \si!=1}{
    \if{\direct2=0}{
      \text{phase=\phase
arc \centre,2*\r,2*(\j)*\r,\ang,\color3
arc \centre,2*\r,2*\r,\ang,\color3
filltoborder \centre[1],\centre[2]+\si*(\j+1)*\r/2,\color3,\color3
      }
    }
    \if{\direct2=1}{
      \text{phase=\phase
arc \centre,2*(\j)*\r,-2*\r,\ang,\color3
arc \centre,2*\r,2*\r,\ang,\color3
filltoborder \centre[1]+(\si)*(\j+1)*\r/2,\centre[2],\color3,\color3
      }
    }
  }{
    text{phase=circles \color3,\centre,\r}
  }
