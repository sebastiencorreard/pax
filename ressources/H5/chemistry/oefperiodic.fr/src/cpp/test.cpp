target test

#include "header.inc"
#include "confparm.inc"

\title{test}

\text{list=wims(record 0 of position)}
\text{colors=white,orange,lightgrey,green,yellow,skyblue,magenta}
\text{drawsrc=}
\integer{xs=30}
\integer{ys=30}
\for{e=1 to \end}{
  \text{ele=row(\e,\list)}
  \integer{x=\ele[4]*\xs}
  \integer{y=\ele[3]*\ys}
  \integer{y=\ele[3]>8?\y+5}
  \integer{x=\ele[3]>8?\x+\xs*2}
  \text{drawsrc=\drawsrc
   frect \x,\y,\x+\xs,\y+\ys,\colors[\ele[5]]
   rect \x,\y,\x+\xs,\y+\ys,black
   text black,\x+10,\y+10,medium,\ele[2]}
}
\for{i=1 to 7}{
  \text{drawsrc=\drawsrc
   text black,10,\i*\ys+10,large,\i
   text black,19*\xs+10,\i*\ys+10,large,\i}
}
\text{ylist=0,1,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,0}
\for{i=1 to 18}{
  \text{drawsrc=\drawsrc
   text black,\i*\xs+10,\ylist[\i]*\ys+4,large,\i}
}
\for{i=1 to 15}{
  \text{drawsrc=\drawsrc
   text black,(\i+2)*\xs+10,\ys*8+20,small,\i}
}
\text{drawsrc=\drawsrc
text black,3*\xs+13,6*\ys+10,large,*
text black,3*\xs+10,7*\ys+10,large,**
text black,2*\xs+13,9*\ys+10,large,*
text black,2*\xs+10,10*\ys+10,large,**
}

\statement{
  <p>\draw{600,360}{
  \drawsrc
  }</p>

}
