target=chgrcarre chgrcube chgrsqrt
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

%% couleur des grilles
\text{gridcolor=lightblue}

%% cadre générique %%
%% Modification du repère avec vecteurs en repère (O,I,J)%%
\text{cadre=
xrange -2,2
yrange -2.5,2.5
gridfill 0,0,5,5,\gridcolor
linewidth 3
vline 1,0,\gridcolor
vline 2,0,\gridcolor
vline -1,0,\gridcolor
vline -2,0,\gridcolor
hline 0,1,\gridcolor
hline 0,2,\gridcolor
hline 0,-1,\gridcolor
hline 0,-2,\gridcolor
linewidth 1
vline 0,0,black
hline 0,0,black
#if defined TARGET_chgrcarre
linewidth 3
points red,1,0,0,1,0,0
text red,1,-0.1,medium,I
text red,-0.2,1.2,medium,J
text red,-0.2,-0.1,medium,O
linewidth 2
#endif
#if defined TARGET_chgrcube || defined TARGET_chgrsqrt
arrow 0,0,1,0,10,magenta
arrow 0,0,0,1,10,magenta
text red,0.7,-0.1,medium,i
text red,-0.2,0.7,medium,j
text black,-0.2,-0.1,medium,O
#endif
}
%% fin du cadre générique %%
#if defined TARGET_chgrcarre
\text{n=2}
#endif
#if defined TARGET_chgrcube
\text{n=3}
#endif
%% liste de trinomes %%
%% on va considérer des trinomes s'écrivant: a(x-b)^\n+c %%
\text{aList=-2,-1,1,2}
\text{bList=-3/2,-1,-1/2,0,1/2,1,3/2}
\text{cList=-1,-3/4,-1/2,-1/4,0,1/4,1/2,3/4,1}

\text{foncsList=}
#if defined TARGET_chgrsqrt
\text{domsList=}
#endif
\for{a in \aList}{
  \for{b in \bList}{
    \for{c in \cList}{
#if defined TARGET_chgrsqrt
      \text{tempf=(\a)*sqrt(x-(\b))+\c}
      \text{domsList=wims(append item \b to \domsList)}
#else
      \text{tempf=(\a)*(x-(\b))^\n+\c}
#endif
      \text{foncsList=wims(append item \tempf to \foncsList)}
    }
  }
}

%% choix aléatoire de 4 fonctions dans la liste ci-dessus %%
\text{foncsList=shuffle(\foncsList)}
\text{permutfoncs=shuffle(4)}
\integer{f1=item(1,\permutfoncs)}
\integer{f2=item(2,\permutfoncs)}
\integer{f3=item(3,\permutfoncs)}
\integer{f4=item(4,\permutfoncs)}
\text{tf1=\foncsList[\f1]}
text{tf1=maxima(expand(\tf1);)}
\text{tf1=maxima(\tf1;)}
\text{tf1=texmath(\tf1)}
\text{tf2=\foncsList[\f2]}
text{tf2=maxima(expand(\tf2);)}
\text{tf2=maxima(\tf2;)}
\text{tf2=texmath(\tf2)}
\text{tf3=\foncsList[\f3]}
text{tf3=maxima(expand(\tf3);)}
\text{tf3=maxima(\tf3;)}
\text{tf3=texmath(\tf3)}
\text{tf4=\foncsList[\f4]}
text{tf4=maxima(expand(\tf4);)}
\text{tf4=maxima(\tf4;)}
\text{tf4=texmath(\tf4)}

%% on choisit d'afficher la première formule dans foncsList (après permutatation) %%
\text{f=item(1,\foncsList)}
\text{f=maxima(\f;)} %%permet de ne pas écrire "-0"%%
\text{f=texmath(\f)}
%% la bonne réponse %%
\integer{brep=position(1,\permutfoncs)}
%% codes des quatre graphes à afficher %%
\text{couleurs=shuffle(red,blue,orange,green)}
\text{graph1=
\cadre
#if defined TARGET_chgrsqrt
range \domsList[\f1],2
#endif
plot \couleurs[1],\foncsList[\f1]
}
\text{graph2=
\cadre
#if defined TARGET_chgrsqrt
range \domsList[\f2],2
#endif
plot \couleurs[2],\foncsList[\f2]
}
\text{graph3=
\cadre
#if defined TARGET_chgrsqrt
range \domsList[\f3],2
#endif
plot \couleurs[3],\foncsList[\f3]
}
\text{graph4=
\cadre
#if defined TARGET_chgrsqrt
range \domsList[\f4],2
#endif
plot \couleurs[4],\foncsList[\f4]
}
%% enoncé de l'exo %%
\text{enonce=wims(replace internal XXXX by \(f(x)=\f\) in \name_enonce)}
\statement{
\enonce
  <table class="wimscenter wimsborder">
    <tr>
      <td>
        \embed{reply 1,1}
      </td><td>
        \draw{200,200}{\graph1}
      </td><td>
        \embed{reply 1,2}
      </td><td>
        \draw{200,200}{\graph2}
      </td>
    </tr><tr>
      <td>
        \embed{reply 1,3}
      </td><td>
        \draw{200,200}{\graph3}
      </td><td>
        \embed{reply 1,4}
      </td><td>
        \draw{200,200}{\graph4}
      </td>
    </tr>
  </table>
}
%% soumission de réponse %%
\reply{\rep}{\brep;1,2,3,4}{type=radio}

\feedback{1=1}{\name_graph 1: \(\tf1)<br>
\name_graph 2: \(\tf2)<br>
\name_graph 3: \(\tf3)<br>
\name_graph 4: \(\tf4)
}
#if defined TARGET_chgrcarre
\solution{\name_sol}
#endif
