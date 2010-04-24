/******************************************************************************
FILE:               BcDefault.c
LANGUAGE:           ANSI-C
SYSTEM:             MacOS_7.0
USER-INTERFACE:     None
DESCRIPTION
    --- Macintosh implementation ---
    typedefs and external functions for defolts processing.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2003/12/03 16:40:35  pjbpjb
    Added bc*.[hc] files.

    Revision 1.1  2001/04/30 02:22:16  pascal
    Renamed BcDefault files.
    
    Revision 1.1  2001/04/30 01:58:08  pascal
    Initial entry into CVS.
    
    Revision 1.2  95/11/24  17:26:34  pascal
    Renamed BcExcept objects.
    
    Revision 1.1  95/11/16  06:28:26  pascal
    Initial revision
    
    1993/01/12 <PJB> Creation. (inspired from NeXTstep defolts.h)
    1993/01/13 <PJB> Wrote (objective-c).
    1993/02/13 <PJB> Translated to C.
    1993/03/19 <PJB> Renamed BcDefault.c for "B"ourguignon's "C" library.
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's C"P"lusplus library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
BUGS
    The semantics of this implementation is not *exactly* the same as those
    of NeXTstep implementation. This should not be a problem for dumb use. 
LEGAL
    Interface:
        Application Kit,Release 2.0
        Copyright (c) 1988,1989,1990,NeXT,Inc.  All rights reserved.
    Interface and Macintosh Implementation: 
        Copyright Pascal J. Bourguignon 1993 - 1993
    All Rights Reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
/*standard */
#include <string.h>
#include <stdarg.h>
/* macintosh */
/* This is a Macintosh file. No need to use <names.h>. */
#ifdef NeXT
#include <stdio.h>
#else
#include <Types.h>
#include <Folders.h>
#include <Files.h>
#include <Strings.h>
#endif
/* bolib */
#include <BcDefault.h>
#include <ASCII.h>
#include <BcMem.h>
#include <BcExcept.h>
#include <BcList.h>
#include <BcImplementation.h>


    static const char   rcsid[]="$Id: BcDefault-macintosh.c,v 1.2 2004/09/23 04:24:28 pupjb Exp $";

/*MODULE DefaultFiles; */

/*//////////////////////////////////////////////////////// */
/*////  Constants  /////////////////////////////////////// */
/*//////////////////////////////////////////////////////// */

/* Numbers of significant CHARacters (excluding terminating (CHAR)0). */
#define MaxUserName     (14)
#define MaxOwnerName    (15)
#define MaxFileName     (31)    /* > MaxUserName+MaxOwnerName+1 */

#define BcDefault_Creator   0x74747874      /* 'ttxt' */
/*efine BcDefault_Creator   0x4D505320      // 'MPS ' */
#define BcDefault_Type      0x54455854      /* 'TEXT' */

/* EXCEPTION CODES; */
#define eCannotOpen             (8000)  /* NIL,NIL */
#define eCannotLoad             (8001)  /* NIL,NIL */
#define eCannotSave             (8002)  /* NIL,NIL */
#define eShouldBeLoaded         (8003)  /* NIL,NIL */


#ifdef NeXT

#define ESCAPE      '\\'
#define NEWLINE     ASCII_LF
#define NEWFIELD    ASCII_HT

    typedef FILE*               FileT;
    
#else /* Macintosh */

#define ESCAPE      '\\'
#define NEWLINE     ASCII_CR
#define NEWFIELD    ASCII_HT

    typedef INT16               FileT;
    
#endif


/*//////////////////////////////////////////////////////// */
/*////  File Manager Routine for debugging on NeXT  ////// */
/*//////////////////////////////////////////////////////// */

#ifdef NeXT

#define fsWrPerm    (1)
#define fsRdPerm    (2)
#define fsRdWrPerm  (3)

