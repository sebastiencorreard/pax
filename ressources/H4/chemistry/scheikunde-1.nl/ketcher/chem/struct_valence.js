/****************************************************************************
 * Copyright (C) 2009-2010 GGA Software Services LLC
 *
 * This file may be distributed and/or modified under the terms of the
 * GNU Affero General Public License version 3 as published by the Free
 * Software Foundation and appearing in the file LICENSE.GPL included in
 * the packaging of this file.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/

if (!window.chem || !chem.Struct)
	throw new Error("Include MolData.js first");

chem.Struct.prototype.calcConn = function (aid)
{
	var conn = 0;
	var atom = this.atoms.get(aid);
	var hasAromatic = false;
	for (var i = 0; i < atom.neighbors.length; ++i) {
		var hb = this.halfBonds.get(atom.neighbors[i]);
		var bond = this.bonds.get(hb.bid);
		switch (bond.type) {
			case chem.Struct.BOND.TYPE.SINGLE:
				conn += 1;
				break;
			case chem.Struct.BOND.TYPE.DOUBLE:
				conn += 2;
				break;
			case chem.Struct.BOND.TYPE.TRIPLE:
				conn += 3;
				break;
			case chem.Struct.BOND.TYPE.AROMATIC:
				conn += 1;
				hasAromatic = true;
				break;
			default:
				return -1;
		}
	}
	if (hasAromatic)
		conn += 1;
	return conn;
};

chem.Struct.Atom.prototype.calcValence = function (conn)
{
	var atom = this;
	var charge = atom.charge;
	var label = atom.label;
	if (atom.isQuery()) {
		this.implicitH = 0;
		return true;
	}
	var elem = chem.Element.getElementByLabel(label);
	if (elem == null) {
		this.implicitH = 0;
		return true;
	}

	var groupno = chem.Element.elements.get(elem).group;
	var rad = chem.Struct.radicalElectrons(atom.radical);

	var valence = conn;
	var hyd = 0;
	var absCharge = Math.abs(charge);

	if (groupno == 1)
	{
		if (label == 'H' ||
			label == 'Li' || label == 'Na' || label == 'K' ||
			label == 'Rb' || label == 'Cs' || label == 'Fr')
			{
			valence = 1;
			hyd = 1 - rad - conn - absCharge;
		}
	}
	else if (groupno == 3)
	{
		if (label == 'B' || label == 'Al' || label == 'Ga' || label == 'In')
		{
			if (charge == -1)
			{
				valence = 4;
				hyd = 4 - rad - conn;
			}
			else
			{
				valence = 3;
				hyd = 3 - rad - conn - absCharge;
			}
		}
		else if (label == 'Tl')
		{
			if (charge == -1)
			{
				if (rad + conn <= 2)
				{
					valence = 2;
					hyd = 2 - rad - conn;
				}
				else
				{
					valence = 4;
					hyd = 4 - rad - conn;
				}
			}
			else if (charge == -2)
			{
				if (rad + conn <= 3)
				{
					valence = 3;
					hyd = 3 - rad - conn;
				}
				else
				{
					valence = 5;
					hyd = 5 - rad - conn;
				}
			}
			else
			{
				if (rad + conn + absCharge <= 1)
				{
					valence = 1;
					hyd = 1 - rad - conn - absCharge;
				}
				else
				{
					valence = 3;
					hyd = 3 - rad - conn - absCharge;
				}
			}
		}
	}
	else if (groupno == 4)
	{
		if (label == 'C' || label == 'Si' || label == 'Ge')
		{
			valence = 4;
			hyd = 4 - rad - conn - absCharge;
		}
		else if (label == 'Sn' || label == 'Pb')
		{
			if (conn + rad + absCharge <= 2)
			{
				valence = 2;
				hyd = 2 - rad - conn - absCharge;
			}
			else
			{
				valence = 4;
				hyd = 4 - rad - conn - absCharge;
			}
		}
	}
	else if (groupno == 5)
	{
		if (label == 'N' || label == 'P')
		{
			if (charge == 1)
			{
				valence = 4;
				hyd = 4 - rad - conn;
			}
			else if (charge == 2)
			{
				valence = 3;
				hyd = 3 - rad - conn;
			}
			else
			{
				if (label == 'N' || rad + conn + absCharge <= 3)
				{
					valence = 3;
					hyd = 3 - rad - conn - absCharge;
				}
				else // ELEM_P && rad + conn + absCharge > 3
				{
					valence = 5;
					hyd = 5 - rad - conn - absCharge;
				}
			}
		}
		else if (label == 'Bi' || label == 'Sb' || label == 'As')
		{
			if (charge == 1)
			{
				if (rad + conn <= 2 && label != 'As')
				{
					valence = 2;
					hyd = 2 - rad - conn;
				}
				else
				{
					valence = 4;
					hyd = 4 - rad - conn;
				}
			}
			else if (charge == 2)
			{
				valence = 3;
				hyd = 3 - rad - conn;
			}
			else
			{
				if (rad + conn <= 3)
				{
					valence = 3;
					hyd = 3 - rad - conn - absCharge;
				}
				else
				{
					valence = 5;
					hyd = 5 - rad - conn - absCharge;
				}
			}
		}
	}
	else if (groupno == 6)
	{
		if (label == 'O')
		{
			if (charge >= 1)
			{
				valence = 3;
				hyd = 3 - rad - conn;
			}
			else
			{
				valence = 2;
				hyd = 2 - rad - conn - absCharge;
			}
		}
		else if (label == 'S' || label == 'Se' || label == 'Po')
		{
			if (charge == 1)
			{
				if (conn <= 3)
				{
					valence = 3;
					hyd = 3 - rad - conn;
				}
				else
				{
					valence = 5;
					hyd = 5 - rad - conn;
				}
			}
			else
			{
				if (conn + rad + absCharge <= 2)
				{
					valence = 2;
					hyd = 2 - rad - conn - absCharge;
				}
				else if (conn + rad + absCharge <= 4)
				// See examples in PubChem
				// [S] : CID 16684216
				// [Se]: CID 5242252
				// [Po]: no example, just following ISIS/Draw logic here
				{
					valence = 4;
					hyd = 4 - rad - conn - absCharge;
				}
				else
				// See examples in PubChem
				// [S] : CID 46937044
				// [Se]: CID 59786
				// [Po]: no example, just following ISIS/Draw logic here
				{
					valence = 6;
					hyd = 6 - rad - conn - absCharge;
				}
			}
		}
		else if (label == 'Te')
		{
			if (charge == -1)
			{
				if (conn <= 2)
				{
					valence = 2;
					hyd = 2 - rad - conn - absCharge;
				}
			}
			else if (charge == 0 || charge == 2)
			{
				if (conn <= 2)
				{
					valence = 2;
					hyd = 2 - rad - conn - absCharge;
				}
				else if (conn <= 4)
				{
					valence = 4;
					hyd = 4 - rad - conn - absCharge;
				}
				else if (charge == 0 && conn <= 6)
				{
					valence = 6;
					hyd = 6 - rad - conn - absCharge;
				}
				else
					hyd = -1;
			}
		}
	}
	else if (groupno == 7)
	{
		if (label == 'F')
		{
			valence = 1;
			hyd = 1 - rad - conn - absCharge;
		}
		else if (label == 'Cl' || label == 'Br' ||
			label == 'I'  || label == 'At')
			{
			if (charge == 1)
			{
				if (conn <= 2)
				{
					valence = 2;
					hyd = 2 - rad - conn;
				}
				else if (conn == 3 || conn == 5 || conn >= 7)
					hyd = -1;
			}
			else if (charge == 0)
			{
				if (conn <= 1)
				{
					valence = 1;
					hyd = 1 - rad - conn;
				}
				// While the halogens can have valence 3, they can not have
				// hydrogens in that case.
				else if (conn == 2 || conn == 4 || conn == 6)
				{
					if (rad == 1)
					{
						valence = conn;
						hyd = 0;
					}
					else
						hyd = -1; // will throw an error in the end
				}
				else if (conn > 7)
					hyd = -1; // will throw an error in the end
			}
		}
	}

	this.valence = valence;
	this.implicitH = hyd;
	if (this.implicitH < 0)
	{
		this.valence = conn;
		this.implicitH = 0;
		this.badConn = true;
		return false;
	}
	/* jm.evers */
	ui.Brutto.push(label);
	if( hyd > 0){
	 for( var i=0; i<hyd;i++){
	  ui.Brutto.push('H');
	 };
	};
	
	return true;
};

