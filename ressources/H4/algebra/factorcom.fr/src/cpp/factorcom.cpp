target= factorcom1 eqfactorcom1 eqfactorcom2
#if defined TARGET_factorcom1
 \title{Factorisation}
#endif
#if defined TARGET_eqfactorcom1
 \title{Equation 1}
#endif
#if defined TARGET_eqfactorcom2
 \title{Equation 2}
#endif
\language{fr}
\author{David Doyen}
\email{david.doyen@u-pem.fr}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Paramètres de configuration
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Nombre de termes

\if{\confparm1=}{\text{ntermes=3}}{\text{ntermes=\confparm1}}

% Type du facteur commun

\text{temp=wims(listintersect \confparm2 and A,B,C,D,E)}
\if{\temp=}{\text{typeFC=A}}{\text{typeFC=randitem(\temp)}}

% Types des termes de l'expression

\text{temp=wims(listintersect \confparm2 and 1,2,3,4,5,6,7)}
\text{ntemp=items(\temp)}

\if{\ntemp=0}{\text{typetermes=2,2,2,2}}
\if{\ntemp=1}{\text{typetermes=\temp,\temp,\temp,\temp}}
\if{\ntemp>=2}{\text{typetermes=shuffle(\temp),shuffle(\temp)}}

% Facteur apparent

\text{FCapp=1}
\if{\confparm3=2}{\text{FCapp=0}}

% Complexité des coefficients

\text{n=6}
\text{nn=2}
\text{m=1}
\text{ls=+,-}
\if{\confparm4=1}{\text{ls=+}}
\if{\confparm4=3}{\text{n=15}\text{nn=5}}
\if{\confparm4=4}{\text{m=6}}

% Nom de la variable

\text{x=x}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Génération du facteur commun FC
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% On génère coefficients a et b du facteur commun.
% Si l'option facteur commun non-apparent a été choisie, des coefficients multiplicatifs
% pour les différentes occurences du facteur commun sont aussi générés.
% Ces coefficients valent 1, 2 ou 3 et sont stockés dans liste \lk.

\if{\FCapp=1}{
	\rational{a=randint(1..\n)/randint(1..\m)}
	\rational{b=randitem(-1,1)*randint(1..\n)/randint(1..\m)}
	\rational{a2=\a}\rational{b2=\b}
	\rational{a3=\a}\rational{b3=\b}
	\text{coeffFC=1,1,1}
	\text{lk=1,1,1,1}
}{
	\rational{a=randint(1..\nn)/randint(1..\m)}
	\rational{b=randitem(-1,1)*randint(1..\nn)/randint(1..\m)}
	\rational{a2=2*\a}\rational{b2=2*\b}
	\rational{a3=3*\a}\rational{b3=3*\b}
	\text{coeffFC=1,2,3}
	\text{lk=shuffle(1,2,3)}
	\text{lk=\lk[1..2]}
	\text{lk=\lk,shuffle(1,2,3)}
}
\text{gcdab=pari(gcd(\a,\b))}
\rational{aa=\a/(\gcdab)}
\rational{bb=\b/(\gcdab)}

% Facteur commun du type A : ax+b

\if{\typeFC=A}{
	\text{FC=(\a*\x+\b),(\a2*\x+\b2),(\a3*\x+\b3)} % Facteur commun
	\text{FCfact1=\gcdab}
	\text{FCfact2=(\aa*\x+\bb)} % Forme factorisée du facteur commun
	\text{T67=(\a*\x+\b)^2,(\a2*\x+\b2)^2,(\a3*\x+\b3)^2} % Terme employé pour les types 6 et 7
	\text{F67=\FC} % Facteur employé pour les types 6 et 7
	\rational{sol=-\b/\a}
}

% Facteur commun du type B : (ax+b)^2

