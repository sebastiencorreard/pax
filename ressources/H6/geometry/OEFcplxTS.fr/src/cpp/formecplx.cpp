target=formecplx1 formecplx2 formecplx3 formecplx4 formecplx5 formecplx6
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\target{html}
\computeanswer{yes}

# define TITRE Transformation d'écriture
#if defined TARGET_formecplx1
# define NUM 1
#endif
#if defined TARGET_formecplx2
# define NUM 2
#endif
#if defined TARGET_formecplx3
# define NUM 3
#endif
#if defined TARGET_formecplx4
# define NUM 4
#endif
#if defined TARGET_formecplx5
# define NUM 5
#endif
#if defined TARGET_formecplx6
# define NUM 6
#endif
\title{TITRE NUM}
\integer{x1=randint(1..3)*2+1}
\integer{x2=2*\x1}
\text{lsta=0,1/6,1/4,1/3,1/2,2/3,3/4,5/6,1,-5/6,-3/4,-2/3,-1/2,-1/3,-1/4,-1/6}
\text{lstc=1,sqrt(3)/2,sqrt(2)/2,1/2,0,-1/2,-sqrt(2)/2,-sqrt(3)/2,-1,-sqrt(3)/2,-sqrt(2)/2,-1/2,0,1/2,sqrt(2)/2,sqrt(3)/2}
\text{lsttc1=\x1,\frac{\x1 \sqrt{3}}{2},\frac{\x1 \sqrt{2}}{2},\frac{\x1}{2},,-\frac{\x1}{2},-\frac{\x1 \sqrt{2}}{2},-\frac{\x1 \sqrt{3}}{2},-\x1,-\frac{\x1 \sqrt{3}}{2},-\frac{\x1 \sqrt{2}}{2},-\frac{\x1}{2},,\frac{\x1}{2},\frac{\x1 \sqrt{2}}{2},\frac{\x1 \sqrt{3}}{2}}
\text{lsttc2=\x2,\x1 \sqrt{3},\x1 \sqrt{2},\x1,,-\x1,-\x1 \sqrt{2},-\x1 \sqrt{3},-\x2,-\x1 \sqrt{3},-\x1 \sqrt{2},-\x1,,\x1,\x1 \sqrt{2},\x1 \sqrt{3}}
\text{lsttc3=\x2 \sqrt{2},\x1 \sqrt{6},\x2,\x1 \sqrt{2},,-\x1 \sqrt{2},-\x2 ,-\x1 \sqrt{6},-\x2 \sqrt{2},-\x1 \sqrt{6},-\x2 ,-\x1 \sqrt{2},,\x1 \sqrt{2},\x2 ,\x1 \sqrt{6}}

\text{lsts=0,1/2,sqrt(2)/2,sqrt(3)/2,0,sqrt(3)/2,sqrt(2)/2,1/2,0,-1/2,-sqrt(2)/2,-sqrt(3)/2,-1,-sqrt(3)/2,-sqrt(2)/2,-1/2}
\text{lstts1=0,\frac{\x1}{2},\frac{\x1 \sqrt{2}}{2},\frac{\x1 \sqrt{3}}{2},\x1,\frac{\x1 \sqrt{3}}{2},\frac{\x1 \sqrt{2}}{2},\frac{\x1}{2},0,-\frac{\x1}{2},-\frac{\x1 \sqrt{2}}{2},-\frac{\x1 \sqrt{3}}{2},-\x1,-\frac{\x1 \sqrt{3}}{2},-\frac{\x1 \sqrt{2}}{2},-\frac{\x1}{2}}
\text{lstts2=0,\x1,\x1 \sqrt{2},\x1 \sqrt{3},\x2,\x1 \sqrt{3},\x1 \sqrt{2},\x1,0,-\x1,-\x1 \sqrt{2},-\x1 \sqrt{3},-\x2,-\x1 \sqrt{3},-\x1 \sqrt{2},-\x1}
\text{lstts3=0,\x1 \sqrt{2},\x2 ,\x1 \sqrt{6},\x2 \sqrt{2},\x1 \sqrt{6},\x2 ,\x1 \sqrt{2},0,-\x1 \sqrt{2},-\x2 ,-\x1 \sqrt{6},-\x2 \sqrt{2},-\x1 \sqrt{6},-\x2 ,-\x1 \sqrt{2}}
\integer{i=randint(1..items(\lsta))}
\rational{ang=\lsta[\i]}
\rational{mang=abs(\ang)}
\real{a=(\ang)*pi}
\text{triga=\ang=1? \pi:texmath(\ang)\pi}
\text{triga=\ang=-1?-\pi}
\text{ta=\ang=1?\imath \pi:\imath texmath(\ang)\pi}
\text{ta=\ang<0?-\imath texmath(\mang) \pi}
\text{ta=\ang=-1?-\imath \pi}
\text{zte=\ang=0? :e^{\displaystyle{\ta}}}
\integer{cas=randint(1..3)}
\if{\cas=1}{
  \text{x=\lsttc1[\i]}
  \text{y=\lstts1[\i]}
  \real{m=\x1}
  \text{tm=\x1}
}
\if{\cas=2}{
  \text{x=\lsttc2[\i]}
  \text{y=\lstts2[\i]}
  \real{m=\x2}
  \text{tm=\x2}
}
\if{\cas=3}{
  \text{x=\lsttc3[\i]}
  \text{y=\lstts3[\i]}
  \text{m=\x2*sqrt(2)}
  \text{tm=\x2 \sqrt{2}}
}
\text{si=\i<10?+:}
\text{z=\y issametext 0?\x:\x \si \y \imath}
#if defined TARGET_formecplx1
# define NUM 1
#endif
#if defined TARGET_formecplx2
# define NUM 2
#endif