chem.Struct.Atom.prototype.calcValenceMinusHyd = function (conn)
{
	var atom = this;
	var charge = atom.charge;
	var label = atom.label;
	var elem = chem.Element.getElementByLabel(label);
	if (elem == null)
		throw new Error("Element " + label + " unknown");
	if (elem < 0) { // query atom, skip
		this.implicitH = 0;
		return null;
	}

	var groupno = chem.Element.elements.get(elem).group;
	var rad = chem.Struct.radicalElectrons(atom.radical);

	if (groupno == 3)
	{
		if (label == 'B' || label == 'Al' || label == 'Ga' || label == 'In')
		{
			if (charge == -1)
				if (rad + conn <= 4)
					return rad + conn;
		}
	}
	else if (groupno == 5)
	{
		if (label == 'N' || label == 'P')
		{
			if (charge == 1)
				return rad + conn;
			if (charge == 2)
				return rad + conn;
		}
		else if (label == 'Sb' || label == 'Bi' || label == 'As')
		{
			if (charge == 1)
				return rad + conn;
			else if (charge == 2)
				return rad + conn;
		}
	}
	else if (groupno == 6)
	{
		if (label == 'O')
		{
			if (charge >= 1)
				return rad + conn;
		}
		else if (label == 'S'  || label == 'Se' || label == 'Po')
		{
			if (charge == 1)
				return rad + conn;
		}
	}
	else if (groupno == 7)
	{
		if (label == 'Cl' || label == 'Br' ||
			label == 'I'  || label == 'At')
			{
			if (charge == 1)
				return rad + conn;
		}
	}

	return rad + conn + Math.abs(charge);
};