\if{\typeFC=B}{
	\text{FC=(\a*\x+\b)^2,(\a2*\x+\b2)^2,(\a3*\x+\b3)^2} % Facteur commun
	\rational{FCfact1=(\gcdab)^2}
	\text{FCfact2=(\aa*\x+\bb)^2} % Forme factorisée du facteur commun
	\text{T67=(\a*\x+\b)^3,(\a2*\x+\b2)^3,(\a3*\x+\b3)^3} % Terme employé pour les types 6 et 7
	\text{F67=(\a*\x+\b),(\a2*\x+\b2),(\a3*\x+\b3)} % Facteur employé pour les types 6 et 7
	\text{coeffFC=1,4,9}
	\rational{sol=-\b/\a}
}

% Facteur commun du type C : ax^2+bx

\if{\typeFC=C}{
	\text{FC=(\a*\x^2+\b*x),(\a2*\x^2+\b2*x),(\a3*\x^2+\b3*x)} % Facteur commun
	\text{FCfact1=\gcdab*x}
	\text{FCfact2=(\aa*\x+\bb)} % Forme factorisée du facteur commun
	\text{T67=(\a*\x^3+\b*x^2),(\a2*\x^3+\b2*x^2),(\a3*\x^3+\b3*x^2)} % Terme employé pour les types 6 et 7
	\text{F67=\x,\x,\x} % Facteur employé pour les types 6 et 7
	\rational{sol=-\b/\a}
	\text{sol=0,\sol}
}

% Facteur commun du type D : (ax^2+b) avec b>0

\if{\typeFC=D}{
	\rational{b=abs(\b)}\rational{b2=abs(\b2)}\rational{b3=abs(\b3)}\rational{bb=abs(\bb)}
	\text{FC=(\a*\x^2+\b),(\a2*\x^2+\b2),(\a3*\x^2+\b3)} % Facteur commun
	\text{FCfact1=\gcdab}
	\text{FCfact2=(\aa*\x^2+\bb)} % Forme factorisée du facteur commun
	\text{T67=(\a*\x^3+\b*x),(\a2*\x^3+\b2*x),(\a3*\x^3+\b3*x)} % Terme employé pour les types 6 et 7
	\text{F67=\x,\x,\x} % Facteur employé pour les types 6 et 7
	\text{sol=}
}

% Facteur commun du type E : (ax^2+b) avec b<0

\if{\typeFC=E}{
	\rational{b=abs(\b)}\rational{b2=abs(\b2)}\rational{b3=abs(\b3)}\rational{bb=abs(\bb)}
	\text{sq=maxima(sqrt(\b/\a))}
	\text{FC=(\a*\x^2-\b),(\a2*\x^2-\b2),(\a3*\x^2-\b3)} % Facteur commun
	\text{FCfact1=\a}
	\text{FCfact2=(\x-\sq)*(\x+\sq)} % Forme factorisée du facteur commun
	\text{T67=(\a*\x^3-\b*x),(\a2*\x^3-\b2*x),(\a3*\x^3-\b3*x)} % Terme employé pour les types 6 et 7
	\text{F67=\x,\x,\x} % Facteur employé pour les types 6 et 7
	\text{sol=\sq,-\sq}
}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Génération des différents termes de l'expression
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% On génére les différents termes de l'expression.
% Les termes sont ajoutés au fur et à mesure à la variable \poly.
% Les facteurs correspondants sont ajoutés à la variable \SF.
% Si l'expression finale est égale au polynôme nul, on recommence.
% Pour éviter d'obtenir des termes identiques, on garde en mémoire les termes déjà générés
% dans les listes \lT12, \lT3, \lT4 et \lT6. Ces listes contiennent également, dès l'initialisation,
% des valeurs particulières que l'on souhaite éviter.

\text{SFred=0}

#if defined TARGET_eqfactorcom2
\text{poseq=randint(2..\ntermes)}
#endif

