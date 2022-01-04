#include <iostream>
#include<cstring>
#include<string>
#include <iomanip>
#include<vector>
#include<list>
#include<iterator>
#include<map>
#include<set>
#include<fstream>
#include<stdlib.h>
using namespace std;

ifstream fin("zile_sarbatori.in");
ofstream fout("despre_an.out");

class Luna{
private:

    int nrLuna; //numarul lunii
    int nrZile; //numarul de zile
    char* NumeLuna; //numele lunii "Martie"
    int nrActivitati; //cate activitati am avut in luna respectiva
    int sterse; //numarul de evenimente sterse din aceasta luna

public:

//toti SETTERII si GETTERII
    int getnrLuna()
    {
        return this->nrLuna;
    }
    void setnrLuna(int nr)
    {
        this->nrLuna=nr;
    }
    int getnrZile()
    {
        return this->nrZile;
    }
    void setnrZile(int nr)
    {
        this->nrZile=nr;
    }
    char* getNumeLuna()
    {
        return this->NumeLuna;
    }
    void setNumeLuna(char* nume)
    {
        if(this->NumeLuna != NULL)
            delete[] this->NumeLuna;
        this->NumeLuna=new char[strlen(nume)+1];
        strcpy(this->NumeLuna,nume);
    }
    int getnrActivitati()
    {
        return this->nrActivitati;
    }
    void setnrActivitati(int nr)
    {
        this->nrActivitati=nr;
    }
    int getsterse()
    {
        return this->sterse;
    }
    void setsterse(int s)
    {
        this->sterse=s;
    }

    friend ostream& operator<<(ostream& out,const Luna& l);
    friend istream& operator>>(istream& in, Luna& l);
    const Luna operator++(int); //post-incrementare
    const Luna operator--(int); //post-decrementare
    Luna operator+(const Luna& l);
    Luna& operator=(const Luna& l);

    double medie_activitati();

//CONSTRUCTORI
    Luna (const Luna& l)//cc
    {
        this->nrLuna=l.nrLuna;
        this->nrZile=l.nrZile;
        this->NumeLuna=new char[strlen(l.NumeLuna)+1];
        strcpy(this->NumeLuna,l.NumeLuna);
        this->nrActivitati=l.nrActivitati;
        this->sterse=l.sterse;
    }
    Luna() //constructorul fara parametri
    {
        nrLuna=0;
        nrZile=0;
        NumeLuna=new char[strlen("Necunoscut")+1];
        strcpy(NumeLuna,"Necunoscut");
        nrActivitati=0;
        sterse=0;

    }
    Luna(int nrLuna,int nrZile, char* NumeLuna) //constructor cu parametri 1
    {
        this->nrLuna=nrLuna;
        this->nrZile=nrZile;
        this->NumeLuna=new char[strlen(NumeLuna)+1];
        strcpy(this->NumeLuna,NumeLuna);
        nrActivitati=0;
        sterse=0;
    }
    Luna(int nrActivitati, int sterse,int nrLuna,int nrZile,char* NumeLuna) //constructor cu toti parametrii 2
    {
        this->nrActivitati=nrActivitati;
        this->sterse=sterse;
        this->nrLuna=nrLuna;
        this->nrZile=nrZile;
        this->NumeLuna=new char[strlen(NumeLuna)+1];
        strcpy(this->NumeLuna,NumeLuna);
    }
    ~Luna() //destructor
    {
        if (this->NumeLuna != NULL)
            delete[] this->NumeLuna;
    }

};

///functie care imi calculeaza si afiseaza media activitatilor pe zi pentru o luna
double Luna::medie_activitati()
{
    float m_activitati;
    m_activitati=float(this->nrActivitati)/float(this->nrZile);;
    return m_activitati;
}

//OPERATORI
Luna Luna::operator+(const Luna& l)//adun doua luni
    {
        Luna aux(*this);
        aux.nrActivitati=aux.nrActivitati+l.nrActivitati;
        aux.sterse=aux.sterse+l.sterse;
        return aux;
    }
istream& operator>>(istream& in,Luna& l)
{
    cout<<"\nNumarul lunii curente: ";
    in>>l.nrLuna;
    cout<<"\nCate zile are luna? ";
    in>>l.nrZile;
    cout<<"\nCare este numele lunii? ";
    char aux[50];
    in>>aux;
    if ( l.NumeLuna != NULL )
        delete[] l.NumeLuna;
    l.NumeLuna=new char[strlen(aux)+1];
    strcpy(l.NumeLuna,aux);
    return in;
}
ostream& operator<<(ostream& out,const Luna& l)
{
    out<<"\nNumarul lunii curente: "<<l.nrLuna;
    out<<"\nNumarul de zile din luna: "<<l.nrZile;
    out<<"\nNumele lunii: "<<l.NumeLuna;
    out<<"\nNumarul activitati din aceasta luna: "<<l.nrActivitati;
    //out<<"\nNumarul activitati sterse din aceasta luna: "<<l.sterse;
    return out;
}
const Luna Luna::operator++(int)//post-incrementare
{
    Luna aux(*this);
    this->sterse++;
    return aux;
}
const Luna Luna::operator--(int)//post-decrementare
{
    Luna aux(*this);
    this->nrActivitati--;
    return aux;
}
Luna& Luna::operator=(const Luna& l)
    {   if (this != &l)
        {
          if (this->NumeLuna!=NULL)
            delete[] this->NumeLuna;
          this->nrLuna=l.nrLuna;
          this->nrZile=l.nrZile;
          this->NumeLuna=new char[strlen(l.NumeLuna)+1];
          strcpy(this->NumeLuna,l.NumeLuna);
          this->nrActivitati=l.nrActivitati;
          this->sterse=l.sterse;
        }
        return *this;
    }

class An
{
private:

    const int nrAn;
    int nrZile; //cate zile are anul meu
    bool bisect;
    float NrEvenimentePerLuna; //media numarului de evenimente/luna din an
    int ziCurenta;
    int lunaCurenta;
    double NrEvenimenteSterse; //media nr evenimentelor sterse/luna
    string ActivitatePreferata; //persoana isi poate alege o activitate preferata/an
    char TipAn;
    char* numarScris; //'doua mii douzeci si unu'
    Luna* luni;


public:
    static int anCurent;

    const int getnrAn();
    int getnrZile();
    void setnrZile(int n);
    bool getbisect();
    void setbisect(bool b);
    float getNrEvenimentePerLuna();
    void setNrEvenimentePerLuna(float ev);
    int getlunaCurenta();
    void setlunaCurenta(int l);
    int getziCurenta();
    void setziCurenta(int z);
    double getNrEvenimenteSterse();
    void setNrEvenimenteSterse(double st);
    string getActivitatePreferata();
    void setActivitatePreferata(string acv);
    char getTipAn();
    void setTipAn(char t);
    char* getnumarScris();
    void setnumarScris(char* numar);
    Luna* getluni();


    friend ostream& operator<<(ostream& out, const An& a);
    friend istream& operator>>(istream& in, An& a);
    An operator+(const An& a); //adun doua obiecte de tip an
    An& operator=(const An& a);

    string calculeaza_data();
    double medie_activitati_an();

    An();
    An(char* numarScris, int nrZile, bool bisect);
    An(int lunaCurenta,int ziCurenta,float NrEvenimentePerLuna,double NrEvenimenteSterse,string ActivitatePreferata,char TipAn,Luna* luni,char* numarScris, int nrZile, bool bisect);
    An(const An& a);
    ~An();

};

int An::anCurent=2021;

///functie care calculeaza media numarului de activitati din an pe luni
double An::medie_activitati_an()
{
    double suma=0.0;
    for (int i=0;i<12;i++)
        suma=suma+luni[i].medie_activitati();
    return suma/12;
}

