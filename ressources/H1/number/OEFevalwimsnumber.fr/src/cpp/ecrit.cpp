target=oefecrit1 oefecrit2 oefecrit3 oefecrit4 oefecrit5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_oefecrit1
\integer{maxchiffres=3}
\integer{dizaine=random(0..9)}
\integer{unite=random(0..9)}
\integer{centaine=\maxchiffres>2?random(1..9):0}
\if{\dizaine==0}
{\text{deuxderniers=item(\unite+1,\chiffres)}}
{\if{\dizaine isin 1,7,9}
{\text{dernier=\dizaine!=1?-item(\unite+1,\apresdix):item(\unite+1,\apresdix)}
\if{\dizaine==7 and \unite==1}{\text{dernier=-et-onze}} \text{deuxderniers=item(\dizaine,\dizaines)\dernier}}
{\text{dernier=\unite!=0?-item(\unite+1,\chiffres)}
\if{\unite==1 and \dizaine <8}{\text{dernier=-et-un}}
\if{\unite==0 and \dizaine==8}{\text{dernier=s}}
\text{deuxderniers=item(\dizaine,\dizaines)\dernier}}
}
\if{\centaine>1} {\text{groupefin=(\unite+\dizaine==0)?item(\centaine+1,\chiffres) cents:item(\centaine+1,\chiffres) cent \deuxderniers}}
{\text{groupefin=(\unite+\dizaine==0)?zéro: cent \deuxderniers}
\if{\centaine==0}{\text{groupefin=\deuxderniers}}}
\integer{nombrefin=\centaine*100+\dizaine*10+\unite}
\integer{nombre=\nombrefin}
\text{tnombre=\groupefin}
\text{enonc=\name_enonc \tnombre.}
\text{rep=\nombre}
\integer{large=20}
#endif
#if defined TARGET_oefecrit2
\integer{maxchiffres=3}
\integer{dizaine=random(0..9)}
\integer{unite=random(0..9)}
\integer{centaine=\maxchiffres>2?random(1..9):0}
\if{\dizaine==0}
{\text{deuxderniers=item(\unite+1,\chiffres)}}
{\if{\dizaine isin 1,7,9}
{\text{dernier=\dizaine!=1?-item(\unite+1,\apresdix):item(\unite+1,\apresdix)}
\if{\dizaine==7 and \unite==1}{\text{dernier=-et-onze}} \text{deuxderniers=item(\dizaine,\dizaines)\dernier}}
{\text{dernier=\unite!=0?-item(\unite+1,\chiffres)}
\if{\unite==1 and \dizaine <8}{\text{dernier=-et-un}}
\if{\unite==0 and \dizaine==8}{\text{dernier=s}}
\text{deuxderniers=item(\dizaine,\dizaines)\dernier}}
}
\if{\centaine>1} {\text{groupefin=(\unite+\dizaine==0)?item(\centaine+1,\chiffres) cents:item(\centaine+1,\chiffres) cent \deuxderniers}}
{\text{groupefin=(\unite+\dizaine==0)?zéro: cent \deuxderniers}
\if{\centaine==0}{\text{groupefin=\deuxderniers}}}
\integer{nombrefin=\centaine*100+\dizaine*10+\unite}
\integer{nombre=\nombrefin}
\text{tnombre=\groupefin}
\text{enonc=\name_enonc \nombre.}
\text{rep=\tnombre}
\integer{large=30}
#endif
#if defined TARGET_oefecrit3
\integer{maxchiffres=8}
\integer{dizaine=random(0..9)}
\integer{unite=random(0..9)}
\integer{centaine=\maxchiffres>2?random(0..9):0}
\if{\dizaine==0}
{\text{deuxderniers=item(\unite+1,\chiffres)}}
{\if{\dizaine isin 1,7,9}
{\text{dernier=\dizaine!=1?-item(\unite+1,\apresdix):item(\unite+1,\apresdix)}
\if{\dizaine==7 and \unite==1}{\text{dernier=-et-onze}} \text{deuxderniers=item(\dizaine,\dizaines)\dernier}}
{\text{dernier=\unite!=0?-item(\unite+1,\chiffres)}
\if{\unite==1 and \dizaine <8}{\text{dernier=-et-un}}
\if{\unite==0 and \dizaine==8}{\text{dernier=s}}
\text{deuxderniers=item(\dizaine,\dizaines)\dernier}}
}
\if{\centaine>1} {\text{groupefin=(\unite+\dizaine==0)?item(\centaine+1,\chiffres) cents:item(\centaine+1,\chiffres) cent \deuxderniers}}
{\text{groupefin=(\unite+\dizaine==0)?zéro: cent \deuxderniers}
\if{\centaine==0}{\text{groupefin=\deuxderniers}}}
\integer{nombrefin=\centaine*100+\dizaine*10+\unite}

