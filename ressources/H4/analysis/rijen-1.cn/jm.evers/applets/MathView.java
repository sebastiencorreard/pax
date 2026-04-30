/*                                                                                                                                          
*  This program is free software; you can redistribute it and/or modify                                       
*  it under the terms of the GNU General Public License as published by                                       
*  the Free Software Foundation; either version 2 of the License, or                                          
*  (at your option) any later version.                                                                        
*                                                                                                             
*  This program is distributed in the hope that it will be useful,                                            
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                                             
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                                              
*  GNU General Public License for more details.                                                               
*                                                                                                             
*  You should have received a copy of the GNU General Public License                                          
*  along with this program; if not, write to the Free Software                                                
*  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                                                  
*/     

/*
 This is a slight modification of a JomeInput.java program
 jm.evers 5/2007
*/

import fr.ove.openmath.jome.Jome;
import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;
import java.io.PrintStream;


public class MathView extends Applet
    implements ActionListener, ItemListener, TextListener, WindowListener
{

    public void setWindow(Frame frame)
    {
        standaloneWindow = frame;
        inAnApplet = false;
    }

    public void toggleFont()
    {
        Jome jome = j;
        if(jome.getFont() == bigFont)
        {
            jome.setFont(defaultFont);
            linearInput.setFont(defaultFont);
        } else
        {
            jome.setFont(bigFont);
            linearInput.setFont(bigFont);
        }
        invalidate();
        jome.invalidate();
        linearInput.invalidate();
        linearInput.requestFocus();
        repaint();
        jome.repaint();
        linearInput.repaint();
    }

    public static void main(String args[])
    {
        MathView mathview = new MathView();
        Frame frame = new Frame();
        mathview.setWindow(frame);
        frame.add(mathview);
        frame.setTitle("MathEdit");
        frame.addWindowListener(mathview);
        mathview.init();
        frame.pack();
        frame.setSize(640,480);
        frame.setVisible(true);
        frame.validate();
        mathview.start();
        mathview.repaint();

    }

    private void reportError(String s)
    {
        if(!inAnApplet)
            System.err.println(s);
    }

    private void addPaletteCard(Choice choice, Container container, String s, Container container1)
    {
        choice.add(s);
        container.add(container1, s);
    }

    private Button addButton(Container container, String s, String s1)
    {
        Button button = new Button(s);
        button.setActionCommand(s1);
        button.addActionListener(this);
        container.add(button);
        return button;
    }

    private Button addButton(Container container, String s, String s1, String s2)
    {
        Button button = new Button(s);
        button.setActionCommand(s1);
        button.addActionListener(this);
        container.add(button, s2);
        return button;
    }

    public void start()
    {
        linearInput.setFont(defaultFont);
        linearInput.invalidate();
        j.invalidate();
        repaint();
        linearInput.requestFocus();
    }
    
    
    public void init()
    {
    
	String parmstr;
	String helptext;
	int font1;
	int font2;
        parmstr=getParameter("smallfont");if(parmstr==null){font1=16;}else{font1 = Integer.parseInt(parmstr);}
	parmstr=getParameter("largefont");if(parmstr==null){font2=24;}else{font2 = Integer.parseInt(parmstr);}
        bigFont = new Font("Helvetica", 0, font2);
        defaultFont = new Font("Helvetica", 0, font1);
	parmstr=getParameter("helptext");if(parmstr==null){helptext="";}else{
	if(parmstr.length() > 40){helptext=" max. 30 chars help param";}else{helptext = parmstr;}}

	Color bgcolor;
        parmstr=getParameter("bgcolor");
	if(parmstr!=null){bgcolor=Color.decode(parmstr);}else { bgcolor=Color.white; }
        setBackground(bgcolor);
        j = new Jome();
        j.setFont(defaultFont);
        j.setDrawBounds(true);
        //j.setBackground(new Color(0xffffdd));
        j.setBackground(bgcolor);	
        BorderLayout borderlayout = new BorderLayout();
        setLayout(new BorderLayout());
	
	

        controlPane = new Panel();
	controlPane.setFont(defaultFont);
        controlPane.setLayout(new BorderLayout());
        palette = new Panel();
        palette.setLayout(new BorderLayout());
	palette.setFont(defaultFont);
        paletteCards = new Panel();
        paletteCardsLayout = new CardLayout(5, 4);
        paletteCards.setLayout(paletteCardsLayout);
        paletteChoice = new Choice();
        paletteChoice.addItemListener(this);

	// param name="my_panel" value="title : function1 : function1 : function1 : function1 "
	String special=getParameter("my_panel");
	if(special!=null){
	// maximum inputs
	    int maxfun=6;
	    String[] results = special.split(":");
	    Panel panel08 = new Panel();
	    panel08.setLayout(new GridLayout());
	    int p;
	    int pos=results.length;
	    if(pos>maxfun+1){pos=maxfun;helptext="maximum functions:"+maxfun ;}
	    String P;
	    String titel=results[0];
	    int r;
	    for (p=1;p<pos;p++){
		P=results[p];
		r=P.compareToIgnoreCase("and");
		if(r==0){P="\u22c0";}
		r=P.compareToIgnoreCase("or");
		if(r==0){P="\u22c1";}
		r=P.compareToIgnoreCase("isin");
		if(r==0){P="\u2208";}
		r=P.compareToIgnoreCase("notin");
		if(r==0){P="\u2209";}
		r=P.compareToIgnoreCase("->");
		if(r==0){P="\u21d4";}
		r=P.compareToIgnoreCase("sqrt()");
		if(r==0){P="\u221a()";}
		// more?
		addButton(panel08, P,"append "+P);
	    }
	    addPaletteCard(paletteChoice, paletteCards , titel , panel08);
	    palette.add(paletteChoice, "North");
	    palette.add(paletteCards, "Center");
	    controlPane.add(palette, "Center");
	    j.setVisible(true);
	    add(j, "Center");
	}

	Panel panel02 = new Panel();
        panel02.setLayout(new GridLayout());
        addButton(panel02, "x", "insert *");
        addButton(panel02, "+", "insert + ");
        addButton(panel02, "-", "insert -");
        addButton(panel02, "/", "insert /()");
        addButton(panel02, "^", "insert ^");
        addPaletteCard(paletteChoice, paletteCards ,"Operators" , panel02);
        palette.add(paletteChoice, "North");
        palette.add(paletteCards, "Center");
        controlPane.add(palette, "Center");
        j.setVisible(true);
        add(j, "Center");

	Panel panel03 = new Panel();
        panel03.setLayout(new GridLayout());
        addButton(panel03, "\u22c0", "insert \u22c0 ");
        addButton(panel03, "\u22c1", "insert \u22c1 ");
        addButton(panel03, "\u221A", "insert \u221A()");
	addButton(panel03, "\u221B", "insert \u221B()");
        addButton(panel03, "\u221C", "insert \u221C()");
        addButton(panel03, "\u03C0", "insert pi");
        addPaletteCard(paletteChoice, paletteCards, "Analysis", panel03);
        palette.add(paletteChoice, "North");
        palette.add(paletteCards, "Center");
        controlPane.add(palette, "Center");
        j.setVisible(true);
        add(j, "Center");
	


        Panel panel06 = new Panel();
        panel06.setLayout(new GridLayout());
	/*isin*/
        addButton(panel06, "\u2208", "insert \u2208");
	/* notin*/
        addButton(panel06, "\u2209", "insert \u2209");
	/* rightarrow*/	
        addButton(panel06, "\u2192", "insert \u2192");	
	/* leftrightarrow*/	
        addButton(panel06, "\u21D4", "insert \u21D4");
	/* inf */
        addButton(panel06, "\u221E", "insert \u221E");
        addPaletteCard(paletteChoice, paletteCards, "Misc. symbols", panel06);
        palette.add(paletteChoice, "North");
        palette.add(paletteCards, "Center");
        controlPane.add(palette, "Center");
        j.setVisible(true);
        add(j, "Center");

        Panel panel07 = new Panel();
        panel07.setLayout(new GridLayout());
        addButton(panel07, "log", "append log()");
        addButton(panel07, "ln", "append ln()");
        addButton(panel07, "|x|", "append |x|");
        addButton(panel07, "f \u00AF\u00B9(x)=", "append f \u00AF\u00B9(x)=");
        addPaletteCard(paletteChoice, paletteCards, "Misc Functions", panel07);
        palette.add(paletteChoice, "North");
        palette.add(paletteCards, "Center");
        controlPane.add(palette, "Center");
        j.setVisible(true);
        add(j, "Center");

        Panel panel01 = new Panel();
        panel01.setLayout(new GridLayout());
        addButton(panel01, "sin()", "append sin()");
        addButton(panel01, "sin\u00B2()", "append sin()^2");
        addButton(panel01, "cos()", "append cos()");
        addButton(panel01, "cos\u00B2()", "append cos()^2");
        addButton(panel01, "tan()", "append tan()");
        addButton(panel01, "tan\u00B2()", "append tan()^2");
        addPaletteCard(paletteChoice, paletteCards, "Trigonometry", panel01);
        palette.add(paletteChoice, "North");
        palette.add(paletteCards, "Center");
        controlPane.add(palette, "Center");
        j.setVisible(true);
        add(j, "Center");


        Panel panel04 = new Panel();
        panel04.setLayout(new GridLayout());
        addButton(panel04, "x \u2208 N \u2216 \u007B a \u003B b \u007D", "append \u2208 N \u2216 \u007B\u007D");
        addButton(panel04, "x \u2208 Z \u2216 \u007B a \u003B b \u007D", "append \u2208 Z \u2216 \u007B\u007D");
        addButton(panel04, "x \u2208 C \u2216 \u007B a \u003B b \u007D", "append \u2208 C \u2216 \u007B\u007D");
        addButton(panel04, "x \u2208 R \u2216 \u007B a \u003B b \u007D", "append \u2208 R \u2216 \u007B\u007D");
        addPaletteCard(paletteChoice, paletteCards, "Domains", panel04);
        palette.add(paletteChoice, "North");
        palette.add(paletteCards, "Center");
        controlPane.add(palette, "Center");
        j.setVisible(true);
        add(j, "Center");


        
	Panel panel2 = new Panel();
        panel2.setLayout(new BorderLayout());
	
	Panel panel4 = new Panel();
        infoArea = new TextArea(helptext,1,30,TextArea.SCROLLBARS_NONE);
	infoArea.setEditable(false);
        infoArea.setFont(defaultFont);
	infoArea.setBackground(Color.white);
        panel4.add(infoArea, "Center");
        panel2.add(panel4, "South");
        reportError("OK");
        Panel panel3 = new Panel();
        panel2.add(panel3, "West");
	undoButton = addButton(panel3, "\u21A9", "undo");
        redoButton = null;
        addButton(panel3, "\261", "toggle_font", "Center");
        controlPane.add(panel2, "South");
        linearInput = new TextArea("",2,1,TextArea.SCROLLBARS_NONE);
        linearInput.addTextListener(this);
        linearInput.setFont(bigFont);
	linearInput.setBackground(Color.white);
        controlPane.add(linearInput, "North");
        add(controlPane, "South");
        setVisible(true);
        setLinear("");
        linearInput.requestFocus();

    }

    private void setLinear(String s)
    {
        markUndo();
        linearInput.setText(s);
        updateJomeView();
    }

    private void markUndo()
    {
        if(redoButton != null)
        {
            undoBuffer[undoBufferCursor] = linearInput.getText();
            undoBufferCursor++;
            if(undoBufferCursor >= undoBuffer.length)
                undoBufferCursor = 0;
            if(undoBufferValidSize < undoBuffer.length)
            {
                undoBufferValidSize++;
                undoBufferValidSizeMax = undoBufferValidSize;
            }
            updateUndoRedoButtons();
        } else
        {
            previousLinear = linearInput.getText();
        }
    }

    private void redo()
    {
        if(undoBufferValidSize < undoBufferValidSizeMax)
        {
            undoBufferCursor++;
            undoBufferValidSize++;
            if(undoBufferCursor >= undoBuffer.length)
                undoBufferCursor = 0;
            linearInput.setText(undoBuffer[undoBufferCursor]);
        }
        updateUndoRedoButtons();
        updateJomeView();
    }

    private void undo()
    {
        if(redoButton != null)
        {
            if(undoBufferValidSize > 0)
            {
                undoBufferValidSize--;
                undoBufferCursor--;
                if(undoBufferCursor < 0)
                    undoBufferCursor = undoBuffer.length - 1;
                if(undoBuffer[undoBufferCursor] != null)
                    linearInput.setText(undoBuffer[undoBufferCursor]);
            }
            updateUndoRedoButtons();
        } else
        if(previousLinear != null)
        {
            String s = linearInput.getText();
            linearInput.setText(previousLinear);
            previousLinear = s;
        }
        updateJomeView();
    }

    private void updateUndoRedoButtons()
    {
        undoButton.setEnabled(undoBufferValidSize > 0);
        redoButton.setEnabled(undoBufferValidSize < undoBufferValidSizeMax);
    }

    private void updateJomeView()
    {
	// StringBuffer(String str)
	// String buffers are used by the compiler to implement the binary string
	// concatenation operator +. For example, the code:
	// x = "a" + 4 + "c" is compiled to the equivalent of:
	// x = new StringBuffer().append("a").append(4).append("c").toString() 	
	// example, if z refers to a string buffer object whose current contents are "start",
	// then the method call z.append("le") would cause the string buffer to contain "startle",
	// whereas z.insert(4, "le") would alter the string buffer to contain "starlet".
	// The principal operations on a StringBuffer are the append and insert methods, 
	String vars;
	vars=getParameter("wimsvars");
	if(vars!=null && vars.length()>0){
	vars=vars.toString();}
	else
	{vars="xyzcstl|";}
	int t=vars.length();
	String s;
	s=linearInput.getText().toString();
	StringBuffer S=new StringBuffer(s);
	int max=S.length();
	int limit=100;
	int p;
	int r;
	int m;
	char x;
	char getal;
	char P1;
	char P2;
	
	String nummers="0123456789"+vars;
	// xx -> x*x
	// 4x -> 4*x
	nummers=nummers.toString();
	int q=nummers.length();
	for(r=0;r<t;r++){
	    x=vars.charAt(r);
	    for(p=0;p<q;p++){
		getal=nummers.charAt(p);
		for(m=0;m<max-1 && max<limit;m++){
		    P1=S.charAt(m);
		    P2=S.charAt(m+1);
		    if((P1==getal) && (P2==x)){S=S.insert(m+1,"*");max=S.length();}
		}
	    }
	}
	
	s=S.toString();
        j.setLinear(s);
    }

    public MathView()
    {

        standaloneWindow = null;
        inAnApplet = true;
        previousLinear = null;
        undoBuffer = new String[50];
        undoBufferCursor = 0;
        undoBufferValidSize = 0;
        undoBufferValidSizeMax = 0;
        bigFont = new Font("Helvetica", 0, 32);
        defaultFont = new Font("Helvetica", 0, 18);
    }

    public void actionPerformed(ActionEvent actionevent)
    {
        String s = actionevent.getActionCommand();
        if(s.startsWith("append "))
        {
            markUndo();
            linearInput.setText(linearInput.getText() + s.substring("append ".length()));
        } else

        if(s.startsWith("insert "))
        {
            markUndo();
            String s1 = linearInput.getText();
            int i = linearInput.getCaretPosition();
            linearInput.setText(s1.substring(0, i) + s.substring("insert ".length()) + s1.substring(i));
        } else
        if(s.startsWith("enclose "))
        {
            markUndo();
            String s2 = linearInput.getText();
            String s3 = s.substring("append ".length(), s.length() - 1);
            String s4 = s.substring(s.length() - 1);
            int k = linearInput.getSelectionStart();
            int l = linearInput.getSelectionEnd();
            linearInput.setText(s2.substring(0, k) + s3 + linearInput.getSelectedText() + s4 + s2.substring(l));
        } else
        if(s.equals("undo"))
            undo();
        else
        if(s.equals("redo"))
            redo();
        else
        if(s.equals("toggle_font"))
        {
            toggleFont();
        } else
        {
            System.out.println("input: " + s);
            updateJomeView();
        }
    }

    public void itemStateChanged(ItemEvent itemevent)
    {

        paletteCardsLayout.show(paletteCards, (String)itemevent.getItem());
        linearInput.requestFocus();
    }

    public void textValueChanged(TextEvent textevent)
    {
        updateJomeView();
    }

    public void windowOpened(WindowEvent windowevent)
    {
    }

    public void windowIconified(WindowEvent windowevent)
    {
    }

    public void windowDeiconified(WindowEvent windowevent)
    {
    }

    public void windowActivated(WindowEvent windowevent)
    {
    }

    public void windowDeactivated(WindowEvent windowevent)
    {
    }

    public void windowResized(WindowEvent windowevent)
    {
    }

    public void windowClosing(WindowEvent windowevent)
    {
        stop();
	destroy();
        if(!inAnApplet)
        {
            standaloneWindow.setVisible(false);
            standaloneWindow.dispose();
        }
    }


    public void windowClosed(WindowEvent windowevent)
    {
	//System.out.println("System exit");
        System.exit(0);
    }

    public String getLinear()
    {

        return j.getLinear();
    }

    Jome j;
    Frame standaloneWindow;
    //
    TextArea infoArea;
    //
    Panel controlPane;
    Panel palette;
    Panel paletteCards;
    CardLayout paletteCardsLayout;
    Choice paletteChoice;
    TextArea linearInput;
    Button undoButton;
    Button redoButton;
    boolean inAnApplet;
    String previousLinear;
    String undoBuffer[];
    int undoBufferCursor;
    int undoBufferValidSize;
    int undoBufferValidSizeMax;
    Font bigFont;
    Font defaultFont;
}
