/*****************************************************************************
FILE:               bjstring_list.c
LANGUAGE:           c
SYSTEM:             POSIX
USER-INTERFACE:     NONE
DESCRIPTION
    
    This module exports routines to manipulate strings and list of strings.
    
AUTHORS
    <PJB> Pascal Bourguignon <pjb@informatimago.com>
MODIFICATIONS
    2003-12-03 <PJB> Created.
BUGS
LEGAL
    GPL
    
    Copyright Pascal Bourguignon 2003 - 2011
    
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
*****************************************************************************/
#include <stdio.h>
#include <bjstring_list.h>

    unsigned int bjstring_count_occurences(const bjstring_t* string,
                                           const bjstring_t* substring)
    {
        unsigned int occurences=0;
        unsigned int string_length=bjstring_length(string);
        unsigned int substring_length=bjstring_length(substring);
        unsigned int position=bjstring_search_forward(string,substring,0);
        while(position<string_length){
            occurences++;
            position=bjstring_search_forward(string,substring,
                                             position+substring_length);
        }
        return(occurences);
    }/*bjstring_count_occurences*/



    bjarray_t* bjstring_split_string(const bjstring_t* string,
                                     const bjstring_t* separator)
    {
        if(separator==0){
            static const bjstring_t* space=0;
            if(space==0){
                bjstring_t* new_space=bjstring_new_string(" ");
                bjobject_retain(new_space);
                space=new_space;
            }
            separator=space;
        }
        {
            unsigned int occurences=bjstring_count_occurences(string,separator);
            bjarray_t* result=bjarray_new(1+occurences);
            unsigned int string_length=bjstring_length(string);
            unsigned int separator_length=bjstring_length(separator);
            unsigned int start=0;
            unsigned int position=bjstring_search_forward(string,separator,0);
            unsigned int idx=0;
            while(position<string_length){
                bjarray_set_element_at(
                    result,idx++,
                    bjstring_substring(string,start,position-start));
                start=position+separator_length;
                position=bjstring_search_forward(string,separator,start);
            }
            bjarray_set_element_at(
                result,idx++,
                bjstring_substring(string,start,string_length-start));
            return(result);
        }
    }/*bjstring_split_string*/


    bjstring_t* bjstring_unsplit_string(const bjarray_t* strings,
                                        const bjstring_t* separator)
    {
        unsigned int i;
        unsigned int length=0;
        bjstring_t*  result=bjstring_new();
        if(separator==0){
            static const bjstring_t* space=0;
            if(space==0){
                bjstring_t* new_space=bjstring_new_string(" ");
                bjobject_retain(new_space);
                space=new_space;
            }
            separator=space;
        }
        for(i=0;i<bjarray_count(strings);i++){
            length+=bjstring_length(bjarray_element_at(strings,i));
        }
        length+=(bjarray_count(strings)-1)*bjstring_length(separator);
        bjstring_set_capacity_copy(result,length,no);
        bjstring_append(result,bjarray_element_at(strings,0));
        for(i=1;i<bjarray_count(strings);i++){
            bjstring_append(result,separator);
            bjstring_append(result,bjarray_element_at(strings,i));
        }
        return(result);
    }/*bjstring_unsplit_string*/



    static void print_words(FILE* out,bjarray_t* words,unsigned int column,
                            unsigned int left,unsigned int right)
        /*
            PRE:    left<right
            DO:     Prints words, separated by one space, flowing them
            from left margin to right margin.
        */
    {
        unsigned int count=bjarray_count(words);
        unsigned int i=0;
        while(i<count){
            bjstring_t* word=bjarray_element_at(words,i++);
            unsigned int length=bjstring_length(word);
            if(column<left){
                fprintf(out,"%*s",left,"");
                column=left;
            }else if(column+length>right){
                fprintf(out,"\n%*s",left,"");
                column=left;
            }
            fprintf(out,"%s ",bjstring_string(word));
            column+=length+1;
        }
    }/*print_words*/



    static void bjstring_test_split_unsplit_check(bjstring_t* text,
                                                  bjstring_t* sep)
    {
        bjstring_t* unsplit;
        bjarray_t* words=bjstring_split_string(text,sep);
        fprintf(stdout,"\nWORDS (split %s%s%s):\n",
                sep?"\"":"",
                sep?bjstring_string(sep):"default",
                sep?"\"":"");
        unsplit=bjstring_unsplit_string(words,sep);
        if(bjstring_compare(unsplit,text)==order_same){
            fprintf(stdout,"EQUAL UNSPLITED.\n\n");
        }else{
            fprintf(stdout,"*** DIFFERENT UNSPLITED!\n\n");
        }
        print_words(stdout,words,0,8,72);
        fprintf(stdout,"\n\n");
    }/*bjstring_test_split_unsplit_check*/


    void bjstring_test_split_unsplit(void)
    {
        bjstring_t* text=bjstring_new_string(
            "line Hao Wang, logicien americain. "\
            "line  "\
            "line L'algorithme en question a ete publie en 1960 dans "\
            "line l'IBM Journal, article intitule \"Toward Mechanical "\
            "line Mathematics\", avec des variantes et une extension au "\
            "line calcul des predicats. Il s'agit ici du \"premier "\
            "line programme\" de Wang, systeme \"P\". "\
            "line  ");
        bjstring_append_string(
            text,
            "line L'article a ete ecrit en 1958, et les experiences "\
            "line effectuees sur IBM 704 - machine a lampes, 32 k mots de "\
            "line 36 bits, celle-la meme qui vit naitre LISP a la meme "\
            "line epoque. Le programme a ete ecrit en assembleur (Fortran "\
            "line existait, mais il ne s'etait pas encore impose) et "\
            "line l'auteur estime que \"there is very little in the program "\
            "line that is not straightforward\". "\
            "line  ");
        bjstring_append_string(
            text,
            "line Il observe que les preuves engendrees sont "\
            "line \"essentiellement des arbres\", et annonce que la "\
            "line machine a demontre 220 theoremes du calcul des "\
            "line propositions (tautologies) en 3 minutes. Il en tire "\
            "line argument pour la superiorite d'une approche "\
            "line algorithmique par rapport a une approche heuristique "\
            "line comme celle du \"Logic Theorist\" de Newell, Shaw et "\
            "line Simon (a partir de 1956 sur la machine JOHNNIAC de la "\
            "line Rand Corporation): un debat qui dure encore... "\
            "line  ");
        bjstring_append_string(
            text,
            "line Cet algorithme a ete popularise par J. McCarthy, comme "\
            "line exemple-fanion d'application de LISP. Il figure dans le "\
            "line manuel de la premiere version de LISP (LISP 1, sur "\
            "line IBM 704 justement, le manuel est date de Mars 1960), et "\
            "line il a ete repris dans le celebre \"LISP 1.5 Programmer's "\
            "line Manual\" publie en 1962 par MIT Press, un des "\
            "line maitres-livres de l'Informatique. ");
        bjstring_test_split_unsplit_check(text,0);
        bjstring_test_split_unsplit_check(text,bjstring_new_string(" "));
        bjstring_test_split_unsplit_check(text,bjstring_new_string("en"));
        bjstring_test_split_unsplit_check(text,bjstring_new_string("line "));
    }/*bjstring_test_split_unsplit*/


/*** bjstring_list.c                  -- 2004-01-01 09:42:40 -- pascal   ***/
