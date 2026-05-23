target=quadrilatere
#include "lang_titles.inc"
#include "author.inc"
\computeanswer{no}
\precision{1000}

\text{somG=0}
\while{\somG=0}{
  \integer{a = random(1,-1)*randint (1..6)}
   \integer{b = random(1,-1)*randint (1..6)}
   \integer{c = random(1,-1)*randint (1..6)}
   \integer{somG =\a+(\b)+(\c)}
}
\text{poids=\a,\b,\c}
\text{quadra=randitem(convexe,concave,croisé,croisé)}

\text{zone=\quadra issametext convexe ? 1,-0.25, 0.25}
\matrix{zone=\quadra issametext concave ? -0.25, 1,-0.25
 1,-0.25,-0.25
 -0.25,-0.25, 1
 1, 1, 1}
\matrix{zone=\quadra issametext croisé ? -0.2, 1, 0.3
1, 0.3,-0.3}

\text{ region = pari(S = [\a,\b,\c]/(\a+\b+\c); S)}
\text{ type = pari([sign(S[1]), sign(S[2]), sign(S[3])])}
\matrix{test_region =
 1, 1, 1
 1, 1,-1
 1,-1, 1
-1, 1, 1
 2,-0.5,-0.5
-0.5,-0.5, 2
-0.5, 2,-0.5
}
\text{ u = pari (T = Mat([\test_region]) ; R = matrix(7,3,i,j,sign(T[i,j])) ;
    u=1 ; while(R[u,] != [\type] , u = u+1) ; u)}

\matrix{ABC = -randitem(0.5,1,1.5),0
 randitem(0.5,1,1.5),randitem(0.5,1,1.5)
0,-randitem(0.5,1,1.5)}
\text{ordre=shuffle(3)}
\matrix{ABC=\ABC[\ordre;]}
\text{A=\ABC[1;]}
\text{B=\ABC[2;]}
\text{C=\ABC[3;]}

\text{AB = pari(t*[\A] + (1-t)*[\B])}
\text{BC = pari(t*[\B] + (1-t)*[\C])}
\text{CA = pari(t*[\C] + (1-t)*[\A])}

\text{range = -3,3}
\text{dessin= xrange \range
yrange \range
trange \range
plot blue, \AB[1],\AB[2]
plot blue, \BC[1],\BC[2]
plot blue, \CA[1],\CA[2]
rectangle \range[1],\range[1],\range[2],\range[2],black
}

\text{mix=shuffle(3)}
\text{mix=1,2,3}
\text{mix_inv = position(1,\mix), position(2,\mix), position(3,\mix)}
\text{lettre = A,B,C}
\text{lettre_mix = \lettre[\mix]}
\text{poids_mix = \poids[\mix_inv]}
\text{SIZE = 300,250}

\text{R=wims(declosing \reply1)}

\text{Dessin1 = xrange \range
yrange \range
text black,\A, large, \lettre_mix[1]
text black,\B, large, \lettre_mix[2]
text black,\C, large, \lettre_mix[3]
text black,\R,large,D
disk \A, 5,blue
disk \B, 5,blue
disk \C, 5,blue
disk \R, 5,blue
}

\text{DESSIN= draw(\SIZE
\dessin)}
\text{Nom_dessin = slib(oef/insfilename)}
\text{Dessin= draw(\SIZE
\Dessin1)}

\text{condition=}
\text{cnt=rows(\zone)}
\text{polygone=}
\for{ i = 1 to \cnt}{
  \text{H = \zone[\i;]}
  \text{V = pari(H = [\H] ; (H[1]+H[2]+H[3])^(-1)*(H[1]*[\A] + H[2]*[\B]
     + H[3]*[\C]))}
  \text{Ppixel = slib(draw/convpixel \V,\SIZE,\range,\range,0,pixels)}
  \real{Px = \Ppixel[1]}
  \real{Py = \Ppixel[2]}
  \text{condition=\i > 1 ? \condition |}
  \text{condition =\condition (bound,\Nom_dessin,\Px,\Py)}
 }

\statement{
<div class="wims_question">Cliquez sur un point \(D) de manière à ce que le
quadrilatère \((\lettre_mix[1]\lettre_mix[2]\lettre_mix[3]D)) soit \quadra :
</div>
<div class="wimscenter"> \embed{reply1}</div>
}

\answer{}{\Dessin; \condition}{type=coord}

\text{R=wims(declosing \reply1)}
\text{P = slib(draw/convpixel \R,\SIZE,\range,\range,0)}
\text{color=\result1=-1? red:green}
\text{DessinF=\Dessin1
text \color,\P,large,D
polyline blue,\A,\B,\C
polyline \color,\C,\P,\A
}

\feedback{1=1}{
Voici le quadrilatère que vous avez choisi :
\if{\result1=-1}{il n'est pas \quadra&nbsp;}{ il est bien \quadra&nbsp;}:
<div class="wimscenter">
\draw{\SIZE}{\DessinF}</div>}
