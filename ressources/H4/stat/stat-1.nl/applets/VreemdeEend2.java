// horrible amateur scriblings...no copyrights

import java.applet.*;
import java.awt.*;
import java.util.*;
import java.awt.event.*;
import java.lang.Math;
import java.net.*;

//    <param name="max" value="20">                                                                                                  
//    <param name="renew" value="yes">                                                                                               
//    <param name="language" value="nl">                                                                                             
//    <param name="show_result" value="no">

public class VreemdeEend2 extends Applet implements Runnable{
    Graphics2D g;
    Image backbuffer;
    Graphics2D backg;
    Font font;
    private static final long serialVersionUID = 1L;
    Thread thread = null;Graphics canvas;String replystring="";
    public int sy=22;public int xsize=800;public int ysize=7*sy;
    int dx;int dy;long start;int foutcounter=1;
    double diff;String duration="" ;
    int counter=0;int goedeantwoord;
    long stop;public long totaltime=0;
    public Image ok;public Image nok;
    String[][] Antwoorden;int v1;int v2;int v3;int v4;
    String[] Vragen;int records=0;int goedzo=1;int klaar=0;
    int volgorde[]={1,2,3,4};long begin;int pressed=1;
    int vraagnummers[];
    int fnsize= 12;
    Color blauw=new Color(0,0,255);
    Color zwart=new Color(0,0,0);
    Color kleur;int max=10;
    int m1=0;int m2=0;
    String s_time = "time";
    String s_attempts = "freq";
    String s_qcm = "Multiplechoice";
    String s_question = "question";
    
    public void init(){
	font= new Font("TimesRoman",Font.BOLD,fnsize); 
	backbuffer = createImage(xsize,ysize+50); // 50 is voor ok/nok plaatje                            
        backg = (Graphics2D) backbuffer.getGraphics();  
        begin=System.currentTimeMillis();klaar=0;
	ok=getImage(getCodeBase(), "ok.gif");nok=getImage(getCodeBase(), "nok.gif");
	String questions=getParameter("questions");if(questions==null){System.out.println("CAN NOT READ QUESTION PARAM");}
	String ss=getParameter("max");if(ss!=null && ss.length()>0){max = Integer.parseInt(ss, 10);}
	ss = getParameter("lang");if(ss!=null && ss.length()>0){
	    if(ss.equalsIgnoreCase("nl")){ s_time="tijd";s_attempts="freq";s_qcm="Meerkeuzevragen";s_question="Vraag";}
	    else
	    if(ss.equalsIgnoreCase("fr")){ s_time="temps";s_attempts="freq";s_qcm="QCM";s_question="Question";}
	}
	StringTokenizer vragen = new StringTokenizer(questions, ":");
	String vraag="";String antwoord="";int w=0;
	Antwoorden=new String[max][4*max];
	vraagnummers=new int[max+1];
	Vragen=new String[max+1];
	int tmp=0;
	for(int s=0;s<max-1;s++){
	    vraag=vragen.nextToken();
	    StringTokenizer antwoorden = new StringTokenizer(vraag, ";");
	    w=antwoorden.countTokens();
	    vraagnummers[s]=s;
	    for(int r=0;r<w;r++){
		antwoord=antwoorden.nextToken();
		tmp=fnsize*antwoord.length();if(tmp>xsize){xsize=tmp;}
		if(r==0){
		    Vragen[s]=antwoord;
		    //System.out.println("de vraag = "+antwoord);
		}
		else
		{
		    Antwoorden[s][r-1]=antwoord;
		    //System.out.println("antwoord  ="+antwoord);
		}
	    }
	}
	vraagnummers=Shuffle(vraagnummers);
	
	addMouseMotionListener(new MouseMotionAdapter(){
	    public void mouseMoved(MouseEvent e){
		if(klaar == 0){
		    dy = e.getY();
		    kleur=zwart;
		    for(int i=2;i<6;i++){
			m1=i*sy;m2=(i+1)*sy;
		        if(dy>m1 && dy<m2){
				pressed=0;
			    kleur=blauw;
			    i=10;
			    prepaint();
			}
		    }
		}
	    }
	});
	
	
	addMouseListener(
	    new MouseAdapter(){
		public void mousePressed(MouseEvent e){
		    dx = e.getX();
		    dy = e.getY();
		    if(klaar==0){
			kleur=zwart;
			for(int p=2;p<7;p++){
			    if(dx>0 && dx<xsize){
				if(dy>(p)*sy+5 && dy<(p+1)*sy+5){
				    if(goedeantwoord == p){
					stop=System.currentTimeMillis();
					diff=(double)(stop-start)/1000;
					duration=duration+","+diff;
					replystring=replystring+"\n"+diff+":"+foutcounter;
					foutcounter=1;
					counter++;goedzo=1;
					if(counter == max){klaar=1;ready();}
					start=System.currentTimeMillis();
					pressed=1;
				    }
				    else
				    {
					goedzo=0;foutcounter++;
					pressed=0;
				    }
				    prepaint();
				}
			    }
			}
		    }
		    else
		    {
			ready();
		    }
		}
	    }
	);
	prepaint();

    }

