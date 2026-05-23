\title{Question 1030 Script Python}
\keywords{mental_calculation,python}
%%%%%%%%%%% question 15 %%%%%%%%%%%

\integer{a15=randitem(5,10,25)} %%% multiples de \a15...
\integer{temp15=\a15*randint(4..9)} 
\integer{rep=\temp15+\a15}
\integer{b15=\temp15+randint(1..4)}
\text{code=def fin (b):
   a = 0
   while a < b :
      a = a + \a15
   return a}
\text{aff_Python=slib(editor [python,[\code]],1,readonly fullscreen theme=[3024-night,3024-day])}
\css{<style>.CodeMirror {max-height:100px;}</style>}
\text{enonce=On considère le script python &#58; 
\aff_Python
L'expression fin(\b15) renvoie &#58; }
\text{enonceb=}
\text{feedback=Lors de l'exécution du programme Python, la variable a prend comme valeurs successives les multiples de \a15 tant qu'ils ne dépassent pas \b15. La réponse est donc \temp15 &#58; le premier  multiple de 
\a15 supérieur à \b15.}
