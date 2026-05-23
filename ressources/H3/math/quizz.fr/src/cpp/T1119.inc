\title{Question T1119 Script Python}
\keywords{mental_calculation,python}
%%%%%%%%%%% question 15 %%%%%%%%%%%

\integer{coef1=randint(2..6)}
\integer{coef2=randint(1..7)}
\integer{coef3=randint(1..5)*randint(1,-1)}
\text{ligne3=(\coef3>0)? c=b+\coef3:c=b\coef3}
\integer{a19=randint(1..9)}
\integer{temp19=\a19*\coef1+\coef2+\coef3} 
\integer{rep=\temp19}
\text{enonce=On considère le script python &#58; <div class="tt">&emsp;def prog(a)&#58;<br>&emsp;&emsp; b=\coef1*a+\coef2<br> &emsp;&emsp; \ligne3<br> &emsp;&emsp; return c</div>L&#146;expression prog(\a19) renvoie &#58; }
%%% avec slib editor
\text{code=def prog(a):
   b=\coef1*a+\coef2
   \ligne3
   return c}
\text{aff_Python=slib(editor [python,[\code]],1,readonly fullscreen theme=[3024-night,3024-day])}
\css{<style>.CodeMirror {max-height:100px;}</style>}
\text{enonce=On considère le script python &#58;
\aff_Python
L'expression prog(\a19) renvoie &#58;}
%%%%%%%%%%%%%%%%%%%%%%%%%
\text{enonceb=}
\integer{b19=\coef1*\a19+\coef2}
\text{corr19=(\coef3>0)? \b19+\coef3:\b19\coef3}
\text{feedback=Lors de l'exécution du programme Python, b prend la valeur \(\coef1 \times \a19+\coef2=\b19) et c prend la valeur \(\corr19=\temp19).}
\integer{size=6}
