target=variables1 variables2 si1 si2 si3 bouclefor1 bouclefor2 bouclewhile1 bouclewhile2 bouclewhile3 fonction2

\css{<style>#tab{text-align:center;overflow:auto;}</style>}
\text{name_instruction=Aucun logiciel de programmation n'est autorisé pour répondre à cet exercice, sans quoi il ne sert pas à grand chose pour progresser.
<br />En revanche, une calculatrice est parfois nécessaire pour trouver la bonne réponse.}
\integer{tot=5}
#include "author.inc"
#if defined TARGET_variables1
\keywords{variables}
\text{explain0=Qu'affiche ce programme en langage Python ?}
# include "variables1.inc"
#endif
#if defined TARGET_variables2
\keywords{variables}
\text{explain0=Qu'affiche ce programme en langage Python ?}
# include "variables2.inc"
#endif
#if defined TARGET_si1
\keywords{cond_instruction}
# include "si1.inc"
#endif
#if defined TARGET_si2
\keywords{cond_instruction}
# include "si2.inc"
#endif
#if defined TARGET_si3
\keywords{cond_instruction}
# include "si3.inc"
#endif
#if defined TARGET_bouclefor1
\keywords{loops}
\integer{tot=4}
# include "bouclefor1.inc"
#endif
#if defined TARGET_bouclefor2
\keywords{loops}
\integer{tot=4}
# include "bouclefor2.inc"
#endif
#if defined TARGET_bouclewhile1
\keywords{loops}
\integer{tot=4}
\text{explain0=Qu'affiche ce programme en langage Python ?}
# include "bouclewhile1.inc"
#endif
#if defined TARGET_bouclewhile2
\keywords{loops}
\integer{tot=4}
\text{explain0=Qu'affiche ce programme en langage Python ?}
# include "bouclewhile2.inc"
#endif
#if defined TARGET_bouclewhile3
\keywords{loops}
\integer{tot=4}
# include "bouclewhile3.inc"
#endif
#if defined TARGET_fonction2
\keywords{prog_functions}
\integer{tot=3}
# include "fonction2.inc"
#endif
\integer{givetrue=1}

:Nombre de mauvais choix "obligatoires".
Par exemple si ce nombre est 2, les deux premiers mauvais choix dans la liste seront toujours présentés dans les exercices générés.
<p> Dans le doute, mettez 0.</p>
\integer{minfalse=0}

:Mots d'option :  <span class="tt wims_code_words">checkbox</span>,  <span class="tt wims_code_words">split</span>.
Ajouter le mot  <span class="tt wims_code_words">checkbox</span> s'il y a plusieurs bonnes réponses et si l'élève doit choisir toutes les bonnes réponses (au lieu d'une seule).
Dans ce cas, ajouter aussi le mot  <span class="tt wims_code_words">split</span> si on autorise une note partielle quand seulement une partie des bonnes réponses sont choisies.
\text{option=}

:Feedback Général
Ce texte s'affichera après la réponse de l'apprenant, qu'elle soit juste ou fausse.
:Feedback en cas de bonne réponse
Ce texte s'affichera après la réponse de l'apprenant, en cas de bonne reponse ou de reponse partielle.
\text{feedback_bon=}

:Feedback en cas de mauvaise réponse
Ce texte s'affichera après la réponse de l'apprenant, s'il a coché au moins une mauvaise réponse.
\text{feedback_mauvais=}

:Indication
Un texte qui peut aider l'apprenant à trouver la bonne réponse
\text{exo_hint=}

:Mise en aléatoire par des accolades emboitables
help
\text{accolade=item(1,1 oui, 2 non)}

:%%%%%%%%%%%%%% Rien à modifier avant l'énoncé %%%%%%%%%%%%%%%%
\text{accolade=wims(word 1 of \accolade)}

\text{empty=}
\if{\feedback_general != \empty}{
  \text{feedback_general=<p class="feedback">\feedback_general</p>}
}
\if{\feedback_bon != \empty}{
  \text{feedback_bon=<div class="feedback good_answer">\feedback_bon</div>}
}
\if{\feedback_mauvais != \empty}{
  \text{feedback_mauvais=<div class="feedback bad_answer">\feedback_mauvais</div>}
}
\if{\exo_hint != \empty}{
  \hint{\exo_hint}
}

\text{datatrue=wims(nonempty rows \datatrue)}
\text{datafalse=wims(nonempty rows \datafalse)}
\integer{truecnt=rows(\datatrue)}
\integer{falsecnt=rows(\datafalse)}
\integer{givetrue=\givetrue<1?1}
\integer{givetrue=\givetrue>\truecnt?\truecnt}
\integer{tot=\tot > \falsecnt+\givetrue?\falsecnt+\givetrue}
\integer{givetrue=\givetrue>\tot-1?\tot-1}
\integer{minfalse=\minfalse>\tot-\givetrue?\tot-\givetrue}
\text{tsh=shuffle(\truecnt)}
\text{true=row(\tsh,\datatrue)}
\if{\minfalse>0}{
 \text{false1=row(1..\minfalse,\datafalse);}
 \text{false2=row(\minfalse+1..\falsecnt,\datafalse)}
}{
 \integer{minfalse=0}
 \text{false1=}
 \text{false2=\datafalse}
}
\text{fsh=shuffle(\falsecnt)}
\text{false2=row(\fsh,\false2)}
\text{pick=row(1..\givetrue,\true);\false1 row(1..\tot-\givetrue-\minfalse,\false2)}
\text{ind=wims(makelist 1 for x=1 to \givetrue),wims(makelist 0 for x=1 to \tot-\givetrue)}

\text{sh=shuffle(\tot)}
\text{ind=item(\sh,\ind)}
\text{pick=row(\sh,\pick)}
\text{pick=\accolade=1 ? wims(embraced randitem \pick)}
\text{explain=\accolade=1 ? wims(embraced randitem \explain)}
\text{ans=positionof(1,\ind)}
\text{list=item(1..\tot,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)}
\text{anstype=checkbox iswordof \option?checkbox:radio}

:%%%%%%%%%%%%% Maintenant l'énoncé en code html. %%%%%%%%%%%%%%%%%%%%

::Vous n'avez pas besoin de modifier ceci en général.
\statement{
  <div class="oef_explain">
  \explain0
    <div class="spacer">
    \special{editarea \explain}
    </div>
  </div>
  \for{i=1 to \tot}
  {<div class="oefreply">\embed{reply 1,\i, \list[\i] :
  \pick[\i;]}</div>}
  <div class="wims_instruction">
  \name_instruction
  </div>
  }


:%%%%%%%%%%%%% Rien à modifier ci-après. %%%%%%%%%%%%%%%%%5

\answer{La réponse}{\ans;\list}{type=\anstype}{option=\option}

\solution{
<p>\feedback_generalpre</p>
 <div class="feedback">
 \special{expandlines \feedback_program}
 </div>
#if defined TARGET_bouclefor1 || defined TARGET_bouclefor2 || defined TARGET_bouclewhile1 || defined TARGET_bouclewhile2 || defined TARGET_bouclewhile3
# include "feedback_tableau.inc"
#endif
<p>\feedback_generalpost</p>
}
\feedback{\reply1 isitemof \list[\ans]}{\feedback_bon}
\feedback{\reply1 notitemof \list[\ans]}{\feedback_mauvais}