\integer{unite2=\maxchiffres>3?random(0..9):0}
\integer{dizaine2=\maxchiffres>4?random(0..9):0}
\integer{centaine2=\maxchiffres>5?random(0..9):0}
\if{\dizaine2==0}
{\text{deuxderniers2=item(\unite2+1,\chiffres)}}
{\if{\dizaine2 isin 1,7,9}
{\text{dernier2=\dizaine2!=1?-item(\unite2+1,\apresdix):item(\unite2+1,\apresdix)}
\if{\dizaine2==7 and \unite2==1}{\text{dernier2=-et-onze}} \text{deuxderniers2=item(\dizaine2,\dizaines)\dernier2}}
{\text{dernier2=\unite2!=0?-item(\unite2+1,\chiffres)}
\if{\unite2==1 and \dizaine2 <8}{\text{dernier2=-et-un}}
\text{deuxderniers2=item(\dizaine2,\dizaines)\dernier2}}
}
\if{\centaine2>1} {\text{groupemille=(\unite2+\dizaine2==0)?item(\centaine2+1,\chiffres) cents mille:item(\centaine2+1,\chiffres) cent \deuxderniers2 mille}}
{\text{groupemille=(\unite2+\dizaine2==0)?zéro: cent \deuxderniers2 mille}
\if{\centaine2==0}{\text{groupemille=\deuxderniers2 mille}}}
\integer{nombremille=\centaine2*100+\dizaine2*10+\unite2}
\if{\nombremille==1}{\text{groupemille=mille}}
\if{\nombremille==0}{\text{groupemille=}}

\integer{unite3=\maxchiffres>6?random(0..9):0}
\integer{dizaine3=\maxchiffres>7?random(1..9):0}

\if{\dizaine3==0}
{\text{deuxderniers3=item(\unite3+1,\chiffres)}}
{\if{\dizaine3 isin 1,7,9}
{\text{dernier3=\dizaine3!=1?-item(\unite3+1,\apresdix):item(\unite3+1,\apresdix)}
\if{\dizaine3==7 and \unite3==1}{\text{dernier3=-et-onze}} \text{deuxderniers3=item(\dizaine3,\dizaines)\dernier3}}
{\text{dernier3=\unite3!=0?-item(\unite3+1,\chiffres)}
\if{\unite3==1 and \dizaine3 <8}{\text{dernier3=-et-un}}
\text{deuxderniers3=item(\dizaine3,\dizaines)\dernier3}}
}
\text{groupemillion=\deuxderniers3 millions}
\integer{nombremillion=\dizaine3*10+\unite3}
\if{\nombremillion==1}{\text{groupemillion=un million}}
\if{\nombremillion==0}{\text{groupemillion=}}

\integer{nombre=\nombremillion*1000000+\nombremille*1000+\nombrefin}
\text{tnombre=(\nombremillion+\nombremille+\nombrefin>0)?\groupemillion \groupemille \groupefin:zéro}
\text{enonc=\name_enonc \tnombre.}
\text{rep=\nombre}
\integer{large=20}
#endif
#if defined TARGET_oefecrit4
\integer{maxchiffres=8}
\integer{dizaine=random(0..9)}
\integer{unite=random(0..9)}
\integer{centaine=\maxchiffres>2?random(0..9):0}
\if{\dizaine==0}
{\text{deuxderniers=item(\unite+1,\chiffres)}}
{\if{\dizaine isin 1,7,9}
{\text{dernier=\dizaine!=1?-item(\unite+1,\apresdix):item(\unite+1,\apresdix)}
\if{\dizaine==7 and \unite==1}{\text{dernier=-et-onze}} \text{deuxderniers=item(\dizaine,\dizaines)\dernier}}
{\text{dernier=\unite!=0?-item(\unite+1,\chiffres)}
\if{\unite==1 and \dizaine <8}{\text{dernier=-et-un}}
\if{\unite==0 and \dizaine==8}{\text{dernier=s}}
\text{deuxderniers=item(\dizaine,\dizaines)\dernier}}
}
\if{\centaine>1} {\text{groupefin=(\unite+\dizaine==0)?item(\centaine+1,\chiffres) cents:item(\centaine+1,\chiffres) cent \deuxderniers}}
{\text{groupefin=(\unite+\dizaine==0)?zéro: cent \deuxderniers}
\if{\centaine==0}{\text{groupefin=\deuxderniers}}}
\integer{nombrefin=\centaine*100+\dizaine*10+\unite}

