%%%%% VARIABLES DE L'EXERCICE %%%%%

%%% Recup confparm %%%
\text{conf1=\confparm1 == ? 1 : \confparm1}
\text{conf1=randitem(\conf1)}
\text{conf2=\confparm2 == ? 1 : \confparm2}
\text{conf2=randitem(\conf2)}

%%% choix des noms de la variable et de la fonction %%%
\text{x = randitem(x , t)}
\if{\x = x}
   {\text{f = randitem(f,g,h)}
    \text{y = t}
   }
   {\text{f = randitem(u,v,w)}
    \text{y = x} 
   }

%%% fonctions polynôme et exponentielle %%%

%%Coefficients de ax^2+bx+c et mx+p (entiers par défaut)
  \integer{a = (-1)^randitem(0,1)*randint(1..10)}
  \integer{b = (-1)^randitem(0,1)*randint(0..10)}
  \integer{c = (-1)^randitem(0,1)*randint(0..10)}
  \integer{m = (-1)^randitem(0,1)*randint(1..10)}
  \integer{p = (-1)^randitem(0,1)*randint(1..10)} 

%le polynôme est de degré 1
# if defined TARGET_1k_exp || defined TARGET_2aff_exp || defined TARGET_4Qexp_k || defined TARGET_5Qexp_aff
   \integer{a = 0}
   \if{\b == 0}{\integer{b = 1}}
# endif
 
%le polynôme est constant non nul et différent de 1
# if defined TARGET_1k_exp || defined TARGET_4Qexp_k
   \integer{b = 0}
   \if{\c == 0 or \c == 1}{\integer{c=-1}}
# endif

%cas des coefficients décimaux
\if{\conf1 == 2}
 {\real{a = \a/randitem(1,2,4,5,10)}
  \real{b = \b/randitem(1,2,4,5,10)}
  \real{c = \c/randitem(1,2,4,5,10)}
  \real{m = \m/randitem(1,2,4,5,10)}
  \real{p = \p/randitem(1,2,4,5,10)}
 }

%cas des coefficients rationnels
\if{\conf1 == 3} 
 {\rational{a = \a/randitem(1,2,4,5,10)}
  \rational{b = \b/randitem(1,2,4,5,10)}
  \rational{c = \c/randitem(1,2,4,5,10)}
  \rational{m = \m/randitem(1,2,4,5,10)}
  \rational{p = \p/randitem(1,2,4,5,10)}
 }

%Pour exp(mx+p)/c : c est entier
  # if defined TARGET_4Qexp_k
    \if{\conf1 == 3}
     {\integer{c = (-1)^randitem(0,1)*randint(2..10)}}
  # endif
  
% mx+p = x (par défaut)
 \if{\conf2 == 1}
 {\integer{m = 1}
  \integer{p = 0}
 }

% mx+p = mx  avec m!=1 et p=0
\if{\conf2 == 2}
 {\integer{p = 0}
  \if{\m=1}{\integer{m=-1}}
 }

#if defined TARGET_4Qexp_k || defined TARGET_5Qexp_aff || defined TARGET_6Qexp_secdeg
 \if{\conf1 == 2}{
  \real{c = randitem(1,2,4,5,8,12.5,25)/10}
  #if defined TARGET_5Qexp_aff || defined TARGET_6Qexp_secdeg
   \real{b = randitem(1,2,4,5,8,12.5,25)/10}
   #if defined TARGET_6Qexp_secdeg
    \real{a = randitem(1,2,4,5,8,12.5,25)/10}
   #endif  
  #endif
 }
#endif
% Ne pas avoir -1 au dénominateur
#if defined TARGET_4Qexp_k
 \if{\c=-1}{\integer{c=randint(2..10)}}
#endif

%Pour exp(mx+p)/(ax^2+bx+c) : si delta>=0, remplacer ax^2+bx+c par a(x-b)(x-c) dont les racines sont b et c
# if defined TARGET_6Qexp_secdeg || defined TARGET_5Qexp_aff
  \real{discr = (\b)^2 - 4*\a*\c}
  \if{\discr >= 0 }
     {\rational{pa = \a}
      \rational{pb = -\a*\b - \a*\c}
      \rational{pc = \a*\b*\c}
      \rational{b_int=\b}
      \rational{c_int=\c}
      \rational{a = \pa}
      \rational{b = \pb}
      \rational{c = \pc}
     } 
  \if{\a=0}{
    \rational{b=\b_int} 
    \rational{c=-\b_int*\c_int} 
  }
