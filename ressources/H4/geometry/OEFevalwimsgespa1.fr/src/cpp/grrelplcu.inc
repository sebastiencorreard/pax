\integer{goodrep=3}
\text{facedest= wims(listintersect \faces[\indpt1;] and \faces[\indpt2;])}
\if{\face isitemof \facedest}{ \integer{goodrep=2}}{
  \if{\face isitemof 1,3,5}{\integer{facepar=\face+1}}{\integer{facepar=\face-1}}
  \if{\facepar isitemof \facedest}{ \integer{goodrep=1}}{
    %%%%%tester droites des milieux
    \if{ (\face=1 or \face=2) and (\pt1 isitemof (Q,R,S,T)) and (\pt2 isitemof (Q,R,S,T))}{
      \integer{goodrep=1}}
    \if{ (\face=3 or \face=4) and (\pt1 isitemof (O,P,K,L)) and (\pt2 isitemof (O,P,K,L))}{
      \integer{goodrep=1}}
    \if{ (\face=1 or \face=2) and (\pt1 isitemof (I,J,M,N)) and (\pt2 isitemof (I,J,M,N))}{
      \integer{goodrep=1}}
  }
}