\integer{unite2=\maxchiffres>3?random(0..9):0}
\integer{dizaine2=\maxchiffres>4?random(0..9):0}
\integer{centaine2=\maxchiffres>5?random(0..9):0}
\if{\dizaine2==0}
{\text{deuxderniers2=item(\unite2+1,\chiffres)}}
{\if{\dizaine2 isin 1,7,9}
{\text{dernier2=\dizaine2!=1?-item(\unite2+1,\apresdix):item(\unite2+1,\apresdix)}
\if{\dizaine2==7 and \unite2==1}{\text{dernier2=-et-onze}} \text{deuxderniers2=item(\dizaine2,\dizaines)\dernier2}}
{\text{dernier2=\unite2!=0?-item(\unite2+1,\chiffres)}
\if{\unite2==1 and \dizaine2 <8}{\text{dernier2=-et-un}}
\text{deuxderniers2=item(\dizaine2,\dizaines)\dernier2}}
}
\if{\centaine2>1} {\text{groupemille=(\unite2+\dizaine2==0)?item(\centaine2+1,\chiffres) cents mille:item(\centaine2+1,\chiffres) cent \deuxderniers2 mille}}
{\text{groupemille=(\unite2+\dizaine2==0)?zéro: cent \deuxderniers2 mille}
\if{\centaine2==0}{\text{groupemille=\deuxderniers2 mille}}}
\integer{nombremille=\centaine2*100+\dizaine2*10+\unite2}
\if{\nombremille==1}{\text{groupemille=mille}}
\if{\nombremille==0}{\text{groupemille=}}

\integer{unite3=\maxchiffres>6?random(0..9):0}
\integer{dizaine3=\maxchiffres>7?random(1..9):0}

\if{\dizaine3==0}
{\text{deuxderniers3=item(\unite3+1,\chiffres)}}
{\if{\dizaine3 isin 1,7,9}
{\text{dernier3=\dizaine3!=1?-item(\unite3+1,\apresdix):item(\unite3+1,\apresdix)}
\if{\dizaine3==7 and \unite3==1}{\text{dernier3=-et-onze}} \text{deuxderniers3=item(\dizaine3,\dizaines)\dernier3}}
{\text{dernier3=\unite3!=0?-item(\unite3+1,\chiffres)}
\if{\unite3==1 and \dizaine3 <8}{\text{dernier3=-et-un}}
\text{deuxderniers3=item(\dizaine3,\dizaines)\dernier3}}
}
\text{groupemillion=\deuxderniers3 millions}
\integer{nombremillion=\dizaine3*10+\unite3}
\if{\nombremillion==1}{\text{groupemillion=un million}}
\if{\nombremillion==0}{\text{groupemillion=}}

\integer{nombre=\nombremillion*1000000+\nombremille*1000+\nombrefin}
\text{tnombre=(\nombremillion+\nombremille+\nombrefin>0)?\groupemillion \groupemille \groupefin:zéro}
\text{rep=\tnombre}
\integer{large=80}
\text{enonc=\name_enonc \nombre.}
#endif
#if defined TARGET_oefecrit5
\integer{maxchiffres=8}

\integer{b=randint(0..1)}
\if{\b=0}{\integer{dizaine=0}}{\integer{dizaine=random(0..9)}}
\integer{unite=0}
\if{\b=0}{\integer{centaine=random(0..9)}}{\integer{centaine=0}}

