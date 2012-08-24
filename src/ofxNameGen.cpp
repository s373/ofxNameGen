/*
 *  ofxNameGen.cpp
 *
 *  Created by andre sier on 20100402.
 *  Copyright 2004,2010 s373.net/x. All rights reserved.
 *
 */

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



#include "ofxNameGen.h"






bool ofxNameGen::setup(string filename){
    
    reset();
    bool loaded = false;
    const string fn = ofToDataPath(filename);
    
    ifstream infile;
    infile.open(fn.c_str());    
    vector <string> txts;
    
    while (!infile.eof()) {        
        string         txt;
        getline(infile,txt);
        txts.push_back(txt);
    }    
    infile.close();

    if(txts.size() > 0){
        loaded = true;
    }
        
    for(int i=0; i<txts.size();i++){
        // TODO: fix this to multiple delims
//        vector <string> strings = ofSplitString( ofToLower(txts[i]), wordsdelim , true, true);
        vector <string> strings = ofSplitString( txts[i], " " ); 
        
        for(int j=0; j<strings.size(); j++){            
            addWords(strings[j]);
        }        
    }
    
    
    return loaded;    
    
}






void ofxNameGen::addWords(string sym){
    
    int nWordLength, nFirstLetter, nLastLetter;

    string small = ofToLower(sym);
    
    nWordLength = sym.length();
    nFirstLetter = ( small[0] - 'a' ) + 1;
    nLastLetter =  ( small[nWordLength-1] - 'a' ) + 1;

    // add to frequency table
    ulWordTable[0][nFirstLetter]++; //space followed by letter
    ulWordTable[nLastLetter][27]++; //letter followed by space
    for (int i=0; i<nWordLength-2; i++) {
        nFirstLetter = ( small[i] - 'a' ) + 1;
        nLastLetter =  ( small[i+1] - 'a' ) + 1;
        ulWordTable[nFirstLetter][nLastLetter]++;
    }
    
    
    
}






void ofxNameGen::post(){
        for (int j=0; j<ALPHABET; j++) {
            printf("%02d ",j);
            for (int i=0; i<ALPHABET; i++) {
                printf(" %02d ", ulWordTable[i][j]);
            } 
            printf("\n");
        }        
}






void ofxNameGen::reset(){    
    bResetTable = false;
    nLetters = 7;
    words = "";
    wordsdelim = ", {}()+-\".;'?!: . )~ºª´`0123456789";
    txtidx = 0;
    txtmax = 0;
    alphabet = ALPHABET;
    resetTable();
}






void ofxNameGen::resetTable(){    
    for (int j=0; j<ALPHABET; j++) {
        for (int i=0; i<ALPHABET; i++) {
            ulWordTable[i][j] = 0;
        } 
    }        
}






const string ofxNameGen::generate(){

    int nLetterPosition;
    
    /// generate random string
    char data[nLetters];
    for (int i=0; i<nLetters; i++) {
        data[i] = (char) ofRandom(255);
    }
    
    // 1. find first letter    
    nLetterPosition = getLetterPosition(0);
    data[0] = (char)nLetterPosition;
    
    
    // 2- compute rest of word
    for (int i=1; i<nLetters;i++) {
        nLetterPosition = getLetterPosition(nLetterPosition);
        data[i] = (char) nLetterPosition;
    }
        
    // 3- char -> string    
    stringstream ss;
    for (int i=0; i<nLetters; i++) {
        ss << data[i];
    }    
    ss >> words;
        
    return words;
}






const string ofxNameGen::generateFromChar(char c){
    
    int nLetterPosition;
    
    /// generate random string
    char data[nLetters];
    
    // 1. find first letter    
    nLetterPosition = getLetterPosition((int)c);
    data[0] = (char)nLetterPosition;
    
    
    // 2- compute rest of word
    for (int i=1; i<nLetters;i++) {
        nLetterPosition = getLetterPosition(nLetterPosition);
        data[i] = (char) nLetterPosition;
    }
    
    // 3- char -> string    
    stringstream ss;
    for (int i=0; i<nLetters; i++) {
        ss << data[i];
    }    
    ss >> words;
    
    return words;
}






const int ofxNameGen::getLetterPosition(int cPrevious){        
    int nCounter;
    int ulFrequencyTotal = 0;
    int ulFrequencyRunningTotal = 0;
    int ulRandomLetter = 0;
    int nChoice;
    
    int nPrevious = (cPrevious-'a')+1;
    if (nPrevious<=0) nPrevious = 0;
    
    int lsum = 0;
    for ( int i=0; i<28;i++) {
        lsum +=  ulWordTable[nPrevious][i];
    }
        
    do {
        nChoice = (int)ofRandom(65536)%ALPHABET;
    } 
    while (ulWordTable[nPrevious][nChoice]==0);
        
    // Change nChoice from a reference into a character
    if ((nChoice == 0) || (nChoice == 27))
        nChoice = ' ';
    else
        nChoice = 'a' + (nChoice - 1);
    
    return nChoice;
            
}






int* ofxNameGen::getFrequencyTablePtr(){
    return &ulWordTable[0][0];
}