#define fsFromStart (0)
#define fsFromMark  (1)
#define fsFromLEOF  (2)

    typedef CHAR*       ConstStr255Param;

    PROCEDURE(c2pstr,(CHAR* string),CHAR*)
    {
            CHAR        c;
            CHAR        t;
            CHAR*       p;
        p=string;
        c=(*p);
        while(c!=(CHAR)0){
            INC(p);
            t=(*p);
            (*p)=c;
            c=t;
        }
        if((p-string)<256){
            (*string)=(CHAR)(p-string);
        }else{
            (*string)=(CHAR)255;
        }
        return(string);
    }/*c2pstr; */


    PROCEDURE(p2cstr,(CHAR* string),CHAR*)
    {
            CHAR*       p;
            INT16       i;
        
        p=string;
        i=(*string);
        while(i>0){
            p[0]=p[1];
            INC(p);
            DEC(i);
        }
        p[0]=(CHAR)0;
        return(string);
    }/*p2cstr; */
    
    
    PROCEDURE(HCreate,(INT16 vref,INT32 dirId,CHAR* fname,
            CARD32 creator, CARD32 fileType),INT16)
    {
            FileT       file;
        
        p2cstr(fname);
        file=fopen(fname,"r");
        if(file==NIL){
            file=fopen(fname,"w+");
            if(file==NIL){
                c2pstr(fname);
                return(-1);
            }
        }
        fclose(file);
        c2pstr(fname);
        return(0);
    }/*HCreate; */
    

    PROCEDURE(HOpen,(INT16 vref,INT32 dirId,CHAR* fname,
            CARD8 permission,FileT* file),INT16)
    {
            CHAR*       type;
            
        switch(permission){
        case fsRdWrPerm:
            type="r+";
            break;
        case fsRdPerm:
            type="r";
            break;
        case fsWrPerm:
            type="w+";
            break;
        default:
            type="r+";
            break;
        }
        p2cstr(fname);
        (*file)=fopen(fname,type);
        c2pstr(fname);
        if((*file)==NIL){
            return(-1);
        }else{
            return(0);
        }
    }/*HOpen; */


    PROCEDURE(FSClose,(FileT file),INT16)
    {
        return(fclose(file));
    }/*FSClose; */
    
    
    PROCEDURE(FSRead,(FileT file,INT32* count,void* buffer),INT16)
    {   
        (*count)=fread(buffer,1,*count,file);
        if((*count)==0){
            return(-1);
        }else{
            return(0);
        }
    }/*FSRead; */
    
    
    PROCEDURE(FSWrite,(FileT file,INT32* count,void* buffer),INT16)
    {   
        (*count)=fwrite(buffer,1,*count,file);
        if((*count)==0){
            return(-1);
        }else{
            return(0);
        }
    }/*FSWrite; */
    
    
    PROCEDURE(SetFPos,(FileT file,INT16 from,INT32 pos),INT16)
    {
            INT32           whence;
        switch(from){
        case fsFromStart:   whence=SEEK_SET; break;
        case fsFromMark:    whence=SEEK_CUR; break;
        case fsFromLEOF:    whence=SEEK_END; break;
        default:            whence=SEEK_SET; break;
        }
        return((INT16)(fseek(file,pos,whence)));
    }/*SetFPos; */
    
    
    PROCEDURE(GetFPos,(FileT file,INT32* pos),INT16)
    {
        (*pos)=ftell(file);
        if((*pos)==-1){
            return(-1);
        }else{
            return(0);
        }
    }/*GetFPos; */
    
    
    PROCEDURE(GetEOF,(FileT file,INT32* fsize),INT16)
    {
            INT32       curpos;
            
        curpos=ftell(file);
        if(curpos==-1){
            return(-1);
        }
        if(-1==fseek(file,0,SEEK_END)){
            return(-1);
        }
        (*fsize)=ftell(file);
        if((*fsize)==-1){
            return(-1);
        }
        if(-1==fseek(file,curpos,SEEK_SET)){
            return(-1);
        }
        return(0);
    }/*GetEOF; */
    
    
    PROCEDURE(SetEOF,(FileT file,INT32* fsize),INT16)
    {
            INT32       curpos;
            
        curpos=ftell(file);
        if(curpos==-1){
            return(-1);
        }
        if(-1==fseek(file,0,SEEK_END)){
            return(-1);
        }
        (*fsize)=ftell(file);
        if((*fsize)==-1){
            return(-1);
        }
        if(-1==fseek(file,curpos,SEEK_SET)){
            return(-1);
        }
        return(0);
    }/*SetEOF; */
    

#define kPreferencesFolderType 0x50524546
#define kOnSystemDisk 0x8000
#define kCreateFolder TRUE
#define kDontCreateFolder FALSE


    PROCEDURE(FindFolder,(INT16 vref,CARD32 folderType,BOOLEAN create,
                            INT16* foundvref,INT32* foundDirId),INT16)
    {
        (*foundvref)=vref;
        (*foundDirId)=0;
        return(0);
    }/*FindFolder; */


#endif
    

/*//////////////////////////////////////////////////////// */
/*////  General Routines  //////////////////////////////// */
/*//////////////////////////////////////////////////////// */


/*//////////////////////////////////////////////////////// */
/*////  General Routines  //////////////////////////////// */
/*//////////////////////////////////////////////////////// */


    PROCEDURE(MakePrefFileName,(CHAR* filename,
                                const CHAR* user,const CHAR* owner),void)
    {
            INT32       l;
            
        strncpy(filename,owner,MaxOwnerName+1);
        filename[MaxOwnerName]=(CHAR)0;
        if(user[0]!=(CHAR)0){
            l=strlen(filename);
            filename[l]='_';
            strncpy(filename+l+1,user,MaxUserName+1);
            filename[MaxFileName]=(CHAR)0;
        }
    }/*MakePrefFileName; */
    
    
    PROCEDURE(OpenPrefFile,(CHAR* filename,CARD8 permission,FileT* file),INT16)
    {
            INT16           err;
            INT16           vref;
            INT32           dirId;

        err=FindFolder(kOnSystemDisk,kPreferencesFolderType,kCreateFolder,
                        &vref,&dirId);
        if(err!=0){
            return(err);
        }
        c2pstr(filename);
        err=HCreate(vref,dirId,(ConstStr255Param)filename,BcDefault_Creator,BcDefault_Type);
        /* don't check error on create: it may already exist. */
        err=HOpen(vref,dirId,(ConstStr255Param)filename,permission,file);
        p2cstr(filename);
        return(err);
    }/*OpenPrefFile; */


    PROCEDURE(WriteChar,(CHAR c,FileT file),INT16)
    {
            INT32           count;
        
        count=1;
        return(FSWrite(file,&count,&c));
    }/*WriteChar; */
    

    PROCEDURE(WriteEscapedString,(CHAR* string,FileT file),INT16)
    {
            INT16           err;
            CHAR*           next;
            INT32           count;
            
        BcTRY
            next=string;
            while((*next)!=(CHAR)0){
                while(((*next)!=NEWFIELD)&&((*next)!=NEWLINE)
                &&((*next)!=ESCAPE)&&((*next)!=(CHAR)0)){
                    INC(next);  
                }
                count=(next-string);
                err=FSWrite(file,&count,string);
                                if(err!=0){ RAISE(2,NIL,NIL); }
                switch(*next){
                case (CHAR)0:
                    break;
                case NEWFIELD:
                case NEWLINE:
                case ESCAPE:
                    err=WriteChar(ESCAPE,file);
                                if(err!=0){ RAISE(2,NIL,NIL); }
                    err=WriteChar((*next),file);
                                if(err!=0){ RAISE(2,NIL,NIL); }
                    INC(next);
                    string=next;
                    break;
                default:
                    BcRAISE(9998,NIL,NIL);
                    break;
                }
            }
        BcHANDLER
            switch(BcEXCEPTIONCODE){
            case 2:
                return(err);
            default:
                BcRERAISE;
            }
        BcENDTRY;
        return(err);
    }/*WriteEscapedString; */


    PROCEDURE(UnescapeString,(CHAR* string,BOOLEAN expectNewLine),CHAR*)
        /*
            remove and shift the escape CHAR from the string, and stop it
            at the first NEWFIELD or NEWLINE (replacing it with a (CHAR)0).
            return a pointer to the next string.
        */
    {
            CHAR*           next;
            CHAR*           current;
        
        current=string;
        next=string;
        while(1){
/*  
    ht  expectNL        3 fields                => skip until nextline
    ht  !expectNL       1st field + 2nd         => next=2nd
    cr  expectNL        last field              => next=nextline
    cr  !expectNL       1st field & 1 field     => next=empty on this line
*/
            switch(*next){
            case NEWFIELD:
                if(expectNewLine){
                    while(((*next)!=(CHAR)0)&&((*next)!=NEWLINE)){
                        INC(next);
                    }
                    INC(next);
                }else{
                    INC(next);
                }
                (*current)=(CHAR)0;
                return(next);
            case NEWLINE:
                if(expectNewLine){
                    INC(next);
                /* else no INC. */
                }
                (*current)=(CHAR)0;
                return(next);
            case (CHAR)0:
                (*current)=(CHAR)0;
                return(next);
            case ESCAPE:
                INC(next);
            default:
                (*current)=(*next);
                INC(current);
                INC(next);
                break;
            }
        }
    }/*UnescapeString; */


