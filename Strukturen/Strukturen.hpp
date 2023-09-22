// ========= Grundstrukturbausteine =========

const int cardBasis = 8;    // Anzahl der Basisgrößen

// ========= Strukturerklärung =========
/*
    Ein Messwert ist wiefolgt aufgebaut:

    Messwert IDENTIFIER = {
        (double) Wert,
        (double) Unsicherheit,
        (Einheit) Einheit
    };

    Dabei ist die Einheit wie folgt aufgebaut:
    Einheit IDENTIFIER = {
        (EinheitSkalierung) Skalierung,
        (EinheitExponent) Exponent
    };
    
*/


/// @brief Grundstrukturbaustein Einheitenbasis: Einträge sind Exponenten der Basisgrößen
struct EinheitSkalierung{
    int s;      // Sekunde
    int m;      // Meter
    int kg;     // Kilogramm
    int A;      // Ampere
    int K;      // Kelvin
    int mol;    // Mol
    int cd;     // Candela
    int deg;    // Grad

    /*
        @brief Punktweise Addition der Exponenten
        @param other: EinheitSkalierung, der addiert werden soll
        @return EinheitSkalierung, der die Summe der Exponenten enthält
    */
    EinheitSkalierung operator+(const EinheitSkalierung& other) const {
        EinheitSkalierung Ergebnis;

        Ergebnis.s = this->s + other.s;
        Ergebnis.m = this->m + other.m;
        Ergebnis.kg = this->kg + other.kg;
        Ergebnis.A = this->A + other.A;
        Ergebnis.K = this->K + other.K;
        Ergebnis.mol = this->mol + other.mol;
        Ergebnis.cd = this->cd + other.cd;
        Ergebnis.deg = this->deg + other.deg;

        return Ergebnis;
    }
};


/// @brief Grundstrukturbaustein EinheitenExponent: Einträge sind Normierungsfaktoren relativ zur Einheitenbasis (SI Standardeinheit)
struct EinheitExponent{
    double s;     // Sekunde
    double m;     // Meter
    double kg;    // Kilogramm
    double A;     // Ampere
    double K;     // Kelvin
    double mol;   // Mol
    double cd;    // Candela
    double deg;   // Grad

    /*
        @brief Punktweise Addition der Exponenten
        @param EinheitSkalierung: EinheitSkalierung, der mit dem EinheitExponent multipliziert werden soll
        @return EinheitSkalierung, der die Summe der Exponenten enthält
    */
    EinheitExponent operator*(const EinheitExponent& other) const {
        EinheitExponent Ergebnis;
        
        Ergebnis.s = this->s + other.s;
        Ergebnis.m = this->m + other.m;
        Ergebnis.kg = this->kg + other.kg;
        Ergebnis.A = this->A + other.A;
        Ergebnis.K = this->K + other.K;
        Ergebnis.mol = this->mol + other.mol;
        Ergebnis.cd = this->cd + other.cd;
        Ergebnis.deg = this->deg + other.deg;

        return Ergebnis;
    }
};


/*
    @brief Kombination der Grundbausteine 'EinheitSkalierung' und 'EinheitExponent' zu einer Einheitstruktur
*/
struct Einheit{
    EinheitSkalierung Skalierung;
    EinheitExponent Exponent;
};


/*
    @brief Grundstrukturbaustein Messwert: Einträge sind Zahlwert, Zahlwert 'Unsicherheit' und Einheitenstruktur
*/
struct Messwert {
    double w;               // Zahlwert
    double uw;              // Unsicherheit
    Einheit e;              // Einheit

    // ========= Normierung =========
    /*
        @brief Normiert den Messwert bezüglich seiner Einheit
        @param Messwert: Messwert, der normiert werden soll
        @return nichts, da Messwert direkt verändert wird
    */
    void EinheitenNormierung(Messwert* Messwert) {
        Messwert->w *= Messwert->e.Exponent.s;
        Messwert->w *= Messwert->e.Exponent.kg;
        Messwert->w *= Messwert->e.Exponent.m;
        Messwert->w *= Messwert->e.Exponent.A;
        Messwert->w *= Messwert->e.Exponent.K;
        Messwert->w *= Messwert->e.Exponent.mol;
        Messwert->w *= Messwert->e.Exponent.cd;
        Messwert->w *= Messwert->e.Exponent.deg;
    }



    // ========= Einheitenvergleich =========
    /*
        @brief Vergleicht zwei Einheitenstrukturen
        @param Einheit1: Einheit, die mit Einheit2 verglichen werden soll
        @param Einheit2: Einheit, die mit Einheit1 verglichen werden soll
        @return true, wenn Einheit1 und Einheit2 gleich sind
    */
    bool EinheitenVergleich(Messwert M1, Messwert M2) {
        EinheitenNormierung(&M1);
    
        if (M1.e.Skalierung.s != M2.e.Skalierung.s) return false;
        if (M1.e.Skalierung.m != M2.e.Skalierung.m) return false;
        if (M1.e.Skalierung.kg != M2.e.Skalierung.kg) return false;
        if (M1.e.Skalierung.A != M2.e.Skalierung.A) return false;
        if (M1.e.Skalierung.K != M2.e.Skalierung.K) return false;
        if (M1.e.Skalierung.mol != M2.e.Skalierung.mol) return false;
        if (M1.e.Skalierung.cd != M2.e.Skalierung.cd) return false;
        if (M1.e.Skalierung.deg != M2.e.Skalierung.deg) return false;
        
        if (M1.e.Exponent.s != M2.e.Exponent.s) return false;
        if (M1.e.Exponent.m != M2.e.Exponent.m) return false;
        if (M1.e.Exponent.kg != M2.e.Exponent.kg) return false;
        if (M1.e.Exponent.A != M2.e.Exponent.A) return false;
        if (M1.e.Exponent.K != M2.e.Exponent.K) return false;
        if (M1.e.Exponent.mol != M2.e.Exponent.mol) return false;
        if (M1.e.Exponent.cd != M2.e.Exponent.cd) return false;
        if (M1.e.Exponent.deg != M2.e.Exponent.deg) return false;
    
        return true;
    }

    /*
        @brief Punktweise Addition der Messwerte
        @param other: Messwert, der addiert werden soll
        @return Messwert, der die Summe der Messwerte enthält
    */
    Messwert operator+(const Messwert& other) const {
        if (!EinheitenVergleich(*this, other)) {
            throw "Einheiten in plus Auswertung sind nicht gleich!";
        }

        Messwert Ergebnis;

        Ergebnis.w = this->w + other.w;
        Ergebnis.uw = sqrt(pow(this->uw, 2) + pow(other.uw, 2));
        Ergebnis.e = this->e;

        return Ergebnis;
    }
};

// ========= Baukasten ========
/*
    @brief Grundstrukturbaustein Messwertpaar: Einträge sind zwei Messwerte
*/
struct Messwertpaar{
    Messwert m1;
    Messwert m2;
};

