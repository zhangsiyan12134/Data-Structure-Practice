/*********************************************************************
  Adpated from:

  Filename:  predator.cpp
  Chapter:   8      Inheritance
  C++ for C Programmers, Edition 3     By Ira Pohl
********************************************************************/
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

class creature;  // forward declarations

/** a world consists of a matrix of pointers to creatures */
class world {

private:
    /** the world is an len by len matrix of pointers to creatures */
    int len;

    /** matrix of pointers to creatures stored by rows in a vector */
    vector<creature*> mat;

public:
    /** create world with len = size and possibly initialize*/
    world(int size, int init = 0);

    /** display the world to out and a creature count summary to sout */
    void display(ostream& out, ostream& sout);

    /**  allows easy access to the matrix */
    creature*& at(int i, int j) {return mat[len*i + j];}

    /** return len */
    int getlen(void) {return len;}
};

/** The ecosystem has a world which evolves through a number of cycles */
class ecosys {
private:
    /** The current world */
    world w;

    /** Number of cycles to simulate */
    int cycles;

    /** Compute w from old using creature::next() */
    void update(void);

public:
    /** set the size of the world and number of cycles*/
    ecosys(int size, int numcycles);

    /** evolve through cycles */
    void evolve(void);
};

/** abstract base class of creatures */
class creature {

friend class ecosys;
friend class world;

public:
    /** construct creature at position row = r, col = c */
    creature(int r, int c) {row = r; col = c; }

    /** type identification */
    virtual char who(void)  = 0;

    /** the creature changes via this function at the next time period */
    virtual creature* next(world& w) = 0;

protected:
    /** vertical position of the creature */
    int row;

    /** horizontal position of the creature */
    int col;

    /** number of positions to scan in each direction when changing */
    static int look;

    /** gives the count of creatures of this type in the world w contained in
        a small box of side length 2*look+1 positions around this creature */
    int count( world& w, char type);
};

/** coyote eat fox and rabbits */
class coyote : public creature {
public:
    coyote(int r, int c, int a = 0) : creature(r,c) {age = a;  }
    char who()  { return 'c'; }
    creature* next(world& w);

private:
    /** used to decide on dying */
    int  age;

    /** foxes die at this age */
    static int lifespan;
};

/** foxes eat rabbits */
class fox : public creature {
public:
    fox(int r, int c, int a = 0) : creature(r,c) {age = a;  }
    char who()  { return 'f'; }
    creature* next(world& w);

private:
    /** used to decide on dying */
    int  age;

    /** foxes die at this age */
    static int lifespan;
};

/** rabbits eat grass */
class rabbit : public creature {
public:
    rabbit(int r, int c, int a = 0) : creature(r,c) {age = a;  }
    char who()  { return 'r'; }
    creature* next(world& w);

private:
    /** used to decide on dying */
    int  age;

    /** rabbits die at this age */
    static int lifespan;
};

/** grass is the only plant life*/
class grass : public creature  {
public:
    grass(int r, int c) : creature(r,c) { }
    char who()  { return 'g'; }
    creature* next(world& w);
};

/** nothing lives here */
class empty : public creature {
public:
    empty(int r, int c) : creature(r,c) { }
    char who()  { return ' '; }
    creature* next(world& w);
};

int main()
{
    int numcycles;
    int size;
    unsigned seed;

    /** get the ecosystem parameters */
    cout << "Enter number of cycles : "; cin >> numcycles;
    cout << "Enter world size : "; cin >> size;

    /** seed the random number generator using the current time */
    srand(time(NULL));

    //cout << "Enter a seed: "; cin >> seed;
    //srand(seed);

    /** create an ecosystem and start evolving */
    ecosys x(numcycles, size);
    x.evolve();

    return 0;
}

//////////////////////// static members /////////////////////////////////

int rabbit::lifespan = 2;
int fox::lifespan = 4;
int coyote::lifespan = 4;
int creature::look = 1;

/////////////////// implementation of creature ////////////////////////////

/** count creatures of this type in a box of length 2*look+1 on a side */
int creature::count( world& w,  char type)
{
    int  i, j, r, c;
    int n = w.getlen();
    int sum = 0;

    for (i = -look; i <= look; i++) { // the box is 2*look+1 on a side
        for ( j = -look; j <= look; j++){
            r = row+i;
            c = col+j;
            if(0 <= r && r < n && 0 <= c && c < n) {
                if( w.at(r,c)->who() == type) sum++;
            }
        }
    }
    return sum;
}

/////////////////////// implementation of empty /////////////////////////

/** creatures pop up spontaneously in a rank order */
creature* empty::next(world& w) // how to fill an empty position
{

    if( count(w, 'c') >1 ) {            // coyote eat rabbits
        return (new coyote(row, col));
    }else if( count(w, 'f') > 1 ){      // fox
        return (new fox(row, col));
    }else if( count(w, 'r') > 1 ){     // rabbit
        return (new rabbit(row, col));
    }else if( count(w, 'g') > 0 ) {   // grass
        return (new grass(row, col));
    }else {                            // empty
        return (new empty(row, col));
    }
}

