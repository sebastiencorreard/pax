target=oefsymfig1
#define NUM 1
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\keywords{symmetry}
\text{tri1=draw(200,200
animate 40,0.01,0
xrange -100,100
yrange -100,100
linewidth 2
rotate 30
segment -150,0,150,0, black
segment -50,40,50,80, black
segment -52,44,-48,36, black
segment 48,84,52,76, black
text black,-60,50,medium,A
text black,35,95,medium,B
text black,95,0,medium,(d)
)}

\text{tri2=draw(200,200
animate 40,0.01,0
xrange -100,100
yrange -100,100
linewidth 2
rotate 30
segment -150,0,150,0, black
segment -50,40,50,80, black
segment -52,44,-48,36, black
segment 48,84,52,76, black
text black,-60,50,medium,A
text black,35,95,medium,B
text black,95,0,medium,(d)
triangle 80-130*s,0,140-130*s,0,80-s*130,104,blue
triangle 90-130*s,10,120-130*s,10,90-s*130,55,blue
fill 85-130*s,5,grey
fill 85-130*s,85,grey)}

\text{tri3=draw(200,200
animate 40,0.01,0
xrange -100,100
yrange -100,100
linewidth 2
rotate 30
segment -150,0,150,0, black
segment -50,40,50,80, black
segment -52,44,-48,36, black
segment 48,84,52,76, black
text black,-60,50,medium,A
text black,35,95,medium,B
text black,95,0,medium,(d)
triangle -50,0,11,0,-50,104,blue
triangle -40,10,-10,10,-40,55,blue
fill -45,5,grey
fill -45,85,grey
segment -50,70,-50,50-140*s,black)}

\text{tri4=draw(200,200
animate 40,0.01,0
xrange -100,100
yrange -100,100
linewidth 2
rotate 30
segment -150,0,150,0, black
segment -50,40,50,80, black
segment -52,44,-48,36, black
segment 48,84,52,76, black
text black,-60,50,medium,A
text black,35,95,medium,B
text black,95,0,medium,(d)
linewidth 1
segment -50,70,-50,-90,black
linewidth 2
arc -50,0,80,80,500-s*220,500,red)}

\text{tri5=draw(200,200
animate 40,0.01,0
xrange -100,100
yrange -100,100
linewidth 2
rotate 30
segment -150,0,150,0, black
segment -50,40,50,80, black
segment -52,44,-48,36, black
segment 48,84,52,76, black
text black,-60,50,medium,A
text black,35,95,medium,B
text black,95,0,medium,(d)
linewidth 1
segment -50,70,-50,-90,black
arc -50,0,80,80,280,320,black
linewidth 2
triangle 80-30*s,0,140-30*s,0,80-s*30,104,blue
triangle 90-30*s,10,120-30*s,10,90-s*30,55,blue
fill 85-30*s,5,grey
fill 85-30*s,85,grey)}

\text{tri6=draw(200,200
animate 40,0.01,0
xrange -100,100
yrange -100,100
linewidth 2
rotate 30
segment -150,0,150,0, black
segment -50,40,50,80, black
segment -52,44,-48,36, black
segment 48,84,52,76, black
text black,-60,50,medium,A
text black,35,95,medium,B
text black,95,0,medium,(d)
linewidth 1
segment -50,70,-50,-90,black
arc -50,0,80,80,280,320,black
linewidth 2
triangle 50,0,110,0,50,104,blue
triangle 60,10,90,10,60,55,blue
fill 55,5,grey
fill 55,85,grey
segment 50,90,50,50-160*s,black
)}
\text{tri7=draw(200,200
animate 40,0.01,0
xrange -100,100
yrange -100,100
linewidth 2
rotate 30
segment -150,0,150,0, black
segment -50,40,50,80, black
segment -52,44,-48,36, black
segment 48,84,52,76, black
text black,-60,50,medium,A
text black,35,95,medium,B
text black,95,0,medium,(d)
linewidth 1
segment -50,70,-50,-90,black
arc -50,0,80,80,280,320,black
segment 50,90,50,-110,black
linewidth 2
arc 50,0,160,160,100,100+s*220,red
)}

\text{tri8=draw(200,200
animate 40,0.01,0
xrange -100,100
yrange -100,100
linewidth 2
rotate 30
segment -150,0,150,0, black
segment -50,40,50,80, black
segment -52,44,-48,36, black
segment 48,84,52,76, black
text black,-60,50,medium,A
text black,35,95,medium,B
text black,95,0,medium,(d)
linewidth 1
segment -50,70,-50,-90,black
arc -50,0,80,80,280,320,black
segment 50,90,50,-110,black
arc 50,0,160,160,280,320,black
text black,-60,-45,medium,A'
text black,35,-90,medium,B'
)}

\text{tri9=draw(200,200
animate 40,0.01,0
xrange -100,100
yrange -100,100
linewidth 2
rotate 30
segment -150,0,150,0, black
segment -50,40,50,80, black
segment -52,44,-48,36, black
segment 48,84,52,76, black
text black,-60,50,medium,A
text black,35,95,medium,B
text black,95,0,medium,(d)
linewidth 1
segment -50,70,-50,-90,black
arc -50,0,80,80,280,320,black
segment 50,90,50,-110,black
arc 50,0,160,160,280,320,black
text black,-60,-45,medium,A'
text black,35,-90,medium,B'
linewidth 2
segment -50,-40,-50+100*s,-40-40*s,black)}

\text{tri=\tri1,\tri2,\tri3,\tri4,\tri5,\tri6,\tri7,\tri8,\tri9}
\text{fig=}
\for{j=1 to 9}{
  \text{fig=\fig<img src="\tri[\j]" alt="\name_step \j">,}
}
\statement{
  \name_enonce
  <ul class="inline wims_nopuce">
  \for{k=1 to 9}{<li><div>\name_step \k <br>\fig[\k] <br>\embed{r\k,250x80}</div></li>}
  </ul>
}

\answer{}{\rep[1]}{type=dragfill}{option=shuffle}
\answer{}{\rep[2]}{type=dragfill}
\answer{}{\rep[3]}{type=dragfill}
\answer{}{\rep[4]}{type=dragfill}
\answer{}{\rep[5]}{type=dragfill}
\answer{}{\rep[6]}{type=dragfill}
\answer{}{\rep[7]}{type=dragfill}
\answer{}{\rep[8]}{type=dragfill}
\answer{}{\rep[9]}{type=dragfill}
