/**
 * stochastic 'infinite' name generation based on table seeded by words 
 * Portions Copyright (C) Guy W. Lecky-Thompson, 2000
 * André Sier, 2004, 2010
 * http://www.gamasutra.com/view/feature/3377/algorithms_for_an_infinite_universe.php?print=1
 **/

/*
 
 Copyright (c) 2010 André Sier
 
 Permission is hereby granted, free of charge, to any person obtaining
 a copy of this software and associated documentation files (the
 "Software"), to deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sublicense, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to
 the following conditions:
 
 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  
 
 */

#pragma once

#define ALPHABET	28
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#include "ofMain.h"



class ofxNameGen{			
	
	public:
	
			ofxNameGen()	{reset();}
			~ofxNameGen()	{}
	
			bool			setup(string filename);
			void			addWords(string sym);
			void			setNumLetters(const int nl = 7) {nLetters = nl;}
			const int		getNumLetters(){return nLetters;}
			const string	generate();
			const string	generateFromChar(char c);
			const string	getWord(){return words;}
	
			void			post();
			void			resetTable();
			void			reset();
	
			int*			getFrequencyTablePtr();
			int				alphabet;
	
	
		private:
			
			int				ulWordTable[ALPHABET][ALPHABET];  
			int				nLetters;
			string			words;
			string			wordsdelim;
			int				txtidx;
			int				txtmax;			
			bool			bResetTable;
			
			const int		getLetterPosition(int cPrevious);			
			
};