# endif

%%%%Fonction f(x)=(ax^2+bx+c)exp(mx+p) ou f(x)=exp(mx+p)/(ax^2+bx+c) 
%(ax^2+bx+c)
\text{trino=slib(polynet \a*\x^2 + \b*\x + \c,\x)}
\function{polyn=(pari(\trino))}  
\function{poly=pari(\trino)}
\if{\x isvarof \poly}{
  \text{polyaff=\left(texmath(\poly)\right)}
  }
  {\text{polyaff=texmath(\poly)}}
\text{polyaffdeno=\polyaff}

\if{(\a=0 and \c=0 and \b>0) or (\a>0 and \c=0 and \b=0)}
  {\text{polyaff=texmath(\poly)}}
  
%mx+p = x ou mx+p=(mx+p)  
\if{\m == 1 and \p == 0}
   {\function{aff = \x}
   }
   {\function{aff = (pari(\m*\x + \p))}
   }
%%f(x)=(ax^2+bx+c)exp(mx+p) avec e en romain
# if defined TARGET_1k_exp || defined TARGET_2aff_exp || defined TARGET_3secdeg_exp
  \function{fonc = (pari(\a*\x^2 + \b*\x + \c)) * e^\aff}
  \text{fonc_modif = wims(replace internal e by aaa in \fonc)}
  \text{fonc_tex = texmath(\fonc_modif)}
  \text{fonc_tex = wims(replace internal aaa by \mathrm{e} in \fonc_tex)}
# endif
%%f(x)=exp(mx+p)/(ax^2+bx+c) avec e en romain
# if defined TARGET_4Qexp_k || defined TARGET_5Qexp_aff || defined TARGET_6Qexp_secdeg
  \text{deno=texmath(\trino)}
  \text{afft=texmath(pari(\aff))}
  \text{fonc_tex= \dfrac{\mathrm{e}^{\afft}}{\deno}}
  # if defined TARGET_4Qexp_k
    %pour exp(mx+p)/k et k<0 alors f(x)=-exp(mx+p)/(-k) ou k=-1 
    \if{\c < 0}
       {\text{deno = pari(-1*\c)}
        \text{fonc_tex = -\dfrac{\mathrm{e}^{\afft}}{\deno}}
       }   
  # endif
# endif

%%%   Domaine de dérivabilité   %%%
# if defined TARGET_1k_exp || defined TARGET_2aff_exp || defined TARGET_3secdeg_exp || defined TARGET_4Qexp_k
  \text{Int = \mathbb{R}}
# endif

# if defined TARGET_5Qexp_aff
  \rational{borne = \c_int}
  \text{borne=slib(polynet \borne)}
  \text{Int = randitem(0,1) == 0 ? \left \rbrack texmath(\borne) \, ; +\infty \right \lbrack : \left \rbrack -\infty \, ;  texmath(\borne) \right \lbrack }
# endif 

# if defined TARGET_6Qexp_secdeg
  \rational{lborne =min(\b_int,\c_int)}
  \rational{rborne =max(\b_int,\c_int)}
     \if{\discr < 0}
        {\text{Int = \mathbb{R}}
        }
        {\if{randitem(0,1) == 0}
            {\text{Int = randitem(0,1) == 0 ? \left \rbrack texmath(\rborne) \, ; +\infty \right \lbrack : \left \rbrack -\infty \, ; texmath(\lborne) \right \lbrack }
            }
            {\text{Int = \discr > 0 ? \left \rbrack texmath(\lborne) \, ; texmath(\rborne) \right \lbrack : \left \rbrack -\infty \, ; texmath(\lborne) \right \lbrack }
            }
        }
# endif 


%%%  Fonction dérivée  %%%

\rational{da = \m*\a}
\rational{d2a = 2*\a}

# if defined TARGET_1k_exp || defined TARGET_2aff_exp || defined TARGET_3secdeg_exp
  \rational{db = \m*\b + 2*\a}
  \rational{dc = \m*\c + \b}