#if (defined TARGET_formecplx1  || defined TARGET_formecplx2 )
# if defined TARGET_formecplx1
\text{natform=trigonométrique}
# else
\text{natform=exponentielle}
# endif

\statement{<p>On veut déterminer la forme \natform du nombre complexe \(z=\z).</p>
<ol>
<li>Calculer son module: <label for="reply1">\(|z|) =</label> \embed{reply1,5}.</li>
<li>Donner son argument principal (appartenant à &#93;\(\pi;\pi)&#93;):
  <label for="reply2">\(Arg(z)=)</label>\embed{reply2,5}.
<div class="wims_instruction">Taper <span class="tt">pi</span> pour \(\pi).</div>
</li>
<li> En déduire la forme \natform de \(z):
# if defined TARGET_formecplx1
<div class="wimscenter">
<label for="reply3">\(z)</label>=\embed{reply3,4}
<label for="reply4">(\(\cos)</label>(\embed{reply4,4})
<label for="reply5">\(+\imath \sin)</label>(\embed{reply5,4}))</div>
</li></ol>
}
\answer{module}{\m}{type=formal}
\answer{Argument}{\a}{type=numeric}
\answer{}{\m}{type=formal}
\answer{}{\a}{type=numeric}
\answer{}{\a}{type=numeric}
\solution{La forme \natform est \(z=\tm(\cos{\left(\triga\right)}+\imath \sin{\left(\triga\right)}))}
# endif
# if defined TARGET_formecplx2
<div class="wimscenter"><label for="reply3">\(z)=</label>\embed{reply3,4} e <sup>\(\imath)\embed{reply4,4}</sup></div>
</li></ol>
}
\answer{module}{\m}{type=formal}
\answer{Argument}{\a}{type=numeric}
\answer{}{\m}{type=formal}
\answer{}{\a}{type=numeric}
\solution{La forme \natform est \(z=\tm\zte)}
# endif
#endif
#if defined TARGET_formecplx3
\real{xx=\m*cos(\lsta[\i]*pi)}
\real{yy=\m*sin(\lsta[\i]*pi)}

\statement{<p>Donner l'écriture algébrique du nombre complexe \(z=\tm \zte\):</p>
<div class="wimscenter"><label for="reply1">\(z=)</label>\embed{reply1,5} + \embed{reply2,5}\(\imath)</div>
}
\answer{x}{\xx}{type=numeric}
\answer{x}{\yy}{type=numeric}
\solution{L'écriture algébrique est \(z=\z)}
#endif
#if defined TARGET_formecplx4
\rational{na=simplify(\ang+1)}
\rational{na=\na>1?simplify(\na-2)}
\statement{<p>Donner le module et l'argument principal du nombre complexe \(z=-\tm \zte):</p>
<div class="wimscenter"><label for="reply1">\(|z|)=</label>\embed{reply1,8}</div>
<div class="wimscenter"><label for="reply2">\(Arg(z))=</label> \embed{reply2,8}\(\pi)</div>
}
\answer{module}{\m}{type=formal}
\answer{argument principal}{\na}{type=numexp}
#endif
#if ( defined TARGET_formecplx5  || defined TARGET_formecplx6 )
\matrix{signes=,-
-,+
-,-}
 \integer{j=randint(1..3)}
\if{\j=1}{\rational{bada=-\ang}}
\if{\j=2}{\rational{bada=\ang>0?simplify(1-\ang):-simplify(1+\ang)}}
\if{\j=3}{\rational{bada=simplify(1+\ang)}}
\text{badz=\signes[\j;1] \tm \cos(texmath(\ang)\pi) \signes[\j;2] \tm \imath \sin(texmath(\ang)\pi)}
\rational{bada=\bada>1?simplify(\bada-2)}
#if defined TARGET_formecplx5
\statement{<p>Donner le module et l'argument principal du nombre complexe \(z=\badz):</p>
<div class="wimscenter"><label for="reply1">\(|z|)=</label> \embed{reply1,8}</div>
<div class="wimscenter"><label for="reply2">\(Arg(z))=</label> \embed{reply2,8}\(\pi)</div>
}
\answer{module}{\m}{type=formal}
\answer{argument principal}{\bada}{type=numexp}
#endif
#if defined TARGET_formecplx6
\statement{<p>Donner la forme exponentielle du nombre complexe \(z=\badz):</p>
<div class="wimscenter"><label for="reply1">\(z)=</label>\embed{reply1,8} e <sup>\(\imath)\embed{reply2,4}\(\pi)</sup></div>
}
\answer{module}{\m}{type=formal}
\answer{argument principal}{\bada}{type=numexp}
#endif
#endif