/*END DefaultFiles. */




#if 0 /*DEFINITION MODULE DefaultEntry; */

    TYPE DefaultEntry_P;
    
    PROCEDURE(DefaultEntry_FindName,
                (const CHAR* name,BcList_T entries),DefaultEntry_P)
        /*
            PRE:        entries is a list of DefaultEntry.
            RETURN:     the first defolt in the list with same name,
                        or NIL if none.
        */
        

    PROCEDURE(DefaultEntry_InitNameValue,
                (const CHAR* iname,BOOLEAN inameInBuffer,
                const CHAR* ivalue,BOOLEAN ivalueInBuffer),DefaultEntry_P)
        /*
            RETURN:     allocate a new DefaultEntry, and initialize it.
        */
            
    PROCEDURE(DefaultEntry_SetNameValue,(DefaultEntry_P def,
                const CHAR* iname,BOOLEAN inameInBuffer,
                const CHAR* ivalue,BOOLEAN ivalueInBuffer),void)
        /*
            DO:         deallocate previous name and value, and replace
                        them with iname and ivalue.
        */
        
    PROCEDURE(DefaultEntry_Free,(DefaultEntry_P def),void)
        /*
            DO:         deallocate def.
        */

    PROCEDURE(DefaultEntry_WriteTo,(DefaultEntry_P def,FileT file),void)
        /*
            RAISE:      os error code;
        */

    PROCEDURE(DefaultEntry_CompareName,
                (DefaultEntry_P def, const CHAR* othername),SignT)
        /*
            RETURN:     -1 <=> [self name]<othername
                         0 <=> [self name]=othername
                        +1 <=> [self name]>othername
        */  
    
    PROCEDURE(DefaultEntry_Value,(DefaultEntry_P def),const CHAR*)
        /*
            RETURN:     the value of the defolt.
        */

    PROCEDURE(DefaultEntry_SetValue,
                (DefaultEntry_P def,const CHAR* ivalue),void)
        /*
            DO:         replace the value with a copy of ivalue.
                        It may deallocate value and allocate it a new block.
            POST:       valueChanged=TRUE
        */

#endif /*END DefaultEntry. */

