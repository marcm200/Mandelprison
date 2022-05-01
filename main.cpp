// MandelPrison - Free Benoit!

#include "stdio.h"
#include "stdint.h"
#include "math.h"
#include <limits>
#include "stdlib.h"
#include "string.h"
#include "time.h"


// consts
const int32_t MP_COMPANZ=16;
const int32_t MP_DEVICEPARTS=3;

const int32_t WAITTIME0=600; // milliseconds1
const int32_t WAITTIME1=1500; // milliseconds1

const uint8_t MP_NODEVICE=0;
const uint8_t MP_DEVICEMANUAL=1;
const uint8_t MP_DEVICEAUTOMATIC=2;

const int32_t MP_PARTS_PER_MULTIPLIERDETECTOR=3;
const int32_t MP_MAXPARAMS=16;

const int32_t MP_ANZ_MULTIPLECHOICE=4;

const int8_t MP_QA_QUESTION_ANSWER=1;
const int8_t MP_QA_MULTIPLECHOICE=2;

const int32_t MP_DIRECTION0=0;
const int32_t MP_NORTH=0;
const int32_t MP_SOUTH=1;
const int32_t MP_WEST =2;
const int32_t MP_EAST =3;
const int32_t MP_DIRECTION1=3;

const char mpDirectionStrD[][16] = { "Nord" ,"Sued" ,"West","Ost"  };
const char mpDirectionStrE[][16] = { "North","South","West","East" };

const uint8_t MP_DOOR_NONE=0;
const uint8_t MP_DOOR_OPEN=1;
const uint8_t MP_DOOR_PARABOLIC_LOCKED=2;

const int32_t MP_LINELEN=64;

const int8_t MP_DEUTSCH=0;
const int8_t MP_ENGLISCH=1;

const int32_t MP_LEVEL_MIN=0;
const int8_t MP_LEVEL_EASY=0;
const int8_t MP_LEVEL_INTERMEDIATE=1;
const int8_t MP_LEVEL_COMPLICATED=2;
const int32_t MP_LEVEL_MAX=2;

const char levelStrDE[][32] = {
    "einfach",
    "mittel",
    "kompliziert"
};

const char levelStrEN[][32] = {
    "easy",
    "intermediate",
    "complicated"
};


// defines as small functions
#define LANGUAGEDE(DD,EE) \
{\
    if (language == MP_DEUTSCH) printf(DD); else printf(EE);\
}

#define WRITETYPE(TT,FF,WW) \
{\
	TT tmpw32=WW;\
	if (fwrite(&tmpw32,1,sizeof(tmpw32),FF) != sizeof(tmpw32) ) {\
		return -1;\
	}\
}

#define READTYPE(TT,FF,VAR) \
{\
	TT tmpw32;\
	if (fread(&tmpw32,1,sizeof(tmpw32),FF) != sizeof(tmpw32) ) {\
		return -1;\
	}\
	VAR=tmpw32; \
}

#define MEMORY(VAR,WW) \
{\
    if ( !(VAR) ) { fprintf(stderr,"\nerror/%i. memory.\n",WW); }\
}

#define SETDOOR(TGT,STATUS,TGTCOMP,TGTROOM) \
{\
    (TGT).status=STATUS;\
    (TGT).target_compid=TGTCOMP;\
    (TGT).target_roomid=TGTROOM;\
}


// structs

const int32_t INT32MAX=(int32_t)1 << 30;
const int64_t INT50MAX=(int64_t)1 << 50;

struct DynSlowString {
	int32_t memory;
	char* text;

	DynSlowString(void);
	DynSlowString(const int32_t);
	virtual ~DynSlowString ();

	void add(const char*);
	void add(DynSlowString&);
	void add(const char);
	void setEmpty(void);
	void add_int(const int64_t);
};

struct mpHero {
    int32_t location0_compid,location0_roomid; // current Location
    int32_t location_compid,location_roomid; // current Location
    uint8_t device_multiplierDetector;
    int8_t tasksuccessfull;
    int8_t dev_part[MP_DEVICEPARTS+1]; // indices 1-3 used

    mpHero();
    void init(void);
    void testDetectorFullyAssembled(void);

    int8_t loadGameState(FILE*);
    int8_t saveGameState(FILE*);

};

struct mpParams {
    int32_t paranz;
    DynSlowString params[MP_MAXPARAMS],tmp;

    int8_t extractParams_A_nonconst(char*);
    int8_t contains_A(const char*);

};

struct mpObject {
    int32_t objid; // starts at 0, unique only as triple (compid,roomid,objid)

    virtual int8_t parseCommand_ACR(mpParams&,const int32_t,const int32_t) { return 0; }
    virtual int8_t getDescr_T(DynSlowString& T) { T.setEmpty(); T.add("(leer)"); return 0; }

    virtual int8_t saveGameState(FILE*) { return 0; }
    virtual int8_t loadGameState(FILE*) { return 0; }

};

typedef mpObject *PmpObject;

struct mpObjFloorNote : public mpObject {
    int8_t alreadyread;
    DynSlowString noteD,noteE;

    virtual int8_t parseCommand_ACR(mpParams&,const int32_t,const int32_t);
    virtual int8_t getDescr_T(DynSlowString&);

    virtual int8_t saveGameState(FILE*);
    virtual int8_t loadGameState(FILE*);

};

struct mpObjNoteBehindMirror : public mpObjFloorNote {
    int8_t objecthidesnote;

    virtual int8_t parseCommand_ACR(mpParams&,const int32_t,const int32_t);
    virtual int8_t getDescr_T(DynSlowString&);

    virtual int8_t saveGameState(FILE*);
    virtual int8_t loadGameState(FILE*);

};

struct mpObjDeviceUnderCarpet : public mpObject {
    int8_t hidden;
    int32_t partnumber;

    virtual int8_t parseCommand_ACR(mpParams&,const int32_t,const int32_t);
    virtual int8_t getDescr_T(DynSlowString&);

    virtual int8_t saveGameState(FILE*);
    virtual int8_t loadGameState(FILE*);

};

struct mpQuestion {
    DynSlowString questionD,questionE;

    virtual int8_t answer(void) { return 0; }

};

struct mpObjCaseDevicePart : public mpObject {
    int8_t locked;
    int8_t partnumber; // <= 0 => already taken
    mpQuestion* qa;

    virtual int8_t parseCommand_ACR(mpParams&,const int32_t,const int32_t);
    virtual int8_t getDescr_T(DynSlowString&);

    virtual int8_t saveGameState(FILE*);
    virtual int8_t loadGameState(FILE*);

};

struct mpObjNoteInCase : public mpObject {
    int8_t locked;
    mpQuestion* qa;
    DynSlowString noteD,noteE;

    virtual int8_t parseCommand_ACR(mpParams&,const int32_t,const int32_t);
    virtual int8_t getDescr_T(DynSlowString&);

    virtual int8_t saveGameState(FILE*);
    virtual int8_t loadGameState(FILE*);

};

struct mpQuestionQA : public mpQuestion {
    DynSlowString answerD,answerE;

    virtual int8_t answer(void);

};

struct mpQuestionMultipleChoice : public mpQuestion {
    // multiple choice
    DynSlowString mchoice[MP_ANZ_MULTIPLECHOICE];
    int32_t mchoice_correct;

    virtual int8_t answer(void);

};

struct mpObjPrisonCell : public mpObject {
    // Benoit Mandelbrot's cell
    int8_t imprisoned;
    mpQuestion* qa;

    mpObjPrisonCell();
    virtual ~mpObjPrisonCell();

    virtual int8_t parseCommand_ACR(mpParams&,const int32_t,const int32_t);
    virtual int8_t getDescr_T(DynSlowString&);

    virtual int8_t saveGameState(FILE*);
    virtual int8_t loadGameState(FILE*);

};

struct mpObjTransmitter : public mpObject {
    // Transmitter to another component of identical periodicity
    // as in order in array in playground.components
    int32_t target_compid,target_roomid;

    virtual int8_t parseCommand_ACR(mpParams&,const int32_t,const int32_t);
    virtual int8_t getDescr_T(DynSlowString&);

    virtual int8_t saveGameState(FILE*);
    virtual int8_t loadGameState(FILE*);

};

struct mpDoor {
    uint8_t status;
    int32_t target_compid,target_roomid;

    int8_t saveGameState(FILE*);
    int8_t loadGameState(FILE*);
};

struct mpRoom {
    int32_t roomid; // starts at 0, unique only as pair (compid,roomid)
    mpDoor doors[4];
    uint8_t predHC; // in case the room contains the hyperbolic center
    int32_t objectanz;
    double multiplier;
    double cReal,cImag; // complex coordinates of center of the room
    PmpObject* objects;

    mpRoom();
    virtual ~mpRoom();
    virtual void destroy();
    virtual int8_t parseCommand_ACR(mpParams&,const int32_t,const int32_t);

    void initObjects(const int32_t);

    int8_t saveGameState(FILE*);
    int8_t loadGameState(FILE*);
};

typedef mpRoom *PmpRoom;

struct mpComponent {
    int32_t compid; // starts at 0, unique in a specific playground
    int32_t roomanz;
    PmpRoom* rooms;
    double hcReal,hcImag; // hyperbolic center
    int32_t period,period_byhero; // as PIN

    mpComponent();
    virtual ~mpComponent();
    virtual void destroy(void);
    virtual int8_t parseCommand_ACR(mpParams&,const int32_t,const int32_t);

    void initRooms(const int32_t);

    mpRoom* getRoomPtr(const int32_t);

    int8_t saveGameState(FILE*);
    int8_t loadGameState(FILE*);

};

typedef mpComponent *PmpComponent;

struct mpPlayground {
    int32_t companz; // companz
    PmpComponent* components;

    mpPlayground();
    virtual ~mpPlayground();
    virtual void destroy(void);
    virtual int8_t parseCommand_ACR(mpParams&,const int32_t,const int32_t);

    void initComponents(const int32_t);
    void getCurrentLocation_T2(DynSlowString&,DynSlowString&);
    void getDoors_T(DynSlowString&);
    void getSight_T(DynSlowString&);

    double getMultiplier_CR(const int32_t,const int32_t);

    mpComponent* getComponentPtr(const int32_t);
    mpRoom* getCurrentRoomPtr(const int32_t,const int32_t);

    int8_t loadGameState(FILE*);
    int8_t saveGameState(FILE*);

};


// globals
mpHero hero;
mpPlayground playground;
int8_t abracadabra=0;
int8_t difficultyLevel=MP_LEVEL_EASY;
int8_t language=MP_DEUTSCH;
int8_t globalwaitflag=0;
int32_t globalwaittime=0;
char line[MP_LINELEN+8];


// routines
char* upper(char* s) {
	if (!s) return 0;
	int32_t L=strlen(s);
	if (L <= 0) return s;

	for(int32_t i=0;i<L;i++) {
		if ((s[i]>='a')&&(s[i]<='z')) s[i]=s[i]-'a'+'A';
		if (s[i]=='ö') s[i]='Ö';
		if (s[i]=='ü') s[i]='Ü';
		if (s[i]=='ä') s[i]='Ä';
	}

	return s;
}

char* chomp(char* s) {
	if (!s) return 0;
	int32_t L=strlen(s);
	for(int32_t i=L;i>=0;i--) {
        if (s[i]<32) s[i]=0; else break;
    }

	return s;
}

void deleteSpaces(char* s) {
	char *b=new char[strlen(s)+1]; // end-zero
	if (!b) { printf("\nerror 42.\n"); exit(99); }

	strcpy(b,s);
	int32_t ergidx=0;
	for(int32_t i=0;i<strlen(b);i++) {
		if (b[i] == ' ') continue;
		s[ergidx]=b[i];
		s[ergidx+1]=0;
		ergidx++;
	}

	delete[] b;

}

int8_t mpParams::contains_A(const char *atxt) {
    for(int32_t k=0;k<paranz;k++) {
        if (strstr(params[k].text,atxt)) return 1;
    } // k

    return 0;
}

int8_t mpParams::extractParams_A_nonconst(char* acmd) {
    upper(acmd);

    // only letters and digits are kept, everythin else is converted
    // to " ", then "  " (2 spaces) are condensed to " " (one space) repeatedly

    paranz=0;
    tmp.setEmpty();

    int32_t alen=strlen(acmd);
    int8_t lastwhite=1; // so starting spaces are deleted
    for(int32_t k=0;k<alen;k++) {
        if (
            ( (acmd[k] >= 'A') && (acmd[k] <= 'Z') ) ||
            ( (acmd[k] >= '0') && (acmd[k] <= '9') )
        ) {
            lastwhite=0;
            tmp.add(acmd[k]);
            continue;
        }

        // character is treated as whit-space
        // if there was already one => skip
        if (lastwhite > 0) continue;

        lastwhite=1;
        tmp.add(" ");

    } // k

    // if does not end in " "; add
    alen=strlen(tmp.text);
    if (alen <= 0) { paranz=0; return 0; }

    if (tmp.text[alen-1] != ' ') tmp.add(" ");

    // now split at every " "
    paranz=0;
    int32_t parid=0; // not 1
    alen=strlen(tmp.text);
    params[0].setEmpty();
    for(int32_t k=0;k<alen;k++) {
        if (tmp.text[k] == ' ') {
            paranz++;
            parid++;
            params[parid].setEmpty();
            if (paranz >= MP_MAXPARAMS) { printf("\nerror 13.\n"); exit(99); }

            continue;
        }

        params[parid].add(tmp.text[k]);

    } // k

    return 1; // success

}

int8_t mpPlayground::saveGameState(FILE* f) {
    if (!f) return 0;

    WRITETYPE(int8_t,f,language)
    WRITETYPE(int8_t,f,globalwaitflag)

    WRITETYPE(int32_t,f,companz)
    for(int32_t k=0;k<companz;k++) {
        if (components[k]->saveGameState(f) <= 0) return 0;
    }

    return 1;

}

int8_t mpPlayground::loadGameState(FILE* f) {
    if (!f) return 0;

    READTYPE(int8_t,f,language)
    READTYPE(int8_t,f,globalwaitflag)

    READTYPE(int32_t,f,companz)
    for(int32_t k=0;k<companz;k++) {
        if (components[k]->loadGameState(f) <= 0) return 0;
    }

    return 1;

}

void mpPlayground::getSight_T(DynSlowString& T) {
    T.setEmpty();

    mpRoom* R=getCurrentRoomPtr(hero.location_compid,hero.location_roomid);
    if (!R) { printf("\nerror 22\n"); exit(99); }

    DynSlowString t2;
    for(int32_t k=0;k<R->objectanz;k++) {
        if (R->objects[k]) if (R->objects[k]->getDescr_T(t2) > 0) {
            T.add("  ");
            T.add(t2);
            T.add("\n");
        }
    } // k

}

int8_t mpPlayground::parseCommand_ACR(
    mpParams& mpp,
    const int32_t loccomp,
    const int32_t locroom
) {
    if (mpp.paranz <= 0) return 0;

    if (strstr(mpp.params[0].text,"CFGNOWAIT")==mpp.params[0].text) { globalwaitflag=0; return 1; }
    if (strstr(mpp.params[0].text,"CFGWAIT")==mpp.params[0].text) { globalwaitflag=1; return 1; }

    // undocumented magic commands
    if (strstr(mpp.params[0].text,"CFGNOMAGIC")==mpp.params[0].text) { abracadabra=0; return 1; }
    if (strstr(mpp.params[0].text,"ABRACADABRA")==mpp.params[0].text) { abracadabra=1; return 1; }

    if (strstr(mpp.params[0].text,"CFGJUMP")==mpp.params[0].text) {
        int32_t c,r;
        int8_t error=0;
        if (mpp.paranz < 3) error=1;
        else {
            if (sscanf(mpp.params[1].text,"%i",&c) != 1) error=1;
            if (sscanf(mpp.params[2].text,"%i",&r) != 1) error=1;
        }

        if ( (c < 0) || (c >= MP_COMPANZ) ) error=1;
        else {
            mpComponent* pc=playground.getComponentPtr(c);
            if (!pc) error=1;
            else if ( (r<0) || (r >= pc->roomanz) ) error=1;
        }

        // no check if valid as only used by administrator
        if (error <= 0) {
            hero.location_compid=c;
            hero.location_roomid=r;
            return 1; // understood
        } else {
            printf("\n  cfg-error. compid,rommid out of range\n");
            return 1; // understood
        }
    }

    // give to componend
    mpComponent* c=getComponentPtr(loccomp);
    if (!c) { printf("\nerror 13.\n"); exit(99); }

    int8_t result=c->parseCommand_ACR(mpp,loccomp,locroom);
    if (result > 0) return result;

    // may there be a special handling?
    // currently: not

    return 0; // command not understood

}

int8_t mpObjFloorNote::saveGameState(FILE* f) {
    if (!f) return 0;

    WRITETYPE(int8_t,f,alreadyread)

    return 1;
}

int8_t mpObjFloorNote::loadGameState(FILE* f) {
    if (!f) return 0;

    READTYPE(int8_t,f,alreadyread)

    return 1;
}

int8_t mpObjFloorNote::getDescr_T(DynSlowString& T) {
    T.setEmpty();

    if (language == MP_DEUTSCH) {
        if (alreadyread <= 0) {
            T.add("ein Zettel liegt auf dem Boden");
        } else {
            T.add("eine Notiz auf dem Boden lautet\n  \"");
            T.add(noteD.text);
            T.add("\"");
        }
    } else {
        if (alreadyread <= 0) {
            T.add("there is a note on the floor");
        } else {
            T.add("a note saying\n  \"");
            T.add(noteE.text);
            T.add("\"");
        }
    }

    return 1;

}

int8_t mpObjDeviceUnderCarpet::saveGameState(FILE* f) {
    if (!f) return 0;

    WRITETYPE(int8_t,f,hidden)
    WRITETYPE(int32_t,f,partnumber)

    return 1;
}

int8_t mpObjDeviceUnderCarpet::loadGameState(FILE* f) {
    if (!f) return 0;

    READTYPE(int8_t,f,hidden)
    READTYPE(int32_t,f,partnumber)

    return 1;
}

int8_t mpObjDeviceUnderCarpet::getDescr_T(DynSlowString& T) {
    T.setEmpty();

    if (hidden > 0) {
        if (language == MP_DEUTSCH) {
            T.add("ein Teppichboden mit loser Ecke");
        } else {
            T.add("a carpet with a loose corner");
        }

        return 1;
    }

    // show device
    if (partnumber > 0) {
        if (language == MP_DEUTSCH) {
            T.add("ein elektronisches Bauteil mit der Aufschrift '");
            T.add_int(partnumber);
            T.add("' unter dem Teppich");
        } else {
            T.add("part of an electronic device inscribd with '");
            T.add_int(partnumber);
            T.add("' under the carpet");
        }
    } else {
        if (language == MP_DEUTSCH) {
            T.add("nichts zu sehen unter dem Teppich");
        } else {
            T.add("nothing to see under the carpet");
        }
    }

    return 1;

}

