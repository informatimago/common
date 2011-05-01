/******************************************************************************
FILE:               Bencoding.h
LANGUAGE:           ANSI-C
SYSTEM:             ANSI
USER-INTERFACE:     ANSI
DESCRIPTION
    This module exports types and routines to manage single-byte
    8-bit character encodings, and convert strings from one encoding
    to an other.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    2003-11-30 <PJB> Replaced BenStringP with const char* for gcc...
    1999-09-13 <PJB> Made this module from the encoding (nema) tool.
LEGAL
    GPL
    
    Copyright Pascal J. Bourguignon 1991 - 2011
    
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version
    2 of the License, or (at your option) any later version.
    
    This program is distributed in the hope that it will be
    useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public
    License along with this program; if not, write to the Free
    Software Foundation, Inc., 59 Temple Place, Suite 330,
    Boston, MA 02111-1307 USA
******************************************************************************/
#ifndef inhibit_Bencoding_h
#define inhibit_Bencoding_h
/* #include <BcTypes.h> */
#include <BcString.h>


    typedef struct {
        const char*            charName;
        const char*            asciiApproximation;
    }                       BenApproximationT;


    typedef struct {
        int                         count;
        BenApproximationT*          approximations;
        /*
            Approximation tables must be sorted on the charName field.
        */
    }                           BenApproximationTableT;


    typedef const char*          BenEncodingTableT[256];

    typedef const char*          BenConversionTableT[256];



    extern const char** BenEncodingTableNames(void);
        /*
            POST:       BenEncodingTableNames()[0]!=NULL.

            RETURN:     A NULL-terminated table containing the names of the
                        encoding tables known to this library.
        */

    extern BenEncodingTableT* BenEncodingTableNamed(const char* tabName);
        /*
            RETURN:     The encoding table named `tabName', 
                        or NULL if it does not exist.
        */

    extern void BenAddEncodingTable(BenEncodingTableT* table,
                                    const char* tabName);
        /*
            DO:         Add the given encoding table to the set of available
                        encoding tables.

                        If a table with the same name already exist, 
                        then it is replaced by the given one.
                        The parameters are hold in the list without copying.

            NOTE:       It is not mandatory to add an encoding table to the
                        list of encoding tables to use it with the other 
                        routines of this module.
        */



    extern const char** BenApproximationNames(void);
        /*
            POST:       BenApproximationNames()[0]!=NULL.

            RETURN:     A NULL-terminated table containing the names of the
                        approximation tables known to this library.
        */

    extern BenApproximationTableT* BenApproximationTableNamed(
        const char* tabName);
        /*
            RETURN:     The approximation table named `tabName', 
                        or NULL if it does not exist.
        */

    extern void BenAddApproximationTable(BenApproximationTableT* table,
                                         const char* tabName);
        /*
            DO:         Add the given approximation table to the set of available
                        approximation tables.

                        If a table with the same name already exist, 
                        then it is replaced by the given one.
                        The parameters are hold in the list without copying.

            NOTE:       It is not mandatory to add an approximation table to the
                        list of approximation tables to use it with the other 
                        routines of this module.
        */


    extern int BenFindCharNameInEncoding(BenEncodingTableT* encoding,
                                           const char* charName);
        /*
            RETURN:    The ascii code (between 0 and 255 inclusive) of the 
                       character named `charName' in the given encoding, or 
                       -1 if no character with such name exists in the encoding.
            NOTE:      The algorithm used is a sequential search. (O(n)).
        */

    extern int BenFindCharNameInApproximationTable(
        BenApproximationTableT* approx,
        const char* charName);
        /*
            RETURN:    The index in the approx table of the entry corresponding
                       to the character named `charName',
                       or -1 if no such entry exists.
            NOTE:      The algorithm used is a dichotomic search. (O(log2(n))).
        */





    typedef enum {
        BenMode_Normal,
            /*
                When the char name is not found in the destination 
                encoding table, then the replacement string is used.
            */
        BenMode_Approximation,
            /*  
                When the char name is not found in the destination 
                encoding table, then it is approximated using the 
                given approximation table.
            */
        BenMode_CharName
            /*  
                When the char name is not found in the destination 
                encoding table, then it is replaced by the given 
                replacement char name.
                If the replacement is not a char name in the 
                destination encoding, then revert to the normal mode.
            */
    } BenModeT;


    extern void BenBuildConversionTable(BenModeT mode,
                                        BenEncodingTableT* from,
                                        BenEncodingTableT* to,
                                        BenApproximationTableT* approx,
                                        const char* replacement,
                                        BenConversionTableT* convtable);
        /*
            DO:         Builds a conversion table between the given from and to
                        encoding tables, using the given approximation table
                        and the replacement string when a code in the from table
                        does not exist in the to table, depending on the mode
                        specified.

            POST:       convtable is filled with strings from the to or the 
                        approx tables, or replacement.
        */


    extern BcString_T BenEscapeString(const char* string);

    extern BcString_T BenConvertString(BenConversionTableT* table,
                                       char* string);
        /*
            RETURN:     A BcString containing the string converted using the
                        given conversion table.
        */



#endif
/*** Bencoding.h                      --                     --          ***/
