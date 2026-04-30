\integer{offx1=0}
\integer{offy1=0}
\integer{offx2=10}
\integer{offy2=0}
\integer{offx3=20}
\integer{offy3=0}
\integer{offx4=30}
\integer{offy4=0}
\integer{offx5=10}
\integer{offy5=-10}
\integer{offx6=10}
\integer{offy6=10}
\text{face1=
segment 0,5,10,5,blue
segment 5,0,5,10,blue
}
\text{face2=
fpoly orange,0,0,10,0,0,10
}
\text{face20=
fpoly orange,10,10,10,0,0,10
}
\text{face3=
fpoly magenta,0,4,10,4,10,6,0,6
}
\text{face4=
fpoly orange,0,10,5,5,10,10
linewidth 2
segment 0,10,10,0,blue
segment 0,0,10,10,blue
}
\text{face40=
fpoly orange,10,0,5,5,0,0
linewidth 2
segment 0,10,10,0,blue
segment 0,0,10,10,blue
}
\text{face5=
linewidth 2
segment 0,10,10,0,blue
}
\text{face6=
fpoly magenta,0,4,10,4,10,6,0,6
fpoly magenta,4,0,4,10,6,10,6,0
}
\text{faceun=
linewidth 2
segment 0+\offx1,5+\offy1,10+\offx1,5+\offy1,blue
segment 5+\offx1,0+\offy1,5+\offx1,10+\offy1,blue
}
\text{facedeux=
fpoly orange,0+\offx2,0+\offy2,10+\offx2,0+\offy2,0+\offx2,10+\offy2
}
\text{facetrois=
fpoly magenta,0+\offx3,4+\offy3,10+\offx3,4+\offy3,10+\offx3,6+\offy3,0+\offx3,6+\offy3
}
\text{facequatre=
fpoly orange,0+\offx4,10+\offy4,5+\offx4,5+\offy4,10+\offx4,10+\offy4
linewidth 2
segment 0+\offx4,10+\offy4,10+\offx4,0+\offy4,blue
segment 0+\offx4,0+\offy4,10+\offx4,10+\offy4,blue
}
\text{facecinq=
linewidth 2
segment 0+\offx5,10+\offy5,10+\offx5,0+\offy5,blue
}
\text{facesix=
fpoly magenta,0+\offx6,4+\offy6,10+\offx6,4+\offy6,10+\offx6,6+\offy6,0+\offx6,6+\offy6
fpoly magenta,4+\offx6,0+\offy6,4+\offx6,10+\offy6,6+\offx6,10+\offy6,6+\offx6,0+\offy6
}

\text{coteun=
segment 10,5,12,8,blue
segment 11,1.5,11,11.5,blue
}
\text{cotedeux=
fpoly orange,10,0,10,10,12,3
}
\text{cotedeuxB=
fpoly orange,12,3,10,10,12,13
}
\text{cotetrois=
fpoly magenta,10,4,12,7,12,9,10,6
}
\text{cotequatre=
fpoly orange,10,10,11,6.5,12,13
linewidth 2
segment 10,10,12,3,blue
segment 10,0,12,13,blue
}
\text{cotequatreB=
fpoly orange,10,0,11,6.5,12,3
linewidth 2
segment 10,10,12,3,blue
segment 10,0,12,13,blue
}
\text{cotecinq=
linewidth 2
segment 10,10,12,3,blue
}
\text{cotesix=
fpoly magenta,10,4,12,7,12,9,10,6
fpoly magenta,10.8,1.2,11.2,1.8,11.2,11.8,10.8,11.2
}
\text{dessusun=
segment 5,10,7,13,blue
segment 1,11.5,11,11.5,blue
}
\text{dessusdeux=
fpoly orange,2,13,0,10,10,10
}
\text{dessustrois=
fpoly magenta,0.8,11.2,10.8,11.2,11.2,11.8,1.2,11.8
}
\text{dessusquatre=
fpoly orange,2,13,6,11.5,12,13
linewidth 2
segment 2,13,10,10,blue
segment 0,10,12,13,blue
}
\text{dessuscinq=
linewidth 2
segment 0,10,12,13,blue
}
\text{dessuscinqB=
linewidth 2
segment 10,10,2,13,blue
}
\text{dessussix=
fpoly magenta,0.8,11.2,10.8,11.2,11.2,11.8,1.2,11.8
fpoly magenta,4,10,6,13,8,13,6,10
}
\text{data=1,6,2
2,6,3
3,6,4
4,6,1
1,5,40
40,50,3
3,5,20
20,50,1
}

