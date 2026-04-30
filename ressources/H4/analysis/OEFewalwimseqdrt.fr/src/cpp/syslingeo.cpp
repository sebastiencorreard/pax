target=syslingeo1 syslingeo2 syslingeo3 syslingeo4 syslingeo5
#include "author.inc"
#define TITRE Interprétation géométrique
\keywords{line, line_equation,linear_system}
\text{lstrep=Aucun couple, un unique couple, une infinité de couples}
\text{cadre=
  xrange -10,10
  yrange -10,10
  parallel -10,-10,-10,10,1,0,21,gray
  parallel -10,-10,10,-10,0,1,21,gray
}
\text{axes=
  linewidth 2
  arrow -10,0,10,0,10,black
  arrow 0,-10,0,10,10,black
  linewidth 3}
\text{repere=
  arrow 0,0,1,0,5,red
  arrow 0,0,0,1,5,red
  text red,0.2,-0.8,medium,i
  text red,-0.8,0.2,medium,j
  }

#if defined TARGET_syslingeo1
\title{TITRE I}
\text{data=\(D_1\) et \(D_2\) sont deux droites strictement parallèles,ne possède aucun couple solution,1
  \(D_1\) et \(D_2\) sont deux droites confondues,possède une infinité de couples solutions,1
  \(D_1\) et \(D_2\) sont deux droites sécantes,possède un unique couple solution,1
  \(D_1\) et \(D_2\) sont deux droites strictement parallèles, possède une infinité de couples solutions,2
  \(D_1\) et \(D_2\) sont deux droites confondues, ne possède aucun couple solution,2
  \(D_1\) et \(D_2\) sont deux droites sécantes,ne possède aucun couple solution,2
  \(D_1\) et \(D_2\) sont deux droites sécantes,a pour solution l'abscisse du point d'intersection de \(D_1\) et \(D_2\),2
  \(D_1\) et \(D_2\) sont deux droites sécantes,a pour solution le couple de coordonnées du point d'intersection de \(D_1\) et \(D_2\),1
}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\text{quest2=\cedata[2]}
\integer{rep=\cedata[3]}

\statement{
  Cocher la bonne réponse.
<div class="wimscenter">Lorsque \quest,
  le système composé des deux équations des droites \(D_1\) et \(D_2\) \quest2.
</div>
<div class="wimscenter">\embed{reply1}</div>
}
\answer{Vrai Faux}{\rep;Vrai,Faux}{type=radio}
#endif

#if defined TARGET_syslingeo3
\title{TITRE III}
\integer{a1=random(0..9)*randint(1,-1)}
\integer{b1=random(0..9)*randint(1,-1)}
\integer{b1=\b1=0 and \a1=0?1}
\integer{c1=random(0..9)*randint(1,-1)}
\text{e1=texmath(maxima(\a1*x+\b1*y))}
\rational{u1=\b1=0?1:simplify(-(\a1) / (\b1))}
\rational{v1=\b1=0?1:simplify((\c1) / (\b1))}
\rational{w1=\a1=0?1:simplify((\c1) / (\a1))}
\text{f1=\c1}
\text{eqd1=\b1=0?texmath(x=\w1):texmath(y=maxima(\u1*x +(\v1)) )}
\text{eqd3=\b1=0?texmath(x=-\w1):texmath(y=maxima(-\u1*x -(\v1)) )}
\text{e3=texmath(maxima(\a1*x-\b1*y))}
\text{f3=\c1}
\integer{a2=random(0..9)*randint(1,-1)}
\integer{b2=random(0..9)*randint(1,-1)}
\if{\a1=\a2 and \b1=\b2}
 {\integer{a2=2*\a1+1}}