# endif
 
# if defined TARGET_4Qexp_k || defined TARGET_5Qexp_aff || defined TARGET_6Qexp_secdeg
  \rational{db = \m*\b - 2*\a}
  \rational{dc = \m*\c - \b}
# endif
 

\text{expo = pari(\m*\x + \p)}
\text{expoaff = texmath(\expo)}
\text{dpoly=slib(polynet \da*\x^2 + \db*\x + \dc,\x)}
\function{dpoly = (\dpoly)}

\text{derpoly = slib(polynet \d2a*\x + \b,\x)}

\if{(\x isvarof \derpoly and \b != 0) or (\a <0 and \b=0)}
   {\text{derpolyaff = \left(texmath(\derpoly)\right)}
   }
   {\text{derpolyaff = texmath(\derpoly)}
   }

# if defined TARGET_1k_exp || defined TARGET_2aff_exp || defined TARGET_3secdeg_exp || defined TARGET_4Qexp_k
\if{\m < 0}
   {\text{coefm = \left(texmath(\m)\right) \times}
   }
   {\text{coefm = texmath(\m) \times}
   }

# else
 \text{coefm = texmath(\m) \times}
#endif
\if{\m = 1 and \p = 0}
   {\text{coefm =}}

\text{facteur1aff = slib(polynet \m*(\poly),\x,tex)}

\if{(\a=0 and \b*\m>0) or (\a*\m>0 and \b=0 and \c=0) }
  {\text{facteur1aff =\facteur1aff}}
  {\text{facteur1aff =\left(\facteur1aff \right)}}

# if defined TARGET_1k_exp || defined TARGET_2aff_exp || defined TARGET_3secdeg_exp
  % bonne réponse
    \function{rep1 = (pari(\da*\x^2 + \db*\x + \dc))*e^(pari(\m*\x + \p))}
     %%function{rep1 = (\da*\x^2 + \db*\x + \dc)*e^(\m*\x + \p)}
  % mauvaise réponse : élève a fait (uv)'= u'*v' 
    \function{rep2 =((2*\a*\x + \b)*\m )* e^(\m*\x + \p)} 
  % mauvaise réponse : élève a fait (exp(u))' = exp(u)
    \function{rep3 = (\a*\x^2 + (2*\a + \b)*\x + \c + \b)*e^(\m*\x + \p)} 

\function{dfonc = \dpoly * e^\aff}
\text{dfonc_modif = wims(replace internal e by aaa in \dfonc)}
\text{dfonc_tex = texmath(\dfonc_modif)}
\text{dfonc_tex = wims(replace internal aaa by \mathrm{e} in \dfonc_tex)}
\text{dfonc_disp = wims(replace internal . by , in \dfonc_tex)}
\text{facteur = pari(\derpoly + (\m) * (\poly))}
\text{facteuraff=texmath(\facteur)}

\text{dfoncLx1 = \derpolyaff \times \mathrm{e}^{\expoaff} + \polyaff  \times \coefm \mathrm{e}^{\expoaff}}
\text{dfoncLx2 = \left(\derpolyaff + \facteur1aff  \right) \mathrm{e}^{\expoaff}}
\text{dfoncLx3 =\dfonc_disp}

\integer{nbSol = 3}
  
\if{\a == 0 and \b == 0}
   {\text{dfoncLx1 = \polyaff  \times \coefm \mathrm{e}^{\expoaff}}
    \text{dfoncLx2 =\dfonc_disp}
    \integer{nbSol = 2}
    \if{\m == 1 and \c == -1}
       {\text{dfoncLx2 = -\mathrm{e}^{\expoaff}}
       } 
   }
# endif