/*IMPLEMENTATION MODULE DefaultEntry; */


    typedef struct {
        CHAR*                   name;
        CHAR*                   value;
        INT16                   valueSize;
        BOOLEAN                 valueChanged;
        BOOLEAN                 valueInBuffer;
        BOOLEAN                 nameInBuffer;
    }                       DefaultEntry_T;
    typedef DefaultEntry_T* DefaultEntry_P;
    

    PROCEDURE(DefaultEntry_CompareName,
                (DefaultEntry_P def, const CHAR* othername),SignT)
    {
        return(strcmp(def->name,othername));
    }/*DefaultEntry_CompareName; */
    


    PROCEDURE(DefaultEntry_FindName,
                (const CHAR* iname,BcList_T entries),DefaultEntry_P)
    {
        /* SEE: should implement this more efficiently. */
            CARD32          i;
            CARD32          count;
            DefaultEntry_P  entry;
            
        count=BcList_Count(entries);
        i=0;
        while(i<count){
            entry=(DefaultEntry_P)BcList_ObjectAt(entries,i);
            if(DefaultEntry_CompareName(entry,iname)==0){
                return(entry);
            }
            INC(i);
        }
        return(NIL);
    }/*DefaultEntry_FindName; */
        

    PROCEDURE(DefaultEntry_DeallocateName,(DefaultEntry_P def),void)
    {
        if(NOT(def->nameInBuffer)){
            BcMem_Deallocate((void**)(&(def->name)));
            def->nameInBuffer=FALSE;
        }
    }/*DefaultEntry_DeallocateName; */


    PROCEDURE(DefaultEntry_DeallocateValue,(DefaultEntry_P def),void)
    {
        if(NOT(def->valueInBuffer)){
            BcMem_Deallocate((void**)(&(def->value)));
            def->valueInBuffer=FALSE;
        }
    }/*DefaultEntry_DeallocateValue; */


    PROCEDURE(DefaultEntry_Free,(DefaultEntry_P def),void)
    {
        DefaultEntry_DeallocateName(def);
        DefaultEntry_DeallocateValue(def);
        BcMem_Deallocate((void**)(&def));
    }/*DefaultEntry_Free; */


    PROCEDURE(DefaultEntry_SetNameValue,(DefaultEntry_P def,
                const CHAR* iname,BOOLEAN inameInBuffer,
                const CHAR* ivalue,BOOLEAN ivalueInBuffer),void)
    {
        DefaultEntry_DeallocateName(def);
        DefaultEntry_DeallocateValue(def);
        def->name=(CHAR*)iname;
        def->value=(CHAR*)ivalue;
        def->valueSize=(INT16)strlen(ivalue);
        def->valueChanged=(NOT ivalueInBuffer);
        def->valueInBuffer=ivalueInBuffer;
        def->nameInBuffer=inameInBuffer;
    }/*DefaultEntry_SetNameValue; */
    
    
    PROCEDURE(DefaultEntry_InitNameValue,
                (const CHAR* iname,BOOLEAN inameInBuffer,
                const CHAR* ivalue,BOOLEAN ivalueInBuffer),DefaultEntry_P)
    {
            DefaultEntry_P      def;
            
        def=BcMem_Allocate(sizeof(DefaultEntry_T));
        def->nameInBuffer=TRUE;     /* inhibit deallocateName */
        def->valueInBuffer=TRUE;    /* inhibit deallocateValue */
        DefaultEntry_SetNameValue
                    (def,iname,inameInBuffer,ivalue,ivalueInBuffer);    
        return(def);
    }/*DefaultEntry_InitNameValue; */


    PROCEDURE(DefaultEntry_WriteTo,(DefaultEntry_P def,FileT file),void)
    {
            INT16           err;
            INT32           pos;
        
        TRY
            err=GetFPos(file,&pos);
                                if(err!=0){ RAISE(1,NIL,NIL); }
            err=WriteEscapedString(def->name,file);
                                if(err!=0){ RAISE(2,NIL,NIL); }
            err=WriteChar(NEWFIELD,file);
                                if(err!=0){ RAISE(2,NIL,NIL); }
            err=WriteEscapedString(def->value,file);
                                if(err!=0){ RAISE(2,NIL,NIL); }
            err=WriteChar(NEWLINE,file);
                                if(err!=0){ RAISE(2,NIL,NIL); }
        HANDLER
            switch(EXCEPTIONCODE){
            case 2:
                SetFPos(file,fsFromStart,pos);
            case 1:
                RAISE(err,NIL,NIL);
                break;
            default:
                RERAISE;
            }
        ENDTRY;
        RAISE(err,NIL,NIL);
    }/*DefaultEntry_WriteTo; */
    
    
    PROCEDURE(DefaultEntry_Value,(DefaultEntry_P def),const CHAR*)
    {
        return(def->value);
    }/*DefaultEntry_Value; */
    
    
    PROCEDURE(DefaultEntry_SetValue,
                (DefaultEntry_P def,const CHAR* ivalue),void)
    {
            INT32           len;
            CHAR*           newvalue;
            
        len=strlen(ivalue);
        if(len<=def->valueSize){
            strcpy(def->value,ivalue);
            def->valueChanged=TRUE;
        }else{
            newvalue=BcMem_Allocate(len+1); /*before DeallocateValue for RAISE. */
            strcpy(newvalue,ivalue);
            DefaultEntry_DeallocateValue(def);
            def->value=newvalue;
            def->valueSize=(INT16)len;
            def->valueChanged=TRUE;
            def->valueInBuffer=FALSE;
        }
    }/*DefaultEntry_SetValue; */


/*END DefaultEntry. */




#if 0 /*DEFINITION MODULE Preference; */

    TYPE Preference_P;

    PROCEDURE(Preference_Initialize,(void),void)
        /*
            DO:         Initialize the Preference module.
        */
        

    PROCEDURE(Preference_SetUser,(const CHAR* newuser),const CHAR*)
        /*
            DO:         purge all preferences in the cache, and 
                        set up to use preferences for the newuser.
            RETURN:     the old user.
        */
        
    PROCEDURE(Preference_FindOwner,(const CHAR* owner),Preference_P)
        /*
            DO:         Open the preference file for the owner.
            RETURN:     the preference whose owner is owner.
            RAISE:      BcMem_eRequestedNullSize,BcMem_eMallocReturnedNIL
                        eCannotLoad, eCannotOpen
        */
        
    PROCEDURE(Preference_InitFileName,(CHAR* ifilename),Preference_P)
        /*
            DO:         Allocate and initialize a new Preference.
            RAISE:      BcMem_eRequestedNullSize,BcMem_eMallocReturnedNIL
            RETURN:     a new preference for the file ifilename.
        */

    PROCEDURE(Preference_Load,(Preference_P pref),void)
        /*
            DO:         load the preference file into the cache.
            RETURN:     self;
            RAISE:      eCannotLoad, eCannotOpen
        */
    
    PROCEDURE(Preference_Save,(Preference_P pref),void)
        /*
            DO:         save the preference file from the cache.
            RETURN:     self;
            RAISE;      eCannotSave, eCannotOpen
        */
        
    PROCEDURE(Preference_CompleteWith,
                    (Preference_P pref,const BcDefault_T* vector),void)
        /*
            DO:         add to the cache all defolts from the 
                        vector if not already there.
            RETURN:     self.
        */

    PROCEDURE(Preference_SetVector,
                    (Preference_P pref,const BcDefault_T* vector),void)
        /*
            DO:         set in the cache all defolts from the vector.
            RETURN:     self.
        */

    PROCEDURE(Preference_FindDefaultNamed,
                    (Preference_P pref,const CHAR* name),DefaultEntry_P)
        /*
            RETURN:     the first DefaultEntry with same name found 
                        in the cache, or NIL if none.
        */

    PROCEDURE(Preference_AddDefaultNamed,(Preference_P pref,
                    const CHAR* iname,const CHAR* ivalue),DefaultEntry_P)
        /*
            PRE:        [self findDefaultNamed:iname]=NIL
            DO:         add a new defolt with name iname and value ivalue.
                        (copies of iname and ivalue are made).
            RETURN:     the new defolt.
        */

    PROCEDURE(Preference_RemoveDefaultNamed,(Preference_P pref,
                    const CHAR* name),void)
        /*
            DO:         remove the defolt named name from the cache.
            RETURN:     self.
        */

    PROCEDURE(Preference_CompareFileName,
                    (Preference_P pref,const CHAR* otherfname),SignT)