    public static int[] Shuffle(int[] S){
	    int ll= S.length;
	    for (int i=0;i<ll;i++){
		int r = (int) (Math.random() * (i+1));
		int swap = S[r];
		S[r] = S[i];
		S[i] = swap;
	    }
        return S;
    }
    
    public void ready(){
	backg.setFont(font);
	backg.setColor(Color.black);backg.fillRect(0,0,xsize,ysize+50);
	StringTokenizer q = new StringTokenizer(replystring, "\n");
	int m=q.countTokens(); 
	String sub="";int X=10;int Y=20; 
	backg.setColor(Color.white);
	backg.drawString(s_time+"\t : \t"+s_attempts,X,Y);
	for(int s=0;s<m;s++){
	    Y=Y+fnsize;sub=q.nextToken(); backg.drawString(sub,X,Y);
	    if(Y>(ysize)){ X=X+120; Y=20;backg.drawString(s_time+"\t : \t"+s_attempts,X,Y);}
	}
	repaint();
    }
    
    public void prepaint(){
	if(counter==0){start = System.currentTimeMillis();}
	int num=vraagnummers[counter];
	backg.setColor(Color.black);backg.fillRect(0,0,xsize,ysize);
	backg.setColor(kleur);backg.fillRect(0,m1+5,xsize,m2+5);
	backg.setColor(Color.black);backg.fillRect(0,m2+5,xsize,6*sy);
	backg.setFont(font);backg.setColor(Color.yellow);
	backg.drawString(s_qcm+ "   "+ s_question+" "+(counter+1)+") ",10,sy);
	backg.drawString(Vragen[num],10,2*sy);
	backg.setColor(Color.white);
	if(pressed!=0){volgorde=Shuffle(volgorde);}
	int k;
	for(int p=0;p<4;p++){
	    k=volgorde[p];
	    if(k==4){goedeantwoord=p+2;}
	    backg.setColor(Color.red);backg.drawLine(0,(p+3)*(sy)+5,xsize,(p+3)*(sy)+5);
	    backg.setColor(Color.white);backg.drawString((p+1)+") "+Antwoorden[num][k-1],10,(p+3)*(sy));
	}
	backg.clearRect(0,6*sy+5,xsize,ysize);
	backg.setColor(Color.black);backg.fillRect(0,6*sy+5,xsize,ysize);
	if(goedzo==0){backg.drawImage(nok,50,ysize, this);}
	else{backg.drawImage(ok,50,ysize, this);}
	repaint();
    }
 
    public void start(){
	if(thread == null){
	    thread = new Thread(this);
    	    thread.start();
	}
    }

 
    public void stop(){
	thread =null;
    }

    public void run(){
	while(thread != null){
	try{
	    Thread.sleep(100);
	}
	catch (InterruptedException e){
	}
    }
}

    
    public void update( Graphics g ) {                                                                                                     
        g.drawImage( backbuffer, 0, 0, this );                                                                                             
        getToolkit().sync();                                                                                                               
    }                                                                                                                                      
                                                                                                                                           
    public void paint( Graphics g ) {                                                                                                      
      update( g );
      if(counter == 1){start = System.currentTimeMillis();}
    }  
    
 
public String ReadApplet(){
    if(counter<max){
	return "error: not finished";
    }
    else
    {
	double totaltime=(double) (stop-begin)/1000;
	return totaltime+":"+(max-1)+"\n"+replystring;
    }
}
 
 
}










