int8_t mpObjDeviceUnderCarpet::parseCommand_ACR(
    mpParams& mpp,
    const int32_t loccomp,
    const int32_t locroom
) {

    // look/move behind and displays what's written on the note

    if (mpp.paranz < 2) return 0;
    // look on/at floor, schaue/blicke auf/an boden
    if (
        (strstr(mpp.params[0].text,"LOOK")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"READ")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"MOVE")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"SCHAU")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"BLICK")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"BEWEG")==mpp.params[0].text)
    ) {
        // floor
        if (
            (mpp.contains_A("RUG") > 0) ||
            (mpp.contains_A("CARPET") > 0) ||
            (mpp.contains_A("TEPPICH") > 0)
        ) {
            if (hidden <= 0) {
                LANGUAGEDE("da ist nichts weiter","nothing new appears");
                globalwaittime=WAITTIME1;
                return 1;
            }

            hidden=0;
            return 1;

        } // rug

    } // look,schau,blick,move

    else
    if (
        (strstr(mpp.params[0].text,"GRAB")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"TAKE")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"NIMM")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"NEHM")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"HOLE")==mpp.params[0].text)
    ) {
        if ( (hidden > 0) || (partnumber < 0) ) return 0; // not understood

        if ( (partnumber < 1) || (partnumber > 3) ) { printf("\nerror 26.\n"); exit(99); }

        if (hero.dev_part[partnumber] > 0) {
            LANGUAGEDE("\nDu traegst bereits dieses Teil.","You're already owning that part.")
            globalwaittime=WAITTIME1;
            return 1;
        }

        hero.dev_part[partnumber]=1;
        partnumber=0; // now box empty
        hero.testDetectorFullyAssembled();
        LANGUAGEDE("Ich stecke das Teil ein.","Grabbing the part.")
        globalwaittime=WAITTIME1;
        return 1;

    } // grab

    return 0;

}

int8_t mpObjFloorNote::parseCommand_ACR(
    mpParams& mpp,
    const int32_t loccomp,
    const int32_t locroom
) {
    if (
        (mpp.contains_A("BEHIND") > 0) ||
        (mpp.contains_A("UNDER") > 0) ||
        (mpp.contains_A("HINTER") > 0) ||
        (mpp.contains_A("UNTER") > 0)
    ) return 0; // not possible here

    // look at/on/ and displays what's written on the note

    if (mpp.paranz < 2) return 0;
    // look on/at floor, schaue/blicke auf/an boden
    if (
        (strstr(mpp.params[0].text,"LOOK")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"READ")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"SCHAU")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"LIES")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"KUCK")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"BLICK")==mpp.params[0].text)
    ) {
        // floor
        if (
            (mpp.contains_A("NOTE") > 0) ||
            (mpp.contains_A("PAPER") > 0) ||
            (mpp.contains_A("NOTIZ") > 0) ||
            (mpp.contains_A("AUFSCHR") > 0) ||
            (mpp.contains_A("ZETTEL") > 0) ||
            (mpp.contains_A("PAPIER") > 0)
        ) {
            LANGUAGEDE("\nDie Notiz lautet\n  \"","\nThe note reads\n  \"")
            LANGUAGEDE(noteD.text,noteE.text);
            printf("\"\n");
            globalwaittime=WAITTIME1;
            alreadyread=1;
            return 1;
        } // note
        else
        if (
            (mpp.contains_A("FLOOR") > 0) ||
            (mpp.contains_A("BODEN") > 0)
        ) {
            LANGUAGEDE("Der Zettel ist beschriftet.","There's something written on the note.");
            globalwaittime=WAITTIME1;
            return 1;
        } // floor

    } // look,schau,blick

    // look on/at note/paper, schaue/blicke auf zettel,papier

    return 0;

}

int8_t mpObjNoteBehindMirror::getDescr_T(DynSlowString& T) {
    T.setEmpty();

    if (objecthidesnote > 0) {
        if (language == MP_DEUTSCH) {
            T.add("ein schiefhaengender Spiegel");
        } else {
            T.add("a mirror hinging on one corner");
        }

        return 1;
    }

    // show note
    if (language == MP_DEUTSCH) {
        if (alreadyread <= 0) {
            T.add("ein Zettel mit einer Aufschrift klebt hinter dem Spiegel");
        } else {
            T.add("eine Notiz hinter dem Spiegel lautet\n  \"");
            T.add(noteD.text);
            T.add("\"");
        }
    } else {
        if (alreadyread <= 0) {
            T.add("A note with something written on it sticks on the mirror's rear side");
        } else {
            T.add("A note behind the mirror says\n  \"");
            T.add(noteE.text);
            T.add("\"");
        }
    }

    return 1;

}

int8_t mpObjNoteBehindMirror::saveGameState(FILE* f) {
    if (!f) return 0;

    WRITETYPE(int8_t,f,objecthidesnote)

    return 1;

}

int8_t mpObjNoteBehindMirror::loadGameState(FILE* f) {
    if (!f) return 0;

    READTYPE(int8_t,f,objecthidesnote)

    return 1;

}

int8_t mpObjNoteBehindMirror::parseCommand_ACR(
    mpParams& mpp,
    const int32_t loccomp,
    const int32_t locroom
) {

    // look behind and displays what's written on the note

    if (mpp.paranz < 2) return 0;
    // look on/at floor, schaue/blicke auf/an boden
    if (
        (strstr(mpp.params[0].text,"LOOK")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"READ")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"SCHAU")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"LIES")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"KUCK")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"BLICK")==mpp.params[0].text)
    ) {
        // floor
        if (
            (objecthidesnote <= 0) && (
                (mpp.contains_A("NOTE") > 0) ||
                (mpp.contains_A("PAPER") > 0) ||
                (mpp.contains_A("NOTIZ") > 0) ||
                (mpp.contains_A("AUFSCHR") > 0) ||
                (mpp.contains_A("ZETTEL") > 0) ||
                (mpp.contains_A("PAPIER") > 0)
            )
        ) {
            LANGUAGEDE("\nDie Notiz lautet\n  \"","\nThe note reads\n  \"")
            LANGUAGEDE(noteD.text,noteE.text);
            printf("\"\n");
            alreadyread=1;
            globalwaittime=WAITTIME1;
            return 1;
        } // note

        if (
            (
                (mpp.contains_A("SPIEGEL") > 0) ||
                (mpp.contains_A("MIRROR") > 0)
            )

        ) {
            if (
                (mpp.contains_A("HINTER") > 0) ||
                (mpp.contains_A("BEHIND") > 0)
            ) {
                objecthidesnote=0;
            } else {
                LANGUAGEDE("*** Es scheint etwas dahinter herauszuschauen.","*** There's something sticking out from behind.");
                globalwaittime=WAITTIME1;
                return 1;
            }

            return 1;
        } // mirror

    } // look,schau,blick

    return 0;

}

mpRoom* mpPlayground::getCurrentRoomPtr(
    const int32_t acomp,
    const int32_t aroom
) {
    mpComponent* c=getComponentPtr(acomp);
    if (!c) return NULL;

    return c->getRoomPtr(aroom);
}

mpComponent* mpPlayground::getComponentPtr(const int32_t a) {
    if ( (a < 0) || (a >= companz) ) return NULL;

    return components[a];
}

double mpPlayground::getMultiplier_CR(
    const int32_t acomp,
    const int32_t aroom
) {
    // needs to be implemented
    mpRoom* R=getCurrentRoomPtr(acomp,aroom);
    if (!R) { printf("\nerror 35.\n"); exit(99); }

    return R->multiplier;

}

void mpPlayground::getDoors_T(DynSlowString& T) {
    T.setEmpty();
    mpComponent* c=getComponentPtr(hero.location_compid);
    if (!c) { printf("\nerror 6.\n"); exit(99); }
    mpRoom *R=c->getRoomPtr(hero.location_roomid);
    if (!R) { printf("\nerror 7.\n"); exit(99); }

    for(int32_t dir=MP_DIRECTION0;dir<=MP_DIRECTION1;dir++) {
        if (R->doors[dir].status == MP_DOOR_OPEN) {
            T.add("  ");
            if (language==MP_DEUTSCH) {
                T.add(mpDirectionStrD[dir][0]);
                T.add(" offen");
            } else {
                T.add(mpDirectionStrE[dir][0]);
                T.add(" open");
            }
        } else if (R->doors[dir].status == MP_DOOR_PARABOLIC_LOCKED) {
            T.add("  ");
            if (language==MP_DEUTSCH) {
                T.add(mpDirectionStrD[dir][0]);
                T.add(" parabolisch verschlossen");
            } else {
                T.add(mpDirectionStrE[dir][0]);
                T.add(" parabolic locked");
            }
        }

    } // dir

}

void mpPlayground::getCurrentLocation_T2(
    DynSlowString& T,
    DynSlowString& Tmult
) {
    T.setEmpty();
    Tmult.setEmpty();
    mpComponent* c=getComponentPtr(hero.location_compid);
    mpRoom* R=getCurrentRoomPtr(hero.location_compid,hero.location_roomid);
    if ( (!R) || (!c) ) { printf("\nerror 18.\n"); exit(99); }

    if (language == MP_DEUTSCH) {
        T.add("Raum Nr ");
        T.add_int(hero.location_roomid);
        T.add(" in Komponente Nr ");
        T.add_int(hero.location_compid);
        if (R->predHC > 0) T.add(" hyperbolisches Zentrum");
    } else {
        T.add("Room no ");
        T.add_int(hero.location_roomid);
        T.add(" in component no ");
        T.add_int(hero.location_compid);
        if (R->predHC > 0) T.add(" hyperbolic center");
    }

    if (hero.device_multiplierDetector == MP_DEVICEAUTOMATIC) {
        char tt[256];
        double m=getMultiplier_CR(hero.location_compid,hero.location_roomid);
        sprintf(tt,"%.5lg",m);
        Tmult.add("Multiplier=");
        Tmult.add(tt);
        Tmult.add("  ");
    }

    if (c->period_byhero > 0) {
        if (language == MP_DEUTSCH) Tmult.add("Periode "); else Tmult.add("period ");
        Tmult.add_int(c->period_byhero);
    }

}

int8_t mpRoom::saveGameState(FILE* f) {
    if (!f) return 0;

    WRITETYPE(int32_t,f,roomid)
    for(int32_t k=0;k<4;k++) {
        if (doors[k].saveGameState(f) <= 0) return 0;
    }
    WRITETYPE(uint8_t,f,predHC)
    WRITETYPE(int32_t,f,objectanz)
    WRITETYPE(double,f,multiplier)
    WRITETYPE(double,f,cReal)
    WRITETYPE(double,f,cImag)
    for(int32_t k=0;k<objectanz;k++) {
        if (objects[k]->saveGameState(f) <= 0) return 0;
    }

    return 1;

}

int8_t mpRoom::loadGameState(FILE* f) {
    // assumes the correct amount of memory has already been allocated
    if (!f) return 0;

    READTYPE(int32_t,f,roomid)
    for(int32_t k=0;k<4;k++) {
        if (doors[k].loadGameState(f) <= 0) return 0;
    }
    READTYPE(uint8_t,f,predHC)
    READTYPE(int32_t,f,objectanz)
    READTYPE(double,f,multiplier)
    READTYPE(double,f,cReal)
    READTYPE(double,f,cImag)
    for(int32_t k=0;k<objectanz;k++) {
        if (objects[k]->loadGameState(f) <= 0) return 0;
    }

    return 1;

}

int8_t mpRoom::parseCommand_ACR(
    mpParams& mpp,
    const int32_t loccomp,
    const int32_t locroom
) {
    // standard handler
    // doors: go, parabolic: enter period etc

    // GO N,S,W,E / GEH(E) N,S,W,E
    if (
        (mpp.paranz >= 2) &&
        (
            (strstr(mpp.params[0].text,"GO" )==mpp.params[0].text) ||
            (strstr(mpp.params[0].text,"GEH")==mpp.params[0].text)
        )
    ) {
        // akzeptziert werden:
        // GEHE NORDEN, GEHE N, GEHE NACH NORDEN, GEHE IN RICHTUNG N
        // und auch GEHE BLAHBLAH BLAHBLAH NTERT = GEH N
        int32_t dir=-1;

        if (language == MP_DEUTSCH) {
            for(int32_t k=MP_DIRECTION0;k<=MP_DIRECTION1;k++) {
                if (mpp.params[mpp.paranz-1].text[0] == mpDirectionStrD[k][0]) { dir=k; break; }
            }
        } else {
            for(int32_t k=MP_DIRECTION0;k<=MP_DIRECTION1;k++) {
                if (mpp.params[mpp.paranz-1].text[0] == mpDirectionStrE[k][0]) { dir=k; break; }
            }
        }

        if ( (dir < MP_DIRECTION0) || (dir > MP_DIRECTION1) ) {
            LANGUAGEDE("\n*** Unerlaubte Richtung.\n","\n*** Direction not available.\n")
            return 1; // success, command understood
        }

        // does a door exist ?
        if (doors[dir].status == MP_DOOR_NONE) {
            LANGUAGEDE("\n*** In dieser Richtung gibt es keinen Ausgang.\n","\n*** There is no exit in that direction.\n")
            return 1; // command understood
        }

        // an open door
        if (doors[dir].status == MP_DOOR_OPEN) {
            // change position of hero
            hero.location_compid=doors[dir].target_compid;
            hero.location_roomid=doors[dir].target_roomid;
            LANGUAGEDE("\n*** Ich gehe.\n","\n*** Going.\n")
            globalwaittime=0;
            return 1; // command understood
        }

        // a parabolic door: enter PIN
        if (doors[dir].status == MP_DOOR_PARABOLIC_LOCKED) {
            mpComponent* c=playground.getComponentPtr(loccomp);
            if (!c) { printf("\nerror 15.\n"); exit(99); }

            if (abracadabra > 0) {
                LANGUAGEDE("\n\n  Das magische Orakel meldet die korrekte Anwort: ","\n\nThe magic oracle tells the correct answer: ")
                printf("%i\n\n",c->period);
            }

            LANGUAGEDE("\nBitte gib die PIN zum Oeffnen ein: ","Please enter PIN to open door: ")
            char cmd[256];
            fgets(cmd,200,stdin);
            chomp(cmd);
            int32_t pin;
            int8_t correct=0;

            if (strlen(cmd) <= 0) pin=-1;
            else if (sscanf(cmd,"%i",&pin) != 1) pin=-1;

            if (pin == c->period) {
                if (c->period_byhero <= 0) {
                    c->period_byhero=c->period;
                } else if (c->period_byhero != c->period) {
                    printf("\nerror 37.\n"); exit(99);
                }

                // change location
                hero.location_compid=doors[dir].target_compid;
                hero.location_roomid=doors[dir].target_roomid;
                LANGUAGEDE("\nIch gehe.\n","\nGoing.\n")
                return 1; // command understood
            } else {
                LANGUAGEDE("\nFalsche PIN..\n","\nIncorrect PIN..\n")
                return 1;
            }

            return 1; // command understood
        }

    } // go command

    // now go over objects
    for(int32_t k=0;k<objectanz;k++) {
        int8_t ret=-1;
        if (objects[k]) ret=objects[k]->parseCommand_ACR(mpp,loccomp,locroom);
        if (ret > 0) return ret;
    } // k

    return 0; // not understood so far

}

mpRoom::mpRoom() {
    objectanz=0;
    objects=NULL;
    for(int32_t k=MP_DIRECTION0;k<=MP_DIRECTION1;k++) {
        doors[k].status=MP_DOOR_NONE;
    } // k
    predHC=0;
}

mpRoom::~mpRoom() {
    destroy();
}

void mpRoom::destroy(void) {
    if (objects) {
        for(int32_t k=0;k<objectanz;k++) delete objects[k];
        delete[] objects;
    }

    objects=NULL;
    objectanz=0;
}

void mpRoom::initObjects(const int32_t aanz) {
    destroy();

    objects=new PmpObject[aanz];
    MEMORY(objects,4);
    objectanz=aanz;
    for(int32_t k=0;k<objectanz;k++) objects[k]=NULL;

}

int8_t mpComponent::saveGameState(FILE* f) {
    if (!f) return 0;

    WRITETYPE(int32_t,f,compid)
    WRITETYPE(int32_t,f,roomanz)
    for(int32_t k=0;k<roomanz;k++) {
        if (rooms[k]->saveGameState(f) <= 0) return 0;
    }
    WRITETYPE(double,f,hcReal)
    WRITETYPE(double,f,hcImag)
    WRITETYPE(int32_t,f,period)
    WRITETYPE(int32_t,f,period_byhero)

    return 1;

}

int8_t mpComponent::loadGameState(FILE* f) {
    // assumes all memory has already been allocated and there is a valid
    // game state running
    if (!f) return 0;

    READTYPE(int32_t,f,compid)
    READTYPE(int32_t,f,roomanz)
    for(int32_t k=0;k<roomanz;k++) {
        if (rooms[k]->loadGameState(f) <= 0) return 0;
    }
    READTYPE(double,f,hcReal)
    READTYPE(double,f,hcImag)
    READTYPE(int32_t,f,period)
    READTYPE(int32_t,f,period_byhero)

    return 1;

}

int8_t mpComponent::parseCommand_ACR(
    mpParams& mpp,
    const int32_t loccomp,
    const int32_t locroom
) {
    // give to room
    mpRoom* R=getRoomPtr(locroom);
    if (!R) { printf("\nerror 14.\n"); exit(99); }

    int8_t result=R->parseCommand_ACR(mpp,loccomp,locroom);
    if (result > 0) return result;

    // special handling?
    // currently: none

    return 0; // command not understood

}

mpRoom* mpComponent::getRoomPtr(const int32_t a) {
    if ( (a < 0) || (a >= roomanz) ) return NULL;

    return rooms[a];
}

mpComponent::mpComponent() {
    roomanz=0;
    rooms=NULL;
    period_byhero=0;
}

mpComponent::~mpComponent() {
    destroy();
}

void mpComponent::destroy(void) {
    // rooms themselves will be destroyed externally (or not)
    if (rooms) {
        for(int32_t k=0;k<roomanz;k++) delete rooms[k];
        delete[] rooms;
    }

    rooms=NULL;
    roomanz=0;
}