\integer{b2=\b2=0 and \a2=0?1}
\integer{c2=random(0..9)*randint(1,-1)}
\integer{c2=\c2=\c1?2*\c1+1}
\text{e2=texmath(maxima(\a2*x+\b2*y))}
\text{f2=\c2}
\rational{u2=\b2=0?1:simplify(-(\a2) / (\b2))}
\rational{v2=\b2=0?1:simplify((\c2) / (\b2))}
\rational{w2=\a2=0?1:simplify((\c2) / (\a2))}
\text{eqd2=\b2=0?texmath(x=\w2):texmath(y=maxima(\u2*x +(\v2)) )}
\text{eqd4=\b2=0?texmath(x=-\w2):texmath(y=maxima(-\u2*x -(\v2)) )}
\text{e4=texmath(maxima(\a2*x-\b2*y))}
\text{f4=\c2}
\text{S1=\( \left \lbrace \begin{array}{rcll} \e1&=&\f1 & (1)\\ \e2&=&\f2 & (2)\end{array}\right .)}
\text{S2=\( \left \lbrace \begin{array}{rcll} \e1&=&\f1 & (1)\\ \e3&=&\f3 & (2)\end{array}\right .)}
\text{S3=\( \left \lbrace \begin{array}{rcll} \e1&=&\f1 & (1)\\ \e4&=&\f4 & (2)\end{array}\right .)}
\text{S4=\( \left \lbrace \begin{array}{rcll} \e2&=&\f2 & (1)\\ \e3&=&\f3 & (2)\end{array}\right .)}
\text{S5=\( \left \lbrace \begin{array}{rcll} \e2&=&\f2 & (1)\\ \e4&=&\f4 & (2)\end{array}\right .)}
\text{S6=\( \left \lbrace \begin{array}{rcll} \e3&=&\f3 & (1)\\ \e4&=&\f4 & (2)\end{array}\right .)}
\text{lstsys=\S2,\S3,\S4,\S5,\S6}
\text{lstsys=shuffle(\lstsys)}
\text{lstsys=\S1,\lstsys[1],\lstsys[2],\lstsys[3]}
\text{ind=shuffle(4)}
\text{lsteq=\eqd1,\eqd2,\eqd3,\eqd4}
\text{eqd1=\lsteq[\ind[1]]}
\text{eqd2=\lsteq[\ind[2]]}
\text{eqd3=\lsteq[\ind[3]]}
\text{eqd4=\lsteq[\ind[4]]}
\integer{i=position(1,\ind)}
\integer{j=position(2,\ind)}
\statement{
  On considère les droites \(D_1, D_2, D_3) et \(D_4) d'équations réduites:
<ul>
<li>\(D_1) : \(\eqd1)</li>
<li>\(D_2) : \(\eqd2)</li>
<li>\(D_3) : \(\eqd3)</li>
<li>\(D_4) : \(\eqd4)</li>
</ul>
 Cocher le système correspondant à la recherche des points d'intersection de
 \(D_\i) et \(D_\j).
<ol><li>\embed{reply1,1}</li><li>\embed{reply1,2}</li><li>
\embed{reply1,3}</li><li>\embed{reply1,4}</li></ol>

}
\answer{Système}{1;\lstsys}{type=radio}{option=shuffle}
#endif

#if (defined TARGET_syslingeo2 || defined TARGET_syslingeo4 || defined TARGET_syslingeo5 )

\text{taille=130 x 200 x 80}

\text{data=\(D_1\) et \(D_2\),1
  \(D_1\) et \(D_3\),2
  \(D_1\) et \(D_4\),2
  \(D_2\) et \(D_2\),3
  \(D_2\) et \(D_3\),2
  \(D_3\) et \(D_4\),1}
\text{ind=shuffle(6)}
\text{cedata=row(\ind[1],\data)}
\text{quest1=\cedata[1]}
\text{rep1=\cedata[2]}
\text{cedata=row(\ind[2],\data)}
\text{quest2=\cedata[1]}
\text{rep2=\cedata[2]}
\text{lstcoef=0,1,1/2,1/3,1/4,2/3,3/4,2,5/2,3}
\text{lstcoef=shuffle(\lstcoef)}
\rational{a1=\lstcoef[1]}
\rational{b1=\lstcoef[2]*randint(1,-1)}
\rational{a3=\lstcoef[3]*(-1)}
\rational{b3=\lstcoef[4]*randint(1,-1)}
real{a3=\a1=\a3?-1*\a1}
real{a3=\a1=\a3?\a1-1}
\rational{a2=\a1}
\rational{b2=\b1>0?\b1-random(2,3,4,5/2):\b1+random(2,3,4,5/2)}
\rational{a4=\a3}
\rational{b4=\b3>0?\b3-random(2,3,4,5/2):\b3+random(2,3,4,5/2)}

#if defined TARGET_syslingeo2
\text{legende=
 text orange,-3,-3*\a1+\b1+0.2,medium,D1
 text green,3,3*\a2+\b2+0.2,medium,D2
 text blue,-1,-1*\a3+\b3+0.2,medium,D3
 text magenta,1,1*\a4+\b4+0.2,medium,D4}
 \text{colors=orange,green,blue,magenta}
