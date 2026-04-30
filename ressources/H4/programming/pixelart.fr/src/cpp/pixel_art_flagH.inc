\title{Pixel Art et les Drapeaux H}
\text{prob=Pixel Art et les Drapeaux avec bandes horizontales}
\integer{x1=randint(1..10)}
\text{nc=24}
\text{nl=18}
\matrix{pays=de la Lituanie,Lituanien,320px-Flag_of_Lithuania.svg.png,if(1<=i && i<=6,[253,185,19],if(7<=i && i<=12,[0,106,68],if(13<=i && i<=18,[193,39,45])))
de l'Allemagne,Allemand,Flag_of_Germany.svg.png,if(1<=i && i<=6,[0,0,0],if(7<=i && i<=12,[221,0,0],if(13<=i && i<=18,[255,206,0])))
de l'Autriche,Autrichien,Flag_of_Austria.svg.png,if(1<=i && i<=6,[200,16,46],if(7<=i && i<=12,[255,255,255],if(13<=i && i<=18,[200,16,46])))
des Pays-Bas,Néerlandais,320px-Flag_of_the_Netherlands.svg.png,if(1<=i && i<=6,[174,28,40],if(7<=i && i<=12,[255,255,255],if(13<=i && i<=18,[33,70,139])))
de l'Arménie,Arménien,Flag_of_Armenia.svg.png,if(1<=i && i<=6,[217,0,18],if(7<=i && i<=12,[0,51,160],if(13<=i && i<=18,[242,168,0])))
de la Bulgarie,Bulgare,Flag_of_Bulgaria.svg.png,if(1<=i && i<=6,[255,255,255],if(7<=i && i<=12,[0,150,110],if(13<=i && i<=18,[214,38,18])))
de la Pologne,Polonais,Flag_of_Poland.svg.png,if(1<=i && i<=9,[255,255,255],if(10<=i && i<=118,[220,20,60]))
de la Russie,Russe,Flag_of_Russia.svg.png,if(1<=i && i<=6,[255,255,255],if(7<=i && i<=12,[0,57,166],if(13<=i && i<=18,[213,43,30])))
de l'Ukraine,Ukrainien,Flag_of_Ukraine.svg.png,if(1<=i && i<=9,[0,91,187],if(10<=i && i<=118,[255,213,0]))
de l'Hongrie,Hongrois,Flag_of_Hungary.svg.png,if(1<=i && i<=6,[206,41,57],if(7<=i && i<=12,[255,255,255],if(13<=i && i<=18,[71,112,80])))
}
\text{DD=pari(m=matrix(\nl,\nc,i,j,\pays[\x1;4]);)}