# if defined TARGET_4Qexp_k || defined TARGET_5Qexp_aff || defined TARGET_6Qexp_secdeg
   % bonne réponse
    %%function{rep1 =  (\da * \x^2 + \db*\x + \dc)*e^(\m*\x + \p)/(\a*\x^2 + \b*\x + \c)^2}
    \function{rep1 =  (pari(\da * \x^2 + \db*\x + \dc))*e^(pari(\m*\x + \p))/(pari(\a*\x^2 + \b*\x + \c))^2}
   % mauvaise réponse : (u/v)'= u'/v'
    \function{rep2 =\m*e^(\m*\x + \p)/(2*\a*\x + \b)} 
   % mauvaise réponse : (exp(u))' = exp(u)
    \function{rep3 = (\a*\x^2 + (-2*\a + \b)*\x + \c - \b)*e^(\m*\x + \p)/(\a*\x^2 + \b*\x + \c)^2} 
 
  # if defined TARGET_5Qexp_aff
    \if{\b<0}
      {\text{derpolyaff = \left(texmath(\derpoly)\right)}}
  # endif
  
  %%%%%%%function{dfonc = maxima((\dpoly * e^(\expo))/(\polyn^2))}
  
  # if defined TARGET_4Qexp_k 
    \text{coef4=slib(polynet \dpoly/\polyn^2)}
    \if{\conf2!=1}
     {\function{dfonc = \coef4 * e^(\expo)}}
     {\function{dfonc = \coef4 * e^\expo}}
  # else
    %%%%%%%function{dfonc = maxima((\dpoly * e^(\expo))/(\polyn^2))}
    \if{(\a=0 and \c=0) or (\b=0 and \c=0)}
      {\function{polyncarre=pari((\trino)^2)}
        \text{coef4=\dpoly/(\polyncarre)}
      }
      {\text{coef4=\dpoly/\polyn^2}}
    \if{\conf2!=1}
     {\function{dfonc = (\coef4) * e^(\expo)}}
     {\function{dfonc = (\coef4) * e^\expo}}
  # endif
 
\text{dfonc_modif = wims(replace internal e by aaa in \dfonc)}
\text{dfonc_tex = texmath(\dfonc_modif)}
\text{dfonc_tex = wims(replace internal aaa by \mathrm{e} in \dfonc_tex)}
 
\text{dfonc_disp = wims(replace internal . by , in \dfonc_tex)}
\text{facteur = pari(-(\derpoly - (\m) * (\poly)))}
\text{facteuraff=texmath(\facteur)}

\text{dfoncLx1 = \dfrac{\coefm \mathrm{e}^{\expoaff} \times \polyaff -\mathrm{e}^{\expoaff} \times \derpolyaff}{\polyaffdeno^2}}
\text{dfoncLx2 = \dfrac{\left(\facteur1aff -\derpolyaff \right) \mathrm{e}^{\expoaff}}{\polyaffdeno^2}}

\text{dfoncLx3 =\dfonc_disp}
\integer{nbSol = 3}
  # if defined TARGET_4Qexp_k 
    \text{dfoncLx1 = \dfrac{1}{\deno} \times \coefm \mathrm{e}^{\afft}}
    \text{dfoncLx2 = \dfonc_tex}
    \integer{nbSol = 2}
    \if{\c < 0}
       {\text{deno = pari(-1*\c)}
        \text{dfoncLx1 = -\dfrac{1}{\deno} \times \coefm \mathrm{e}^{\afft}}
        \text{dfoncLx2 = \dfonc_tex}
       }
  # endif    
# endif 

\text{Int = wims(replace internal . by , in \Int)}
\text{fonc_disp = wims(replace internal . by , in \fonc_tex)}

\text{dfoncLx1 = wims(replace internal . by , in \dfoncLx1)}
\text{dfoncLx2 = wims(replace internal . by , in \dfoncLx2)}
\text{dfoncLx3 = wims(replace internal . by , in \dfoncLx3)}

%%% variables pour après statement %%%
\text{Delta2=}
\text{Delta3=}
\function{rep=}

%%%% Bloc solution %%%
\text{soluce =
      \(\forall \x \in \Int,\, \f^'(\x)=\dfoncLx1\)
     }
\if{\nbSol > 1}
   {\text{soluce = \soluce
                   <br>
                   \(\phantom{\forall \x \in \Int,\, \f^'(\x)}=\dfoncLx2\)
         }
    \if{\nbSol == 3 }
       {\text{soluce = \soluce
                       <br> 
                       \(\phantom{\forall \x \in \Int,\, \f^'(\x)}=\dfoncLx3\)
             }
       }
   }
%%%% Largeur des champs réponse %%%
# if defined TARGET_1k_exp ||  defined TARGET_4Qexp_k
 \integer{largeur=40}
# else
 \integer{largeur=70}
#endif