#else
 \text{colors=black,black,black,black}
 \rational{x1=(\b3-\b1)/(\a1-\a3)}
 \rational{y1=\a1*\x1+\b1}
 \rational{x2=(\b4-\b1)/(\a1-\a3)}
 \rational{y2=\a1*\x2+\b1}
 \rational{x3=(\b3-\b2)/(\a1-\a3)}
 \rational{y3=\a1*\x3+\b2}
 \rational{x4=(\b4-\b2)/(\a1-\a3)}
 \rational{y4=\a1*\x4+\b2}
\text{legende=
 linewidth 5
 point \x1,\y1,red
 point \x2,\y2,blue
 point \x3,\y3,green
 point \x4,\y4,magenta
 text red,\x1-0.2,\y1-0.5,medium,A
 text blue,\x2-0.2,\y2-0.5,medium,B
 text green,\x3-0.2,\y3-0.5,medium,C
 text magenta,\x4-0.2,\y4-0.5,medium,D}
\text{e1=texmath(maxima(\a1*x-y))}
\text{e2=texmath(maxima(\a2*x-y))}
\text{e3=texmath(maxima(\a3*x-y))}
\text{e4=texmath(maxima(\a4*x-y))}
\text{f1=\b1=0?0:texmath(-\b1)}
\text{f2=\b2=0?0:texmath(-\b2)}
\text{f3=\b3=0?0:texmath(-\b3)}
\text{f4=\b4=0?0:texmath(-\b4)}
\text{S1=\( \left \lbrace \begin{array}{rcll} \e1&=&\f1 & \\ \e3&=&\f3 & \end{array}\right .)}
\text{S2=\( \left \lbrace \begin{array}{rcll} \e1&=&\f1 & \\ \e4&=&\f4 & \end{array}\right .)}
\text{S3=\( \left \lbrace \begin{array}{rcll} \e2&=&\f2 & \\ \e3&=&\f3 & \end{array}\right .)}
\text{S4=\( \left \lbrace \begin{array}{rcll} \e2&=&\f2 & \\ \e4&=&\f4 & \end{array}\right .)}
\text{S5=\( \left \lbrace \begin{array}{rcll} \e1&=&\f1 & \\ x&=&0 & \end{array}\right .)}
\text{S6=\( \left \lbrace \begin{array}{rcll} \e2&=&\f2 & \\ x&=&0 & \end{array}\right .)}
#if defined TARGET_syslingeo4
\text{sysList=\S1,\S2,\S3,\S4}
\text{ptList=<span style="color:red">A</span>,<span style="color:blue">B</span>,<span style="color:green">C</span>,<span style="color:magenta">D</span>}
#endif
#if defined TARGET_syslingeo5
\text{sysList=\S1,\S2,\S3,\S4,\S5,\S6}
\text{ptList=<span style="color:red">A</span>,<span style="color:blue">B</span>,<span style="color:green">C</span>,<span style="color:magenta">D</span>,<span style="color:orange">E</span>,<span style="color:purple">F</span>}
\text{legende=\legende
 point 0,\b1,orange
 point 0,\b2,purple
 text orange,-0.2,\b1-0.5,medium,E
 text purple,-0.2,\b2-0.5,medium,F
}

#endif
#endif

\text{image=\cadre
 \axes
 linewidth 1
 plot \colors[1],\a1*x+\b1
 plot \colors[2],\a2*x+\b2
 plot \colors[3],\a3*x+\b3
 plot \colors[4],\a4*x+\b4
 \legende
}
#if defined TARGET_syslingeo2
\title{TITRE II}
\statement{
<div class="float_left spacer">\draw{400,400}{\image}</div>
<div class="float_left">
  Cocher le nombre de solutions du système composé des équations réduites
  des deux droites suivantes :
<ol>
<li>\quest1 : \embed{reply1}</li>
<li>\quest2 : \embed{reply2}</li>
</ol>
</div>
}
\answer{S1}{\rep1;\lstrep}{type=radio}
\answer{S2}{\rep2;\lstrep}{type=radio}
#else
#if defined TARGET_syslingeo4
\title{TITRE IV}
#endif
#if defined TARGET_syslingeo5
\title{TITRE V}
#endif
\statement{
<div> Associer points d'intersection et systèmes linéaires.</div>
<div class="float_left spacer">
\draw{400,400}{\image}
</div>
<div class="float_left spacer">
\embed{reply1,\taille}
</div>

}
\answer{Correspondance }{\sysList;\ptList}{type=correspond}
#endif
#endif
