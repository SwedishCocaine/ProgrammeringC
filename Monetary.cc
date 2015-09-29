//Monetary.cc
#include "Monetary.h"
#include <string>
#include <iostream>
using namespace std;

namespace monetary
{

    Money::Money (string a, int b, int c)
    {
        if(a.size() != 3 && a.size() != 0)
        {
            cerr << "Fel längd på valutabeteckning!" << endl;
            return;
        }
        
        if(b < 0)
        {
            cerr << "Antal enheter kan inte vara negativt!" << endl;
            return;
        }

        if(c < 0 || c > 99)
        {
            cerr << "Antal hundradelar har fått ett ogiltigt värde!" << endl;
            return;
        }
        currency = a;
        units = b;
        hundreds = c;
    }
    
    Money::Money (Money& m)
    {
        currency = m.cur();
        units = m.uni();
        hundreds = m.hun();
    }

    void Money::print(ostream& o_stream)
    {
        if(this->cur() != "")
        {
            o_stream << this->cur() << " ";
        }
       
        o_stream << this->uni() << ".";

        if(this->hun() < 10)
        {
            o_stream << 0;
        }

        o_stream << this->hun();

        return;
    } 

    ostream& operator<< (ostream& o, Money& m)
    {
        m.print(o);
        return o;
    }

    Money& Money::operator= (Money& rhs)
    {
        if(this->currency == rhs.currency)
        {
            this->units = rhs.units;
            this->hundreds = rhs.hundreds;
            return *this;
        }

        if(rhs.currency == "")
        {
            this->units = rhs.units;
            this->hundreds = rhs.hundreds;
            return *this;
        }

        if(this->currency == "")
        {
            this->currency = rhs.cur();
            return *this;
        }
        cerr << "En specificerad valuta får ej ändras!" << endl;
        return *this;
    }

    Money& Money::operator+ (Money& rhs)
    {
        Money m;
        int increase_units{0};
        int hundreds_to_add{this->hundreds + rhs.hundreds};

        if(hundreds_to_add > 99)
        {
            increase_units = 1;
            hundreds_to_add = hundreds_to_add - 100;
        }

        if(this->currency == rhs.currency)
        {
            m.currency = this->currency;
            m.units = this->units + rhs.units + increase_units;
            m.hundreds = hundreds_to_add;
            return m;
        }

        if(this->currency == "")
        {
            m.currency = rhs.currency;
            m.units = this->units + rhs.units + increase_units;
            m.hundreds = hundreds_to_add;
            return m;
        }
        
        if(rhs.currency == "")
        {
            m.currency = this->currency;
            m.units = this->units + rhs.units + increase_units;
            m.hundreds = hundreds_to_add;
            return m;
        }

        cerr << "Du kan inte summera två objekt av olika valutor!" << endl;
        return m;
    }

    bool Money::operator== (Money& rhs)
    {
        bool is_equal{false};
        
        if(this->currency == rhs.currency)
        {
            if((this->units == rhs.units) && (this->hundreds == rhs.hundreds))
            {
                is_equal = true;
                return is_equal;
            }

            return is_equal;
        }

        if((this->currency == "") || (rhs.currency == ""))
        {
            if((this->units == rhs.units) && (this->hundreds == rhs.hundreds))
            {
                is_equal = true;
                return is_equal;
            }

            return is_equal;
        }
        
        cerr << "Du kan inte jämföra två objekt av olika valutor!" << endl;
        return is_equal;
    }
        
    bool Money::operator< (Money& rhs)
    {
        bool is_less{false};
        
        if(this->currency == rhs.currency)
        {
            if(this->units < rhs.units)
            {
                is_less = true;
                return is_less;
            }
            
            if((this->units == rhs.units) && (this->hundreds < rhs.hundreds))
            {
                is_less = true;
                return is_less;
            }

            return is_less;
        }

        if((this->currency == "") || (rhs.currency == ""))
        {
            if(this->units < rhs.units)
            {
                is_less = true;
                return is_less;
            }
            
            if((this->units == rhs.units) && (this->hundreds < rhs.hundreds))
            {
                is_less = true;
                return is_less;
            }

            return is_less;
        }

        cerr << "Du kan inte jämföra två objekt av olika valutor!" << endl;
        return is_less;
    }

    bool Money::operator<= (Money& rhs)
    {
        bool is_less_or_equal{false};
        if((*this < rhs) || (*this == rhs))
        {
            is_less_or_equal = true;
            return is_less_or_equal;
        }
        
        return is_less_or_equal;
    }

    bool Money::operator> (Money& rhs)
    {
        bool is_greater{true};

        if(*this <= rhs)
        {
            is_greater = false;
            return is_greater;
        }

        return is_greater;
    }

    bool Money::operator>= (Money& rhs)
    {
        bool is_greater_or_equal{false};

        if((*this > rhs) || (*this == rhs))
        {
            is_greater_or_equal = true;
            return is_greater_or_equal;
        }
        
        return is_greater_or_equal;
    }

    bool Money::operator!= (Money& rhs)
    {
        bool not_equal{true};
        
        if(*this == rhs)
        {
            not_equal = false;
            return not_equal;
        }
        
        return not_equal;
    }
}

