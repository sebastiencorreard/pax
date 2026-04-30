target= deg2ent1 deg2rat1 deg3ent2 deg3rat2 deg2noent deg2noentrat deg2norat
#if defined TARGET_deg2ent1
 \title{Polynôme de degré 2 (1 racine entière donnée)}
#endif
#if defined TARGET_deg3ent2
 \title{Polynôme de degré 3 (2 racines entières données)}
#endif
#if defined TARGET_deg2rat1
 \title{Polynôme de degré 2 (1 racine rationnelle donnée)}
#endif
#if defined TARGET_deg3rat2
 \title{Polynôme de degré 3 (2 racines rationnelles données)}
#endif
#if defined TARGET_deg2noent
 \title{Polynôme de degré 2 (pas de racine donnée) 1}
#endif
#if defined TARGET_deg2noentrat
 \title{Polynôme de degré 2 (pas de racine donnée) 2}
#endif
#if defined TARGET_deg2norat
 \title{Polynôme de degré 2 (pas de racine donnée) 3}
#endif
\language{fr}
\author{David Doyen}
\email{david.doyen@u-pem.fr}

\text{x=x}

#if defined TARGET_deg2ent1
\integer{x1=randitem(-1,1)*randint(1..5)}
\rational{x2=randitem(-1,1)*randitem(1/2,3/2,5/2,1/3,2/3,4/3,5/3,1/4,3/4,5/4,1/5,2/5,3/5,4/5,1/6,5/6,1/7,2/7,3/7,4/7)}
\text{b2=pari(denominator(\x2))}
\text{poly=simplify(randitem(-1,1)*randint(1..2)*(\x-\x1)*(\b2*\x-\b2*\x2))}
\text{Fr=(simplify(\x-\x1))}
#endif
#if defined TARGET_deg2rat1
\text{s=shuffle(1/2,3/2,5/2,1/3,2/3,4/3,5/3,1/4,3/4,5/4,1/5,2/5,3/5,4/5,1/6,5/6,1/7,2/7,3/7,4/7)}
\rational{x1=randitem(-1,1)*\s[1]}
\rational{x2=randitem(-1,1)*\s[2]}
\text{b1=pari(denominator(\x1))}
\text{b2=pari(denominator(\x2))}
\text{poly=simplify(randitem(-1,1)*randint(1..2)*(\b1*\x-\b1*\x1)*(\b2*\x-\b2*\x2))}
\text{Frbis=(\x-\x1)}
\text{Fr=(simplify(\b1*\x-\b1*\x1))}
#endif
#if defined TARGET_deg2noent
\text{s=shuffle(7)}
\integer{x1=randitem(-1,1)*\s[1]}
\integer{x2=randitem(-1,1)*\s[2]}
\text{poly=simplify(randitem(-1,1)*randint(1..3)*(\x-\x1)*(\x-\x2))}
\text{Fr=(simplify(\x-\x1))*(simplify(\x-\x2))}
#endif
#if defined TARGET_deg2noentrat
\integer{x1=randitem(-1,1)*randint(1..7)}
\rational{x2=randitem(-1,1)*randitem(1/2,3/2,5/2,1/3,2/3,4/3,5/3,1/4,3/4,5/4,1/5,2/5,3/5,4/5)}
\text{b2=pari(denominator(\x2))}
\text{poly=simplify(randitem(-1,1)*randint(1..3)*(\x-\x1)*(\b2*\x-\b2*\x2))}
\text{Frbis=(\x-\x1)(\x-\x2)}
\text{Fr=(simplify(\x-\x1))*(simplify(\b2*\x-\b2*\x2))}
#endif
#if defined TARGET_deg2norat
\text{s=shuffle(1/2,3/2,5/2,1/3,2/3,4/3,5/3,1/4,3/4,5/4,1/5,2/5,3/5,4/5)}
\rational{x1=randitem(-1,1)*\s[1]}
\rational{x2=randitem(-1,1)*\s[2]}
\text{b1=pari(denominator(\x1))}
\text{b2=pari(denominator(\x2))}
\text{poly=simplify(randitem(-1,1)*randint(1..3)*(\b1*\x-\b1*\x1)*(\b2*\x-\b2*\x2))}
\text{Frbis=(\x-\x1)(\x-\x2)}
\text{Fr=(simplify(\b1*\x-\b1*\x1))*(simplify(\b2*\x-\b2*\x2))}
#endif
#if defined TARGET_deg3ent2
\text{s=shuffle(5)}
\integer{x1=randitem(-1,1)*\s[1]}
\integer{x2=randitem(-1,1)*\s[2]}
\rational{x3=randitem(-1,1)*randitem(1/2,3/2,5/2,1/3,2/3,4/3,5/3,1/4,3/4,5/4,1/5,2/5,3/5,4/5,1/6,5/6,1/7,2/7,3/7,4/7)}
\text{b3=pari(denominator(\x3))}
\text{poly=simplify(randitem(-1,1)*(\x-\x1)*(\x-\x2)*(\b3*\x+\b3*\x3))}
\text{Fr=(simplify(\x-\x1))*(simplify(\x-\x2))}
#endif
#if defined TARGET_deg3rat2
\text{s=shuffle(1/2,3/2,5/2,1/3,2/3,4/3,5/3,1/4,3/4,5/4,1/5,2/5,3/5,4/5)}
\rational{x1=randitem(-1,1)*\s[1]}
\rational{x2=randitem(-1,1)*\s[2]}
\rational{x3=randitem(-1,1)*\s[3]}
\text{b1=pari(denominator(\x1))}
\text{b2=pari(denominator(\x2))}
\text{b3=pari(denominator(\x3))}
\text{poly=simplify(randitem(-1,1)*(\b1*\x-\b1*\x1)*(\b2*\x-\b2*\x2)*(\b3*\x-\b3*\x3))}
\text{Frbis=(\x-\x1)(\x-\x2)}
\text{Fr=(simplify(\b1*\x-\b1*\x1))*(simplify(\b2*\x-\b2*\x2))}
#endif


