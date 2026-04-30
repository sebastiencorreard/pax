\text{chiffreun=<img src="
draw(40,40
xrange 0,10
yrange 0,10
fcircle 5,5,8,red
)"
width="40"
height="40"
alt="">
}
\text{chiffredeux=<img src="
draw(40,40
xrange 0,10
yrange 0,10
fcircle 8,2,8,red
fcircle 2,8,8,red
)"
width="40"
height="40"
alt="">
}
\text{chiffretrois=<img src="
draw(40,40
xrange 0,10
yrange 0,10
fcircle 2,2,8,red
fcircle 5,5,8,red
fcircle 8,8,8,red
)"
width="40"
height="40"
alt="">
}
\text{chiffrequatre=<img src="
draw(40,40
xrange 0,10
yrange 0,10
fcircle 2,2,8,red
fcircle 2,8,8,red
fcircle 8,8,8,red
fcircle 8,2,8,red
)"
width="40"
height="40"
alt="">
}
\text{chiffrecinq=<img src="
draw(40,40
xrange 0,10
yrange 0,10
fcircle 2,2,8,red
fcircle 2,8,8,red
fcircle 8,8,8,red
fcircle 8,2,8,red
fcircle 5,5,8,red
)"
width="40"
height="40"
alt="">
}
\text{chiffresix=<img src="
draw(40,40
xrange 0,10
yrange 0,10
fcircle 2,2,8,red
fcircle 2,8,8,red
fcircle 8,8,8,red
fcircle 8,2,8,red
fcircle 2,5,8,red
fcircle 8,5,8,red
)"
width="40"
height="40"
alt="">
}
\text{coteun=
fcircle 11,-8.5,8,red
}
\text{cotedeux=
fcircle 10.8,-12.5,8,red
fcircle 11.6,-4.5,8,red
}
\text{cotetrois=
fcircle 10.8,-12.5,8,red
fcircle 11.3,-8.5,8,red
fcircle 11.6,-4.5,8,red
}
\text{cotequatre=
fcircle 10.8,-12.5,8,red
fcircle 10.8,-6.5,8,red
fcircle 11.6,-4.5,8,red
fcircle 11.6,-10.5,8,red
}
\text{cotecinq=
fcircle 10.8,-12.5,8,red
fcircle 10.8,-6.5,8,red
fcircle 11.2,-9,8,red
fcircle 11.6,-4.5,8,red
fcircle 11.6,-10.5,8,red
}
\text{cotesix=
fcircle 10.8,-12.5,8,red
fcircle 10.8,-6.5,8,red
fcircle 10.8,-9.5,8,red
fcircle 11.6,-7.5,8,red
fcircle 11.6,-4.5,8,red
fcircle 11.6,-10.5,8,red
}
\text{dessusun=
fcircle 6.5,-3.5,8,red
}
\text{dessusdeux=
fcircle 3,-3,8,red
fcircle 8,-4,8,red
}
\text{dessustrois=
fcircle 3,-3,8,red
fcircle 8,-4,8,red
fcircle 5.5,-3.5,8,red
}
\text{dessusquatre=
fcircle 3,-3,8,red
fcircle 8,-4,8,red
fcircle 2,-4,8,red
fcircle 9,-3,8,red
}
\text{dessuscinq=
fcircle 3,-3,8,red
fcircle 8,-4,8,red
fcircle 2,-4,8,red
fcircle 9,-3,8,red
fcircle 5,-3.5,8,red
}
\text{dessussix=
fcircle 3,-3,8,red
fcircle 8,-4,8,red
fcircle 2,-4,8,red
fcircle 9,-3,8,red
fcircle 5,-4,8,red
fcircle 6,-3,8,red
}
\text{data=1,2,3
3,2,6
6,2,4
4,2,1
1,5,4
3,5,1
6,5,3
4,5,6
3,1,2
2,1,4
4,1,5
5,1,3
2,6,3
3,6,5
5,6,4
4,6,2
1,3,5
5,3,6
6,3,2
2,3,1
1,4,2
2,4,6
6,4,5
5,4,1
}
\text{cedata=randomrow(\data)}

\integer{nchiffre=\cedata[1]}
\if{\nchiffre=1}
 {\text{chiffre=\chiffreun}}
\if{\nchiffre=2}
 {\text{chiffre=\chiffredeux}}
\if{\nchiffre=3}
 {\text{chiffre=\chiffretrois}}
\if{\nchiffre=4}
 {\text{chiffre=\chiffrequatre}}
\if{\nchiffre=5}
 {\text{chiffre=\chiffrecinq}}
\if{\nchiffre=6}
 {\text{chiffre=\chiffresix}}
\integer{ncote=\cedata[3]}
\if{\ncote=1}
 {\text{cote=\coteun}}
\if{\ncote=2}
 {\text{cote=\cotedeux}}
\if{\ncote=3}
 {\text{cote=\cotetrois}}
\if{\ncote=4}
 {\text{cote=\cotequatre}}
\if{\ncote=5}
 {\text{cote=\cotecinq}}
\if{\ncote=6}
 {\text{cote=\cotesix}}
\integer{ndessus=\cedata[2]}
\if{\ndessus=1}
 {\text{dessus=\dessusun}}
\if{\ndessus=2}
 {\text{dessus=\dessusdeux}}
\if{\ndessus=3}
 {\text{dessus=\dessustrois}}
\if{\ndessus=4}
 {\text{dessus=\dessusquatre}}
\if{\ndessus=5}
 {\text{dessus=\dessuscinq}}
\if{\ndessus=6}
 {\text{dessus=\dessussix}}