chem.Struct.prototype.calcImplicitHydrogen = function (aid)
{
	var conn = this.calcConn(aid);
	var atom = this.atoms.get(aid);
	atom.badConn = false;
	if (conn < 0 || atom.isQuery()) {
		atom.implicitH = 0;
		return;
	}
	if (atom.explicitValence >= 0) {
		var elem = chem.Element.getElementByLabel(atom.label);
		atom.implicitH = 0;
		if (elem != null) {
			atom.implicitH = atom.explicitValence - atom.calcValenceMinusHyd(conn);
			if (atom.implicitH < 0) {
				atom.implicitH = 0;
				atom.badConn = true;
			}
		}
	} else {
		atom.calcValence(conn);
	}
};

/* jm evers : needed for molmass calculations ...*/
var AllElements={H:1.00794,
He:4.002602,
Li:6.941,
Be:9.01218,
B:10.811,
C:12.011,
N:14.00674,
O:15.9994,
F:18.998403,
Ne:20.1797,
Na:22.989768,
Mg:24.305,
Al:26.981539,
Si:28.0855,
P:30.973762,
S:32.066,
Cl:35.4527,
Ar:39.948,
K:39.0983,
Ca:40.078,
Sc:44.95591,
Ti:47.88,
V:50.9415,
Cr:51.9961,
Mn:54.93805,
Fe:55.847,
Co:58.9332,
Ni:58.6934,
Cu:63.546,
Zn:65.39,
Ga:69.723,
Ge:72.61,
As:74.92159,
Se:78.96,
Br:79.904,
Kr:83.8,
Rb:85.4678,
Sr:87.62,
Y:88.90585,
Zr:91.224,
Nb:92.90638,
Mo:95.94,
Tc:97.9072,
Ru:101.07,
Rh:102.9055,
Pd:106.42,
Ag:107.8682,
Cd:112.411,
In:114.818,
Sn:118.71,
Sb:121.760,
Te:127.6,
I:126.90447,
Xe:131.29,
Cs:132.90543,
Ba:137.327,
La:138.9055,
Ce:140.115,
Pr:140.90765,
Nd:144.24,
Pm:144.9127,
Sm:150.36,
Eu:151.965,
Gd:157.25,
Tb:158.92534,
Dy:162.50,
Ho:164.93032,
Er:167.26,
Tm:168.93421,
Yb:173.04,
Lu:174.967,
Hf:178.49,
Ta:180.9479,
W:183.84,
Re:186.207,
Os:190.23,
Ir:192.22,
Pt:195.08,
Au:196.96654,
Hg:200.59,
Tl:204.3833,
Pb:207.2,
Bi:208.98037,
Po:208.9824,
At:209.9871,
Rn:222.0176,
Fr:223.0197,
Ra:226.0254,
Ac:227.0278,
Th:232.0381,
Pa:231.03588,
U:238.0289,
Np:237.048,
Pu:244.0642,
Am:243.0614,
Cm:247.0703,
Bk:247.0703,
Cf:251.0796,
Es:252.083,
Fm:257.0951,
Md:258.1,
No:259.1009,
Lr:262.11};
