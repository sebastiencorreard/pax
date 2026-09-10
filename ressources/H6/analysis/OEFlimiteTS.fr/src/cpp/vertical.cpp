target=vertical6
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
#define NUM
#include "lang_titles.inc"
\text{infd=\(+\infty)}
\text{infg=\(-\infty)}

\integer{a=randint(-4..-1)}
\integer{b=randint(1..4)}
\integer{c=randint(1..3)*10}
\integer{d=randint(-3..3)}
\integer{d2=-\d}
\rational{e=randint(0.2,0.5,0.8,0.3)}
\text{data=\c/((x-\a)^2*(x-\b)^2)+\d,\a,\infd,\b,\infd,+\infty,\d,\d,
-\c/((x-\a)^2*(x-\b)^2)+\d,\a,\infg,\b,\infg,+\infty,\d,\d,
\c/((x-\a)*(x-\b)^2)+\d,\a,\sans,\b,\infd,-\infty,\d,\d,
\c/((\a-x)*(x-\b)^2)+\d,\a,\sans,\b,\infg,+\infty,\d,\d,
-\c/((x-\a)*(x-\b)^2)+\d,\a,\sans,\b,\infg,-\infty,\d,\d,
-\c/((\a-x)*(x-\b)^2)+\d,\a,\sans,\b,\infd,-\infty,\d,\d,
\c/((x-\a)^2*(x-\b))+\d,\a,\infg,\b,\sans,+\infty,\d,\d,
\c/((\a-x)^2*(\b-x))+\d,\a,\infd,\b,\sans,+\infty,\d,\d,
-\c/((x-\a)^2*(x-\b))+\d,\a,\infd,\b,\sans,+\infty,\d,\d,
-\c/((\a-x)^2*(\b-x))+\d,\a,\infg,\b,\sans,-\infty,\d,\d,

\c/((x-\a)^2*(x-\b)^2)+\e*x+\d,\a,\infd,\b,\infd,+\infty,\infd,\e*x+\d
-\c/((x-\a)^2*(x-\b)^2)-\e*x+\d,\a,\infg,\b,\infg,+\infty,\infg,-\e*x+\d
\c/((x-\a)*(x-\b)^2)+\e*x+\d,\a,\sans,\b,\infd,-\infty,\infg,\e*x+\d
\c/((\a-x)*(x-\b)^2)-\e*x+\d,\a,\sans,\b,\infg,-\infty,\infd,-\e*x+\d
-\c/((x-\a)*(x-\b)^2)+\e*x+\d,\a,\sans,\b,\infg,+\infty,\infd,\e*x+\d
-\c/((\a-x)*(x-\b)^2)-\e*x+\d,\a,\sans,\b,\infd,+\infty,\infg,-\e*x+\d
\c/((x-\a)^2*(x-\b))+\e*x+\d,\a,\infg,\b,\sans,+\infty,\infd,\e*x+\d
\c/((\a-x)^2*(\b-x))-\e*x+\d,\a,\infd,\b,\sans,+\infty,\infg,-\e*x+\d
-\c/((x-\a)^2*(x-\b))-\e*x+\d,\a,\infd,\b,\sans,+\infty,\infg,-\e*x+\d
-\c/((\a-x)^2*(\b-x))+\e*x+\d,\a,\infg,\b,\sans,+\infty,\infd,\e*x+\d
}
\text{eqa=x=\a}
\text{eqb=x=\b}

\integer{i=randint(1..rows(\data)/2)}
///integer{i=10}
\text{cedata=row(\i,\data)}
\text{f=maxima(\cedata[1])}
\text{ft=texmath(\f)}
\text{g=\cedata[8]}
\real{ybor=abs(evalue(\f,x=0))}
\integer{yb=\ybor<6?7:\ybor+2}
\text{lstrep=\infd,\infg,0,\d,\d2,\sans}
\text{lstrep=wims(listunique \lstrep)}

\text{dessin=
 xrange -7,7
 yrange -\yb,\yb
 parallel -7,-\yb,7,-\yb,0,1,2*\yb+1,gray
 parallel -7,-\yb,-7,\yb,1,0,15,gray
 arrow -7,0,7,0,10,black
 arrow 0,-\yb,0,\yb,10,black
 text black,0.8,-0.5,small,1
 text black,-0.3,0.8,small,1
 segment -0.1,1,0.1,1,black
 segment 1,0.1,1,-0.1,black
 linewidth 2
 arrow 0,0,0,1,5,black
 arrow 0,0,1,0,5,black
 linewidth 3
 plot red,\f
 plot green,\g
 dsegment \a,-\yb,\a,\yb,green
 dsegment \b,-\yb,\b,\yb,green
}

#if defined TARGET_vertical6
\text{datarep=1,
2,
3,
4,
4,
3,
5,
6,
6,
5,
}
\text{cerep=row(\i,\datarep)}
\integer{n=items(\cerep)}
\text{rep=item(1..\n-1,\cerep)}
\text{lstrep=}
\text{lstrow=1,2,3,4,7,8}
\for{j in \lstrow}{
 \text{ced=row(\j,\data)}
 \text{ced=\(texmath(maxima(\ced[1])))}
 \text{lstrep=wims(append item \ced to \lstrep)}
}
\statement{
  <div class="wims_columns">
 <div class="medium_size img_col">
 \draw{300,300}{\dessin}
 </div><div class="medium_size text_col">
  Cocher l'expression algébrique pouvant avoir une représentation graphique
  telle que celle dessinée ci-contre:
  <ul><li>
  \embed{reply1,1}</li><li>\embed{reply1,2}
  </li><li>
  \embed{reply1,3}</li><li>\embed{reply1,4}
  </li><li>
  \embed{reply1,5}</li><li>\embed{reply1,6}
  </li></ul>
  </div></div>
}
\answer{expression algébrique possible}{\rep;\lstrep}{type=radio}
#endif
