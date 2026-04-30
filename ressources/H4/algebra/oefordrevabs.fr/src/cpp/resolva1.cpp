target=resolva1

%%
\observation{L'objet de l'exercice est de résoudre un abs(x-a) = b par l'appartenance à un intervalle}
%%
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\computeanswer{yes}
\precision{1000}
\format{html}
#include "css.inc"

%% borne pour le rayon %%
\integer{rayonmax=20}

%% borne pour le centre %%
\integer{centremax=10}

%% Choix des bornes %%
\integer{sing1=random(1..\centremax)*randint(1,-1)}
\integer{sing2=random(1..\rayonmax)}


%% Choix de l'hypothèse
    \text{eqx=\(abs(texmath(x-(\sing1)))) = \sing2 }
    \text{eqs1=texmath(x-(\sing1))}

%% calcul de la bonne réponse %%
\integer{v1=\sing2+(\sing1)}
\integer{v2=-(\sing2)+(\sing1)}
\integer{rep2=\v2<\v1?\v1:\v2}
\integer{rep1=\v2<\v1?\v2:\v1}

%% Maintenant, rédigeons l'énoncé %%
\statement{
<div class="rm">
  \name_question:
  <div class="wimscenter">
   \eqx.
  </div>
  <div class="wims_instruction">
  \name_instruction
  </div>
  <p>\name_answer:</p>
  <div class="wimscenter">
  S= &#123; \embed{reply1,3} ; \embed{reply2,3}&#125;.
  </div>
</div>
}

%% Récupération des réponses %%
\answer{}{\rep1}{type=numeric}
\answer{}{\rep2}{type=numeric}

%% Indication
\hint{ <div class="hint">
\(abs(a)) = \(b) \(\Leftrightarrow ) \(a) = \(b) \name_or \(a) = -\(b)
</div>}

%% Solution
\solution{
<div class="solution">
\eqx \(\Leftrightarrow ) \eqs1 = \sing2 \name_or \eqs1 = -(\sing2)<br>
\(\Leftrightarrow) x = \sing2 + (\sing1) \name_or x = -(\sing2)+(\sing1)
</div>}