///functie care imi determina data calendaristica folosind numarul zilei(si pentru an bisect)
string An::calculeaza_data()
{
    if(this->bisect)
    {
        if(this->ziCurenta>=0 && this->ziCurenta<=31)
            return to_string(this->ziCurenta) + " Ianuarie";
        if(this->ziCurenta>=32 && this->ziCurenta<=60)
            return to_string(this->ziCurenta-31) + " Februarie";
        if(this->ziCurenta>=61 && this->ziCurenta<=91)
            return to_string(this->ziCurenta-60) + " Martie";
        if(this->ziCurenta>=92 && this->ziCurenta<=121)
            return to_string(this->ziCurenta-91) + " Aprilie";
        if(this->ziCurenta>=120 && this->ziCurenta<=152)
            return to_string(this->ziCurenta-121) + " Mai";
        if(this->ziCurenta>=153 && this->ziCurenta<=182)
            return to_string(this->ziCurenta-151) + " Iunie";
        if(this->ziCurenta>=183 && this->ziCurenta<=213)
            return to_string(this->ziCurenta-182) + " Iulie";
        if(this->ziCurenta>=214 && this->ziCurenta<=244)
            return to_string(this->ziCurenta-213) + " August";
        if(this->ziCurenta>=245 && this->ziCurenta<=274)
            return to_string(this->ziCurenta-244) + " Septembrie";
        if(this->ziCurenta>=275 && this->ziCurenta<=305)
            return to_string(this->ziCurenta-274) + " Octombrie";
        if(this->ziCurenta>=306 && this->ziCurenta<=335)
            return to_string(this->ziCurenta-305) + " Noiembrie";
        if(this->ziCurenta>=336 && this->ziCurenta<=366)
            return to_string(this->ziCurenta-335) + " Decembrie";
    }
    else
    {
        if(this->ziCurenta>=0 && this->ziCurenta<=31)
            return to_string(this->ziCurenta) + " Ianuarie";
        if(this->ziCurenta>=32 && this->ziCurenta<=59)
            return to_string(this->ziCurenta-31) + " Februarie";
        if(this->ziCurenta>=60 && this->ziCurenta<=90)
            return to_string(this->ziCurenta-59) + " Martie";
        if(this->ziCurenta>=91 && this->ziCurenta<=120)
            return to_string(this->ziCurenta-90) + " Aprilie";
        if(this->ziCurenta>=121 && this->ziCurenta<=151)
            return to_string(this->ziCurenta-120) + " Mai";
        if(this->ziCurenta>=152 && this->ziCurenta<=181)
            return to_string(this->ziCurenta-151) + " Iunie";
        if(this->ziCurenta>=182&& this->ziCurenta<=212)
            return to_string(this->ziCurenta-181) + " Iulie";
        if(this->ziCurenta>=213 && this->ziCurenta<=243)
            return to_string(this->ziCurenta-212) + " August";
        if(this->ziCurenta>=244 && this->ziCurenta<=273)
            return to_string(this->ziCurenta-243) + " Septembrie";
        if(this->ziCurenta>=274 && this->ziCurenta<=304)
            return to_string(this->ziCurenta-273) + " Octombrie";
        if(this->ziCurenta>=305 && this->ziCurenta<=334)
            return to_string(this->ziCurenta-304) + " Noiembrie";
        if(this->ziCurenta>=335 && this->ziCurenta<=365)
            return to_string(this->ziCurenta-334) + " Decembrie";
    }
}


//OPERATORI
An An::operator+(const An& a) //adun doua obiecte de tip an
{
    An aux(*this);
    aux.ActivitatePreferata=aux.ActivitatePreferata+" si "+a.ActivitatePreferata;
    return aux;
}
istream& operator>>(istream& in, An& a)
{
    cout<<"\nLuna curenta(numar): ";
    in>>a.lunaCurenta;
    cout<<"\nZiua curenta: ";
    in>>a.ziCurenta;
    cout<<"\nActivitate preferata: ";
    in.get();
    char aux[100];
    in.getline(aux,100);
    string s(aux);
    a.ActivitatePreferata=s;
    cout<<"\nNumarul anului scris: ";
    char aux2[100];
    in.getline(aux2,100);
    if(a.numarScris != NULL)
        delete[] a.numarScris;
    a.numarScris=new char[strlen(aux2)+1];
    strcpy(a.numarScris,aux2);


    return in;
}
ostream& operator<<(ostream& out, const An& a)
{
    out<<"Anul: "<<a.nrAn<<endl;
    out<<"\nNumarul de zile: "<<a.nrZile<<endl;
    out<<"\nAnul este bisect? ";
    if (a.bisect)
        out<<"Da"<<endl;
    else
        out<<"Nu"<<endl;
    out<<"\nMedia numarului de evenimente per luna pentru acest an este: "<<a.NrEvenimentePerLuna<<endl;
    out<<"\nMedia numarului de evenimente sterse per luna este: "<<a.NrEvenimenteSterse<<endl;
    out<<"\nActivitatea preferata din acest an este: "<< a.ActivitatePreferata<<endl;
    out<<"\nTipul anului este: "<<a.TipAn<<" \n --Tip l(liber)-media numarului de evenimente per luna <1 \n --Tip n(normal)-media este cuprinsa intre [1,4] \n --Tip o(ocupat)-media >4 "<<endl;
    out<<"\nAnul se scrie: "<<a.numarScris<<endl;
    if (a.luni!=NULL)
    {   out<<"\n\nLunile din an sunt: "<<endl;
        for (int i=0; i<12; ++i)
            out<<a.luni[i]<<'\n';
    }
    out<<endl;
    return out;
}
An& An::operator=(const An& a)
{
    if (this != &a)
    {
        if(this->numarScris != NULL)
            delete[] this->numarScris;
        if(this->luni != NULL)
            delete[] this->luni;
        this->lunaCurenta=a.lunaCurenta;
        this->ziCurenta=a.ziCurenta;
        this->NrEvenimentePerLuna=a.NrEvenimentePerLuna;
        this->NrEvenimenteSterse=a.NrEvenimenteSterse;
        this->ActivitatePreferata=a.ActivitatePreferata;
        this->TipAn=a.TipAn;
        this->luni=new Luna[12];
        for(int i=0; i<12; i++)
            this->luni[i]=a.luni[i];
        this->numarScris=new char[strlen(a.numarScris)+1];
        strcpy( this->numarScris, a.numarScris);
        this->nrZile=a.nrZile;
        this->bisect=a.bisect;
    }
    return *this;
}

//toti SETTERII si GETTERII
const int An::getnrAn()
{
    return this->nrAn;
}
int An::getnrZile()
{
    return this->nrZile;
}
void An::setnrZile(int n)
{
    this->nrZile=n;
}
bool An::getbisect()
{
    return this->bisect;
}
void An::setbisect(bool b)
{
    this->bisect=b;
}
float An::getNrEvenimentePerLuna()
{
    return this->NrEvenimentePerLuna;
}
void An::setNrEvenimentePerLuna(float ev)
{
    this->NrEvenimentePerLuna=ev;
}
int An::getlunaCurenta()
{
    return this->lunaCurenta;
}
void An::setlunaCurenta(int l)
{
    this->lunaCurenta=l;
}
int An::getziCurenta()
{
    return  this->ziCurenta;
}
void An::setziCurenta(int z)
{
    this->ziCurenta=z;
}
double An::getNrEvenimenteSterse()
{
    return this->NrEvenimenteSterse;
}
void An::setNrEvenimenteSterse(double st)
{
    this->NrEvenimenteSterse=st;
}
string An::getActivitatePreferata()
{
    return this->ActivitatePreferata;
}
void An::setActivitatePreferata(string acv)
{
    this->ActivitatePreferata=acv;
}
char An::getTipAn()
{
    return this->TipAn;
}
void An::setTipAn(char t)
{
    this->TipAn=t;
}
char* An::getnumarScris()
{
    return this->numarScris;
}
void An::setnumarScris(char* numar)
{
    if (this->numarScris != NULL)
        delete[] this->numarScris;
    this->numarScris=new char[strlen(numar)+1];
    strcpy(this->numarScris,numar);

}
Luna*An:: getluni()
{
    return this->luni;
}



//CONSTRUCTORI
An::An():nrAn(anCurent++) //constructorul fara parametri
{
    nrZile=365;
    bisect=false;
    NrEvenimentePerLuna=0;
    lunaCurenta=0;
    ziCurenta=0;
    NrEvenimenteSterse=0;
    ActivitatePreferata="Necunoscuta";
    TipAn='l';
    numarScris=NULL;
    luni=NULL;

}
An::An(char* numarScris, int nrZile, bool bisect):nrAn(anCurent++) //constructor cu parametri 1
{
    this->numarScris=new char[strlen(numarScris)+1];
    strcpy( this->numarScris, numarScris);
    this->nrZile=nrZile;
    this->bisect=bisect;
    NrEvenimentePerLuna=0;
    lunaCurenta=0;
    ziCurenta=0;
    NrEvenimenteSterse=0;
    ActivitatePreferata="Necunoscuta";
    TipAn='l';
    luni=NULL;
}
An::An(int lunaCurenta,int ziCurenta,float NrEvenimentePerLuna,double NrEvenimenteSterse,string ActivitatePreferata,char TipAn,Luna* luni,char* numarScris, int nrZile, bool bisect):nrAn(anCurent++) //constructor cu parametri 2
{
    this->lunaCurenta=lunaCurenta;
    this->ziCurenta=ziCurenta;
    this->NrEvenimentePerLuna=NrEvenimentePerLuna;
    this->NrEvenimenteSterse=NrEvenimenteSterse;
    this->ActivitatePreferata=ActivitatePreferata;
    this->TipAn=TipAn;
    this->luni=new Luna[12];
    for(int i=0; i<12; i++)
        this->luni[i]=luni[i];
    this->numarScris=new char[strlen(numarScris)+1];
    strcpy( this->numarScris, numarScris);
    this->nrZile=nrZile;
    this->bisect=bisect;

}
An::An(const An& a):nrAn(a.nrAn) //cc
{
    this->lunaCurenta=a.lunaCurenta;
    this->ziCurenta=a.ziCurenta;
    this->NrEvenimentePerLuna=a.NrEvenimentePerLuna;
    this->NrEvenimenteSterse=a.NrEvenimenteSterse;
    this->ActivitatePreferata=a.ActivitatePreferata;
    this->TipAn=a.TipAn;
    this->luni=new Luna[12];
    for(int i=0; i<12; i++)
        this->luni[i]=a.luni[i];
    this->numarScris=new char[strlen(a.numarScris)+1];
    strcpy( this->numarScris, a.numarScris);
    this->nrZile=a.nrZile;
    this->bisect=a.bisect;
}
An::~An() //destructor
{
    if(this->numarScris != NULL)
        delete[] this->numarScris;;
    if(this->luni != NULL)
        delete[] this->luni;
}