void mpComponent::initRooms(const int32_t aanz) {
    destroy();

    rooms=new PmpRoom[aanz];
    MEMORY(rooms,3)
    roomanz=aanz;
    for(int32_t k=0;k<roomanz;k++) rooms[k]=NULL;

}

mpPlayground::mpPlayground() {
    companz=0;
    components=NULL;
}

mpPlayground::~mpPlayground() {
    destroy();
}

void mpPlayground::destroy(void) {
    // components themselves will be destroyed externally (or not)
    if (components) {
        for(int32_t k=0;k<companz;k++) delete components[k];
        delete[] components;
    }

    components=NULL;
    companz=0;
}

mpObjPrisonCell* createPrisonCell_I(const int32_t aidd) {
    mpObjPrisonCell* o=new mpObjPrisonCell;
    MEMORY(o,22)
    o->objid=aidd;
    o->imprisoned=1;

    return o;
}

mpQuestionMultipleChoice* createQuestionMultipleChoice_QQC0123(
    const char *qd,
    const char *qe,
    const int32_t acorrect,
    const char* mc0,
    const char* mc1,
    const char* mc2,
    const char* mc3
) {
    mpQuestionMultipleChoice *q=new mpQuestionMultipleChoice;
    MEMORY(q,40)

    q->mchoice_correct=acorrect;
    q->questionD.setEmpty(); q->questionD.add(qd);
    q->questionE.setEmpty(); q->questionE.add(qe);
    q->mchoice[0].setEmpty(); q->mchoice[0].add(mc0);
    q->mchoice[1].setEmpty(); q->mchoice[1].add(mc1);
    q->mchoice[2].setEmpty(); q->mchoice[2].add(mc2);
    q->mchoice[3].setEmpty(); q->mchoice[3].add(mc3);

    return q;

}

mpObjCaseDevicePart* createCaseDevice_multiplechoice_INQQC0123(
    const int32_t aidd,
    const int32_t apart, // 1 to 3
    const char *qd,
    const char *qe,
    const int32_t acorrect,
    const char* mc0,
    const char* mc1,
    const char* mc2,
    const char* mc3
) {
    mpObjCaseDevicePart* o=new mpObjCaseDevicePart;
    MEMORY(o,32)

    o->objid=aidd;
    o->partnumber=apart;
    o->locked=1;
    o->qa=createQuestionMultipleChoice_QQC0123(qd,qe,acorrect,mc0,mc1,mc2,mc3);

    return o;
}

mpQuestionQA* createQuestionQA_QQAA(
    const char *qd,
    const char *qe,
    const char *ad,
    const char *ae
) {
    mpQuestionQA *q=new mpQuestionQA;
    MEMORY(q,41)

    q->questionD.setEmpty(); q->questionD.add(qd);
    q->questionE.setEmpty(); q->questionE.add(qe);
    q->answerD.setEmpty(); q->answerD.add(ad);
    q->answerE.setEmpty(); q->answerE.add(ae);

    return q;

}

mpObjCaseDevicePart* createCaseDevice_INQQAA(
    const int32_t aidd,
    const int32_t apart,
    const char *qd,
    const char *qe,
    const char *ad,
    const char *ae
) {
    mpObjCaseDevicePart* o=new mpObjCaseDevicePart;
    MEMORY(o,28)

    o->objid=aidd;
    o->partnumber=apart;
    o->locked=1;
    o->qa=createQuestionQA_QQAA(qd,qe,ad,ae);

    return o;
}

mpObjCaseDevicePart* createCaseDevice_open_IN(
    const int32_t aidd,
    const int32_t apart
) {
    mpObjCaseDevicePart* o=new mpObjCaseDevicePart;
    MEMORY(o,28)

    o->objid=aidd;
    o->partnumber=apart;
    o->locked=0;
    o->qa=NULL;

    return o;
}

mpObjNoteInCase* createNoteInCase_IQDE(
    const int32_t aidd,
    mpQuestion* aquestion,
    const char* anoteD,
    const char* anoteE
) {
    mpObjNoteInCase* o=new mpObjNoteInCase;
    MEMORY(o,45)

    o->locked=1;
    o->qa=aquestion;
    o->noteD.setEmpty(); o->noteD.add(anoteD);
    o->noteE.setEmpty(); o->noteE.add(anoteE);

    return o;

}

mpObjFloorNote* createFloorNote_IDE(
    const int32_t aidd,
    const char* anoteD,
    const char* anoteE
) {
    mpObjFloorNote *o=new mpObjFloorNote;
    MEMORY(o,24)

    o->alreadyread=0;
    o->objid=aidd;
    o->noteD.setEmpty();
    o->noteE.setEmpty();
    o->noteD.add(anoteD);
    o->noteE.add(anoteE);

    return o;

}

mpObjNoteBehindMirror* createNoteBehindMirror_IDE(
    const int32_t aidd,
    const char* anoteD,
    const char* anoteE
) {
    mpObjNoteBehindMirror *o=new mpObjNoteBehindMirror;
    MEMORY(o,43)

    o->objid=aidd;
    o->alreadyread=0;
    o->objecthidesnote=1;
    o->noteD.setEmpty();
    o->noteE.setEmpty();
    o->noteD.add(anoteD);
    o->noteE.add(anoteE);

    return o;

}

mpObjTransmitter* createTransmitter_IDD(
    const int32_t aidd,
    const int32_t atgtcompid,
    const int32_t atgtroomid
) {
    mpObjTransmitter* o=new mpObjTransmitter;
    MEMORY(o,21)

    o->objid=aidd;
    o->target_compid=atgtcompid;
    o->target_roomid=atgtroomid;

    return o;
}

mpComponent* createComponent5(void) {
	mpComponent* mpc=new mpComponent;
	if (!mpc) return NULL;

	// component 5, period-16 attached north of period-4 in period-doubling on x-axis

	mpc->hcReal=-1.3125026413368328093;
	mpc->hcImag=0.062600000000000002864;
	mpc->period=16;

	mpRoom* R;

	mpc->initRooms(2);

	// room 5.0
	R=new mpRoom; MEMORY(R,10) R->roomid=0;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,5,1)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_PARABOLIC_LOCKED,2,7)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.3124088913368328058;
	R->cImag=0.059209375000000008527;
	R->multiplier=0.84301447533033646575;
	mpc->rooms[R->roomid]=R;

	// room 5.1
	R=new mpRoom; MEMORY(R,10) R->roomid=1;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,5,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=1;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.3123307663368328768;
	R->cImag=0.06278750000000000997;
	R->multiplier=0.0057046576785409466512;
	R->initObjects(2);
	int32_t oc=0;
	R->objects[oc]=createTransmitter_IDD(oc,1,0);
	oc++;
	R->objects[oc]=createFloorNote_IDE(oc,
        "Die Periode ist 16.",
        "The periodicity is 16."
    );
    oc++;
	mpc->rooms[R->roomid]=R;

	return mpc;
}

void mpPlayground::initComponents(const int32_t aanz) {
    destroy();

    components=new PmpComponent[aanz];
    companz=aanz;
    for(int32_t k=0;k<companz;k++) components[k]=NULL;

}

// routines
mpComponent* createComponent7(void) {
	mpComponent* mpc=new mpComponent;
	if (!mpc) return NULL;

	// component 7, period 15 attached to period 5 attachoed to main cardioid

	mpc->hcReal=-0.54737499999999994493;
	mpc->hcImag=0.55781249999999993339;
	mpc->period=15;

	mpRoom* R;

	mpc->initRooms(7);

	// room 7.0
	R=new mpRoom; MEMORY(R,10) R->roomid=0;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,7,2)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,7,1)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.54753437499999990656;
	R->cImag=0.55679062499999998348;
	R->multiplier=0.065867314151509703812;

	R->initObjects(1);
	int32_t oc=0;
	R->objects[oc]=createNoteBehindMirror_IDE(oc,
        "Die Komponente hat nur genau eine parabolische Tuer.",
        "This component only harbours one parabolic door."
    );
	oc++;

	mpc->rooms[R->roomid]=R;

	// room 7.1
	R=new mpRoom; MEMORY(R,10) R->roomid=1;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,7,4)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,7,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.54536874999999995772;
	R->cImag=0.55676249999999993801;
	R->multiplier=0.27555550567993847277;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createNoteInCase_IQDE(oc,
        createQuestionMultipleChoice_QQC0123(
            "Wann erschien Mandelbrots erste Veroeffentlichung\nueber die nach ihm benannte Menge?",
            "In which year did Mandelbrot publish for the first\ntime about his set?",
            1,
            "1976",
            "1980",
            "1986",
            "1990"
        ),
        "Die aktuelle Periode ist 15.",
        "The current periodicty is 15."
    );
    oc++;

	mpc->rooms[R->roomid]=R;

	// room 7.2
	R=new mpRoom; MEMORY(R,10) R->roomid=2;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,7,3)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,7,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=1;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.54751562499999995026;
	R->cImag=0.55765312499999997176;
	R->multiplier=0.0046401813261634306321;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createTransmitter_IDD(oc,8,7);
	oc++;

	mpc->rooms[R->roomid]=R;

	// room 7.3
	R=new mpRoom; MEMORY(R,10) R->roomid=3;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,7,2)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,7,4)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.54747812499999992664;
	R->cImag=0.55808437499999996589;
	R->multiplier=0.0051677845551228685991;
	mpc->rooms[R->roomid]=R;

	// room 7.4
	R=new mpRoom; MEMORY(R,10) R->roomid=4;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,7,6)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,7,1)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,7,3)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,7,5)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.54538749999999991402;
	R->cImag=0.55809374999999994404;
	R->multiplier=0.2043749557153390628;
	mpc->rooms[R->roomid]=R;

	// room 7.5
	R=new mpRoom; MEMORY(R,10) R->roomid=5;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,7,4)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_PARABOLIC_LOCKED,6,3)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.54319374999999991971;
	R->cImag=0.5581031249999999222;
	R->multiplier=0.92437715427339472996;
	mpc->rooms[R->roomid]=R;

	// room 7.6
	R=new mpRoom; MEMORY(R,10) R->roomid=6;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,7,4)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.54538749999999991402;
	R->cImag=0.55979062499999987512;
	R->multiplier=0.39743566019407611245;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createFloorNote_IDE(
        oc,
        "die Ziffer '1', die durchgestrichen ist",
        "digit '1' with strikethrough"
	);
	oc++;

	mpc->rooms[R->roomid]=R;


	return mpc;
}

mpObjDeviceUnderCarpet* createDeviceUnderTable_IN(
    const int32_t aidd,
    const int32_t apartnumber

) {
    mpObjDeviceUnderCarpet* o=new mpObjDeviceUnderCarpet;
    MEMORY(o,50)

    o->hidden=1;
    o->partnumber=apartnumber;
    o->objid=aidd;

    return o;

}

mpComponent* createComponent9(void) {
	mpComponent* mpc=new mpComponent;
	if (!mpc) return NULL;

	// component 9, period 105 to 15 attached to period 5 attachoed to main cardioid

	mpc->hcReal=-0.49075562499999997312;
	mpc->hcImag=0.60132299999999994089;
	mpc->period=105;

	mpRoom* R;

	mpc->initRooms(10);

	// room 9.0
	R=new mpRoom; MEMORY(R,10) R->roomid=0;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,9,3)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.4907235624999999879;
	R->cImag=0.60130668749999993672;
	R->multiplier=0.15309392065413379713;

	R->initObjects(1);
	int32_t oc=0;
	R->objects[oc]=createNoteInCase_IQDE(oc,
        createQuestionQA_QQAA(
            "Welches ist die kleinste Periode p, die 1 Million oder mehr\nhyperbolische Komponenten mit genau dieser Periodizitaet aufweist?",
            "Which is the smallest period p that allows for 1 million or more\nhyperbolic compoennts of that exact period?",
            "21",
            "21"
        ),
        "Die aktuelle Periode ist 105.",
        "Current component's period is 105."
    );
	oc++;

	mpc->rooms[R->roomid]=R;

	// room 9.1
	R=new mpRoom; MEMORY(R,10) R->roomid=1;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,9,6)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,9,2)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.49080774999999998709;
	R->cImag=0.60132674999999990995;
	R->multiplier=0.31493797536086715061;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createFloorNote_IDE(oc,"Die beiden höchstwertigsten Ziffern der Periode sind durch\n   die Buchstaben 'J' auf einfache Art kodiert.",
        "The two leftmost digits of the current periodicity\n   were encoded in a simple cipher by the letter 'J'-");
	oc++;

	mpc->rooms[R->roomid]=R;

	// room 9.2
	R=new mpRoom; MEMORY(R,10) R->roomid=2;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,9,1)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,9,3)
	R->predHC=1;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.49075131249999998095;
	R->cImag=0.60132712499999996236;
	R->multiplier=0.0039898909788742198054;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createDeviceUnderTable_IN(oc,3);
	oc++;

	mpc->rooms[R->roomid]=R;

	// room 9.3
	R=new mpRoom; MEMORY(R,10) R->roomid=3;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,9,4)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,9,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,9,2)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.4907241249999999555;
	R->cImag=0.60132656249999993925;
	R->multiplier=0.1157442476045252161;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createNoteBehindMirror_IDE(oc,"Die niedrigstwertige Stelle ist kodiert in einer einfachen Verschluesselung als Buchstabe 'E'.","The rightmost digit of the period was encoded in a simple by letter 'E'.");
	oc++;

	mpc->rooms[R->roomid]=R;

	// room 9.4
	R=new mpRoom; MEMORY(R,10) R->roomid=4;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,9,3)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,9,5)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.4907235624999999879;
	R->cImag=0.60134493749999995416;
	R->multiplier=0.16999000430788771543;
	mpc->rooms[R->roomid]=R;

	// room 9.5
	R=new mpRoom; MEMORY(R,10) R->roomid=5;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,9,4)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_PARABOLIC_LOCKED,8,3)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.49067312499999998776;
	R->cImag=0.60134531249999989555;
	R->multiplier=0.8291525112768551864;
	mpc->rooms[R->roomid]=R;

	// room 9.6
	R=new mpRoom; MEMORY(R,10) R->roomid=6;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,9,8)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,9,1)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,9,7)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.49080831249999995469;
	R->cImag=0.60137268749999994721;
	R->multiplier=0.56857359173529187224;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createFloorNote_IDE(oc,"Die aktuelle Periode ist 3-stellig.","Current periodicity has 3 digits.");
	oc++;

	mpc->rooms[R->roomid]=R;

	// room 9.7
	R=new mpRoom; MEMORY(R,10) R->roomid=7;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,9,9)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,9,6)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.49079931249999997345;
	R->cImag=0.60137249999999997652;
	R->multiplier=0.4728769511318638985;
	mpc->rooms[R->roomid]=R;

	// room 9.8
	R=new mpRoom; MEMORY(R,10) R->roomid=8;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,9,6)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,9,9)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.49080756249999996088;
	R->cImag=0.60138337499999994229;
	R->multiplier=0.67784748983187215199;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createCaseDevice_multiplechoice_INQQC0123(oc,1,
        "Wo hat Benoit Mandelbrat viele Jahre gearbeitet?",
        "Benoit Mandelbrot worked for many years at:",
        0,
        "International Business Machines Corporation",
        "Advanced Micro Devices",
        "Federal Reserve Bank",
        "Dornier"
	);
	oc++;

	mpc->rooms[R->roomid]=R;

	// room 9.9
	R=new mpRoom; MEMORY(R,10) R->roomid=9;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,9,7)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,9,8)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.49079818749999998273;
	R->cImag=0.60138337499999994229;
	R->multiplier=0.58352721052286204984;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createCaseDevice_multiplechoice_INQQC0123(oc,2,
        "Die c-Parameter-Menge fuer z^d+c hat als Limit fuer d->inf\nwelches mathematische Objekt?",
        "The c-parameter space for z^d+c limits for d->inf to which\nmathematical object?",
        3,
        "{c | c in C, ||Re(c)|| < 1 and ||Im(c)|| <= 1}",
        "{c | c in C, ||c+3/4|| <= 1}",
        "{c | c in C, ||c|| < 1}",
        "{c | c in C, ||c|| <= 1}"
	);
	oc++;

	mpc->rooms[R->roomid]=R;



	return mpc;
}

mpComponent* createComponent8(void) {
	mpComponent* mpc=new mpComponent;
	if (!mpc) return NULL;

	// component 8, period 15 attached to period 5 attachoed to main cardioid

	mpc->hcReal=-0.48624999999999996003;
	mpc->hcImag=0.60206249999999994493;
	mpc->period=15;

	mpRoom* R;

	mpc->initRooms(8);

	// room 8.0
	R=new mpRoom; MEMORY(R,10) R->roomid=0;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,8,1)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.48838749999999997442;
	R->cImag=0.5984718749999999865;
	R->multiplier=0.95036629176924503071;
	mpc->rooms[R->roomid]=R;

	// room 8.1
	R=new mpRoom; MEMORY(R,10) R->roomid=1;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,8,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,8,2)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.48838749999999997442;
	R->cImag=0.60088124999999992237;
	R->multiplier=0.31411229617526675861;

	R->initObjects(1);
	int32_t oc=0;
	R->objects[oc]=createNoteInCase_IQDE(oc,
        createQuestionQA_QQAA(
            "Wieviele Cardioide besitzen  die Perioden 1-5 insgesamt?",
            "How many cardioids are there with periods 1-5?",
            "15",
            "15"
        ),
        "Diese Komponente hat exakt eine parabolische Tuer.",
        "This component harbours exactly one parabolic door."
	);
	oc++;

	mpc->rooms[R->roomid]=R;

	// room 8.2
	R=new mpRoom; MEMORY(R,10) R->roomid=2;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,8,6)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,8,1)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.48647499999999993525;
	R->cImag=0.6008343749999999206;
	R->multiplier=0.093982438568528489653;
	mpc->rooms[R->roomid]=R;

	// room 8.3
	R=new mpRoom; MEMORY(R,10) R->roomid=3;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_PARABOLIC_LOCKED,9,5)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,8,4)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.49044062499999996341;
	R->cImag=0.60134999999999994014;
	R->multiplier=0.90663475105110880037;
	mpc->rooms[R->roomid]=R;

	// room 8.4
	R=new mpRoom; MEMORY(R,10) R->roomid=4;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,8,5)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,8,3)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.48743124999999998259;
	R->cImag=0.60130312499999993836;
	R->multiplier=0.10566280030402028234;
	mpc->rooms[R->roomid]=R;

	// room 8.5
	R=new mpRoom; MEMORY(R,10) R->roomid=5;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,8,4)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,8,6)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.48744062499999996074;
	R->cImag=0.60225937499999993019;
	R->multiplier=0.070788590482865690334;
	mpc->rooms[R->roomid]=R;

	// room 8.6
	R=new mpRoom; MEMORY(R,10) R->roomid=6;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,8,2)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,8,5)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,8,7)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.48654062499999994884;
	R->cImag=0.60228749999999997566;
	R->multiplier=0.0044859706410477597285;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createFloorNote_IDE(oc,
        "Diese Komponente liegt vollstaendig in der\n   positiv-imaginaeren komplexen Ebenenhaelfte.",
        "The component resides entirely in the positive\n   imaginary part of the complex plane."
    );
	oc++;

	mpc->rooms[R->roomid]=R;

	// room 8.7
	R=new mpRoom; MEMORY(R,10) R->roomid=7;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,8,6)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=1;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.486006249999999973;
	R->cImag=0.60229687499999995381;
	R->multiplier=0.0065632141219706969376;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createTransmitter_IDD(oc,7,0);
	oc++;

	mpc->rooms[R->roomid]=R;

	return mpc;
}