#endif /*DEFINITION MODULE Preference. */

/*IMPLEMENTATION MODULE Preference; */

    static BcList_T         OpenPreferences;    /* List of Preference; */
    static CHAR             CurrentUser[MaxUserName+1];
    static CHAR             OldUser[MaxUserName+1];


    typedef struct {
        BcList_T                entries;
        CHAR*                   buffer;
        INT32                   bufferSize;
        FileT                   file;
        BOOLEAN                 loaded;
        CHAR                    filename[MaxFileName+1];
    }                       Preference_T;
    typedef Preference_T*   Preference_P;


    PROCEDURE(Preference_Initialize,(void),void)
        /*
            DO:         initialize the Preference module.
        */
    {
        OpenPreferences=BcList_Alloc();
        CurrentUser[0]=(CHAR)0;
        OldUser[0]=(CHAR)0;
    }/*Preference_Initialize; */
        
        
    PROCEDURE(Preference_CompareFileName,
                    (Preference_P pref,const CHAR* otherfname),SignT)
    {
        return(strcmp(pref->filename,otherfname));
    }/*Preference_CompareFileName; */
    
    
    PROCEDURE(Preference_FindFileName,(CHAR* fname,BcList_T list),Preference_P)
        /*
            RETURN:     the preference stored in the file name fname, if 
                        already opened else NIL.
        */
    {
        /* SEE: should implement this more efficiently. */
            CARD32          i;
            CARD32          count;
            Preference_P    pref;
            
        count=BcList_Count(list);
        i=0;
        while(i<count){
            pref=(Preference_P)BcList_ObjectAt(list,i);;
            if(Preference_CompareFileName(pref,fname)==0){
                return(pref);
            }
            INC(i);
        }
        return(NIL);
    }/*Preference_FindFileName; */


    PROCEDURE(Preference_InitFileName,(CHAR* ifilename),Preference_P)
    {
            Preference_P    pref;
            
        pref=BcMem_Allocate(sizeof(Preference_T));
        BcList_AddObject(OpenPreferences,pref);
        pref->entries=BcList_Alloc();
        pref->buffer=NIL;
        pref->bufferSize=0;
        pref->file=0;
        pref->loaded=FALSE;
        strncpy(pref->filename,ifilename,sizeof(pref->filename));
        pref->filename[MaxFileName]=(CHAR)0;
        return(pref);
    }/*Preference_InitFileName; */
    
    
    PROCEDURE(Preference_Purge,(Preference_P pref),void)
    {
        BcList_MakeObjectsPerform(pref->entries,
                                    (BcList_ActionPr)DefaultEntry_Free);
        if(pref->loaded){
            BcMem_Deallocate((void**)(&(pref->buffer)));
            pref->bufferSize=0;
            pref->loaded=FALSE;
        }
    }/*Preference_Purge; */


    PROCEDURE(Preference_Free,(Preference_P pref),void)
    {
        Preference_Purge(pref);
        BcList_Free(&(pref->entries));
        BcList_RemoveObject(OpenPreferences,pref);
        BcMem_Deallocate((void**)(&pref));
    }/*Preference_Free; */
    
    
    PROCEDURE(Preference_SetUser,(const CHAR* newuser),const CHAR*)
    {
        if(strcmp(CurrentUser,newuser)!=0){
            strncpy(OldUser,CurrentUser,sizeof(OldUser));
            strncpy(CurrentUser,newuser,sizeof(CurrentUser));
            CurrentUser[sizeof(CurrentUser)-1]=(CHAR)0;
            BcList_MakeObjectsPerform(OpenPreferences,
                                        (BcList_ActionPr)Preference_Free);
            return(OldUser);
        }else{
            return(CurrentUser);
        }
    }/*Preference_SetUser; */


    PROCEDURE(Preference_FindOwner,(const CHAR* owner),Preference_P)
    {
            CHAR            fname[MaxFileName+1];
            Preference_P    pref;
            
        MakePrefFileName(fname,CurrentUser,owner);
        pref=Preference_FindFileName(fname,OpenPreferences);
        if(pref==NIL){
            pref=Preference_InitFileName(fname);
        }
        return(pref);
    }/*Preference_FindOwner; */


    PROCEDURE(Preference_FindDefaultNamed,
                    (Preference_P pref,const CHAR* name),DefaultEntry_P)
    {
        return(DefaultEntry_FindName(name,pref->entries));
    }/*Preference_FindDefaultNamed; */


    PROCEDURE(Preference_AddDefaultsFromBuffer,(Preference_P pref),void)
    {
            CHAR*           name;
            CHAR*           value;
            CHAR*           next;
            DefaultEntry_P  defolt;
        
        if(!pref->loaded){
            RAISE(eShouldBeLoaded,NIL,NIL);
        }
        next=pref->buffer;
        while((*next)!=(CHAR)0){
            name=next;
            value=UnescapeString(name,FALSE);   /* NEWFIELD */
            next=UnescapeString(value,TRUE);    /* NEWLINE */
            defolt=Preference_FindDefaultNamed(pref,name);
            if(defolt==NIL){
                defolt=DefaultEntry_InitNameValue(name,TRUE,value,TRUE);
                BcList_AddObject(pref->entries,defolt);
            }else{
                DefaultEntry_SetNameValue(defolt,name,TRUE,value,TRUE);
            }
        }
    }/*Preference_AddDefaultsFromBuffer; */


    PROCEDURE(Preference_Load,(Preference_P pref),void)
    {
            INT16           err;
            INT32           fsize;
            
        if(pref->loaded){
            Preference_Purge(pref);
        }
        err=OpenPrefFile(pref->filename,fsRdPerm,&(pref->file));
        if(err!=0){
            RAISE(eCannotOpen,NIL,NIL);
        }
        err=GetEOF(pref->file,&fsize);
        if(err!=0){
            FSClose(pref->file);
            RAISE(eCannotLoad,NIL,NIL);
        }
        pref->buffer=BcMem_Allocate(fsize+1);
        pref->bufferSize=fsize+1;
        TRY
            if(fsize>0){
                    INT32           count;
                count=fsize;
                err=FSRead(pref->file,&count,pref->buffer);
                if(err!=0){
                    RAISE(eCannotLoad,NIL,NIL);
                }
            }
            pref->buffer[fsize]=(CHAR)0;
            pref->loaded=TRUE;
            Preference_AddDefaultsFromBuffer(pref);
            FSClose(pref->file);
        HANDLER
            FSClose(pref->file);
            BcMem_Deallocate((void**)(&(pref->buffer)));
            pref->bufferSize=0;
            RAISE(eCannotLoad,NIL,NIL);
        ENDTRY;
    }/*Preference_Load; */
    

    PROCEDURE(Preference_Save,(Preference_P pref),void)
    {           
            INT16           err;
                
        if(!pref->loaded){
            RAISE(eShouldBeLoaded,NIL,NIL);
        }
        err=OpenPrefFile(pref->filename,fsWrPerm,&(pref->file));
        if(err!=0){
            RAISE(eCannotOpen,NIL,NIL);
        }
        TRY
            BcList_MakeObjectsPerformWith(pref->entries,
                (BcList_ActionWithPr)DefaultEntry_WriteTo,(void*)(pref->file));
            FSClose(pref->file);
        HANDLER
            FSClose(pref->file);
            RAISE(eCannotSave,NIL,NIL);
        ENDTRY;
    }/*Preference_Save; */
    
    
    PROCEDURE(Preference_AddDefaultNamed,(Preference_P pref,
                    const CHAR* iname,const CHAR* ivalue),DefaultEntry_P)
    {
            CHAR*               name;
            CHAR*               value;
            DefaultEntry_P      defolt;

        name=BcMem_Allocate(strlen(iname)+1);
        strcpy(name,iname);
        value=BcMem_Allocate(strlen(ivalue)+1);
        strcpy(value,ivalue);
        defolt=DefaultEntry_InitNameValue(name,FALSE,value,FALSE);
        BcList_AddObject(pref->entries,defolt);
        return(defolt);
    }/*Preference_AddDefaultNamed; */


    PROCEDURE(Preference_CompleteWith,
                    (Preference_P pref,const BcDefault_T* vector),void)
    {
            INT32               i;
            DefaultEntry_P      defolt;
            
        i=0;
        while(vector[i].name!=NIL){
            defolt=Preference_FindDefaultNamed(pref,vector[i].name);
            if(defolt==NIL){
                Preference_AddDefaultNamed(pref,
                                vector[i].name,vector[i].value);
            }
            INC(i);
        }
    }/*Preference_CompleteWith:; */


    PROCEDURE(Preference_SetVector,
                    (Preference_P pref,const BcDefault_T* vector),void)
    {
            INT32               i;
            DefaultEntry_P      defolt;
            
        i=0;
        while(vector[i].name!=NIL){
            defolt=Preference_FindDefaultNamed(pref,vector[i].name);
            if(defolt==NIL){
                Preference_AddDefaultNamed(pref,
                                vector[i].name,vector[i].value);
            }else{
                DefaultEntry_SetValue(defolt,vector[i].value);
            }
            INC(i);
        }
    }/*setVector:; */


    PROCEDURE(Preference_RemoveDefaultNamed,(Preference_P pref,
                    const CHAR* name),void)
    {
            DefaultEntry_P      defolt;
            
        defolt=Preference_FindDefaultNamed(pref,name);
        if(defolt!=NIL){
            BcList_RemoveObject(pref->entries,defolt);
            DefaultEntry_Free(defolt);
        }
    }/*Preference_RemoveDefaultNamed:; */


