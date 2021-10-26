class Instrumento{
public:
    typedef enum tclase = {instrumento, percusion, cuerda, viento};
    Instrumento(string n): nombre(n), clase_(instrumento){}
    void tocar(){
        cout << "Soy un " << nombre << " y soy de tipo " << clase() << endl;
    }
    string nombre() const{return nombre;}
    string clase() const{
        switch (clase_){
            case percusion: return "percusión";
            case cuerda: return "cuerda";
            case viento: return "viento";
            default: return "instrumento";
        }
    }
protected:
    string nombre;
    tclase clase_;
}

class Percusion : public Instrumento{
public:
    Percusion(string n):Instrumento(n){clase_ = percusion;}
}
class Cuerda : public Instrumento{
public:
    Cuerda(string n):Instrumento(n){clase_ = cuerda;}
}
class Viento : public Instrumento{
public:
    Viento(string n):Instrumento(n){clase_ = viento;}
}

int main(){
    Instrumento* v = {new Percusion("tambor"), new Percusion("triangulo"), new Instrumento("teclado"), new Cuerda("piano")};
    for (auto i:v){
        i->tocar();
        delete i;
    }
    return 0;
}