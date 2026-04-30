target=reconnait1,reconnait2,reconnait3,reconnait4,reconnait5
#include "author.inc"
\precision{100}
#if defined TARGET_reconnait1
# define NUM 1
#endif
#if defined TARGET_reconnait2
# define NUM 2
#endif
#if defined TARGET_reconnait3
# define NUM 3
#endif
#if defined TARGET_reconnait4
# define NUM 4
#endif
#if defined TARGET_reconnait5
# define NUM 5
#endif
#include "lang_titles.inc"
\text{f=randitem(f,g,h)}

#if defined TARGET_reconnait1
 \text{v=wims(values v,-v for v=2 to 20)}
 \text{v=shuffle(\v)}
 \text{good=Oui}
 \text{form=texmath(\v[1]*x+\v[2])}
 \text{enonce=Soit \(\f\) la fonction définie par : <div class="wimscenter"> \(\f : x \mapsto \form)</div>}
 \text{compenonce=Cette fonction est-elle une fonction affine}
#endif
#if defined TARGET_reconnait2
 \text{v=wims(values v for v=2 to 20)}
 \text{v=shuffle(\v)}
 \text{good=Oui}
 \text{form=texmath(\sqrt{\v[1]}*x+\v[2])}
 \text{enonce=Soit \(\f\) la fonction définie par : <div class="wimscenter"> \(\f : x \mapsto \form).</div>}
 \text{compenonce=Cette fonction est-elle une fonction affine}
#endif
#if defined TARGET_reconnait3
 \text{v=wims(values v for v=2 to 20)}
 \text{v=shuffle(\v)}
 \text{good=Non}
 \text{form=texmath(\v[1]*x+\v[2]+\v[3]*x^2)}
 \text{enonce=Soit \(\f\) la fonction définie par : <div class="wimscenter"> \(\f : x \mapsto \form).</div>}
 \text{compenonce=Cette fonction est-elle une fonction affine}
#endif
#if defined TARGET_reconnait4
 \text{v=wims(values v for v=2 to 20)}
 \text{v=shuffle(\v)}
 \text{good=Oui}
 \text{enonce=Soit \(\f\) la fonction définie par : <div class="wimscenter"> \(\f : x \mapsto \frac{\v[1]}{\v[2]}x).</div>}
 \text{compenonce=Cette fonction est-elle une fonction affine}
#endif
#if defined TARGET_reconnait5
 \text{v=wims(values v,-v for v=2 to 20)}
 \text{v=shuffle(\v)}
 \integer{ch=randint(1..2)}
 \integer{c1=\v[4]*\v[1]+\v[5]}
 \integer{c2=\v[4]*\v[2]+\v[5]}
 \if{\ch=1}{
  \text{good=Oui}
  \integer{c3=\v[4]*\v[3]+\v[5]}
 }{
  \text{good=Non}
  \integer{c3=\v[4]*\v[3]+\v[6]}
 }
 \text{enonce=Soit \(\f\) une fonction dont les valeurs connues sont reportées dans le tableau ci-dessous :
 <table class="wimscenter wimsborder">
 <tr><th>x</th><td>\v[1]</td><td>\v[2]</td><td>\v[3]</td></tr>
 <tr><th>\(\f(x))</th><td>\c1</td><td>\c2</td><td>\c3</td></tr>
 </table>}
 \text{compenonce=Cette fonction peut-elle être une fonction affine}
#endif

\text{bad=Oui,Non}
\statement{
\enonce<br>
\compenonce ?}

\choice{réponse}{\good}{\bad}
