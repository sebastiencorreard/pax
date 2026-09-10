\text{lstsigne=<font size=+2>+</font>,<font size=+2>-</font>}
\text{lstvar=\(\nearrow),\(\searrow)}
\text{lstsing=\(> 0),\(< 0),0}
\text{size=50x50x1}

#if defined TARGET_nbsol1
\title{TITRE 1}
\integer{a=randint(1..5)*randint(1,-1)}
\integer{b=randint(1..5)*randint(1,-1)}
%%%%
integer{a=1}
integer{b=1}
%%%%
\function{f=\a*x^4+\b*x^3}
\function{fder=4*\a*x^3+3*\b*x^2}
\rational{sing=simplify(-3*\b/(4*\a))}
\rational{bads=-\b/\a}
\if{\sing>0}
   {
    \text{repvar=\a>0?2,2,1:1,1,2}
    \text{tbornes=\a>0?\(L_2 > 0) et \( L_1 > 0):\(L_2 < 0) et \( L_1 < 0)}
   }
   {
    \text{repvar=\a>0?2,1,1:1,2,2}
    \text{tbornes=\a>0?\(L_2 > 0) et \( L_1 > 0):\(L_2 < 0) et \( L_1 < 0)}
   }

\text{sv=\lstvar[\repvar]}
\text{sd=\lstsigne[\repvar]}
\text{lstrep=\lstvar,\lstsigne}

\integer{x1=floor(\sing)}
\integer{x2=ceil(\sing)}
\if{\x1=\x2}
 {
%% on va calculer directemnt f(x0)
%%

 \integer{y0=evalue(\f,x=\sing)}
 \integer{nbsol=randint(0,2)}
 \if{\nbsol=2}
  {
   \integer{d=\a>0?randint(\y0+2..\y0+5):randint(\y0-5..\y0-2)}
  }
  {
   \integer{d=\a<0?randint(\y0+2..\y0+5):randint(\y0-5..\y0-2)}
  }
 \integer{yy0=\y0-\d}
 \integer{sx0=\yy0>0?1:2}
  \text{mstep=r1,r2,r3,r4,r5,r6,r7,r8,r13,r12}
 }
 {
  \integer{yy1=evalue(\f,x=\x1)}
  \integer{yy2=evalue(\f,x=\x2)}
  \integer{z1=\yy1>\yy2?\yy2:\yy1}
  \integer{z2=\yy1>\yy2?\yy1:\yy2}
  \integer{nbsol=2}
   \integer{plage=\z2-\z1-4}
   \if{\plage<0}
    {
     \integer{d=randint(\z1+3..\z1+10)}
    }
    {
     \integer{d=randint(\z1+2..\z2-2)}
    }
   \integer{d=\a<0?-\d}
   \integer{z=\z1-\d}
  \text{mstep=r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12}
 }
\function{g=maxima(\a*x^4+\b*x^3-\d)}
\text{ft=texmath(\g)}
\text{tencad=\a>0?minoration:majoration}
\text{symb=\a>0?\(<):\(>)}
\rational{singg=\sing>0?0:\sing}
\rational{singd=\sing<0?0:\sing}

\steps{\mstep}
#endif

#if defined TARGET_nbsol2 || defined TARGET_nbsol5
#if defined TARGET_nbsol2
\title{TITRE 2}
\text{size2=\size}
#endif
#if defined TARGET_nbsol5
\title{TITRE 5}
\text{size2=3}
#endif
\integer{x0=randint(-3..3)}
\integer{x1=\x0+2*randint(-2..2)}
\integer{x2=\x1+2*randint(1..3)}
\integer{a=randint(1..3)*randint(1,-1)}
\function{g=maxima(\a*x^3-3*\a*(\x1+\x2)*x^2/2+3*\a*\x1*\x2*x)}
\integer{y1=evalue(\g,x=\x1)}
\integer{y2=evalue(\g,x=\x2)}
\integer{yy1=\y1>\y2?\y2:\y1}
\integer{yy2=\y1>\y2?\y1:\y2}
\integer{s=\y1*\y2}
\integer{d=0}
\integer{nbsol=\s=0?2:randint(1,3)}
\if{\nbsol=1}
  { \integer{d=\s<0?random(-\yy1+randint(1..3),-\yy2-randint(1..3))}
    \integer{z1=\yy1+\d}
    \text{sg=\z1>0?\lstsing[1],\lstsing[1]:\lstsing[2],\lstsing[2]}
  }
\if{\nbsol=3}
  { \integer{d=\s>0?-randint(\yy1+1..\yy2-1)}
    \text{sg=\a>0?\lstsing[1,2]:\lstsing[2,1]}
  }