mpComponent* createComponent0(void) {
	mpComponent* mpc=new mpComponent;
	if (!mpc) return NULL;

	// component 0, period-doubling 8 on x-axis

	mpc->hcReal=-1.3815474844320614345;
	mpc->hcImag=0;
	mpc->period=8;

	mpRoom* R;

	mpc->initRooms(6);

	// room 0
	R=new mpRoom; MEMORY(R,10) R->roomid=0;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,0,2)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.3839693594320614523;
	R->cImag=-0.0025781250000000005551;
	R->multiplier=0.075618331050231427093;

	R->initObjects(1);
	int32_t oc=0;
	R->objects[oc]=createCaseDevice_multiplechoice_INQQC0123(oc,3,
	/*
        Quasiconformal homeomorphisms and dynamics I. Solution of the Fatou-Julia problem
        on wandering domains

        Theorem A, referencing Dennis Sullivan
	*/
        "Wer bewies das No-Wandering-Theorem fuer rationale Funktionen?",
        "Who proved the no-wandering theorem for rational functions?",
        2,
        "Pierre Fatou", // 0
        "Leonhard Euler", // 1
        "Dennis Sullivan", // 2
        "Gaston Julia" // 3
	); //
	oc++;

	mpc->rooms[R->roomid]=R;

	// room 1
	R=new mpRoom; MEMORY(R,10) R->roomid=1;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_PARABOLIC_LOCKED,1,1)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,0,2)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.3936568594320613013;
	R->cImag=0.00039062499999999861222;
	R->multiplier=0.93755569033625207886;

	mpc->rooms[R->roomid]=R;

	// room 2
	R=new mpRoom; MEMORY(R,10) R->roomid=2;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,0,1)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,0,3)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.3838131094320613723;
	R->cImag=0.00031250000000000027756;
	R->multiplier=0.031584914521908417917;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createCaseDevice_open_IN(oc,1); // already open
	oc++;

	mpc->rooms[R->roomid]=R;

	// room 0.3
	R=new mpRoom; MEMORY(R,10) R->roomid=3;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,0,5)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,0,2)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,0,4)
	R->predHC=1;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.3802974844320614611;
	R->cImag=0.0011718749999999993061;
	R->multiplier=0.01737825765783148485;

	R->initObjects(2);
	oc=0;
	R->objects[oc]=createTransmitter_IDD(oc,-1,-1); // inactivbe
	oc++;
	R->objects[oc]=createCaseDevice_INQQAA(oc,2,
        "Wieviele anziehende unterschiedliche Zyklen hat die\nJuliamenge z^3+(-1.1057+i*0.6074)*z^2+(0.7111-1.1915*i) ?",
        "How many distinct attracting cycles does the Julia set to\nz^3+(-1.1057+i*0.6074)*z^2+(0.7111-1.1915*i) own?",
        "1",
        "1");
	oc++;
	mpc->rooms[R->roomid]=R;

	// room 4
	R=new mpRoom; MEMORY(R,10) R->roomid=4;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,0,3)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_PARABOLIC_LOCKED,2,2)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.3685787344320614611;
	R->cImag=0.00039062499999999861222;
	R->multiplier=0.93324240842205108404;
	mpc->rooms[R->roomid]=R;

	// room 5
	R=new mpRoom; MEMORY(R,10) R->roomid=5;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,0,3)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.3810006094320614878;
	R->cImag=0.0028906250000000008327;
	R->multiplier=0.051433941297953277016;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createFloorNote_IDE(oc,
        "Die aktuelle Periodizitaet ist die Haelfte der Summe der vier Ziffern\n   des Geburtsjahres von Benoit Mandelbrot.",
        "Current component's periodicity equals half the sum of the four digits\n   of Benoit Mandelbrot's year of birth."
    );
	oc++;
	mpc->rooms[R->roomid]=R;

	return mpc;
}

mpComponent* createComponent10(void) {
	mpComponent* mpc=new mpComponent;
	if (!mpc) return NULL;

	// component 10, period 3-cardioid

	mpc->hcReal=-1.7548776662466927245;
	mpc->hcImag=0;
	mpc->period=3;

	mpRoom* R;

	mpc->initRooms(5);

	// room 10.0
	R=new mpRoom; MEMORY(R,10) R->roomid=0;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,10,2)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7572067678091927156;
	R->cImag=-0.0079833984375000006939;
	R->multiplier=0.5254485975703485634;
	mpc->rooms[R->roomid]=R;

	// room 10.1
	R=new mpRoom; MEMORY(R,10) R->roomid=1;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,10,3)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_PARABOLIC_LOCKED,12,3)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,10,2)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7679880178091926801;
	R->cImag=-0.0025488281249999994449;
	R->multiplier=0.96923752628848225399;
	int32_t oc=0;
	R->initObjects(1);
	R->objects[oc]=createNoteInCase_IQDE(oc,
        createQuestionMultipleChoice_QQC0123(
            "Der Algorithmus von Figueiredo et al zum Berechnen von mathematisch korrekten Obermengen zu polynomiellen Juliamengen\nzeichnet sich durch eine Schluesseleigenschaft aus. Welche?",
            "The algorithm by Figueiredo et al to draw a superset of the filled-in Julia set\n   of a polynomial owns a key feature, which is ...",
            0,
            "cell-mapping with 1-iterate",
            "tremendously high precision",
            "a time complexiy of sub-linear",
            "highly parallelized"
        ),
        "Die aktuelle Periode ist 3.",
        "Current component's period equals 3."
    );
	oc++;
	mpc->rooms[R->roomid]=R;

	// room 10.2
	R=new mpRoom; MEMORY(R,10) R->roomid=2;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,10,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,10,1)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7572067678091927156;
	R->cImag=-0.0025341796875000006245;
	R->multiplier=0.10525149121100546568;
	mpc->rooms[R->roomid]=R;

	// room 10.3
	R=new mpRoom; MEMORY(R,10) R->roomid=3;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,10,1)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_PARABOLIC_LOCKED,11,4)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,10,4)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7681198537466926712;
	R->cImag=8.7890624999999861222e-05;
	R->multiplier=0.95365167947938767057;
	mpc->rooms[R->roomid]=R;

	// room 10.4
	R=new mpRoom; MEMORY(R,10) R->roomid=4;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,10,3)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=1;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7547897756216928045;
	R->cImag=4.3945312499999930611e-05;
	R->multiplier=0.00010750941401047011596;
	oc=0;
	R->initObjects(1);
	R->objects[oc]=createNoteBehindMirror_IDE(oc,
        "Der Manhattan-Abstand dieses Raumes zum Zentrum des\n   Hauptkardioids is ungefaehr 1.75483",
        "The Manhattan distance from this room to the center\n   of the main cardioid is approximately 1.75483"
	);
	oc++;
	mpc->rooms[R->roomid]=R;


	return mpc;
}

mpComponent* createComponent11(void) {
	mpComponent* mpc=new mpComponent;
	if (!mpc) return NULL;

	// component 11, period 6 attached period 3-cardioid

	mpc->hcReal=-1.7728952443716927689;
	mpc->hcImag=0;
	mpc->period=6;

	mpRoom* R;

	mpc->initRooms(5);

	// room 11.0
	R=new mpRoom; MEMORY(R,10) R->roomid=0;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_PARABOLIC_LOCKED,14,6)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,11,1)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7754587209341927689;
	R->cImag=-0.0033105468749999996877;
	R->multiplier=0.93319475016589614746;
	mpc->rooms[R->roomid]=R;

	// room 11.1
	R=new mpRoom; MEMORY(R,10) R->roomid=1;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,11,3)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,11,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,11,2)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7728366506216928222;
	R->cImag=-0.0032812499999999994449;
	R->multiplier=0.57011181149375933508;
	mpc->rooms[R->roomid]=R;

	// room 11.2
	R=new mpRoom; MEMORY(R,10) R->roomid=2;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,11,1)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7721994435904426801;
	R->cImag=-0.0032958984375;
	R->multiplier=0.59979146946064465507;
	mpc->rooms[R->roomid]=R;

	// room 11.3
	R=new mpRoom; MEMORY(R,10) R->roomid=3;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,11,1)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,11,4)
	R->predHC=1;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7728732717154427334;
	R->cImag=2.1972656249999965306e-05;
	R->multiplier=4.5962279825605291796e-05;
	int32_t oc=0;
	R->initObjects(2);
	R->objects[oc]=createNoteBehindMirror_IDE(oc,
        "Der Manhattan-Abstand dieses Raumes zum Zentrum des\n   Hauptkardioids is ungefaehr 1.772895",
        "The Manhattan distance from this room to the center\n   of the main cardioid is approximately 1.772895"
	);
	oc++;
	R->objects[oc]=createTransmitter_IDD(oc,-1,-1);
	oc++;
	mpc->rooms[R->roomid]=R;

	// room 11.4
	R=new mpRoom; MEMORY(R,10) R->roomid=4;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,11,3)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_PARABOLIC_LOCKED,10,3)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7686325490591927601;
	R->cImag=4.3945312499999930611e-05;
	R->multiplier=0.95345707449262206978;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createNoteInCase_IQDE(oc,
        createQuestionMultipleChoice_QQC0123(
            "f(z)=z^3+(-0.5-1.875*i)*z^2+(-2+0.875*i)*z+(0.75+i) hat zwei anziehende Zyklen:\nLaenge 16 und 17. Was passiert mit den Zyklen, wenn man die 2-Komposition G(z) := f(f(z)) betrachtet?",
            "f(z)=z^3+(-0.5-1.875*i)*z^2+(-2+0.875*i)*z+(0.75+i) harbours two attracting cycles:\nlength 16 and 17. What happens to the cycles if one considers the 2-iterate G(z) := f(f(z))?",
            3,
            "the cycles in G stay the same as in f",
            "the critical points of f swap the cycle they enter in G",
            "the odd cycle doubles its length and the even cycle remains unchanged in G",
            "the odd cycle remains unchanged, the even cycle splits into two cycles\n      of half the length in G"
        ),
        "Die Periode der aktuellen Komponente ist 6.",
        "Current component's period equals 6."
	);
	oc++;
	mpc->rooms[R->roomid]=R;


	return mpc;
}

mpComponent* createComponent12(void) {
	mpComponent* mpc=new mpComponent;
	if (!mpc) return NULL;

	// component 12, period 63 at period 6 attached period 3-cardioid

	mpc->hcReal=-1.7682956349966927334;
	mpc->hcImag=-0.0026074218749999999306;
	mpc->period=63;

	mpRoom* R;

	mpc->initRooms(4);

	// room 12.0
	R=new mpRoom; MEMORY(R,10) R->roomid=0;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,12,1)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7683016818716927876;
	R->cImag=-0.0026248593750000000224;
	R->multiplier=0.19282781669008711156;
	mpc->rooms[R->roomid]=R;

	// room 12.1
	R=new mpRoom; MEMORY(R,10) R->roomid=1;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,12,2)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,12,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7682904318716927694;
	R->cImag=-0.0026248593750000000224;
	R->multiplier=0.16523013374865055947;
	int32_t oc=0;
	R->initObjects(1);
	// Zakeri Sm Biaccessibility in quadratic Julia sets II: The Siegel and Cremer case
	R->objects[oc]=createNoteInCase_IQDE(oc,
        createQuestionMultipleChoice_QQC0123(
            "f(z)=z^2+z*e^(2*PI*i*A) hat einen indifferenten Fixpunkt an z=0. Welche der folgenden Mengen\nbzgl. A ist die groesste (im Sinne von echter Obermenge),\nbei der eine Siegel-Disk entsteht?",
            "f(z)=z^2+z*e^(2*PI*i*A) has an indifferent fix point at z=0.\nWhich set below with respect to the value A is the largest (in the sense of strict superset),\nthat allows the existence of a Siegel disk?",
            3,
            "Q+ (positive rational numbers)",
            "R-Q (all strictly irrational numbers)",
            "CT (strictly irrational numbers of constant type continued fraction expansion)",
            "Brjuno set (strictly irrational numbers fulfilling the Brjuno condition sum[log(q_(n+1))/q_n] < inf\n      with q_n being the denominator of the n-th rational approximation"
        ),
        "In dieser Komponente gibt es keinen Hinweis auf die Periodizitaet.",
        "This component does not hide a clue to its periodicity."
    );
	oc++;
	mpc->rooms[R->roomid]=R;

	// room 12.2
	R=new mpRoom; MEMORY(R,10) R->roomid=2;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,12,1)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,12,3)
	R->predHC=1;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7682947912466926432;
	R->cImag=-0.0026065781249999999541;
	oc=0;
	R->initObjects(1);
	R->objects[oc]=createTransmitter_IDD(oc,13,5);
	oc++;
	R->multiplier=0.0014746549755761135386;

	mpc->rooms[R->roomid]=R;

	// room 12.3
	R=new mpRoom; MEMORY(R,10) R->roomid=3;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,12,2)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_PARABOLIC_LOCKED,10,1)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7682578068716927611;
	R->cImag=-0.0026061562499999999659;
	R->multiplier=0.75637664652769553975;
	oc=0;
	R->initObjects(1);
	R->objects[oc]=createFloorNote_IDE(oc,
        "Der euklidische Abstand dieses Zimmers zu Benoits Telle betraegt circa 1.76826",
        "The Euclidean distance to Benoit's cell is approx. 1.76826"
	);
	oc++;
	mpc->rooms[R->roomid]=R;


	return mpc;
}

