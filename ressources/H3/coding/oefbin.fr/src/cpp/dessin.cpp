target=dessin

\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{choix=random(1,2)}
\text{codage1= pari(A=matrix(4,4,i,j,RANDOM(2));
B=matrix(4,4,i,j,A[i,5-j]); C=matrix(4,4,i,j,A[5-i,j]);
D=matrix(4,4,i,j,A[5-i,5-j]); U=concat(A,B);
V=concat(C,D); print(concat(mattranspose(U),mattranspose(V))))}
\text{codage2= pari(A=print(matrix(8,8,i,j,RANDOM(2))))}
\text{codage=\choix=1 ? \codage1:\codage2}
\text{codage=wims(declosing \codage)}
\text{dessin=}
\text{reponse=2}
\for{i=1 to 8}{
  \text{rep=}
  \for{j=1 to 8}{
    \if{1 isin item(\j,row(\i,\codage))}{
      \text{dessin=\dessin
fill \j-1/2,9-\i-1/2,blue}
      \text{rep=\rep,1}
    }
    {\text{rep=\rep,0}}
  }
  \text{rep=wims(items2words \rep)}
  \text{rep=wims(nospace \rep)}
  \text{reponse=\reponse,\rep}
}
\text{reponse=item([2..9],\reponse)}
\statement{\name_question:
<div class="wimscenter">
\draw{200,200}{
  xrange 0,8.2
  yrange -0.2,8
  parallel 0,0,0,8,1,0,9,black
  parallel 0,0,8,0,0,1,9,black
  \dessin}
</div>
<div class="wims_instruction">
\name_inst</div>
}
\answer{\name_answer}{\reponse}{type=atext}
