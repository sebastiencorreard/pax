\title{Pixel Art et les Drapeaux C}
\text{prob=Pixel Art et les Drapeaux avec une croix}
\integer{x1=randint(1..4)}
\matrix{pays=de la Finlande,Finlandais,Flag_of_Finland.svg.png,if((8<=j && j<=11)||(6<=i && i<=9),[0,53,128],[255,255,255]),26,14
du Danemark,Danois,Flag_of_Denmark.svg.png,if((8<=j && j<=11)||(8<=i && i<=11),[255,255,255],[200,16,46]),26
de la Suède,Suèduois,320px-Flag_of_Sweden.svg.png,if((8<=j && j<=11)||(6<=i && i<=9),[254,204,0],[0,106,167]),26,14
dela Suisse,Suisse,Flag_of_Switzerland.svg.png,if((8<=j && j<=11 && 3<=i && i<=16)||(8<=i && i<=11 && 3<=j && j<=16),[255,255,255],[218,41,28]),18,18
}

\text{nc=(\pays[\x1;5]==)?24:\pays[\x1;5]}
\text{nl=(\pays[\x1;6]==)?18:\pays[\x1;6]}

\text{DD=pari(m=matrix(\nl,\nc,i,j,\pays[\x1;4]);)}