\text{cube=linewidth 3
polyline black,0,0,0,10,10,10,10,0,0,0
polyline black,0,10,2,13,12,13,10,10
polyline black,10,0,12,3,12,13
}

\text{indl=shuffle(8)}
\for{i=1 to 4}{
\text{cedata=row(\indl[\i],\data)}

\integer{nchiffre=\cedata[1]}
\if{\nchiffre=1}{
  \text{face=\face1}
  \text{bdessus=\dessusun}
 }
\if{\nchiffre=2}{
  \text{face=\face2}
  \text{bdessus=\dessusdeux}
 }
\if{\nchiffre=20}{
  \text{face=\face20}
  \text{bdessus=\dessusdeux}
 }
\if{\nchiffre=3}{
  \text{face=\face3}
  \text{bdessus=\dessustrois}
 }

\if{\nchiffre=4}
 {\text{face=\face4}
  \text{bdessus=\dessusquatre}
 }
\if{\nchiffre=40}
 {\text{face=\face40}
  \text{bdessus=\dessusquatre}
 }

\if{\nchiffre=5}
 {\text{face=\face5}
  \text{bdessus=\dessuscinq}
 }

\if{\nchiffre=6}
 {\text{face=\face6}
  \text{bdessus=\dessussix}
 }

\integer{ncote=\cedata[3]}
\if{\ncote=1}
 {\text{cote=\coteun}}
\if{\ncote=2}
 {\text{cote=\cotedeux}}
\if{\ncote=20}
 {\text{cote=\cotedeuxB}}
\if{\ncote=3}
 {\text{cote=\cotetrois}}
\if{\ncote=4}
 {\text{cote=\cotequatre}}
\if{\ncote=40}
 {\text{cote=\cotequatreB}}
\if{\ncote=5}
 {\text{cote=\cotecinq}}
\if{\ncote=6}
 {\text{cote=\cotesix}}
\integer{ndessus=\cedata[2]}
\if{\ndessus=1}
 {\text{dessus=\dessusun}
  \text{bface=\face1}
 }
\if{\ndessus=2}
 {\text{dessus=\dessusdeux}
  \text{bface=\face2}
 }

\if{\ndessus=3}
 {\text{dessus=\dessustrois}
  \text{bface=\face3}
 }

\if{\ndessus=4}
 {\text{dessus=\dessusquatre}
  \text{bface=\face4}
 }

\if{\ndessus=5}
 {\text{dessus=\dessuscinq}
  \text{bface=\face5}
 }
\if{\ndessus=50}
 {\text{dessus=\dessuscinqB}
  \text{bface=\face5}
 }

\if{\ndessus=6}
 {\text{dessus=\dessussix}
  \text{bface=\face6}
 }
 \if{\i=1}
 {
 \text{graph1=<img src="
draw(100,100
xrange -5,15
yrange -5,15
\face
\dessus
\cote
\cube
)"
width="100"
height="100"
alt="" >
}
}
 \if{\i=2}
 {
 \text{graph2=<img src="
draw(100,100
xrange -5,15
yrange -5,15
\bface
\bdessus
\cote
\cube
)"
width="100"
height="100"
alt="" >
}
}
 \if{\i=3}
 {
 \text{graph3=<img src="
draw(100,100
xrange -5,15
yrange -5,15
\face
\dessus
\cote
\cube
)"
width="100"
height="100"
alt="" >
}
 }
 \if{\i=4}
 {
 \text{graph4=<img src="
draw(100,100
xrange -5,15
yrange -5,15
\bface
\bdessus
\cote
\cube
)"
width="100"
height="100"
alt="" >

}
}

}