/////////////////////// implementation of grass /////////////////////////

/** if rabbit count >= grass count grass dies */
creature* grass::next(world& w)
{
    if( count(w, 'r') >= count(w, 'g') ) {   // eat grass
        return (new empty(row, col));
    }else {
        return (new grass(row, col));
    }
}

/////////////////////// implementation of rabbit /////////////////////////

/** if fox count >= rabbit count then rabbit dies */
creature* rabbit::next(world& w)
{
    if( count(w, 'c') >= count(w, 'r') ) {         // coyote eat rabbits
        return (new empty(row, col));
    }else if( count(w, 'f') >= count(w, 'r') ) {   // foxes eat rabbits
        return (new empty(row, col));
    }else if(age >= lifespan) {                    // rabbit is too old
        return (new empty(row, col));
    }else {
        return (new rabbit(row, col, age + 1));    // rabbit is 1 year older
    }
}

/////////////////////// implementation of fox /////////////////////////

/** if there are too many foxes or fox is too old then fox dies */
creature* fox::next(world& w)
{
    if( count(w, 'c') >= count(w, 'f') ) {       // coyote eat foxes
        return (new empty(row, col));
    }else if( count(w, 'f') > ((2*look+1)*(2*look+1))/2 + 1) {
        return (new empty(row, col));            // too many foxes
    }else if(age >= lifespan) {
        return (new empty(row, col));            // fox is too old
    }else {
        return (new fox(row, col, age + 1));     // fox is 1 year older
    }
}

/////////////////////// implementation of coyote /////////////////////////

creature* coyote::next(world& w)
{
    if( count(w, 'c') > ((2*look+1)*(2*look+1))/2 + 1) {
        return (new empty(row, col));            // too many coyotes
    }else if(age >= lifespan) {
        return (new empty(row, col));            // coyotes is too old
    }else {
        return (new coyote(row, col, age + 1));     // coyotes is 1 year older
    }
}

/////////////////////// implementation of world /////////////////////////

/** world is uninitialized or filled with a random pattern */
world::world(int size, int init) : mat(size*size)
{
    int  i, j, p;
    float t;
    len = size;

    if(init !=0) {   // initialize with random creatures
        for(i = 0; i < len; i++) {
            for( j = 0; j < len; j++) {
                t = rand() *100.0/RAND_MAX;
                delete at(i,j);
                if (t < 8.0) {                // 8% grass
                    at(i,j) = new grass(i, j);
                }else if (t < 12.0) {          // 4% rabbits
                    at(i,j) = new rabbit(i, j);
                }else if(t < 16.0) {           // 4% foxes
                    at(i,j) = new fox(i, j);
                }else if(t < 20.0){            // 4% coyotes
                    at(i,j) = new coyote(i, j);
                }else {                        // 80% empty
                    at(i,j) = new empty(i,j);
                }
            }
        }
    }
}

/** display world to out and summary to sout */
void world::display(ostream& out, ostream& sout)
{
    int i,j;
    int nc = 0; // number of coyotes
    int nf = 0; // number of foxes
    int nr = 0; // number of rabbits
    int ng = 0; // number of grass
    creature* p;
    char type;

    for(i = 0; i < len; ++i) {
        for( j = 0; j < len; j++){
            type = at(i,j)->who();
            out << type;
            if(type == 'c') nc++;
            else if(type == 'f') nf++;
            else if (type == 'r') nr++;
            else if (type == 'g') ng++;
        }
        out << endl;
    }

    out << setw(8) << ng;
    out << setw(8) << nr;
    out << setw(8) << nf;
    out << setw(8) << nc;

    sout << setw(8) << ng;
    sout << setw(8) << nr;
    sout << setw(8) << nf;
    sout << setw(8) << nc;
}

/////////////////////// implementation of ecosys /////////////////////////

ecosys::ecosys(int numcycles, int size) : w(size, 1)
{
    cycles = numcycles;
}

/** go through cycles printing output to files */
void ecosys::evolve(void)
{
    int i=0;
    ofstream fout("ecosysout.txt");
    ofstream sout("summaryout.txt");

    sout << "   cycle   grass rabbits   foxes coyotes\n";
    sout << "----------------------------------------\n";
    fout << "inital world\n";
    sout << setw(8) << i;
    w.display(fout, sout); // show initial state
    sout << "\n";

    for (i = 1; i <= cycles; i++) { //update and display the world each time
        update();
        sout << setw(8) << i;
        fout << "\n\ncycle number " << i << "\n";
        w.display(fout, sout);
        sout << "\n";
    }
}

/** new world is computed from old world */
void ecosys::update(void)
{
    int i, j;
    int n = w.getlen();
    world nw(n); // new world to be created from the current one.


    // compute a new world
    for (i = 0; i < n ; i++) {
        for (j = 0; j < n ; j++) {
            nw.at(i,j) = w.at(i,j)->next(w);
        }
    }

    // now get rid of the old world
    for (i = 0; i < n ; ++i) {
        for (j = 0; j < n ; ++j) {
            delete w.at(i,j);
            w.at(i,j) = nw.at(i,j);
        }
    }
}
