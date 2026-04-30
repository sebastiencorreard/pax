target=ptetrigo1 ptetrigo2 ptetrigo3 ptetrigo4 ptetrigo5
#define TITRE1 Signe de
#if defined TARGET_ptetrigo1
# define NUM 1
#endif
#if defined TARGET_ptetrigo2
# define NUM 2
#endif
#if defined TARGET_ptetrigo3
# define NUM 3
#endif
#if defined TARGET_ptetrigo4
# define NUM 4
#endif
#if defined TARGET_ptetrigo5
# define NUM 5
#endif
#include "lang_titles.inc"
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\computeanswer{yes}
\precision{1000}

\text{dessin=
 xrange -1,1
 yrange -1,1
 circle 0,0,200,black
 darrow -1,0,1,0,10,black
 darrow 0,-1,0,1,10,black
 dsegment -cos(pi/6),-sin(pi/6),cos(pi/6),sin(pi/6),green
 dsegment -cos(pi/3),-sin(pi/3),cos(pi/3),sin(pi/3),green
 dsegment -cos(-pi/6),-sin(-pi/6),cos(-pi/6),sin(-pi/6),green
 dsegment -cos(-pi/3),-sin(-pi/3),cos(-pi/3),sin(-pi/3),green
 dsegment cos(pi/4),sin(pi/4),-cos(pi/4),-sin(pi/4),red
 dsegment cos(-pi/4),sin(-pi/4),-cos(-pi/4),-sin(-pi/4),red
 }

\real{pp=3.1415926535897932385}
\text{courbesin=
 xrange -6.28,6.28
 yrange -2,2
 arrow -6.28,0,6.28,0,10,black
 arrow 0,-2,0,2,10,black
 parallel -2*\pp,-0.1,-2*\pp,0.1,\pp/4,0,17,black
 parallel -0.1,-2,0.1,-2,0,1,5,black
 text black,0.2,1.2,large,+1
 text black,0.2,-0.8,large,-1
 plot red,sin(x)
}
\text{courbecos=
  xrange -6.28,6.28
  yrange -2,2
  arrow -6.28,0,6.28,0,10,black
  arrow 0,-2,0,2,10,black
  parallel -2*\pp,-0.1,-2*\pp,0.1,\pp/4,0,17,black
  parallel -0.1,-2,0.1,-2,0,1,5,black
  text black,0.2,1.2,large,+1
  text black,0.2,-0.8,large,-1
  plot red,cos(x)
}
#if defined TARGET_ptetrigo1
\text{lstrep=\(\sin{x} \le 0),\(\sin{x} \ge 0)}
\text{interdata= &#91; \(0;\frac{\pi}{2}) &#93;,2
&#91; \(\frac{\pi}{2};\pi) &#93;,2
&#91; \(\frac{\pi}{4};\frac{3\pi}{4}) &#93;,2
&#91; \(\pi;\frac{3\pi}{2}) &#93;,1
&#91; \(\frac{3\pi}{2};2\pi) &#93;,1
&#91; \(\frac{5\pi}{4};\frac{7\pi}{4}) &#93;,1
}
\text{cedata=randomrow(\interdata)}
\text{inter=\cedata[1]}
\integer{rep=\cedata[2]}
\statement{
<div class="grid-x grid-margin-x">
  <div class="cell small-12 medium-6 large-7">
   A l'aide du cercle trigonométrique ci-contre, déterminer le signe de \(\sin{x})
  <div class="wimscenter"> lorsque \(x \in) \inter.</div>
  <div class="wimscenter">\embed{reply1}</div>
  </div>
  <div class="cell auto">
    \draw{200,200}{\dessin}
  </div>
</div>
 }