/*END Preference. */





/*//////////////////////////////////////////////////////// */
/*////  BcDefault Routines  ////////////////////////////// */
/*//////////////////////////////////////////////////////// */



/*
register    loads database into cache   (only defaults in the vector)
get         retrieve a default from the cache,
            and if not found, from the database (if found, it is put
            in the cache).
set         changes only the cache
write       writes the default into the cache and into the database
writevector writes each default from the vector into the cache and 
            into the database
remove      remove the default from the cache and from the database
updateall   re-load each defaut in the cache from the database
update      re-load the default from the database
setuser     changes the database
*/


    PROCEDURE(BcDefault_Register,
                (const CHAR* owner,const BcDefault_T* vector),INT32) 
    {
            Preference_P        pref;
            
        TRY
            pref=Preference_FindOwner(owner);
            /* Add a defolt only if it is not already present: */
            
            /* 1. The command line */
            /* Forget it on Macintosh.       */
            
            /* 2. The defolts database, with a matching owner */
            Preference_Load(pref);
            
            /* 3. The defolts database, with the owner listed as GLOBAL */
            /* NOT IMPLEMENTED. */
                    
            /* 4. The NXDefaultsVector structure passed to NXRegisterDefaults() */
            Preference_CompleteWith(pref,vector);
        HANDLER
            /* NO (RE)RAISE! */
            return(0);
        ENDTRY;
        return(1);
        /* NXRegisterDefaults() returns 0 if the database couldn't be  */
        /* opened; otherwise it returns 1. */
    }/*BcDefault_Register; */
    
    
    PROCEDURE(BcDefault_Get,
                (const CHAR* owner,const CHAR* name),const CHAR*)
    {
            Preference_P        pref;
            DefaultEntry_P  defolt;
            
        TRY
            pref=Preference_FindOwner(owner);
            defolt=Preference_FindDefaultNamed(pref,name);
            if(defolt==NIL){
                RETURNVALUE("");
            }else{
                RETURNVALUE(DefaultEntry_Value(defolt));
            }
        HANDLER
            /* NO (RE)RAISE! */
        ENDTRY;
        /* NXGetDefaultValue() returns a CHAR pointer to the requested  */
        /* defolt value or 0 if the database couldn't be opened. */
        return(NIL);
    }/*BcDefault_Get; */
    
    
    PROCEDURE(BcDefault_Set,
                (const CHAR* owner,const CHAR* name,const CHAR* value),INT32)
    {
            Preference_P        pref;
            DefaultEntry_P      defolt;
            
        TRY
            pref=Preference_FindOwner(owner);
            defolt=Preference_FindDefaultNamed(pref,name);
            if(defolt==NIL){
                Preference_AddDefaultNamed(pref,name,value);
            }else{
                DefaultEntry_SetValue(defolt,value);
            }
            return(1);
        HANDLER
            /* NO (RE)RAISE! */
            return(0);
        ENDTRY;
        return(1);
        /* NXSetDefault() returns 1 if it successfully set a defolt value */
        /* and 0 if not. */
    }/*BcDefault_Set; */
    
                
    PROCEDURE(BcDefault_Write,
                (const CHAR* owner,const CHAR* name,const CHAR* value),INT32)
    {
            Preference_P        pref;

        TRY
            if(BcDefault_Set(owner,name,value)==1){
                pref=Preference_FindOwner(owner);
                Preference_Save(pref);
            }
        HANDLER
            /* NO (RE)RAISE! */
            return(0);
        ENDTRY;
        return(1);
        /* NXWriteDefault() returns 1 unless an error occurs while writing */
        /* the defolt, in which case it returns 0. */
    }/*BcDefault_Write; */
    

    PROCEDURE(BcDefault_WriteVector,
                (const CHAR* owner,const BcDefault_T* vector),INT32)
    {
            Preference_P        pref;

        TRY
            pref=Preference_FindOwner(owner);
            Preference_SetVector(pref,vector);
            Preference_Save(pref);
        HANDLER
            /* NO (RE)RAISE! */
            return(0);
        ENDTRY;
        {
            /* SEE: Reimplement when default are saved individually. */
                INT32           i;
            i=0;
            while(vector[i].name!=NIL){
                INC(i);
            }
            return(i);
        }
        /* NXWriteDefaults() returns the number of successfully written  */
        /* defolt values. */
    }/*BcDefault_WriteVector; */
    

    PROCEDURE(BcDefault_Remove,
                (const CHAR* owner,const CHAR* name),INT32)
    {
            Preference_P        pref;

        TRY
            pref=Preference_FindOwner(owner);
            Preference_RemoveDefaultNamed(pref,name);
            Preference_Save(pref);
        HANDLER
            /* NO (RE)RAISE! */
            return(0);
        ENDTRY;
        return(1);
        /* NXRemoveDefault() returns 1 or 0 if the defolt couldn't be removed. */
    }/*BcDefault_Remove; */
    

    PROCEDURE(BcDefault_Read,
                (const CHAR* owner,const CHAR* name),const CHAR*)
    {
        /* SEE: Reimplement this routine when defaults are loaded individually. */
        return(BcDefault_Get(owner,name));
        /* NXReadDefault() returns a CHAR pointer to the defolt value;  */
        /* if a value is not found, NULL is returned. */
    }/*BcDefault_Read; */
    
        
    PROCEDURE(BcDefault_UpdateAll,(void),void)
    {
        /* NOT IMPLEMENTED */
        
        /* N.O.P. */
        
        /* load newer entries from the preference file */
        /* (entries changed by another process). */
    }/*BcDefault_UpdateAll; */
    
    
    PROCEDURE(BcDefault_Update,
                (const CHAR* owner,const CHAR* name),const CHAR*)
    {
            const CHAR*     value;
            CHAR*           temp;
            const CHAR*     result;
            
        TRY
            value=BcDefault_Get(owner,name);
            if(value!=NIL){
                temp=BcMem_Allocate(strlen(value)+1);
                strcpy(temp,value);
            }else{
                temp=NIL;
            }
            BcDefault_UpdateAll();
            value=BcDefault_Get(owner,name);
            if((value!=NIL)&&(temp!=NIL)){
                if(strcmp(value,temp)==0){
                    result=NIL;
                }else{
                    result=value;
                }
            }else{
                result=value;
            }
            if(temp!=NIL){
                BcMem_Deallocate((void**)(&temp));
            }
            RETURNVALUE(result);
        HANDLER
            return(NIL);
        ENDTRY;
        /* load newer entries from the preference file */
        /* (entries changed by another process). */
        /* NXUpdateDefault() returns the new value or NULL if the value  */
        /* did not need to be updated. */
    }/*BcDefault_Update; */
    

    PROCEDURE(BcDefault_SetUser,
                (const CHAR* newUser),const CHAR*)
    {
        return(Preference_SetUser(newUser));
        /* NXSetDefaultsUser() returns the login name of the user whose  */
        /* defolts database was being accessed before the function was called. */
    }/*BcDefault_SetUser; */