\if{\dizaine==0}
{\text{deuxderniers=item(\unite+1,\chiffres)}}
{\if{\dizaine isin 1,7,9}
{\text{dernier=\dizaine!=1?-item(\unite+1,\apresdix):item(\unite+1,\apresdix)}
\if{\dizaine==7 and \unite==1}{\text{dernier=-et-onze}} \text{deuxderniers=item(\dizaine,\dizaines)\dernier}}
{\text{dernier=\unite!=0?-item(\unite+1,\chiffres)}
\if{\unite==1 and \dizaine <8}{\text{dernier=-et-un}}
\if{\unite==0 and \dizaine==8}{\text{dernier=s}}
\text{deuxderniers=item(\dizaine,\dizaines)\dernier}}
}
\if{\centaine>1} {\text{groupefin=(\unite+\dizaine==0)?item(\centaine+1,\chiffres) cents:item(\centaine+1,\chiffres) cent \deuxderniers}}
{\text{groupefin=(\unite+\dizaine==0)?: cent \deuxderniers}
\if{\centaine==0}{\text{groupefin=\deuxderniers}}}
\integer{nombrefin=\centaine*100+\dizaine*10+\unite}

\integer{unite2=0}
\integer{c=randint(0..1)}
\if{\c=0}{\integer{dizaine2=0}}{\integer{dizaine2=random(0..9)}}
\if{\c=0}{\integer{centaine2=random(0..9)}}{\integer{centaine2=0}}
\if{\dizaine2==0}
{\text{deuxderniers2=item(\unite2+1,\chiffres)}}
{\if{\dizaine2 isin 1,7,9}
{\text{dernier2=\dizaine2!=1?-item(\unite2+1,\apresdix):item(\unite2+1,\apresdix)}
\if{\dizaine2==7 and \unite2==1}{\text{dernier2=-et-onze}} \text{deuxderniers2=item(\dizaine2,\dizaines)\dernier2}}
{\text{dernier2=\unite2!=0?-item(\unite2+1,\chiffres)}
\if{\unite2==1 and \dizaine2 <8}{\text{dernier2=-et-un}}
\text{deuxderniers2=item(\dizaine2,\dizaines)\dernier2}}
}
\if{\centaine2>1} {\text{groupemille=(\unite2+\dizaine2==0)?item(\centaine2+1,\chiffres) cents mille:item(\centaine2+1,\chiffres) cent \deuxderniers2 mille}}
{\text{groupemille=(\unite2+\dizaine2==0)?: cent \deuxderniers2 mille}
\if{\centaine2==0}{\text{groupemille=\deuxderniers2 mille}}}
\integer{nombremille=\centaine2*100+\dizaine2*10+\unite2}
\if{\nombremille==1}{\text{groupemille=mille}}
\if{\nombremille==0}{\text{groupemille=}}

\integer{unite3=random(0..9)}
\integer{dizaine3=random(1..9)}

\if{\dizaine3==0}
{\text{deuxderniers3=item(\unite3+1,\chiffres)}}
{\if{\dizaine3 isin 1,7,9}
{\text{dernier3=\dizaine3!=1?-item(\unite3+1,\apresdix):item(\unite3+1,\apresdix)}
\if{\dizaine3==7 and \unite3==1}{\text{dernier3=-et-onze}} \text{deuxderniers3=item(\dizaine3,\dizaines)\dernier3}}
{\text{dernier3=\unite3!=0?-item(\unite3+1,\chiffres)}
\if{\unite3==1 and \dizaine3 <8}{\text{dernier3=-et-un}}
\text{deuxderniers3=item(\dizaine3,\dizaines)\dernier3}}
}
\text{groupemillion=\deuxderniers3 millions}
\integer{nombremillion=\dizaine3*10+\unite3}
\if{\nombremillion==1}{\text{groupemillion=un million}}
\if{\nombremillion==0}{\text{groupemillion=}}

\integer{nombre=\nombremillion*1000000+\nombremille*1000+\nombrefin}
\text{tnombre=(\nombremillion+\nombremille+\nombrefin>0)?\groupemillion \groupemille \groupefin}
\text{rep=\nombre}
\integer{large=20}
\text{enonc=\name_enonc \tnombre.}
#endif
\statement{
\enonc \embed{r1,\large}
}
\answer{}{\rep}
\latex{
\begin{statement}
\enonc
\end{statement}
}