\answer{TITRE1 sin x}{\rep;\lstrep}{type=radio}
#endif
#if defined TARGET_ptetrigo2
\text{lstrep=\(\cos{x} \le 0),\(\cos{x} \ge 0)}
\text{interdata= &#91; \(0;\frac{\pi}{2}) &#93;,2
&#91; \(\frac{\pi}{2};\pi) &#93;,1
&#91; \(\frac{3\pi}{4};\frac{5\pi}{4}) &#93;,1
&#91; \(\pi;\frac{3\pi}{2}) &#93;,1
&#91; \(\frac{3\pi}{2};2\pi) &#93;,2
&#91; \(\frac{-\pi}{4};\frac{\pi}{4}) &#93;,2
}
\text{cedata=randomrow(\interdata)}
\text{inter=\cedata[1]}
\integer{rep=\cedata[2]}
\statement{
<div class="grid-x grid-margin-x">
  <div class="cell small-12 medium-6 large-7">
   A l'aide du cercle trigonométrique ci-contre, déterminer le signe de \(\cos{x})
  lorsque \(x \in) \inter.
  <div class="wimscenter">\embed{reply1}</div>
  </div>
  <div class="cell auto">
    \draw{200,200}{\dessin}
  </div>
</div>
}
\answer{TITRE1 cos x}{\rep;\lstrep}{type=radio}
#endif
#if defined TARGET_ptetrigo3
\text{lstrep=la fonction <b>sinus</b> est croissante ,la fonction <b>sinus</b> est décroissante}
\text{interdata= &#91; \(0;\frac{\pi}{2}) &#93;,1
&#91; \(\frac{\pi}{2};\pi) &#93;,2
&#91; \(\frac{\pi}{4};\frac{3\pi}{4}) &#93;,2
&#91; \(\pi;\frac{3\pi}{2}) &#93;,2
&#91; \(\frac{3\pi}{2};2\pi) &#93;,1
&#91; \(\frac{-\pi}{4};\frac{3\pi}{4}) &#93;,1
}
\text{cedata=randomrow(\interdata)}
\text{inter=\cedata[1]}
\integer{rep=\cedata[2]}
\statement{
<div class="grid-x grid-margin-x">
  <div class="cell small-12 medium-6 large-7">
   A l'aide de la représentation graphique ci-contre (l'unité sur l'axe des abscisses est
  \(\frac{\pi}{4}\)), déterminer le sens
  de variation de la fonction <b>sinus</b>
  lorsque \(x \in) \inter.
  <div class="wimscenter">\embed{reply1}</div>
  </div>
  <div class="cell auto">
    \draw{200,200}{\courbesin}
  </div>
</div>

}
\answer{La fonction <b>sinus</b> est}{\rep;\lstrep}{type=radio}
#endif
#if defined TARGET_ptetrigo4
\text{lstrep=la fonction <b>cosinus</b> est croissante ,la fonction <b>cosinus</b> est décroissante}
\text{interdata= &#91; \(0;\frac{\pi}{2}) &#93;,2
&#91; \(\frac{\pi}{2};\pi) &#93;,2
&#91; \(\frac{\pi}{4};\frac{3\pi}{4}) &#93;,2
&#91; \(\pi;\frac{3\pi}{2}) &#93;,1
&#91; \(\frac{3\pi}{2};2\pi) &#93;,1
&#91; \(\frac{5\pi}{4};\frac{7\pi}{4}) &#93;,1
}
\text{cedata=randomrow(\interdata)}
\text{inter=\cedata[1]}
\integer{rep=\cedata[2]}
\statement{
<div class="grid-x grid-margin-x">
  <div class="cell small-12 medium-6 large-7">
   A l'aide de la représentation graphique ci-contre (l'unité sur l'axe des abscisses est
  \(\frac{\pi}{4}\)), déterminer le sens
  de variation de la fonction <b>cosinus</b>
  lorsque \(x \in) \inter.
<div class="wimscenter">\embed{reply1}</div>
  </div>
  <div class="cell auto">
    \draw{200,200}{\courbecos}
  </div>
</div>

}
\answer{Sens de variation de cos x}{\rep;\lstrep}{type=radio}
#endif
#if defined TARGET_ptetrigo5
\integer{k=randint(1..4)}
\text{repdata=La fonction est paire,La fonction est impaire
  La courbe représentative est symétrique par rapport à l'axe des ordonnées,La courbe représentative est symétrique par rapport à l'origine
\(\sin{(-x)}=\sin{x}),\(\sin{(-x)}=-\sin{x})
\(\cos{(-x)}=\cos{x}),\(\cos{(-x)}=-\cos{x})
}
\text{lstrep=row(\k,\repdata)}
\if{\k<3}{\integer{rep=randint(1,2)}}
{
  \if{\k=3}{\integer{rep=2}}{\integer{rep=1}}
}
\text{fonct=\rep=1?cosinus:sinus}
\statement{
  Cocher la propriété concernant la fonction <b>\fonct</b>.
<ul><li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
</ul>
}
\answer{propriété de \fonct}{\rep;\lstrep}{type=radio}
#endif
