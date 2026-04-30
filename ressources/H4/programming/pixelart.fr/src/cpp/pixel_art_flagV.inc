\text{prob=Pixel Art et les Drapeaux avec bandes verticales}
\title{Pixel Art et les Drapeaux V}
\integer{x1=randint(1..7)}
\text{nc=24}
\text{nl=18}
\matrix{pays=de la France,Français,Flag_of_France.svg.png,if(1<=j && j<=8,[0,38,84],if(9<=j && j<=16,[255,255,255],if(17<=j && j<=24,[206,17,38])))
de l'Italie,Italien,Flag_of_Italy.svg.webp,if(1<=j && j<=8,[0,146,70],if(9<=j && j<=16,[255,255,255],if(17<=j && j<=24,[206,43,55])))
de l'Irlande,Irlandais,320px-Flag_of_Ireland.svg.png,if(1<=j && j<=8,[22,155,98],if(9<=j && j<=16,[255,255,255],if(17<=j && j<=24,[255,136,62])))
du Mali,Malien,320px-Flag_of_Mali.svg.png,if(1<=j && j<=8,[20,181,58],if(9<=j && j<=16,[252,209,22],if(17<=j && j<=24,[206,17,38])))
du Tchad,Tchadien,320px-Flag_of_Chad.svg.png,if(1<=j && j<=8,[0,38,100],if(9<=j && j<=16,[254,203,0],if(17<=j && j<=24,[198,12,48])))
de la Côte d'Ivoire,Ivoirien,Flag_of_Cote_Ivoire.svg.png,if(1<=j && j<=8,[247,127,0],if(9<=j && j<=16,[255,255,255],if(17<=j && j<=24,[0,158,96])))
de la Belgique,Belge,Flag_of_Belgium.svg.png,if(1<=j && j<=8,[0,0,0],if(9<=j && j<=16,[253,218,37],if(17<=j && j<=24,[239,51,64])))
}
\text{DD=pari(m=matrix(\nl,\nc,i,j,\pays[\x1;4]);)}
