target=acoscos acossin

#include "author.inc"
\precision{10000}
\computeanswer{yes}
#include "lang_titles.inc"
#include "lang.inc"

\real{x=random(-1,1)*floor(random(10..150))/10}
\integer{ra=random(1,2)}
\real{add=item(\ra,0,pi/2)}
\text{cos=item(\ra,cos,sin)}
#if defined TARGET_acossin
\text{sin=item(\ra,sin,cos)}
#endif
\real{r=\x+\add}
\real{c=floor(\r/pi)}
\real{d=floor(\c/2)}
#if defined TARGET_acoscos
\real{a=\c%2=0?\x:-\x}
\integer{e=item(\ra,2,1)}
\real{b=\c%2=0?-2*\d:2*\d+\e}
\text{choix=arc\cos}
#endif
#if defined TARGET_acossin
\real{a=\c%2=0?-\x:\x}
\real{e2=item(\ra,-1.5,-0.5)}
\real{b=\c%2=0?2*\d+0.5:-2*\d+\e2}
\text{choix=arc\sin}
#endif
\statement{\name_enonce[1] \(x = \choix(\cos(\x))\) \name_enonce[2]
  \(x = a + b pi\) \name_enonce[3]
}

\answer{\(a\)}{\a}
\answer{\(b\)}{\b}
\hint{\name_hint}