class Zi{
protected:

    int activitati; //numarul de activitati din ziua respectiva
    string* program; //lungime 24, ' '= ora libera, in rest numele activitatii; ex: "Sport"

public:

//toti SETTERII si GETTERII
    int getactivitati()
    {
        return this->activitati;
    }
    void setactivitati(int activitati)
    {
        this->activitati=activitati;
    }
    string* getprogram()
    {
        return this->program;
    }
    void setprogram(string* program)
    {
        if (this->program != NULL)
          delete[] this->program;
        this->program=new string[24];
        for(int i=0;i<24;i++)
            this->program[i]=program[i];
    }

    friend ostream& operator<<(ostream& out,const Zi& z);
    friend istream& operator>>(istream& in,Zi& z);
    string operator[](int index);
   /* Zi operator-(int x);
    Zi operator+=(int x);*/
    Zi& operator=(const Zi& z);

    virtual  int* getore(){};
    virtual  void setore(int* ore){};
    virtual bool getvacanta(){};
    virtual void setvacanta(bool v){};

    virtual void programul_zilei()=0;

//CONSTRUCTORI
    Zi(const Zi& z) //cc
    {
        this->activitati=z.activitati;
        this->program=new string[24];
        for(int i=0;i<24;i++)
            program[i]=z.program[i];
    }
    Zi(int activitati) //constructor cu paramatri 1
    {
        this->activitati=activitati;
        program=NULL;
    }
    Zi(int activitati, string* program) //constructor cu toti paramatrii 2
    {
        this->activitati=activitati;
        this->program=new string[24];
        for (int i=0;i<24;i++)
            this->program[i]=program[i];
    }
    Zi()//constructor fara parametri
    {
        activitati=0;
        program=NULL;
    }
    virtual ~Zi()//destructor
    {
        if(this->program != NULL)
            delete[] this->program;
    }

};

//OPERATORI
/*Zi Zi::operator-(int x)
    {
        Zi aux(*this);
        aux.activitati=aux.activitati-x;
        return aux;
    }
Zi Zi::operator+=(int x)
    {
        this->activitati+=x;
        return *this;
    }*/
string Zi::operator[](int index)
    {
        if(index>=0 && index<24)
            return this->program[index];
        else
            return "\nindex nepotrivit"; //caz pentru index nepotrivit,cum fuctia mea returneaza un int nu puteam pune mesaj
    }
istream& operator>>(istream& in,Zi& z)
{
    cout<<"\n Cate activitati are aceasta zi? ";
    in>>z.activitati;
    return in;
}
ostream& operator<<(ostream& out,const Zi& z)
{
    out<<"\n Numarul de activitati din aceasta zi: "<<z.activitati;
    /* if (z.program != NULL) //am facut functie speciala care nu imi afiseaza si orele libere
        {out<<"\nProgramul zilei: ";
        for(int i=0;i<24;i++)
            out<<z.program[i]<<"; ";} */
    return out;
}
Zi& Zi::operator=(const Zi& z)
        {
            if(this != &z)
            {
                if(this->program != NULL)
                    delete[] this->program;
                this->activitati=z.activitati;
                this->program=new string[24];
                for(int i=0;i<24;i++)
                    program[i]=z.program[i];
            }
            return *this;
        }


class ZiSarbatoare:public Zi
{
private:
    bool vacanta;
public:

//SETTERI & GETTERI
    bool getvacanta()
    {
        return this->vacanta;
    }
    void setvacanta(bool v)
    {
        this->vacanta=v;
    }

//CONSTRUCTORI
    ZiSarbatoare():Zi()
    {
        this->vacanta=false;
    }
    ZiSarbatoare(int activitati,string* program,bool vacanta):Zi(activitati,program)
    {
        this->vacanta=vacanta;
    }
    ZiSarbatoare(const ZiSarbatoare& zs):Zi(zs)
    {
        this->vacanta=zs.vacanta;

    }
    ~ZiSarbatoare(){};

//OPERATORI
   ZiSarbatoare& operator=(const ZiSarbatoare& zs)
   {
       if (this != NULL)
       {
           Zi::operator=(zs);
           this->vacanta=zs.vacanta;
           return *this;
       }
   }
   friend istream& operator>>(istream& in, ZiSarbatoare& zs)
   {
       in>>(Zi&)zs;
       cout<<"\n In aceasta zi din concediu sunteti plecat in vacanta?[0-nu/1-da] ";
       in>>zs.vacanta;
       return in;
   }
   friend ostream& operator<<(ostream& out, const ZiSarbatoare& zs)
   {
       out<<(Zi&)zs;
       out<<"\n In aceasta zi din concediu sunteti plecat in vacanta: ";
       if (zs.vacanta ==1)
        out<<"da";
        else
        out<<"nu";
       return out;
   }

///functie care imi afiseaza programul zilei,numarul de ore ocupate si daca aceasta este sau nu o zi de vacanta
void programul_zilei()
{
    if(this->program != NULL)
    {
        int nr=0;
        for(int i=0;i<24;i++)
        {
            if(this->program[i] != " ")
                {cout<<"\nOra "<<i+1<<": "<<this->program[i];
                nr++;}
        }
        cout<<"\nAceasta zi are "<<nr<<" ore ocupate.";

    }
    else
        cout<<"\nNu se poate afisa programul.";

    if(vacanta)
            cout<<"\nIn aceasta zi sunteti plecat in vacanta.";
    else
            cout<<"\nIn aceasta zi nu sunteti plecat in vacanta.";
}
};


class ZiMunca:public Zi
{
private:
   int* ore; //vector de ore de lungime 2, ore[0]-startul intervalului in care muncesc,ore[1]-finalul intervalului

public:

//SETTERI & GETTERI
  int* getore()
    {
        return this->ore;
    }
  void setore(int* ore)
    {
        if(this->ore !=NULL)
            delete[] this->ore;
        this->ore=new int[2];
        for(int i=0;i<2;i++)
            this->ore[i]=ore[i];
    }

//CONSTRUCTORI
    ZiMunca():Zi()
    {
        this->ore=NULL;
    }

    ZiMunca(int activitati,string* program, int*ore):Zi(activitati,program)
    {
        this->ore= new int[2];
        for(int i=0;i<2;i++)
            this->ore[i]=ore[i];
    }
    ZiMunca(const ZiMunca& zm):Zi(zm)
    {
        this->ore= new int[2];
        for(int i=0;i<2;i++)
            this->ore[i]=zm.ore[i];
    }
    ~ZiMunca()
    {
        if (this->ore != NULL)
            delete this->ore;
    }

//OPERATORI
    ZiMunca& operator=(const ZiMunca& zm)
    {
        if (this != &zm)
        {
          Zi::operator=(zm);
          if (this->ore != NULL)
            delete this->ore;
          this->ore=new int[2];
          for(int i=0;i<2;i++)
            this->ore[i]=zm.ore[i];

        }
        return *this;
    }

    friend istream& operator>>(istream& in, ZiMunca& zm)
    {
        in>>(Zi&)zm;
        cout<<"\n Intervalul orar de munca pentru aceasta zi este: (exemplu: 9 17) ";
        if( zm.ore != NULL)
            delete[] zm.ore;
        zm.ore=new int[2];
        in>>zm.ore[0];
        in>>zm.ore[1];
        return in;
    }

    friend ostream& operator<<(ostream& out, const ZiMunca& zm)
    {
        out<<(Zi&)zm;
        out<<"\n Intervalul orar de munca pentru aceasta zi este: ";
        out<<zm.ore[0]<<":00 - "<<zm.ore[1]<<":00 ";
        return out;

    }

///functie care imi afiseaza programul zilei,numarul de ore ocupate, intervalul de munca
void programul_zilei()
{
    if(this->program != NULL)
    {
        int nr=0;
        for(int i=0;i<24;i++)
        {
            if(this->program[i] != " ")
                {cout<<"\nOra "<<i+1<<": "<<this->program[i];
                nr++;}
        }
        if(this->ore != NULL)
         {cout<<"\nAceasta zi are "<<nr<<" ore ocupate.";
        cout<<"\nIntervalul de munca pentru aceasta zi este: "<<this->ore[0]<<":00 - "<<this->ore[1]<<":00 ";}
    }
    else
            cout<<"\nNu se poate afisa.";

}
};


