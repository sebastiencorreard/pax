\title{Question 1126 Suite et Script Python}
\keywords{mental_calculation,python}
%%%%%%%%%%% question 15 %%%%%%%%%%%
\text{question=shuffle(2,3)}
\integer{max=randint(5..7)}
\integer{r=\question[1]} 
\integer{u0=\question[2]}
\integer{n=0}
\integer{u=\u0}
\text{ul=\u0}
\text{nl=\n}
\while{\u<\max}{
\integer{n=\n+1}
\integer{u=\u+\r}
\text{ul=\ul,\u}
\text{nl=\nl,\n}
}
\integer{rep=\n}
\text{code=def Suite (u):
   n = 0
   while u < \max :
      u = u + \r
      n = n + 1
   return n}
\text{aff_Python=slib(editor [python,[\code]],1,readonly fullscreen theme=[3024-night,3024-day])}
\css{<style>.CodeMirror {max-height:110px;}</style>}
\text{enonce=On considère le script python &#58; 
\aff_Python
Suite(\u0) renvoie &#58; }
\text{enonceb=}
\text{feedback=Lors de l'exécution du programme Python, la variables u et n prennent comme valeurs successives : 
<br>u : \ul<br> n : \nl}