\while{\SFred=0}{

\text{poly=}
\text{eq=}
\text{SF=}
\text{lT12=\FC}\integer{nT12=1}
\text{lT3=1}\integer{nT3=1}
\text{lT4=1}\integer{nT4=1}
\text{lT6=1}\integer{nT6=1}

\for{i=1 to \ntermes}{

\text{type=\typetermes[\i]}
\text{k=\lk[\i]}

% Terme des types 1 ou 2 : e*FC*(cx+d) ou FC*(cx+d)

\if{\type<=2}{
	\text{ok=0}
	\while{\ok=0}{
		\rational{c=randint(1..\n)/randint(1..\m)}
		\rational{d=randitem(-1,1)*randint(1..\n)/randint(1..\m)}
		\text{temp=pari(\c*\x+\d)}
		\text{ok=1}
		\for{j=1 to \nT12}{
			\text{temp2=pari(\temp-(\lT12[\j]))}
			\if{\temp2=0}{\text{ok=0}}
		}
	}
	\text{lT12=\lT12,\temp}
	\integer{nT12=\nT12+1}
	\if{\type=1}{
		\rational{e=randint(2..5)}
		\text{F=\e*(\temp)}
		\text{T=randitem(\e*(\temp)*\FC[\k],\e*\FC[\k]*(\temp))}
	}{
		\text{F=(\temp)}
		\text{T=randitem((\temp)*\FC[\k],\FC[\k]*(\temp))}
	}
}


% Terme du type 3 : cx*FC

\if{\type=3}{
	\text{ok=0}
	\while{\ok=0}{
		\rational{c=randint(1..\n)/randint(1..\m)}
		\text{ok=1}
		\for{j=1 to \nT3}{
			\text{temp=simplify(\c-\lT3[\j])}
			\if{\temp=0}{\text{ok=0}}
		}
	}
	\text{lT3=\lT3,\c}
	\integer{nT3=\nT3+1}
	\text{F=\c*\x}\text{T=\F*\FC[\k]}
}

% Terme du type 4 : c*FC

\if{\type=4}{
	\text{ok=0}
	\while{\ok=0}{
		\rational{c=randint(1..\n)/randint(1..\m)}
		\text{ok=1}
		\for{j=1 to \nT4}{
			\text{temp=simplify(\c-\lT4[\j])}
			\if{\temp=0}{\text{ok=0}}
		}
	}
	\text{lT4=\lT4,\c}
	\integer{nT4=\nT4+1}
	\text{F=\c}\text{T=\F*\FC[\k]}
}

% Terme du type 5 : FC

\if{\type=5}{\text{F=1}\text{T=\FC[\k]}}

% Terme du type 6 : dépendant du type de facteur commun

\if{\type=6}{
	\text{ok=0}
	\while{\ok=0}{
		\rational{c=randint(1..\n)/randint(1..\m)}
		\text{ok=1}
		\for{j=1 to \nT6}{
			\text{temp=simplify(\c-\lT6[\j])}
			\if{\temp=0}{\text{ok=0}}
		}
	}
	\text{lT6=\lT6,\c}
	\integer{nT6=\nT6+1}
	\text{F=\c*\F67[\k]}\text{T=\c*\T67[\k]}
}

% Terme du type 7 : dépendant du type de facteur commun

\if{\type=7}{\text{F=\F67[\k]}\text{T=\T67[\k]}}

% Ajout du terme à l'expression

\text{s=randitem(\ls)} % Le signe du terme est tiré au sort.
\text{ss=\s}
\if{(\i=1) and (\s=+)}{\text{ss=}} % Gestion du signe + en début d'expression
\text{poly=\poly \ss \T} % Le terme est ajouté à l'expression.
\text{SF=\SF \ss \coeffFC[\k]*\F} % Le facteur correspondant est ajouté à la somme des facteurs.
#if defined TARGET_eqfactorcom1
\text{eq=\eq \ss \T} % Le terme est ajouté à l'équation.
#endif
#if defined TARGET_eqfactorcom2
\if{(\i>=\poseq) and (\s=+)}{\text{ss=-}}
\if{(\i>\poseq) and (\s=-)}{\text{ss=+}}
\if{(\i=\poseq) and (\s=-)}{\text{ss=}}
\if{\i=\poseq}{\text{eq=\eq = \ss \T}} % Le terme est ajouté à l'équation.
\if{\i<>\poseq}{\text{eq=\eq \ss \T}} % Le terme est ajouté à l'équation.
#endif

}

\text{SFred=pari(\SF)}
}