class DespreActivitati
{
public:
    virtual void detalii_activitate()=0;
    virtual void unde(){
    cout<<"\n Locatia activitatii este necunoscuta";}
};

class Activitate: public DespreActivitati{
protected:

    string NumeActivitate;
    int frecventa; //de cate ori a aparut in agenda

public:

//toti SETTERII si GETTERII

  string getNumeActivitate()
  {
      return this->NumeActivitate;
  }
  void setNumeActivitate(string nume)
  {
      this->NumeActivitate=nume;
  }
  int getfrecventa()
  {
      return this->frecventa;
  }
  void setfrecventa(int f)
  {
      this->frecventa=f;
  }

  friend ostream& operator<<(ostream& out, const Activitate& a);
  friend istream& operator>>(istream& in, Activitate& a);
  const Activitate& operator++();  // pre-incremenatre
  const Activitate& operator--();//pre-incrementare
  bool operator==(const Activitate& ac);
  bool operator<(const Activitate& ac)const;
  Activitate operator+(int x);
  Activitate& operator=(const Activitate& ac);

  void detalii_activitate()
  {
      cout<<"\n Aceasta activitate nu este legata de munca.";
  }
  void tip_activitate();


//CONSTRUCTORI
  Activitate(const Activitate& ac) //cc
  {
      this->NumeActivitate=ac.NumeActivitate;
      this->frecventa=ac.frecventa;
  }
  Activitate(string NumeActivitate) //constructor cu paramatri 1
  {
      this->NumeActivitate=NumeActivitate;
      frecventa=0;

  }
  Activitate(int frecventa,string NumeActivitate) //constructor cu toti parametri 2
  {
      this->frecventa=frecventa;
      this->NumeActivitate=NumeActivitate;

  }
  Activitate() //constructor fara parametri
  {
      NumeActivitate="Necunoscut";
      frecventa=0;
  }
 ~Activitate(){}; //destructor
};

///functie care imi determina tipul unei activitati in fuctie de frecventa ei
void Activitate::tip_activitate()
{
    if(this->frecventa==0)
     cout<<"\nActivitatea "<<this->NumeActivitate<<" nu apare in agenda.";
    else
        {
            if(this->frecventa<=5)
              cout<<"\nActivitatea "<<this->NumeActivitate<<" apare rar in agenda.";
            else
            {
              if(this->frecventa<10 && this->frecventa>5)
                cout<<"\nActivitatea "<<this->NumeActivitate<<" este comuna in agenda.";
              else
                cout<<"\nActivitatea "<<this->NumeActivitate<<" apare des in agenda.";
            }

        }
}


//OPERATORI
istream& operator>>(istream& in, Activitate& a)
{
    cout<<"\nNumele activitatii este: ";
    char aux[100];
    in.getline(aux,100);
    string s(aux);
    a.NumeActivitate=s;
    return in;
}
ostream& operator<<(ostream& out, const Activitate& a)
{
    out<<"\nNume Activitate: "<<a.NumeActivitate;
    out<<"\nFrecventa activitatii: "<<a.frecventa;
    return out;

}
const Activitate& Activitate::operator++() // pre-incremenatre
{
    this->frecventa++;
    return *this;
}
const Activitate& Activitate::operator--()// pre-decremenatre
{
    this->frecventa--;
    return *this;
}
bool Activitate::operator==(const Activitate& ac)
{
    if (this->NumeActivitate==ac.NumeActivitate && this->frecventa==ac.frecventa)
        return true;
    return false;
}
bool Activitate::operator< (const Activitate& ac)const
{
    if (this->NumeActivitate<ac.NumeActivitate)
        return true;
    return false;
}
Activitate Activitate::operator+(int x)
  {
      Activitate aux(*this);
      aux.frecventa=aux.frecventa+x;
      return aux;
  }
Activitate& Activitate::operator=(const Activitate& ac)
  {   if (this != &ac)
      {
      this->NumeActivitate=ac.NumeActivitate;
      this->frecventa=ac.frecventa;
      }
      return *this;
  }


class ActivitateProfesionala:public Activitate
{
private:
    string locatie;
public:

    ActivitateProfesionala();
    ActivitateProfesionala(string NumeActivitate,int frecventa,string locatie);
    ActivitateProfesionala(const ActivitateProfesionala& acprof);

    ActivitateProfesionala& operator=(const ActivitateProfesionala& acprof);
    friend istream& operator>>(istream& in,ActivitateProfesionala& acprof);
    friend ostream& operator<<(ostream& out,const ActivitateProfesionala& acprof);

    string getlocatie()
      {
          return this->locatie;
      }
    void setlocatie(string nume)
      {
          this->locatie=nume;
      }

    void detalii_activitate()
    {
        cout<<"\n Aceasta activitate este legata de munca.";
    }
    void unde()
    {
        cout<<"\n Locatia activitatii este "<<this->locatie;
    }


    ~ActivitateProfesionala(){};

};

//CONSTRUCTORI
ActivitateProfesionala::ActivitateProfesionala():Activitate()
{
    this->locatie="Necunoscuta";
}

ActivitateProfesionala::ActivitateProfesionala(string NumeActivitate,int frecventa,string locatie):Activitate(frecventa,NumeActivitate)
{
    this->locatie=locatie;
}

ActivitateProfesionala::ActivitateProfesionala(const ActivitateProfesionala& acprof):Activitate(acprof)
{
    this->locatie=acprof.locatie;
}

//OPERATORI

ActivitateProfesionala& ActivitateProfesionala::operator=(const ActivitateProfesionala& acprof)
{
    if(this != &acprof)
    {
        Activitate::operator=(acprof);
        this->locatie=acprof.locatie;
    }
    return *this;
}

istream& operator>>(istream& in,ActivitateProfesionala& acprof)
{
    in>>(Activitate&) acprof;
    cout<<"\nLocatia acestei activitati este: ";
    in>>acprof.locatie;
    return in;
}
ostream& operator<<(ostream& out,const ActivitateProfesionala& acprof)
{
    out<<(Activitate&)acprof;
    out<<"\n Locatia acestei activitati este: ";
    out<<acprof.locatie;
    return out;
}
///functie care converteste o data din an in numarul zilei din an
int converteste_data(int zi,int luna)
{
    int nrZi;
    if (luna==1)
    {
        nrZi=zi;
        return nrZi;
    }
     if (luna==2)
    {
        nrZi=zi+31;
        return nrZi;
    }
     if (luna==3)
    {
        nrZi=zi+59;
        return nrZi;
    }
     if (luna==4)
    {
        nrZi=zi+90;
        return nrZi;
    }
     if (luna==5)
    {
        nrZi=zi+120;
        return nrZi;
    }
     if (luna==6)
    {
        nrZi=zi+151;
        return nrZi;
    }
     if (luna==7)
    {
        nrZi=zi+181;
        return nrZi;
    }
     if (luna==8)
    {
        nrZi=zi+212;
        return nrZi;
    }
     if (luna==9)
    {
        nrZi=zi+243;
        return nrZi;
    }
     if (luna==10)
    {
        nrZi=zi+273;
        return nrZi;
    }
     if (luna==11)
    {
        nrZi=zi+304;
        return nrZi;
    }
     if (luna==12)
    {
        nrZi=zi+334;
        return nrZi;
    }
}

void adauga_activitate(An &an2021,vector <Zi*> &Zile,map <string, string> &Locatii,set <Activitate> &Activitati,
                       int luna_aux,int ziua_aux,int ora_aux,string nume_aux,bool decizie_aux,string locatie_aux)
{
     int gasita=0;

     an2021.getluni()[luna_aux-1].setnrActivitati(an2021.getluni()[luna_aux-1].getnrActivitati()+1);

     int nr_zi= converteste_data(ziua_aux,luna_aux);

     int nr_ac=(*Zile[nr_zi-1]).getactivitati();

    (*Zile[nr_zi-1]).setactivitati(nr_ac+1);

     if((*Zile[nr_zi-1]).getprogram()== NULL)
                        {
                             string* p_aux= new string[24];
                             for(int i=0;i<24;i++)
                             {
                                 if (i != (ora_aux-1))
                                    p_aux[i]=" ";
                                 else
                                    p_aux[i]=nume_aux;
                             }
                            (*Zile[nr_zi-1]).setprogram(p_aux);
                        }
                        else
                        {

                            string* p_aux= new string[24];
                            for(int i=0;i<24;i++)
                            {
                                if (i == (ora_aux-1))
                                    p_aux[i]=nume_aux;
                                else
                                {
                                  p_aux[i]=(*Zile[nr_zi-1]).getprogram()[i];
                                }
                            }
                            (*Zile[nr_zi-1]).setprogram(p_aux);
                        }
      if (decizie_aux)

                {
                    for (auto it = Activitati.begin(); it != Activitati.end(); ++it)
                                {
                                    Activitate a=(*it);
                                    //cout<<a.getNumeActivitate()<<" "<<nume_aux<<endl;
                                    if (a.getNumeActivitate() == nume_aux)
                                    {

                                        Activitati.erase(a);
                                        a.setfrecventa(a.getfrecventa()+1);
                                        //cout<<endl<<a.getfrecventa();
                                        Activitati.insert(a);
                                        gasita=1;
                                        break;
                                    }
                                  }

                    if (!gasita)
                                {
                                    ActivitateProfesionala acp(nume_aux,1,locatie_aux);
                                    Activitati.insert(acp);
                                   //cout<<(acp);

                                    /*for(auto it= Activitati.begin();it != Activitati.end();it++)
                                        cout<<endl<<(*it);

                                    */Locatii.insert(pair<string,string>(nume_aux,locatie_aux));

                                }
                }

                            else
                            {
                                for (auto it = Activitati.begin(); it != Activitati.end(); ++it)
                                {
                                    Activitate a=(*it);
                                    //cout<<a.getNumeActivitate()<<" "<<nume_aux<<endl;
                                    if (a.getNumeActivitate() == nume_aux)
                                    {
                                        a.setfrecventa(a.getfrecventa()+1);
                                        gasita=1;
                                    }
                                    if(gasita)
                                    {
                                        Activitati.erase((*it));
                                        Activitati.insert(a);
                                        break;
                                    }
                                }

                                if (!gasita)
                                {
                                    Activitate ac(1,nume_aux);
                                    Activitati.insert(ac);
                                }
                            }


}