\if{\nbsol=2}
 {
  \if{\y1=0}
   { \text{sg=\a>0?\lstsing[3,2]:\lstsing[3,1]} }
   { \text{sg=\a>0?\lstsing[1,3]:\lstsing[2,3]} }
 }
\function{f=maxima(\g+\d)}
\text{ft=texmath(\f)}

\text{repvar=\a>0?1,2,1:2,1,2}
\text{tbornes=\a>0?\(L_1 < 0 < L_2) :\(L_1 > 0 > L_2)}
\text{sv=\lstvar[\repvar]}
\text{sd=\lstsigne[\repvar]}
\text{lstrep=\lstvar,\lstsigne,\lstsing}

#endif
#if defined TARGET_nbsol5
\integer{k=randint(1..4)}
\if{\k=1}
  {
   \integer{bg=\x1-randint(1..3)}
   \integer{bd=\x2+randint(1..3)}
  }
\if{\k=2}
  {
   \integer{bg=\x1-randint(1..3)}
   \integer{bd=randint(\x1+1..\x2-1)}
  }
\if{\k=3}
  {
   \integer{bd=\x2+randint(1..3)}
   \integer{bg=randint(\x1+1..\x2-1)}
  }
\if{\k=4}
  {
   \integer{bg=\x1+1}
   \integer{bd=\x2-1}
  }
\integer{zg=evalue(\f,x=\bg)}
\integer{zd=evalue(\f,x=\bd)}
\integer{u1=\y1+\d}
\integer{u2=\y2+\d}
\if{\k=1}
  {
   \text{zl=\zg,\zd,\u1,\u2}
   \text{zl=wims(sort numeric list \zl)}
   \integer{z1=\zl[1]}
   \integer{z2=\zl[-1]}
  }
\if{\k=4}
  {
   \integer{z1=\zg<\zd?\zg:\zd}
   \integer{z2=\zg<\zd?\zd:\zg}
  }
\if{\k=2}
  {
   \text{zl=\zg,\zd,\u1}
   \text{zl=wims(sort numeric list \zl)}
   \integer{z1=\zl[1]}
   \integer{z2=\zl[-1]}
  }
\if{\k=3}
  {
   \text{zl=\zg,\zd,\u2}
   \text{zl=wims(sort numeric list \zl)}
   \integer{z1=\zl[1]}
   \integer{z2=\zl[-1]}
  }

#endif

#if defined TARGET_nbsol3
%% on veut que la somme x1+x2 soit un multiple de 3
\text{x1l=-6,-6,-6,-5,-5,-5,-4,-4,-4,-3,-3,-2,-2,-1,-1,1,2}
\text{x2l=-3,3,6,2,-1,-4,1,-2,-5,3,6,-1,-4,4,1,2,4}
\integer{i=randint(1..items(\x1l))}
\integer{x1=\x1l[\i]}
\integer{x2=\x2l[\i]}

\integer{a=randint(1..3)*randint(1,-1)}
\function{g=maxima(\a*x^4-4*\a*(\x1+\x2)*x^3/3+2*\a*\x1*\x2*x^2)}
\text{xl=\x1,\x2,0}
\text{xl=wims(sort numeric list \xl)}
\integer{x1=\xl[1]}
\integer{x2=\xl[2]}
\integer{x3=\xl[3]}

\integer{y1=evalue(\g,x=\x1)}
\integer{y2=evalue(\g,x=\x2)}
\integer{y3=evalue(\g,x=\x3)}
\text{yl=\y1,\y2,\y3}
\text{yl=wims(sort numeric list \yl)}
%%attention à la suppression de doublon
\integer{n=items(\yl)}
\if{\n=2}
  {
  \text{yl=\a>0?\yl[1,1,2]:\yl[1,2,2]}
  }
\integer{yy1=\yl[1]}
\integer{yy2=\yl[2]}
\integer{yy3=\yl[3]}
\integer{nbsol=randint(0..4)}
%%integer{nbsol=4}
\if{\nbsol=0}
 {
  \if{\a>0}
   {
    \integer{d=\yy1>0?0:-\yy1+randint(1..5)}
    \text{sg=\lstsing[1,1,1]}
   }
   {
    \integer{d=\yy3<0?0:-\yy3-randint(1..5)}
    \text{sg=\lstsing[2,2,2]}
   }
 }
