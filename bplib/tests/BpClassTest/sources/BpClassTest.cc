/******************************************************************************
FILE:               BpClassTest.cc
LANGUAGE:           C++
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
AUTHOR
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    1995-11-19 <PJB> Creation. 
LEGAL
    Copyright Pascal J. Bourguignon 1995 - 2002

    This file is part of the bplib library..

    This  program is  free software;  you can  redistribute  it and/or
    modify it  under the  terms of the  GNU General Public  License as
    published by the Free Software Foundation; either version 2 of the
    License, or (at your option) any later version.

    This program  is distributed in the  hope that it  will be useful,
    but  WITHOUT ANY WARRANTY;  without even  the implied  warranty of
    MERCHANTABILITY or FITNESS FOR  A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a  copy of the GNU General Public License
    along with  this program; see the  file COPYING; if  not, write to
    the Free  Software Foundation, Inc.,  59 Temple Place,  Suite 330,
    Boston, MA 02111-1307 USA
******************************************************************************/
#include <BpClassTest.hh>
#include <BcImplementation.h>


    CONSTRUCTOR(BpClassTest)
    {
        {
            static BpClass* BpClassTestClass=NIL;
            if(BpClassTestClass==NIL){
                BpClassTestClass=NEW(BpClass);
                BpClassTestClass->nameSet("BpClassTest");
                BpClassTestClass->superClassSet(isa);
                BpClassTestClass->factorySet(NEW(BpClassTest));
            }
            isa=BpClassTestClass;
        }
    }//BpClassTest;
    
    
    DESTRUCTOR(BpClassTest)
    {
    }//~BpClassTest;
    
    
    METHOD(BpClassTest,test,(void),void)
    {
    }//test;
    
    
int main(void)
{
    BpClassTest*        test;
    
    test=NEW(BpClassTest);
    test->test();
    DELETE(test);
    return(0);
}//main;

//END.