mpComponent* createComponent14(void) {
	mpComponent* mpc=new mpComponent;
	if (!mpc) return NULL;

	// component 14, period 84 at period-6 near 3-cardioid

	mpc->hcReal=-1.7756203224966926602;
	mpc->hcImag=-0.0033990624999999997403;
	mpc->period=84;

	mpRoom* R;

	mpc->initRooms(7);

	// room 14.0
	R=new mpRoom; MEMORY(R,10) R->roomid=0;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,14,5)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,14,1)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7756334474966926074;
	R->cImag=-0.0034081249999999996964;
	R->multiplier=0.41368132233565924061;
	int32_t oc=0;
	R->initObjects(1);

	// createCaseDevice_multiplechoice_INQQC0123(
	// createCaseDevice_INQQAA(
	R->objects[oc]=createCaseDevice_multiplechoice_INQQC0123(oc,1,
        "  Wenn N(d) die Anzahl der Iterationen darstellt, die z_(n+1)=(z_n)^2+c fuer z0=0 und c=0.25+d fuer positive\n  d benoetigt, damit ||z_n|| > 2 wird. Existiert lim (d->0) sqrt(d)*N(d) und wenn, was stellt er dar?",
        "Let N(d) denote the number of iterations the point z0=0 needs under z_(n+1)=(z_n)^2+c for c=0.25+d \nand positive d until ||z_n|| exceeds 2.\nDoes lim (d->0) sqrt(d)*N(d) exist, and if so, what does it value to?",
        2,
        "no limit exists",
        "the area of the Mandelbrot set",
        "pi",
        "Euler's constant divided by pi"
    );
	oc++;

	mpc->rooms[R->roomid]=R;

	// room 14.1
	R=new mpRoom; MEMORY(R,10) R->roomid=1;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,14,4)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,14,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7756139162466926251;
	R->cImag=-0.0034086718749999998096;
	R->multiplier=0.23608848953480768285;

	oc=0;
	R->initObjects(1);
	R->objects[oc]=createCaseDevice_multiplechoice_INQQC0123(oc,2,
        "Was, neben der Menge, wurde nach Benoit Mandelbrot benannt?",
        "What, besides the famous set, has been named after Benoit Mandelbrot?",
        1,
        "Subway station",
        "Asteroid",
        "Beetle specias",
        "Computer chip layout"
	);
	oc++;
	mpc->rooms[R->roomid]=R;

	// room 14.2
	R=new mpRoom; MEMORY(R,10) R->roomid=2;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,14,3)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=1;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7756216506216926376;
	R->cImag=-0.0034004687499999998457;
	R->multiplier=0.0058012683877333333371;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createFloorNote_IDE(oc,
        "Die Periodizitaet dieser Komponenten sei P (<100). Dann gibt es\n   insgesamt 9671406556914834240182310 Komponenten mit dieser Periodizitaet in z^2+c.",
        "Let P (<100) be the periodicity of the current component. Then there are a total of\n   9671406556914834240182310 hyperbolic components with exactly that period in z^2+c."
	);
	oc++;
	mpc->rooms[R->roomid]=R;

	// room 14.3
	R=new mpRoom; MEMORY(R,10) R->roomid=3;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,14,2)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,14,4)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.775621884996692712;
	R->cImag=-0.0033966406249999999203;
	R->multiplier=0.015046725543243160902;
	R->initObjects(1);
	oc=0;
	R->objects[oc]=createFloorNote_IDE(oc,
        "Die Periodizitaet dieser Komponenten sei P. Dann ist P-13 Teil eines Primzahlzwillings.",
        "Let P be the periodicity of the current component. Then P-13 is part of a twin prime."
	);
	oc++;
	mpc->rooms[R->roomid]=R;

	// room 14.4
	R=new mpRoom; MEMORY(R,10) R->roomid=4;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,14,1)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,14,3)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.775613603746692748;
	R->cImag=-0.0033967187499999995648;
	R->multiplier=0.093795959715530771716;

	oc=0;
	R->initObjects(1);
	R->objects[oc]=createCaseDevice_INQQAA(oc,3,
        // solutions to c^6+2*c^5+2*c^4+2*c^3+c^2+1 = 0
        "Wieviele Misiurewicz-Punkte mit exakter Praeperiode 2 und exakter Periode 3 hat z^2+c?\n   (Es sind weniger als 11)\n   Article: Hitz et al. Misiurewicz points for polynomial maps and transversality, 2014.",
        "How many Misiureqicz points of exact preperiod 2 and exact period 3 does z^2+c harbour?\n   (Fewer than 11)\n   Article: Hitz et al. Misiurewicz points for polynomial maps and transversality, 2014.",
        "6",
        "6"
	);

	/*

        answer 6: misiurewicz_multibrot:dmn(2,2,3)
            // Maxima-Skirpt

kill(all);
numer:false;
display2d:false;

// general dynatomic polynomial to arrive at Misiurewicz points for the quadratic Mandelbrot set
// based on: B Hitz, A Towsley. Misiurewicz points for polynomial maps and transversality, 2014.

// n-fold composition of z^2+c
composition_fn(f,n) := (
	ret:"Error. ,composition_fn",

	if n = 0 then ret:z
	else if n > 0 then (
		ret:f,

		for i from 2 thru n do (
			ret:subst(f,z,ret)
		)
	) else print("Error. composition_fn"),

	ratsimp(ret)

)$

// the dynatomic polynomial
dynatomic_fz0n(f,z0,n) := (
	erg:"Error. dynatomic_fz0n",

	if n < 1 then (
		erg:"Error. Period must be at least 1.",
		print("Error. Period must be at least 1.")
	) else (
		erg:1,
		for k from 1 thru n do (
			if mod(n,k) = 0 then (
				co:composition_fn(f,k),
				co:subst(z0,z,co),
				erg: erg * ( ( co - z0 ) ^ moebius(n/k) )
			)
		)
	),

	ratsimp(erg)
)$

// generalized dynatomic polynomial
general_dynatomic_fz0mn(f,z0,m,n) := (
	ret:"Error. general_dynatomic_fz0mn",

	if m = 0 and n > 0 then (
		ret: dynatomic_fz0n(f, z , n)
	) else if m > 0 and n > 0 then (
		ret: ratsimp(
			dynatomic_fz0n(f, composition_fn(f,m) , n)
			/
			dynatomic_fz0n(f, composition_fn(f,m-1) , n)
		),
		ret:subst(z0,z,ret)
	) else print("Error. general_dynatomic_fz0mn"),

	ratsimp(ret)
)$

// Misiurewicz points for unicritical multibrot z^d+c with exact preperiod m and period n
misiurewicz_multibrot_dmn(d,m,n) := (
	ret: "Error misiurewicz_multibrot_dmn",

	if m > 0 and n > 0 and d >= 2 then (
		ret1: general_dynatomic_fz0mn(z^d+c,z,m,n),
		ret1: ratsimp(subst(0,z,ret)),

		if m # 0 and mod(m-1,n) = 0 then (
			ret2: general_dynatomic_fz0mn(z^d+c,z,0,n),
			ret2: subst(0,z,ret2) ^ (d-1),
			ret: ret1 / ret2
		) else ret: ret1
	) else print("Error misiurewicz_multibrot_dmn"),

	ret:ratsimp(ret),
	print("Misiurewicz points as solution from"),
	print(ret,"= 0"),

	sol:solve(ret=0,c),
	numer:true,
	for i from 1 thru length(sol) do (
		print("solution",realpart(expand(rhs(sol[i])))," + i*", imagpart(expand(rhs(sol[i]))) )
	)
)$

extractc(f,var) := (
	for i from 0 thru hipow(f,var) do (
		print("r",i,",",coeff(f,var,i),",0")
	)
);


	*/

	oc++;
	mpc->rooms[R->roomid]=R;

	// room 14.5
	R=new mpRoom; MEMORY(R,10) R->roomid=5;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,14,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,14,6)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7756333693716925826;
	R->cImag=-0.0033848437499999998318;
	R->multiplier=0.62869949239708511346;
	mpc->rooms[R->roomid]=R;

	// room 14.6
	R=new mpRoom; MEMORY(R,10) R->roomid=6;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,14,5)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_PARABOLIC_LOCKED,11,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7756051662466927343;
	R->cImag=-0.0033846093749999995974;
	R->multiplier=0.84113150153488847049;
	mpc->rooms[R->roomid]=R;


	return mpc;
}

mpComponent* createComponent13(void) {
	mpComponent* mpc=new mpComponent;
	if (!mpc) return NULL;

	// component 13, period 63 at other bulb at period 6 attached period 3-cardioid

	mpc->hcReal=-1.7560934865591926179;
	mpc->hcImag=-0.012949218749999999792;
	mpc->period=63;

	mpRoom* R;

	mpc->initRooms(45);

	// room 13.0
	R=new mpRoom; MEMORY(R,10) R->roomid=0;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,5)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,1)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560944365591926175;
	R->cImag=-0.012953181249999999244;
	R->multiplier=0.86814413776309051762;
	mpc->rooms[R->roomid]=R;

	// room 13.1
	R=new mpRoom; MEMORY(R,10) R->roomid=1;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,6)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,2)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560928865591927117;
	R->cImag=-0.012953068749999999479;
	R->multiplier=0.77511409914919648934;
	mpc->rooms[R->roomid]=R;

	// room 13.2
	R=new mpRoom; MEMORY(R,10) R->roomid=2;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,7)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,1)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560921240591926829;
	R->cImag=-0.012953081249999999838;
	R->multiplier=0.83031444126281828133;
	mpc->rooms[R->roomid]=R;

	// room 13-3
	R=new mpRoom; MEMORY(R,10) R->roomid=3;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,9)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,4)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560957365591927104;
	R->cImag=-0.012952481249999999932;

	int32_t oc=0;
	R->initObjects(1);
	// J Gao, On buried points and phase transitions in the Julia set concerning renormalization trasnsformation.
	R->objects[oc]=createNoteInCase_IQDE(oc,
        createQuestionMultipleChoice_QQC0123(
            "Sei f(z)=[(z^2+L-1)/(2*z+L-2)]^5 fuer L=1.824. Der Punkt z0=-1.1484375 hat eine spezielle Eigenschaft. Welche?",
            "Let f(z)=[(z^2+L-1)/(2*z+L-2)]^5 with L=1.824. The point z0=-1.1484375 has a particular property, which is ...",
            2,
            "a parabolic fix point",
            "a pole of f(z)",
            "lies inside a buried real interval in the Julia set",
            "forms a single point Fatou component"
        ),
        "Die linkeste Ziffer der Periode ist eine 6.",
        "The leftmost digit of the periodicity is a 6."
    );
	oc++;

	R->multiplier=0.90679146431046753207;
	mpc->rooms[R->roomid]=R;

	// room 13.4
	R=new mpRoom; MEMORY(R,10) R->roomid=4;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,17)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,3)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,5)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560951240591926581;
	R->cImag=-0.012952506249999998916;

	oc=0;
	R->initObjects(1);
	R->objects[oc]=createNoteInCase_IQDE(oc,
        createQuestionMultipleChoice_QQC0123(
            "Wieviele Geiser-Komponenten hat die Mandelbrot-Menge?",
            "How many ghost components does the Mandelbrot set have?",
            2,
            "0",
            "finitely many",
            "currently unknown",
            "infinitely many"
        ),
        "Die Zahlenfolge 1,1,2,4 (oder eine Permutation davon) stellt den Weg zum Ausgang dar,\n   wenn Du den STARTpunkt gefunden hast.",
        "The series 1,1,2,4 (or a permutation thereof) depicts a route to the exit, once you've found the STARTing room."

    );
	oc++;

	R->multiplier=0.78284093691138978421;
	mpc->rooms[R->roomid]=R;

	// room 13.5 transmitter landing
	R=new mpRoom; MEMORY(R,10) R->roomid=5;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,10)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,4)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,6)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560944115591925474;
	R->cImag=-0.01295241874999999987;

	oc=0;
	R->initObjects(1);
	mpObjFloorNote* tmp=createFloorNote_IDE(oc,
        "Fast alle der vielen Raeume dieser Komponente sind leer. Aber gib nicht auf!\n   Es gilt, wichtige Informationen zu finden.",
        "Almost all of the many rooms in this component are empty. But don't give up!\n   There is important information to be found."
    );
    tmp->alreadyread=1; // make it visible
    R->objects[oc]=tmp;
	oc++;
	R->multiplier=0.64922321230516888413;
	mpc->rooms[R->roomid]=R;

	// room 13.6
	R=new mpRoom; MEMORY(R,10) R->roomid=6;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,11)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,1)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,5)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,7)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560927365591925131;
	R->cImag=-0.012952356249999999807;
	R->multiplier=0.57481861106105824888;
	mpc->rooms[R->roomid]=R;

	// room 13.7
	R=new mpRoom; MEMORY(R,10) R->roomid=7;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,12)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,2)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,6)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,8)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560919615591925602;
	R->cImag=-0.012952568749999998979;
	R->multiplier=0.70334808467574216895;
	mpc->rooms[R->roomid]=R;

	// room 13.8
	R=new mpRoom; MEMORY(R,10) R->roomid=8;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,14)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,7)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560906865591925374;
	R->cImag=-0.012952343749999999448;
	R->multiplier=0.87541918957553621627;
	mpc->rooms[R->roomid]=R;

	// room 13.9
	R=new mpRoom; MEMORY(R,10) R->roomid=9;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,16)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,3)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,10)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.756095899059192611;
	R->cImag=-0.012951731249999999182;
	R->multiplier=0.79529982338225813088;
	mpc->rooms[R->roomid]=R;

	// room 13.10
	R=new mpRoom; MEMORY(R,10) R->roomid=10;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,18)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,5)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,9)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,11)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560944490591925415;
	R->cImag=-0.012951693749999999838;
	R->multiplier=0.46801950436447709025;
	mpc->rooms[R->roomid]=R;

	// room 13.11
	R=new mpRoom; MEMORY(R,10) R->roomid=11;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,19)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,6)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,10)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,12)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560927740591925073;
	R->cImag=-0.012951806249999999604;
	R->multiplier=0.42607931752739469644;
	mpc->rooms[R->roomid]=R;

	// room 13.12
	R=new mpRoom; MEMORY(R,10) R->roomid=12;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,30)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,7)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,11)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,13)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560920615591926186;
	R->cImag=-0.012951718749999998823;
	R->multiplier=0.47386743314279533568;
	mpc->rooms[R->roomid]=R;

	// room 13.13
	R=new mpRoom; MEMORY(R,10) R->roomid=13;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,26)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,12)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,14)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560913115591925138;
	R->cImag=-0.012951856249999999307;
	R->multiplier=0.63105659712168504782;
	mpc->rooms[R->roomid]=R;

	// room 13.14
	R=new mpRoom; MEMORY(R,10) R->roomid=14;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,20)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,8)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,13)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560904740591927187;
	R->cImag=-0.01295166874999999912;
	R->multiplier=0.78834501505572784907;
	mpc->rooms[R->roomid]=R;

	// room 13.15
	R=new mpRoom; MEMORY(R,10) R->roomid=15;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,22)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,16)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560964615591925231;
	R->cImag=-0.012950956249999999448;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createFloorNote_IDE(oc,
        "Diese Komponente hat keine parabolische Tuer. Suche einen anderen Ausgang.",
        "This component does not have a parabolic door. You have to look for a different exit."
    );
	oc++;

	R->multiplier=0.87543798023959906729;
	mpc->rooms[R->roomid]=R;

	// room 13.16
	R=new mpRoom; MEMORY(R,10) R->roomid=16;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,23)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,9)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,15)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,17)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560960240591925174;
	R->cImag=-0.012951006249999999151;
	R->multiplier=0.72857502683930386311;
	mpc->rooms[R->roomid]=R;

	// room 13.17
	R=new mpRoom; MEMORY(R,10) R->roomid=17;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,35)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,4)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,16)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,18)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560950490591926698;
	R->cImag=-0.012950906249999999745;
	R->multiplier=0.4253296023322923336;
	mpc->rooms[R->roomid]=R;

	// room 13.18
	R=new mpRoom; MEMORY(R,10) R->roomid=18;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,24)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,10)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,17)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,19)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560943240591926351;
	R->cImag=-0.012950918750000000104;
	R->multiplier=0.2786464592693422837;
	mpc->rooms[R->roomid]=R;

	// room 13.19
	R=new mpRoom; MEMORY(R,10) R->roomid=19;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,25)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,11)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,18)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,20)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560927740591925073;
	R->cImag=-0.012950956249999999448;
	R->multiplier=0.22970552198952756684;
	mpc->rooms[R->roomid]=R;

	// room 13.20
	R=new mpRoom; MEMORY(R,10) R->roomid=20;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,32)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,14)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,19)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,21)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560905865591927011;
	R->cImag=-0.012950931250000000464;
	R->multiplier=0.64059783112093438007;
	mpc->rooms[R->roomid]=R;

	// room 13.21
	R=new mpRoom; MEMORY(R,10) R->roomid=21;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,27)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,20)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560898490591925203;
	R->cImag=-0.012951006249999999151;
	R->multiplier=0.87370249594181781383;
	mpc->rooms[R->roomid]=R;

	// room 13.22
	R=new mpRoom; MEMORY(R,10) R->roomid=22;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,15)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,23)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560965240591925873;
	R->cImag=-0.012950343749999999182;
	R->multiplier=0.87592197493017254217;
	mpc->rooms[R->roomid]=R;

	// room 13.23
	R=new mpRoom; MEMORY(R,10) R->roomid=23;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,34)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,16)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,22)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,24)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560958615591926169;
	R->cImag=-0.012950306249999999839;
	R->multiplier=0.62241026842877933412;
	mpc->rooms[R->roomid]=R;

	// room 13.24
	R=new mpRoom; MEMORY(R,10) R->roomid=24;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,36)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,18)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,23)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,25)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560944115591925474;
	R->cImag=-0.012950231249999999417;
	R->multiplier=0.18078393352858854182;
	mpc->rooms[R->roomid]=R;

	// room 13.25
	R=new mpRoom; MEMORY(R,10) R->roomid=25;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,29)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,19)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,24)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,26)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560929865591925481;
	R->cImag=-0.012950168749999999354;
	R->multiplier=0.07977986559007016476;
	mpc->rooms[R->roomid]=R;

	// room 13.26
	R=new mpRoom; MEMORY(R,10) R->roomid=26;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,31)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,13)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,25)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,27)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.756091361559192654;
	R->cImag=-0.012950218749999999057;
	R->multiplier=0.35555078177013138552;
	mpc->rooms[R->roomid]=R;

	// room 13.27
	R=new mpRoom; MEMORY(R,10) R->roomid=27;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,33)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,21)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,26)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560898365591925963;
	R->cImag=-0.012950268750000000495;
	R->multiplier=0.81640469037837060107;
	mpc->rooms[R->roomid]=R;

	// room 13.28
	R=new mpRoom; MEMORY(R,10) R->roomid=28;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,29)
	R->predHC=1;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560936115591925244;
	R->cImag=-0.012949418750000000339;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createTransmitter_IDD(oc,15,3);
	oc++;

	R->multiplier=0.0061530709201883708806;
	mpc->rooms[R->roomid]=R;

	// room 13.29
	R=new mpRoom; MEMORY(R,10) R->roomid=29;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,42)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,25)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,28)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,30)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560928990591926357;
	R->cImag=-0.01294938124999999926;
	R->multiplier=0.026725014750200479924;
	mpc->rooms[R->roomid]=R;

	// room 13.30
	R=new mpRoom; MEMORY(R,10) R->roomid=30;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,37)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,12)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,29)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,31)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560920740591925426;
	R->cImag=-0.012949406249999999979;
	R->multiplier=0.15554601554222086124;
	mpc->rooms[R->roomid]=R;

	// room 13.31
	R=new mpRoom; MEMORY(R,10) R->roomid=31;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,38)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,26)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,30)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,32)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560913365591925839;
	R->cImag=-0.012949518749999999745;
	R->multiplier=0.33154826356907268758;
	mpc->rooms[R->roomid]=R;

	// room 13.32
	R=new mpRoom; MEMORY(R,10) R->roomid=32;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,39)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,20)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,31)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,33)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560906490591925433;
	R->cImag=-0.012949418750000000339;
	R->multiplier=0.53559739380681958831;
	mpc->rooms[R->roomid]=R;

	// room 13.33
	R=new mpRoom; MEMORY(R,10) R->roomid=33;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,40)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,27)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,32)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560898740591925904;
	R->cImag=-0.012949318749999999198;
	R->multiplier=0.80299915155370349407;
	mpc->rooms[R->roomid]=R;

	// room 13.34
	R=new mpRoom; MEMORY(R,10) R->roomid=34;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,23)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,35)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.756095624059192728;
	R->cImag=-0.012948768749999998995;
	R->multiplier=0.7608357465860366986;
	mpc->rooms[R->roomid]=R;

	// room 13.35
	R=new mpRoom; MEMORY(R,10) R->roomid=35;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,17)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,34)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,36)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560949865591926056;
	R->cImag=-0.012948643750000000605;
	R->multiplier=0.56795901861324771254;
	mpc->rooms[R->roomid]=R;

	// room 13.36
	R=new mpRoom; MEMORY(R,10) R->roomid=36;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,41)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,24)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,35)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,37)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560943865591926993;
	R->cImag=-0.012948706250000000667;
	R->multiplier=0.26047930816964409706;
	mpc->rooms[R->roomid]=R;

	// room 13.37
	R=new mpRoom; MEMORY(R,10) R->roomid=37;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,30)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,36)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,38)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560920865591926887;
	R->cImag=-0.012948781249999999354;
	R->multiplier=0.19101568628490675494;
	mpc->rooms[R->roomid]=R;

	// room 13.38
	R=new mpRoom; MEMORY(R,10) R->roomid=38;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,43)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,31)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,37)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,39)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560913365591925839;
	R->cImag=-0.012948781249999999354;

	oc=0;
	R->initObjects(1);
	R->objects[oc]=createNoteInCase_IQDE(oc,
        createQuestionMultipleChoice_QQC0123(
            "Sei f_d(z)=1/(z^17+d). Die Punkte z=0 und z=inf haben fuer bspw. f_0(z) eine besondere Eigenschaft fuer f_0. Welche?",
            "Let f_d(z)=1/(z^17+d). The points z=0 and z=inf have a particular property for f_0, which is ...",
            0,
            "the only two exceptional poins",
            "two of infinitely many exceptional points",
            "lie both in the Julia set J_f",
            "are both poles of f_0(z)"
        ),
        "Die niedrigste Ziffer der Periode ist die Haelfte der hoechsten.",
        "The rightmost digit of the periodicity is half the leftmost one."
    );
	oc++;

	R->multiplier=0.37496424662757815716;
	mpc->rooms[R->roomid]=R;

	// room 13.39
	R=new mpRoom; MEMORY(R,10) R->roomid=39;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,13,44)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,32)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,38)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,40)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560905865591927011;
	R->cImag=-0.012948606249999999526;
	R->multiplier=0.62466996776325667273;
	mpc->rooms[R->roomid]=R;

	// room 13.40
	R=new mpRoom; MEMORY(R,10) R->roomid=40;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,33)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,39)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560899865591925728;
	R->cImag=-0.01294875625000000037;
	R->multiplier=0.81077815269696129619;
	mpc->rooms[R->roomid]=R;

	// room 13.41
	R=new mpRoom; MEMORY(R,10) R->roomid=41;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,36)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,42)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560941990591927286;
	R->cImag=-0.012947893749999999854;
	R->multiplier=0.62109447077340651511;
	mpc->rooms[R->roomid]=R;

	// room 13.42
	R=new mpRoom; MEMORY(R,10) R->roomid=42;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,29)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,41)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,43)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560929240591927059;
	R->cImag=-0.012947893749999999854;
	R->multiplier=0.28364841124586709364;
	mpc->rooms[R->roomid]=R;

	// room 13.43
	R=new mpRoom; MEMORY(R,10) R->roomid=43;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,38)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,42)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,13,44)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560913365591925839;
	R->cImag=-0.012947931249999999198;
	R->multiplier=0.53591567354288827119;
	mpc->rooms[R->roomid]=R;

	// room 13.44
	R=new mpRoom; MEMORY(R,10) R->roomid=44;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,13,39)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,13,43)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.7560905990591926251;
	R->cImag=-0.012948093750000000401;

	oc=0;
	R->initObjects(1);
	tmp=createFloorNote_IDE(oc,
        "Der Multiplier-Detektor koennte hier helfen, einen Ausgang zu finden.",
        "The multiplier detector might be of help here to find an exit."
    );
    tmp->alreadyread=1;
    R->objects[oc]=tmp;
	oc++;

	R->multiplier=0.71240014884586222443;
	mpc->rooms[R->roomid]=R;


	return mpc;

}