\text{Q=pari((\poly)/(\Fr))}
\text{poly=maxima(expand(\poly))}
\text{poly=pari(\poly)}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Enoncé de l'exercice
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\statement{
#if defined TARGET_deg2ent1 || TARGET_deg2rat1
Factoriser le polynôme \(P(x)=\poly\) en remarquant que \(P(\x1)=0\).<br class="spacer">
#endif
#if defined TARGET_deg3ent2 || TARGET_deg3rat2
Factoriser le polynôme \(P(x)=\poly\) en remarquant que \(P(\x1)=0\) et \(P(\x2)=0\).<br class="spacer">
#endif
#if defined TARGET_deg2noent || TARGET_deg2noentrat || TARGET_deg2norat
Factoriser le polynôme \(P(x)=\poly\).<br class="spacer">
#endif
\(P(\x) =\)\embed{reply 1,30}
}


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





#if defined TARGET_deg2ent1
\text{corr=Puisque \(\x1\) est racine de \(P\), alors \(P\) peut se factoriser par \(\Fr\). Autrement dit, \(P(x)=\Fr*Q(x)\), où \(Q\) est un polynôme à déterminer.<br>
Puisque \(P\) est un poynôme de degré 2, \(Q\) est nécessairement de degré 1 et donc \(P(x)=\Fr (a x + b)\).<br>
Il ne reste plus qu'à identifier \(a\) et \(b\) en développant (partiellement) l'expression \(\Fr (a x + b)\) et en la comparant à \(\poly\).<br>
On trouve finalement \(P(x)=\Fr (\Q)\).
}
#endif
#if defined TARGET_deg3ent2
\text{corr=Puisque \(\x1\) et \(\x2\) sont racines de \(P\), alors \(P\) peut se factoriser par \(\Fr\). Autrement dit, \(P(x)=\Fr*Q(x)\), où \(Q\) est un polynôme à déterminer.<br>
Puisque \(P\) est un poynôme de degré 3, \(Q\) est nécessairement de degré 1 et donc \(P(x)=\Fr (a x + b)\).<br>
Il ne reste plus qu'à identifier \(a\) et \(b\) en développant (partiellement) l'expression \(\Fr (a x + b)\) et en la comparant à \(\poly\).<br>
On trouve finalement \(P(x)=\Fr (\Q).\)
}
#endif
#if defined TARGET_deg2rat1
\text{corr=Puisque \(\x1\) est racine de \(P\), alors \(P\) peut se factoriser par \(\Frbis\) ou, ce qui est équivalent, par \(\Fr\). Autrement dit, \(P(x)=\Fr*Q(x)\), où \(Q\) est un polynôme à déterminer.<br>
Puisque \(P\) est un poynôme de degré 2, \(Q\) est nécessairement de degré 1 et donc \(P(x)=\Fr (a x + b)\).<br>
Il ne reste plus qu'à identifier \(a\) et \(b\) en développant (partiellement) l'expression \(\Fr (a x + b)\) et en la comparant à \(\poly\).<br>
On trouve finalement \(P(x)=\Fr (\Q)\).
}
#endif
#if defined TARGET_deg3rat2
\text{corr=Puisque \(\x1\) et \(\x2\) sont racines de \(P\), alors \(P\) peut se factoriser par \(\Frbis\) ou, ce qui est équivalent, par \(\Fr\). Autrement dit, \(P(x)=\Fr*Q(x)\), où \(Q\) est un polynôme à déterminer.<br>
Puisque \(P\) est un poynôme de degré 3, \(Q\) est nécessairement de degré 1 et donc \(P(x)=\Fr (a x + b)\).<br>
Il ne reste plus qu'à identifier \(a\) et \(b\) en développant (partiellement) l'expression \(\Fr (a x + b)\) et en la comparant à \(\poly.\)<br>
On trouve finalement \(P(x)=\Fr (\Q)\).
}
#endif
#if defined TARGET_deg2noent
\text{corr=On calcule les racines de \(P\) (par les formules habituelles) : les racines sont \(\x1\) et \(\x2\).<br>
Ainsi \(P\) peut se factoriser par \(\Fr\). Or \(P\) est un poynôme de degré 2, donc \(P(x)=a \Fr\), où \(a\) est un nombre à déterminer.<br>
On trouve finalement \(P(x)=\Q*\Fr\).}
#endif
#if defined TARGET_deg2noentrat || TARGET_deg2norat
\text{corr=On calcule les racines de \(P\) (par les formules habituelles) : les racines sont \(\x1\) et \(\x2\).<br>
Ainsi \(P\) peut se factoriser par \(\Frbis\) ou, ce qui est équivalent, par \(\Fr\). Or \(P\) est un poynôme de degré 2, donc \(P(x)=a \Fr\), où \(a\) est un nombre à déterminer.<br>
On trouve finalement \(P(x)=\Q*\Fr\).}
#endif

\feedback{1=1}{\affrepok}
\feedback{1=1}{\anal1}
\feedback{1=1}{\anal2}
\feedback{1=1}{\anal3}
\feedback{1=1}{<br><div class="bold" style="color:gray">Correction</div>
\corr}