#if defined TARGET_eqfactorcom1
\text{eq=\eq=0}
#endif


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Factorisations de l'expression (partielles et totale)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\text{polyfact1=\FC[1]*(\SF)}
\text{polyfact2=\FC[1]*(\SFred)}

\text{deg=pari(poldegree(\SFred,\x))}
\if{\deg=1}{
	\text{a=pari(polcoeff(\SFred,1))}
	\text{b=pari(polcoeff(\SFred,0))}
	\if{\b=0}{
		\text{F1=simplify(\FCfact1*(\SFred))}
		\text{polyfact3=\F1*\FCfact2}
	}{
		\text{gcdab=pari(gcd(\a,\b))}
		\if{\a>0}{
			\rational{aa=\a/(\gcdab)}
			\rational{bb=\b/(\gcdab)}
			\text{F1=simplify(\FCfact1*\gcdab)}
		}{
			\rational{aa=-\a/(\gcdab)}
			\rational{bb=-\b/(\gcdab)}
			\text{F1=simplify(-\FCfact1*\gcdab)}
		}
		\text{polyfact3=\F1*\FCfact2*(\aa*x+\bb)}
	}
}{
	\text{F1=simplify(\FCfact1*(\SFred))}
	\text{polyfact3=\F1*\FCfact2}
}


#if defined TARGET_eqfactorcom1 || defined TARGET_eqfactorcom2
% Calcul de l'éventuelle racine du facteur \SFred

\text{deg=pari(poldegree(\SFred,\x))}
\if{\deg=1}{
	\rational{sol1=pari(-polcoeff(\SFred,0)/polcoeff(\SFred,1))}
	\text{sol=wims(append item \sol1 to \sol)}
}
\text{sol=wims(listuniq \sol)}
\if{\sol=}{\text{sol=vide}}
#endif

#if defined TARGET_factorcom1
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Enoncé de l'exercice
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\statement{Factoriser dans \({\mathbb{R}}\) l'expression suivante :
<p class="wimscenter">\(P(\x)=\poly\).</p>
<div>\(P(\x) =\)\embed{reply 1,40}</div>
}

\hint{Les différents termes de cette expression ont un facteur commun : \(\FC[1]\).}

\answer{}{\polyrep}{type=raw}{option=noanalyzeprint}
\text{polyrep=wims(rawmath \polyrep)}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Analyse de la réponse
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\text{degrep=pari(poldegree(\polyrep,\x))}

% On teste si la réponse est égale à l'expression de l'énoncé

\text{diff=simplify(\polyrep-(\poly))}
\if{\diff=0}{\text{iseq=1}}{\text{iseq=0}}