mpComponent* createComponent15(void) {
	mpComponent* mpc=new mpComponent;
	if (!mpc) return NULL;

	// component 15, period 63 at main cardioid

	mpc->hcReal=0.18021309423352691037;
	mpc->hcImag=0.5579737964726595445;
	mpc->period=63;

	mpRoom* R;

	mpc->initRooms(4);

	// room 15.0
	R=new mpRoom; MEMORY(R,10) R->roomid=0;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_PARABOLIC_LOCKED,4,6)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,15,1)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=0.18007871923352691823;
	R->cImag=0.55783864022265960969;
	R->multiplier=0.88362171977560277636;
	mpc->rooms[R->roomid]=R;

	// room 15.1
	R=new mpRoom; MEMORY(R,10) R->roomid=1;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,15,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,15,2)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=0.18015918798352689723;
	R->cImag=0.55784020272265955054;
	R->multiplier=0.49573185465080821244;
	mpc->rooms[R->roomid]=R;

	// room 15.2
	R=new mpRoom; MEMORY(R,10) R->roomid=2;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,15,3)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,15,1)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=0.18019746923352691903;
	R->cImag=0.55784176522265960241;
	R->multiplier=0.41959133284203542491;
	mpc->rooms[R->roomid]=R;

	// room 15.3
	R=new mpRoom; MEMORY(R,10) R->roomid=3;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,15,2)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=1;
	R->objectanz=0; R->objects=NULL;
	R->cReal=0.18019903173352691539;
	R->cImag=0.55795973397265952176;

	R->multiplier=0.0085871550682133993004;

	R->initObjects(2);
	int32_t oc=0;
	R->objects[oc]=createTransmitter_IDD(oc,12,0);
	oc++;

    R->objects[oc]=createFloorNote_IDE(oc,
        "Die Periode der aktuellen Komponente besteht aus zwei Ziffern.\n   Die 2te ist die Periode des anziehenden Zyklus fuer z^2-1.765625.\n   Die 1te ist die Anzahl der Iterationen, die der Punkt\n     z0=1.91953125602077922057144155331910811798336541288694335038397109589140005053853\n   benoetigt, um in einem \"immediate Basin\" des Zyklus zu landen.",
        "The current component's period consists of two digits.\n   The 2nd is the period of the attracting cycle for z^2-1.765625.\n   The 1st is the number of iterations the point\n     z0=1.91953125602077922057144155331910811798336541288694335038397109589140005053853\n   needs to land in an immediate basin of the cycle."
    );
    oc++;

	mpc->rooms[R->roomid]=R;


	return mpc;
}

mpComponent* createComponent4(void) {
	mpComponent* mpc=new mpComponent;
	if (!mpc) return NULL;

	// component 4, main cardioid

	mpc->hcReal=0;
	mpc->hcImag=0;
	mpc->period=1;

	mpRoom* R;

	mpc->initRooms(7);

	// room 4.0
	R=new mpRoom; MEMORY(R,10) R->roomid=0;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_PARABOLIC_LOCKED,3,3)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,4,1)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.73150000000000003908;
	R->cImag=0;
	R->multiplier=0.96317272644895968181;

	R->initObjects(1);
	int32_t oc=0;
	R->objects[oc]=createFloorNote_IDE(oc,
        "Die Flaeche dieser Komponente ist 3/8*PI.",
        "This component's area equals 3/8*PI."
    );
    // source: https://iquilezles.org/articles/msetarea/ "Area of the M1 cardioid"
	oc++;

	mpc->rooms[R->roomid]=R;

	// room 4.1
	R=new mpRoom; MEMORY(R,10) R->roomid=1;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,4,4)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,4,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,4,2)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.20404999999999995364;
	R->cImag=-0.02502499999999996394;
	R->multiplier=0.12260465375556664491;
	mpc->rooms[R->roomid]=R;

	// room 4.2
	R=new mpRoom; MEMORY(R,10) R->roomid=2;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,4,1)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=1;
	R->objectanz=0; R->objects=NULL;
	R->cReal=0.036093749999999924505;
	R->cImag=0.033687499999999981348;
	R->multiplier=0.010479082657655201805;

	R->initObjects(2);
	oc=0;
	R->objects[oc]=createTransmitter_IDD(oc,-1,-1); // inactivbe
	oc++;
	R->objects[oc]=createPrisonCell_I(oc); // imprisoned
	oc++;
	mpc->rooms[R->roomid]=R;

	// room 4.3
	R=new mpRoom; MEMORY(R,10) R->roomid=3;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_PARABOLIC_LOCKED,6,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,4,4)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.4812500000000000111;
	R->cImag=0.51974999999999993427;
	R->multiplier=0.97926020432263838345;
	mpc->rooms[R->roomid]=R;

	// room 4.4
	R=new mpRoom; MEMORY(R,10) R->roomid=4;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,4,5)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,4,1)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,4,3)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.20789999999999997371;
	R->cImag=0.52744999999999997442;
	R->multiplier=0.75237084385753416615;
	mpc->rooms[R->roomid]=R;

	// room 4.5
	R=new mpRoom; MEMORY(R,10) R->roomid=5;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,4,4)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,4,6)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.17132499999999994955;
	R->cImag=0.57653749999999992504;
	R->multiplier=0.84247859390695190029;
	mpc->rooms[R->roomid]=R;

	// room 4.6
	R=new mpRoom; MEMORY(R,10) R->roomid=6;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,4,5)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_PARABOLIC_LOCKED,15,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=0.13667499999999999094;
	R->cImag=0.5659499999999999531;
	R->multiplier=0.95840272683832161693;
	mpc->rooms[R->roomid]=R;


	return mpc;
}

mpComponent* createComponent6(void) {
	mpComponent* mpc=new mpComponent;
	if (!mpc) return NULL;

	// component 6, period 5 attached to main cardioid

	mpc->hcReal=-0.50500000000000000444;
	mpc->hcImag=0.5625;
	mpc->period=5;

	mpRoom* R;

	mpc->initRooms(10);

	// room 6.0
	R=new mpRoom; MEMORY(R,10) R->roomid=0;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,6,2)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_PARABOLIC_LOCKED,4,3)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.484375;
	R->cImag=0.53156249999999993783;
	R->multiplier=0.92797039735931574622;

	R->initObjects(1);

	/*
        accumulation point of period-doubling ont eh x axis
        https://fractalforums.org/fractal-mathematics-and-new-theories/28/accumulation-point-of-period-doubling/4440/msg30822#msg30822
        reliably computed accurate digits: -1.4011551___
	*/
	int32_t oc=0;
	R->objects[oc]=createNoteInCase_IQDE(oc,
        createQuestionMultipleChoice_QQC0123(
            "Der Akkumulationspunkt der klassischen Periodenverdopplung\nauf der reellen Achse liegt in",
            "The accumulation point of the classical period doubling\non the real axis lies within",
            2,
            "[-1.437 .. -1.436]",
            "[-1.423 .. -1.422]",
            "{-1.402 .. -1.401]",
            "[-1.401 .. -1.400]"
        ),
        "Die aktuelle Periode ist 5.",
        "The current periodicty is 5."
    );
    oc++;

	mpc->rooms[R->roomid]=R;

	// room 6.1
	R=new mpRoom; MEMORY(R,10) R->roomid=1;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,6,5)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,6,2)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.50837500000000002132;
	R->cImag=0.54749999999999998668;
	R->multiplier=0.16636452964452949632;
	mpc->rooms[R->roomid]=R;

	// room 6.2
	R=new mpRoom; MEMORY(R,10) R->roomid=2;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,6,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,6,1)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.48418749999999999289;
	R->cImag=0.54787500000000000089;
	R->multiplier=0.42175860833269207539;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createNoteBehindMirror_IDE(oc,
        "Der Manhattan-Abstand dieses Raumes zum Zentrum des\n   Hauptkardioids is ungefaehr 1.0321",
        "The Manhattan distance from this room to the center\n   of the main cardioid is approximately 1.0321"
	);
	oc++;
	mpc->rooms[R->roomid]=R;

	// room 6.3
	R=new mpRoom; MEMORY(R,10) R->roomid=3;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_PARABOLIC_LOCKED,7,5)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,6,4)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.5413749999999999396;
	R->cImag=0.56006249999999990763;
	R->multiplier=0.90907233968336154106;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createNoteInCase_IQDE(oc,
        createQuestionQA_QQAA(
            "Wieviele Petals hat die Julia-Menge zu\nz^2+(-0.22252093395631458717-0.97492791218182361934*i)*z",
            "How many petals shows the Julia set of\nz^2+(-0.22252093395631458717-0.97492791218182361934*i)*z",
            "7",
            "7"
        ),
        "Der euklidische Abstand dieses Raumes zum Zentrum des\n   Hauptkardioids is ungefaehr 0.7789",
        "The Euclidean distance from this room to the center\n   of the main cardioid is approximately 0.7789"
    );
	oc++;

	mpc->rooms[R->roomid]=R;

	// room 6.4
	R=new mpRoom; MEMORY(R,10) R->roomid=4;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,6,3)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,6,5)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.53049999999999997158;
	R->cImag=0.55968750000000000444;
	R->multiplier=0.45867872630335398965;
	mpc->rooms[R->roomid]=R;

	// room 6.5
	R=new mpRoom; MEMORY(R,10) R->roomid=5;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,6,7)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,6,1)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,6,4)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,6,6)
	R->predHC=1;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.50762499999999999289;
	R->cImag=0.56006249999999990763;
	R->multiplier=0.012029211377230503502;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createFloorNote_IDE(oc,
        "Der euklidische Abstand der reellen Koordinate dieses Raumes zum\n   Zentrum des noerdlichen Period-3-Bulbs ist ungefaehr 0.3851",
        "The Euclidean distance of the real coordinate from this room to\n   the center of the north period-3 bulb is approximately 0.3851"
	);
	oc++;

	mpc->rooms[R->roomid]=R;

	// room 6.6
	R=new mpRoom; MEMORY(R,10) R->roomid=6;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,6,9)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,6,5)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.49018749999999999822;
	R->cImag=0.55968750000000000444;
	R->multiplier=0.14002810729212322727;
	mpc->rooms[R->roomid]=R;

	// room 6.7
	R=new mpRoom; MEMORY(R,10) R->roomid=7;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,6,5)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,6,8)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.50706249999999997158;
	R->cImag=0.58274999999999999023;
	R->multiplier=0.2684367965313237403;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createFloorNote_IDE(oc,
        "Die aktuelle Periode ist eine Primzahl.",
        "The current periodicity is prime."
	);
	oc++;

	mpc->rooms[R->roomid]=R;

	// room 6.8
	R=new mpRoom; MEMORY(R,10) R->roomid=8;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,6,7)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.49581249999999998934;
	R->cImag=0.58274999999999999023;
	R->multiplier=0.31206163677234421971;
	mpc->rooms[R->roomid]=R;

	// room 6.9
	R=new mpRoom; MEMORY(R,10) R->roomid=9;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,6,6)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.48868749999999999689;
	R->cImag=0.59662499999999996092;
	R->multiplier=0.91577611406172509945;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createFloorNote_IDE(oc,
        "Der euklidische Abstand dieses Raumes zum Zentrum des\n  Hauptkardioid is ungefaehr 0.7712",
        "The Euclidean distance from this room to the center\n  of the main cardioid is approximately 0.7712"
    );
	oc++;

	mpc->rooms[R->roomid]=R;


	return mpc;
}

mpComponent* createComponent3(void) {
	mpComponent* mpc=new mpComponent;
	if (!mpc) return NULL;

	// component 3, period-doubling 2 on x-axis

	mpc->hcReal=-1;
	mpc->hcImag=0;
	mpc->period=2;

	mpRoom* R;

	mpc->initRooms(7);

	// room 0
	R=new mpRoom; MEMORY(R,10) R->roomid=0;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_PARABOLIC_LOCKED,2,5)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,3,1)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.2432031249999999645;
	R->cImag=0.0017187499999999911182;
	R->multiplier=0.94641142578129933138;

	R->initObjects(1);
	int32_t oc=0;
	R->objects[oc]=createFloorNote_IDE(oc,
        "Der erste Teil eines Satzes: \"Die Komponente ist ein perfekter ...\"",
        "The first part of a sentence: \"The component is a perfect ...\""
	);
	oc++;
	mpc->rooms[R->roomid]=R;

	// room 1
	R=new mpRoom; MEMORY(R,10) R->roomid=1;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,3,4)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,3,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,3,2)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.12890625;
	R->cImag=0.00085937499999999555911;
	R->multiplier=0.26588095703124986491;
	mpc->rooms[R->roomid]=R;

	// room 2
	R=new mpRoom; MEMORY(R,10) R->roomid=2;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,3,6)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,3,1)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,3,3)
	R->predHC=1;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.98539062499999996447;
	R->cImag=0.012031249999999993339;
	R->multiplier=0.0057309570312499957118;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createTransmitter_IDD(oc,-1,-1); // inactivbe
	oc++;
	mpc->rooms[R->roomid]=R;

	// room 3
	R=new mpRoom; MEMORY(R,10) R->roomid=3;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,3,2)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_PARABOLIC_LOCKED,4,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.76023437500000001776;
	R->cImag=0.0025781249999999866773;
	R->multiplier=0.91990722656249812594;
	mpc->rooms[R->roomid]=R;

	// room 4
	R=new mpRoom; MEMORY(R,10) R->roomid=4;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,3,1)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,3,5)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.12890625;
	R->cImag=0.03179687500000000222;
	R->multiplier=0.28204580078124874554;
	mpc->rooms[R->roomid]=R;

	// room 5
	R=new mpRoom; MEMORY(R,10) R->roomid=5;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,3,4)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,3,6)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.0549999999999999378;
	R->cImag=0.034375000000000044409;
	R->multiplier=0.067306249999999900879;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createNoteInCase_IQDE(oc,
        createQuestionQA_QQAA(
            "Wieviele Komponenten mit Periode exakt 4 hat die Mandelbrotmenge?",
            "How many components of exact period 4 does the Mandelbrot set have?",
            "6",
            "6"
        ),
        "Kreis",
        "circle"
	);
	oc++;
	mpc->rooms[R->roomid]=R;

	// room 6
	R=new mpRoom; MEMORY(R,10) R->roomid=6;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,3,2)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,3,5)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-0.99484375000000002665;
	R->cImag=0.03265624999999999778;
	R->multiplier=0.017488281250000004691;
	mpc->rooms[R->roomid]=R;

	return mpc;
}

mpComponent* createComponent2(void) {
	mpComponent* mpc=new mpComponent;
	if (!mpc) return NULL;

	// component 2, period-doubling 4 on x-axis

	mpc->hcReal=-1.3107026413368327855;
	mpc->hcImag=0;
	mpc->period=4;

	mpRoom* R;

	mpc->initRooms(8);

	// room 0
	R=new mpRoom; MEMORY(R,10) R->roomid=0;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,2,3)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,2,1)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.315702641336832901;
	R->cImag=-0.0050000000000000044409;
	R->multiplier=0.014441734420104664072;
	mpc->rooms[R->roomid]=R;

	// room 1
	R=new mpRoom; MEMORY(R,10) R->roomid=1;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,2,4)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,2,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.3083026413368328278;
	R->cImag=-0.0054000000000000020206;
	R->multiplier=0.010015530338404739913;
	mpc->rooms[R->roomid]=R;

	// room 2
	R=new mpRoom; MEMORY(R,10) R->roomid=2;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_PARABOLIC_LOCKED,0,4)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,2,3)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.3661026413368329013;
	R->cImag=0.0022000000000000075051;
	R->multiplier=0.93135326701485421363;
	mpc->rooms[R->roomid]=R;

	// room 3
	R=new mpRoom; MEMORY(R,10) R->roomid=3;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,2,7)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,2,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,2,2)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,2,4)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.315702641336832901;
	R->cImag=0.0020000000000000017764;
	R->multiplier=0.0083762055954889266807;
	mpc->rooms[R->roomid]=R;

	// room 4
	R=new mpRoom; MEMORY(R,10) R->roomid=4;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_OPEN,2,6)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,2,1)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,2,3)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,2,5)
	R->predHC=1;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.3055026413368326921;
	R->cImag=0.0051999999999999962919;
	R->multiplier=0.015469721104678802598;

	R->initObjects(1);
	int32_t oc=0;
	R->objects[oc]=createTransmitter_IDD(oc,-1,-1);
	oc++;
	mpc->rooms[R->roomid]=R;

	// room 5
	R=new mpRoom; MEMORY(R,10) R->roomid=5;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,2,4)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_PARABOLIC_LOCKED,3,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.2553026413368326697;
	R->cImag=0.0023999999999999993561;
	R->multiplier=0.83868885381286384373;
	mpc->rooms[R->roomid]=R;

	// room 6
	R=new mpRoom; MEMORY(R,10) R->roomid=6;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,2,4)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.3083026413368328278;
	R->cImag=0.010599999999999998312;
	R->multiplier=0.033878418687294922784;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createFloorNote_IDE(oc,
        "Die Periode ist um eins geringer als die Anzahl\n   der Komponenten mit Periode hoechstens 3.",
        "The period is the number of components of periods\n   up to and including 3 subtracted by one."
	);
	oc++;

	mpc->rooms[R->roomid]=R;

	// room 7
	R=new mpRoom; MEMORY(R,10) R->roomid=7;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_PARABOLIC_LOCKED,5,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_OPEN,2,3)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_NONE,0,0)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.3129026413368327653;
	R->cImag=0.055599999999999996647;
	R->multiplier=0.8919206493464174601;
	mpc->rooms[R->roomid]=R;

	return mpc;
}

