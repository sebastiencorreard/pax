target=convert1 convert2 convert3 convert4 convert5
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\precision{1000}
\format{html}
#if defined TARGET_convert1
# define NUM 1
#endif
#if defined TARGET_convert2
# define NUM 2
#endif
#if defined TARGET_convert3
# define NUM 3
#endif
#if defined TARGET_convert4
# define NUM 4
#endif
#if defined TARGET_convert5
# define NUM 5
#endif
#include "lang_titles.inc"
\text{datadegre=30,45,60,90,120,135,150,180,210,235,240,270,300,315,330}
\text{dataradian=pi/6,pi/4,pi/3,pi/2,2*pi/3,3*pi/4,5*pi/6,pi,7*pi/6,5*pi/4,4*pi/3,3*pi/2,5*pi/3,7*pi/4,11*pi/6}
\text{dataradiant=\frac{\pi}{6},\frac{\pi}{4},\frac{\pi}{3},\frac{\pi}{2},\frac{2\pi}{3},\frac{3\pi}{4},\frac{5\pi}{6},\pi,\frac{7\pi}{6},\frac{5\pi}{4},\frac{4\pi}{3},\frac{3\pi}{2},\frac{5\pi}{3},\frac{7\pi}{4},\frac{11\pi}{6}}

#if defined TARGET_convert1
\computeanswer{yes}
\integer{i=randint(1..items(\datadegre))}
\real{vald=\datadegre[\i]}
\real{valr=\dataradian[\i]}
\text{valrt=\dataradiant[\i]}
\statement{
  On considère un angle \(x=\vald^\circ).<p>
  Donner sa valeur en radian sous forme de fraction:</p>

  <div class="wimscenter"><label for="reply1">Angle en radian&nbsp;:</label> \embed{reply1,10}</div>
  <div class="wims_instruction">Taper <span class="tt">pi</span>
  pour \(\,\pi).</div>
}
\answer{Angle en radian}{\valr}{type=numeric}
\feedback{\reply1 <> \valr}{Soit sous forme de fraction: \(\valrt)}
#endif

#if defined TARGET_convert2
\computeanswer{no}
\integer{i=randint(1..items(\datadegre))}
\real{vald=\datadegre[\i]}
\text{valr=texmath(\dataradian[\i])}
\statement{
  On considère un angle \(\alpha=\valr) \({}rad).
  Donner sa valeur en degré:
<div class="wimscenter">
  <label for="reply1">Angle en degré&nbsp;:</label> \embed{reply1,5}
</div>
}
\answer{Angle en degré}{\vald}{type=numeric}
#endif
#if defined TARGET_convert3
\computeanswer{yes}
\integer{vald=randint(1..179)}
\real{valr=\vald*pi/180}
\statement{
  On considère un angle \(x=\vald^\circ).
  Donner sa valeur en radian:
<div class="wimscenter"><label for="reply1">Angle en radian&nbsp;:</label> \embed{reply1,5}</div>
<div class="wims_instruction">Taper <span class="tt">pi</span> pour \(\,pi).
</div>
}
\answer{Angle en radian}{\valr}{type=numeric}
#endif
#if defined TARGET_convert4
\computeanswer{no}
\real{valr=randint(10..30)/10}
\rational{vald=180*\valr/pi}
\integer{vald=100*\vald}
\real{vald=\vald/100}
\statement{
  On considère un angle \(\alpha=\valr) \({}rad).
  Donner sa valeur en degré à \(10^{-2}) près:
<div class="wimscenter">
  <label for="reply1">Angle en degré&nbsp;:</label>\embed{reply1,5}
</div>
}
\answer{Angle en degré}{\vald}{type=numeric}
#endif
#if defined TARGET_convert5
\computeanswer{yes}
\integer{den=randint(3,4,6,8,12)}

\text{numl=wims(makelist x for x=1 to \den-1),wims(makelist x for x=\den+1 to 2*\den-1)}
\text{numl=shuffle(\numl)}
\text{angl=}
\for{i=1 to 4}
 {
  \integer{num=\numl[\i]}
  \rational{k=simplify(\num / \den)}
  \text{tk=\k}
  \text{tk=wims(replace internal / by , in \tk)}
  \text{tk=\tk[1]=1?\frac{\pi}{\tk[2]}:\frac{\tk[1] \pi}{\tk[2]}}
  \text{angl=wims(append item \tk to \angl)}
}
\text{coefl=}
\rational{base=simplify(\numl[1] / \den)}
\for{i=2 to 4 }
 {
  \integer{num=\numl[\i]}
  \rational{k=simplify(\num / \den)}
  \rational{coef=simplify((\k) / (\base))}
  \text{coefl=wims(append item \coef to \coefl)}
 }
\statement{
  Un angle \(\alpha) mesure \(\angl[1]) rad.
  Ecrire chacune des mesures suivantes en radian sous la forme \(k \times \alpha),
  avec \(k\) rationnel.

<ol>
<li><label for="reply1">\(\angl[2]) rad=</label> \embed{reply1,3}\(\alpha)</li>
<li><label for="reply2">\(\angl[3]) rad=</label> \embed{reply2,3}\(\alpha)</li>
<li><label for="reply3">\(\angl[4]) rad=</label> \embed{reply3,3}\(\alpha)</li>
</ol>
}
\answer{angle 1}{\coefl[1]}{type=numeric}
\answer{angle 2}{\coefl[2]}{type=numeric}
\answer{angle 3}{\coefl[3]}{type=numeric}
#endif