\if{\nbsol=1}
 {
  \if{\a>0}
   {
    \integer{d=\yy1>0?0:-\yy1}
    \text{sg=\y1=\yy1?\lstsing[3,1,1]:\lstsing[1,1,3]}

    \integer{nbsol=\yy1=\yy2?2}
    \text{sg=\yy1=\yy2?\lstsing[3,1,3]}
   }
   {
    \integer{d=\yy3<0?0:-\yy3}
    \text{sg=\y1=\yy3?\lstsing[3,2,2]:\lstsing[2,2,3]}
    \integer{nbsol=\yy2=\yy3?2}
    \text{sg=\yy2=\yy3?\lstsing[3,2,3]}
   }
 }
\if{\nbsol=2}
 {
  \if{\a>0}
   {
    \integer{d=\yy1=\yy2?-\yy1:-randint(\yy1+1..\yy2-1)}
    \text{sg=\y1=\yy1?\lstsing[2,1,1]:\lstsing[1,1,2]}
    \text{sg=\yy1=\yy2?\lstsing[3,1,3]}
   }
   {
    \integer{d=\yy2=\yy3?-\yy3:-randint(\yy2+1..\yy3-1)}
    \text{sg=\y1=\yy2?\lstsing[2,2,1]:\lstsing[1,2,2]}
    \text{sg=\yy3=\yy2?\lstsing[3,2,3]}
   }
 }

\if{\nbsol=3}
 {
    \integer{d=\a>0?-\yy3:-\yy1}
    \text{sg=\a>0?\lstsing[2,3,2]:\lstsing[1,3,1]}
 }
\if{\nbsol=4}
 {
    \integer{d=\a>0?-randint(\yy2+1..\yy3-1):-randint(\yy1+1..\yy2-1)}
    \text{sg=\a>0?\lstsing[2,1,2]:\lstsing[1,2,1]}

 }
\function{f=maxima(\g+\d)}
\text{ft=texmath(\f)}

\text{repvar=\a>0?2,1,2,1:1,2,1,2}
\text{tbornes=\a>0?\(L_2 > 0) et \( L_1 > 0):\(L_2 < 0) et \( L_1 < 0)}

\text{sv=\lstvar[\repvar]}
\text{sd=\lstsigne[\repvar]}
\text{lstrep=\lstvar,\lstsigne,\lstsing}

#endif

#if defined TARGET_nbsol4
\title{TITRE 4}
\integer{x0=randint(-3..3)}
\integer{x1=\x0+2*randint(-2..2)}
\integer{x2=\x1+2*randint(1..3)}
\text{Dl=3,5,7,8,11,13}
\text{ol=1,2,2,2,3,3}
\integer{i=randint(1..6)}
\integer{D=\Dl[\i]}
\integer{o=\ol[\i]}
\real{x1=\x0-sqrt(\D)}
\real{x2=\x0+sqrt(\D)}
\integer{xa1=\x0-\o-1}
\integer{xb1=\x0-\o}
\integer{xa2=\x0+\o}
\integer{xb2=\x0+\o+1}
\integer{a=randint(1..3)*randint(1,-1)}
\function{g=maxima(\a*x^3-6*\a*\x0*x^2/2+3*\a*((\x0)^2-\D)*x)}
\real{y1=evalue(\g,x=\x1)}
\real{y2=evalue(\g,x=\x2)}
\real{yy1=\y1>\y2?\y2:\y1}
\real{yy2=\y1>\y2?\y1:\y2}
\real{s=\y1*\y2}
\integer{d=0}
\integer{nbsol=\s=0?2:randint(1,3)}
%%integer{nbsol=1}
\if{\nbsol=1}
  { \integer{d=\s<0?random(-\yy1+randint(1..3),-\yy2-randint(1..3))}
    \integer{z1=\yy1+\d}
    \text{sg=\z1>0?\lstsing[1],\lstsing[1]:\lstsing[2],\lstsing[2]}
  }
\if{\nbsol=3}
  { \integer{d=\s>0?-randint(\yy1+1..\yy2-1)}
    \text{sg=\a>0?\lstsing[1,2]:\lstsing[2,1]}
  }
\if{\nbsol=2}
 {
  \if{\y1=0}
   { \text{sg=\a>0?\lstsing[3,2]:\lstsing[3,1]} }
   { \text{sg=\a>0?\lstsing[1,3]:\lstsing[2,3]} }
 }
\function{f=maxima(\g+\d)}
\text{ft=texmath(\f)}

\text{repvar=\a>0?1,2,1:2,1,2}
\text{tbornes=\a>0?\(L_1 < 0 < L_2) :\(L_1 > 0 > L_2)}
\text{sv=\lstvar[\repvar]}
\text{sd=\lstsigne[\repvar]}
\text{lstrep=\lstvar,\lstsigne,\lstsing}

#endif