int main()
{

///Creez anul 2021
Luna ian(0,0,1,31,"Ianuarie");
Luna feb(0,0,2,28,"Februarie");
Luna mar(0,0,3,31,"Martie");
Luna apr(0,0,4,30,"Aprilie");
Luna mai(0,0,5,31,"Mai");
Luna iun(0,0,6,30,"Iunie");
Luna iul(0,0,7,31,"Iulie");
Luna aug(0,0,8,31,"August");
Luna sep(0,0,9,30,"Septembrie");
Luna oct(0,0,10,31,"Octombrie");
Luna noi(0,0,11,30,"Noiembrie");
Luna dec(0,0,12,31,"Decembrie");

Luna Luni[12]= {ian,feb,mar,apr,mai,iun,iul,aug,sep,oct,noi,dec};

An an2021(0,0,0.0,0.0,"Citit",'l',Luni,"Doua mii douazeci si unu",365,0);

fout<<an2021;

///Citesc din fisier zilele de sarbatoare si creez o lista cu datele convertite in numarul zilelor
    list<int> date;

    string text;
    int zi,luna,data,poz=0;


   while (getline(fin,text))
        {
           poz=text.find('/');
           zi= stoi(text.substr(0,poz));
           luna=stoi(text.erase(0,poz+1));
           data=converteste_data(zi,luna);
           date.push_back(data);
        }
/*
    list <int> :: iterator it;
    for(it = date.begin(); it != date.end(); ++it)
        cout << *it<<' ';
    cout << '\n';
*/

///Creez un Vector cu 365 de zile, cele de tip Zi Sarbatoare avand numarul corespunzator unei valori din lista date

vector<Zi*> Zile;

for(int i=0;i<365;i++)
   {   int ok=0;
       list <int> :: iterator it;

       for(it = date.begin(); it != date.end(); ++it)
       {

           if (i+1 == (*it))
             {
                 ok=1;

             }
       }

       if(ok == 0)
       {
           ZiMunca *zm=new ZiMunca;;
           Zile.push_back(zm);
       }
       else
       {
           ZiSarbatoare *zs=new ZiSarbatoare;
           Zile.push_back(zs);
       }
}



/*(*Zile[1]).programul_zilei();
(*Zile[4]).programul_zilei();
(*Zile[3]).setactivitati(4);
cout<<(*Zile[3]).getactivitati(); */
/*
for(auto it= Zile.begin();it != Zile.end();++it)
{
    cout<<(*it)<<' ';
}*/

///SET DE ACTIVITATI

set <Activitate> Activitati;


///MAP cu numele ACTIVITATILOR PROFESIONALE si locatiile lor

map <string, string> Locatii;

/*
ActivitateProfesionala activ1("Curs",3,"Universitatea Bucuresti");
ActivitateProfesionala activ2("Munca",300,"Birou");


Locatii.insert(pair<string,string>(activ1.getNumeActivitate(),activ1.getlocatie()));
Locatii.insert(pair<string,string>(activ2.getNumeActivitate(),activ2.getlocatie()));

map<string,string> :: iterator itr;


for (auto itr = Locatii.begin(); itr != Locatii.end(); ++itr)
{
    cout<<itr->first<<" "<<itr->second<<endl;
}
*/
///Adaug activitati
adauga_activitate(an2021,Zile,Locatii,Activitati,1,1,12,"Jogging",false," ");
adauga_activitate(an2021,Zile,Locatii,Activitati,5,6,10,"Laborator SD",true,"MS Teams");
adauga_activitate(an2021,Zile,Locatii,Activitati,5,8,21,"Petrecere 20 de ani",false," ");
adauga_activitate(an2021,Zile,Locatii,Activitati,5,10,10,"Prezentare proiect POO",true,"MS Teams");
adauga_activitate(an2021,Zile,Locatii,Activitati,5,10,12,"Invatat GAL",true,"Acasa");
adauga_activitate(an2021,Zile,Locatii,Activitati,5,10,13,"Invatat GAL",true,"Acasa");
adauga_activitate(an2021,Zile,Locatii,Activitati,5,11,12,"Test GAL",true,"Zoom");
adauga_activitate(an2021,Zile,Locatii,Activitati,5,14,17,"Terapie",false," ");
adauga_activitate(an2021,Zile,Locatii,Activitati,5,20,10,"Prezentare proiect SD",true,"MS Teams");
adauga_activitate(an2021,Zile,Locatii,Activitati,5,21,12,"Laborator LFA",true,"MS Teams");
adauga_activitate(an2021,Zile,Locatii,Activitati,5,21,13,"Laborator LFA",true,"MS Teams");
adauga_activitate(an2021,Zile,Locatii,Activitati,5,21,14,"Seminar POO",true,"Google Meet");
adauga_activitate(an2021,Zile,Locatii,Activitati,5,21,15,"Seminar POO",true,"Google Meet");
adauga_activitate(an2021,Zile,Locatii,Activitati,5,21,16,"Seminar SD",true,"MS Teams");
adauga_activitate(an2021,Zile,Locatii,Activitati,5,21,17,"Seminar SD",true,"MS Teams");
adauga_activitate(an2021,Zile,Locatii,Activitati,5,25,15,"Dentist",false," ");

/*int nr= converteste_data(21,5);
(*Zile[nr-1]).programul_zilei();
cout<<(*Zile[nr-1])[12]<<' '<<(*Zile[nr-1])[13]<<' '<<(*Zile[nr-1])[14]<<' '<<(*Zile[nr-1])[15];
*/

///MENIUL INTERACTIV


cout<<"AGENDA ANUL 2021\n";

int dorinta=1;

while(dorinta !=4)
{
    cout<<"\nCe doriti sa faceti?";
    cout<<"\n 1 Sa modificati agenda";
    cout<<"\n 2 Sa vizualizati date din agenda";
    cout<<"\n 3 Sa tesati clasele programului";
    cout<<"\n 4 Iesire";
    cout<<endl;
    cin>>dorinta;
    cout<<endl;
    switch (dorinta)
    {
      case 1:
        {
            int comanda=1;

            while(comanda != 0)
            {
                cout<<"\n\nMENIU MODIFICARE AGENDA\n";
                cout<<"\n 1 Adaugati o activitate";
                cout<<"\n 2 Stergeti o activitate";
                cout<<"\n 3 Setati o zi de sarbatoare ca zi de vacanta";
                cout<<"\n 4 Setati intervalul de munca pentru o zi de munca";
                cout<<"\n 0 Intoarcere la meniul principal";

                cout<<endl;
                cin>>comanda;
                system("CLS");
                cout<<endl;

                switch(comanda)
                {
                case 1:
                    {
                        int luna_aux,ziua_aux,ora_aux,gasita=0;
                        bool decizie_aux;
                        cout<<"\nIntroduceti luna:"<<endl<<"(numar) ";
                        cin>>luna_aux;
                        cout<<"\nIntroduceti ziua:"<<endl;
                        cin>>ziua_aux;
                        cout<<"\nIntroduceti ora:"<<endl;
                        cin>>ora_aux;
                        cout<<"\nIntroduceti numele activitatii:"<<endl;
                        cin.get();
                        char aux[100];
                        cin.getline(aux,100);
                        string nume_aux(aux);
                        cout<<"\nAdaugati o activitate profesionala?[0=nu/1=da]"<<endl;
                        cin>>decizie_aux;


                     /*   Luna* luni_aux= an2021.getluni();


                        luni_aux[luna_aux-1].setnrActivitati(luni_aux[luna_aux-1].getnrActivitati()+1);
                        cout<<luni_aux[luna_aux-1];
                      */
                        an2021.getluni()[luna_aux-1].setnrActivitati(an2021.getluni()[luna_aux-1].getnrActivitati()+1);

                        int nr_zi= converteste_data(ziua_aux,luna_aux);

                        int nr_ac=(*Zile[nr_zi-1]).getactivitati();

                        (*Zile[nr_zi-1]).setactivitati(nr_ac+1);

                        if((*Zile[nr_zi-1]).getprogram()== NULL)
                        {
                             string* p_aux= new string[24];
                             for(int i=0;i<24;i++)
                             {
                                 if (i != (ora_aux-1))
                                    p_aux[i]=" ";
                                 else
                                    p_aux[i]=nume_aux;
                             }
                            (*Zile[nr_zi-1]).setprogram(p_aux);
                        }
                        else
                        {
                            string* p_aux= new string[24];
                            for(int i=0;i<24;i++)
                            {
                                if (i == (ora_aux-1))
                                    p_aux[i]=nume_aux;
                                else
                                {
                                  p_aux[i]=(*Zile[nr_zi-1]).getprogram()[i];
                                }


                            }
                            (*Zile[nr_zi-1]).setprogram(p_aux);
                            //(*Zile[nr_zi-1])[ora_aux-1]=nume_aux;
                        }
                        if (decizie_aux)
                            {
                                string locatie_aux;
                                cout<<"\nIntroduceti locatia activitatii:"<<endl;
                                cin>>locatie_aux;


                                for (auto it = Activitati.begin(); it != Activitati.end(); ++it)
                                {
                                    Activitate a=(*it);

                                    if (a.getNumeActivitate() == nume_aux)
                                    {
                                        Activitati.erase(a);
                                        a.setfrecventa(a.getfrecventa()+1);
                                        Activitati.insert(a);
                                        gasita=1;
                                        break;
                                    }
                                }

                                if (!gasita)
                                {
                                    ActivitateProfesionala acp(nume_aux,1,locatie_aux);
                                    Activitati.insert(acp);
                                    Locatii.insert(pair<string,string>(nume_aux,locatie_aux));
                                }


                            }

                            else
                            {
                                for (auto it = Activitati.begin(); it != Activitati.end(); ++it)
                                {
                                    Activitate a=(*it);

                                    if (a.getNumeActivitate() == nume_aux)
                                    {
                                        a.setfrecventa(a.getfrecventa()+1);
                                        gasita=1;
                                    }
                                    if(gasita)
                                    {
                                        Activitati.erase((*it));
                                        Activitati.insert(a);
                                        break;
                                    }
                                }

                                if (!gasita)
                                {
                                    Activitate ac(1,nume_aux);
                                    Activitati.insert(ac);

                                }
                            }


                        if(luna_aux > 12 || nr_zi >365 || ora_aux > 24)
                            {cout<<"\nAti introdus date incorecte.";
                            break;}

                        cout<<"\nActivitatea "<<nume_aux<<" a fost adaugata in agenda, pe data de ";
                        cout<<ziua_aux<<'.'<<luna_aux<<" ora "<<ora_aux;
                        break;
                    }
                case 2:
                    {
                        int luna_aux,ziua_aux,ora_aux;
                        cout<<"\nIntroduceti luna:"<<endl<<"(numar) ";
                        cin>>luna_aux;
                        cout<<"\nIntroduceti ziua:"<<endl;
                        cin>>ziua_aux;
                        cout<<"\nIntroduceti ora:"<<endl;
                        cin>>ora_aux;
                        cout<<"\nIntroduceti numele activitatii:"<<endl;
                        cin.get();
                        char aux[100];
                        cin.getline(aux,100);
                        string nume_aux(aux);


                        an2021.getluni()[luna_aux-1]++;
                        an2021.getluni()[luna_aux-1]--;

                        int nr_zi= converteste_data(ziua_aux,luna_aux);

                        int nr_ac=(*Zile[nr_zi-1]).getactivitati();

                        (*Zile[nr_zi-1]).setactivitati(nr_ac-1);

                        if((*Zile[nr_zi-1]).getprogram()== NULL || (*Zile[nr_zi-1])[ora_aux-1]== " ")
                        {
                            cout<<"\nNu exista aceasta activitate la ora data.";
                         break;
                        }
                        else
                        {

                            string* p_aux= new string[24];
                            for(int i=0;i<24;i++)
                            {
                                if (i == (ora_aux-1))
                                    p_aux[i]=" ";
                                else
                                {
                                  p_aux[i]=(*Zile[nr_zi-1]).getprogram()[i];
                                }


                            }
                            (*Zile[nr_zi-1]).setprogram(p_aux);
                        }


                        if(luna_aux > 12 || nr_zi >365 || ora_aux > 24)
                            {cout<<"\nAti introdus date incorecte.";
                            break;}

                        cout<<"\nActivitatea "<<nume_aux<<", de pe data "<<ziua_aux<<'.'<<luna_aux<<" a fost stearsa din agenda.";
                        cout<<"\nNoul program:\n";
                        (*Zile[nr_zi-1]).programul_zilei();

                        break;
                    }
                case 3:
                    {
                        int luna_aux,ziua_aux,ok=0;

                        cout<<"\nIntroduceti luna:"<<endl<<"(numar) ";
                        cin>>luna_aux;
                        cout<<"\nIntroduceti ziua:"<<endl;
                        cin>>ziua_aux;

                        int nr_zi= converteste_data(ziua_aux,luna_aux);

                        list <int> :: iterator it;
                        for(it = date.begin(); it != date.end(); ++it)
                           {
                               if (nr_zi == (*it))
                                 {
                                     ok=1;
                                     break;
                                 }
                           }

                        if(luna_aux > 12 || nr_zi >365 )
                            {cout<<"\nAti introdus date incorecte.";
                            break;}

                        if (!ok)
                        {
                            cout<<"\nNu aveti aceasta optiune pentru zilele de munca.";
                            break;
                        }


                        (*Zile[ziua_aux-1]).setvacanta(true);
                        cout<<"\nZiua "<<ziua_aux<<'.'<<luna_aux<<" a fost setata ca zi de vacanta";


                        break;
                    }
                case 4:
                    {
                        int luna_aux,ziua_aux,ora_s,ora_f;

                        cout<<"\nIntroduceti luna:"<<endl<<"(numar) ";
                        cin>>luna_aux;
                        cout<<"\nIntroduceti ziua:"<<endl;
                        cin>>ziua_aux;
                        cout<<"\nIntroduceti ora de inceput:"<<endl;
                        cin>>ora_s;
                        cout<<"\nIntroduceti ora de final:"<<endl;
                        cin>>ora_f;

                        int nr_zi= converteste_data(ziua_aux,luna_aux);
                        int ok=0;
                        list <int> :: iterator it;
                        for(it = date.begin(); it != date.end(); ++it)
                           {
                               if (ziua_aux == (*it))
                                 {
                                     cout<<"\nNu aveti aceasta optiune pentru o zi de sarbatoare.";
                                     ok=1;
                                     break;
                                 }
                           }

                        if(luna_aux > 12 || nr_zi >365 || ora_s > 24 || ora_f > 24)
                            {cout<<"\nAti introdus date incorecte.";
                            break;}
                        if (ok)
                                break;
                         int* o_aux=new int[2];
                         o_aux[0]=ora_s;
                         o_aux[1]=ora_f;
                        (*Zile[ziua_aux-1]).setore(o_aux);
                        //(*Zile[ziua_aux-1]).programul_zilei();

                        cout<<"\nProgramul de munca din data "<<ziua_aux<<'.'<<luna_aux<<" a fost setat ca "<<ora_s<<'-'<<ora_f;

                        break;
                    }

                }

            }
            break;
        }
    case 2:
        {
            int comanda=1;

            while(comanda != 0)
            {
                cout<<"\n\nMENIU VIZUALIZARE AGENDA\n";
                cout<<"\n 1  Vizualizarea programului unei zile";
                cout<<"\n 2  Vizualizarea numarului de activitati dintr-o zi";
                cout<<"\n 3  Vizualizarea mediei numarului de activitati dintr-o luna";
                cout<<"\n 4  Vizualizarea mediei numarului de activitati din an";
                cout<<"\n 5  Aflati tipul anului 2021";
                cout<<"\n 6  Aflati activitatea preferata din anul 2021";
                cout<<"\n 7  Aflati frecventa unei activitati";
                cout<<"\n 8  Aflati tipul unei activitati";
                cout<<"\n 9  Afisati locatia unei activitati profesionale";
                cout<<"\n 10 Convertiti numarul unei zile intr-o data";
                cout<<"\n 11 Afisati toate activitatile profesionale si locatiile lor";
                cout<<"\n 12 Afisati toate activitatile";
                cout<<"\n 0  Intoarcere la meniul principal";

                cout<<endl;
                cin>>comanda;
                system("CLS");

                cout<<endl;

                switch(comanda)
                {
                case 1:
                    {
                        int luna_aux,ziua_aux;
                        cout<<"\nIntroduceti luna:"<<endl<<"(numar) ";
                        cin>>luna_aux;
                        cout<<"\nIntroduceti ziua:"<<endl;
                        cin>>ziua_aux;


                        int nr_zi= converteste_data(ziua_aux,luna_aux);

                        if(luna_aux > 12 || nr_zi >365)
                            {cout<<"\nAti introdus date incorecte.";
                            break;}

                        if ((*Zile[nr_zi-1]).getprogram() != NULL)
                                (*Zile[nr_zi-1]).programul_zilei();

                        else
                            cout<<"\nAceasta zi are programul gol.";

                        break;
                    }
                case 2:
                    {
                        int luna_aux,ziua_aux;
                        cout<<"\nIntroduceti luna:"<<endl<<"(numar) ";
                        cin>>luna_aux;
                        cout<<"\nIntroduceti ziua:"<<endl;
                        cin>>ziua_aux;


                        int nr_zi= converteste_data(ziua_aux,luna_aux);

                        if(luna_aux > 12 || nr_zi >365)
                            {cout<<"\nAti introdus date incorecte.";
                            break;}
                        cout<<"\nIn aceasta zi aveti "<<(*Zile[nr_zi-1]).getactivitati()<<" activitati.";

                        break;
                    }
                case 3:
                    {
                        int luna_aux;
                        cout<<"\nIntroduceti luna:"<<endl<<"(numar) ";
                        cin>>luna_aux;

                        if(luna_aux > 12)
                            {cout<<"\nAti introdus date incorecte.";
                            break;}

                        cout<<"Luna "<<an2021.getluni()[luna_aux-1].getNumeLuna() <<" a avut o medie de ";
                        cout<<setprecision(2)<<an2021.getluni()[luna_aux-1].medie_activitati()<<" activitati pe zi.";
                        break;
                    }
                case 4:
                    {

                        cout<<"\nMedia numarului de activitati din anul 2021 este "<< an2021.medie_activitati_an()<<endl;
                    }
                case 5:
                    {
                        double medie=an2021.medie_activitati_an();
                        if (medie<1)
                            {
                                cout<<"\nAnul este liber (media numarului de evenimente per luna <1) ";
                                an2021.setTipAn('l');
                                break;
                             }
                        if(medie>=1 && medie<=4)
                            {
                                cout<<"\nAnul este normal (media numarului de evenimente per luna este cuprinsa intre [1,4]) ";
                                an2021.setTipAn('n');
                                break;
                            }
                        if(medie>4)
                            {
                                cout<<"\nAnul este ocupat (media numarului de evenimente per luna >4 ) ";
                                an2021.setTipAn('o');
                                break;
                            }

                        break;
                    }
                case 6:
                    {
                        cout<<"\nActivitatea preferata din anul 2021 este: "<<an2021.getActivitatePreferata();
                        break;

                    }
                case 7:
                    {  int gasita=0;
                        cout<<"\nIntroduceti numele activitatii:"<<endl;
                        cin.get();
                        char aux[100];
                        cin.getline(aux,100);
                        string nume(aux);

                        for (auto it = Activitati.begin(); it != Activitati.end(); ++it)
                                {

                                    Activitate a=(*it);

                                    if (a.getNumeActivitate() == nume)
                                    {
                                        cout<<"\nFrecventa activitatii "<<nume<<" este "<<a.getfrecventa();
                                        gasita=1;
                                        break;
                                    }
                                }
                         if(!gasita)
                                    cout<<"\nNu exista nicio activitate cu numele dat in agenda.";
                         break;
                    }
                case 8:
                    {
                        int gasita=0;
                        cout<<"\nIntroduceti numele activitatii:"<<endl;
                        cin.get();
                        char aux[100];
                        cin.getline(aux,100);
                        string nume(aux);

                        for (auto it = Activitati.begin(); it != Activitati.end(); ++it)
                                {

                                    Activitate a=(*it);

                                    if (a.getNumeActivitate() == nume)
                                    {
                                        a.tip_activitate();
                                        gasita=1;
                                        break;
                                    }
                                }
                         if(!gasita)
                                    cout<<"\nNu exista nicio activitate cu numele dat in agenda.";
                        break;
                    }
                case 9:
                    {
                        int gasita=0;
                        cout<<"\nIntroduceti numele activitatii:"<<endl;
                        cin.get();
                        char aux[100];
                        cin.getline(aux,100);
                        string nume(aux);
                        string activ;

                        for (auto it = Locatii.begin(); it != Locatii.end(); ++it)
                                {

                                    if (it->first == nume)
                                    {
                                        cout<<"\nLocatia activitatii este: "<<it->second;
                                        gasita=1;
                                        break;
                                    }
                                }
                         if(!gasita)
                                    cout<<"\nNu exista nicio activitate profesionala cu numele dat in agenda.";
                        break;
                    }
                case 10:
                    {
                        int numar;
                        cout<<"\nIntroduceti numarul zilei din an: "<<endl;
                        cin>>numar;
                        an2021.setziCurenta(numar);
                        cout<<an2021.calculeaza_data();

                        break;
                    }
                case 11:
                    {
                        map<string,string> :: iterator itr;

                        for ( itr = Locatii.begin(); itr != Locatii.end(); ++itr)
                        {
                            cout<<itr->first<<" - "<<itr->second<<endl;
                        }
                        break;
                    }
                case 12:
                    {
                        for (auto itr = Activitati.begin();itr != Activitati.end();++itr)
                            cout<<*itr<<endl;
                        break;
                    }
                }

            }

            break;
        }
    case 3:
        {
            int comanda=1;

            while(comanda !=0 )
         {


            cout<<"INTRODUCETI COMANDA: \n "<<endl;
            cout<<"0 Intoarcere la meniul principal"<<endl;
            cout<<"1 Teste clasa An"<<endl;
            cout<<"2 Teste clasa Luna"<<endl;
            cout<<"3 Teste clasa abstracta Zi, clasa ZiMunca si clasa ZiSarbatoare"<<endl;
            cout<<"4 Teste clasa Activitate si clasa ActivitateProfesionala"<<endl;
            cin>>comanda;
            system("CLS");

            switch(comanda)
            {


                case 1:
                    {
                    system("CLS");
                    cout<<"TESTE CLASA AN"<<endl<<"____";

                    An a1; //constructor fara param
                    char numarscris[]="Doua mii douazeci si unu";
                    char numarscris2[]="Doua mii douazeci si trei";
                    Luna ian(0,0,1,31,"Ianuarie");
                    Luna feb(0,0,2,28,"Februarie");
                    Luna mar(0,0,3,31,"Martie");
                    Luna apr(0,0,4,30,"Aprilie");
                    Luna mai(0,0,5,31,"Mai");
                    Luna iun(0,0,6,30,"Iunie");
                    Luna iul(0,0,7,31,"Iulie");
                    Luna aug(0,0,8,31,"August");
                    Luna sep(0,0,9,30,"Septembrie");
                    Luna oct(0,0,10,31,"Octombrie");
                    Luna noi(0,0,11,30,"Noiembrie");
                    Luna dec(0,0,12,31,"Decembrie");
                    Luna toate_lunile[12]= {ian,feb,mar,apr,mai,iun,iul,aug,sep,oct,noi,dec};
                    //for(int i=0; i<12; i++)
                    //    cout<<toate_lunile[i]<<endl;

                    //constructor cu param 1
                    An a2(3,9,3.5,0.0,"Alergat",'l',toate_lunile,numarscris,30,false);
                    //cout<<a2;
                    //constructor cu param 2
                    An a3(numarscris2, 9, false);
                    //copy constructor
                    An a4(a2);
                    a4.setbisect(true);
                    cout<<a4;
                    //operatorul =
                    An a5;
                    a5=a4;
                    cout<<"\nTeste setteri & getteri pentru al doilea obiect de tip an (2022)"<<endl<<"--------";
                    cout<<"\nAnul: "<<a2.getnrAn();
                    a2.setnrZile(365);
                    cout<<"\nNumarul de zile: "<<a2.getnrZile();
                    a2.setbisect(false);
                    cout<<"\nAnul este bisect? [0=Nu/1=Da] "<<a2.getbisect();
                    a2.setNrEvenimentePerLuna(3.5);
                    cout<<"\nMedia numarului de evenimente per luna pentru acest an este: "<<a2.getNrEvenimentePerLuna();
                    a2.setNrEvenimenteSterse(0.65);
                    cout<<"\nMedia numarului de evenimente sterse per luna este: "<<a2.getNrEvenimenteSterse();
                    a2.setActivitatePreferata("Mersul la cinema");
                    cout<<"\nActivitatea preferata din acest an este: "<< a2.getActivitatePreferata();
                    a2.setTipAn('n');
                    cout<<"\nTipul anului este: "<<a2.getTipAn()<<" \n --Tip l(liber)-media numarului de evenimente per luna <1 \n --Tip n(normal)-media este cuprinsa intre [1,4] \n --Tip o(ocupat)-media >4 ";
                    a2.setnumarScris(numarscris2);
                    cout<<"\nAnul se scrie: "<<a2.getnumarScris();

                    a2.setlunaCurenta(9);
                    a2.setziCurenta(15);
                    cout<<endl;

                    cout<<"\nTeste operatori"<<endl<<"--------";
                    cout<<endl<<"\nOperatorul >>\n";
                    An a7;
                    cin>>a7;
                    cout<<endl<<"\nOperatorul <<\n";
                    cout<<a7;
                    cout<<endl<<"\nOperatorul + (concateneaza activitatile preferate)";
                    a3.setActivitatePreferata("Inot");
                    cout<<a2+a3<<endl;
                    cout<<"\n\nTest functia de calcul a datei pentru a2 (ziua curenta este 15)"<<endl<<"--------";
                    cout<<endl<<a2.calculeaza_data();
                    cout<<endl;

                    break;
                    }


            case 2:
                    {
                    system("CLS");
                    cout<<"\nTESTE CLASA LUNA"<<endl<<"____";

                    char numeluna[]="Martie";
                    Luna l1; //constructor fara parametri
                    Luna l2(8,2,3,31,numeluna); //constructor cu parametri 1
                    Luna l3(3,31,numeluna);//constructor cu parametri 2
                    Luna l4(l3);//cc
                    Luna l5;
                    l5=l4;//operatorul =

                    cout<<"\nTeste setteri & getteri"<<endl<<"--------";
                    l1.setnrLuna(3);
                    cout<<"\nNumarul lunii: "<<l1.getnrLuna();
                    l1.setnrZile(31);
                    cout<<"\nLuna are "<<l1.getnrZile()<<" zile";
                    l1.setNumeLuna(numeluna);
                    cout<<"\nNumele lunii: "<<l1.getNumeLuna();
                    l1.setnrActivitati(46);
                    cout<<"\nNumarul de activitati din aceasta luna: "<<l1.getnrActivitati();
                    l1.setsterse(15);
                    cout<<"\nNumarul de activitati sterse: "<<l1.getsterse();

                    cout<<endl<<"\nTeste operatori"<<endl<<"--------";
                    cout<<endl<<"\nOperatorul >>"<<endl;
                    Luna l;
                    cin>>l;
                    l.setnrActivitati(11);
                    l.setsterse(3);
                    cout<<endl<<"\nOperatorul << pentru l"<<endl;
                    cout<<l<<endl;
                    cout<<endl<<"\nOperatorul << pentru l2"<<endl;
                    cout<<l2<<endl;
                    cout<<endl<<"\nOperatorul + pentru l si l2 (aduna numarul de activitati si numarul de activitati sterse) "<<endl;
                    cout<<l+l2<<endl;
                    cout<<endl<<"\nOperatorul ++(post) pentru l2"<<endl;
                    cout<<l2++<<endl;
                    cout<<endl<<"\nOperatorul -- pentru l2"<<endl;
                    cout<<l2--<<endl;
                    cout<<"\n\nTest functie care calculeaza doua medii"<<endl<<"--------";
                    cout<<endl;
                    l1.medie_activitati();
                    cout<<endl<<endl;

                    break;
                    }

            case 3:
                    {
                    system("CLS");
                    cout<<"\nTESTE CLASA ZI"<<endl<<"____________";

                    int ore3[2]={9,17};
                    string prog[]={" "," "," "," "," "," "," "," "," ","Sport","Citit","Curs POO","Curs POO","Lucrat Proiect","Lucrat Proiect","Lucrat Proiect","Lucrat Proiect"," "," "," "," "," "," "," "," "};

                    Zi *z1[2];
                    z1[0]= new ZiMunca();
                    z1[1]= new ZiSarbatoare();

                    ZiMunca zm;//constructor fara parametri
                    ZiMunca zm1(3,prog,ore3);//constructor cu parametri 1

                    ZiSarbatoare zs;
                    ZiSarbatoare zs1(3,prog,true);

                    cout<<"\n\nTeste operatori"<<endl<<"--------";

                    cout<<endl<<"\nOperatorul <<"<<endl;
                    cout<<endl<<"\nPentru Zi Sarbatoare"<<endl;
                    cin>>zs;
                    cout<<endl<<"\nPentru Zi Munca"<<endl;
                    cin>>zm;

                    cout<<endl<<"\nOperatorul >>"<<endl;
                    cout<<endl<<"\nPentru Zi Sarbatoare"<<endl;
                    cout<<zs;
                    cout<<endl<<"\nPentru Zi Munca"<<endl;
                    cout<<zm;

                    /*cout<<endl<<"\nOperatorul - (scade din numarul de activitati)"<<endl;
                    zm1=zc1-10;
                    cout<<zc1;

                    cout<<endl<<"\nOperatorul += (adauga la numarul de activitati)"<<endl;
                    zm1+=10;
                    cout<<zm1;
                */
                   cout<<endl<<"\nOperatorul [] (pentru int* program)"<<endl;
                    cout<<zm1[13];

                    cout<<endl<<"\nTest functie care imi afiseaza programul zilei"<<endl<<"--------";
                    cout<<endl;

                    cout<<"\n Pentru ZiMunca"<<endl<<"--------";
                    zm1.programul_zilei();
                    cout<<endl;

                    cout<<"\n Pentru ZiSarbatoare"<<endl<<"--------";
                    zs1.programul_zilei();
                    cout<<endl<<endl;

                    break;
                    }

            case 4:

                    {
                       system("CLS");

                    cout<<"\nTESTE CLASA ACTIVITATE"<<endl<<"____________";

                    Activitate ac1; //constructor fara parametri
                    Activitate ac2(3,"Seminar"); //constructor cu parametri 2
                    Activitate ac3("Curs");//constructor cu parametri 1
                    Activitate ac4(ac3); //cc
                    Activitate ac5;//operatorul==
                    ac5=ac4;

                    cout<<"\nTeste setteri & getteri"<<endl<<"--------";
                    ac1.setNumeActivitate("Programare Dentist");
                    cout<<"\nNumele Activitatii: "<<ac1.getNumeActivitate();
                    ac1.setfrecventa(1);
                    cout<<"\nFrecventa Activitatii: "<<ac1.getfrecventa();

                    cout<<"\n\nTeste operatori"<<endl<<"--------";
                    cout<<endl<<"Operatorul >>"<<endl;
                    Activitate ac8;
                    cin.get();
                    cin>>ac8;
                    cout<<endl<<"\nOperatorul <<"<<endl;
                    cout<<ac8<<endl;
                    cout<<endl<<"\nOperatorul ++ (pre)"<<endl;
                    cout<<++ac8<<endl;
                    cout<<endl<<"\nOperatorul -- (pre)"<<endl;
                    cout<<--ac8<<endl;

                    Activitate ac9(3,"Curs");
                    ++ac9;
                    cout<<endl<<ac9<<endl;
                    cout<<"\nOperatorul < (compara numele lui ac9 cu cel al lui ac8)"<<endl;
                    if(ac9<ac8)
                        cout<<"Este mai mare";
                        else
                        cout<<"Nu este mai mare";
                    cout<<endl<<"\nOperatorul + (aduna la frecventa unei activitati)"<<endl;
                    ac2=ac2+3;//frecventa lui ac2 era 3, ar trebui sa fie 6 acum
                    cout<<ac2<<endl;
                    cout<<"\nTest functie care imi afiseaza despre activitate"<<endl<<"--------";
                    cout<<endl;
                    ac2.tip_activitate();
                    cout<<"\nTest metode pentru tip Activitate"<<endl<<"--------";
                    ac2.detalii_activitate();
                    ac2.unde();
                    cout<<endl;

                    cout<<"\nTESTE CLASA DERIVATA ACTIVITATE PROFESIONALA"<<endl<<"____________";

                    ActivitateProfesionala acp1; //constructor fara parametri
                    ActivitateProfesionala acp2("Seminar",3,"Universitate Bucuresti"); //constructor cu parametri 2
                    ActivitateProfesionala acp3(acp2); //cc
                    ActivitateProfesionala acp4;//operatorul==
                    acp4=acp3;

                    cout<<"\nTeste setteri & getteri"<<endl<<"--------";
                    acp1.setNumeActivitate("Prezentare Proiect");
                    cout<<"\nNumele Activitatii: "<<acp1.getNumeActivitate();
                    acp1.setfrecventa(1);
                    cout<<"\nFrecventa Activitatii: "<<acp1.getfrecventa();

                    cout<<"\n\nTeste operatori"<<endl<<"--------";
                    cout<<endl<<"Operatorul >>"<<endl;
                    ActivitateProfesionala acp5;
                    cin>>acp5;
                    cout<<endl<<"\nOperatorul <<"<<endl;
                    cout<<acp5<<endl;

                    cout<<"\nTest functie care imi afiseaza despre activitate"<<endl<<"--------";
                    cout<<endl;
                    acp2.tip_activitate();
                    cout<<"\nTest metode pentru tip Activitate"<<endl<<"--------";
                    acp2.detalii_activitate();
                    acp2.unde();
                    cout<<endl<<endl;

                    break;
                    }

            }

            }



            break;
        }
    }
}



    fin.close();
    fout.close();
    return 0;
}

