target=equava
%%
\observation{ L'objet de l'exercice est de résoudre un abs(a x- c) = abs( b x-d) par l'appartenance à un intervalle}
%%
\language{fr}
\computeanswer{yes}
\precision{1000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format{html}
#include "css.inc"
%% Choix des coefficients %%
\integer{a=random(1..10)*random(1,-1)}
\integer{b=\a+random(1..3)*random(1,-1)}
\if{\b=\a or \b=-\a}{\integer{b=2*\a}}
\integer{c=random(1..10)*random(1,-1)}
\integer{d=random(1..10)*random(1,-1)}

%% Choix de l'hypothèse
\text{eqx=\(abs(texmath(\a * x-(\c)))) = \(abs(texmath(\b * x-(\d)))) }
\text{eqs1=texmath(\a * x-(\c))}
\text{eqs2=texmath(\b * x-(\d))}
\text{eqs3=texmath(-(\b) * x+(\d))}

%% calcul de la bonne réponse %%
\integer{n1=\c - (\d)}
\integer{d1=\a - (\b)}
\rational{v1= \n1 /(\d1)}

\integer{n2=\c + (\d)}
\integer{d2=\a + (\b)}
\rational{v2= \n2 /(\d2)}
\rational{rep1=\v1<\v2?\v1:\v2}
\rational{rep2=\v1<\v2?\v2:\v1}

\text{size=\confparm1=1 ? :x-large}
%% Maintenant, rédigeons l'énoncé %%
\statement{
<div class="rm">
  \name_question
  <div class="wimscenter">
    \eqx.
  </div>
  <div class="wims_instruction">
  \name_instruction
  </div>
  <p>\name_answer:</p>
  <div class="wimscenter">
     S= &#123; \embed{reply1,3} ; \embed{reply2,3} &#125;.
  </div>
</div>
}

%% Récupération des réponses %%
\answer{}{\rep1}{type=numeric}
\answer{}{\rep2}{type=numeric}

%% Indication
\hint{ <div class="hint">
&#124; a &#124; = &#124; b &#124; \(\Leftrightarrow) a = b \name_or a = -b<br>
\name_hint
</div>}

%% Solution
\solution{<div class="solution">
 \eqx \( \Leftrightarrow) \eqs1 = \eqs2 \name_or \eqs1 = \eqs3<br>
\(\Leftrightarrow) \d1 x = \n1 \name_or \d2 x = \n2 \(\Leftrightarrow) x = \(\frac{\n1}{\d1}) \name_or x = \(\frac{\n2}{\d2})
</div>

}