mpComponent* createComponent1(void) {
	mpComponent* mpc=new mpComponent;
	if (!mpc) return NULL;

	// component 1, period-doubling 16 on x-axis

	mpc->hcReal=-1.3969453597045606852;
	mpc->hcImag=0;
	mpc->period=16;

	mpRoom* R;

	mpc->initRooms(2);

	// room 0
	R=new mpRoom; MEMORY(R,10) R->roomid=0;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_EAST ],MP_DOOR_OPEN,1,1)
	R->predHC=1;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.3968828597045606088;
	R->cImag=7.8125000000000069389e-05;
	R->multiplier=0.0012860718085564257652;

	R->initObjects(1);
	int32_t oc=0;
	R->objects[oc]=createTransmitter_IDD(oc,5,1);
	oc++;
	mpc->rooms[R->roomid]=R;

	// room 1
	R=new mpRoom; MEMORY(R,10) R->roomid=1;
	SETDOOR(R->doors[MP_NORTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_SOUTH],MP_DOOR_NONE,0,0)
	SETDOOR(R->doors[MP_WEST ],MP_DOOR_OPEN,1,0)
	SETDOOR(R->doors[MP_EAST],MP_DOOR_PARABOLIC_LOCKED,0,1)
	R->predHC=0;
	R->objectanz=0; R->objects=NULL;
	R->cReal=-1.3942891097045606585;
	R->cImag=4.6875000000000041633e-05;
	R->multiplier=0.84517832316723517927;

	R->initObjects(1);
	oc=0;
	R->objects[oc]=createNoteBehindMirror_IDE(oc,"Die aktuelle Periode ist 16.","Current period is 16.");
	oc++;

	mpc->rooms[R->roomid]=R;

	return mpc;
}

int8_t mpObjPrisonCell::saveGameState(FILE* f) {
    if (!f) return 0;

    WRITETYPE(int8_t,f,imprisoned)

    return 1;

}

int8_t mpObjPrisonCell::loadGameState(FILE* f) {
    if (!f) return 0;

    READTYPE(int8_t,f,imprisoned)

    return 1;

}

mpObjPrisonCell::mpObjPrisonCell() {
    /*
        maxima script:
        kill(all);numer:false;display2d:false;

        p(z):=z^2+d;
        f(z):=c*z*(1-z);
        h(z):=v*z+w;
        eqA:expand(h(p(z)));eqB:expand(f(h(z)));
        coA2:coeff(eqA,z,2);coB2:coeff(eqB,z,2);
        coA1:coeff(eqA,z,1);coB1:coeff(eqB,z,1);
        coA0:coeff(eqA,z,0);coB0:coeff(eqB,z,0);
        sol:solve([coA2=coB2,coA1=coB1,coA0=coB0],[v,w,d]);

        linear solution:  [v = -1/c,w = 1/2,d = -(c^2-2*c)/4]]

    */

    /*
        LECTURE NOTES ON DYNAMICAL SYSTEMS, CHAOS AND FRACTAL GEOMETRY
        Geoffrey R. Goodson

        exercise 6.3.1

    */

    qa=createQuestionMultipleChoice_QQC0123(
        "  Konjugiere affin die Mandelbrotmenge p(z)=z^2+d zur\n  logistischen Gleichung f(z)=c*z*(1-z) mittels h(z)=v*z+w,\n  so dass h(p(z))=f(h(z)).",
        "  Affinely conjugate the Mandelbrot set p(z)=z^2+d with\n  the logistic map f(z)=c*z*(1-z) via h(z)=v*z+w\n  such that h(p(z))=f(h(z)).",
        2,
        "v=1/c,w=1/2,d=(2*c+c^2)/4",
        "v=1/c,w=2,d=(2*c+c^2)/5",
        "v=-1/c,w=1/2,d=-(c^2-2*c)/4", // correct
        "v=sqrt(1/c),w=-1/2,d=-(c^2-2*c)/4"
    );

}

mpObjPrisonCell::~mpObjPrisonCell() {
    if (qa) delete qa;
}

int8_t mpObjPrisonCell::getDescr_T(DynSlowString& T) {
    T.setEmpty();

    if (imprisoned > 0) {
        if (language == MP_DEUTSCH) T.add("Benoit Mandelbrot in seiner Gefaengniszelle.");
        else T.add("Benoit Mandelbrot imprisoned in a locked cell.");
    } else {
        if (language == MP_DEUTSCH) T.add("Leere Zelle.");
        else T.add("Empty prison cell.");
    }

    return 1;
}

int8_t mpObjPrisonCell::parseCommand_ACR(
    mpParams& mpp,
    const int32_t currcomp,
    const int32_t currroom
) {
    // free Benoit/mandelbrot, open cell, open prison, rescue benoit/mandelbrot
    // befreie benout, oeffne zelle, oeffne gefaengnis, befreie mandelbrot

    int8_t free=1;
    if (free > 0) if (mpp.paranz < 2) free=0;
    if (free > 0) {
        if (
        !(
            (
                (
                    (strstr(mpp.params[0].text,"FREE" )==mpp.params[0].text) ||
                    (strstr(mpp.params[0].text,"RESCU")==mpp.params[0].text) ||
                    (strstr(mpp.params[0].text,"BEFRE")==mpp.params[0].text) ||
                    (strstr(mpp.params[0].text,"RETT" )==mpp.params[0].text)
                ) &&
                (
                    (strstr(mpp.params[mpp.paranz-1].text,"BENOI")==mpp.params[mpp.paranz-1].text) ||
                    (strstr(mpp.params[mpp.paranz-1].text,"MANDE")==mpp.params[mpp.paranz-1].text)
                )
            ) ||
            (
                (
                    (strstr(mpp.params[0].text,"OPEN" )==mpp.params[0].text) ||
                    (strstr(mpp.params[0].text,"OEFFN")==mpp.params[0].text)
                ) &&
                (
                    (strstr(mpp.params[mpp.paranz-1].text,"CELL" )==mpp.params[mpp.paranz-1].text) ||
                    (strstr(mpp.params[mpp.paranz-1].text,"PRISO")==mpp.params[mpp.paranz-1].text) ||
                    (strstr(mpp.params[mpp.paranz-1].text,"ZELLE")==mpp.params[mpp.paranz-1].text) ||
                    (strstr(mpp.params[mpp.paranz-1].text,"GEFAE")==mpp.params[mpp.paranz-1].text)
                )
            )
        )
        ) free=0;
    } //

    if (free <= 0) return 0; // not understood

    int8_t answeredcorrectly=0;
    int32_t tries=2;
    if (difficultyLevel == MP_LEVEL_EASY) tries=3;
    LANGUAGEDE("\nDu hast ","\nYou have ");
    printf("%i",tries);
    LANGUAGEDE(" Versuche, bis der Alarm losgeht und Du an Deinen Startpunkt\nzurueckteleportiert wirst.",
        " tries until an alarm will go off and you will be teleported back to your starting room.");
    printf("\n");

    for(int32_t k=1;k<=tries;k++)  {
        if (answeredcorrectly > 0) break;

        // free Benout: answer question
        LANGUAGEDE("\nDu musst diese Frage beantworten:\n","\nYou have to answer a question:\n")
        int8_t correct=0;
        if (qa) correct=qa->answer();

        if (correct > 0) { answeredcorrectly=1; break; }

        // incorrect
        LANGUAGEDE("\n\nLeider falsch.\n","\n\nIncorrect answer.\n");

    } //

    if (answeredcorrectly > 0) {
        hero.tasksuccessfull=1;
        return 1; // understood
    } else {
        LANGUAGEDE("\n*** Du wirst nun zurueckteleportiert an den Spielstart.",
            "*** You will be teleported back to the start of the game.");
        hero.location_roomid=hero.location0_roomid;
        hero.location_compid=hero.location0_compid;
        return 1; // understood
    }

    return 0;

}

int8_t mpObjTransmitter::saveGameState(FILE* f) {
    // nothing to store here
    return 1;
}

int8_t mpObjTransmitter::loadGameState(FILE* f) {
    // nothing to load here
    return 1;
}

int8_t mpObjTransmitter::getDescr_T(DynSlowString& T) {
    T.setEmpty();

    if ( (target_compid >= 0) && (target_roomid >= 0) ) {
        if (language == MP_DEUTSCH) T.add("Transmitter betriebsbereit");
        else T.add("active transmitter");
    } else {
        if (language == MP_DEUTSCH) T.add("desaktivierter Transmitter");
        else T.add("inactive transmitter");
    }

    return 1;
}

int8_t mpObjTransmitter::parseCommand_ACR(
    mpParams& mpp,
    const int32_t herocompid,   // not relevant here
    const int32_t heroroomid    // not relevant here
) {

    // treats commands USE TRANSMITTER, BENUTZE TRANSMITTER
    // VERWENDE TRANSMITTER
    // does not check whether the current room has a transmitter, this
    // has to be done externally

    if (
        (mpp.contains_A("ACTIVAT") > 0) ||
        (mpp.contains_A("AKTIVIE") > 0)
    ) {
        LANGUAGEDE("Es ist nicht moeglich, diesen Transmitter zu aktivieren.","It is not possible to activate this transmitter.")
        return 1;
    }

    int8_t commanduse=1;
    if (mpp.paranz < 2) commanduse=0;
    if (commanduse > 0) {
        if  ( !(
                (strstr(mpp.params[0].text,"USE")==mpp.params[0].text) ||
                (strstr(mpp.params[0].text,"NUTZ")==mpp.params[0].text) ||
                (strstr(mpp.params[0].text,"BENUTZ")==mpp.params[0].text) ||
                (strstr(mpp.params[0].text,"VERWEND")==mpp.params[0].text)
                )
        ) commanduse=0;
    }

    if (commanduse > 0) {
        if (strstr(mpp.params[mpp.paranz-1].text,"TRANSMIT") != mpp.params[mpp.paranz-1].text) commanduse=0;
    }

    if (commanduse > 0) {
        if ( (target_compid < 0) || (target_roomid < 0) ) {
            LANGUAGEDE("*** Kein Transmitterziel vorhanden.","*** No destination possible.")
            globalwaittime=WAITTIME1;
            return 1; // understood
        }

        // change location of hero
        hero.location_compid=target_compid;
        hero.location_roomid=target_roomid;

        LANGUAGEDE("*** Ich teleportiere.","*** Teleporting.")
        globalwaittime=WAITTIME1;
        return 1; // understood

    } // USE TRANSMITTER

    return 0;

}

int8_t mpObjCaseDevicePart::saveGameState(FILE* f) {
    if (!f) return 0;

    WRITETYPE(int8_t,f,locked)
    WRITETYPE(int32_t,f,partnumber)

    return 1;

}

int8_t mpObjCaseDevicePart::loadGameState(FILE* f) {
    if (!f) return 0;

    READTYPE(int8_t,f,locked)
    READTYPE(int32_t,f,partnumber)

    return 1;

}

int8_t mpObjCaseDevicePart::parseCommand_ACR(
    mpParams& mpp,
    const int32_t acomp,
    const int32_t aroom
) {
    // look at/in box
    // look at device
    // take,grab device

    if (mpp.paranz < 2) return 0; // not understandable

    int8_t atbox=0,atdevice=0;

    if (
        (mpp.contains_A("BOX") > 0) ||
        (mpp.contains_A("CASE") > 0) ||
        (mpp.contains_A("KISTE") > 0) ||
        (mpp.contains_A("TRUHE") > 0)
    ) atbox=1;

    if (
        (mpp.contains_A("DEVICE") > 0) ||
        (mpp.contains_A("PART") > 0) ||
        (mpp.contains_A("TEIL") > 0) || // also BAUTEIK
        (mpp.contains_A("GERAET") > 0) ||
        (mpp.contains_A("STUECK") > 0)
    ) atdevice=1;

    if (
        (strstr(mpp.params[0].text,"LOOK")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"VIEW")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"SCHAU")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"BLICK")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"BETRACHT")==mpp.params[0].text)
    ) {
        if ( (atbox > 0) && (atdevice > 0) ) return 0; // not clear at what

        // box or device, locked or open
        if (locked > 0) {
            if (atbox > 0) {
                LANGUAGEDE("Darauf steht eine Aufforderung, die Kiste zu oeffnen.","Printed on the box is a suggestion to simply open it.")
                globalwaittime=WAITTIME1;
                return 1;
            }

            return 0;
        } // locked

        // open

        if (atbox > 0) {
            if (partnumber > 0) {
                LANGUAGEDE("Die Kiste ist geoeffnet. Es liegt ein elektronisches\nBauteil darin.",
                    "The box is open and contains part of an electronic device.");
                globalwaittime=WAITTIME1;
                return 1;
            } else {
                // empty
                LANGUAGEDE("Die Kiste ist geoeffnet und leer.","The box is open and empty.")
                globalwaittime=WAITTIME1;
                return 1;
            }
        }
        //
        else if (atdevice > 0) {
            if (partnumber <= 0) return 0; // not undferstood
            DynSlowString A,B;
            A.setEmpty();
            A.add("Es sieht aus wie das Bauteil zu einem Messgeraet.\nDie Ziffer ");
            A.add_int(partnumber);
            A.add(" ist darauf geschrieben.");
            B.setEmpty();
            B.add("Looks like an electronic part of a measuring device.\nIt reads the digit ");
            B.add_int(partnumber);
            B.add(".");
            LANGUAGEDE(A.text, B.text);
            globalwaittime=WAITTIME1;
            return 1;
        } // device

        return 0; //

    } // view

    // open
    if (
        (strstr(mpp.params[0].text,"OPEN")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"OEFFN")==mpp.params[0].text)
    ) {
        if (atbox <= 0) return 0;

        // answer question
        if (locked <= 0) {
            LANGUAGEDE("\nDie Kiste ist bereits offen.","\nThe box is already opened.")
            globalwaittime=WAITTIME1;
            return 1;
        }

        LANGUAGEDE("\n\n\n\n\n\nEin Display fordert zum Beantworten einer Frage auf:\n\n","\n\n\n\n\n\nA display demands to answer a question:\n\n")

        int8_t correct=0;
        if (qa) correct=qa->answer();

        if (correct <= 0) {
            LANGUAGEDE("\nLeider war diese Antwort falsch.\n","\nUnfortunately this answer was incorrect.\n");
            globalwaittime=WAITTIME1;
            return 1;
        }

        LANGUAGEDE("Korrekt.","Correctly answered.")
        globalwaittime=WAITTIME1;

        // korrekte Antwort
        locked=0; // now opened

        return 1;
    } // open

    // grab
    if (
        (strstr(mpp.params[0].text,"GRAB")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"TAKE")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"NIMM")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"NEHM")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"HOLE")==mpp.params[0].text)
    ) {
        if (atbox > 0) {
            LANGUAGEDE("Die Box ist zu schwer.","The box is way too heavy to carry.")
            globalwaittime=WAITTIME1;
            return 1;
        }

        if (locked > 0) return 0; // must be open
        if (partnumber <= 0) return 0; // empty

        // does hero already carry this part (from a different component)
        if ( (partnumber < 1) || (partnumber > 3) ) { printf("\nerror 26.\n"); exit(99); }

        if (hero.dev_part[partnumber] > 0) {
            LANGUAGEDE("\nDu traegst bereits dieses Teil.","You're already owning that part.")
            globalwaittime=WAITTIME1;
            return 1;
        }

        hero.dev_part[partnumber]=1;
        partnumber=0; // now box empty
        hero.testDetectorFullyAssembled();

        return 1;

    } // take

    return 0;
}

int8_t mpObjCaseDevicePart::getDescr_T(DynSlowString& T) {
    T.setEmpty();

    if (locked > 0) {
        if (language == MP_DEUTSCH) {
            T.add("eine verschlossene grosse Kiste");
        } else {
            T.add("a large locked box");
        }

        return 1;
    }

    // open, part still present?
    if (partnumber > 0) {
        if (language == MP_DEUTSCH) {
            T.add("eine offene Kiste und ein elektronisches Bauteil mit Aufschrift \'");
            T.add_int(partnumber);
            T.add("\'");
        } else {
            T.add("an open box and an electronic device part inscribed \'");
            T.add_int(partnumber);
            T.add("\'");
        }

        return 1;

    } //

    // empty
    if (language == MP_DEUTSCH) {
        T.add("eine offene, aber leere Kiste");
    } else {
        T.add("an open but empty box");
    }

    return 1;
}

int8_t mpQuestionQA::answer(void) {
    // ret: -1 => error, 0 => incorrect answer, >0 => correct
    // answerD,answerD

    LANGUAGEDE(questionD.text,questionE.text);

    if (abracadabra > 0) {
        LANGUAGEDE("\n\nDas magische Orakel meldet die korrekte Anwort: ","\n\nThe magic oracle tells the correct answer: ")
        LANGUAGEDE(answerD.text,answerE.text);
        printf("\n\n");
    }

    LANGUAGEDE("\n\n  Deine Antwort> ","\n\n  Your answer> ");

    char ans[256];
    fgets(ans,80,stdin);

    if (strlen(ans) <= 0) return 0; // incorrect
    chomp(ans);

    if (strlen(ans) <= 0) return 0; // incorrect
    upper(ans); deleteSpaces(ans);

    if (strlen(ans) <= 0) return 0; // incorrect

    int8_t correct=0;
    if ( (!strcmp(ans,answerD.text)) || (!strcmp(ans,answerE.text)) ) correct=1;

    return correct;

};