\if{\iseq=1}{

\text{temp=maxima(simp:false)}

% On identifie les différents facteurs de la réponse.
% Ces facteurs sont stockés dans la liste \fac (de taille \nbfac).

\text{polyrep2=\polyrep}

\if{\degrep<>}{

	% Gestion du cas où la réponse commence par un signe -
	\text{op=maxima(op(\polyrep2))}
	\if{\op issametext "-"}{
		\text{polyrep2=maxima(args(\polyrep2))}
	}

	% Gestion du cas où la réponse contient une division par un réel
	\text{op=maxima(op(\polyrep2))}
	\if{\op issametext "/"}{
		\text{polyrep2=maxima(args(\polyrep2))}
		\text{polyrep2=\polyrep2[1]}
	}

	\text{op=maxima(op(\polyrep2))}
	\if{\op issametext "*"}{
		\text{fac=maxima(args(\polyrep2))}
		\text{nbfac=items(\fac)}
		\text{areallfacirred=1}
		\text{areallfacsimp=1}
	}{
		\text{fac=\polyrep2}
		\text{nbfac=1}
		\text{areallfacirred=1}
		\text{areallfacsimp=1}
	}
}

% Pour chaque facteur de la réponse, on teste :
%	- s'il est irréductible dans R ;
%	- s'il est simplifié (sous forme réduite).
% Les facteurs non-irréductibles sont stockés dans la liste facnotirred.
% Les facteurs non-simplifiés sont stockés dans la liste facnotsimp.

\text{facnotsimp=}
\text{facnotirred=}

\for{i=1 to \nbfac}{

	\text{factor=\fac[\i]}

	% Gestion du signe "-"
	\text{op=maxima(op(\factor))}
	\if{(\op issametext "-")}{
		\text{factor=maxima(args(\factor))}
	}

	% Gestion du cas où le facteur est une puissance
	\text{op=maxima(op(\factor))}
	\if{(\op issametext "^")}{
		\text{factor=maxima(args(\factor))}
		\text{factor=\factor[1]}
	}

	% On teste si le facteur est simplifié (sous forme réduite).
	% Pour cela, on vérifie qu'il s'agit d'une somme de monômes et qu'il n'y a pas deux monômes de même degré.
	\text{deg=pari(poldegree(\factor,\x))}
	\text{op=maxima(op(\factor))}
	\if{(\op issametext "+")}{
		\text{terms=maxima(args(\factor))}
		\text{nbterms=items(\terms)}
		\text{degterms=}
		% On vérifie que chaque terme est un monôme
		\for{j=1 to \nbterms}{
			\text{term=\terms[\j]}
			\text{degterm=pari(poldegree(\term,\x))}
			\text{degterms=wims (append item \degterm to \degterms)}
			\text{coeff=pari(polcoeff(\term,\degterm))}
			\text{temp=simplify(\coeff*x^(\degterm)-(\terms))}
			\if{\temp<>0}{\text{facsimp=0}}
		}
		% On vérifie qu'il n'y a pas deux monômes de même degré.
		\text{temp1=items(\degterms)}
		\text{temp2=wims(listuniq \degterms)}
		\text{temp2=items(\temp2)}
		\if{(\facsimp<>0) or (\temp1<>\temp2)}{
			\text{facnotsimp=wims(append item \factor to \facnotsimp)}
			\text{areallfacsimp=0}
		}
	}

	% Si le facteur est de degré >= 3, alors il n'est pas irréductible
	\if{\deg>=3}{
		\text{areallfacirred=0}
		\text{facnotirred=wims (append item \factor to \facnotirred)}
	}
	% Si le facteur est de degré 2 et de discriminant positif, alors il n'est pas irréductible
	\if{\deg=2}{
		\text{a=pari(polcoeff(\factor,2))}
		\text{b=pari(polcoeff(\factor,1))}
		\text{c=pari(polcoeff(\factor,0))}
		\real{d=(\b)^2-4*\a*\c}
		\if{\d>=0}{
			\text{areallfacirred=0}
			\text{facnotirred=wims (append item \factor to \facnotirred)}
		}
	}

}

}


% Finalement, la réponse est correcte si :
% 	- elle est égale à l'expression de l'énoncé,
%	- tous les facteurs sont irréductibles,
%	- tous les facteurs sont simplifiés.

\condition{}{(\iseq=1) and (\areallfacirred=1) and (\areallfacsimp=1)}{option=hide}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Correction
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\if{(\iseq=1) and (\areallfacirred=1) and (\areallfacsimp=1)}{
	\text{affrepok=<div class="oef_indgood">Bonne réponse</div>}
}{
	\text{affrepok=<div class="oef_indbad">Mauvaise réponse</div>}
}