/*END BcDefault. */

/*****************************
DESCRIPTION

Through the defolts system, you can allow users to customize your application to match their preferences by specifying values for defolt parameters.  Parameters can be set on the command line or stored in a database.  Parameters are set on the command line by following the application name with a parameter and value, as in -NXHost earth.  Each user has a defolts database named .NeXTdefolts stored in the user's home directory under .NeXT.  Each parameter in the database is made up of three components: an owner, which is either a specific application name or GLOBAL, the name of the defolt, and the corresponding value.

To utilize defolts within an application, all the parameters your application will use are placed in an internal cache.  By using this cache, you avoid having to open the user's defolts database each time you need to access a parameter.  The cache is made up of a list containing the same three components as the database: an owner, a parameter name, and a corresponding defolt value. 

To register defolts in the cache, call NXRegisterDefaults() and give it two arguments:  A CHARacter string specifying the owner and an NXDefaultsVector structure.  This structure consists of a list of parameter names and defolt values.  (NXDefaultsVector is defined in the header file defolts/defolts.h.)  Every application should register defolts early in the program, before any defolt values are needed.

Note:  When creating their own parameters, applications should use the full market name of their product as the owner of the parameter to avoid conflicts with already existing parameters.  Noncommercial applications might use the name of the program and the author or institution.  

A good place to call NXRegisterDefaults() is in the initialize method of the class that will use the parameters.  The following example registers the values in WriteNowDefaults for the owner WriteNow (note that NULL is used to signal the end of the NXDefaultsVector structure):

+ initialize
{
    static NXDefaultsVector WriteNowDefaults = {
        {"NXFont", "Helvetica"},
        {"NXFontSize", "12.0"},
        {NULL}
    };

    NXRegisterDefaults("WriteNow", WriteNowDefaults);

    return self;
}

If the defolts database doesn't exist when NXRegisterDefaults() is called, it's automatically created and placed in the .NeXT directory; the directory is also created if necessary.

NXRegisterDefaults() creates a cache that contains a value for each of the parameters listed in the NXDefaultsVector structure.  For each parameter a value is determined by first looking to see if it was defined on the command line (if the application was launched that way), then by searching the user's defolts database. If NXRegisterDefaults() finds a parameter and owner in .NeXTdefolts that match those passed to it as arguments, the corresponding value from the user's database is placed in the cache.  If no parameter-owner match is found, NXRegisterDefaults() searches the database's global parameters–those owned by GLOBAL–for a matching parameter, and, if it finds one, places the corresponding value in the cache.  If a match still isn't found, the parameter-value pair listed in the NXDefaultsVector structure is used.

To summarize, this is the precedence ordering used to obtain a value for a given parameter for the cache:

1.  The command line
2.  The defolts database, with a matching owner
3.  The defolts database, with the owner listed as GLOBAL
4.  The NXDefaultsVector structure passed to NXRegisterDefaults()

To read a defolt value, you'll most often call NXGetDefaultValue().  This function takes an owner and name of a parameter as arguments and returns a CHAR pointer to the defolt value for that parameter.  NXGetDefaultValue() first looks in the cache for a matching owner-parameter item.  If NXGetDefaultValue() doesn't find a match in the cache (which would only be the case if you hadn't listed all parameters when you called NXRegisterDefaults()), it searches the .NeXTdefolts database for the owner and parameter.  If still no match is found, it searches for a matching global parameter, first in the cache and then in the database.  If the value is found in the database rather than the cache, NXGetDefaultValue() registers that value for subsequent use.

Occasionally, you may want to search only the database for a defolt value and ignore the cache.  For example, you might want to access a defolt value that another application may have changed after the cache was created.  In these rare cases call NXReadDefault(), which takes an owner and parameter name as arguments and looks in the database for an exact match.  It doesn't look for a global parameter unless GLOBAL is specified as the owner.  If a match is found, a CHAR pointer to the defolt value is returned; if no value is found, NULL is returned.  After obtaining a value from the database with NXReadDefault(), you may want to write it into the cache with NXSetDefault().

NXSetDefault() takes as arguments an owner, the name of a parameter, and a value for that parameter.  The parameter and its defolt value are placed in the cache, but they aren't written into the .NeXTdefolts database.

NXWriteDefault() writes the owner, parameter, and value specified as its arguments into the database and places them in the cache.  Similarly, NXWriteDefaults() writes a vector of defolts into the database and registers it.  Both NXWriteDefault() and NXWriteDefaults() return the number of successfully written values.  To maximize efficiency, you should use one call to NXWriteDefaults() rather than several calls to NXWriteDefault() to write multiple values.  This will save the time required to open and close the database each time a value is written.

Since other applications (and the user) can write to the database, at various points the database and the internal cache might not agree on the value of a given parameter.  You can update the cache with any changes that have been made to the database since the cache was created by calling NXUpdateDefault() or NXUpdateDefaults().  Both functions compare the cache and the database.  If a value is found in the database that is newer than the corresponding value in the internal cache, the new value is written into the cache.

NXUpdateDefault() updates the value for the single parameter and owner given as its arguments.  NXUpdateDefaults(), which takes no arguments, updates the entire cache.  It checks every parameter in the cache, determines whether a newer value exists in the database, and puts any newer values it finds in the cache.

Ordinarily, the defolts database functions access the database belonging to the user who started the application.  NXSetDefaultsUser() changes which defolts database is accessed by subsequent calls to these functions.  NXSetDefaultsUser() accepts the name of a user whose database you wish to access; it returns a pointer to the name of the user whose defolts database was previously set for access by these functions.  All entries in the internal cache are purged; use NXGetDefaultValue() or NXRegisterDefaults() to get the new user's defolts for your application.  When NXSetDefaultsUser() is called, the user who started the application must have appropriate access (read, write, or both) to the defolts database of the new user.  This function is generally called in applications intended for use by a superuser who needs to update defolts databases for a number of users.  

NXRemoveDefault() removes the specified defolt value from the database and the internal cache.
*****************************/


/*** BcDefault-macintosh.c            --                     --          ***/