int8_t mpQuestionMultipleChoice::answer(void) {
    LANGUAGEDE(questionD.text,questionE.text);
    printf("\n");
    for(int32_t k=0;k<MP_ANZ_MULTIPLECHOICE;k++) {
        if (strlen(mchoice[k].text) > 0) {
            printf("\n  (%i) %s",k,mchoice[k].text);
        }
    } // k

    if (abracadabra > 0) {
        LANGUAGEDE("\n\nDas magische Orakel meldet die korrekte Anwort: ","\n\nThe magic oracle tells the correct answer: ")
        printf("  %i\n\n",mchoice_correct);
    }

    LANGUAGEDE("\n\n  Deine Antwort> ","\n\n  Your answer> ");

    char ans[256];
    fgets(ans,80,stdin);
    if (strlen(ans) <= 0) return 0; // incorrect

    chomp(ans);
    if (strlen(ans) <= 0) return 0; // incorrect

    upper(ans);
    if (strlen(ans) <= 0) return 0; // incorrect

    deleteSpaces(ans);
    if (strlen(ans) <= 0) return 0; // incorrect

    int8_t correct=0;
    int32_t a;
    if (sscanf(ans,"%i",&a) == 1) if (a == mchoice_correct) correct=1;

    return correct;

};

int8_t mpObjNoteInCase::saveGameState(FILE* f) {
    if (!f) return 0;

    WRITETYPE(int8_t,f,locked)

    return 1;

}

int8_t mpObjNoteInCase::loadGameState(FILE* f) {
    if (!f) return 0;

    READTYPE(int8_t,f,locked)

    return 1;

}

int8_t mpObjNoteInCase::parseCommand_ACR(
    mpParams& mpp,
    const int32_t acomp,
    const int32_t room
) {

    int8_t opencommand=0,readcommand=0,boxcommand=0,notecommand=0;

    if (
        (strstr(mpp.params[0].text,"OPEN")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"OEFFN")==mpp.params[0].text)
    ) opencommand=1;

    if (
        (strstr(mpp.params[0].text,"LOOK")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"READ")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"SCHAU")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"BLICK")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"KUCK")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"LESE")==mpp.params[0].text) ||
        (strstr(mpp.params[0].text,"LIES")==mpp.params[0].text)
    ) readcommand=1;

    if (
        (mpp.contains_A("NOTE") > 0) ||
        (mpp.contains_A("PAPER") > 0) ||
        (mpp.contains_A("NOTIZ") > 0) ||
        (mpp.contains_A("AUFSCHR") > 0) ||
        (mpp.contains_A("ZETTEL") > 0) ||
        (mpp.contains_A("PAPIER") > 0)
    ) notecommand=1;

    if (
        (mpp.contains_A("BOX") > 0) ||
        (mpp.contains_A("KISTE") > 0)
    ) boxcommand=1;

    if (locked > 0) {
        if ( (opencommand > 0) && (boxcommand > 0) ) {
            LANGUAGEDE("\n\n\n\n\n\nEin Display fordert zum Beantworten einer Frage auf:\n\n","\n\n\n\n\n\nA display demands to answer a question:\n\n")

            int8_t correct=0;
            if (qa) correct=qa->answer();

            if (correct > 0) {
                LANGUAGEDE("*** Die Kiste oeffnet sich.","*** The box opens.")
                globalwaittime=WAITTIME1;
                locked=0;
                return 1;
            }

            LANGUAGEDE("Die Antwort war falsch.","The answer was incorrect.");
            globalwaittime=WAITTIME1;

            return 1;
        }

        return 0;

    } else {
        if ( (readcommand > 0) && (notecommand > 0) ) {
            LANGUAGEDE("Die Notiz lautet:\n  \"","The note reads:\n  ");
            LANGUAGEDE(noteD.text,noteE.text);
            printf("\"\n");
            globalwaittime=WAITTIME1;

            return 1;
        }

        return 0;

    } // open

    return 0;
}

int8_t mpObjNoteInCase::getDescr_T(DynSlowString& T) {
    T.setEmpty();

    if (locked > 0) {
        // locked
        if (language == MP_DEUTSCH) T.add("eine verschlossene Kiste");
        else T.add("a locked box");

        return 1;

    } else {
        if (language == MP_DEUTSCH) {
           T.add("eine geoeffnete Kiste mit einer Notiz:\n  \"");
           T.add(noteD);
           T.add("\"");
        } else {
           T.add("an open box with a note reading´\n  \"");
           T.add(noteE);
           T.add("\"");
        }

        return 1;

    } // open

    return 1;

}

int8_t mpHero::saveGameState(FILE* f) {
    // ret: <= 0 => error, > 0 => success
    if (!f) return 0;

    WRITETYPE(int32_t,f,location0_compid)
    WRITETYPE(int32_t,f,location0_roomid)
    WRITETYPE(int32_t,f,location_compid)
    WRITETYPE(int32_t,f,location_roomid)
    WRITETYPE(uint8_t,f,device_multiplierDetector)
    WRITETYPE(int8_t,f,tasksuccessfull)
    for(int32_t k=0;k<=MP_DEVICEPARTS;k++) {
        WRITETYPE(int8_t,f,dev_part[k]);
    }

    return 1;

}

int8_t mpHero::loadGameState(FILE* f) {
    // ret: <= 0 => error, > 0 => success
    if (!f) return 0;

    READTYPE(int32_t,f,location0_compid)
    READTYPE(int32_t,f,location0_roomid)
    READTYPE(int32_t,f,location_compid)
    READTYPE(int32_t,f,location_roomid)
    READTYPE(uint8_t,f,device_multiplierDetector)
    READTYPE(int8_t,f,tasksuccessfull)
    for(int32_t k=0;k<=MP_DEVICEPARTS;k++) {
        READTYPE(int8_t,f,dev_part[k]);
    }

    return 1;

}

void mpHero::testDetectorFullyAssembled(void) {
    if (device_multiplierDetector != MP_NODEVICE) return;

    int8_t alle=1;
    for(int32_t k=1;k<=MP_DEVICEPARTS;k++) {
        if (dev_part[k] <= 0) { alle=0; break; }
    } // k

    if (alle > 0) {
        LANGUAGEDE("Der Multiplier-Detekter ist nun funktionsbereit.","The multiplier detector is now working.")
        device_multiplierDetector=MP_DEVICEAUTOMATIC;
    }

}

mpHero::mpHero() {
    #define MPHEROINIT \
    {\
        location_compid=0;\
        location_roomid=0;\
        device_multiplierDetector=MP_NODEVICE;\
        tasksuccessfull=0;\
        for(int32_t tmpk=0;tmpk<=MP_DEVICEPARTS;tmpk++) dev_part[tmpk]=0;\
    }

    MPHEROINIT
}

void mpHero::init(void) {
    MPHEROINIT
}

void mpStart(void) {
    for(int32_t k=0;k<MP_LINELEN;k++) {
        line[k]='-';
        line[k+1]=0;
    } // k

    printf("\n\n%s\nMandelPrison - Free Benoit!\n%s\n\nPlease choose language\n  (d)eutsch (ohne Umlaute)\n  (e)nglish\n> ",line,line);
    const int32_t CMDLEN=1024,CMDGET=200;
    char cmd[CMDLEN];
    fgets(cmd,CMDGET,stdin);
    if (strlen(cmd) <= 0) sprintf(cmd,"E");

    chomp(cmd);
    if (strlen(cmd) <= 0) sprintf(cmd,"E");

    upper(cmd);
    if (strlen(cmd) <= 0) sprintf(cmd,"E");

    language=MP_DEUTSCH;
    if (cmd[0] == 'E') language=MP_ENGLISCH;

    LANGUAGEDE("\nWelchen Schwierigkeitsgrad?","\nWhich level of difficulty?")
    printf(" (%i-%i)\n> ",MP_LEVEL_MIN,MP_LEVEL_MAX);
    int32_t k;
    difficultyLevel=MP_LEVEL_EASY;
    fgets(cmd,CMDGET,stdin);
    if (strlen(cmd) <= 0) sprintf(cmd,"0");

    chomp(cmd);
    if (strlen(cmd) <= 0) sprintf(cmd,"0");

    upper(cmd);
    if (strlen(cmd) <= 0) sprintf(cmd,"0");

    if (sscanf(cmd,"%i",&k) == 1) {
        if ( (k >= MP_LEVEL_MIN) && (k <= MP_LEVEL_MAX) ) difficultyLevel=k;
    }

    LANGUAGEDE("\ngewaehlt ","\nchosen ")
    LANGUAGEDE(levelStrDE[difficultyLevel],levelStrEN[difficultyLevel])

    // init Playground, Components, Rooms
    playground.initComponents( MP_COMPANZ );

    // Component 0: period-doubling 64 at c=-1.4009619629448410402961163158698065994827705204271881893204558985104252699305954409
    printf("\n\ninitialize playground ... ");

    MEMORY(playground.components[0]=createComponent0(),16)
    MEMORY(playground.components[1]=createComponent1(),16)
    MEMORY(playground.components[2]=createComponent2(),16)
    MEMORY(playground.components[3]=createComponent3(),16)
    MEMORY(playground.components[4]=createComponent4(),16)
    MEMORY(playground.components[5]=createComponent5(),16)
    MEMORY(playground.components[6]=createComponent6(),16)
    MEMORY(playground.components[7]=createComponent7(),16)
    MEMORY(playground.components[8]=createComponent8(),16)
    MEMORY(playground.components[9]=createComponent9(),16)
    MEMORY(playground.components[10]=createComponent10(),16)
    MEMORY(playground.components[11]=createComponent11(),16)
    MEMORY(playground.components[12]=createComponent12(),16)
    MEMORY(playground.components[13]=createComponent13(),16)
    MEMORY(playground.components[14]=createComponent14(),16)
    MEMORY(playground.components[15]=createComponent15(),16)

    printf("\ninitialize our hero ... ");
    hero.init();

    // initialize our Hero
    switch (difficultyLevel) {
        case MP_LEVEL_EASY: {
            // period 64 in period-doubling cascade on x-axis
            hero.location0_compid=hero.location_compid=0;
            hero.location0_roomid=hero.location_roomid=5; // starting

            break;
        }
        case MP_LEVEL_INTERMEDIATE: {
            // period 105 above main cardioid, exit only per transmitter
            hero.location0_compid=hero.location_compid=9;
            hero.location0_roomid=hero.location_roomid=8; // starting
            break;
        }
        case MP_LEVEL_COMPLICATED: {
            // period 84 next to period-6 next to period-3 cardioid
            hero.location0_compid=hero.location_compid=14;
            hero.location0_roomid=hero.location_roomid=5; // starting
            break;
        }

        default: {
            printf("\nerror. not yet implemented\n");
            exit(99);
        }
    };

}

void mpCommandLoop(void) {
    const int32_t CMDLEN=1024,CMDGET=200;
    char cmd[CMDLEN];
    DynSlowString T,Tmult;
    T.setEmpty();
    Tmult.setEmpty();
    mpParams* mpp=new mpParams;
    MEMORY(mpp,10)

    #define PADDINGPRINT(WW) \
    {\
        if ( (WW) ) {\
            int32_t tmpw=MP_LINELEN - strlen(WW);\
            tmpw >>= 1;\
            for(int32_t tmpk=0;tmpk<tmpw;tmpk++) printf(" ");\
        }\
    }

    while (1) {
        if (hero.tasksuccessfull > 0) break;

        // print current location and interior of room
        printf("\n\n\n%s\n",line);
        playground.getCurrentLocation_T2(T,Tmult);
        PADDINGPRINT(T.text)
        printf("%s\n",T.text);

        if (Tmult.text) if (strlen(Tmult.text) > 0) {
            PADDINGPRINT(Tmult.text)
            printf("%s\n",Tmult.text);
        }

        printf("%s\n\n",line);

        // parts
        T.setEmpty();
        if (hero.device_multiplierDetector == MP_NODEVICE) {
            int32_t pn=0;
            for(int32_t k=1;k<=MP_DEVICEPARTS;k++) {
                if (hero.dev_part[k] > 0) pn++;
            } // k

            if (pn > 0) {
                char w[256];
                sprintf(w,"%.0lf%%",100.0*(double)pn/(double)MP_DEVICEPARTS);
                if (language == MP_DEUTSCH) {
                    T.add("Multiplier-Detektor ");
                    T.add(w);
                    T.add(" fertiggestellt\n");
                } else {
                    T.add("Multiplier detector ");
                    T.add(w);
                    T.add(" assembled\n");
                }
            }

        } else
        if (hero.device_multiplierDetector == MP_DEVICEMANUAL) {
            if (language == MP_DEUTSCH) {
                T.add("Multiplier-Detektor arbeitsbereit");
            } else {
                T.add("Multiplier detector ready to be used");
            }
        }

        if (T.text) if (strlen(T.text) > 0) {
            printf("%s\n\b",T.text);
        }

        // which doors are there
        LANGUAGEDE("Wege nach:","Doors:")
        playground.getDoors_T(T);
        printf("%s",T.text);

        // what's inside the room
        printf("\n\n");
        LANGUAGEDE("Du siehst:\n","You see:\n")
        playground.getSight_T(T);
        if (strlen(T.text) <= 0) {
            LANGUAGEDE("nichts","nothing")
        } else {
            printf("%s",T.text);
        }

        // command
        printf("\n\n> ");
        fgets(cmd,CMDGET,stdin);
        if (strlen(cmd) <= 0) continue;

        printf("\n");

        chomp(cmd);

        if (strlen(cmd) <= 0) continue;
        upper(cmd);

        // if it consist of one letter => assume GO DIRECION
        if (strlen(cmd) == 1) {
            char ch=cmd[0];
            if (language == MP_DEUTSCH) {
                sprintf(cmd,"GEHE %c",ch);
            } else {
                sprintf(cmd,"GO %c",ch);
            }
        }

        if (!strcmp(cmd,"LOAD")) {
            FILE *f=fopen("mandelp.plg","rb");
            if (!f) {
                printf("\nerror. could not open file for loading.\n");
                continue;
            }
            int8_t error=0;
            if (hero.loadGameState(f) <= 0) error=1;
            if (playground.loadGameState(f) <= 0) error=1;

            fclose(f);

            if (error <= 0) printf("\ncurrent game state loaded.\n"); else printf("\nerror. not able to load.\n");
            continue;
        } else
        if (!strcmp(cmd,"SAVE")) {
            FILE *f=fopen("mandelp.plg","wb");
            if (!f) {
                printf("\nerror. could not open file for storage.\n");
                continue;
            }
            int8_t error=0;
            if (hero.saveGameState(f) <= 0) error=1;
            if (playground.saveGameState(f) <= 0) error=1;

            fclose(f);

            if (error <= 0) printf("\ncurrent game state stored.\n"); else printf("\nerror. not able to store.\n");
            continue;
        }

        // extract parameters
        if (mpp->extractParams_A_nonconst(cmd) <= 0) { printf("\nerror 11\n"); exit(99); }

        if (mpp->paranz <= 0) continue; // just agaim

        if (
            (strstr(mpp->params[0].text,"END" )==mpp->params[0].text) ||
            (strstr(mpp->params[0].text,"QUIT")==mpp->params[0].text)
        ) break;

        // now parse commands
        int32_t ret=playground.parseCommand_ACR(*mpp,hero.location_compid,hero.location_roomid);
        if (ret <= 0) {
            LANGUAGEDE("*** Ich verstehe nicht.","*** I do not understand.")
            _sleep(WAITTIME0);
        }

        if ( (ret > 0) && (globalwaitflag > 0) && (globalwaittime > 0) ) {
            _sleep(globalwaittime);
        }

    } // while

    if (hero.tasksuccessfull > 0) {
        printf("\n\n\n\n%s\n",line);
        LANGUAGEDE("Aufgabe erfolgreich geloest.","Your task has been successfully completed.");
        printf("\n%s\n\n",line);
    }

    delete mpp;

}

void mpEnd(void) {
    // nothing to do
}

int32_t sum_int32t(
	const int32_t a,
	const int32_t b
) {
	int64_t sum=(int64_t)a + (int64_t)b;
	if (
		(sum < (-INT32MAX)) ||
		(sum >   INT32MAX)
	) {
		printf("\nError. Overflow by int32 addition\n");
		exit(99);
	}

	return (int32_t)sum; // lower half
}

// DynSlowString
void DynSlowString::setEmpty(void) {
	if (text) text[0]=0;
}

void DynSlowString::add_int(const int64_t aw) {
    char tt[256];
    sprintf(tt,"%I64d",aw);
    add(tt);
}

DynSlowString::DynSlowString(const int32_t amem) {
	memory=amem;
	text=new char[memory];
	if (!text) {
		printf("\nError. Memory. DynSlowString.\n");
		exit(99);
	}
}

DynSlowString::DynSlowString() {
	memory=0;
	text=NULL;
}

DynSlowString::~DynSlowString() {
	if (text) delete[] text;
}

void DynSlowString::add(const char ac) {
	char tmp[16];
	sprintf(tmp,"%c",ac);

	add(tmp);
}

void DynSlowString::add(const char* atext) {
	if (!atext) return;

	int32_t ttlen=strlen(atext);
	if (ttlen <= 0) return;

	int32_t currentlen;
	if (text) currentlen=strlen(text); else currentlen=0;

	if (
		(sum_int32t(currentlen,ttlen) > (memory-8) ) ||
		(!text)
	) {
		// new memory necessary
		int32_t mem0=sum_int32t(currentlen,ttlen);
		memory = sum_int32t(mem0,mem0);
		char* oldtext=text;
		text=new char[memory];
		if (!text) {
			printf("\nError. DynSlowString::add.\n");
			exit(99);
		}
		if (oldtext) {
			strcpy(text,oldtext);
			delete[] oldtext;
		} else {
			text[0]=0;
		}
	} // allocating

	// enough memory allocated
	sprintf(&text[currentlen],"%s",atext);
}

void DynSlowString::add(DynSlowString& as) {
	if (as.text) add(as.text);
}

int8_t mpDoor::saveGameState(FILE* f) {
    // nothingf to store as doors do not change
    return 1;
}

int8_t mpDoor::loadGameState(FILE* f) {
    // nothing to load
    return 1;

}

// main
int32_t main(int argc,char** argv) {

    mpStart();
    mpCommandLoop();
    mpEnd();

	return 0;
}