\if{\degrep=}{
	\text{anal1=Votre réponse n'est pas une expression polynômiale.}
}{
	\if{\iseq=0}{
		\text{anal1=Votre réponse n'est pas égale à l'expression de départ.}
	}
	\if{(\iseq=1) and (\areallfacirred=0)}{
		\text{ntemp=items(\facnotirred)}
		\if{\ntemp=1}{\text{anal2=Le terme \facnotirred n'est pas irréductible dans \({\RR}\) : il peut encore être factorisé.}}
		\if{\ntemp>1}{\text{anal2=Les termes \facnotirred ne sont pas irréductibles dans \({\RR}\) : ils peuvent encore être factorisés.}}
	}
	\if{(\iseq=1) and (\areallfacsimp=0)}{
		\text{ntemp=items(\facnotsimp)}
		\if{\ntemp=1}{\text{anal3=Le terme \facnotsimp n'est pas simplifié.}}
		\if{\ntemp>1}{\text{anal3=Les termes \facnotsimp ne sont pas simplifiés.}}
	}
}
\text{corr= \(\begin{array}{rcl} P(\x)&=&texmath(\polyfact1) \\ & = & texmath(\polyfact2) \\ & = & texmath(\polyfact3) \end{array}\)}

\feedback{1=1}{\affrepok}
\feedback{1=1}{\anal1}
\feedback{1=1}{\anal2}
\feedback{1=1}{\anal3}
\feedback{1=1}{<div class="bold" style="color:gray">Correction</div>
On remarque que le terme \(\FC[1]\) est un facteur commun à tous les termes de l'expression \(P(\x)\). D'où :<br>
\corr}
#endif

#if defined TARGET_eqfactorcom1 || defined TARGET_eqfactorcom2
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Enoncé de l'exercice
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\statement{Résoudre dans \({\mathbb{R}}\) l'équation suivante :
<p class="wimscenter">\(\eq\).</p>
<div>L'ensemble des solutions de cette équation est \embed{reply 1,20}</div>
<div class="wims_instruction"> Si l'équation n'a pas de solution, écrire le mot <span class="tt">vide</span> dans le champ de réponse.</div>
}

\hint{Les différents termes de l'équation ont un facteur commun : \(\FC[1]\).}

\answer{}{\solrep}{type=fset}{option=noanalyzeprint}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Analyse de la réponse
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\text{repok=maxima(is({\sol}={\solrep}))}
\condition{}{\repok issametext true}{option=hide}
\text{nbwrongans=maxima(cardinality(setdifference({\solrep},{\sol})))}
\text{nbmisssol=maxima(cardinality(setdifference({\sol},{\solrep})))}
\if{\sol=vide}{\text{nbmisssol=0}}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Correction
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\if{\repok issametext true}{
	\text{affrepok=<div class="oef_indgood">Bonne réponse</div>}
}{
	\text{affrepok=<div class="oef_indbad">Mauvaise réponse</div>}
}
\if{\nbmisssol>0}{
	\text{anal1=Vous avez oublié une ou plusieurs solutions de l'équation.}
}
\if{\nbwrongans>0}{
	\text{anal2=Une ou plusieurs de vos réponses ne sont pas des solutions de l'équation.}
}
\text{corr1= \(\begin{array}{rl}  & texmath(\eq)\\ \Leftrightarrow  & texmath(\polyfact1) = 0\\ \Leftrightarrow & texmath(\polyfact2) = 0 \\ \Leftrightarrow & texmath(\polyfact3) = 0 \end{array}\)}
\text{soltex=texmath(\sol)}
\if{\sol=vide}{
	\text{corr2=Cette équation n'a donc pas de solution (l'ensemble des solutions est vide).}
}{
	\text{corr2=L'ensemble des solutions de l'équation est donc \(\left\{\soltex\right\}\)}
}
\feedback{1=1}{\affrepok}
\feedback{1=1}{\anal1}
\feedback{1=1}{\anal2}
\feedback{1=1}{<div class="bold" style="color:gray">Correction</div>
On remarque que le terme \(\FC[1]\) est un facteur commun à tous les termes de l'équation. D'où : <br>
\corr1 <br>
\corr2}
#endif
